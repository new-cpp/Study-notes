
## resources:
   - https://www.youtube.com/watch?v=s2doMS59tVc&t=472s
   - https://learn.microsoft.com/fr-fr/vcpkg/get_started/get-started?pivots=shell-cmd


steps to make sdl project in windows with vcpkg and sdl:


first time :

 git clone https://github.com/microsoft/vcpkg.git
 cd vcpkg && bootstrap-vcpkg.bat
 set VCPKG_ROOT="C:\path\to\vcpkg"
 set PATH=%VCPKG_ROOT%;%PATH%
 
 mkdir helloworld && cd helloworld
 vcpkg new --application
 
 
 
next :
 #add depedencies :
 vcpkg add port fmt
 
 
 create CMakeLists.txt:
   {
       cmake_minimum_required(VERSION 3.1...3.29)

       project(
       SDL_leaning_example
       VERSION 1.0
       LANGUAGES CXX)


       message("here : " ${FILENAME})
       add_executable(main ${FILENAME}.cpp)


       find_package(SDL2 CONFIG REQUIRED)

       target_link_libraries(main PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2::SDL2-static)
   }
	

create CMakePresets.json:
 
 
 {
	{  
    "version": 2,
    "configurePresets": 
          [     
              {       
                  "name": "default",       
                  "generator": "Visual Studio 17 2022",
                  "binaryDir": "${sourceDir}/build",       
                  "cacheVariables":
                  {         
                      "CMAKE_TOOLCHAIN_FILE": "D:/tools/vcpkg/scripts/buildsystems/vcpkg.cmake",
                      "VCPKG_TARGET_TRIPLET": "x64-windows-static"
                  }     
              }   
          ]
    }
 }
 
 
 
 cmake --preset=default -DFILENAME="filename"
 cmake --build build
 .\build\main.exe
