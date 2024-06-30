#
#

cmake_minimum_required(VERSION 3.10)
project("theplanets")

message("System: ${CMAKE_SYSTEM_NAME}")
#
# GLFW
#
#find_package(glfw3 REQUIRED)
#if (GLFW3_FOUND)
#    message("found GLFW3")
#    include_directories($(GLFW3_INCLUDE_DIRS))    
#endif()
#
# for 


set(CMAKE_C_LINK_EXECUTABLE "g++")
set(SRCBASE "Source/src")
set(INCBASE "Source/include")
set(LIBBASE "Source/lib")
set(BINDIR  "./build/bin/${CMAKE_SYSTEM_NAME}")


include_directories(
    ${INCBASE}
    ${INCBASE}/CGL
    ${INCBASE}/Graflib
    ${INCBASE}/Reslib
    ${INCBASE}/Tools
    ${INCBASE}/ThePlanets
)


#find_package(SDL2 REQUIRED)
#include_directories(${SDL2_INCLUDE_DIR})


add_executable(theplanets
    ${SRCBASE}/mainSdl.cpp 
    ${SRCBASE}/CGLApplication.cpp
    ${SRCBASE}/CGL_Gradnetz.cpp
    ${SRCBASE}/CGL_KraterCircle.cpp
    ${SRCBASE}/COpenGLAction.cpp
    ${SRCBASE}/CMond.cpp
    ${SRCBASE}/CPlanet.cpp
    ${SRCBASE}/CLabels.cpp
    ${SRCBASE}/NPlanets.cpp
    ${LIBBASE}/Resource/CG3DReslistInterface.cpp
    ${LIBBASE}/Resource/CG3DResource.cpp
    ${LIBBASE}/Resource/CG3DResourceImgRef.cpp
    ${LIBBASE}/Resource/CG3DResourceButton.cpp
    ${LIBBASE}/Resource/CG3DResourceOButton.cpp
    ${LIBBASE}/Resource/CG3DResourceList.cpp
    ${LIBBASE}/Resource/CG3DResourceDialog.cpp
    ${LIBBASE}/Resource/CG3DResourceImage.cpp
    ${LIBBASE}/Resource/CG3DResourceString.cpp
    ${LIBBASE}/Resource/CG3DResourceFont.cpp
    ${LIBBASE}/Resource/CG3DResourceLine.cpp
    ${LIBBASE}/Resource/CG3DResourceBox.cpp
    ${LIBBASE}/Resource/CG3DResourceRoot.cpp
    ${LIBBASE}/Resource/CG3DResourceTextfield.cpp
    ${LIBBASE}/Resource/CG3DResourceTooltipp.cpp
    ${LIBBASE}/Resource/CG3DResourceClipframe.cpp
    ${LIBBASE}/Resource/CG3DResChild.cpp
    ${LIBBASE}/Tools/CTagList.cpp
    ${LIBBASE}/Tools/CErrorMessage.cpp
    ${LIBBASE}/Tools/CDatabase3.cpp
    ${LIBBASE}/Tools/CFileIO.cpp
    ${LIBBASE}/Tools/NStringTool.cpp
    ${LIBBASE}/Graflib/CPixel24.cpp
    ${LIBBASE}/Graflib/CPixel32.cpp
    ${LIBBASE}/Graflib/CGraflib.cpp
    ${LIBBASE}/Graflib/CGraflibTga.cpp
    ${LIBBASE}/Graflib/CGraflibJpeg.cpp
    ${LIBBASE}/Graflib/CGraphicsJpeg.cpp
    ${LIBBASE}/CGL/CGL_MatObject.cpp
    ${LIBBASE}/CGL/CGL_Patch.cpp
    ${LIBBASE}/CGL/CGL_Ellipsoid.cpp
    ${LIBBASE}/CGL/CGL_EllipsoidPatched.cpp
    ${LIBBASE}/CGL/CGL_Texture.cpp           
    ${LIBBASE}/CGL/CGL_Camera.cpp
    ${LIBBASE}/CGL/CGL_Object.cpp
    ${LIBBASE}/CGL/CGL_Disk.cpp
    ${LIBBASE}/CGL/CGL_GLU_Object.cpp
    ${LIBBASE}/CGL/CGL_GLU_Sphere.cpp
    ${LIBBASE}/CGL/CGL_FontTableau.cpp
    ${LIBBASE}/CGL/CGL_Circle.cpp
    ${LIBBASE}/CGL/CGL_Ellipse.cpp
    ${LIBBASE}/CGL/CGL_StarField.cpp
    ${LIBBASE}/CSDL/CSDL_App.cpp
    ${LIBBASE}/mvlib/mvpng/mv_graphics_png.c
)


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    #
    # Windows
    #
    SET(SYSTEM_NAME "windows")
    target_link_libraries(${CMAKE_PROJECT_NAME}
        glu32        
        opengl32
        gdi32
        winmm
        jpeg
        SDL2
        glew32
        png
    )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    #
    # Linux
    #
    SET(SYSTEM_NAME "linux")
    target_link_libraries(${CMAKE_PROJECT_NAME}
        GL
        GLU
        SDL2
        GLEW
        jpeg
        png)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    #
    # Mac OS
    #
    # *TODO*
    SET(SYSTEM_NAME "mac")
endif()



add_definitions(-DSDL_MAIN_HANDLED)

file(MAKE_DIRECTORY ${BINDIR})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ../distribution/${CMAKE_PROJECT_NAME}/${CMAKE_PROJECT_NAME}) 

