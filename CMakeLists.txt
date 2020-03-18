cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(BuoyancySimulation
	VERSION 0.2.0
	LANGUAGES CXX C
	DESCRIPTION "Buoyancy Simulation"
)

# Define Release by default.
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()
message(STATUS "Build type is set to ${CMAKE_BUILD_TYPE}")

include(GNUInstallDirs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")


set(CMAKE_CXX_STANDARD 14)
set(OpenGL_GL_PREFERENCE "GLVND")

find_package(OpenGL REQUIRED)

list(APPEND qt_modules
	Core
	Gui
	Quick
)
find_package(Qt5 COMPONENTS ${qt_modules} REQUIRED)

foreach(module ${qt_modules})
	list(APPEND qt_libs "Qt5::${module}")
endforeach()


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(include/)

file(GLOB header_moc_list "include/render/*.h")
list(APPEND header_moc_list "include/physics/PhysicsEngine.h")

list(APPEND source_render
	src/render/Camera.cpp
	src/render/ObjectData.cpp
	src/render/Renderer.cpp
	src/render/Render.cpp
	src/render/Scene.cpp
	src/render/Shader.cpp
	src/render/VertexArray.cpp
	src/render/VertexBuffer.cpp
	src/render/Cursor.cpp

	glad/glad.c
	glad/glad.h
	glad/khrplatform.h
)

list(APPEND source_physics
	src/physics/Functions.cpp
	src/physics/PhysicsEngine.cpp
	src/physics/Polyhedron.cpp
	src/physics/RigidBody.cpp
	src/physics/World.cpp
)

list(APPEND resources
	qml/qmldocuments.qrc
	res/resources.qrc
)

add_executable(${PROJECT_NAME}
	src/main.cpp
	${source_physics}
	${source_render}
	${header_moc_list}
	${resources}
)

target_link_libraries(${PROJECT_NAME} PUBLIC ${qt_libs})

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_link_libraries(${PROJECT_NAME} PUBLIC GL)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_link_libraries(${PROJECT_NAME} PUBLIC opengl32)
endif()

if (CMAKE_COMPILER_IS_GNUCXX)
	target_link_libraries(${PROJECT_NAME} PUBLIC dl)
endif()

set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGING_INSTALL_PREFIX "/src")
set(CPACK_SOURCE_GENERATOR "ZIP")
list(APPEND CPACK_SOURCE_IGNORE_FILES
	${CMAKE_BINARY_DIR}
	CMakeLists.txt.user
	.git/
	.gitignore
	.vs/
	x64/
	.kdev4/
	.kdev4
)

include(CPack)
