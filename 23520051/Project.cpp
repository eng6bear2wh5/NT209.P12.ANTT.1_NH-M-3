#include <stdio.h>
int bitOr(int x, int y)
{
    return(~(~x & ~y));
}

int negative(int x)
{
    return ~x+1; //toán tử ~để lật bit của x
}

int flipByte(int x, int n) {
    return x ^ (0xFF << (n << 3));
}

int mod2n(int x, int n)
{
    return x;
}

unsigned int divpw2(unsigned int x, int n) {
    unsigned int mask = (n >> 31);
    unsigned int abs_n = (n ^ mask) + (~mask+1); 
    return (x << (mask & abs_n)) >> (~mask & abs_n);
}

int isEqual(int x, int y) {
    return !(x^y); //Mô phỏng và trả về kết quả như cổng logic XNor

}

int is16x(int x) {
    return !((x & 10000) ^ x);;
}

int isPositive(int x) {
    
    return !(x >> 31) & !(!x); // kết quả trả về sẽ là 1 (đảo nghịch từ bit dấu dương là 0 để thỏa mãn output);
}

int isGE2n(int x, int n) {
    return ((x + (~(1 << n)+1)) >> 31) & 1 ^ 1;
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