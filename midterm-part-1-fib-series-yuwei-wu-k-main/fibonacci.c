/**
* Solving the Fibonacci Series using c.
* Author: Yuwei Wu
* Semester: 2nd Semester 2022-2023
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>


// max number of inputs
#define MAX_FIB 50000
// invalid value for memoization table
#define INVALID -1

// allocate space to hold computed data values
typedef unsigned long long ull;
ull fib_memo[MAX_FIB];


/** Solve the fibonacci series using iteration.
 *  Returns the current Nth number of the series.
 **/
ull fib_iter(int n) {
    if (n <= 1) {
        return n;
    }

    int x = 0, y = 1, curr = 0;
    for (int i = 2; i <= n; i++) {
        curr = x + y;
        x = y;
        y = curr;
    }

    return curr;
}


/** Solve the fibonacci series using recursion.
 *  Returns the Nth number of the series.
 **/
ull fib_rec(int n) {
    if (n <= 1 ) {
        return n;
    }

    return fib_rec(n - 1) + fib_rec(n - 2);
}


/** Solve the fibonacci series using dynamic programming.
 *  Returns fib_memo[n].
 **/
ull fib_dp(int n){ 
    if (n <= 0 ){
        return fib_memo[0];
    }else if (n == 1) {
        return fib_memo[1];
    }else if (fib_memo[n] != INVALID) {
        return fib_memo[n];
    }
    // store computed data
    fib_memo[n] = fib_dp(n - 1) + fib_dp(n - 2);
    return fib_memo[n];

}
/** Get entire row of 0 to nth fibonacci series.
 *  Returns the entire row.
 **/
void getEntireRow(int n, int type, bool print) {
    ull entire_row[n];

    if (type == 0) {
        for (int i = 0; i < n; i++) {
            entire_row[i] = fib_iter(i);
        }
    } else if (type == 1) {
        for (int i = 0; i < n; i++) {
            entire_row[i] = fib_rec(i);
        }
    } else if (type == 2) {
        for (int i = 0; i < MAX_FIB; i++) {
            fib_memo[i] = INVALID;
        }

        fib_memo[0] = 0;
        fib_memo[1] = 1;

        for(int i = 0; i < n; i++) {
            entire_row[i] = fib_dp(i);
        }
    }

    if (print) {
        for (int i = 0; i < n; i++) {
            printf("%llu ", entire_row[i]);
        }
        printf("\n");
    }
    
}


/** Print Nth fib number
 *  Returns nothing.
 **/
void getNth(int n, int type) {
    if (type == 0) {
        printf("%llu\n", fib_iter(n));
    } else if (type == 1) {
        printf("%llu\n", fib_rec(n));
    } else if (type == 2) {
        for (int i = 0; i < MAX_FIB; i++) {
            fib_memo[i] = INVALID;
        }

        fib_memo[0] = 0;
        fib_memo[1] = 1;

        printf("%llu\n", fib_dp(n));
    }
}


/**
 * Find max number
*/
void findMax() {
    int i = 0;
    ull a[200];
    a[0] = 0;
    a[1] = 1;
    for (i = 2; a[i] / a[i - 1] >= 1; i++) {
        a[i + 1] = a[i] + a[i - 1];
    }

    printf("Max input in unsigned long long: %d", i);
}


/** help function
 * three arguments needed for the program to run.
 **/
void help() {
    printf("./fibonacci.out N [Type] [Print Level]\n");
    printf("\tN is Nth value of the Fibonacci Series, required.\n");
    printf("\t[Type] is either 0 for iterative version, defaults to 0, 1 for recursive version, 2 for dynamic programming version.\n");
    printf("\t[Print Level] is 0 for no print/speed compare only, 1 for print Nth number, 2 for print entire row, defaults to 0.\n");

}

/** Main function
 *  prints the entire or Nth number of the fibonacci series.
 **/
int main(int argc, char* argv[])

{

    if (argc < 2)
    {
        printf("at least two arguments needed!\n");
        help();
        return 1;
    }

    const int n = atoi(argv[1]);
    int type = 0;
    int print = 0;
    if (argc > 2) {
        type = atoi(argv[2]);
    }
    if(argc > 3) {
        print = atoi(argv[3]);
    }

    bool print_it = false;
    if (print > 1) {
        print_it = true;
    }
    
    getEntireRow(n, type, print_it);
    if (print == 1) {
        getNth(n - 1, type);
    }
}