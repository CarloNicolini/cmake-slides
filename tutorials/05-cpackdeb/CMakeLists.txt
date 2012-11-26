cmake_minimum_required (VERSION 2.6)

set(MY_PROGRAM_SRCS 
myProgram.cpp
)

add_executable(myProgram ${MY_PROGRAM_SRCS})
target_link_libraries(myProgram boost_thread-mt)

# alternativo, linkare TUTTO boost
#target_link_libraries(testBoostThreads ${BOOST_LIBS})
