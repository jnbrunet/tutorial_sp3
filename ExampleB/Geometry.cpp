#include <Eigen/Eigen>
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include <iostream>

using Vec3 = Eigen::Matrix<double, 3, 1>;
namespace py = pybind11;

struct Triangle {

    Triangle(const Vec3 & p1, const Vec3 & p2, const Vec3 & p3)
    : p_p1(p1), p_p2(p2), p_p3(p3)
    {}

    Vec3 normal () const {
        Vec3 e1  = p_p2 - p_p1;
        Vec3 e2  = p_p3 - p_p1;
        Vec3 res = e1.cross(e2);
        return res.normalized();
    }

private:
    Vec3 p_p1, p_p2, p_p3;
};

PYBIND11_MODULE(Geometry, m) {
    std::cout << "The module Geometry has been loaded !" << std::endl;

    py::class_<Triangle> t(m, "Triangle");
    t.def(py::init<const Vec3 &, const Vec3 &, const Vec3 &>());
    t.def("normal", &Triangle::normal);

}