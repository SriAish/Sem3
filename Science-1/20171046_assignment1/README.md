# Random Walk Model (Computation)

## Problem

Two drunks start out at the origin, each having equal probability of making a left or a right. Find the probability of them meeting again after N steps. Plot P(N) vs. N for calculated and theoritical values of P(N).

## Solution

### Theoretical calculation

P(N) = (2N)! / ((N!)^2*(2^2N))

### Computational calculation

The drunks start at x = 0 for each experiment. A direction (either left or right) is chosen randomly and they take one step in that direction. If they meet, the count for that value of N is incremented. The graph P(N) vs. N is plotted both for theoretically calculated values of P(N) and computationally calculated values of P(N).  

## Requirements

Make sure **matplotlib** module is installed.

`pip3 install matplotlib`

## Running the code

`python3 2drunk_walk.py`
