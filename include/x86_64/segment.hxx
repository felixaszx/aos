#ifndef X86_64_SEGMENT_HXX
#define X86_64_SEGMENT_HXX

#include "std_extention.hxx"

namespace krn
{
    extern "C" struct seg_desc_t
    {
        struct flags
        {
            inline static const u8 invalid = 0;
            enum : u8
            {
                long_mode = 0b10, // L
                size = 0b100,     // DB
                paging = 0b1000   // G
            };
        };

        struct access
        {
            inline static const u8 invalid = 0;
            enum : u8
            {
                rw = 1 << 1,         // RW
                dc = 1 << 2,         // DC
                executable = 1 << 3, // E
                code_data = 1 << 4,  // S
                ring_0 = 0 << 5,    // DPL 0
                ring_1 = 1 << 5,    // DPL 1
                ring_2 = 2 << 5,    // DPL 2
                ring_3 = 3 << 5,    // DPL 3
                present = 1 << 7,

                // system selector flags
                ldt = 0x2,
                tss64_avl = 0x9,
                tss64_busy = 0xb,
            };
        };

      protected:
        u16 limit0_ = 0;
        u16 base0_ = 0;
        u8 base1_ = 0;

      public:
        u8 access_ = access::invalid;

      protected:
        u8 limit1_ : 4 = 0;

      public:
        u8 flags_ : 4 = flags::invalid;

      protected:
        u8 base2_ = 0;

      public:
        inline constexpr auto& //
        limit(u32 new_limit)
        {
            limit0_ = (new_limit & 0xffff);
            limit1_ = (new_limit >> 16);
            return *this;
        }

        inline constexpr auto& //
        base(u32 new_base)
        {
            base0_ = (new_base & 0xffff);
            base1_ = ((new_base >> 16) & 0xff);
            base2_ = ((new_base >> 24) & 0xff);
            return *this;
        }

        inline constexpr auto& //
        flags(u8 new_flags)
        {
            flags_ = new_flags;
            return *this;
        }

        inline constexpr auto& //
        access(u8 acc)
        {
            access_ = acc;
            return *this;
        }

    } __attribute__((packed));

    extern "C" struct sys_seg_desc_t : public seg_desc_t
    {
      protected:
        u32 base3_ = 0;
        u32 rsvd_ = 0;

      public:
        inline constexpr auto& //
        base(u64 new_base)
        {
            seg_desc_t::base(new_base);
            base3_ = (new_base >> 32);
            return *this;
        }

        inline constexpr void //
        write_to_gdt(seg_desc_t entries[2])
        {
            auto dst = castr(std::byte*, entries);
            auto src = castr(std::byte*, this);
            for (usz i = 0; i < sizeof(seg_desc_t) * 2; i++)
            {
                dst[i] = src[i];
            }
        }

    } __attribute__((packed));

    extern "C" struct seg_selector_t
    {
        u16 rpl_ : 2 = 0;
        u16 ti_ : 1 = 0;
        u16 idx_ : 13 = 0;

        inline constexpr auto& //
        request_level(u8 ring)
        {
            rpl_ = ring;
            return *this;
        }

        inline constexpr auto& //
        use_ldt()
        {
            ti_ = 1;
            return *this;
        }

        inline constexpr auto& //
        index(u16 idx)
        {
            idx_ = idx;
            return *this;
        }
    } __attribute__((packed));

    using gdt_t __attribute__((aligned(16_b))) = seg_desc_t[7];

    struct gdtr_t
    {
        u16 size_ = 0;
        seg_desc_t* base_ = 0;
    } __attribute__((packed));

    struct tss_t
    {
      protected:
        u32 rsvd0_ = 0;

      public:
        u64 rsp_[3] = {};

      protected:
        u64 rsvd1_ = 0;

      public:
        u64 ist_[7] = {}; // starting at ist1

      protected:
        u64 rsvd2_ = 0;
        u16 rsvd3_ = 0;

      public:
        u16 iopb_ = sizeof(tss_t);
    } __attribute__((packed));

    struct gate_desc_t
    {
      protected:
        u16 off0_ = 0;

      public:
        seg_selector_t seg_selector_ = {};
        u8 ist_ : 3 = 0;

      protected:
        u8 rsvd0_ : 5 = 0;

      public:
        u8 type_ : 4 = 0;

      protected:
        u8 rsvd1_ : 1 = 0;

      public:
        u8 dpl_ : 2 = 0;
        u8 present_ : 1 = 1;

      protected:
        u16 off1_ = 0;
        u32 off2_ = 0;
        u32 rsvd2_ = 0;

      public:
        inline constexpr auto& //
        isr(u64 ptr)
        {
            off0_ = (ptr & 0xffff);
            off1_ = ((ptr >> 16) & 0xffff);
            off2_ = ((ptr >> 32) & 0xffffffff);
            return *this;
        }

        inline constexpr auto& //
        seg_selector(seg_selector_t selector)
        {
            seg_selector_ = selector;
            return *this;
        }

        inline constexpr auto& //
        ist(u8 off)
        {
            ist_ = off;
            return *this;
        }

        inline constexpr auto& //
        set_trap64()
        {
            type_ = 0xf;
            return *this;
        }

        inline constexpr auto& //
        set_intr64()
        {
            type_ = 0xe;
            return *this;
        }

        inline constexpr auto& //
        dpl(u8 ring)
        {
            dpl_ = ring;
            return *this;
        }

        inline constexpr auto& //
        set_present()
        {
            present_ = 1;
            return *this;
        }
    } __attribute__((packed));

    inline constexpr u64 MAX_IDT_ENTRY_COUNT = 256;
    using idt_t __attribute__((aligned(16_b))) = gate_desc_t[MAX_IDT_ENTRY_COUNT];
    struct idtr_t
    {
        u16 size_ = 0;
        gate_desc_t* base_ = nullptr;
    } __attribute__((packed));

    extern "C" void //
    lgdt(const gdtr_t* gdtr, seg_selector_t code, seg_selector_t data);

    extern "C" void isr_0_handler(); // more handler defined in asm
}; // namespace krn

#endif // X86_64_SEGMENT_HXX
