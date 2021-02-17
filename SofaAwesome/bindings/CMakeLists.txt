cmake_minimum_required(VERSION 3.12)
project(SofaAwesomeBindings VERSION 20.12 LANGUAGES CXX)

set(HEADER_FILES
    )

set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/SofaAwesome.cpp
    )

if (NOT TARGET SofaPython3::Plugin)
    find_package(SofaPython3 REQUIRED)
endif()

SP3_add_python_module (
    TARGET       ${PROJECT_NAME}
    PACKAGE      SofaAwesome
    MODULE       SofaAwesome
    #    DESTINATION  Awesome
    SOURCES      ${SOURCE_FILES}
    HEADERS      ${HEADER_FILES}
    DEPENDS      SofaAwesome SofaPython3::Bindings
)

#SP3_add_python_package (
#    SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/package
#    TARGET_DIRECTORY Awesome
#)

message(STATUS "Python:
    Version: ${Python_VERSION}
    Executable: ${Python_EXECUTABLE}
    Headers: ${Python_INCLUDE_DIRS}
    Libraries: ${Python_LIBRARIES}"
        )
message(STATUS "pybind11:
    Version: ${pybind11_VERSION}
    Config: ${pybind11_CONFIG}"
        )