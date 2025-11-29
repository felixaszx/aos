#include "std_extention.hxx"

#include <limine.h>

namespace limine
{
    namespace
    {
        extern "C" __attribute__((used, section(".limine_requests_start"))) //
        volatile u64 limine_requests_start_marker[] = LIMINE_REQUESTS_START_MARKER;
    };

    extern "C"
    {
        __attribute__((used, section(".limine_requests"))) //
        volatile u64 limine_base_revision[] = LIMINE_BASE_REVISION(4);

        __attribute__((used,
                       section(".limine_requests")))    //
        volatile limine_framebuffer_request framebuffer //
            = {.id = LIMINE_FRAMEBUFFER_REQUEST_ID,     //
               .revision = 0,
               .response = nullptr};

        __attribute__((used, section(".limine_requests"))) //
        volatile limine_memmap_request mem_map             //
            = {.id = LIMINE_MEMMAP_REQUEST_ID,             //
               .revision = 0,
               .response = nullptr};

        __attribute__((used, section(".limine_requests"))) //
        volatile limine_rsdp_request rsdp                  //
            = {.id = LIMINE_RSDP_REQUEST_ID,               //
               .revision = 0,
               .response = nullptr};

        __attribute__((used, section(".limine_requests"))) //
        volatile limine_hhdm_request hhdm                  //
            = {.id = LIMINE_HHDM_REQUEST_ID,               //
               .revision = 0,
               .response = nullptr};

        __attribute__((used, section(".limine_requests")))   //
        volatile limine_executable_address_request exec_addr //
            = {.id = LIMINE_EXECUTABLE_ADDRESS_REQUEST_ID,   //
               .revision = 0,
               .response = nullptr};

        __attribute__((used, section(".limine_requests"))) //
        volatile limine_stack_size_request stack_size      //
            = {.id = LIMINE_STACK_SIZE_REQUEST_ID,         //
               .revision = 0,
               .response = nullptr,
               .stack_size = 8 * 1024 * 1024};

        __attribute__((used, section(".limine_requests"))) //
        volatile limine_paging_mode_request paging_mode    //
            = {.id = LIMINE_PAGING_MODE_REQUEST_ID,        //
               .revision = 0,
               .response = nullptr,
               .mode = LIMINE_PAGING_MODE_X86_64_5LVL,
               .max_mode = LIMINE_PAGING_MODE_X86_64_5LVL,
               .min_mode = LIMINE_PAGING_MODE_X86_64_MIN};

        __attribute__((used, section(".limine_requests"))) //
        volatile limine_executable_file_request exec_file  //
            = {.id = LIMINE_EXECUTABLE_FILE_REQUEST_ID,    //
               .revision = 0,
               .response = nullptr};
    }

    namespace
    {
        extern "C" __attribute__((used, section(".limine_requests_end"))) //
        volatile u64 limine_requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;
    };
}; // namespace limine