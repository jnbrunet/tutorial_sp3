#include <pybind11/pybind11.h>
#include <iostream>
#include <SofaAwesome/AwesomeCamera.h>
#include <SofaPython3/Sofa/Core/Binding_Base.h>

class PyAwesomeCamera : public AwesomeCamera {
    using AwesomeCamera::AwesomeCamera;

    std::string parse_file_path(std::string filepath) const override {
        pybind11::gil_scoped_acquire g;
        PYBIND11_OVERLOAD(std::string, AwesomeCamera, parse_file_path, filepath);
    }
};

PYBIND11_MODULE(SofaAwesome, m) {
    pybind11::class_<
            AwesomeCamera,
            sofa::component::visualmodel::BaseCamera,
            PyAwesomeCamera,
            sofapython3::py_shared_ptr<AwesomeCamera>> awesome_camera(m, "AwesomeCamera");
    awesome_camera.def(pybind11::init());
    awesome_camera.def("save_frame", &AwesomeCamera::save_frame, pybind11::arg("filepath"));
    awesome_camera.def("parse_file_path", &AwesomeCamera::parse_file_path, pybind11::arg("filepath"));
}
