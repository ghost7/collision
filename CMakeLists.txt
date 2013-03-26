# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Collision)

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
file(COPY ${SHADERS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
