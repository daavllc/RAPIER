//------------------------------------------------------------------------------------------------------
//----==============================================================================================~~~~
//----=                                                                                            =----
//----=                      MMMM       MMM       MMM      M         MMM                           =----
//----=                      M   M     M   M     M   M     M        M                              =----
//----=                      M   M     MMMMM     MMMMM     M         MM                            =----
//----=                      M   M     M   M     M   M     M           M                           =----
//----=                      M MM      M   M     M   M     MMMMM    MMM                            =----
//----=                                                                                            =----
//----==============================================================================================~~~~
//----=----------------------------------  version 0.0.1a  ----------------------------------------=----
//----==============================================================================================----
//	Author: Devon Adams (https://github.com/devonadams)
//	License : GPLv3
//	Language: C++17
//	Dependencies: A Sandbox Application
//	DAALS - Devon Adams Asset Library Systemics
//	  DAALS are various abstracted DAGGer libraries that serve specific tasks
//	  They are intended to be systemic (IE work together and know of eachother) but don't have to
///////////////////////////////////////////////////
#pragma once

#include "DAAGS/DAAGS.h"
#include "DACMS/DACMS.h"
#include "DAINS/DAINS.h"
#include "DAUMS/DAUMS.h"
#include "DAUSS/DAUSS.h"

namespace DAALS
{
	class DAALS
	{
	public:
		DAALS* Get() { return this->s_Instance; }

		void SetDAUMS(bool enable) { this->bDAUMS = enable; }
		void SetDAAGS(bool enable) { this->bDAAGS = enable; }
		void SetDAINS(bool enable) { this->bDAINS = enable; }
		void SetDACMS(bool enable) { this->bDACMS = enable; }
		void SetDAUSS(bool enable) { this->bDAUSS = enable; }
	private:
		bool bDAUMS = true;	//	Health Management
		bool bDAAGS = true;	//	Asset Generation
		bool bDAINS = true;	//	Machine Learning / A.I.
		bool bDACMS = true;	//	Color Management
		bool bDAUSS = true;	//	Music and Sound
	private:
		DAALS* s_Instance;
	};
}	//	END namespace DAALS
