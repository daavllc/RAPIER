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
	#define RP_ENABLE_PROFILING 1
	#define RP_ENABLE_RENDERER_PROFILING 1
#endif
#include "RAPIER/Debug/Profiler.h"

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
