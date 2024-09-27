#include <stdio.h>

//1.1: Thực hiện | bit 2 số nguyên (không dùng | chỉ dùng & và ~)
int bitOr(int x, int y)
{
    return(~(~x & ~y)); // Biến đổi bảng chân trị của AND sang bảng chân trị của OR
}

// 1.2: Tính giá trị của -x mà không dùng dấu -
int negative(int x)
{
    return ~x + 1; // Tính dạng bù 2 của x
}

// 1.3: Lật byte thứ n của số nguyên x
int flipByte(int x, int n)
{
    return x ^ (0xFF << (n << 3)); // x XOR với 0xFF được dịch trái 8*n bit (0 <= n <= 3)
}

// 1.4: Tính kết quả phép chia lấy dư x % 2^n
int mod2n(int x, int n)
{
    int n_bit_1 = ((1 << n) + (1 + ~1)); // Tạo ra mask với n bit 1
    return x & n_bit_1; // x AND với n bit 1 sẽ ra được số dư
}

//1.5: Tính kết quả của x/2^n với mọi giá trị của n (-31 <= n <= 31)
unsigned int divpw2(unsigned int x, int n) {
    unsigned int mask = (n >> 31); // Tạo mask kiểm tra dấu của n
    unsigned int abs_n = (n ^ mask) + (~mask + 1); // Tính giá trị tuyệt đối của n
    return (x << (mask & abs_n)) >> (~mask & abs_n); // Dịch trái hoặc dịch phải bit của x tùy theo dấu của n
}

//2.1: Kiểm tra 2 số x và y có bằng nhau hay không?
int isEqual(int x, int y) {
    return !(x ^ y); //Mô phỏng và trả về kết quả như cổng logic XNOR
}

//2.2: Kiểm tra số nguyên x có chia hết cho 16 hay không?
int is16x(int x) {
    return !(x & 15); // AND x với 15 (1111) để tìm số dư của phép chia x cho 16, nếu có dư thì ! (số dư) thành 0 và ngược lại.
}

//2.3: Trả về 1 nếu x > 0
int isPositive(int x) {

    return !(x >> 31) & !(!x); // kết quả trả về sẽ là 1 (đảo nghịch từ bit dấu dương là 0 để thỏa mãn output);
}

// 2.4: Trả về 1 nếu x >= 2^n
int isGE2n(int x, int n) {

    return ((x + (~(1 << n) + 1)) >> 31) & 1 ^ 1; // Lấy bit dấu của kết quả phép tính (x - 2^n) XOR với 1
}

int main()
{
    int score = 0;
    // 1.1
    printf("1.1 bitOr");
    if (bitOr(3, -9) == (3 | -9))
    {
        printf("\tPass.");
        score += 1;
    }
    else
        printf("\tFailed.");

    //1.2
    printf("\n1.2 negative");
    if (negative(0) == 0 && negative(9) == -9 && negative(-5) == 5)
    {
        printf("\tPass.");
        score += 1;
    }
    else
        printf("\tFailed.");

    //1.3
    printf("\n1.3 flipByte");
    if (flipByte(10, 0) == 245 && flipByte(0, 1) == 65280 && flipByte(0x5501, 1) == 0xaa01)
    {
        printf("\tPass.");
        score += 2;
    }
    else
        printf("\tFailed.");

    //1.4
    printf("\n1.4 mod2n");
    if (mod2n(2, 1) == 0 && mod2n(30, 2) == 2 && mod2n(63, 6) == 63)
    {
        printf("\tPass.");
        score += 2;
    }
    else
        printf("\tFailed.");

    //1.5
    printf("\n1.5 divpw2");
    if (divpw2(0xfffffff, -4) == 0xfffffff0 && divpw2(15, -2) == 60 && divpw2(2, -4) == 32)
    {
        if (divpw2(10, 1) == 5 && divpw2(50, 2) == 12)
        {
            printf("\tAdvanced Pass.");
            score += 4;
        }
        else
        {
            printf("\tPass.");
            score += 3;
        }
    }
    else
        printf("\tFailed.");

    //2.1
    printf("\n2.1 isEqual");
    if (isEqual(4, 4) == 1 && isEqual(-5, 2) == 0 && isEqual(-5, -5) == 1)
    {
        printf("\tPass.");
        score += 2;
    }
    else
        printf("\tFailed.");

    //2.2
    printf("\n2.2 is16x");
    if (is16x(16) == 1 && is16x(23) == 0 && is16x(0) == 1)
    {
        printf("\tPass.");
        score += 2;
    }
    else
        printf("\tFailed.");

    //2.3
    printf("\n2.3 isPositive");
    if (isPositive(16) == 1 && isPositive(0) == 0 && isPositive(-8) == 0)
    {
        printf("\tPass.");
        score += 3;
    }
    else
        printf("\tFailed.");

    //2.4
    printf("\n2.4 isGE2n");
    if (isGE2n(12, 4) == 0 && isGE2n(8, 3) == 1 && isGE2n(15, 2) == 1)
    {
        printf("\tPass.");
        score += 3;
    }
    else
        printf("\tFailed.");

    printf("\n------\nYour score: %.1f", (float)score / 2);
    return 0;
}
