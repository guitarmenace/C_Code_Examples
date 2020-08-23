/*
Travis Grice
08/22/2020
LSFR Example
Based on an example by Prof. James CM Li
(https://www.youtube.com/watch?v=s2t1AiSPjn0)
*/

// includes
#include <stdio.h>
#include <stdint.h>

// defines
#define BIT0 1
#define BIT1 2

// typedefs
typedef uint8_t STATE;

// prototypes
void showStates(STATE);
char * toBinary(STATE);

// main function
int main(void) {
    uint9_t init_seed = 0b1000;
    
    // prints every state of the LFSR register
    // which satisfies the recurrence relation
    // described below.
    showStates(init_seed);
    
    return 0;
}

/* This function takes an input 'seed' and generates
   new values for the register composed of Q3Q2Q1Q0 that
   satisfies the following recurrence relations.

   Q3 = Q1 ^ Q0
   Q2 = Q3
   Q1 = Q2
   Q0 = Q1

   The example register is shown here.
   -------------------------<+<------<
   |                         ^       ^
   ----->Q3----->Q2----->Q1--^-->Q0--^------> Output

   Also called an 'autonomous LFSR' this register performs
   mod-2 addition with Q1 and Q0 as operands and outputs
   a pseudo-random value between 1 and 16. */
   
void showStates(STATE seed) {
    // declarations
    STATE current, next;
    current = seed;
    do {
        // Assign the next STATE
        next = current >> 1;
        next |= (((current & BIT1) >> 1) ^ (current & BIT0)) << 3;
        printf("current state = %s\n", toBinary(current));
        current = next;
    } while (current != seed);
}

/* This function takes a 4-bit binary value represented as a STATE
   and returns the equivalent as a binary string. */
   
char * toBinary(STATE state) {
    char temp[4] = "0000";
    int i, j;
    for (i = 8, j = 0; i > 0; i /= 2, j++) {
        if (state >= i) {
            temp[j] = '1';
            state -= i;
        }
    }
    char * str = temp;
    return str;
}
