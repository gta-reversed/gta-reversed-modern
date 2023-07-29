## gtasa-reversed [![Build Status](https://github.com/gta-reversed/gta-reversed-modern/workflows/Build/badge.svg?event=push&branch=master)](https://github.com/gta-reversed/gta-reversed-modern/actions?query=workflow%3ABuild)

A project to reverse Grand Theft Auto San Andreas completely, and to rewrite and document every function. 

### What exactly is this project? 
Building this project will result in a DLL file that can be injected into GTA:SA using any ASI loader out there. After the DLL file has been injected, the ingame functions will be replaced by the reversed ones. The game will behave the same. Now if we make any changes to the reversed code, it will take effect in the game. The goal is to keep reversing until we have the entire game reversed to compile a standalone executable.

### Progress
The progress of reversed classes can be tracked [here](docs/ReversedClasses.MD). (needs to be updated)
We currently estimate that about 50-60% of the code is done.
Since this project is done as a hobby, and worked on at irregular intervals, there's no real time estimate.

### Coding Guidelines 
Before you start writing code, please make sure to read the [coding guidelines](docs/CodingGuidelines.MD) for this project.

### Requirements
* [Visual Studio 2022](https://visualstudio.microsoft.com/en/downloads/) (Community Edition is enough)
* [CMake](https://cmake.org) (for those who want to use CMake instead of premake5)

### Build Instructions

You can either build with **Premake5** or **CMake**; that's up to you, but a C++20 capable compiler [with `<ranges>`, `<format>` support] is required.

First clone the project, including the submodules:
```shell
git clone --recurse-submodules https://github.com/gta-reversed/gta-reversed-modern.git
```

<details>
<summary>Premake5</summary>

1) Execute `premake5.bat`

2) You'll find gta_reversed.sln shortcut in the same folder as premake5.

3) Open it, and once the project has loaded, just hit `CTRL + SHIFT + B`
</details>

<details>
<summary>CMake</summary>

0) Sadly CMake requires VS22, because since CMake v3.20.4 `cxx_20` maps to `std=c++20` instead of `std=c++latest`. If you really want to avoid VS22, you can either downgrade your CMake, or change `c++20` to `c++latest` manually in the project settings... Or just use premake5 instead.

1) Download and install the latest version of CMake for windows from [HERE](https://cmake.org/download/) and make sure to add it to your PATH.

##### GUI

2) Open CMake GUI

3) Set the Source and Build directories (Don't forget to append "Bin" after the path for build), like this: 

![Capture](https://gitlab.com/gtahackers/gta-reversed/uploads/a4c08a7094c1d8fe6727e24aad6c0203/Capture.PNG)

4) Click configure, then you will see a dialogue box. Choose the IDE you have (In the image below it's VS2019) and "Win32", then click Finish.

![CMakeSettings](https://user-images.githubusercontent.com/10183157/63577623-37a13480-c5a8-11e9-8fe4-da81fa47ca58.PNG)

5) Once the configuration is complete, click the Generate button.

6) You'll find GTASA.sln in the Bin folder.

##### CLI

2) Open Command Prompt in the `gta-reversed` directory and run `cmake -Bbuild -H. -A Win32`.

3) To open the Visual Studio project, simply run `cmake --open build` or open `build/GTASA.sln` manually.

4) Once the configuration is complete, click the Generate button.

5) You'll find GTASA.sln in Bin folder.

</details>

### Game
To install all the necessary files, run `install.py` with **__administrator privileges__** [Necessary to create symlinks on Windows] in the root directory.
Alternatively, you can install them by yourself:

* GTA SA **Compact** exe
* [ASI Loader](https://gtaforums.com/topic/523982-relopensrc-silents-asi-loader/)
* [III.VC.SA.WindowedMode.asi](https://github.com/ThirteenAG/III.VC.SA.WindowedMode)
* Mouse Fix (**dinput8.dll**) [Can be found in the zip in `./contrib`]

You can download them in a single [archive](https://github.com/gta-reversed/gta-reversed-modern/blob/master/contrib/plugins.zip).
Using other plugins is strongly discouraged and we provide __**no support**__.

### Preparing Environment (Optional)
[If you have ran `install.py` in the previous step then this step is already done]

<details>
<summary>Instructions</summary>

You can create symbolic links [symlinks] for artifacts [the `.asi`] to need not copy them every time you compile the project.

Open a console with **__administrator privileges__** in the git repo's directory and run `contrib\link_asi.bat` or right click `link_asi.bat` file and click `Run as administrator`, then
follow instructions at the command window.

</details>
    
### What to work on?
Check [this](https://github.com/gta-reversed/gta-reversed-modern/discussions/402) out for some inspiration ;)
    
### Credits
- All contributors of the [plugin-sdk](https://github.com/DK22Pac/plugin-sdk) project.
- All contributors of the [original project](https://github.com/codenulls/gta-reversed).
- Hundreds of great people on [gtaforums.com](https://gtaforums.com/topic/194199-documenting-gta-sa-memory-addresses).
- [re3 team](https://github.com/GTAmodding/re3).
- And everyone who contributed to GTA:SA reversing.
