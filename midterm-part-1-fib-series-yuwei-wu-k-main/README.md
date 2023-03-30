# Midterm p1: Report on Analysis of Fibonacci  Series
* **Author**: Yuwei Wu
* **GitHub**: https://github.com/Spring23-CS5008-BOS-Lionelle/midterm-part-1-fib-series-yuwei-wu-k
* **Semester** Spring 2023
* **Languages Used**: C, Python 

## Overview
This report focuses on analyzing three algorithms for fibonacci series and their time analysis. 

The [Fibonacci series]<sup>4</sup> is a sequence of numbers where each number is the sum of the two preceding ones, usually starting with 0 and 1. The sequence goes as 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, ...  Fibonacci numbers also exist in nature and they are associated with the Golden Ratio. 

There are three algorithms for computing the Nth Fibonacci number Fn: iterative approach, recursive approach, and dynamic programming approach, each will be discussed in more details below. To analyze the cost of these algorithms, we need to use Big O notation. Big O Astands for the theoretical measure of the execution of an algorithm. It is about finding an asymptotic upper bound. 

The following chart represents the Big O value of three algorithms which will be analyzed in this report. 

| Version |  Big O | Space Used | 
| :-- | :-- |  :-- |
| Iterative | $O(n)$ | $O(1)$ |
| Recursive | $O(2^n)$  | $O(n)$ |
| Dynamic Programming | $O(n)$ | $O(n)$ |


### Approach 1: Iterative
1.1 Implementation
```text 
Function fib_iter(n):
    if n == 0:
        return 0
    else if n == 1:
        return 1

    x = 0
    y = 1
    curr = 0
    for i from 2 to n:
        curr = x + y
        x = y
        y = curr

    return curr
```

1.2 Time Complexity Analysis

Iterative is an efficient algorithms on this list. As the loop runs from 2 to n iterations before returning, and each iteration does constant work, the time complexity is linear which runs in $O(n)$ time. 


### Approach 2: Recursive
In recursion, the function calls itself until the base condition is met. Here, the function fib() makes a call to itself.

An example tree representing what fib(5) would look like
![recursive_example]  


2.1 Implementation 

The recursive formula is given as:
```text
F(0) = 0, // this is a given base case
F(1) = 1, // this is a given base case
F(n) = F(n-1) + F(n-2) for (n > 1) // this is every other case for n > 1
```

2.2 Time Complexity Analysis

To calculate time complexity, we can solve a recurrence relation: 
```c 
T(0) = 0
T(1) = 1
T(n) = T(n - 1) + T(n - 2) + O(1)
```

T(n) represents the fib function. $T(n−1)$ and $T(n−2)$ represent the recursive calls to $fib(n-1)$ and $fib(n-2)$. $T(0) = 0$, $T(1) = 1$ represent the base cases, O(1) represents the constant time to perform the previous addition.

So we can first establish a lower bound by approximating that $T(n-1) ≈ T(n-2)$, though $T(n - 1) >= T(n - 2)$, hence lower bound

![equation1]


For the uppder bound, we can approximate $T(n-1) ≈ T(n-2)$ as $T(n-1) <= T(n-2)$. 

![equation2]

This two are just approxiamte calculation. After searching, I discovered the tight bound of [Big O]<sup>1</sup> is $O(1.6180^n)$.

![Big_O]


Since Big-O notation represents the upper bound of the running time of an algorithm, in other words, the worst-case complexity, the time taken by recursive approach is $O(2^n)$ or exponential, which isn’t very efficient. This has the potential to be bad in cases that there isn't enough physical memory to handle the increasingly growing stack, leading to a StackOverflowError.


### Approach 3: Dynamic Programming

This is similar to the recursive solution but using a “memo” for caching the result of fibo(n) when it is called for the first time.

Recursive Call Tree
![fib_dp]


Recursive calls that return their result immediately are shaded in gray. As shown in the figure, subtrees correspond to subproblems that have already been solved are pruned from this recursive call tree.

3.1 Implementation
```text 
F(n): 
     if n < 0
          return INVALID
     if fib(n) was previously computed 
          return stored value fib(n) 
     else return fib(n − 1) + fib(n − 2)
```


3.2 Time Complexity Analysis

As for the recursive solution, the time complexity is the number of nodes in the recursive call tree. 

