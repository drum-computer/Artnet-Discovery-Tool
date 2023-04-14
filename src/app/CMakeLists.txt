qt_add_executable(artnet_discovery_tool
    application.qrc
    main.cpp
    artnettoolutils.h
    udpserver.h udpserver.cpp
    devicefinder.h devicefinder.cpp
    artpollreplytablemodel.h artpollreplytablemodel.cpp
    networkinterfaceselectormodel.h networkinterfaceselectormodel.cpp
    networkinterfaceselector.h networkinterfaceselector.cpp
)

qt_add_qml_module(artnet_discovery_tool
    URI cm_tool
    VERSION 1.0
)

set_target_properties(artnet_discovery_tool PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(artnet_discovery_tool
    PRIVATE Qt6::Quick Qt6::QuickControls2)

install(TARGETS artnet_discovery_tool
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
