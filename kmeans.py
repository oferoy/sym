import math
EPSILON = 0.0001
ITER = 300


def dist(p1, p2):
    dimension = len(p1)
    dist = 0.0
    for i in range(dimension):
        dist += math.pow(p1[i] - p2[i], 2)
    return math.sqrt(dist)

def kmeans(pointsArr, k):
    numOfPoints = len(pointsArr)
    dimension = len(pointsArr[0])
    centroidsArr = []
    for i in range(k):
        centroidsArr.append(pointsArr[i])

    for it in range(ITER):
        newCentroids = [[0.0] * dimension for _ in range(k)]
        
        countArr =[0]
        for i in range(k-1):
            countArr.append(0)
        for point in pointsArr:
            closestCentIndex = 0
            #calculate the distance of the point from all of the centroids and find the closest one
            minDist = dist(centroidsArr[0], point)
            for index in range(len(centroidsArr)):
                currDist = dist(centroidsArr[index], point)
                #found a closer centroid
                if currDist < minDist:
                    #update centroid
                    closestCentIndex = index
                    minDist = currDist
            countArr[closestCentIndex] += 1
            for d in range(dimension):
                newCentroids[closestCentIndex][d] += point[d]

        for cl in range(k):
            for dim in range(dimension):
                newCentroids[cl][dim] /= countArr[cl]

        
        smallerThanEps = True
        for c in range(len(centroidsArr)):
            if(abs(dist(newCentroids[c],centroidsArr[c])) >= EPSILON):
                smallerThanEps = False
        if(smallerThanEps):
            break
        

    centroidsArr = newCentroids
    labels = []
    for point in pointsArr:
        distances = [dist(point, cent) for cent in centroidsArr]
        labels.append(distances.index(min(distances)))

    return labels