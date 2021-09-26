/////////////////////////////////////////////////////////////////
//	Author: Anonoei (https://github.com/anonoei)
//  License : GPLv3
//  Language: C++
//  This file serves as the hub for DAGGer definitions
/////////////////////////////
/*
	PROFILING....DEFINES
	LOGGING......DEFINES

		See Also:
			KeyCodes.h...........DAGGer Keycode Defines
			MouseCodes.h.........DAGGer Mouse Button Code Defines

*/
#pragma once

#define Dr		DAGGer	//	Shortcut for the DAGGer namespace

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
