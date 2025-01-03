cmake_minimum_required(VERSION 3.30)
project(untitled4)

set(CMAKE_CXX_STANDARD 20)


# raylib
find_package(raylib QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            GIT_REPOSITORY https://github.com/raysan5/raylib.git
            GIT_TAG 5.5
    )
    FetchContent_MakeAvailable(raylib)
endif ()

# raylib-cpp
find_package(raylib_cpp QUIET)
if (NOT raylib_cpp_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib_cpp
            GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
            GIT_TAG v5.5.0
    )
    FetchContent_MakeAvailable(raylib_cpp)
endif ()

# fmt
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 11.1.1
)
FetchContent_MakeAvailable(fmt)

# glm
find_package(glm QUIET)
if (NOT glm_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG 1.0.1
    )
    FetchContent_MakeAvailable(glm)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DRELEASE)
    message(STATUS "Building in Release mode")

    if (MSVC)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /GL /Gy")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /GL /Gy")
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
    else ()
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -flto -fvisibility=hidden")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -flto -fvisibility=hidden")
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -flto -s")
    endif ()

else ()
    add_definitions(-DDEBUG)
    add_definitions(-DDEBUG_EXTRA)
endif ()


add_executable(${PROJECT_NAME} main.cpp includes.h
        string.cpp
        string.h
        simpleTypes.h
        virtualFileSystem.cpp
        virtualFileSystem.h
        Spatial.cpp
        Spatial.h
        semath.cpp
        semath.h
        Components/GameObject.cpp
        Components/GameObject.h
)
target_link_libraries(${PROJECT_NAME} PUBLIC raylib raylib_cpp fmt glm)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR})

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Resources
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/Resources
)



