cmake_minimum_required(VERSION 3.16)
project(SFML_Project_test LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
#=== SFML ===
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)

#=== IMGUI ===
FetchContent_Declare(imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui
        GIT_TAG 35b1148efb839381b84de9290d9caf0b66ad7d03 # 1.82
)
set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)

FetchContent_MakeAvailable(SFML imgui)

# ImGui-SFML
FetchContent_Declare(imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml
        GIT_TAG 82dc2033e51b8323857c3ae1cf1f458b3a933c35 # 2.3
)

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)

FetchContent_MakeAvailable(imgui-sfml)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE sfml-graphics)
target_link_libraries(main PRIVATE ImGui-SFML::ImGui-SFML)
target_compile_features(main PRIVATE cxx_std_17)

set(RESOURCE_DIR ${CMAKE_SOURCE_DIR}/resources)

add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${RESOURCE_DIR} $<TARGET_FILE_DIR:main>/resources
        COMMENT "Copying resources folder"
)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
    # Copy DLLs needed for runtime on Windows
    if (BUILD_SHARED_LIBS)
        add_custom_command(TARGET example_exe POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
                $<TARGET_FILE:sfml-graphics>
                $<TARGET_FILE:sfml-window>
                $<TARGET_FILE:sfml-system>
                $<TARGET_FILE_DIR:example_exe>)
    endif()
endif()

message(STATUS "SFML_SOURCE_DIR: ${SFML_SOURCE_DIR}")
