/*******************************************************
 Travis Grice
 08/23/2020
 Defining an LFSR with bit-fields
 The goals of this program were to
 1) learn about bit-fields
 2) practice using pointers to functions
 3) apply concepts of a shift register with C
 
 Although it isn't really a Linear Feedback Shift 
 Register (LFSR) because at the moment there is no
 linear feedback, it was a good reminder of the more
 fundamental aspects of c programming. Also in general
 these functions would all be done using bit-wise
 shifting on a word (or double word) length unit
 of memory (such as an unsigned integer). 
 *******************************************************/
 
#include <stdio.h>
#include <stdint.h>

// type definitions
typedef struct reg LFSR;
typedef void (*funcptr)(void);
typedef void (*shiftfunc)(LFSR *);

struct reg {
    uint8_t q3 : 1; // Most significant bit (MSB)
    uint8_t q2 : 1;
    uint8_t q1 : 1;
    uint8_t q0 : 1; // Least significant bit (LSB)
    uint8_t    : 4; // Not used. Padded with zeros.
    
    shiftfunc sr_4bit; // shift right
    shiftfunc sl_4bit; // shift left
};

// Prototypes
void testFunction(void);
void shift_right(LFSR *);

/****************************************************
 In this main function, an LFSR data structure will 
 be declared, right shift operations performed on the
 internal data, and the results displayed. 
 ****************************************************/
int main()
{
    printf("Hello World\n\n");
    // Start the register with a value of 1000.
    LFSR l0 = {1, 0, 0, 0, shift_right, shift_right};
    printf("%d%d%d%d\n", l0.q3, l0.q2, l0.q1, l0.q0);
    
    // Next - shift the contents right four times.
    l0.sr_4bit(&l0);
    printf("%d%d%d%d\n", l0.q3, l0.q2, l0.q1, l0.q0);
    l0.sr_4bit(&l0);
    printf("%d%d%d%d\n", l0.q3, l0.q2, l0.q1, l0.q0);
    l0.sr_4bit(&l0);
    printf("%d%d%d%d\n", l0.q3, l0.q2, l0.q1, l0.q0);
    l0.sr_4bit(&l0);
    printf("%d%d%d%d\n", l0.q3, l0.q2, l0.q1, l0.q0);
    return 0;
}

/***************************************
 This function was used to test pointer 
 function assignment. I needed to remind
 myself of how pointers to functions are
 declared, assigned, and passed around.
 ***************************************/

void testFunction() {
    printf("Hello function pointer.\n");
}

/******************************
 This function takes a pointer
 to an LFSR and assigns values
 to the four bit-fields that 
 are shifted by one field. A 
 shift in this way is similar 
 to dividing a binary number
 by two.
 *****************************/
void shift_right(LFSR * lfsr) {
    LFSR * temp = lfsr;
    temp -> q0 = temp -> q1;
    temp -> q1 = temp -> q2;
    temp -> q2 = temp -> q3;
    temp -> q3 = 0;
}
