#include <stdio.h>
#include <stdlib.h>

/*
Author: Travis Grice
Date: 07/19/2020

To run use the following format
    revbits4.exe [integer] [upper] [lower]
This program reverses the bits in a specified
range of bits with the provided upper and 
lower indices. For example: revbits4.exe 61680 11 4
outputs 65280. The representations are as follows.

61680 = 00000000000000001111 00001111 0000

After reversing bits 4 through 11:
65280 = 00000000000000001111 11110000 0000

An example of a use for this program is in a communications
stack where a layer of protocols is implemented by a machine
in an unexpected endian scheme.

*/
int main(int c, char * argv[])
{   

    int n = atoi(argv[1]);
    int i = atoi(argv[3]);
    int j = atoi(argv[2]);
    
    printf("\nn=%d i=%d j=%d\n\n", n, i, j);
    
    int k = 0;
    int sum = 0;
    int m = 1;
    int p = j;
    
    while (k < i) {
        if (n & m) {
            sum += (1 << k);
            printf("%d\n", 1 << k);
        }
        m = m << 1;
        k = k + 1;
    }
    
    while (k <= j) {
        if (n & m) {
            sum += (1 << p);
            printf("%d\n", 1 << p);
        }
        p = p - 1;
        m = m << 1;
        k = k + 1;
    }
    
    while (k < 32) {
        if (n & m) {
            sum += (1 << k);
            printf("%d\n", 1 << k);
        }
        m = m << 1;
        k = k + 1;
    }
    
    printf("%d\n", sum);
}

/*
The following tests passed. Each line has a number and an output.
Outputs with an x passed.
*/
    // 11011 10110 11101 = 28381
    // 11011 01101 11101 = 28093 x
    
    // 0000000000000000010110 10001 10001 = 23089
    // 0000000000000000010110 10001 10001 = 23089 x
    
    // 0000000000000000101011 00101 01100 = 44204
    // 0000000000000000101011 10100 01100 = 44684 x
    
    // 0000000000000000110100 00100 11010 = 53402
    // 0000000000000000110100 00100 11010 = 53402 x
    
    // 0000000000000000110010 01000 00111 = 51463
    // 0000000000000000110010 00010 00111 = 51271 x
    
    // 0000000000000000111001 00110 01000 = 58568
    // 0000000000000000111001 01100 01000 = 58760 x
    
    // 0000000000000000011000 00101 10000 = 24752
    // 0000000000000000011000 10100 10000 = 25232 x
    
    // 0000000000000000010100 00110 10111 = 20695
    // 0000000000000000010100 01100 10111 = 20887 x
    
    // 0000000000000001010111 11110 01010 = 90058
    // 0000000000000001010111 01111 01010 = 89578 x
    
    // 0000000000000000100100 01110 10101 = 37333
    // 0000000000000000100100 01110 10101 = 37333 x
    
    // 0000000000000000101000 00000 11001 = 40985
    // 0000000000000000101000 00000 11001 = 40985 x
    
    // 0101 1010 0011 0001 = 23089
    // 0101 1100 0101 0001 = 23633 x
    
    // 1111 0000 1111 0000 = 61680
    // 1111 1111 0000 0000 = 65280 x