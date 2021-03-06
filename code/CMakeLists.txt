# This project is intended to give a fast overview of the CMake build-system possibilities
project(cmake-tutorials)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0 FATAL_ERROR)

OPTION(CREATE_QT_OPENGL_EXAMPLE "Create QT+OpenGL executable" OFF)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
set(PROJECT_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build/")
set(LIBRARY_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/" CACHE PATH "Single directory for all libraries")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/" CACHE PATH "Single directory for all executables")

# This flag helps compiling dynamic libraries in OSX in both flavors
if (APPLE)
#set(CMAKE_OSX_ARCHITECTURES "i386;x86_64")
endif (APPLE)

set(BOOST_LIBS thread date_time system program_options filesystem regex serialization iostreams)
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)

link_directories ( ${Boost_LIBRARY_DIRS} )
include_directories ( ${Boost_INCLUDE_DIRS} )
find_package(Boost COMPONENTS ${BOOST_LIBS} REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
find_package(Threads REQUIRED)

####################### END BOOST LIBRARIES INCLUDE AND LINKING ################

# Activates OpenMP on architectures which support it
include(FindOpenMP)
if(OPENMP_FOUND)
    message(STATUS "Adding OpenMP flags to MSVC: ${OpenMP_CXX_FLAGS} and ${OpenMP_EXE_LINKER_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${PROJECT_BINARY_DIR} )

add_subdirectory(src/01-helloworld)
add_subdirectory(src/02-staticlib)
add_subdirectory(src/03-sharedlib)
add_subdirectory(src/04-boostusage)
add_subdirectory(src/05-cpackdeb)
add_subdirectory(src/06-staticlibrarylinking)

if ( CREATE_QT_OPENGL_EXAMPLE )
# Find OpenGL and GLUT libraries
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})
set(GL_LIBS ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})

# Search for QT LIBRARIES
set(QT_MIN_VERSION "4.6.0")
set(QT_USE_QTMAIN TRUE)
set(QT_USE_OPENGL TRUE)
find_package(Qt4 4.6.0 COMPONENTS QtGui QtCore QtOpenGL QtSvg REQUIRED )
INCLUDE(${QT_USE_FILE})
add_subdirectory(src/07-qt+opengl)
endif ( CREATE_QT_OPENGL_EXAMPLE )

# Sezione creazione pacchi per i vari sistemi operativi

################################################################################
############################ CREAZIONE LINUX ###################################
################################################################################
set(MY_BOOST_THREAD_EXAMPLE_MAJOR "1")
set(MY_BOOST_THREAD_EXAMPLE_MINOR "0")
set(MY_BOOST_THREAD_EXAMPLE_PATCH "0")

set(CPACK_PACKAGE_NAME "myProgram")
set(CPACK_PACKAGE_VERSION "${MY_BOOST_THREAD_EXAMPLE_MAJOR}.${MY_BOOST_THREAD_EXAMPLE_MINOR}.${MY_BOOST_THREAD_EXAMPLE_PATCH}")
set(CPACK_PACKAGE_DESCRIPTION "Esempio di creazione di un pacco Linux per un semplice programma")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Abbiamo creato un pacco contenente un semplice eseguibile che sfrutta boost::thread")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.txt")
set(CPACK_PACKAGE_CONTACT "John Doe ilmio@indirizzo.com")
set(CPACK_PACKAGE_AUTHOR "John Doe")
set(CPACK_PACKAGE_VENDOR "The XXX team")

