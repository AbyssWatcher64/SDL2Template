# Install script for directory: C:/Users/Pol/source/repos/SDL2Template/vcpkg_installed/x64-windows/vcpkg/blds/sdl2-mixer/src/ease-2.8.0-5d1a2b7a04.clean

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/Pol/source/repos/SDL2Template/vcpkg_installed/x64-windows/vcpkg/pkgs/sdl2-mixer_x64-windows")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Pol/source/repos/SDL2Template/vcpkg_installed/x64-windows/vcpkg/blds/sdl2-mixer/x64-windows-rel/SDL2_mixer.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "library" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Pol/source/repos/SDL2Template/vcpkg_installed/x64-windows/vcpkg/blds/sdl2-mixer/x64-windows-rel/SDL2_mixer.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES "C:/Users/Pol/source/repos/SDL2Template/vcpkg_installed/x64-windows/vcpkg/blds/sdl2-mixer/src/ease-2.8.0-5d1a2b7a04.clean/include/SDL_mixer.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2_mixer" TYPE FILE FILES
    "C:/Users/Pol/source/repos/SDL2Template/vcpkg_installed/x64-windows/vcpkg/blds/sdl2-mixer/x64-windows-rel/SDL2_mixerConfig.cmake"
    "C:/Users/Pol/source/repos/SDL2Template/vcpkg_installed/x64-windows/vcpkg/blds/sdl2-mixer/x64-windows-rel/SDL2_mixerConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2_mixer/SDL2_mixer-shared-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2_mixer/SDL2_mixer-shared-targets.cmake"
         "C:/Users/Pol/source/repos/SDL2Template/vcpkg_installed/x64-windows/vcpkg/blds/sdl2-mixer/x64-windows-rel/CMakeFiles/Export/97cddd3d921342b27159922255cdc1b6/SDL2_mixer-shared-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2_mixer/SDL2_mixer-shared-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2_mixer/SDL2_mixer-shared-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2_mixer" TYPE FILE FILES "C:/Users/Pol/source/repos/SDL2Template/vcpkg_installed/x64-windows/vcpkg/blds/sdl2-mixer/x64-windows-rel/CMakeFiles/Export/97cddd3d921342b27159922255cdc1b6/SDL2_mixer-shared-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2_mixer" TYPE FILE FILES "C:/Users/Pol/source/repos/SDL2Template/vcpkg_installed/x64-windows/vcpkg/blds/sdl2-mixer/x64-windows-rel/CMakeFiles/Export/97cddd3d921342b27159922255cdc1b6/SDL2_mixer-shared-targets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  
        # FIXME: use file(COPY_FILE) if minimum CMake version >= 3.21
        execute_process(COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "C:/Users/Pol/source/repos/SDL2Template/vcpkg_installed/x64-windows/vcpkg/blds/sdl2-mixer/x64-windows-rel/SDL2_mixer-Release.pc"
            "C:/Users/Pol/source/repos/SDL2Template/vcpkg_installed/x64-windows/vcpkg/blds/sdl2-mixer/x64-windows-rel/SDL2_mixer.pc")
        file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig"
            TYPE FILE
            FILES "C:/Users/Pol/source/repos/SDL2Template/vcpkg_installed/x64-windows/vcpkg/blds/sdl2-mixer/x64-windows-rel/SDL2_mixer.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "library" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/licenses/SDL2_mixer" TYPE FILE FILES "C:/Users/Pol/source/repos/SDL2Template/vcpkg_installed/x64-windows/vcpkg/blds/sdl2-mixer/src/ease-2.8.0-5d1a2b7a04.clean/LICENSE.txt")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/Pol/source/repos/SDL2Template/vcpkg_installed/x64-windows/vcpkg/blds/sdl2-mixer/x64-windows-rel/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
