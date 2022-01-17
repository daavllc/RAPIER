# RAPIER
#### Renderer Agnostic Paramount Imagination Engine Reborn

![RAPIER](/Branding/RAPIER_SplashScreen.jpg?raw=true "RAPIER")

## Purpose
Provide the backbone for graphical projects to be built upon. Creating a render API agnostic graphics engine enables the best possbile performance on any platform by using the API built for that platform. Creating a multi-platform engine also enables projects to be more easily ported to different platforms with less hassle. 

## Details
 - Project lead: [Anonoei](https://github.com/Anonoei)
 - Language: C++17
 - License: MIT
 - Dependancies:
   - [premake](https://github.com/premake/premake-core) - Build configuration
   - [box2d](https://github.com/erincatto/box2d) - 2D Physics
   - [entt](https://github.com/skypjack/entt) - Entity management
   - [glfw](https://github.com/glfw/glfw) - Window manager
   - [glm](https://github.com/Groovounet/glm) - Mathematics
   - [imgui](https://github.com/ocornut/imgui) -  GUI
   - [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo) - GUI gizmos
   - [spdlog](https://github.com/gabime/spdlog) - Logging
   - [stb (image)](https://github.com/nothings/stb) - Image loading
   - [yaml-cpp](https://github.com/jbeder/yaml-cpp) - Serialization
   - [VulkanSDK](https://www.lunarg.com/vulkan-sdk/) - Shader compilation
   - [glad](https://glad.dav1d.de/) - OpenGL bindings
   - [mono](https://github.com/mono/mono) - C# bindings

----

## Current status/roadmap
 - [ ] Initial Release
 - [ ] Documentation
 - [X] FORGE
   - [ ] Initial Release
   - [X] Physics Collider Visualizers
   - [X] Play/Pause
   - [X] Initial implementation
 - [X] RAPIER
   - [ ] POMMEL
     - [ ] Initial implementation
   - [ ] 3D
     - [ ] Physics
   - [X] 2D
     - [X] Physics
     - [X] Initial implementation
   - [ ] Features
     - [ ] HDR
 - [ ] Platforms
   - [ ] Desktop
     - [X] Windows
     - [ ] Linux
     - [ ] MacOS
   - [ ] Mobile
     - [ ] iOS
     - [ ] Android
   - [ ] Console
     - [ ] Sony
     - [ ] Microsoft
     - [ ] Nintendo
 - [ ] Render APIs
   - [ ] Metal
   - [ ] DirectX
   - [ ] Vulkan
   - [X] OpenGL

## Installation
There are currently no releases, so you must download and compile from source. Check the `Contributing` section for instructions.
## Contributing
Visual Studio 2017 or 2019 is recommended, RAPIER is officially untested on other development environments while we focus on a Windows build and feature development.

1. **Download the repository**
   - Run `git clone --recursive https://github.com/daavofficial/RAPIER`.
   - Near the rop right, click Code > Download ZIP
     - Extract the zip file

2. **Creating the solution**

   1. Run [Win-Setup.bat](https://github.com/daavofficial/RAPIER/blob/master/scripts/Win-Setup.bat) found in the [scripts](https://github.com/daavofficial/RAPIER/blob/master/scripts) folder. This will download any missing dependencies for RAPIER.
      - If the VulkanSDK is not installed, you will be prompted to download and install it. Once downloaded, follow the steps it provides to install it. After it is installed, please re-run [Win-Setup.bat](https://github.com/daavofficial/RAPIER/blob/master/scripts/Win-Setup.bat) to verify it's installation
      - If premake is not found in the [vendor/premake/bin](https://github.com/daavofficial/RAPIER/blob/master/vendor/premake/bin) folder, you will be prompted to download premake.
   2. After all dependencies are installed, [Win-GenProjects.bat](https://github.com/daavofficial/RAPIER/blob/master/scripts/files/Win-GenProjects.bat) will be executed automatically, and will generate a Visual Studio solution file for you to use.

If you make changes to any `premake5.lua` files, or if you want to regenerate the project files, re-run [Win-Setup.bat](https://github.com/daavofficial/RAPIER/blob/master/scripts/Win-Setup.bat).

----
## License: MIT
Copyright © 2022 DAAV, LLC

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
