# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Grafika)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.1.2/include/GLFW/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# Our Project Interior Decorator
add_executable(Interior_decorator
	Interior_decorator/Interior_decorator.cpp
	Interior_decorator/file_loader.h
	Interior_decorator/file_loader.cpp
	Interior_decorator/Raw_Obj_Data.h
	Interior_decorator/Raw_Obj_Data.cpp
	Interior_decorator/Display.h
	Interior_decorator/Display.cpp
	utilities/shader_loader.cpp
	utilities/shader_loader.h
	utilities/control_objects.cpp
	utilities/control_objects.h
	utilities/controls.cpp
	utilities/controls.h
	utilities/control_camera.cpp
	utilities/control_camera.h
	utilities/time.cpp
	utilities/time.h
	common/texture.cpp
	common/texture.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	common/quaternion_utils.cpp
	common/quaternion_utils.hpp
	
	Interior_decorator/VertexShader.vert
	Interior_decorator/FragmentShader.frag
)
target_link_libraries(Interior_decorator
	${ALL_LIBS}
	ANTTWEAKBAR_116_OGLCORE_GLFW
)
# Xcode and Visual working directories
set_target_properties(Interior_decorator PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Interior_decorator/")
create_target_launcher(Interior_decorator WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Interior_decorator/")




# To coś tworzy podfolder w projekcie
SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(utilities REGULAR_EXPRESSION ".*/utilities/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*Shader*" )


if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
add_custom_command(
   TARGET Interior_decorator POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/Interior_decorator${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/Interior_decorator/"
)

elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

