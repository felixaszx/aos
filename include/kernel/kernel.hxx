#ifndef KERNEL_KERNEL_HXX
#define KERNEL_KERNEL_HXX

#include "std_extention.hxx"

namespace krn
{
    // kernel virtual memory manager
    struct kvmm
    {
    };

    struct krn
    {
        kvmm kvmm_ = {};

        void //
        init0();
    };

}; // namespace krn

#endif // KERNEL_KERNEL_HXX
