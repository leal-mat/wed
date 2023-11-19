cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)

include(CMakePrintHelpers)



project(modelagem LANGUAGES CXX)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGLWidgets)
find_package(glm)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

qt_add_executable(
    wed
    main.cpp
    # Mesh.cpp
    # Wed.cpp
    # Utils.hpp
    # Face.hpp
    # Vertex.hpp
)

target_link_libraries(wed PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::OpenGLWidgets)