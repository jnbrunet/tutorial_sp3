project(ExampleB)

set(PYBIND11_PYTHON_VERSION 3.9)
find_package(pybind11 REQUIRED)
find_package(Eigen3 REQUIRED)

pybind11_add_module(Algebra SHARED Algebra.cpp)
target_link_libraries(Algebra PRIVATE Eigen3::Eigen)
set_target_properties(Algebra PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/site-packages/ExampleB")

pybind11_add_module(Geometry SHARED Geometry.cpp)
target_link_libraries(Geometry PRIVATE Eigen3::Eigen)
set_target_properties(Geometry PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/site-packages/ExampleB")
