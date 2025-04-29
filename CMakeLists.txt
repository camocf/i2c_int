##************************************************************************
##  CMakeLists.txt for i2c_int Library
##************************************************************************
## Copyright (c) Cameron Fielden
##                                                                        
## Permission is hereby granted, free of charge, to any person obtaining  
## a copy of this software and associated documentation files (the        
## "Software"), to deal in the Software without restriction, including    
## without limitation the rights to use, copy, modify, merge, publish,    
## distribute, sublicense, and/or sell copies of the Software, and to     
## permit persons to whom the Software is furnished to do so, subject to  
## the following conditions:                                              
##                                                                        
## The above copyright notice and this permission notice shall be         
## included in all copies or substantial portions of the Software.        
##                                                                        
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        
## EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     
## MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
## IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   
## CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   
## TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      
## SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 
##************************************************************************

cmake_minimum_required(VERSION 3.20)

###################### VARIABLES ######################################
set (PROJECT_NAME  "i2c_int")
set (CMAKE_TOOLCHAIN_FILE "avr-toolchain.cmake")

# Specify the AVR target and other flags
set(AVR_MCU "" CACHE STRING "Set Target MCU") # Replace with your target MCU
set(F_CPU   "" CACHE STRING "Set MCU Frequency") # Replace with your target frequency
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Set Build Type")

if(NOT AVR_MCU)
    message(FATAL_ERROR "AVR_MCU is not set. Please set it in the CMake GUI or command line.")
endif()
if(NOT F_CPU)
    message(FATAL_ERROR "F_CPU is not set. Please set it in the CMake GUI or command line.")
endif()

set (PROJECT_SOURCES
    source/i2c_int.c
    )
set (PROJECT_INCLUDES
    include
    )

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building ${PROJECT_NAME}: Debug")
    set (PROJECT_C_FLAGS
        -mmcu=${AVR_MCU}
        -DF_CPU=${F_CPU}
        -Wall
        -Wextra
        -Werror
        -g
        )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
message(STATUS "Building ${PROJECT_NAME}: Release")
    set (PROJECT_C_FLAGS
        -mmcu=${AVR_MCU}
        -DF_CPU=${F_CPU}
        -Os
        -Wall
        -Wextra
        -Werror
        )
else()
    message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}. Use 'Debug' or 'Release'.")
endif()

################## PROJECT SETUP ######################################
project(${PROJECT_NAME})
add_compile_options(${PROJECT_C_FLAGS})
include_directories( ${PROJECT_INCLUDES})
add_library(${PROJECT_NAME} ${PROJECT_SOURCES})
