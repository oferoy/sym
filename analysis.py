import sys
import kmeans as km
import symnmf as sn
from sklearn.metrics import silhouette_score

def getPyPointsFromFile(filename):
    matrix = []
    with open(filename, "r") as f:
        for line in f:
            line = line.strip()
            tokens = line.split(",")
            row = [float(token) for token in tokens]
            matrix.append(row)
    return matrix

k = int(sys.argv[1])
filename = sys.argv[2]
points = getPyPointsFromFile(filename)
kmeansLabels = km.kmeans(points, k)
symnmfLabels = sn.labels(points, k)
kmeansScore = silhouette_score(points, kmeansLabels)
symnmfScore = silhouette_score(points, symnmfLabels)
print("nmf: " + "%.4f"%symnmfScore)
print("kmeans: " + "%.4f"%kmeansScore)


