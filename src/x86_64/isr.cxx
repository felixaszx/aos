
#include "kernel/kernel.hxx"
#include "instructions.hxx"
#include "isr.hxx"

#include "limine.h"
#include "flanterm_backends/fb.h"

extern flanterm_context* ft_ctx;

extern "C" krn::isr_state_t* //
interrupt_disaptch(krn::isr_state_t* ctx)
{
    switch (casts(krn::isr_state_t::vtx_t, ctx->vtx_))
    {
        case krn::isr_state_t::DE:
        {
            const char msg[] = "DE\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::DB:
        {
            const char msg[] = "DB\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::NMI:
        {
            const char msg[] = "NMI\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::BP:
        {
            const char msg[] = "BP\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::OF:
        {
            const char msg[] = "OF\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::BR:
        {
            const char msg[] = "BR\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::UD:
        {
            const char msg[] = "UD\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::NM:
        {
            const char msg[] = "NM\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::DF:
        {
            const char msg[] = "DF\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::TS:
        {
            const char msg[] = "TS\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::NP:
        {
            const char msg[] = "NP\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::SS:
        {
            const char msg[] = "SS\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::GP:
        {
            const char msg[] = "GP\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::PF:
        {
            const char msg[] = "PF\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::MF:
        {
            const char msg[] = "MF\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::AC:
        {
            const char msg[] = "AC\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::MC:
        {
            const char msg[] = "MC\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::XM:
        {
            const char msg[] = "XM\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::VE:
        {
            const char msg[] = "VE\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::CP:
        {
            const char msg[] = "CP\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
        case krn::isr_state_t::rsvd0:
        case krn::isr_state_t::rsvd1:
        case krn::isr_state_t::rsvd2:
        case krn::isr_state_t::external_vtx:
        case krn::isr_state_t::last_vtx:
        {
            const char msg[] = "Not Handled Exception\n";
            flanterm_write(ft_ctx, msg, sizeof(msg));
            break;
        }
    }

    return ctx;
}