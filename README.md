## gtasa-reversed [![Build Status](https://github.com/codenulls/gta-reversed/workflows/Build/badge.svg?event=push&branch=master)](https://github.com/codenulls/gta-reversed/actions?query=workflow%3ABuild)

A project to reverse Grand Theft Auto San Andreas completely, and to rewrite and document every function. 

### Discord
[Join our discord server](https://discord.gg/P5zVn6C). You can request us to decompile a function for you. If you wish to contribute, then we'll be happy to assist you.

### What exactly is this project? 
Building this project will result in a DLL file, that DLL file can be injected into GTA:SA using any ASI loader out there. After the DLL file has been injected, the ingame functions will be replaced by the reversed code. The game will behave exactly the same. Now if we make any changes to the reversed code, it will take effect in the game. The goal is to keep reversing until we have the entire game reversed to compile a standalone executable.

### Progress
The progress of reversed classes can be tracked [here](docs/ReversedClasses.MD).

### Coding Guidelines 
Before you start writing code, please make sure to read the [coding guidelines](docs/CodingGuidelines.MD) for this project.

### Build Instructions
You can either build with Premake5 or CMake, that's up to you.
##### Premake5
1) Clone the project, including the submodules `git clone --recurse-submodules https://github.com/codenulls/gta-reversed.git`.

2) Execute `premake5.bat` (Visual Studio 2019 is required)

3) You'll find gta_reversed.sln shortcut in the same folder as premake5.bat.

##### CMake (GUI)
1) Download and install latest CMake for windows from [HERE](https://cmake.org/download/).

2) Open CMake GUI ![Capture](https://gitlab.com/gtahackers/gta-reversed/uploads/9409c1da6c25fbe4423f750d45f29000/Capture.PNG) 

3) Clone the project, including the submodules `git clone --recurse-submodules https://github.com/codenulls/gta-reversed.git`.

4) Set the Source and Build directories (Don't forget to append "Bin" after the path for build), like this: 

![Capture](https://gitlab.com/gtahackers/gta-reversed/uploads/a4c08a7094c1d8fe6727e24aad6c0203/Capture.PNG)

5) Click configure, you'll see a dialogue box. Choose "Visual Studio 16 2019" and "Win32," then click Finish.

![CMakeSettings](https://user-images.githubusercontent.com/10183157/63577623-37a13480-c5a8-11e9-8fe4-da81fa47ca58.PNG)


6) Once configuration is complete, click the Generate button.  
7) You'll find GTASA.sln in Bin folder.

##### CMake (CLI)
1) Download and install latest CMake for windows from [HERE](https://cmake.org/download/) and make sure to add it to your PATH.

2) Clone the project, including the submodules `git clone --recurse-submodules https://github.com/codenulls/gta-reversed.git`.

3) Open Command Prompt in the `gta-reversed` directory and run `cmake -Bbuild -H. -A Win32`.

4) To open the Visual Studio project, simply run `cmake --open build` or open `build/GTASA.sln` manually.

### Credits
- All contributors of [plugin-sdk](https://github.com/DK22Pac/plugin-sdk) project.
- Hundreds of great people on [gtaforums.com](https://gtaforums.com/topic/194199-documenting-gta-sa-memory-addresses).
- [re3 team](https://github.com/GTAmodding/re3).
- And everyone who contributed to GTA:SA reversing.
