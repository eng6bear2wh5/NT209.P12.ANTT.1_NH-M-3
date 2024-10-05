.section .data
     rs:  .string "Love UIT" # khai báo vùng nhớ tên là rs lưu chuỗi "Love UIT"
     rs_len = . -rs          # khai báo hằng số tên là rs_len lưu giá trị độ dài của chuỗi rs (tính cả NULL)
     newline: .string "\n"   # khai báo vùng nhớ để lưu ký tự xuống dòng

.section .bss
     .lcomm output, 2        # khai báo vùng nhớ tên là output gồm 2 bytes
 
.section .text
     .globl _start
 _start:
 
     movl $rs_len, (output)  # chuyển độ dài của chuỗi rs vô vùng nhớ output
     addl $48,(output)       # cộng dữ liệu trong output với 48 để chuyển đổi từ số sang ký tự số
     subl $1,(output)        # trừ đi 1 do không tính NULL
     
     # Ngoài ra ta có thể gộp 2 dòng trên thành một lệnh như sau: 
     # addl $47,(output)     # cộng dữ liệu trong output (độ dài của chuỗi rs tính cả NULL) với 47 để chuyển từ số sang ký tự số của số đó được trừ đi 1 (bỏ NULL)
 
# xuất ra màn hình độ dài của chuỗi (số kỳ tự - không tính ký tự NULL)
movl $4, %eax                # sys_write
movl $1, %ebx                # std_out
movl $output, %ecx           # địa chỉ ô nhớ output
movl $2, %edx                # độ dài sẽ xuất ra (bytes)
int $0x80                    # call kernel

# xuống dòng
movl $4, %eax                # sys_write
movl $1, %ebx                # std_out
movl $newline, %ecx          # địa chỉ ô nhớ newline
movl $1, %edx                # độ dài sẽ xuất ra (bytes)
int $0x80                    # call kernel

movl $1, %eax                # system call number (sys_exit)
int $0x80                    # call kernel
