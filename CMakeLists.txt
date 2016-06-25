#cmake_minimum_required(VERSION 3.5)
cmake_minimum_required(VERSION 2.8)
project(missile)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(PkgConfig)

pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

set(SOURCE_FILES
        main.cpp
        usb_utils.h
        usb_utils.cpp
        MissileDevice.h
        MissileDevice.cpp
        MissileKeyboardHandler.h
        MissileKeyboardHandler.cpp
        MissileController.h
        MissileController.cpp
        )

add_executable(missile ${SOURCE_FILES})

link_directories(${GTKMM_LIBRARY_DIRS})

include_directories(${GTKMM_INCLUDE_DIRS})

target_link_libraries(missile usb ${GTKMM_LIBRARIES})



