cmake_minimum_required(VERSION 3.10)
project("theplanets")

message("System: ${CMAKE_SYSTEM_NAME}")
#
# GLFW
#
find_package(glfw3 REQUIRED)
if (GLFW3_FOUND)
    message("found GLFW3")
    include_directories($(GLFW3_INCLUDE_DIRS))    
endif()

include_directories(Source/include)

set(SRCBASE "Source/src")
set(LIBBASE "Source/lib")
set(BINDIR  "./build/bin/${CMAKE_SYSTEM_NAME}")

add_executable(theplanets
           ${SRCBASE}/main.cpp 
           ${SRCBASE}/CGLApplication.cpp
           ${SRCBASE}/COpenGLAction.cpp
           ${LIBBASE}/CG3DReslistInterface.cpp
           ${LIBBASE}/CGL_Patch.cpp
           ${LIBBASE}/CGL_Ellipsoid.cpp
           ${LIBBASE}/CG3DResource.cpp
           ${LIBBASE}/CG3DResourceImgRef.cpp
           ${LIBBASE}/CG3DResourceButton.cpp
           ${LIBBASE}/CG3DResourceOButton.cpp
           ${LIBBASE}/CG3DResourceList.cpp
           ${LIBBASE}/CG3DResourceDialog.cpp
           ${LIBBASE}/CG3DResourceImage.cpp
           ${LIBBASE}/CG3DResourceString.cpp
           ${LIBBASE}/CG3DResourceFont.cpp
           ${LIBBASE}/CG3DResourceLine.cpp
           ${LIBBASE}/CG3DResourceBox.cpp
           ${LIBBASE}/CG3DResourceRoot.cpp
           ${LIBBASE}/CG3DResourceTextfield.cpp
           ${LIBBASE}/CG3DResourceTooltipp.cpp
           ${LIBBASE}/CG3DResourceClipframe.cpp
           ${LIBBASE}/CG3DResChild.cpp
           ${LIBBASE}/CTagList.cpp
           ${LIBBASE}/CErrorMessage.cpp
           ${LIBBASE}/CPixel24.cpp
           ${LIBBASE}/CDatabase3.cpp
           ${LIBBASE}/CFileIO.cpp
           ${LIBBASE}/CGraflib.cpp
           ${LIBBASE}/CGraflibTga.cpp
           ${LIBBASE}/CGraflibJpeg.cpp
           ${LIBBASE}/CGraphicsJpeg.cpp
           ${LIBBASE}/CGL_MatObject.cpp
           ${LIBBASE}/CGL_Texture.cpp
           ${LIBBASE}/COpenGL.cpp
           ${LIBBASE}/CGL_Camera.cpp
           ${LIBBASE}/CGL_Object.cpp
           ${LIBBASE}/CGL_Disk.cpp
           ${LIBBASE}/CGL_GLU_Object.cpp
           ${LIBBASE}/CGL_GLU_Sphere.cpp
           ${LIBBASE}/CGL_FontTableau.cpp
           ${LIBBASE}/CGL_Circle.cpp
)


if (CMAKE_SYSTEM_NAME STREQUAL "MSYS")
    #
    # Windows
    #
    SET(SYSTEM_NAME "windows")
    target_link_libraries(theplanets
        gl)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    #
    # Linux
    #
    SET(SYSTEM_NAME "linux")
    target_link_libraries(theplanets
        GL
        GLU
        glut
        jpeg)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    #
    # Mac OS
    #
    # *TODO*
    SET(SYSTEM_NAME "mac")
endif()


file(MAKE_DIRECTORY ${BINDIR})
set_target_properties(theplanets PROPERTIES OUTPUT_NAME ../${BINDIR}/theplanets)    
