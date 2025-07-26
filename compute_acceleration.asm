section .data
    align 8
    convert_const: dq 0.27777777778         ; double constant: 1000/3600

section .text
    global compute_acceleration

compute_acceleration:
    push rbp
    mov rbp, rsp
    sub rsp, 16
    movsd [rsp], xmm7
    movsd xmm7, [convert_const]

    xor r9d, r9d

.loop:
    cmp r9d, r8d
    jge .done

    mov eax, r9d
    imul eax, 24
    mov rax, rax

    movsd xmm0, [rcx + rax]         ; vi
    movsd xmm1, [rcx + rax + 8]     ; vf
    movsd xmm2, [rcx + rax + 16]    ; t

    subsd xmm1, xmm0        ; xmm1 = vf - vi
    mulsd xmm1, xmm7        ; convert to m/s
    divsd xmm1, xmm2        ; divide by time

    ; Round and convert to int
    cvtsd2si eax, xmm1                   ; eax = (int)acceleration

    ; Store to results
    mov [rdx + r9*4], eax

    inc r9d
    jmp .loop

.done:
    movsd xmm7, [rsp]  ; restore xmm7
    add rsp, 16
    pop rbp
    ret