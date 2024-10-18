.section .data
    str: .string "Enter a string (max 255 chars): "

.section .bss
    .lcomm input, 256       # Dung luong luu tru toi da la 255 ky tu
    .lcomm prev_char, 1     # Bien nho tam thoi
    .lcomm word_count, 4    # Bien dem so tu

.section .text
    .globl _start

_start:
    # In ra thong bao
    movl $4, %eax
    movl $1, %ebx
    movl $str, %ecx
    movl $30, %edx
    int $0x80

    # Doc vao chuoi (toi da 255 ky tu)
    movl $3, %eax
    movl $0, %ebx
    movl $input, %ecx
    movl $255, %edx
    int $0x80

    # Khoi tao cac bien
    movl $0, %ecx
    movb $32, prev_char     # Ky tu truoc la khoang trang ban dau
    movl $0, word_count     # Khoi tao dem so tu

Loop:
    movl $input, %eax
    movb (%eax, %ecx), %bl
    cmpb $0, %bl
    je _output              # Neu ket thuc chuoi, in ket qua
    cmpb $255, %cl
    je _output              # Gioi han chieu dai chuoi la 255

    # Kiem tra ky tu hien tai co phai la khoang trang
    cmpb $32, %bl
    je _check_next_char

    # Dem tu neu ky tu hien tai khong phai khoang trang va truoc do la khoang trang
    cmpb $32, prev_char
    jne _not_space
    addl $1, word_count
    cmpl $10, word_count    # Gioi han so tu la 10
    jge _output

_not_space:
    # Kiem tra neu ky tu truoc la khoang trang de chuyen doi ky tu hien tai
    cmpb $32, prev_char
    je _capitalize          # Neu ky tu truoc la khoang trang thi chuyen ky tu nay thanh hoa

    # Neu ky tu hien tai la chu hoa, chuyen no thanh chu thuong
    cmpb $65, %bl
    jl _next
    cmpb $90, %bl
    jg _next
    addb $32, %bl           # Chuyen sang chu thuong
    movb %bl, (%eax, %ecx)

_next:
    movb %bl, prev_char     # Cap nhat ky tu hien tai thanh ky tu truoc do
    incl %ecx
    jmp Loop

_capitalize:
    # Chuyen ky tu hien tai thanh chu hoa neu la chu thuong
    cmpb $97, %bl
    jl _continue_lowercase  # Neu khong phai chu thuong thi bo qua
    cmpb $122, %bl
    jg _continue_lowercase
    subb $32, %bl           # Viet hoa ky tu dau tien
    movb %bl, (%eax, %ecx)

_continue_lowercase:
    movb %bl, prev_char     # Cap nhat ky tu hien tai thanh ky tu truoc do
    incl %ecx
    jmp Loop

_check_next_char:
    # Bo qua khoang trang neu ky tu tiep theo cung la khoang trang
    movl $input, %eax
    movb (%eax, %ecx), %bl
    cmpb $32, %bl
    je _skip_space
    movb $32, %bl

_skip_space:
    movb %bl, prev_char
    incl %ecx
    jmp Loop

_output:
    movl $4, %eax
    movl $1, %ebx
    movl $input, %ecx
    movl $255, %edx
    int $0x80

_exit:
    movl $1, %eax
    int $0x80
