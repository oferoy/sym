# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "symnmf.h"

#define DEFAULT_ITERS_NUM (300)
#define MAX_ITERS_NUM (1000)
#define BETA (0.5)
#define EPSILON (0.1)

double dist(double *p1, double *p2, int dim){  
    double distance = 0.0;
    int i;
    for(i = 0; i < dim; i++){
        distance += pow(p1[i]- p2[i], 2);
    }
    return distance;
}

double** initMatrix(int width, int height){
    int i, j;
    double** matrix = (double**)calloc(height, sizeof(double*));
    if(!matrix){
        printf("An Error Has Occurred\n");
        return NULL;
    }
    for(i=0; i<height; i++){
        matrix[i] = (double*)calloc(width, sizeof(double));
        if(!matrix[i]){
            for (j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            printf("An Error Has Occurred\n");
            return NULL;
        }
    }
    return matrix;
}

double** transpose(double** matrix, int height, int width){
    int i, j;
    double** transposed = initMatrix(height, width);
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
            transposed[j][i] = matrix[i][j];
        }
    }
    return transposed;
}

void freeMatrix(double** matrix, int limit)
{
    int j;
    for (j = 0; j < limit; j++) {
        free(matrix[j]);
    }  
    free(matrix);
}



double** matrixMult(double** A, double** B, int heightA, int widthA, int widthB) {
    int i, j, k;
    double sum = 0;
    double** matrixMult = initMatrix(heightA, widthB);
    for (i=0; i<heightA; i++) {
        for (j=0; j<widthB; j++) {
            for (k=0; k<widthA; k++) {
                sum += (A[i][k]*B[k][j]);
            }
            matrixMult[i][j] = sum;
            sum = 0;
        }
    }
    return matrixMult;
}

double** subMatrixes(double** mat1, double** mat2, int size)
{
    int i, j;
    double** matrixSub = initMatrix(size, size);
    for (i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            matrixSub[i][j] = mat1[i][j] - mat2[i][j];
        }
    }  
    return matrixSub;  
}

double squaredForbeniusNorm(double** matrix, int size)
{
    double sqNorm = 0;
    int i, j;
    for (i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++){
            sqNorm += pow(matrix[i][j], 2);
        }
    }
    return sqNorm;
}


double** computeSym(int numOfPoints, int dimension, double** pointsArr){
    int i, j;
    double** symMatrix = initMatrix(numOfPoints, numOfPoints);
    for(i = 0; i < numOfPoints; i++){
        for(j = 0; j < numOfPoints; j++){
            if (i == j) {
                symMatrix[i][j] = 0;
            }
            else {
                symMatrix[i][j] = exp(dist(pointsArr[i], pointsArr[j], dimension) / (-2));
            }
        }
    }
    return symMatrix;
}

double** computeDdg(int numOfPoints, int dimension, double** pointsArr) {
    int i, j;
    double sum = 0;
    double** symMatrix = sym(numOfPoints, dimension, pointsArr);
    double** ddgMatrix = initMatrix(numOfPoints, numOfPoints);
    for(i = 0; i < numOfPoints; i++){
        for(j = 0; j < numOfPoints; j++){
            sum += symMatrix[i][j];
        }
        ddgMatrix[i][i] = sum;
        sum = 0;
    }
    freeMatrix(symMatrix, numOfPoints);
    return ddgMatrix;
}

double** computeNorm(int numOfPoints, int dimension, double** pointsArr) {
    int i, j;
    double** normMatrix;
    double** symMatrix = sym(numOfPoints, dimension, pointsArr);
    double** ddgMatrix = ddg(numOfPoints, dimension, pointsArr);
    for (i=0; i< numOfPoints; i++) {
        ddgMatrix[i][i] = 1/sqrt(ddgMatrix[i][i]);
    }
    normMatrix = matrixMult(ddgMatrix, symMatrix, numOfPoints, numOfPoints, numOfPoints);
    normMatrix = matrixMult(normMatrix,ddgMatrix, numOfPoints, numOfPoints, numOfPoints);
    freeMatrix(symMatrix, numOfPoints);
    freeMatrix(ddgMatrix, numOfPoints);
    return normMatrix;
}

double** updateH(int numOfPoints, int dimension, double** H, double** W){
    int i, j;
    double nextH = initMatrix(numOfPoints, dimension);
    double** numerator = matrixMult(W, H, numOfPoints, numOfPoints, dimension);
    double** denominator = matrixMult(H, transpose(H, numOfPoints, dimension), numOfPoints, dimension, numOfPoints);
    denominator = matrixMult(denominator, H, numOfPoints, numOfPoints, dimension);
    for(i = 0; i<numOfPoints; i++){
        for(j=0; j<dimension; j++){
            nextH[i][j] = H[i][j]*(1-BETA+BETA*(numerator[i][j]/denominator[i][j]));
        }
    }
    return nextH;
}

double** optimizeH(int numOfPoints, int dimension, double** H, double** W)
{
    double** W = initMatrix(    )
}
   