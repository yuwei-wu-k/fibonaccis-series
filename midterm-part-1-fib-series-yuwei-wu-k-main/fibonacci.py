"""
Solving the Fibonacci Series using python.
Author: Yuwei Wu
Semester: 2nd Semester 2022-2023
"""
from enum import Enum
from functools import lru_cache
import click
import sys
import fib_test_runner

STACK_LIMIT = 10000
MAX_FIB = 7000
sys.setrecursionlimit(100000)

class FibonacciType(Enum):
    DP = 2
    RECURSIVE = 1
    ITERATIVE = 0

# invalid value for memoization table(fib_table)
INVALID = -1

# fib table
fib_table = [INVALID] * MAX_FIB


@lru_cache(maxsize=None)
def fib_dp(n:int) -> int:
    """
    Solves the fibonacci using dynaic programming with 
    simple recursion and built in memoization
    Args:
        n: the nth number
    Returns:
        fib_table[n]
    """
    fib = [0, 1]
    for i in range(2, n+1):
        fib.append(fib[i-1] + fib[i-2])
    return fib[n]


def fib_iter(n: int) -> int:
    """
    Solves the fibonacci using simple iteration
    Args:
        n (int): the nth number
    Returns:
        the current number in the iteration
    """
    if n < 0:
        return INVALID

    x, y, curr = 0, 1, 0
    for i in range(2, n + 1):
        curr = x + y
        x = y
        y = curr
    return curr


def fib_rec(n: int) -> int:
    """
    Solves the fibonacci using simple recursion
    Args:
        n (int): the nth number
    Returns:
        the nth number 
    """
    if n < 0:
        return 0
    if n == 0 or n == 1:
        return n
    return fib_rec(n - 1) + fib_rec(n - 2)


def get_entire_row(n: int, print_type: int, print_it: bool) -> None:
    """
    get the entire row of the fibonacci series
    Args:
        n (int): the nth number
        print_type (int): the type of the algorithm
        print_it (bool): whether to print the entire row
    Returns:
        none
    """
    entire_row = []

    if print_type == 0:
        for i in range(n):
            entire_row.append(fib_iter(i))
    elif print_type == 1:
        for i in range(n):
            entire_row.append(fib_rec(i))
    elif print_type == 2:
        for i in range(MAX_FIB):
            fib_table[i] = INVALID

        fib_table[0] = 0
        fib_table[1] = 1

        for i in range(n):
            entire_row.append(fib_dp(i))

    #if print_it:
     #   print(entire_row)


def get_nth(n: int, print_type: int) -> None:
    """
    get the nth number of the fibonacci series
    Args:
        n (int): the nth number
        print_type (int): the type of the algorithm
    Returns:
        none
    """
    if print_type == 0:
        fib_iter(n)
    elif print_type == 1:
        fib_rec(n)
    elif print_type == 2:
        for i in range(MAX_FIB):
            fib_table[i] = INVALID

        fib_table[0] = 0
        fib_table[1] = 1

        # print(fib_dp(n))


@click.command()
@click.argument("n", type=click.IntRange(min=0, max=50000, clamp=True))
@click.option("--algo", type=click.Choice(['recursive', 'dp', 'iterative'], case_sensitive=False), default='recursive')
@click.option("--print-type", type=click.Choice(['all', 'none', 'Nth'], case_sensitive=False), default='all')
def main(n: int, algo: str, print_type: str):
    """
    Prints the row/none/nth of the fibonacci series.

    Args:
        n (int): the nth number
        print_type (str): three types of printing
        algo (str): three types of algorithms
    """
    print_it = print_type 
    t = FibonacciType.ITERATIVE
    if algo == 'recursive':
        t = FibonacciType.RECURSIVE
    elif algo == 'dp':
        t = FibonacciType.DP
    row = get_entire_row(n, t.value, print_it)

    # if print_type == 'all':
        # print(row)
    # elif print_type == 'Nth':
        #get_nth(n, t.value)
    

if __name__ == '__main__':
    main()
