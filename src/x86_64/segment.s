bits 64
default rel

global lgdt
lgdt:
    cli
    lgdt [rdi]

    mov ax, dx
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    pop rdi
    mov rax, rsi
    push rax
    push rdi
    retfq
