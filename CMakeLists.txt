# CMake entry point
cmake_minimum_required (VERSION 2.8)
project (Collision)

# Macro to copy files to a specified diectory
# Arguments:
#	TARGET	- copy when this target is built
#	SRC_DIR	- the source directory
#	DST_DIR - the destination directory
#	FILES	- files to copy
MACRO(COPY_IF_DIFFERENT TARGET SRC_DIR DST_DIR FILES)
	foreach(FILENAME ${FILES})
		set(SRC "${SRC_DIR}/${FILENAME}")
		set(DST ${DST_DIR})

		add_custom_command(TARGET ${TARGET} PRE_BUILD
						   COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SRC} ${DST})
	endforeach(FILENAME)
ENDMACRO(COPY_IF_DIFFERENT TARGET SRC_DIR DST_DIR FILES)

find_package(OpenGL REQUIRED)

# Compile external dependencies 
add_subdirectory (external)

include_directories(
	external/glfw-2.7.7/include/
	external/glew-1.9.0/include/
	external/glm-0.9.4.0/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	GLFW_277
	GLEW_190
)

set(SHADERS
	SimpleFragmentShader.frag
	SimpleVertexShader.vert
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_executable(demo 
	demo.cpp
	sat/Polygon.h
	sat/Polygon.cpp
	sat/PolygonArtist.cpp
	sat/PolygonArtist.h
	util/ShaderProgram.cpp
	util/ShaderProgram.h
	${SHADERS}
)
target_link_libraries(demo
	${ALL_LIBS}
)

# Copy shaders to build directory
COPY_IF_DIFFERENT(demo ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} "${SHADERS}")




