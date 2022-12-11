cmake_minimum_required(VERSION 3.8)
project(opengl-engine CXX)

# Finding source and header files
file(GLOB_RECURSE SOURCE_FILES
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp
)
file(GLOB_RECURSE HEADER_FILES
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp
)
# Providing sources to IDE
source_group(TREE ${CMAKE_SOURCE_DIR}/src)

# Configure options
set(SDL_SHARED OFF CACHE BOOL "" FORCE)

set(SDL_VIDEO ON CACHE BOOL "" FORCE)
set(SDL_EVENTS ON CACHE BOOL "" FORCE)
set(SDL_JOYSTICK ON CACHE BOOL "" FORCE)
set(SDL_THREADS ON CACHE BOOL "" FORCE)
set(SDL_LOADSO ON CACHE BOOL "" FORCE)

set(SDL_ATOMIC OFF CACHE BOOL "" FORCE)
set(SDL_AUDIO OFF CACHE BOOL "" FORCE)
set(SDL_RENDER OFF CACHE BOOL "" FORCE)
set(SDL_HAPTIC OFF CACHE BOOL "" FORCE)
set(SDL_HIDAPI OFF CACHE BOOL "" FORCE)
set(SDL_POWER OFF CACHE BOOL "" FORCE)
set(SDL_TIMERS OFF CACHE BOOL "" FORCE)
set(SDL_FILE OFF CACHE BOOL "" FORCE)
set(SDL_CPUINFO OFF CACHE BOOL "" FORCE)
set(SDL_FILESYSTEM OFF CACHE BOOL "" FORCE)
set(SDL_SENSOR OFF CACHE BOOL "" FORCE)
set(SDL_LOCALE OFF CACHE BOOL "" FORCE)
set(SDL_MISC OFF CACHE BOOL "" FORCE)

# Adding thirdparty C++ libraries
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/glm EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/SDL EXCLUDE_FROM_ALL)
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/glad EXCLUDE_FROM_ALL)

# Create output executable and configuring it
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

# Adding includes
target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/thirdparty/stb_image
		${CMAKE_SOURCE_DIR}/thirdparty/SDL/include
)

if(TARGET SDL2::SDL2main)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE
    glad
	glm::glm
	SDL2::SDL2-static
)
