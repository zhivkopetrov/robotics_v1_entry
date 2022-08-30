cmake_minimum_required(VERSION 3.16.3)

project(red-eye LANGUAGES CXX)

###   CMake Compilation Options   ###
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

###   Variables   ###
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(INC_DIR ${ROOT_DIR}/include)
set(SRC_DIR ${ROOT_DIR}/src)

###   Global Compilation Options   ###
include_directories(${INC_DIR})


###   Targets   ###

##  Utils  ##
add_library(
    utils STATIC
        ${INC_DIR}/utils/CommonDefines.h
        ${INC_DIR}/utils/EyePatterns.h
        ${INC_DIR}/utils/FileParser.h
        ${INC_DIR}/utils/FunctionTracer.h
        ${INC_DIR}/utils/Image.h
        ${INC_DIR}/utils/SolutionEvaluator.h

        ${SRC_DIR}/utils/Image.cpp
)

target_include_directories(
    utils PRIVATE
        ${INC_DIR}/utils
)

##  Executable  ##
add_executable(
    ${PROJECT_NAME}
        ${INC_DIR}/Solution.h

        ${SRC_DIR}/main.cpp
)

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
        utils
)
