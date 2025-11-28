#include "kernel/kernel.hxx"
#include "instructions.hxx"

// Segmentation is oudated, This GDT is only a place holder for paging
#include "segment.hxx"

namespace krn
{
    extern gdt_t gdt;
    extern gdtr_t gdtr;
    extern tss_t tss;
    extern idt_t idt;
    extern idtr_t idtr;

    void //
    init_idt_and_segment();

    void //
    init_kvmm();
} // namespace krn

void //
krn::init_idt_and_segment()
{
    // load gdt
    gdt[0] = {};
    for (usz g = 1; g < 5; g++)
    {
        gdt[g].access(                      //
            seg_desc_t::access::code_data | //
            seg_desc_t::access::rw |        //
            seg_desc_t::access::present);
        gdt[g].flags(seg_desc_t::flags::paging);
        gdt[g].limit(max_v);

        if (g % 2 != 0)
        {
            gdt[g].access_ |= seg_desc_t::access::executable;
            gdt[g].flags_ |= seg_desc_t::flags::long_mode;
        }

        if (g >= 3)
        {
            gdt[g].access_ |= seg_desc_t::access::ring_3;
        }
        else
        {
            gdt[g].access_ |= seg_desc_t::access::ring_0;
        }
    }
    gdtr = {.size_ = sizeof(gdt) - 1, .base_ = gdt};
    lgdt(&gdtr, seg_selector_t().index(1), seg_selector_t().index(2));

    // load tss
    sys_seg_desc_t tss_desc = {};
    tss_desc.base(castr(u64, &tss));
    tss_desc.limit(sizeof(tss) - 1);
    tss_desc.access(sys_seg_desc_t::access::ring_0 |    //
                    sys_seg_desc_t::access::tss64_avl | //
                    sys_seg_desc_t::access::present);
    tss_desc.write_to_gdt(gdt + 5);
    ltr(seg_selector_t().index(5));

    // load idt
    for (u64 i = 0; i < 32; i++)
    {
        idt[i].isr(castr(u64, isr_0_handler) + (i * 16));
        idt[i].seg_selector(seg_selector_t().index(1));
        idt[i].set_trap64();
        idt[i].dpl(0);
    }

    idtr_t idtr = {.size_ = sizeof(idt) - 1, .base_ = idt};
    lidt(idtr);
    sti();
}

void //
krn::init_kvmm()
{
    cpuid_ret_t cpu_id = cpuid(1);
    bool apic = cpu_id.edx_ & bit_APIC;
    
    if(!apic)
    {
        hcf();
    }
}