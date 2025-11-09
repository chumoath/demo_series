#include <pybind11/pybind11.h>
#include "math_utils.hpp"

namespace py = pybind11;

// `math_utils` 是 Python 中导入的模块名。
// `m` 是表示模块的变量，用于创建绑定。
PYBIND11_MODULE(math_utils, m) {
    m.doc() = "A simple math utilities module implemented in C++"; // 模块文档

    // 将 MathUtils 类暴露给 Python
    py::class_<MathUtils>(m, "MathUtils")
        .def(py::init<double>()) // 暴露构造函数，对应 Python 中的 __init__
        .def("get_value", &MathUtils::getValue) // 暴露成员函数
        .def("add", &MathUtils::add)
        .def_static("distance", &MathUtils::distance); // 暴露静态函数，Python 中可通过类名直接调用

    // 你也可以暴露独立的函数（假设我们有一个）
    // m.def("some_standalone_function", &someFunction, "A free function");
}