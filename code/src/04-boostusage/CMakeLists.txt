cmake_minimum_required (VERSION 2.6)

set(MY_BOOST_EXAMPLE_SRCS 
testBoostThreads.cpp
)

add_executable(testBoostThreads ${MY_BOOST_EXAMPLE_SRCS})
target_link_libraries(testBoostThreads ${BOOST_LIBS})

# alternativo, linkare TUTTO boost
#target_link_libraries(testBoostThreads ${BOOST_LIBS})