There are $n-1$ non-immediately returning calls to fibo, and each of the corresponding nodes has another child that returns immediately. Plus the node for $n=2$ has one additional child that returns immediately (one of the base cases). Thus, there are $2(n-1) + 1 = 2n-1$ nodes in the tree. The time complexity is thus $O(n)$, which is much more efficient than recursive solution.


## Empirical Data & Discussion 
When computing the fibonacci numbers beyond the range of the 'long long' data type which is n = 95, the result will overflow and the time won't be accurate. 

I also write a function to test it.
```c 
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
``` 

I maxed out the time within 60 seconds to run multiple iteration. For the recursive versions for C and Python, both maxed out longer than the rest of the algorithms. 

### Recursive Versions
![recursive_c]

The c recursive version stop at n = 48 taking about 50 seconds to run. The curve start to rise sharply between n = 40 and 48.

![recursive_p]

The python recursive version also rises very quick with topped out at n = 40, taking about 40 seconds to run. 

![recursive_c_p]

I also combined the previous recursive results for C and Python in a graph. C runs much faster than Python and they have a similar curve. 


### Iterative and Dynamic Programming Versions
Due to the algorithm of the iterative and dynamic programming versions, I compared their speed both in Python and C versions with larger n values up to 5000.

![p_comparison]

As shown in the graph, the iterative approach grows slower than dynamic programming, indicating that iterative is faster than dp. But basically they have similar curve with number increases. There might also be slight variations on each run as the computer was working on different tasks.


![c_comparison]

Due to the algorithm, even n = 5000 is hard to see. For this C comparison, the iterative and dynamic programming approach also grow gradually. For n = 5000, the iterative version only takes about 0.03 seconds and the dynamic programming takes about 0.04. We can concludes that C runs much faster than Python. 



I concluded the timeout windows for each algorithm listed below.

| Algorithm | N (timeout < 60 seconds) | Last Timed Incident (seconds)
|--|:--:|:--:|
| Iterative C            | 1000,00+   | 18| 
| Recursive C            | 48        | 50 |
| Dynamic Programming  C | 10,000    | 55|
| Iterative P            | 1200     | 31 |
| Recursive P            | 40        | 40 |
| Dynamic Programming  P | 1035     | 45 |

For every case across both languages  Iterative was faster than dynamic programming was much faster than rcursive versions. 


## Language Analysis

The code writing can be found in the following files:

[fibonacci.c] -- implementation of functions in C

[fibonacci.py] -- implementation of function in Python

[fib_test_runner.py] -- run script to help with tests and keep timings

After analyzing the smaple files provided in class, I dicided to start devloping code in c as there is a similair example to impelment pascal in the instructions. Then I switched to Python and mirrored thoses functions in C. 

### Language 1: C

For three algorihtm implementation in c, I got inspiration from canvas videos and [Geeks for Geeks]<sup>2<sup> . 

Iterative and recursive approaches shown below are straightforward. 

```c  
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

ull fib_rec(int n) {
    if (n <= 1) {
        return n;
    }
    
    return fib_rec(n - 1) + fib_rec(n - 2);
}
```

For dynamic programming method, I'm thinking using that the sovling any subproblem depends solving the smaller subproblems. So I implemented the solution and saved each subproblem in an array. 
```c  
ull fib_dp(int n){ 
    int f[n+1];
    int i;
    
    // base case
    f[0] = 0;
    f[1] = 1;
    
    for (i = 2; i <= n; i++) {
        f[i] = f[i-1] + f[i-2];
    }
    
    return f[n];
}
```

The top-down approach is easy to implement as I just added an array or a lookup table to store results during recursion. But through searching on [memoization]<sup>3</sup>, I found that this is slower than another bottom-up approach becuase of large recursive calls when the number gets bigger, and it takes up more memory space. If the recursion tree is very deep, it may run out of stack space and crash my program. 


Since we have to meet three conditions of print out from 1 to n, just n, or northing of the sequence, I wrote a getEntireRow and getNth function that would generate entire row up to n or just nth value. For deciding whether it is needed to print, I added an print argument of type boolen in getEntireRow.


### Language 2: Python 
I selected Python for my second language not only becuase I learned it in the first semester and it is a widely used language. Besides, the analytics libraries give me the flexibiiltly to experiment with the builtin tools as well as practice quick development. 

In fibonacci.py, the main function uses click to define a command line interface that takes in a value for n, the type of algorithm to use (recursive, dp, or iterative), and whether to print the entire row or just the nth number. It then calls the appropriate function(s) based on the input.

