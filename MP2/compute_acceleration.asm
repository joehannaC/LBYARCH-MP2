section .data
    align 8
    convert_const: dq 0.27777777778         ; double constant: 1000 / 3600

section .text
    global _compute_acceleration            ; added "_" for macos

_compute_acceleration:                      ; added "_" for macos
    push rbp
    mov rbp, rsp
    sub rsp, 16
    movsd [rsp], xmm7

    movsd xmm7, [rel convert_const]

    xor ecx, ecx

.loop:
    cmp ecx, edx        ; used edx for macos
    jge .done

    mov eax, ecx
    imul eax, 24
    mov rax, rax

    ; used rdi instead of rcx for macos
    movsd xmm0, [rdi + rax]       ; vi
    movsd xmm1, [rdi + rax + 8]   ; vf
    movsd xmm2, [rdi + rax + 16]  ; t

    subsd xmm1, xmm0              ; vf - vi
    mulsd xmm1, xmm7              ; convert to m/s
    divsd xmm1, xmm2              ; acceleration

    cvtsd2si eax, xmm1            ; convert to int
    mov [rsi + rcx*4], eax        ; for results, used rsi instead of rdx for macos

    inc ecx
    jmp .loop

.done:
    movsd xmm7, [rsp]  ; restore xmm7
    add rsp, 16
    pop rbp
    ret
