#
#
# Windows (MSYS):
# use generator cmake -G "Unix Makefiles" 
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

include_directories(Source/include)

set(CMAKE_C_LINK_EXECUTABLE "g++")
set(SRCBASE "Source/src")
set(LIBBASE "Source/lib")
set(BINDIR  "./build/bin/${CMAKE_SYSTEM_NAME}")

add_executable(theplanets
           ${SRCBASE}/main.cpp 
           ${SRCBASE}/CGLApplication.cpp
           ${SRCBASE}/COpenGLAction.cpp
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
           ${LIBBASE}/Graflib/CPixel24.cpp
           ${LIBBASE}/Graflib/CPixel32.cpp
           ${LIBBASE}/Graflib/CGraflib.cpp
           ${LIBBASE}/Graflib/CGraflibTga.cpp
           ${LIBBASE}/Graflib/CGraflibJpeg.cpp
           ${LIBBASE}/Graflib/CGraphicsJpeg.cpp
           ${LIBBASE}/CGL/CGL_MatObject.cpp
           ${LIBBASE}/CGL/CGL_Patch.cpp
           ${LIBBASE}/CGL/CGL_Ellipsoid.cpp
           ${LIBBASE}/CGL/CGL_Texture.cpp
           ${LIBBASE}/CGL/COpenGL.cpp
           ${LIBBASE}/CGL/CGL_Camera.cpp
           ${LIBBASE}/CGL/CGL_Object.cpp
           ${LIBBASE}/CGL/CGL_Disk.cpp
           ${LIBBASE}/CGL/CGL_GLU_Object.cpp
           ${LIBBASE}/CGL/CGL_GLU_Sphere.cpp
           ${LIBBASE}/CGL/CGL_FontTableau.cpp
           ${LIBBASE}/CGL/CGL_Circle.cpp
           ${LIBBASE}/CGL/CGL_StarField.cpp
)


if (CMAKE_SYSTEM_NAME STREQUAL "MSYS")
    #
    # Windows
    #
    SET(SYSTEM_NAME "windows")
    target_link_libraries(theplanets
		glu32
		freeglut
		opengl32
		gdi32
		winmm
		jpeg62
		)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    #
    # Linux
    #
    SET(SYSTEM_NAME "linux")
    target_link_libraries(theplanets
        GL
        GLU
        glut
        libjpeg.so.62)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    #
    # Mac OS
    #
    # *TODO*
    SET(SYSTEM_NAME "mac")
endif()


file(MAKE_DIRECTORY ${BINDIR})
set_target_properties(theplanets PROPERTIES OUTPUT_NAME ../${BINDIR}/theplanets)    
