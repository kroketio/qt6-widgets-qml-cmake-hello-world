set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets QuickWidgets Gui Quick Quick3D Multimedia)

file(GLOB SOURCE_FILES
    "*.h"
    "*.cpp"
    "lib/*.h"
    "lib/*.cpp"
    )

qt_add_executable(hello
  main.cpp
  ${SOURCE_FILES}
)

target_link_libraries(hello PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Multimedia
    Qt6::Qml
    Qt6::Quick
    Qt6::Quick3D
    Qt6::Widgets
    Qt6::QuickWidgets
    PNG::PNG
)

qt_add_qml_module(hello
    URI Hello
    VERSION 1.0
    QML_FILES
        qml/main.qml
    RESOURCES
        assets/rabbit.png
    NO_RESOURCE_TARGET_PATH
)
