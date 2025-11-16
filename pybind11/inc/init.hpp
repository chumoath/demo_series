#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <list>
#include <map>
#include <string>

namespace example
{

class EmbeddedPyBind
{
  public:
    EmbeddedPyBind(const char *_name,
                   void (*init_func)(pybind11::module_ &),
                   const char *_base);

    EmbeddedPyBind(const char *_name,
                   void (*init_func)(pybind11::module_ &));

    static void initAll(pybind11::module_ &_m5);

  private:
    void (*initFunc)(pybind11::module_ &);

    void init();

    bool registered = false;
    const std::string name;
    const std::string base;

    // The _m5 module.
    static pybind11::module_ *mod;

    // A map from initialized module names to their descriptors.
    static std::map<std::string, EmbeddedPyBind *> &getReady();
    // A map to pending modules from the name of what they're waiting on.
    static std::multimap<std::string, EmbeddedPyBind *> &getPending();

    // Initialize all modules waiting on "finished".
    static void initPending(const std::string &finished);
};

void pybind_init_math(pybind11::module_ &m_native);

} // namespace example
