# Minecraft clone in C++
This is a simple graphics and game engine project, that implements something similar to minecraft.

> #### **_Contributions are welcome!!_**

## Installation and Setup 

1. **Vcpkg**: We are using the [Vcpkg](https://github.com/microsoft/vcpkg) package manager to install project dependencies. This project is oriented to be cross-platform, and Vcpkg provides an easy way to install packages on various operating systems.
   You can read more [here](https://vcpkg.io/en/) and [here](https://learn.microsoft.com/en-us/vcpkg/get_started/overview).

2. **Git Submodules**: You don't need to install vcpkg manually, it is included as a git submodule (shallow, depth==1). You can clone the project using the following command:
```bash
git clone --recursive --shallow-submodules https://github.com/taylor-swif/minecraft.git
```
3. **Bootstrapping Vcpkg**: After cloning the project, you can bootstrap vcpkg using the following commands:

#### MacOS/Linux:
```bash
./vcpkg/bootstrap-vcpkg.sh -disableMetrics
```

#### Windows:
```bash
./vcpkg/bootstrap-vcpkg.bat
```

4. **Install Dependencies**: Now you can install the project dependencies using the following command:
   vcpkg install glfw3 glew glad imgui

```bash
./vcpkg/vcpkg install opengl glad glew glfw3 glm imgui
```
***WARNING***

Read information's in your terminal while installing dependencies. Probably you will be missing some dependencies, so you need to install them manually.
There should be a message like this:

MacOS:
```bash
brew install libxinerama-dev libxcursor-dev xorg-dev libglu1-mesa-dev pkg-config
```

Ubuntu:
```bash
sudo apt install libxinerama-dev libxcursor-dev xorg-dev libglu1-mesa-dev pkg-config
```

Then repeat 4th step.

## Building the Project
1. **CMake**: We are using CMake to build the project. It is automated, so you do not have to do anything. 
   For example, if you are using MacOS/Linux, you can use the following command to build the project:
```bash
mkdir build
cd build
cmake ../
make all
./minecraft
```

or

Green magic button in your IDE e.g. CLion.

But for multiplatform development, I recommend using the terminal. WSL should work fine.

## Controls
- <kbd>**Esc**</kbd> - Exit
- <kbd>**W**</kbd><kbd>**A**</kbd><kbd>**S**</kbd><kbd>**D**</kbd> - Move
- <kbd>**Space**</kbd> - Jump
- <kbd>**Left Shift**</kbd> - Sprint
- <kbd>**M**</kbd> - Change to flight mode
- <kbd>**Left mouse button**</kbd> - Destroy block
- <kbd>**Right mouse button**</kbd> - Place block
- <kbd>**/\<blockID> Enter**</kbd> - Select block

## Blocks
<table>
  <tr>
    <td>
      <p align="center"><img src="screenshots/blocks/dirt.png" style="width: 32px; height: 32px;"></p>
      <p align="center">1</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/grass.png" style="width: 32px; height: 32px;"></p>
      <p align="center">2</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/sand.png" style="width: 32px; height: 32px;"></p>
      <p align="center">3</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/gravel.png" style="width: 32px; height: 32px;"></p>
      <p align="center">4</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/rock.png" style="width: 32px; height: 32px;"></p>
      <p align="center">5</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/oak_wood.png" style="width: 32px; height: 32px;"></p>
      <p align="center">6</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/oak_planks.png" style="width: 32px; height: 32px;"></p>
      <p align="center">7</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/birch_wood.png" style="width: 32px; height: 32px;"></p>
      <p align="center">8</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/birch_planks.png" style="width: 32px; height: 32px;"></p>
      <p align="center">9</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/leafs.png" style="width: 32px; height: 32px;"></p>
      <p align="center">10</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/cactus.png" style="width: 32px; height: 32px;"></p>
      <p align="center">11</p>
    </td>
  </tr>
  <tr>
    <td>
      <p align="center"><img src="screenshots/blocks/snow.png" style="width: 32px; height: 32px;"></p>
      <p align="center">12</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/full_snow.png" style="width: 32px; height: 32px;"></p>
      <p align="center">13</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/watermelon.png" style="width: 32px; height: 32px;"></p>
      <p align="center">14</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/pumpkin.png" style="width: 32px; height: 32px;"></p>
      <p align="center">15</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/coal_vein.png" style="width: 32px; height: 32px;"></p>
      <p align="center">16</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/iron_vein.png" style="width: 32px; height: 32px;"></p>
      <p align="center">17</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/emerald_vein.png" style="width: 32px; height: 32px;"></p>
      <p align="center">18</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/diamond_vein.png" style="width: 32px; height: 32px;"></p>
      <p align="center">19</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/bedrock.png" style="width: 32px; height: 32px;"></p>
      <p align="center">20</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/brick.png" style="width: 32px; height: 32px;"></p>
      <p align="center">21</p>
    </td>
    <td>
      <p align="center"><img src="screenshots/blocks/water.png" style="width: 32px; height: 32px;"></p>
      <p align="center">22</p>
    </td>
  </tr>
</table>


## Non-standard libraries

- **GLFW**: Window creation and input handling
- **GLAD**: OpenGL loader
- **GLM**: Math library
- **std_image**: Image loading library
- **Perlin noise**: Noise generation library
- **stb_image**: Image loading library

## About code

## Some screenshots from development process
![image](screenshots/s10.png)
![image](screenshots/s20.png)
![image](screenshots/s30.png)
![image](screenshots/s35.png)
![image](screenshots/s40.png)
![image](screenshots/s50.png)
![image](screenshots/s60.png)

##

# Final results
![image](screenshots/final1.jpeg)
![image](screenshots/final2.jpeg)
![image](screenshots/final3.jpeg)
![image](screenshots/final4.jpeg)
![image](screenshots/house.jpg)

##

## Credits 
- LearnOpenGL: https://learnopengl.com/
- Perlin noise library:
- Other clone: https://github.com/Hopson97/MineCraft-One-Week-Challenge

## Requirements
cmake
