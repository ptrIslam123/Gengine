cmake_minimum_required(VERSION 3.18)

project(Gengine)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(BUILD_EXAMPLES "Build the examples" ON)
option(BUILD_TOOLS "Build the tools" ON)
option(BUILD_TESTS "Build the tests" ON)
option(ENABLE_TSAN "Build with TSAN" OFF)
option(ENABLE_ASAN "Build with ASAN" OFF)

if(ENABLE_TSAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -g") # enable thread sanitize
endif()

if(ENABLE_ASAN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g") # enable address sanitize
endif()

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)

add_subdirectory(external/glad)
add_subdirectory(external/glm)
add_subdirectory(atom)

set(CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(LIB_NAME ${PROJECT_NAME}_core)
set(LIB_DIRS ${CURRENT_SOURCE_DIR} ${CURRENT_SOURCE_DIR}/external ${CURRENT_SOURCE_DIR}/include)
message(STATUS "CIENGINE_DIRS=${LIB_DIRS}")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_INCLUDE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/include")

file(GLOB_RECURSE HDRS "${CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE SRCS "${CURRENT_SOURCE_DIR}/src/*.cpp")

set(LIB_HDRS
${HDRS}
)

set(LIB_SRCS
${SRCS}
)

message(STATUS "LIB_INSTALL_DIR=${CMAKE_BINARY_DIR}/lib")

if(BUILD_SHARED_LIBS)
    message(STATUS "BUILD_TYPE=DYNAMIC_LIBRARY")

    add_library(${LIB_NAME} SHARED ${LIB_HDRS} ${LIB_SRCS})
else()
    message(STATUS "BUILD_TYPE=STATIC_LIBRARY")

    add_library(${LIB_NAME} STATIC ${LIB_HDRS} ${LIB_SRCS})
endif()

target_include_directories(${LIB_NAME} PUBLIC ${LIB_DIRS} glad glm)

# dependencies
target_link_libraries(${LIB_NAME} PUBLIC glad glm atom)

set_target_properties(${LIB_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

file(MAKE_DIRECTORY ${CMAKE_INCLUDE_OUTPUT_DIRECTORY})

add_custom_command(
    TARGET ${LIB_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/include" ${CMAKE_INCLUDE_OUTPUT_DIRECTORY}
)

function(target_builder TARGET_NAME SRCS HDRS HDRS_DIR LIBS LIBS_DIR OUTPUT_DIR)
    add_executable(${TARGET_NAME} ${SRCS} ${HDRS})

    target_include_directories(${TARGET_NAME} PUBLIC ${HDRS_DIR} ${CURRENT_SOURCE_DIR} ${CURRENT_SOURCE_DIR}/include ${CURRENT_SOURCE_DIR}/eternal)

    target_link_directories(${TARGET_NAME} PUBLIC ${LIBS_DIR})

    target_link_libraries(${TARGET_NAME} PUBLIC ${LIBS})

    set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${OUTPUT_DIR}")
endfunction(target_builder)

#******************************************************* Build example dir *******************************************************#
if(BUILD_EXAMPLES)
    message(STATUS "BUILD_EXAMPLES=ON")

    target_builder("triangles" "examples/triangles.cpp" "" "" "${PROJECT_NAME};SDL2::SDL2;glad" "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}" "examples")
endif()
