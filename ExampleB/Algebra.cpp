#include <Eigen/Eigen>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <iostream>

using Vec3 = Eigen::Matrix<double, 3, 1>;
namespace py = pybind11;

Vec3 cross(const Vec3 & p1, const Vec3 & p2) {
    return p1.cross(p2);
}

py::object normalize(const py::object & p) {
    Vec3 p_eigen = py::cast<Vec3>(p);
    Vec3 n = p_eigen.normalized();
    return py::cast(n);
}

PYBIND11_MODULE(Algebra, m) {
    std::cout << "The module Algebra has been loaded !" << std::endl;

    m.def("cross", &cross, py::arg("p1"), py::arg("p2"));
    m.def("normalize", &normalize, py::arg("p"));

}