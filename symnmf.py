import sys
import math
import numpy as np

np.random.seed(1234)

def averageEntry(matrix, size):
    sum = 0
    for i in range(size):
        for j in range(size):
            sum += matrix[i][j]
    average = sum / (size * size)
    return average


def initH(W, n, k):
    boundary = 2 * math.sqrt(averageEntry(W, n) / k)
    H = np.zeros((n, k))
    for i in range(n):
        for j in range(k):
            H[i][j] = np.random.uniform(low=0, high=boundary)
    return H




