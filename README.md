# DAGGer
 Devon Adams Gordian Graphics Engine Reimagined
 
 This is another long development project that is way outside of my bounds as of writing.
 I'd like to create a Graphics Engine to make my workflow easier in the future.
 I'm more comfortable with programming than using something like Unity,
 So why not!
 Welcome to the journey!
 
----
Features:
	Free and Open Source
	Cross-platform window system (GFLW)
	Vulkan API (Better Preformance)
	Libraries to draw items to screen easier
		(Vulkan's worst feature)
	Supporting a single freelance developer 
 ----
 There are two branches of DAGGer
 DA Console Engine		//		DA Graphics Engine
		DACE			//			DAGE

	These two will be separated, at the very least for now.
	This allows for the code to remain smaller, 
	and for not being forced to include redundant code.
~Written 2021/01/18
	
----
DAGGer Structure:
	-- main.cpp (Your Application)
		Contains App information and settings, etc
		Stores App specific code for where things are drawn
		-- DAGGer (DAGraphical.h / DAConsole.h)
			Contains code for GLFW, GLM and Vulkan
			Creates Vulkan devices etc
			
			

==========================================================================
                             License:
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
