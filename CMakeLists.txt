cmake_minimum_required(VERSION 3.13)
project(FROpenGLWrapper)

set(CMAKE_CXX_STANDARD 17)

set(header
        ${header}
        #${FR_X11_WINDOWS_MANAGER_PATH}/renderer.h
        )

set(src
        ${src}
        #${FR_X11_WINDOWS_MANAGER_PATH}/renderer.cpp
        )

set(libraries
        ${libraries}
        X11
        GL
        GLEW
        )