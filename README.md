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

### Requirements

* [Visual Studio 2019](https://visualstudio.microsoft.com/en/downloads/) (Enough Community Edition)
* [CMake](https://cmake.org) (Optional, we have premake5)

#### Game

* GTA SA **Compact** exe
* [ASI Loader](https://gtaforums.com/topic/523982-relopensrc-silents-asi-loader/)
* [III.VC.SA.WindowedMode.asi](https://github.com/ThirteenAG/III.VC.SA.WindowedMode)
* [Improved Fast Loader](https://www.gtagarage.com/mods/show.php?id=25665) (Optional)
* Mouse Fix (**dinput8.dll**)

You can download this in a single [archive](https://github.com/codenulls/gta-reversed/files/6949371/gta_sa.zip).
Using other plugins is strongly discouraged. 

### Build Instructions

You can either build with **Premake5** or **CMake**, that's up to you.

First of all clone the project, including the submodules:
```shell
git clone --recurse-submodules https://github.com/codenulls/gta-reversed.git
```

<details>
<summary>Premake5</summary>

1) Execute `premake5.bat` (Visual Studio 2019 is required)

2) You'll find gta_reversed.sln shortcut in the same folder as premake5.bat.

</details>

<details>
<summary>CMake</summary>

1) Download and install latest CMake for windows from [HERE](https://cmake.org/download/) and make sure to add it to your PATH.

##### GUI

2) Open CMake GUI

3) Set the Source and Build directories (Don't forget to append "Bin" after the path for build), like this: 

![Capture](https://gitlab.com/gtahackers/gta-reversed/uploads/a4c08a7094c1d8fe6727e24aad6c0203/Capture.PNG)

4) Click configure, you'll see a dialogue box. Choose "Visual Studio 16 2019" and "Win32," then click Finish.

![CMakeSettings](https://user-images.githubusercontent.com/10183157/63577623-37a13480-c5a8-11e9-8fe4-da81fa47ca58.PNG)

5) Once configuration is complete, click the Generate button.

6) You'll find GTASA.sln in Bin folder.

##### CLI

2) Open Command Prompt in the `gta-reversed` directory and run `cmake -Bbuild -H. -A Win32`.

3) To open the Visual Studio project, simply run `cmake --open build` or open `build/GTASA.sln` manually.

4) Once configuration is complete, click the Generate button.

5) You'll find GTASA.sln in Bin folder.

</details>


### Preparing Environment (Optional)

For better experience you can create symlinks for artifacts and you no longer need to copy files every time.

Run console (administrator privileges may be needed) and type these commands (**don't forget change paths**).

```shell
cd "c:\Games\GTA San Andreas\scripts"
mklink gta_reversed.asi c:\Games\gta-reversed\Bin\Debug\gta_reversed.asi
mklink gta_reversed.ilk c:\Games\gta-reversed\Bin\Debug\gta_reversed.ilk
mklink gta_reversed.pdb c:\Games\gta-reversed\Bin\Debug\gta_reversed.pdb
```
    
### Credits
- All contributors of [plugin-sdk](https://github.com/DK22Pac/plugin-sdk) project.
- Hundreds of great people on [gtaforums.com](https://gtaforums.com/topic/194199-documenting-gta-sa-memory-addresses).
- [re3 team](https://github.com/GTAmodding/re3).
- And everyone who contributed to GTA:SA reversing.
