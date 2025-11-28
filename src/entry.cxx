#include "std_extention.hxx"

#include <instructions.hxx>
#include <kernel/kernel.hxx>

extern "C" void //
_kernel_entry()
{
    krn::krn kernel;
    kernel.init0();
    while (true)
    {
    }
}