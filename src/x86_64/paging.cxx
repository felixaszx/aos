#include "kernel/kernel.hxx"
#include "instructions.hxx"

// paging
#include "paging.hxx"
#include "limine.h"

namespace limine
{
    extern "C"
    {
        extern volatile limine_executable_file_request exec_file;
        extern volatile limine_executable_address_request exec_addr;
        extern volatile limine_hhdm_request hhdm;
    };
}; // namespace limine
using namespace limine;

void //
krn::vmm::init()
{
    // map all used memory first
    paddr_t krn_paddr = exec_addr.response->physical_base;
    vaddr_t krn_vaddr = exec_addr.response->virtual_base;
    vaddr_t hhdm_off = hhdm.response->offset;
    int a = 0;
}

void krn::phy_mem_mgr::init()
{
}
