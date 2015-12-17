# OpenCV-Bootstrap
Set up OpenCV c++ project in a few seconds, good for Visual Studio in Windows/OS X/Linux, etc

### What's new
- Add script for creating vs2015 project
- More elegant way to organize code
- Add Eclipse CDT generator on unix-like systems 

## What
This is a CMake powered bootstrap project for everyone who need to set up OpenCV C++ environment. 

With OpenCV-Bootstrap, one can create a valid project in just a few seconds if prerequisites are already satisfied.

## Why 
*Keyword: automation.*

Config OpenCV correctly is a trivial but complicated work, even an expert on this area may take a while and googling around to be able to set up all the include directories and link targets. 

It is even more frustrating in Visual Studio, where you have to figure out the different link targets according to OpenCV version and debug/release mode. 

Hopefully this script will save the waste-of-time useless steps in order to bootstrap a OpenCV project.

## How-to use the script

#### Prerequisites
You can skip this step if you have CMake and OpenCV installed.
- [CMake](https://cmake.org/)
  1. Windows: 
    - If you use a msi-installer on Windows, be sure to let installer add CMake to the PATH.
  2. Linux: 
    - The best way to get CMake is to use package manager, whatever apt-get, yum...
  3. OS X: 
    - Use homebrew to install CMake
    - If you use the application downloaded directly, use **Tools->Install For Command Line Use** menu item
- [OpenCV](https://http://opencv.org/)
  1. Windows:
    - Download the pre-complied zip file from the official website, extract to anywhere you like, e.g. "c:\\dev\\opencv"
  2. Unix-like OS:
    - Use apt-get, yum or homebrew to get opencv directly, e.g. sudo apt-get install opencv-dev. All set.
    - Or, if you are familiar enough, manually build opencv(Let BUILD_SHARED_LIBS=ON to build shared library, OFF for static library)
	
#### Organize source code

If you don't have existing code, just wanna try it, then skip this step

- Put headers to include in /path/to/project/include, remember to use **"#include \<xxx.h\>"** for these headers. I usually put 3rdparty template libraries(actually any header-only libraries) and my own API fuctions in this folder. 
- Put all source codes (headers and sources) in /path/to/project/src, use **"#include "xxx.h"** for these headers

#### Config
Open CMakeLists.txt using text editor in /path/to/project/build. There are only four parameters.

By default, windows users have to change **CUSTOM_OPENCV_DIR**, linux users don't need to modify anything.
- SET(PROJECT_NAME **"opencv-bootstrap"**) : Set up the project name which will later be created
- SET(LINK_OPENCV_STATIC **ON**) : This option is only valid for windows users, if set to ON, will create static linked project using static libraries.
- SET(CUSTOM_OPENCV_DIR **"D:\\Dev\\opencv\\build"**) : Where to look for opencv, most likely it is the extracted folder from a zip file downloaded from website for windows users(don't forget to include '/build' in path).
- SET(USE_CUSTOM_OPENCV_DIR_IN_NIX **OFF**) : For non-windows only, turn this on will force to use the previous opencv directory, otherwise it will search the system default path such as "/usr/local/lib"

#### Run the script
```
# open a command line prompt
$cd /path/to/project
$cd /build

# for VS project on windows
$create_vs2013_project.bat
# Or you can double click on the bat file to run it in explorer

# for Eclipse CDT on unix-like OS
$./generate_eclipse_cdt.sh
# import project as a makefile project in eclipse
# "File -> Import -> Existing code as Makefile project" -> navigate to /path/to/proj/build/cdt4

# for others using script
$./build_script.sh
```
When finished, visual studio project will be created in build/vc12 folder. For other OS, the makefile and build binary will be created within build folder.

---

#### Some notes
##### Static or Shared
I choose to link opencv static libraries by default
- Pros
  - No need to carry opencv*.dll around anymore
  - No need to figure out which dll to include in distributed softwares.
  - Single binary file, clean and simple
- Cons
  - The generated binary will larger than dynamically linked one in size.
  - Runtime portability? Not sure really.

Turn on static build is enough for windows, however, for linux for example, this flag has no effect. Let BUILD_SHARED_LIBS=OFF when building OpenCV.

##### OpenCV path in windows
In traditional tutorials, they tell you to add opencv build path to system PATH, so that you can run program against the dlls. 

The story is a little bit different here, to build the project, you don't even have to do that, the script will handle the opencv_dir from anywhere on disk as long as you set **CUSTOM_OPENCV_DIR**. 

- If you build using static library, after build, it is good to run anywhere.
- If you build using dynamic library as usual, you have either **copy opencv_xxx.dll to the same directory** or **add opencv build dir to system PATH**, because the binary file need to 'see' the dlls.
  
### Compare to manual setup
| Scenario | opencv-bootstrap | manual setup |
| ---- | ---------------- | ------------ |
| Setup environment | 0(already installed) ~ 45min(depend on network) |  0(already installed) ~ 40min(depend on network)  |
| Config the first project | <1min | 15min ~ ?? |
| Portablity | Awesome | Bad |
| Version control | happlily commit script to git | better not commit the entire solution to git |
| Update opencv version | slight modify, no pain | most like will not do it, too complicated and trivial |
| Corrupted project | delete and rebuild project in seconds | desperately want to recover the old settings |
| Mood | :) | :( |
