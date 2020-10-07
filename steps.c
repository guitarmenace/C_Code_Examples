/*
Travis Grice
10/07/2020
Staircase Problem (See below for descripiton)

There's a staircase with N steps, and you can climb 1 or 2 steps at a time. Given N, 
write a function that returns the number of unique ways you can climb the staircase. 
The order of the steps matters.

For example, if N is 4, then there are 5 unique ways:

1, 1, 1, 1
2, 1, 1
1, 2, 1
1, 1, 2
2, 2

What if, instead of being able to climb 1 or 2 steps at a time, you could climb any 
number from a set of positive integers X? For example, if X = {1, 3, 5}, you could 
climb 1, 3, or 5 steps at a time. Generalize your function to take in X.

This sample code only addresses the first part of the problem. Although it is very
easy to adapt to solving the second part by adjusting the 'other_ways_possible' to
dynamically store the number of the (n-x) step count.

*/
#include <stdio.h>
#include <stdint.h>

uint64_t ways_possible(uint8_t top_step);
uint64_t other_ways_possible(uint8_t top_step);
void test_function(uint64_t (*func)(uint8_t));
#define TOP 30

int main() {
    
    // Test the first method
    test_function(ways_possible);
    
    // Test the second method - which is the faster of the two.
    test_function(other_ways_possible);
    
    return 0;
}

/* Takes a function and prints the output of the function with
a range of integer inputs like a testbench. */
void test_function(uint64_t (*func)(uint8_t)) {
    uint8_t i = 0;
    while (i < TOP) {
        printf("Number of ways with %d steps = %lu\n",
            i, func(i));
        i++;
    }
}

/* This method is very redundant and slow - especially if there
are more than 30 steps involved, but is easy to read and is fairly
intuitive. */
uint64_t ways_possible(uint8_t top_step) {
    if (top_step < 3) return top_step;
    else return ways_possible(top_step - 1) + ways_possible(top_step - 2);
}

/* This method utilizes dynamic programming so it's much faster. */
uint64_t other_ways_possible(uint8_t top_step) {
    if (top_step < 3) {
        return top_step;
    } else {
        // example: 10 steps -> step 10 == stairs[10]
        uint64_t stairs[top_step + 1];
        
        // step 0 is like the ground - no stairs exist
        stairs[1] = 1;
        stairs[2] = 2;
        
        uint8_t i = 3;
        while (i <= top_step) {
            stairs[i] = stairs[i - 1] + stairs[i - 2];
            i++;
        }
        return stairs[top_step];
    }
}
