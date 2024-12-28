# N Body Simulation C++

A somewhat well documented 3D n-body simulator in C++. There are build and run scripts for nearly all platforms if you have clang and a C++ standard library implementation that support c++20.

## Windows Clang and MSVC STL Installation

### Clang

- Install [LLVM](https://releases.llvm.org/)
- Add `C:\Program Files\LLVM\bin` to [PATH](https://stackoverflow.com/a/44272417/17921095)

### MSVC STL

- Install [Build Tools for Visual Studio 2022](https://aka.ms/vs/17/release/vs_BuildTools.exe)
- Open the **Visual Studio Installer**. If it doesn’t open automatically, locate and launch the **Visual Studio Installer**.
- In **Build Tools for Visual Studio 2022**, click the **Modify** button.
- In the Workloads tab, check the option labeled **Desktop development with C++**.
- In **Installation Details** and **Optional**, have **MSVC v143** checked. MSVC is the only one we need, so you can uncheck the others.
- Click the **Modify** button at the bottom-right corner to start the installation.

## 500 Bodies

![500 Bodies](./images/500-bodies.gif)

## 250 Bodies

![250 Bodies](./images/250-bodies.gif)

## 100 Bodies

![100 Bodies](./images/100-bodies.gif)

## 50 Bodies

![50 Bodies](./images/50-bodies.gif)

## 10 Bodies

![10 Bodies](./images/10-bodies.gif)
