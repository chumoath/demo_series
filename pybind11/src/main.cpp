#include <Python.h>

#include <iostream>
#include "pybind11/embed.h"
#include "pybind11/pybind11.h"

namespace py = pybind11;

// main() is now pretty stripped down and just sets up python and then
// calls EmbeddedPython::initAll which loads the various embedded python
// modules into the python environment and then starts things running by
// running python's m5.main().
int
main(int argc, const char **argv)
{
    py::scoped_interpreter guard;

    // Embedded python doesn't set up sys.argv, so we'll do that ourselves.
    py::list py_argv;
    auto sys = py::module::import("sys");
    if (py::hasattr(sys, "argv")) {
        // sys.argv already exists, so grab that.
        py_argv = sys.attr("argv");
    } else {
        // sys.argv doesn't exist, so create it.
        sys.add_object("argv", py_argv);
    }

    if (argc < 2) {
        std::cerr << "Usage: testpy SCRIPT [arg] ..." << std::endl;
        std::exit(1);
    }

    py::module_::import("_example").attr("math").attr("MathUtils").attr("print_hello")();

    // Fill it with our argvs.
    for (int i = 1; i < argc; i++)
        py_argv.append(argv[i]);

    // Actually call the script.
    py::eval_file(argv[1]);

    return 0;
}
