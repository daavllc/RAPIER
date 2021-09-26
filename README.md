# DAGGer v0.2.2a
#### DA Gordian Graphics Engine Reimagined
This is supposed to serve as an easy to use C++17 graphics/game engine. I'm not writting the engine with the intent for other people use use, however feel free to use, modify, and create whatever you want with it!

## Features (WiP):
  * Free and Open Source
  * Cross-platform
  * Multi-Render API (only OpenGL for now)
  * Easy-to-use API
  * Supporting a single freelance developer 

~Written 2021/02/16

## Getting Started
Visual Studio 2017 or 2019 is recommended, DAGGer is officially untested on other development environments while I focus on a Windows build.

<ins>**1. Downloading the repository:**</ins>
Start by cloning the repository with `git clone --recursive https://github.com/Anonoei/DAGGer`.

If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.

<ins>**2. Configuring the dependencies:**</ins>

1. Run the [Setup.bat](https://github.com/Anonoei/DAGGer/blob/master/scripts/Win-Setup.bat) file found in `scripts` folder. This will download the required prerequisites for the project if they are not present yet.
2. One prerequisite is the Vulkan SDK. If it is not installed, the script will execute the `VulkanSDK.exe` file, and will prompt the user to install the SDK.
3. After installation, run the [Setup.bat](https://github.com/Anonoei/DAGGer/blob/master/scripts/Win-Setup.bat) file again. If the Vulkan SDK is installed properly, it will then download the Vulkan SDK Debug libraries. (This may take a longer amount of time)
4. After donwloading and unzipping the files, the [Win-GenProjects.bat](https://github.com/Anonoei/DAGGer/blob/master/scripts/files/Win-GenProjects.bat) script file will get executed automatically, which will then generate a Visual Studio solution file for user's usage.

If changes are made, or if you want to regenerate project files, rerun the [Win-GenProjects.bat](https://github.com/Anonoei/DAGGer/blob/master/scripts/files/Win-GenProjects.bat) script file found in `scripts` folder.

***

## Structure:
Project Name | Purpose
------------ | --------
FORGE | DAGGer graphical scene editor
SandboxApp | DAGGer application template
DAGGer | The actual engine itself


## Libraries:
#### DAALS (DA Asset Library Systemics)
DAALS are various abstrtacted libraries for specific tasks, from a music and sound engine to weather to health management
DAALS Name | Purpose | Sub-items
---------- | ------- | -----------
DAAGS | Generation of maps/weather | LARG, LASG, LAWS
DACMS | Color Management Systems | CAPE, CARP
DAINS | A.I./machine learning | NIANN, NIME, NISST, NNICS
DAUMS | Health Management | HARE, HATE
DAUSS | Music and Sound | MASAE, MASTA

## License: GPLv3
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
