#ifndef X86_64_INSTRUCTION_HXX
#define X86_64_INSTRUCTION_HXX

#include "std_extention.hxx"
#include "segment.hxx"
#include <cpuid.h>

namespace krn
{
    inline static constexpr void //
    hlt()
    {
        asm("hlt");
    }

    inline static constexpr void //
    hcf [[noreturn]] ()
    {
        while (true)
        {
            hlt();
        }
    }

    inline static constexpr void //
    lidt(idtr_t idtr)
    {
        asm volatile("lidt %0" ::"m"(idtr));
    }

    inline static constexpr void //
    ltr(seg_selector_t selector)
    {
        asm volatile("ltr %0" ::"r"(selector));
    }

    inline static constexpr void //
    sti()
    {
        asm volatile("sti");
    }

    template <typename T>
        requires std::unsigned_integral<T> && //
                 (sizeof(T) <= sizeof(u32))
    inline static constexpr void //
    out(u16 port, T val)
    {
        asm volatile("out %0,%1" : : "a"(val), "d"(port) : "memory");
    }

    template <typename T>
        requires std::unsigned_integral<T> && //
                 (sizeof(T) <= sizeof(u32))
    inline static constexpr T //
    in [[nodiscard]] (u16 port)
    {
        T val;
        asm volatile("in %1,%0" : "=a"(val) : "d"(port) : "memory");
        return val;
    }

    struct cpuid_ret_t
    {
        u32 eax_ = 0;
        u32 ebx_ = 0;
        u32 ecx_ = 0;
        u32 edx_ = 0;
    };

    inline static constexpr cpuid_ret_t //
    cpuid(u32 leaf)
    {
        cpuid_ret_t ret = {};
        __get_cpuid(leaf, &ret.eax_, &ret.ebx_, &ret.ecx_, &ret.edx_);
        return ret;
    }

    struct msr_t
    {
        u32 low_ = 0;
        u32 high_ = 0;
    };

    inline static constexpr msr_t //
    read_msr(u32 msr)
    {
        msr_t ret = {};
        asm volatile("rdmsr" : "=a"(ret.low_), "=d"(ret.low_) : "c"(msr));
        return ret;
    }

    inline static constexpr void //
    write_msr(uint32_t msr, msr_t data)
    {
        asm volatile("wrmsr" : : "a"(data.low_), "d"(data.high_), "c"(msr));
    }
} // namespace krn

#endif // X86_64_INSTRUCTION_HXX
