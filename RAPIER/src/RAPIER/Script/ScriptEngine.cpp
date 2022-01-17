#include "rppch.h"
#include "ScriptEngine.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/attrdefs.h>
#include <mono/metadata/mono-gc.h>

#include <iostream>
#include <chrono>
#include <thread>

#include "ScriptEngineRegistry.h"

#include "RAPIER/Scene/Scene.h"
#include "RAPIER/Debug/Profiler.h"

#include "imgui.h"

namespace RAPIER {

	static MonoDomain* s_CurrentMonoDomain = nullptr;
	static MonoDomain* s_NewMonoDomain = nullptr;
	static std::string s_CoreAssemblyPath;
	static Ref<Scene> s_SceneContext;

	// Assembly images
	MonoImage* s_AppAssemblyImage = nullptr;
	MonoImage* s_CoreAssemblyImage = nullptr;

	static EntityInstanceMap s_EntityInstanceMap;

	static MonoMethod* GetMethod(MonoImage* image, const std::string& methodDesc);

	static MonoMethod* s_ExceptionMethod = nullptr;
	static MonoClass* s_EntityClass = nullptr;

	struct EntityScriptClass
	{
		std::string FullName;
		std::string ClassName;
		std::string NamespaceName;

		MonoClass* Class = nullptr;
		MonoMethod* Constructor = nullptr;
		MonoMethod* OnCreateMethod = nullptr;
		MonoMethod* OnDestroyMethod = nullptr;
		MonoMethod* OnUpdateMethod = nullptr;
		MonoMethod* OnPhysicsUpdateMethod = nullptr;

		// Physics
		MonoMethod* OnCollisionBeginMethod = nullptr;
		MonoMethod* OnCollisionEndMethod = nullptr;
		MonoMethod* OnTriggerBeginMethod = nullptr;
		MonoMethod* OnTriggerEndMethod = nullptr;
		MonoMethod* OnJointBreakMethod = nullptr;
		MonoMethod* OnCollision2DBeginMethod = nullptr;
		MonoMethod* OnCollision2DEndMethod = nullptr;

		void InitClassMethods(MonoImage* image)
		{
			Constructor = GetMethod(s_CoreAssemblyImage, "RAPIER.Entity:.ctor(ulong)");
			OnCreateMethod = GetMethod(image, FullName + ":OnCreate()");
			OnUpdateMethod = GetMethod(image, FullName + ":OnUpdate(single)");
			OnPhysicsUpdateMethod = GetMethod(image, FullName + ":OnPhysicsUpdate(single)");

			// Physics (Entity class)
			OnCollisionBeginMethod = GetMethod(s_CoreAssemblyImage, "RAPIER.Entity:OnCollisionBegin(ulong)");
			OnCollisionEndMethod = GetMethod(s_CoreAssemblyImage, "RAPIER.Entity:OnCollisionEnd(ulong)");
			OnTriggerBeginMethod = GetMethod(s_CoreAssemblyImage, "RAPIER.Entity:OnTriggerBegin(ulong)");
			OnTriggerEndMethod = GetMethod(s_CoreAssemblyImage, "RAPIER.Entity:OnTriggerEnd(ulong)");
			OnJointBreakMethod = GetMethod(s_CoreAssemblyImage, "RAPIER.Entity:OnJointBreak(Vector3,Vector3)");
			OnCollision2DBeginMethod = GetMethod(s_CoreAssemblyImage, "RAPIER.Entity:OnCollision2DBegin(ulong)");
			OnCollision2DEndMethod = GetMethod(s_CoreAssemblyImage, "RAPIER.Entity:OnCollision2DEnd(ulong)");
		}
	};

	MonoObject* EntityInstance::GetInstance()
	{
		RP_CORE_ASSERT(Handle, "Entity has not been instantiated!");
		return mono_gchandle_get_target(Handle);
	}

	bool EntityInstance::IsRuntimeAvailable() const
	{
		return Handle != 0;
	}

	static std::unordered_map<std::string, EntityScriptClass> s_EntityClassMap;

