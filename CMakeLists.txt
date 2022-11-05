cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME scene)
project(${PROJECT_NAME})


if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(MSVC)

set(RESOURCE_LIST
    res/shaders/shader.frag
    res/shaders/shader.vert)


file(GLOB_RECURSE ROOT_SOURCE src/*.cpp)
file(GLOB_RECURSE ROOT_HEADER src/*.h)

source_group("Resource Files" FILES ${RESOURCE_LIST})

add_executable(${PROJECT_NAME}
    ${RESOURCE_LIST}
    ${ROOT_SOURCE}
    ${ROOT_HEADER})

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)

add_subdirectory(external/assimp)
target_link_libraries(${PROJECT_NAME} assimp)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)


# Copy output file
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
