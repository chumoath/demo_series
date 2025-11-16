#include <pybind11/pybind11.h>
#include "init.hpp"
#include "math_utils.hpp"

namespace example {

namespace py = pybind11;

void
pybind_init_math(py::module_ &m_native)
{
    py::module_ m_math = m_native.def_submodule("math");

    py::class_<MathUtils>(m_math, "MathUtils")
        .def(py::init<double>(), py::arg("value") = 0)
        .def("getValue", &MathUtils::getValue)
        .def("add", &MathUtils::add, py::arg("x"))
        .def_static("distance", &MathUtils::distance, py::arg("x1"), py::arg("y1"), py::arg("x2"), py::arg("y2"))
        .def_static("print_hello", &MathUtils::print_hello)
        ;
}

} // namespace example