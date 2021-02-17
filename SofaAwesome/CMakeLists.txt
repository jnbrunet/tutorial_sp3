cmake_minimum_required(VERSION 3.12)
project(SofaAwesome VERSION 20.12 LANGUAGES CXX)

# Detect if this is a subproject of SOFA
if ("${CMAKE_PROJECT_NAME}" STREQUAL "Sofa")
    set(COMPILED_AS_SOFA_SUBPROJECT 1)
    message(STATUS "${PROJECT_NAME} is compiled as a subproject to SOFA.")
else()
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif ()

find_package(SofaFramework REQUIRED) # Dependency to SofaCore and SofaSimulationCore targets
find_package(SofaBase REQUIRED) # Dependency to SofaBaseVisual target

set(SOURCE_FILES
    src/${PROJECT_NAME}/initSofaAwesome.cpp
    src/${PROJECT_NAME}/AwesomeCamera.cpp
)

set(HEADER_FILES
    src/${PROJECT_NAME}/AwesomeCamera.h
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PUBLIC SofaCore SofaBaseVisual SofaSimulationCore)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Create package Config, Version & Target files.
sofa_create_package_with_targets(
    PACKAGE_NAME ${PROJECT_NAME}
    PACKAGE_VERSION ${PROJECT_VERSION}
    TARGETS ${PROJECT_NAME} AUTO_SET_TARGET_PROPERTIES
    INCLUDE_SOURCE_DIR "src"
    INCLUDE_INSTALL_DIR ${PROJECT_NAME}
    EXAMPLE_INSTALL_DIR "share/examples"
    RELOCATABLE "plugins"
)

find_package(pybind11 QUIET) # This is needed to get the latest installed version of python
find_package(SofaPython3 QUIET)
if (SofaPython3_FOUND)
    add_subdirectory(bindings)
endif()