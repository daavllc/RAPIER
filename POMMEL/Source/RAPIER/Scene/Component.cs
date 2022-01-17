using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace RAPIER
{
	public abstract class Component
	{
		public Entity Entity { get; set; }
	}

	public class TagComponent : Component
	{
		public string Tag
		{
			get
			{
				return GetTag_Native(Entity.ID);
			}
			set
			{
				SetTag_Native(Entity.ID, value);
			}
		}
		[MethodImpl(MethodImplOptions.InternalCall)]
		public static extern string GetTag_Native(ulong entityID);

		[MethodImpl(MethodImplOptions.InternalCall)]
		public static extern void SetTag_Native(ulong entityID, string tag);

	}

	public class TransformComponent : Component
	{
		public Transform Transform
		{
			get
			{
				GetTransform_Native(Entity.ID, out Transform result);
			}
			set
			{
				SetTransform_Native(Entity.ID, ref value);
			}
		}
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal static extern void GetTransform_Native(ulong entityID, out Transform outTransform);
		[MethodImpl(MethodImplOptions.InternalCall)]
		internal static extern void SetTransform_Native(ulong entityID, ref Transform inTransform);

	}

	public class CameraComponent : Component
	{
		// TODO
	}

	public class ScriptComponent : Component
	{
		// TODO
	}

	public class SpriteRendererComponent : Component
	{
		// TODO
	}

	public class BoxCollider2DComponent : Component
	{
		// TODO
	}

	public class CircleCollider2DComponent : Component
	{
		//	TODO
	}

}   // END namespace RAPIER
