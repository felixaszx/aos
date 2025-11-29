#include "kernel/kernel.hxx"
#include "instructions.hxx"

// Segmentation is oudated, This GDT is only a place holder for paging
#include "segment.hxx"

namespace krn
{
    gdt_t gdt = {};
    gdtr_t gdtr = {};
    tss_t tss = {};
    idt_t idt = {};
    idtr_t idtr = {};

    void //
    init_idt_and_segment();
} // namespace krn

// paging
#include "paging.hxx"

namespace krn
{
    phy_mem_mgr pmm = {};
    vmm krn_vmm = {};

    void //
    init_kmm();
} // namespace krn

#include "limine.h"
#include "flanterm_backends/fb.h"

namespace limine
{
    extern "C"
    {
        extern volatile limine_framebuffer_request framebuffer;
    };
}; // namespace limine

flanterm_context* ft_ctx = nullptr;

void //
krn::krn::init0()
{
    limine_framebuffer* framebuffer = limine::framebuffer.response->framebuffers[0];
    ft_ctx = flanterm_fb_init(nullptr, nullptr, castr(u32*, framebuffer->address), framebuffer->width,
                              framebuffer->height, framebuffer->pitch, framebuffer->red_mask_size,
                              framebuffer->red_mask_shift, framebuffer->green_mask_size, framebuffer->green_mask_shift,
                              framebuffer->blue_mask_size, framebuffer->blue_mask_shift, nullptr, nullptr, nullptr,
                              nullptr, nullptr, nullptr, nullptr, nullptr, 0, 0, 1, 0, 0, 0);
    init_idt_and_segment();
    init_kmm();
}
