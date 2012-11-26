cmake_minimum_required (VERSION 2.6)

set(MY_STATIC_LIBRARY_SRCS 
MyStaticLibrary.cpp
)

set(MY_STATIC_LIBRARY_HDRS
MyStaticLibrary.h
)

add_library(MyStaticLibrary ${MY_STATIC_LIBRARY_SRCS})

