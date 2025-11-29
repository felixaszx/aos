#include "kernel/kernel.hxx"
#include "instructions.hxx"

// paging
#include "paging.hxx"
#include "limine.h"
#include "printf.h"

namespace limine
{
    extern "C"
    {
        extern volatile limine_executable_file_request exec_file;
        extern volatile limine_executable_address_request exec_addr;
        extern volatile limine_framebuffer_request framebuffer;
        extern volatile limine_hhdm_request hhdm;
        extern volatile limine_memmap_request mem_map;
    };
}; // namespace limine
extern u32 end_of_krn;

void //
krn::phy_mem_mgr::init()
{
    limine_memmap_response* mem_map_res = limine::mem_map.response;
    for (usz i = 0; i < mem_map_res->entry_count; i++)
    {
        const limine_memmap_entry* ent = mem_map_res->entries[i];
        const char* type_name = nullptr;
        switch (ent->type)
        {
            case LIMINE_MEMMAP_USABLE:
            {
                type_name = "USABLE";
                break;
            }
            case LIMINE_MEMMAP_RESERVED:
            {
                type_name = "RESERVED";
                break;
            }
            case LIMINE_MEMMAP_ACPI_RECLAIMABLE:
            {
                type_name = "ACPI_RECLAIMABLE";
                break;
            }
            case LIMINE_MEMMAP_ACPI_NVS:
            {
                type_name = "ACPI_NVS";
                break;
            }
            case LIMINE_MEMMAP_BAD_MEMORY:
            {
                type_name = "BAD_MEMORY";
                break;
            }
            case LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE:
            {
                type_name = "BOOTLOADER_RECLAIMABLE";
                break;
            }
            case LIMINE_MEMMAP_EXECUTABLE_AND_MODULES:
            {
                type_name = "EXECUTABLE_AND_MODULES";
                break;
            }
            case LIMINE_MEMMAP_FRAMEBUFFER:
            {
                type_name = "FRAMEBUFFER";
                break;
            }
            case LIMINE_MEMMAP_ACPI_TABLES:
            {
                type_name = "ACPI_TABLES";
                break;
            }
        }

        if (type_name != nullptr)
        {
            u64 end = ent->base + ent->length;
            printf("%22s base: 0x%llx (%zu) length: 0x%llx (%zu) end: 0x%llx (%zu)\n", //
                   type_name, ent->base, ent->base, ent->length, ent->length, end, end);
        }
    }
}

void //
krn::vmm::init()
{
}

