##************************************************************************
##  avr-toolchain.cmake for i2c_int Library
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

set (CMAKE_SYSTEM_PROCESSOR "avr" CACHE STRING "")
set (CMAKE_SYSTEM_NAME "Generic" CACHE STRING "")

# Skip link step during toolchain validation.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(TOOLCHAIN_PREFIX   "avr-")
set(CMAKE_C_COMPILER   "${TOOLCHAIN_PREFIX}gcc")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PREFIX}gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PREFIX}g++")
set(CMAKE_AR           "${TOOLCHAIN_PREFIX}ar")
set(CMAKE_LINKER       "{TOOLCHAIN_PREFIX}ld")
set(CMAKE_OBJCOPY      "${TOOLCHAIN_PREFIX}objcopy")
set(CMAKE_RANLIB       "${TOOLCHAIN_PREFIX}ranlib")
set(CMAKE_SIZE         "${TOOLCHAIN_PREFIX}size")
set(CMAKE_STRIP        "${TOOLCHAIN_PREFIX}ld")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)


