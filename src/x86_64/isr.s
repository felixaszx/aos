bits 64
default rel

;Interupt Service Traps (IST) 

extern interrupt_disaptch
interrupt_stub:
    push rax
    push rbx
    ;push other registers here
    push r14
    push r15
    mov rdi, rsp
    call interrupt_disaptch
    mov rsp, rax
    pop r15
    pop r14
    ;push other registers here
    pop rbx
    pop rax
    ;remove the vector number + error code
    add rsp, 16
    iretq

%macro isr_call 1
global isr_%1_handler
align 16
isr_%1_handler:
    push 0 ;error code
    push %1 ;vector number
    jmp interrupt_stub
%endmacro

%macro error_isr_call 1
global isr_%1_handler
align 16
isr_%1_handler:
    push %1 ;vector number
    jmp interrupt_stub
%endmacro

isr_call       0  ;#DE
isr_call       1  ;#DB
isr_call       2  ;#NMI
isr_call       3  ;#BP
isr_call       4  ;#OF
isr_call       5  ;#BR
isr_call       6  ;#UD
isr_call       7  ;#NM
error_isr_call 8  ;#DF
isr_call       9
error_isr_call 10 ;#TS
error_isr_call 11 ;#NP
error_isr_call 12 ;#SS
error_isr_call 13 ;#GP
error_isr_call 14 ;#PF
isr_call       15
isr_call       16 ;#MF
error_isr_call 17 ;#AC
isr_call       18 ;#MC
isr_call       19 ;#XF
isr_call       20 ;#VE
isr_call       21 ;#CP
isr_call       22
isr_call       23
isr_call       24
isr_call       25
isr_call       26
isr_call       27
isr_call       28 ;#HV
isr_call       29 ;#VC
error_isr_call 30 ;#SX
isr_call       31
