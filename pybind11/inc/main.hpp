#pragma once

namespace example {
    struct PybindModuleInit
    {
        PybindModuleInit(const char *name, PyObject *(*func)())
        {
            if (Py_IsInitialized()) {
                // If python is running, initialize and inject the module.
                PyImport_AddModule(name);
                PyObject *sys_modules = PyImport_GetModuleDict();
                PyDict_SetItemString(sys_modules, name, func());
            } else {
                // If not, tell python how to build importer itself later.
                PyImport_AppendInittab(name, func);
            }
        }
    };
}


#define EXAMPLE_PYBIND_MODULE_INIT(name, func) \
namespace { \
 \
::PyObject * \
initializer() \
{ \
    static ::pybind11::module_::module_def mod_def; \
    static auto m = ::pybind11::module_::create_extension_module( \
            #name, nullptr, &mod_def); \
    func(m); \
    m.inc_ref(); \
    return m.ptr(); \
} \
 \
::example::PybindModuleInit modInit(#name, initializer); \
 \
} // anonymous namespace
