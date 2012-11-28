cmake_minimum_required (VERSION 2.6)

# Con questo includiamo la directory 02-staticlib al compilatore che permette di trovare
# la classe MyStaticLibrary semplicemente includendola con #include "MyStaticLibrary.h"
include_directories(../02-staticlib)

set(TEST_STATIC_LINKING_SRC
testStaticLinking.cpp
)

add_executable(testStaticLinking ${TEST_STATIC_LINKING_SRC})
target_link_libraries(testStaticLinking MyStaticLibrary)
