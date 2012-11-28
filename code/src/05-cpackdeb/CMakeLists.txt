cmake_minimum_required (VERSION 2.6)

set(MY_PROGRAM_SRCS 
myProgram.cpp
)

add_executable(myProgram ${MY_PROGRAM_SRCS})
target_link_libraries(myProgram ${BOOST_LIBS})

# Parte relativa a CPACK per generazione del pacchetto (debian o rpm, facendo così installa anche le dipendenze da Qt e FreeGLUT
install(TARGETS myProgram DESTINATION bin COMPONENT)
install(FILES "${CMAKE_SOURCE_DIR}/resources/icons/logo.png" DESTINATION share/myProgram/icons/)
# alternativo, linkare TUTTO boost
#target_link_libraries(testBoostThreads ${BOOST_LIBS})
