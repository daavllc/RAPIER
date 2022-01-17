using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace RAPIER
{
	public class Entity
	{
		public ulong ID { get; private set; }

		internal Entity(ulong id)
		{
			ID = id;
		}

		~Entity()
		{}

		public T CreateComponent<T>() where T : Component, new()
		{
			CreateComponent_Native(ID, typeof(T));
			T component = new T();
			component.Entity = this;
			return component;
		}

		public bool HasComponent<T>() where T : Component, new()
		{
			return HasComponent_Native(ID, typeof(T));
		}

		public bool HasComponent(Type type)
		{
			return HasComponent_Native(ID, type);
		}

		public T GetComponent<T>() where T : Component, new()
		{
			if (HasComponent<T>())
			{
				T component = new T();
				component.Entity = this;
				return component;
			}
			return null;
		}

		public Entity FindEntityByTag(string tag)
		{
			ulong entityID = FindEntityByTag_Native(tag);
			if (entityID == 0)
				return null;

			return new Entity(entityID);
		}

		public Entity FindEntityByID(ulong entityID)
		{
			return new Entity(entityID); // TODO: Verify
		}

		public Entity Create()
		{
			return new Entity(CreateEntity_Native(ID));
		}

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern void CreateComponent_Native(ulong entityID, Type type);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern bool HasComponent_Native(ulong entityID, Type type);
		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern ulong FindEntityByTag_Native(string tag);

		[MethodImpl(MethodImplOptions.InternalCall)]
		private static extern ulong CreateEntity_Native(ulong entityID);


	}
}	//	END namespace RAPIER
