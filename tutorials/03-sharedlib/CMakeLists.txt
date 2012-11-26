cmake_minimum_required (VERSION 2.6)

set(MY_DYNAMIC_LIBRARY_SRCS 
MyDynamicLibrary.cpp
)

set(MY_DYNAMIC_LIBRARY_HDRS
MyDynamicLibrary.h
)

add_library(MyDynamicLibrary SHARED ${MY_DYNAMIC_LIBRARY_SRCS})

