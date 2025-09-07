# Simulation Checklist

Many of the easy ICPC problems reduce to an iterative simulation, like calculating the trajectory of a ball.  

There are several pitfalls that can lose you these easy points. Here is a checklist I use to minimize silly errors.
### 1. Normalize Inputs
- During input parsing, make sure that your units are correct and consistent (ms → ns, dollar → cents), and make sure you are *indexing consistently* (0- or 1- based)
- Replace floats with integers whenever possible (floating point precision errors will bite you.)

### 2. Fully Define the State
- You will want a consistent data structure that describes the state of the simulation at each iteration.  
    - Example: `{index, counter, timer, pointer, current sum/min/max}`

### 3. Choose How You Are Going To Iterate
- Iterating over every tick is usually naive and too slow. Only tick loop if `#ticks < 2e6`
- Often times you can iterate over "events": filter out ticks where nothing happens, then loop over the ones where something does. (sometimes you need a heap/PQ to sort events with custom comparator)

### 4. List Your Transitions/Rules
- Define exactly how your state updates for each event. 
- If multiple events occur simultaneously, define a tie-breaker so that state updates are consistent.

### 5. Ensure Your State Is Always Valid (Maintain Invariants)
- Things like "the stock must remain positive" or "no car can pass another" are ground truths about your state that can never be violated.
- Check them using `asserts` during local testing, then disable for submission.

### 6. Boundaries and Sentinels
- Countless times I have lost points because I forgot to do one last "flush" after looping over an array (e.g. taking the max *one more time* after the loop ends.) These are guard events and you should be mindful of when they need to be applied.
- When sweeping/folding/reducing/aggregating over an array, make sure that you set your answer to be a sentinel value, to ensure edge cases don't occur (e.g. finding min element → initialize answer to INT_MAX).

### 7. Numerical Safety
- Using `long long` for sums and products, or if you see large input sizes. 
- Always prefer integer math
- If you need to compare ratios, cross-multiply (`a/b > c/d → ad > cb`) to avoid precision errors.

### 8. Complexity Budget
- Problems come with input bounds. Use them to determine what kind of time complexity algorithm you need to shoot for. Here's my rule of thumb:
    - Assume C++ can perform 1e8 ~ 2^26 simple operations per second
        - N <= 10: anything (backtracking, factorial, brute force OK)
        - N <= 20: 2^N feasible
        - N = 30-40: 2^(N/2) OK
        - N <= 1e3: N^2 safe N^3 borderline feasible
        - N = 2-5e3: N^2 feasible
        - N = 1e4: N log N, N^2 borderline
        - N = 1e5: N log N, or N
        - N = 1e6: N or log N only


### 9. Adversarial Testing
- You don't want to lose points because of a nasty edge case. Be smart and make several adversarial test cases to catch those.
    - e.g. the empty set, when N is the min/max it can be, tie conditions, etc.
- Sometimes, it may be worth writing a **Brute-Force Oracle**, that works for small N, to check your work.
