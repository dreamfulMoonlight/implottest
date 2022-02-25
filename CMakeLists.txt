cmake_minimum_required(VERSION 3.5)

project(implot_test LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenCV 4 REQUIRED)

add_executable(implot_test
    Global.h
    GraphicsDataItem.h
    GraphicsDataItem.cpp
    GraphicsPlotItem.h
    GraphicsPlotItem.cpp
    GraphicsPlotLegend.h
    GraphicsPlotLegend.cpp
    imconfig.h
    imgui.h
    imgui.cpp
    implot_demo.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_internal.h
    imgui_tables.cpp
    imgui_widgets.cpp
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    implot.cpp
    implot.h
    imgui_impl_opengl3_loader.h
    imgui_impl_opengl3.h
    imgui_impl_opengl3.cpp
#    imgui_impl_glfw.h
#    imgui_impl_glfw.cpp
    implot_internal.h
    implot_items.cpp
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(implot_test PUBLIC Qt5::Widgets Qt5::Gui Qt5::Core)
#target_link_libraries(implot_test PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.dll
#    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3_mt.lib
#    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3dll.lib)

#add_custom_command(
#    TARGET implot_test POST_BUILD
#    COMMAND  ${CMAKE_COMMAND} -E copy_if_different
#    ${CMAKE_CURRENT_SOURCE_DIR}/glfw3.dll
#    $<TARGET_FILE_DIR:implot_test>)
