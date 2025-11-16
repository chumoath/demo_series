#include "pybind11/embed.h"
#include "init.hpp"
#include <map>
#include <string>
#include <cstdio>
#include "main.hpp"

namespace py = pybind11;

namespace example
{

pybind11::module_ *EmbeddedPyBind::mod = nullptr;

EmbeddedPyBind::EmbeddedPyBind(const char *_name,
                               void (*init_func)(py::module_ &),
                               const char *_base) :
    initFunc(init_func), name(_name), base(_base)
{
    init();
}

EmbeddedPyBind::EmbeddedPyBind(const char *_name,
                               void (*init_func)(py::module_ &)) :
    EmbeddedPyBind(_name, init_func, "")
{}

void
EmbeddedPyBind::init()
{
    // If this module is already registered, complain and stop.
    if (registered) {
        printf("Warning: %s already registered.\n", name.c_str());
        return;
    }

    auto &ready = getReady();
    auto &pending = getPending();

    // If we're not ready for this module yet, defer intialization.
    if (!mod || (!base.empty() && ready.find(base) == ready.end())) {
        pending.insert({std::string(base), this});
        return;
    }

    // We must be ready, so set this module up.
    initFunc(*mod);
    ready[name] = this;
    registered = true;

    // Find any other modules that were waiting for this one and init them.
    initPending(name);
}

void
EmbeddedPyBind::initPending(const std::string &finished)
{
    auto &pending = getPending();

    auto range = pending.equal_range(finished);
    std::list<std::pair<std::string, EmbeddedPyBind *>> todo(
        range.first, range.second);
    pending.erase(range.first, range.second);

    for (auto &entry: todo)
        entry.second->init();
}

std::map<std::string, EmbeddedPyBind *> &
EmbeddedPyBind::getReady()
{
    static std::map<std::string, EmbeddedPyBind *> ready;
    return ready;
}

std::multimap<std::string, EmbeddedPyBind *> &
EmbeddedPyBind::getPending()
{
    static std::multimap<std::string, EmbeddedPyBind *> pending;
    return pending;
}

void
EmbeddedPyBind::initAll(py::module_ &_example)
{
    pybind_init_math(_example);

    mod = &_example;

    // Init all the modules that were waiting on the _example module itself.
    initPending("");
}

EXAMPLE_PYBIND_MODULE_INIT(_example, EmbeddedPyBind::initAll)

}
