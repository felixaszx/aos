set(CMAKE_SYSTEM_NAME AOS)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(triple x86_64-unknown-none-elf)
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET ${triple})
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_COMPILER_TARGET ${triple})
set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS "s")
set(CMAKE_LINKER ld.lld)


set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic-errors \
-nostdinc \
-ffreestanding \
-fno-stack-protector \
-fno-stack-check \
-fno-lto \
-fno-PIC \
-ffunction-sections \
-fdata-sections \
-m64 \
-march=x86-64 \
-mabi=sysv \
-mno-80387 \
-mno-mmx \
-mno-sse \
-mno-sse2 \
-mno-red-zone \
-mcmodel=kernel")
set(CMAKE_CXX_FLAGS_DEBUG "-g ${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

set(CMAKE_EXE_LINKER_FLAGS "-m elf_x86_64 \
-nostdlib \
-static \
-z max-page-size=0x1000 \
--gc-sections \
-T ${CMAKE_SOURCE_DIR}/src/linker.lds")

set(ISO_ROOT ${CMAKE_SOURCE_DIR}/iso_root)
set(CMAKE_CXX_LINK_EXECUTABLE "<CMAKE_LINKER> <LINK_FLAGS> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>")
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_LINKER> <LINK_FLAGS> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>")
