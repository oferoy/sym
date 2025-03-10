import sys
import math
import numpy as np
import mysymnmf as sn

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


def getPyPointsFromFile(filename):
    matrix = []
    with open(filename, "r") as f:
        for line in f:
            line = line.strip()
            tokens = line.split(",")
            row = [float(token) for token in tokens]
            matrix.append(row)
    return matrix

def printMatrix(matrix):
    height = len(matrix)
    width = len(matrix[0])
    for i in range(height):
        for j in range(width - 1):
            formatted = "%.4f"%matrix[i][j]
            print(f"{formatted},", end="")
        formatted = "%.4f"%matrix[i][width - 1]
        print(formatted)


k = int(sys.argv[1])
goal = sys.argv[2]
if(len(sys.argv) > 3):
    filename = sys.argv[3]
    pointsArr = getPyPointsFromFile(filename)

def computeH(points, k):
    numOfPoints = len(points)
    W = sn.norm(points)
    H = initH(W, numOfPoints, k)
    H = H.tolist()
    out = sn.symnmf(W, H, k)
    return out

if(goal == "sym"):
    out = sn.sym(pointsArr)
    printMatrix(out)

elif(goal == "ddg"):
    out = sn.ddg(pointsArr)
    printMatrix(out)

elif(goal == "norm"):
    out = sn.norm(pointsArr)
    printMatrix(out)

elif(goal == "symnmf"):
    out = computeH(pointsArr, k)
    printMatrix(out)
    

def labels(points, k):
    H = computeH(points, k)
    labels = []
    for i in range(len(points)):
        max = H[i][0]
        maxIdx = 0
        for j in range(1, k):
            if(H[i][j] > max):
                max = H[i][j]
                maxIdx = j
        labels.append(maxIdx) 
    return labels      








