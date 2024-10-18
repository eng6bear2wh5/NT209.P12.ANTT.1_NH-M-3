.section .data
     Cau_dan: .string "Enter a number (4-digits): "
     Tang: .string "Tang dan"
     Khong_tang: .string "Khong tang dan"
     newline: .string "\n" # Chuỗi xuống dòng

.section .bss
     .lcomm input, 5

.section .text
    .globl _start
_start:
    
    # In thông báo nhập vào một chuỗi số có 4 chữ số
    movl $4, %eax
    movl $1, %ebx
    movl $Cau_dan, %ecx
    movl $28, %edx
    int $0x80
    
    #Nhập chuỗi số có 4 chữ số 
    movl $3, %eax
    movl $0, %ebx
    movl $input, %ecx
    movl $5, %edx
    int $0x80
    
    movl $input, %eax                         # Đưa địa chỉ của chuỗi số có 4 chữ số vô thanh ghi %eax
    
    # so sánh input[0] với input[1]
    movb (%eax), %bl                          # Đưa số input[0] (ở dạng ký tự số) vô thanh ghi %bl
    movb 1(%eax), %bh                         # Đưa số input[1] (ở dạng ký tự số) vô thanh ghi %bh
    subb $48, %bl                             # Chuyển ký tự số input[0] thành số
    subb $48, %bh                             # Chuyển ký tự số input[1] thành số
    cmpb %bl, %bh                             # So sánh số input[1] ? input[0]
    jle .L2                                   # Nếu số input[1] <= input[0] thì nhảy đến .L2
    
    # so sánh input[1] với input[2]
    movb 1(%eax), %bl                         # Đưa số input[1] (ở dạng ký tự số) vô thanh ghi %bl
    movb 2(%eax), %bh                         # Đưa số input[2] (ở dạng ký tự số) vô thanh ghi %bh
    subb $48, %bl                             # Chuyển ký tự số input[1] thành số
    subb $48, %bh                             # Chuyển ký tự số input[2] thành số
    cmpb %bl, %bh                             # So sánh số input[2] ? input[1]
    jle .L2                                   # Nếu số input[2] <= input[1] thì nhảy đến .L2
    
    # so sánh input[2] với input[3]
    movb 2(%eax), %bl                         # Đưa số input[2] (ở dạng ký tự số) vô thanh ghi %bl
    movb 3(%eax), %bh                         # Đưa số input[3] (ở dạng ký tự số) vô thanh ghi %bh
    subb $48, %bl                             # Chuyển ký tự số input[2] thành số
    subb $48, %bh                             # Chuyển ký tự số input[3] thành số
    cmpb %bl, %bh                             # So sánh số input[3] ? input[2]
    jle .L2                                   # Nếu số input[3] <= input[2] thì nhảy đến .L2
    
    # Nếu dãy số trên tăng dần thì sẽ thực hiện in ra "Tang dan"
    movl $4, %eax
    movl $1, %ebx
    movl $Tang, %ecx
    movl $8, %edx
    int $0x80

    # xuống dòng
    movl $4, %eax                  
    movl $1, %ebx                   
    movl $newline, %ecx             
    movl $1, %edx                   
    int $0x80                   
    
    jmp .Done   # Nhảy xuống Done để kết thúc chương trình. Không thực hiện in ra "Khong tang dan"
    
    .L2:      # Nếu như có bất kỳ số ở sau nào bé hơn hoặc bằng số liền trước nó thì sẽ nhảy xuống .L2 để in ra "Khong tang dan"
    movl $4, %eax
    movl $1, %ebx
    movl $Khong_tang, %ecx
    movl $14, %edx
    int $0x80

    # xuống dòng
    movl $4, %eax                   
    movl $1, %ebx                   
    movl $newline, %ecx            
    movl $1, %edx                  
    int $0x80                     
    
    .Done:      #  Kết thúc chương trình
    movl $1, %eax
    int $0x80
    
    
    
