/*
Contains:
	PROFILING DEFINES
	LOGGING DEFINES

		See Also:
			KeyCodes.h for Keycode Defines
			MouseCodes.h for Mouse Button Code Defines

*/
#pragma once

//  ---------------------------------------------------------------------------------------------------------------------  //
//  ----------------------------------------------    PROFILING DEFINES    ----------------------------------------------  //
//  ---------------------------------------------------------------------------------------------------------------------  //
#ifdef RP_DEBUG
	#define RP_PROFILE 1
	#define RP_PROFILE_RENDERER 1
#endif
#if RP_PROFILE
	// Resolve which function signature macro will be used. Note that this only
	// is resolved when the (pre)compiler starts, so the syntax highlighting
	// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define RP_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define RP_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define RP_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define RP_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define RP_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define RP_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define RP_FUNC_SIG __func__
	#else
		#define RP_FUNC_SIG "RP_FUNC_SIG unknown!"
	#endif

	#define RP_PROFILE_BEGIN_SESSION(name, filepath) ::RAPIER::Instrumentor::Get().BeginSession(name, filepath)
	#define RP_PROFILE_END_SESSION() ::RAPIER::Instrumentor::Get().EndSession()
	#define RP_PROFILE_SCOPE(name) constexpr auto fixedName = ::RAPIER::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
												::RAPIER::InstrumentationTimer timer##__LINE__(fixedName.Data)
	#define RP_PROFILE_FUNCTION() RP_PROFILE_SCOPE(RP_FUNC_SIG)
	#ifdef RP_PROFILE_RENDERER	//  ----------------------------------  RENDERER PROFILING -----------------------------------  //
		#define RP_PROFILE_RENDERER_SCOPE(name) constexpr auto fixedName = ::RAPIER::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
													::RAPIER::InstrumentationTimer timer##__LINE__(fixedName.Data)
		#define RP_PROFILE_RENDERER_FUNCTION() RP_PROFILE_RENDERER_SCOPE(RP_FUNC_SIG)
	#endif
#else
	#define RP_PROFILE_BEGIN_SESSION(name, filepath)
	#define RP_PROFILE_END_SESSION()
	#define RP_PROFILE_SCOPE(name)
	#define RP_PROFILE_FUNCTION()
	#define RP_PROFILE_RENDERER_SCOPE(name)
	#define RP_PROFILE_RENDERER_FUNCTION()
#endif	//  END PROFILING DEFINES

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


//	RAPIER Shortcuts / Key Items
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
