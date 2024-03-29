cmake_minimum_required(VERSION 3.14)

project(mediaplayer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Multimedia DBus REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Multimedia DBus REQUIRED)

set(DBUS_ADAPTER_UICONTROL_XML_FILES
    iappuicontrol.xml
)

qt5_add_dbus_adaptor(ADAPTER_UICONTROL_SOURCES
    ${DBUS_ADAPTER_UICONTROL_XML_FILES}
    iappuicontrol.h
    IAppUIControl
)

set(DBUS_INTERFACE_UICONTROL_XML_FILES
    iappmanageruicontrol.xml
)

qt5_add_dbus_interface(INTERFACE_UICONTROL_SOURCES ${DBUS_INTERFACE_UICONTROL_XML_FILES} IAppManagerUIControl)

set(DBUS_ADAPTER_MEDIACONTROL_XML_FILES
    imediaplayercontrol.xml
)

qt5_add_dbus_adaptor(ADAPTER_MEDIACONTROL_SOURCES
    ${DBUS_ADAPTER_MEDIACONTROL_XML_FILES}
    imediaplayercontrol.h
    IMediaPlayerControl
)

set(PROJECT_SOURCES
        main.cpp
        iappuicontrol.h
        iappuicontrolreceiver.h
        iappuicontrolreceiver.cpp
        appuicontrol.cpp
        appuicontrol.h
        song.cpp
        song.h
        player.cpp
        player.h
        songlist.cpp
        songlist.h
        appmanageruicontrol.cpp
        appmanageruicontrol.h
        imediaplayercontrol.h
        imediaplayercontrolreceiver.cpp
        imediaplayercontrolreceiver.h
        qml.qrc
        ${ADAPTER_UICONTROL_SOURCES}
        ${INTERFACE_UICONTROL_SOURCES}
        ${ADAPTER_MEDIACONTROL_SOURCES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(mediaplayer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

else()
    if(ANDROID)
        add_library(mediaplayer SHARED
            ${PROJECT_SOURCES}
        )

    else()
        add_executable(mediaplayer
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(mediaplayer PRIVATE ${TAGLIB_INCLUDE_DIRS})

target_compile_definitions(mediaplayer
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(mediaplayer
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick tag Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::DBus)

set_target_properties(mediaplayer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(mediaplayer)
    qt_finalize_executable(mediaplayer)
endif()
