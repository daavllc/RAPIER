/////////////////////////////////////////////////////////////////
//  Author: Devon Adams (https://github.com/devonadams)
//  License : GPLv3
//  Language: C++
//  This file serves as the hub for DAGGer definitions
/////////////////////////////
/*
	SCOPE/REF....DEFINES
	ASSERT.......DEFINES
	PROFILING....DEFINES
	LOGGING......DEFINES

		See Also:
			KeyCodes.h...........DAGGer Keycode Defines
			MouseCodes.h.........DAGGer Mouse Button Code Defines

*/
#pragma once

#define Dr		DAGGer	//	Shortcut for the DAGGer namespace

//  ---------------------------------------------------------------------------------------------------------------------  //
//  ----------------------------------------------    SCOPE/REF DEFINES    ----------------------------------------------  //
//  ---------------------------------------------------------------------------------------------------------------------  //

namespace DAGGer
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>	//	TODO: inclusive reference system
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}   //  END namespace DAGGer


//  ---------------------------------------------------------------------------------------------------------------------  //
//  ------------------------------------------------    ASSERT DEFINES    -----------------------------------------------  //
//  ---------------------------------------------------------------------------------------------------------------------  //
// TODO: ASSERT w/ no arguments except condition
#ifdef Dr_ENABLE_ASSERTS
#define Dr_ASSERT(x, ...) { if(!(x)) { Dr_ERROR("Assertion Failed: {0}", __VA_ARGS__); Dr_DEBUGBREAK(); } }
#define Dr_CORE_ASSERT(x, ...) { if(!(x)) { Dr_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); Dr_DEBUGBREAK(); } }
#else
#define Dr_ASSERT(x, ...)
#define Dr_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define Dr_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

//  ---------------------------------------------------------------------------------------------------------------------  //
//  ----------------------------------------------    PROFILING DEFINES    ----------------------------------------------  //
//  ---------------------------------------------------------------------------------------------------------------------  //
#ifdef Dr_DEBUG
	#define Dr_PROFILE 1
	#define Dr_PROFILE_RENDERER 1
#endif
#if Dr_PROFILE
	// Resolve which function signature macro will be used. Note that this only
	// is resolved when the (pre)compiler starts, so the syntax highlighting
	// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define Dr_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define Dr_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define Dr_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define Dr_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define Dr_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define Dr_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define Dr_FUNC_SIG __func__
	#else
		#define Dr_FUNC_SIG "Dr_FUNC_SIG unknown!"
	#endif

	#define Dr_PROFILE_BEGIN_SESSION(name, filepath) ::DAGGer::Instrumentor::Get().BeginSession(name, filepath)
	#define Dr_PROFILE_END_SESSION() ::DAGGer::Instrumentor::Get().EndSession()
	#define Dr_PROFILE_SCOPE(name) constexpr auto fixedName = ::DAGGer::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
												::DAGGer::InstrumentationTimer timer##__LINE__(fixedName.Data)
	#define Dr_PROFILE_FUNCTION() Dr_PROFILE_SCOPE(Dr_FUNC_SIG)
	#ifdef Dr_PROFILE_RENDERER	//  ----------------------------------  RENDERER PROFILING -----------------------------------  //
		#define Dr_PROFILE_RENDERER_SCOPE(name) constexpr auto fixedName = ::DAGGer::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
													::DAGGer::InstrumentationTimer timer##__LINE__(fixedName.Data)
		#define Dr_PROFILE_RENDERER_FUNCTION() Dr_PROFILE_RENDERER_SCOPE(Dr_FUNC_SIG)
	#endif
#else
	#define Dr_PROFILE_BEGIN_SESSION(name, filepath)
	#define Dr_PROFILE_END_SESSION()
	#define Dr_PROFILE_SCOPE(name)
	#define Dr_PROFILE_FUNCTION()
	#define Dr_PROFILE_RENDERER_SCOPE(name)
	#define Dr_PROFILE_RENDERER_FUNCTION()
#endif	//  END PROFILING DEFINES

