cmake_minimum_required(VERSION 3.15)

project(Snake)

set(SRC_FILES
    src/Snake.hpp
    src/Snake.cpp
    src/main.cpp
)

add_subdirectory(external/SFML)

if(NOT TARGET sfml-graphics)
	message(FATAL_ERROR "sfml-graphics is required!")
elseif(NOT TARGET sfml-main AND WIN32)
	message(FATAL_ERROR "sfml-main is required!")
elseif(NOT TARGET sfml-system)
	message(FATAL_ERROR "sfml-system is required!")
elseif(NOT TARGET sfml-window)
	message(FATAL_ERROR "sfml-window is required!")
endif()

if(NOT BUILD_SHARED_LIBS)
	add_compile_definitions(SFML_STATIC)
endif()
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(${PROJECT_NAME} ${SRC_FILES})
else()
    add_executable(${PROJECT_NAME} WIN32 ${SRC_FILES})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE "external/SFML/include")

target_link_libraries(${PROJECT_NAME} PRIVATE "sfml-graphics;sfml-system;sfml-window")

if(WIN32)
    target_link_libraries(${PROJECT_NAME} "sfml-main")
endif()

set_target_properties( ${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)
