## gtasa-reversed ![Build](https://github.com/saml1er/gta-reversed/workflows/Build/badge.svg?event=push&branch=master)
A project to reverse Grand Theft Auto San Andreas completely, and to rewrite and document every function. 

### Discord
[Join our discord server](https://discord.gg/P5zVn6C). You can request us to decompile a function for you. If you wish to contribute, then we'll be happy to assist you.

#### Build Instructions

##### Premake5
1) Execute `premake5.bat` (Visual Studio 2019 is required)

2) gta_reversed.sln shortcut will be created.

##### CMake
1) Download and install latest CMake for windows from [HERE](https://cmake.org/download/).

2) Open CMake GUI ![Capture](https://gitlab.com/gtahackers/gta-reversed/uploads/9409c1da6c25fbe4423f750d45f29000/Capture.PNG) 

3) Set the Source and Build directories (Don't forget to append "Bin" after the path for build), like this: 

![Capture](https://gitlab.com/gtahackers/gta-reversed/uploads/a4c08a7094c1d8fe6727e24aad6c0203/Capture.PNG)

4) Click configure, you'll see a dialogue box. Choose "Visual Studio 16 2019" and "Win32," then click Finish.

![CMakeSettings](https://user-images.githubusercontent.com/10183157/63577623-37a13480-c5a8-11e9-8fe4-da81fa47ca58.PNG)


5) Once configuration is complete, click the Generate button.  
6) You'll find GTASA.sln in Bin folder.


#### What exactly is this project? 
Building this project will result in a DLL file, that DLL file can be injected into GTA:SA using any ASI loader out there. After the DLL file has been injected, it will hook these reversed functions, if your game crashes, then it means there's some problem with the code and it has to be fixed, otherwise if the game runs smoothly, our code works, and we can focus on reversing more functions and classes, that's pretty much it. 

#### Motivation
I'm an active contributor for [Multi Theft Auto San Andreas](https://www.mtasa.com), which is a project that adds multiplayer functionality to GTA:SA. GTA:SA was reversed by MTA team and many other hackers on GTA related forum, they documented the addresses of GTA functions, but almost no one seems to rewrite the code in readable and compilable C++, that is the main reason why this project was created. Currently, MTA:SA has barely any active contributors because to add new features, you must know how to reverse GTA:SA, so to make it easier for new contributors, rewriting and documenting these functions in C++ will allow them to understand how GTA:SA works internally without the need of understanding ASM or any low level stuff.

#### Advice
The goal is to rewrite every GTA:SA function exactly as you see in the executable, so anyone who is trying to reverse GTA:SA should find this project helpful. 

- It's okay to do minor improvements if deemed necessary.
- Use naming convention of [plugin-sdk](https://github.com/DK22Pac/plugin-sdk) project.

#### Credits
TODO