When I ran dp function the run time is longer than expected. To optimize the function, I searched the Python library and found the runctool for dynamic programming such as lru_cache and cache decorator that help reduce the run time of dp excution.

```python
from functtools import lru_cache

@lru_cache(maxsize=None)
def fib_dp(n:int) -> int:
    if n < 0:
        return INVALID
    if fib_table[n] != INVALID:
        return fib_table[n]
    fib_table[n] = fib_dp(n - 1) + fib_dp(n - 2)
    return fib_table[n]
```

As can been shown in the Python comparison of iterative and dynamic programming the time processed becomes instantly faster. I also import enum to improve the function selection and the click module to help assist the user in converting the input data with three arguments. 

```python
@click.command()
@click.argument("n", type=click.IntRange(min=0, max=50000, clamp=True))
@click.option("--algo", type=click.Choice(['recursive', 'dp', 'iterative'], case_sensitive=False), default='recursive')
@click.option("--print-type", type=click.Choice(['all', 'none', 'Nth'], case_sensitive=False), default='all')
```

### Comparison and Discussion Between Experiences
After comparison and analysis, I found C runs much faster than Python. In Python, dynamic programming runs faster than iterative due to the cache in memory. I tried to install pypy3 but kept getting errors about my environment setting. So I didn't added it to my experiment list due to time limit. I also spent much time on debugging get_entire_row and dp functions. I first wrote get_entire_row in each algorithm and relized later that I could optimized it by pull out three same loop and put them in one single function, which increases the code readability. 


## Conclusions / Reflection

In conclusion, recursive runs much slower than iterative and dynamic programming as can be seen in the graphs. Although there are another methods for implemting dynamic programming such as "matrix" and "math", this approach is pretty fast compared to others with only O(n) time taken. I learned much about fibonacci number and the algorithms for calculation with Big O analysis. I reviewd and explored the algorithms with focus mainly on recursive and dynamic programming. There might be more efficient way to implement recursion but due to time limit I'm unable to explore those solutions. It would be much more efficient if we choose the right algorithm to solve problems. I also dived into the Big O and tried to analyze it with different algorithms. Besides, during coding and debugging, I became more aware of the logical flow of the program, and paying more attention on the input and return value/type of each function. Fianlly, I developed my research skills, writing skills, ability to handle useful tools like Latex and Datawrapper (data visulaizatino). 



## References
1. GeeksforGeeks, "Time complexity of recursive Fibonacci program," GeeksforGeeks, October 20, 2017. 
https://www.geeksforgeeks.org/time-complexity-recursive-fibonacci-program/. Accessed on: February 26, 2023.
2. GeeksforGeeks, "C Program For Fibonacci Numbers," GeeksforGeeks, October 18, 2021. 
https://www.geeksforgeeks.org/c-program-for-fibonacci-numbers/. Accessed on: February 26, 2023.
3. GeeksforGeeks, "Tabulation vs Memoization," GeeksforGeeks, December 30, 2021. 
https://www.geeksforgeeks.org/tabulation-vs-memoization/. Accessed on: February 27, 2023.
4. Wikipedia, "Fibonacci number," https://en.wikipedia.org/wiki/Fibonacci_number. Accessed on: February 25, 2023. 
5. freeCodeCamp, "What is Big O Notation Explained: Space and Time Complexity," Janurary16, 2020. https://www.freecodecamp.org/news/big-o-notation-why-it-matters-and-why-it-doesnt-1674cfa8a23c/. Accessed on March 2, 2023. 


<!-- auto references -->
[recursive_example]: recursive.JPG
[fib_dp]: fib_dp.png
[Big O]: https://www.geeksforgeeks.org/time-complexity-recursive-fibonacci-program/
[Geeks for Geeks]: https://www.geeksforgeeks.org/c-program-for-fibonacci-numbers/
[memoization]: https://www.geeksforgeeks.org/tabulation-vs-memoization/
[Fibonacci series]: https://en.wikipedia.org/wiki/Fibonacci_number
[recursive_c]: recursive_c.png
[recursive_p]: recursive_p.png
[recursive_c_p]: recursive_c_p.png
[p_comparison]: p_comparison.png
[c_comparison]: c_comparison.png
[fibonacci.c]: fibonacci.c
[fibonacci.py]: fibonacci.py
[fib_test_runner.py]: fib_test_runner.py
[equation1]: equation1.png
[equation2]: equation2.png
[Big_O]: Big_O.png
