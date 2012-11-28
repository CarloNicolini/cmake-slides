cmake_minimum_required (VERSION 2.6)

set(HELLOGL_HDR glwidget.h  qtlogo.h  window.h)
set(HELLOGL_SRC glwidget.cpp  main.cpp  qtlogo.cpp  window.cpp)
#set(HELLOGL_FORMS "MainWindow.ui")
#set(HELLOGL_RESOURCES "")
link_libraries(${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${Boost_LIBRARIES})
include_directories(${QT_INCLUDE_PATH} ${QT_QTGUI_INCLUDE_DIR} ${QT_QTCORE_INCLUDE_DIR} )

# Supporto per la gestione dei resources files
#QT4_ADD_RESOURCES( HELLOGL_RESOURCES_SOURCES ${HELLOGL_RESOURCES} )
# Supporto per la gestione dei form e la loro moc-izzazione
#QT4_WRAP_UI( HELLOGL_FORMS_HEADERS ${HELLOGL_FORMS} )
QT4_WRAP_CPP( HELLOGL_HEADERS_MOC ${HELLOGL_HDR} )

# Inizia la parte dipendente dal sistema operativo.

#### LINUX ####
if (UNIX AND NOT APPLE)
add_executable(helloGL ${HELLOGL_SRC} ${HELLOGL_HDR} ${HELLOGL_HEADERS_MOC}
	# Se si vogliono inserire i file risorsa per il progetto metterli qui: 
	# ${HELLOGL_RESOURCES_SOURCES} ${HELLOGL_RCS}
	# Se si hanno dei form .ui ${HELLOGL_FORMS_HEADERS}
	)

target_link_libraries(helloGL ${QT_LIBRARIES} ${GL_LIBS})
install(TARGETS helloGL DESTINATION bin COMPONENT "${QT_LIBRARIES};${GL_LIBS}")
endif (UNIX AND NOT APPLE)

