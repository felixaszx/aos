#ifndef X86_64_ISR_HXX
#define X86_64_ISR_HXX

#include "instructions.hxx"

namespace krn
{
    extern "C" struct isr_state_t
    {
        enum vtx_t : u8
        {
            DE = 0,
            DB,
            NMI,
            BP,
            OF,
            BR,
            UD,
            NM,
            DF,
            rsvd0 = 9,
            TS,
            NP,
            SS,
            GP,
            PF,
            rsvd1 = 15,
            MF,
            AC,
            MC,
            XM,
            VE,
            CP,
            rsvd2 = 22,
            rsvd2_end = 32,
            external_vtx = rsvd2_end,
            last_vtx = 255
        };

        u64 r15_ = 0;
        u64 r14_ = 0;
        u64 rbx_ = 0;
        u64 rax_ = 0;

        u64 vtx_ = 0;
        u64 error_ = 0;

        u64 iret_rip_ = 0;
        u64 iret_cs_ = 0;
        u64 iret_flags_ = 0;
        u64 iret_rsp_ = 0;
        u64 iret_ss_ = 0;
    };
}; // namespace krn

#endif // X86_64_ISR_HXX