	MonoAssembly* LoadAssemblyFromFile(const char* filepath)
	{
		if (filepath == NULL)
		{
			return NULL;
		}

		HANDLE file = CreateFileA(filepath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (file == INVALID_HANDLE_VALUE)
		{
			return NULL;
		}

		DWORD file_size = GetFileSize(file, NULL);
		if (file_size == INVALID_FILE_SIZE)
		{
			CloseHandle(file);
			return NULL;
		}

		void* file_data = malloc(file_size);
		if (file_data == NULL)
		{
			CloseHandle(file);
			return NULL;
		}

		DWORD read = 0;
		ReadFile(file, file_data, file_size, &read, NULL);
		if (file_size != read)
		{
			free(file_data);
			CloseHandle(file);
			return NULL;
		}

		MonoImageOpenStatus status;
		MonoImage* image = mono_image_open_from_data_full(reinterpret_cast<char*>(file_data), file_size, 1, &status, 0);
		if (status != MONO_IMAGE_OK)
		{
			return NULL;
		}
		auto assemb = mono_assembly_load_from_full(image, filepath, &status, 0);
		free(file_data);
		CloseHandle(file);
		mono_image_close(image);
		return assemb;
	}

	static void InitMono()
	{
		RP_CORE_ASSERT(!s_CurrentMonoDomain, "Mono has already been initialised!");
		mono_set_assemblies_path("mono/lib");
		// mono_jit_set_trace_options("--verbose");
		auto domain = mono_jit_init("RAPIER");
	}

	static void ShutdownMono()
	{
		// Apparently according to https://www.mono-project.com/docs/advanced/embedding/
		// we can't do mono_jit_init in the same process after mono_jit_cleanup...
		// so don't do this
		// mono_jit_cleanup(s_MonoDomain);
	}

	static MonoAssembly* LoadAssembly(const std::string& path)
	{
		MonoAssembly* assembly = LoadAssemblyFromFile(path.c_str());

		if (!assembly)
			std::cout << "Could not load assembly: " << path << std::endl;
		else
			std::cout << "Successfully loaded assembly: " << path << std::endl;

		return assembly;
	}

	static MonoImage* GetAssemblyImage(MonoAssembly* assembly)
	{
		MonoImage* image = mono_assembly_get_image(assembly);
		if (!image)
			std::cout << "mono_assembly_get_image failed" << std::endl;

		return image;
	}

	static MonoClass* GetClass(MonoImage* image, const EntityScriptClass& scriptClass)
	{
		MonoClass* monoClass = mono_class_from_name(image, scriptClass.NamespaceName.c_str(), scriptClass.ClassName.c_str());
		if (!monoClass)
			std::cout << "mono_class_from_name failed" << std::endl;

		return monoClass;
	}

	static uint32_t Instantiate(EntityScriptClass& scriptClass)
	{
		RP_PROFILE_FUNC();

		// NOTE(Peter): This likes to crash when the file system watcher detects a change in a prefab file, and it's probably because we're trying to call this from a different thread other than the main thread.
		MonoObject* instance = mono_object_new(s_CurrentMonoDomain, scriptClass.Class);
		if (!instance)
			std::cout << "mono_object_new failed" << std::endl;

		mono_runtime_object_init(instance);
		uint32_t handle = mono_gchandle_new(instance, false);
		return handle;
	}

	static void Destroy(uint32_t handle)
	{
		mono_gchandle_free(handle);
	}

	static MonoMethod* GetMethod(MonoImage* image, const std::string& methodDesc)
	{
		RP_CORE_VERIFY(image);
		MonoMethodDesc* desc = mono_method_desc_new(methodDesc.c_str(), NULL);
		if (!desc)
			RP_CORE_ERROR("[ScriptEngine] mono_method_desc_new failed ({0})", methodDesc);

		MonoMethod* method = mono_method_desc_search_in_image(desc, image);
		if (!method)
			RP_CORE_WARN("[ScriptEngine] mono_method_desc_search_in_image failed ({0})", methodDesc);

		return method;
	}

	static std::string GetStringProperty(const char* propertyName, MonoClass* classType, MonoObject* object)
	{
		MonoProperty* property = mono_class_get_property_from_name(classType, propertyName);
		MonoMethod* getterMethod = mono_property_get_get_method(property);
		MonoString* string = (MonoString*)mono_runtime_invoke(getterMethod, object, NULL, NULL);
		return string != nullptr ? std::string(mono_string_to_utf8(string)) : "";
	}

	static MonoObject* CallMethod(MonoObject* object, MonoMethod* method, void** params = nullptr)
	{
		MonoObject* pException = nullptr;
		MonoObject* result = mono_runtime_invoke(method, object, params, &pException);
		if (pException)
		{
			MonoClass* exceptionClass = mono_object_get_class(pException);
			MonoType* exceptionType = mono_class_get_type(exceptionClass);
			const char* typeName = mono_type_get_name(exceptionType);
			std::string message = GetStringProperty("Message", exceptionClass, pException);
			std::string stackTrace = GetStringProperty("StackTrace", exceptionClass, pException);

			RP_CONSOLE_ERROR("{0}: {1}. Stack Trace: {2}", typeName, message, stackTrace);

			void* args[] = { pException };
			MonoObject* result = mono_runtime_invoke(s_ExceptionMethod, nullptr, args, nullptr);
		}
		return result;
	}

	static void PrintClassMethods(MonoClass* monoClass)
	{
		MonoMethod* iter;
		void* ptr = 0;
		while ((iter = mono_class_get_methods(monoClass, &ptr)) != NULL)
		{
			printf("--------------------------------\n");
			const char* name = mono_method_get_name(iter);
			MonoMethodDesc* methodDesc = mono_method_desc_from_method(iter);

			const char* paramNames = "";
			mono_method_get_param_names(iter, &paramNames);

			printf("Name: %s\n", name);
			printf("Full name: %s\n", mono_method_full_name(iter, true));
		}
	}

	static void PrintClassProperties(MonoClass* monoClass)
	{
		MonoProperty* iter;
		void* ptr = 0;
		while ((iter = mono_class_get_properties(monoClass, &ptr)) != NULL)
		{
			printf("--------------------------------\n");
			const char* name = mono_property_get_name(iter);

			printf("Name: %s\n", name);
		}
	}

	static MonoAssembly* s_AppAssembly = nullptr;
	static MonoAssembly* s_CoreAssembly = nullptr;
	static MonoAssembly* s_CoreAssemblyToUnload = nullptr;

	static MonoString* GetName()
	{
		return mono_string_new(s_CurrentMonoDomain, "Hello!");
	}

	static bool s_PostLoadCleanup = false;

	bool ScriptEngine::LoadRapierRuntimeAssembly(const std::string& path)
	{
		s_CoreAssemblyPath = path;
		if (s_CurrentMonoDomain)
		{
			s_NewMonoDomain = mono_domain_create_appdomain("RAPIER Runtime", nullptr);
			mono_domain_set(s_NewMonoDomain, false);
			s_PostLoadCleanup = true;
		}
		else
		{
			s_CurrentMonoDomain = mono_domain_create_appdomain("RAPIER Runtime", nullptr);
			mono_domain_set(s_CurrentMonoDomain, false);
			s_PostLoadCleanup = false;
		}

		s_CoreAssemblyToUnload = s_CoreAssembly;
		s_CoreAssembly = LoadAssembly(s_CoreAssemblyPath);
		if (!s_CoreAssembly)
			return false;

		s_CoreAssemblyImage = GetAssemblyImage(s_CoreAssembly);

		s_ExceptionMethod = GetMethod(s_CoreAssemblyImage, "RAPIER.RuntimeException:OnException(object)");
		s_EntityClass = mono_class_from_name(s_CoreAssemblyImage, "RAPIER", "Entity");

		return true;
	}

	bool ScriptEngine::LoadAppAssembly(const std::string& path)
	{
		if (s_AppAssembly)
		{
			s_AppAssembly = nullptr;
			s_AppAssemblyImage = nullptr;
			return ReloadAssembly(path);
		}

		auto appAssembly = LoadAssembly(path);
		if (!appAssembly)
			return false;

		auto appAssemblyImage = GetAssemblyImage(appAssembly);
		ScriptEngineRegistry::RegisterAll();

		if (s_PostLoadCleanup)
		{
			mono_domain_unload(s_CurrentMonoDomain);
			if (s_CoreAssemblyToUnload)
			{
				//mono_assembly_close(s_CoreAssemblyToUnload);
				s_CoreAssemblyToUnload = nullptr;
			}
			s_CurrentMonoDomain = s_NewMonoDomain;
			s_NewMonoDomain = nullptr;

			//mono_assembly_close(s_AppAssembly);
			s_AppAssembly = nullptr;
		}

		s_AppAssembly = appAssembly;
		s_AppAssemblyImage = appAssemblyImage;
		return true;
	}

	bool ScriptEngine::ReloadAssembly(const std::string& path)
	{
		if (!LoadRapierRuntimeAssembly(s_CoreAssemblyPath))
			return false;

		if (!LoadAppAssembly(path))
			return false;

		if (s_EntityInstanceMap.size())
		{
			Ref<Scene> scene = ScriptEngine::GetCurrentSceneContext();
			RP_CORE_ASSERT(scene, "No active scene!");
			if (auto& entityInstanceMap = s_EntityInstanceMap.find(scene->GetUUID()); entityInstanceMap != s_EntityInstanceMap.end())
			{
				const auto& entityMap = scene->GetEntityMap();
				for (auto& [entityID, entityInstanceData] : entityInstanceMap->second)
				{
					RP_CORE_ASSERT(entityMap.find(entityID) != entityMap.end(), "Invalid entity ID or entity doesn't exist in scene!");
					InitScriptEntity(entityMap.at(entityID));
				}
			}
		}

		return true;
	}

	void ScriptEngine::Init(const std::string& assemblyPath)
	{
		InitMono();
		LoadRapierRuntimeAssembly(assemblyPath);
	}

	void ScriptEngine::Shutdown()
	{
		ShutdownMono();
		s_SceneContext = nullptr;
		s_EntityInstanceMap.clear();
	}

	void ScriptEngine::OnSceneDestruct(UUID sceneID)
	{
		if (s_EntityInstanceMap.find(sceneID) != s_EntityInstanceMap.end())
		{
			s_EntityInstanceMap.at(sceneID).clear();
			s_EntityInstanceMap.erase(sceneID);
		}
	}

	static std::unordered_map<std::string, MonoClass*> s_Classes;
	void ScriptEngine::SetSceneContext(const Ref<Scene>& scene)
	{
		s_Classes.clear();
		if (!scene)
			s_EntityInstanceMap.clear();
		s_SceneContext = scene;
	}

	const Ref<Scene>& ScriptEngine::GetCurrentSceneContext()
	{
		return s_SceneContext;
	}

	void ScriptEngine::CopyEntityScriptData(UUID dst, UUID src)
	{
		RP_CORE_ASSERT(s_EntityInstanceMap.find(dst) != s_EntityInstanceMap.end());
		RP_CORE_ASSERT(s_EntityInstanceMap.find(src) != s_EntityInstanceMap.end());

		auto& dstEntityMap = s_EntityInstanceMap.at(dst);
		auto& srcEntityMap = s_EntityInstanceMap.at(src);

		for (auto& [entityID, entityInstanceData] : srcEntityMap)
		{
			for (auto& [moduleName, srcFieldMap] : srcEntityMap.at(entityID).ModuleFieldMap)
			{
				auto& dstModuleFieldMap = dstEntityMap[entityID].ModuleFieldMap;
				for (auto& [fieldName, field] : srcFieldMap)
				{
					RP_CORE_ASSERT(dstModuleFieldMap.find(moduleName) != dstModuleFieldMap.end());
					auto& fieldMap = dstModuleFieldMap.at(moduleName);
					RP_CORE_ASSERT(fieldMap.find(fieldName) != fieldMap.end());
					fieldMap.at(fieldName).SetStoredValueRaw(field.m_StoredValueBuffer);
				}
			}
		}
	}

	void ScriptEngine::OnCreateEntity(Entity entity)
	{
		RP_PROFILE_FUNC();

		EntityInstance& entityInstance = GetEntityInstanceData(entity.GetSceneUUID(), entity.GetUUID()).Instance;
		if (entityInstance.ScriptClass->OnCreateMethod)
			CallMethod(entityInstance.GetInstance(), entityInstance.ScriptClass->OnCreateMethod);
	}

	void ScriptEngine::OnUpdateEntity(Entity entity, Timestep ts)
	{
		RP_PROFILE_FUNC();
		EntityInstance& entityInstance = GetEntityInstanceData(entity.GetSceneUUID(), entity.GetUUID()).Instance;
		entityInstance.ScriptClass->FullName.c_str();
		if (entityInstance.ScriptClass->OnUpdateMethod)
		{
			void* args[] = { &ts };
			CallMethod(entityInstance.GetInstance(), entityInstance.ScriptClass->OnUpdateMethod, args);
		}
	}

	void ScriptEngine::OnPhysicsUpdateEntity(Entity entity, float fixedTimeStep)
	{
		RP_PROFILE_FUNC();
		EntityInstance& entityInstance = GetEntityInstanceData(entity.GetSceneUUID(), entity.GetUUID()).Instance;
		if (entityInstance.ScriptClass->OnPhysicsUpdateMethod)
		{
			void* args[] = { &fixedTimeStep };
			CallMethod(entityInstance.GetInstance(), entityInstance.ScriptClass->OnPhysicsUpdateMethod, args);
		}
	}

	void ScriptEngine::OnCollision2DBegin(Entity entity, Entity other)
	{
		RP_PROFILE_FUNC();
		EntityInstance& entityInstance = GetEntityInstanceData(entity.GetSceneUUID(), entity.GetUUID()).Instance;
		if (entityInstance.ScriptClass->OnCollision2DBeginMethod)
		{
			UUID id = other.GetUUID();
			void* args[] = { &id };
			CallMethod(entityInstance.GetInstance(), entityInstance.ScriptClass->OnCollision2DBeginMethod, args);
		}
	}

	void ScriptEngine::OnCollision2DEnd(Entity entity, Entity other)
	{
		RP_PROFILE_FUNC();
		EntityInstance& entityInstance = GetEntityInstanceData(entity.GetSceneUUID(), entity.GetUUID()).Instance;
		if (entityInstance.ScriptClass->OnCollision2DEndMethod)
		{
			UUID id = other.GetUUID();
			void* args[] = { &id };
			CallMethod(entityInstance.GetInstance(), entityInstance.ScriptClass->OnCollision2DEndMethod, args);
		}
	}

	void ScriptEngine::OnCollisionBegin(Entity entity, Entity other)
	{
		RP_PROFILE_FUNC();
		EntityInstance& entityInstance = GetEntityInstanceData(entity.GetSceneUUID(), entity.GetUUID()).Instance;
		if (entityInstance.ScriptClass->OnCollisionBeginMethod)
		{
			UUID id = other.GetUUID();
			void* args[] = { &id };
			CallMethod(entityInstance.GetInstance(), entityInstance.ScriptClass->OnCollisionBeginMethod, args);
		}
	}

	void ScriptEngine::OnCollisionEnd(Entity entity, Entity other)
	{
		RP_PROFILE_FUNC();
		EntityInstance& entityInstance = GetEntityInstanceData(entity.GetSceneUUID(), entity.GetUUID()).Instance;
		if (entityInstance.ScriptClass->OnCollisionEndMethod)
		{
			UUID id = other.GetUUID();
			void* args[] = { &id };
			CallMethod(entityInstance.GetInstance(), entityInstance.ScriptClass->OnCollisionEndMethod, args);
		}
	}

	void ScriptEngine::OnTriggerBegin(Entity entity, Entity other)
	{
		RP_PROFILE_FUNC();
		EntityInstance& entityInstance = GetEntityInstanceData(entity.GetSceneUUID(), entity.GetUUID()).Instance;
		if (entityInstance.ScriptClass->OnTriggerBeginMethod)
		{
			UUID id = other.GetUUID();
			void* args[] = { &id };
			CallMethod(entityInstance.GetInstance(), entityInstance.ScriptClass->OnTriggerBeginMethod, args);
		}
	}

	void ScriptEngine::OnTriggerEnd(Entity entity, Entity other)
	{
		RP_PROFILE_FUNC();
		EntityInstance& entityInstance = GetEntityInstanceData(entity.GetSceneUUID(), entity.GetUUID()).Instance;
		if (entityInstance.ScriptClass->OnTriggerEndMethod)
		{
			UUID id = other.GetUUID();
			void* args[] = { &id };
			CallMethod(entityInstance.GetInstance(), entityInstance.ScriptClass->OnTriggerEndMethod, args);
		}
	}

	void ScriptEngine::OnJointBreak(Entity entity, const glm::vec3& linearForce, const glm::vec3& angularForce)
	{
		RP_PROFILE_FUNC();
		EntityInstance& entityInstance = GetEntityInstanceData(entity.GetSceneUUID(), entity.GetUUID()).Instance;
		if (entityInstance.ScriptClass->OnJointBreakMethod)
		{
			void* args[] = { (void*)&linearForce, (void*)&angularForce };
			CallMethod(entityInstance.GetInstance(), entityInstance.ScriptClass->OnJointBreakMethod, args);
		}
	}

	MonoObject* ScriptEngine::Construct(const std::string& fullName, bool callConstructor, void** parameters)
	{
		std::string namespaceName;
		std::string className;
		std::string parameterList;

		if (fullName.find(".") != std::string::npos)
		{
			namespaceName = fullName.substr(0, fullName.find_first_of('.'));
			className = fullName.substr(fullName.find_first_of('.') + 1, (fullName.find_first_of(':') - fullName.find_first_of('.')) - 1);
		}

		if (fullName.find(":") != std::string::npos)
		{
			parameterList = fullName.substr(fullName.find_first_of(':'));
		}

		MonoClass* clazz = mono_class_from_name(s_CoreAssemblyImage, namespaceName.c_str(), className.c_str());
		RP_CORE_ASSERT(clazz, "Could not find class!");
		MonoObject* obj = mono_object_new(mono_domain_get(), clazz);

		if (callConstructor)
		{
			MonoMethodDesc* desc = mono_method_desc_new(parameterList.c_str(), NULL);
			MonoMethod* constructor = mono_method_desc_search_in_class(desc, clazz);
			MonoObject* exception = nullptr;
			mono_runtime_invoke(constructor, obj, parameters, &exception);
		}

		return obj;
	}

	MonoClass* ScriptEngine::GetCoreClass(const std::string& fullName)
	{
		if (s_Classes.find(fullName) != s_Classes.end())
			return s_Classes[fullName];

		std::string namespaceName = "";
		std::string className;

		if (fullName.find('.') != std::string::npos)
		{
			namespaceName = fullName.substr(0, fullName.find_last_of('.'));
			className = fullName.substr(fullName.find_last_of('.') + 1);
		}
		else
		{
			className = fullName;
		}

		MonoClass* monoClass = mono_class_from_name(s_CoreAssemblyImage, namespaceName.c_str(), className.c_str());
		if (!monoClass)
			std::cout << "mono_class_from_name failed" << std::endl;

		s_Classes[fullName] = monoClass;

		return monoClass;
	}

	bool ScriptEngine::IsEntityModuleValid(Entity entity)
	{
		return entity.HasComponent<ScriptComponent>() && ModuleExists(entity.GetComponent<ScriptComponent>().ModuleName);
	}

	void ScriptEngine::OnScriptComponentDestroyed(UUID sceneID, UUID entityID)
	{
		if (s_EntityInstanceMap.find(sceneID) != s_EntityInstanceMap.end())
		{
			auto& entityMap = s_EntityInstanceMap.at(sceneID);
			//RP_CORE_ASSERT(entityMap.find(entityID) != entityMap.end());
			if (entityMap.find(entityID) != entityMap.end())
				entityMap.erase(entityID);
		}
	}

	bool ScriptEngine::ModuleExists(const std::string& moduleName)
	{
		RP_PROFILE_FUNC();

		if (!s_AppAssemblyImage) // No assembly loaded
			return false;

		std::string NamespaceName, ClassName;
		if (moduleName.find('.') != std::string::npos)
		{
			NamespaceName = moduleName.substr(0, moduleName.find_last_of('.'));
			ClassName = moduleName.substr(moduleName.find_last_of('.') + 1);
		}
		else
		{
			ClassName = moduleName;
		}

		MonoClass* monoClass = mono_class_from_name(s_AppAssemblyImage, NamespaceName.c_str(), ClassName.c_str());
		if (!monoClass)
			return false;

		auto isEntitySubclass = mono_class_is_subclass_of(monoClass, s_EntityClass, 0);
		return isEntitySubclass;
	}

	std::string ScriptEngine::StripNamespace(const std::string& nameSpace, const std::string& moduleName)
	{
		std::string name = moduleName;
		size_t pos = name.find(nameSpace + ".");
		if (pos == 0)
			name.erase(pos, nameSpace.length() + 1);
		return name;
	}

	static FieldType GetRAPIERFieldType(MonoType* monoType)
	{
		int type = mono_type_get_type(monoType);
		switch (type)
		{
		case MONO_TYPE_BOOLEAN: return FieldType::Bool;
		case MONO_TYPE_R4: return FieldType::Float;
		case MONO_TYPE_I4: return FieldType::Int;
		case MONO_TYPE_U4: return FieldType::UnsignedInt;
		case MONO_TYPE_STRING: return FieldType::String;
		case MONO_TYPE_CLASS:
		{
			char* name = mono_type_get_name(monoType);
			if (strcmp(name, "RAPIER.Prefab") == 0) return FieldType::Asset;
			if (strcmp(name, "RAPIER.Entity") == 0) return FieldType::Entity;
			return FieldType::ClassReference;
		}
		case MONO_TYPE_VALUETYPE:
		{
			char* name = mono_type_get_name(monoType);
			if (strcmp(name, "RAPIER.Vector2") == 0) return FieldType::Vec2;
			if (strcmp(name, "RAPIER.Vector3") == 0) return FieldType::Vec3;
			if (strcmp(name, "RAPIER.Vector4") == 0) return FieldType::Vec4;
		}
		}
		return FieldType::None;
	}

	void ScriptEngine::InitScriptEntity(Entity entity)
	{
		RP_PROFILE_FUNC();

		Scene* scene = entity.m_Scene;
		UUID id = entity.GetComponent<IDComponent>().ID;
		RP_CORE_TRACE("InitScriptEntity {0} ({1})", id, entity.m_EntityHandle);
		auto& moduleName = entity.GetComponent<ScriptComponent>().ModuleName;
		if (moduleName.empty())
			return;

		if (!ModuleExists(moduleName))
		{
			RP_CORE_ERROR("Entity references non-existent script module '{0}'", moduleName);
			return;
		}

		EntityScriptClass& scriptClass = s_EntityClassMap[moduleName];
		scriptClass.FullName = moduleName;
		if (moduleName.find('.') != std::string::npos)
		{
			scriptClass.NamespaceName = moduleName.substr(0, moduleName.find_last_of('.'));
			scriptClass.ClassName = moduleName.substr(moduleName.find_last_of('.') + 1);
		}
		else
		{
			scriptClass.ClassName = moduleName;
		}

		scriptClass.Class = GetClass(s_AppAssemblyImage, scriptClass);
		scriptClass.InitClassMethods(s_AppAssemblyImage);

		EntityInstanceData& entityInstanceData = s_EntityInstanceMap[scene->GetUUID()][id];
		EntityInstance& entityInstance = entityInstanceData.Instance;
		entityInstance.ScriptClass = &scriptClass;

		ScriptComponent& scriptComponent = entity.GetComponent<ScriptComponent>();
		ScriptModuleFieldMap& moduleFieldMap = scriptComponent.ModuleFieldMap;
		auto& fieldMap = moduleFieldMap[moduleName];

		// Save old fields
		// The point of this is that if you reload the script entity, then the values
		// of fields and properties will be preserved (so long as the reloaded entity still has those fields, and they
		// are the same type)
		std::unordered_map<std::string, PublicField> oldFields;
		oldFields.reserve(fieldMap.size());
		for (auto& [fieldName, field] : fieldMap)
			oldFields.emplace(fieldName, std::move(field));

		// Default construct an instance of the script class
		// We then use this to set initial values for any public fields that are
		// not already in the fieldMap
		entityInstance.Handle = Instantiate(*entityInstance.ScriptClass);

		void* param[] = { &id };
		CallMethod(entityInstance.GetInstance(), entityInstance.ScriptClass->Constructor, param);

		// Retrieve public fields (TODO: cache these fields if the module is used more than once)
		fieldMap.clear();
		{
			MonoClassField* iter;
			void* ptr = 0;
			while ((iter = mono_class_get_fields(scriptClass.Class, &ptr)) != NULL)
			{
				const char* name = mono_field_get_name(iter);
				uint32_t flags = mono_field_get_flags(iter);
				if ((flags & MONO_FIELD_ATTR_PUBLIC) == 0)
					continue;

				MonoType* fieldType = mono_field_get_type(iter);
				FieldType RAPIERFieldType = GetRAPIERFieldType(fieldType);

				char* typeName = mono_type_get_name(fieldType);

				auto old = oldFields.find(name);
				if ((old != oldFields.end()) && (old->second.TypeName == typeName))
				{
					fieldMap.emplace(name, std::move(oldFields.at(name)));
					PublicField& field = fieldMap.at(name);
					field.m_MonoClassField = iter;
					continue;
				}

				if (RAPIERFieldType == FieldType::None || RAPIERFieldType == FieldType::ClassReference)
					continue;

				// TODO: Attributes
				MonoCustomAttrInfo* attr = mono_custom_attrs_from_field(scriptClass.Class, iter);

				PublicField field = { name, typeName, RAPIERFieldType };
				field.m_MonoClassField = iter;
				field.CopyStoredValueFromRuntime(entityInstance);
				fieldMap.emplace(name, std::move(field));
			}
		}

		{
			MonoProperty* iter;
			void* ptr = 0;
			while ((iter = mono_class_get_properties(scriptClass.Class, &ptr)) != NULL)
			{
				const char* propertyName = mono_property_get_name(iter);

				if (oldFields.find(propertyName) != oldFields.end())
				{
					fieldMap.emplace(propertyName, std::move(oldFields.at(propertyName)));
					PublicField& field = fieldMap.at(propertyName);
					field.m_MonoProperty = iter;
					continue;
				}

				MonoMethod* propertySetter = mono_property_get_set_method(iter);
				MonoMethod* propertyGetter = mono_property_get_get_method(iter);

				uint32_t setterFlags = 0;
				uint32_t getterFlags = 0;

				bool isReadOnly = false;
				MonoType* monoType = nullptr;

				if (propertySetter)
				{
					void* i = nullptr;
					MonoMethodSignature* sig = mono_method_signature(propertySetter);
					setterFlags = mono_method_get_flags(propertySetter, nullptr);
					isReadOnly = (setterFlags & MONO_METHOD_ATTR_PRIVATE) != 0;
					monoType = mono_signature_get_params(sig, &i);
				}
				else if (propertyGetter)
				{
					MonoMethodSignature* sig = mono_method_signature(propertyGetter);
					getterFlags = mono_method_get_flags(propertyGetter, nullptr);
					monoType = mono_signature_get_return_type(sig);

					if ((getterFlags & MONO_METHOD_ATTR_PRIVATE) != 0)
						continue;
				}

				if ((setterFlags & MONO_METHOD_ATTR_STATIC) != 0)
					continue;

				if (monoType == nullptr)
					continue;

				FieldType type = GetRAPIERFieldType(monoType);
				if (type == FieldType::ClassReference)
					continue;

				if (propertySetter == nullptr)
					isReadOnly = true;

				char* typeName = mono_type_get_name(monoType);

				PublicField field = { propertyName, typeName, type, isReadOnly };
				field.m_MonoProperty = iter;
				field.CopyStoredValueFromRuntime(entityInstance);
				fieldMap.emplace(propertyName, std::move(field));
			}
		}

		Destroy(entityInstance.Handle);
	}

	void ScriptEngine::ShutdownScriptEntity(Entity entity, const std::string& moduleName)
	{
		{
			EntityInstanceData& entityInstanceData = GetEntityInstanceData(entity.GetSceneUUID(), entity.GetUUID());
			ScriptModuleFieldMap& moduleFieldMap = entityInstanceData.ModuleFieldMap;
			if (moduleFieldMap.find(moduleName) != moduleFieldMap.end())
				moduleFieldMap.erase(moduleName);
		}

		{
			ScriptComponent& scriptComponent = entity.GetComponent<ScriptComponent>();
			ScriptModuleFieldMap& moduleFieldMap = scriptComponent.ModuleFieldMap;
			if (moduleFieldMap.find(moduleName) != moduleFieldMap.end())
				moduleFieldMap.erase(moduleName);
		}
	}


	void ScriptEngine::InstantiateEntityClass(Entity entity)
	{
		RP_PROFILE_FUNC();

		Scene* scene = entity.m_Scene;
		UUID id = entity.GetComponent<IDComponent>().ID;
		RP_CORE_TRACE("InstantiateEntityClass {0} ({1})", id, entity.m_EntityHandle);
		ScriptComponent& scriptComponent = entity.GetComponent<ScriptComponent>();
		auto& moduleName = scriptComponent.ModuleName;

		EntityInstanceData& entityInstanceData = GetEntityInstanceData(scene->GetUUID(), id);
		EntityInstance& entityInstance = entityInstanceData.Instance;
		RP_CORE_ASSERT(entityInstance.ScriptClass);
		entityInstance.Handle = Instantiate(*entityInstance.ScriptClass);

		void* param[] = { &id };
		CallMethod(entityInstance.GetInstance(), entityInstance.ScriptClass->Constructor, param);

		// Set all public fields to appropriate values
		ScriptModuleFieldMap& moduleFieldMap = scriptComponent.ModuleFieldMap;
		if (moduleFieldMap.find(moduleName) != moduleFieldMap.end())
		{
			auto& publicFields = moduleFieldMap.at(moduleName);
			for (auto& [name, field] : publicFields)
				field.CopyStoredValueToRuntime(entityInstance);
		}
	}

	EntityInstanceData& ScriptEngine::GetEntityInstanceData(UUID sceneID, UUID entityID)
	{
		RP_CORE_ASSERT(s_EntityInstanceMap.find(sceneID) != s_EntityInstanceMap.end(), "Invalid scene ID!");
		auto& entityIDMap = s_EntityInstanceMap.at(sceneID);

		// Entity hasn't been initialized yet
		if (entityIDMap.find(entityID) == entityIDMap.end())
			ScriptEngine::InitScriptEntity(s_SceneContext->GetEntityMap().at(entityID));

		return entityIDMap.at(entityID);
	}

	EntityInstanceMap& ScriptEngine::GetEntityInstanceMap()
	{
		return s_EntityInstanceMap;
	}

	static uint32_t GetFieldSize(FieldType type)
	{
		switch (type)
		{
		case FieldType::Bool:		 return 1;
		case FieldType::Float:       return 4;
		case FieldType::Int:         return 4;
		case FieldType::UnsignedInt: return 4;
		case FieldType::String:      return 8;
		case FieldType::Vec2:        return 4 * 2;
		case FieldType::Vec3:        return 4 * 3;
		case FieldType::Vec4:        return 4 * 4;
		case FieldType::Asset:       return 8;
		case FieldType::Entity:		 return 8;
		}
		RP_CORE_ASSERT(false, "Unknown field type!");
		return 0;
	}

	PublicField::PublicField(const std::string& name, const std::string& typeName, FieldType type, bool isReadOnly)
		: Name(name), TypeName(typeName), Type(type), IsReadOnly(isReadOnly)
	{
		if (Type != FieldType::String)
			m_StoredValueBuffer = AllocateBuffer(Type);
	}

	PublicField::PublicField(const PublicField& other)
		: Name(other.Name), TypeName(other.TypeName), Type(other.Type), IsReadOnly(other.IsReadOnly)
	{
		if (Type != FieldType::String)
		{
			m_StoredValueBuffer = AllocateBuffer(Type);
			memcpy(m_StoredValueBuffer, other.m_StoredValueBuffer, GetFieldSize(Type));
		}
		else
		{
			m_StoredValueBuffer = other.m_StoredValueBuffer;
		}

		m_MonoClassField = other.m_MonoClassField;
		m_MonoProperty = other.m_MonoProperty;
	}

	PublicField& PublicField::operator=(const PublicField& other)
	{
		if (&other != this)
		{
			Name = other.Name;
			TypeName = other.TypeName;
			Type = other.Type;
			IsReadOnly = other.IsReadOnly;
			m_MonoClassField = other.m_MonoClassField;
			m_MonoProperty = other.m_MonoProperty;
			if (Type != FieldType::String)
			{
				m_StoredValueBuffer = AllocateBuffer(Type);
				memcpy(m_StoredValueBuffer, other.m_StoredValueBuffer, GetFieldSize(Type));
			}
			else
			{
				m_StoredValueBuffer = other.m_StoredValueBuffer;
			}
		}

		return *this;
	}

	PublicField::PublicField(PublicField&& other)
	{
		Name = std::move(other.Name);
		TypeName = std::move(other.TypeName);
		Type = other.Type;
		IsReadOnly = other.IsReadOnly;
		m_MonoClassField = other.m_MonoClassField;
		m_MonoProperty = other.m_MonoProperty;
		m_StoredValueBuffer = other.m_StoredValueBuffer;

		other.m_MonoClassField = nullptr;
		other.m_MonoProperty = nullptr;
		if (Type != FieldType::String)
			other.m_StoredValueBuffer = nullptr;
	}

	PublicField::~PublicField()
	{
		if (Type != FieldType::String)
			delete[] m_StoredValueBuffer;
	}

	void PublicField::CopyStoredValueToRuntime(EntityInstance& entityInstance)
	{
		RP_CORE_ASSERT(entityInstance.GetInstance());

		if (IsReadOnly)
			return;

		if (Type == FieldType::ClassReference)
		{
			RP_CORE_VERIFY(!TypeName.empty());

			// Create Managed Object
			void* params[] = {
				&m_StoredValueBuffer
			};
			MonoObject* obj = ScriptEngine::Construct(TypeName + ":.ctor(intptr)", true, params);
			mono_field_set_value(entityInstance.GetInstance(), m_MonoClassField, obj);
		}
		else if (Type == FieldType::Asset || Type == FieldType::Entity)
		{
			RP_CORE_VERIFY(!TypeName.empty());

			// Create Managed Object
			void* params[] = { m_StoredValueBuffer };
			MonoObject* obj = ScriptEngine::Construct(TypeName + ":.ctor(ulong)", true, params);
			if (m_MonoProperty)
			{
				void* data[] = { obj };
				mono_property_set_value(m_MonoProperty, entityInstance.GetInstance(), data, nullptr);
			}
			else
			{
				mono_field_set_value(entityInstance.GetInstance(), m_MonoClassField, obj);
			}
		}
		else if (Type == FieldType::String)
		{
			SetRuntimeValue_Internal(entityInstance, *(std::string*)m_StoredValueBuffer);
		}
		else
		{
			SetRuntimeValue_Internal(entityInstance, m_StoredValueBuffer);
		}
	}

	void PublicField::CopyStoredValueFromRuntime(EntityInstance& entityInstance)
	{
		RP_CORE_ASSERT(entityInstance.GetInstance());

		if (Type == FieldType::String)
		{
			if (m_MonoProperty)
			{
				MonoString* str = (MonoString*)mono_property_get_value(m_MonoProperty, entityInstance.GetInstance(), nullptr, nullptr);
				ScriptEngine::s_PublicFieldStringValue[Name] = mono_string_to_utf8(str);
				m_StoredValueBuffer = (uint8_t*)&ScriptEngine::s_PublicFieldStringValue[Name];
			}
			else
			{
				MonoString* str;
				mono_field_get_value(entityInstance.GetInstance(), m_MonoClassField, &str);
				ScriptEngine::s_PublicFieldStringValue[Name] = mono_string_to_utf8(str);
				m_StoredValueBuffer = (uint8_t*)&ScriptEngine::s_PublicFieldStringValue[Name];
			}
		}
		else
		{
			if (m_MonoProperty)
			{
				MonoObject* result = mono_property_get_value(m_MonoProperty, entityInstance.GetInstance(), nullptr, nullptr);
				memcpy(m_StoredValueBuffer, mono_object_unbox(result), GetFieldSize(Type));
			}
			else
			{
				mono_field_get_value(entityInstance.GetInstance(), m_MonoClassField, m_StoredValueBuffer);
			}
		}
	}

	void PublicField::SetStoredValueRaw(void* src)
	{
		if (IsReadOnly)
			return;

		uint32_t size = GetFieldSize(Type);
		memcpy(m_StoredValueBuffer, src, size);
	}

	void PublicField::SetRuntimeValueRaw(EntityInstance& entityInstance, void* src)
	{
		RP_CORE_ASSERT(entityInstance.GetInstance());

		if (IsReadOnly)
			return;

		if (m_MonoProperty)
		{
			void* data[] = { src };
			mono_property_set_value(m_MonoProperty, entityInstance.GetInstance(), data, nullptr);
		}
		else
		{
			mono_field_set_value(entityInstance.GetInstance(), m_MonoClassField, src);
		}
	}

	void* PublicField::GetRuntimeValueRaw(EntityInstance& entityInstance)
	{
		RP_CORE_ASSERT(entityInstance.GetInstance());

		uint8_t* outValue = nullptr;
		mono_field_get_value(entityInstance.GetInstance(), m_MonoClassField, outValue);
		return outValue;
	}

	uint8_t* PublicField::AllocateBuffer(FieldType type)
	{
		uint32_t size = GetFieldSize(type);
		uint8_t* buffer = new uint8_t[size];
		memset(buffer, 0, size);
		return buffer;
	}

	void PublicField::SetStoredValue_Internal(void* value)
	{
		if (IsReadOnly)
			return;

		uint32_t size = GetFieldSize(Type);
		memcpy(m_StoredValueBuffer, value, size);
	}

	void PublicField::GetStoredValue_Internal(void* outValue) const
	{
		uint32_t size = GetFieldSize(Type);
		memcpy(outValue, m_StoredValueBuffer, size);
	}

	void PublicField::SetRuntimeValue_Internal(EntityInstance& entityInstance, void* value)
	{
		RP_CORE_ASSERT(entityInstance.GetInstance());

		if (IsReadOnly)
			return;

		if (m_MonoProperty)
		{
			void* data[] = { value };
			mono_property_set_value(m_MonoProperty, entityInstance.GetInstance(), data, nullptr);
		}
		else
		{
			mono_field_set_value(entityInstance.GetInstance(), m_MonoClassField, value);
		}
	}

	void PublicField::SetRuntimeValue_Internal(EntityInstance& entityInstance, const std::string& value)
	{
		if (IsReadOnly)
			return;

		RP_CORE_ASSERT(entityInstance.GetInstance());

		MonoString* monoString = mono_string_new(mono_domain_get(), value.c_str());

		if (m_MonoProperty)
		{
			void* data[] = { monoString };
			mono_property_set_value(m_MonoProperty, entityInstance.GetInstance(), data, nullptr);
		}
		else
		{
			mono_field_set_value(entityInstance.GetInstance(), m_MonoClassField, monoString);
		}
	}

	void PublicField::GetRuntimeValue_Internal(EntityInstance& entityInstance, void* outValue) const
	{
		RP_CORE_ASSERT(entityInstance.GetInstance());

		if (Type == FieldType::Entity)
		{
			MonoObject* obj;
			if (m_MonoProperty)
				obj = mono_property_get_value(m_MonoProperty, entityInstance.GetInstance(), nullptr, nullptr);
			else
				mono_field_get_value(entityInstance.GetInstance(), m_MonoClassField, &obj);

			MonoProperty* idProperty = mono_class_get_property_from_name(entityInstance.ScriptClass->Class, "ID");
			MonoObject* idObject = mono_property_get_value(idProperty, obj, nullptr, nullptr);
			memcpy(outValue, mono_object_unbox(idObject), GetFieldSize(Type));
		}
		else
		{
			if (m_MonoProperty)
			{
				MonoObject* result = mono_property_get_value(m_MonoProperty, entityInstance.GetInstance(), nullptr, nullptr);
				memcpy(outValue, mono_object_unbox(result), GetFieldSize(Type));
			}
			else
			{
				mono_field_get_value(entityInstance.GetInstance(), m_MonoClassField, outValue);
			}
		}

	}

	void PublicField::GetRuntimeValue_Internal(EntityInstance& entityInstance, std::string& outValue) const
	{
		RP_CORE_ASSERT(entityInstance.GetInstance());

		MonoString* monoString;
		if (m_MonoProperty)
			monoString = (MonoString*)mono_property_get_value(m_MonoProperty, entityInstance.GetInstance(), nullptr, nullptr);
		else
			mono_field_get_value(entityInstance.GetInstance(), m_MonoClassField, &monoString);

		outValue = mono_string_to_utf8(monoString);
	}

	// Debug
	void ScriptEngine::OnImGuiRender()
	{
		ImGui::Begin("Script Engine Debug");

		float gcHeapSize = (float)mono_gc_get_heap_size();
		float gcUsageSize = (float)mono_gc_get_used_size();
		ImGui::Text("GC Heap Info(Used/Available): %.2fKB / %.2fKB", gcUsageSize / 1024.0f, gcHeapSize / 1024.0f);

		for (auto& [sceneID, entityMap] : s_EntityInstanceMap)
		{
			bool opened = ImGui::TreeNode((void*)(uint64_t)sceneID, "Scene (%llx)", sceneID);
			if (opened)
			{
				Ref<Scene> scene = Scene::GetScene(sceneID);
				for (auto& [entityID, entityInstanceData] : entityMap)
				{
					Entity entity = scene->GetEntityMap().at(entityID);
					std::string entityName = "Unnamed Entity";
					if (entity.HasComponent<TagComponent>())
						entityName = entity.GetComponent<TagComponent>().Tag;
					opened = ImGui::TreeNode((void*)(uint64_t)entityID, "%s (%llx)", entityName.c_str(), entityID);
					if (opened)
					{
						for (auto& [moduleName, fieldMap] : entityInstanceData.ModuleFieldMap)
						{
							opened = ImGui::TreeNode(moduleName.c_str());
							if (opened)
							{
								for (auto& [fieldName, field] : fieldMap)
								{

									opened = ImGui::TreeNodeEx((void*)&field, ImGuiTreeNodeFlags_Leaf, fieldName.c_str());
									if (opened)
									{

										ImGui::TreePop();
									}
								}
								ImGui::TreePop();
							}
						}
						ImGui::TreePop();
					}
				}
				ImGui::TreePop();
			}
		}
		ImGui::End();
	}

	std::unordered_map<std::string, std::string> ScriptEngine::s_PublicFieldStringValue;

}