# Imposta la versione del pacco, MAJOR-MINOR-PATCH
set(CPACK_PACKAGE_VERSION_MAJOR ${MY_BOOST_THREAD_EXAMPLE_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${MY_BOOST_THREAD_EXAMPLE_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${MY_BOOST_THREAD_EXAMPLE_PATCH})

# Importante imposta il nome finale del pacchetto
set(CPACK_PACKAGE_FILE_NAME  "${CPACK_PACKAGE_NAME}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
#set(CPACK_SET_DESTDIR ON) # http://cmake.3232098.n2.nabble.com/CPack-RPM-and-install-td5213420.html

##########################################################
if (UNIX AND NOT APPLE)
	INCLUDE (InstallRequiredSystemLibraries)
        #If a sysconfdir is specified, use it instead
        #of the default configuration dir.
        if(DEFINED SYSCONFDIR)
                set(SYSCONFDIR ${SYSCONFDIR} CACHE PATH "config directory")
        else(DEFINED SYSCONFDIR)
                set(SYSCONFDIR ${PREFIX}/etc CACHE PATH "config directory")
        endif(DEFINED SYSCONFDIR)
        #If an XDG Config Dir is specificed, use it instead
        #of the default XDG configuration dir.
        if(DEFINED XDG_CONFIG_DIR)
        set(XDG_CONFIG_DIR ${XDG_CONFIG_DIR} CACHE PATH "xdg config directory")
        else(DEFINED XDG_CONFIG_DIR)
                set(XDG_CONFIG_DIR ${SYSCONFDIR}/xdg CACHE PATH "xdg config directory")
        endif(DEFINED XDG_CONFIG_DIR)
        
        # Importante questo imposta i generatori utilizzati per generare il pacco
        # http://www.vtk.org/Wiki/CMake:CPackPackageGenerators#TGZ
	set(CPACK_GENERATOR "DEB;RPM;STGZ;TGZ")
	set(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
	set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS TRUE)
        # LE DIPENDENZE PER IL PACCO RPM VENGONO RISOLTE AUTOMATICAMENTE DA CMAKE VERSIONE >= 2.8.1
        if( NOT DESKTOP_ENTRY )
        set( DESKTOP_ENTRY ${CMAKE_CURRENT_SOURCE_DIR}/myProgram.desktop )
        endif( NOT DESKTOP_ENTRY )
        # Crea il file myprogram.desktop
        add_custom_command( OUTPUT ${DESKTOP_ENTRY} COMMAND touch ${DESKTOP_ENTRY} COMMAND sh ${CMAKE_MODULE_PATH}/generateLinuxDesktopEntry.sh ${CMAKE_INSTALL_PREFIX} >${DESKTOP_ENTRY} 
                DEPENDS ${CMAKE_MODULE_PATH}/generateLinuxDesktopEntry.sh COMMENT "Generating desktop entry file")
        add_custom_target( DESKTOP_ENTRY_FILE ALL DEPENDS ${DESKTOP_ENTRY} )
        # crea il file myProgram.menu XML contenente le informazioni per aggiungere al menu
        if( NOT MENU_ENTRY )
                set( MENU_ENTRY ${CMAKE_CURRENT_SOURCE_DIR}/myProgram.menu )
        endif( NOT MENU_ENTRY )
        add_custom_command( OUTPUT ${MENU_ENTRY} COMMAND touch ${MENU_ENTRY} COMMAND sh ${CMAKE_MODULE_PATH}/generateLinuxMenuEntry.sh ${CMAKE_INSTALL_PREFIX} >${MENU_ENTRY} DEPENDS ${CMAKE_MODULE_PATH}/generateLinuxMenuEntry.sh COMMENT "Generating menu XML entry file")
        add_custom_target( MENU_ENTRY_FILE ALL DEPENDS ${MENU_ENTRY} )

        if( NOT DIRECTORY_ENTRY )
                set( DIRECTORY_ENTRY ${CMAKE_CURRENT_SOURCE_DIR}/myProgram.directory )
        endif( NOT DIRECTORY_ENTRY )
        add_custom_command( OUTPUT ${DIRECTORY_ENTRY} COMMAND touch ${DIRECTORY_ENTRY} COMMAND sh ${CMAKE_MODULE_PATH}/generateLinuxDirectory.sh ${CMAKE_INSTALL_PREFIX} >${DIRECTORY_ENTRY} DEPENDS ${CMAKE_MODULE_PATH}/generateLinuxDirectory.sh COMMENT "Generating linux directory entry file")
        add_custom_target( DIRECTORY_ENTRY_FILE ALL DEPENDS ${DIRECTORY_ENTRY} )

        # Imposta l'icona
        set(APP_ICON ${CMAKE_SOURCE_DIRECTORY}/resources/icons/logo.png)
        # freedesktop file, lo copia in /usr/share/applications dove stanno tutti gli altri file delle applicazioni da mostrare nella lista principale
        #install(FILES myProgram.desktop DESTINATION "share/applications/")
        #install(FILES myProgram.menu DESTINATION "${XDG_CONFIG_DIR}/menus/")
        #install(FILES myProgram.directory DESTINATION "share/desktop-directories/")
endif(UNIX AND NOT APPLE)


include(CPack)