//  ---------------------------------------------------------------------------------------------------------------------  //
//  -----------------------------------------------    LOGGING DEFINES    -----------------------------------------------  //
//  ---------------------------------------------------------------------------------------------------------------------  //
#ifdef Dr_DEBUG	//	DEBUG
	// Core Log Defines
	#define Dr_CORE_TRACE(...)	::DAGGer::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define Dr_CORE_INFO(...)	::DAGGer::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define Dr_CORE_WARN(...)	::DAGGer::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define Dr_CORE_ERROR(...)	::DAGGer::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define Dr_CORE_CRITICAL(...)	::DAGGer::Log::GetCoreLogger()->critical(__VA_ARGS__)

	//	Client Log Defines
	#define Dr_TRACE(...)	::DAGGer::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define Dr_INFO(...)	::DAGGer::Log::GetClientLogger()->info(__VA_ARGS__)
	#define Dr_WARN(...)	::DAGGer::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define Dr_ERROR(...)	::DAGGer::Log::GetClientLogger()->error(__VA_ARGS__)
	#define Dr_CRITICAL(...)	::DAGGer::Log::GetClientLogger()->critical(__VA_ARGS__)
#endif

#ifdef Dr_RELEASE	//	RFELEASE
		//	Don't Log Engine Messages
	#define Dr_CORE_TRACE
	#define Dr_CORE_INFO
	#define Dr_CORE_WARN
	#define Dr_CORE_ERROR
	#define Dr_CORE_CRITICAL
	//	Client Log Defines
	#define Dr_TRACE(...)	::DAGGer::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define Dr_INFO(...)	::DAGGer::Log::GetClientLogger()->info(__VA_ARGS__)
	#define Dr_WARN(...)	::DAGGer::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define Dr_ERROR(...)	::DAGGer::Log::GetClientLogger()->error(__VA_ARGS__)
	#define Dr_CRITICAL(...)	::DAGGer::Log::GetClientLogger()->critical(__VA_ARGS__)
#endif

#ifdef Dr_DISTRIBUTION	//	DISTRIBUTION
		//	Don't Log Engine Messages
	#define Dr_CORE_TRACE
	#define Dr_CORE_INFO
	#define Dr_CORE_WARN
	#define Dr_CORE_ERROR
	#define Dr_CORE_CRITICAL
		//	Don't Log Client Messages
	#define Dr_TRACE
	#define Dr_INFO
	#define Dr_WARN
	#define Dr_ERROR
	#define Dr_CRITICAL
#endif	//	END LOGGING DEFINES


//  ---------------------------------------------------------------------------------------------------------------------  //
//  ------------------------------------------------    MACRO DEFINES    ------------------------------------------------  //
//  ---------------------------------------------------------------------------------------------------------------------  //

// glm macros
#define DrVec2			glm::vec2	//	glm::vec2
#define DrVec3			glm::vec3	//	glm::vec3
#define DrVec4			glm::vec4	//	glm::vec4
#define DrMat3			glm::mat3	//	glm::mat4
#define DrMat4			glm::mat4	//	glm::mat4

// alternate definitions
#define DrInt				int		//	int
#define DrIntArray			int*	//	int*
#define DrFloat				float	//	float
#define DrFloat2			DrVec2	//	glm::vec2
#define DrFloat3			DrVec3	//	glm::vec3
#define DrFloat4			DrVec4	//	glm::vec4


//	DAGGer Shortcuts / Key Items
#define DrPos1(x)						{ x, x, x }					//	3 coordiate fill {x, x, x}
#define DrPos2(x, y)					{ x, y }					//	2 coordinate position { x, y }
#define DrPos3(x, y, z)					{ x, y, z }					//	3 coordinate position { x, y, z }

#define DrSize1(x)						{ x, x }					//	create a square { x, x }
#define DrSize2(width, height)			{ width, height }			//	2 coordinate size { width, height }
#define DrSize3(width, height, depth)	{ width, height, depth }	//	3 coordiate size { width, height, depth}

#define DrRotation2(rotation)			glm::radians(rotation)		//	converts float to radians (rotation)
#define DrRotate2(rotation)				DrRotation2(rotation)		//	converts float to radians (rotation)
#define DrRotation3(x, y, z)			glm::vec3(x, y, z)			//	XYZ rotation (x, y, z)
#define DrRotate3(x, y, z)				DrRotation3(x, y, z)		//	XYZ rotation (x, y, z)

#define DrColor(r, g, b, a)				glm::vec4( r, g, b, a )		//	RGBA color ( r, g, b, a )
#define DrColor3(r, g, b)				DrColor( r, g, b, 1.0f )	//	RGB color  ( r, g, b, 1.0f)

#define DrTile(Muiltiplier)				( Muiltiplier )				//	Float for tiling textures