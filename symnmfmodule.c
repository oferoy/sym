# define PY_SSIZE_T_CLEAN
# include <Python.h>
# include "symnmf.h"

double** makeCMatrix(int height, int width, PyObject* pyMatrix){
    int i, j;
    PyObject *line, *item;
    double** matrix = (double **)malloc(height * sizeof(double *));
    if(!matrix){
        printf("An Error Has Occurred\n");
        return NULL;
    }
    for(i=0; i<height; i++)
    {
        matrix[i] = (double *)malloc(width * sizeof(double));
        if(!matrix[i]){
            for (j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            printf("An Error Has Occurred\n");
            return NULL;
        }
        line = PyList_GetItem(pyMatrix, i);
        for(j=0; j<width; j++)
        {
            item = PyList_GetItem(line, j);
            matrix[i][j] = PyFloat_AsDouble(item);
        }
    }
    return matrix;
}

static PyObject* makePyMatrix(int height, int width, double **cMatrix){
    int i, j;
    PyObject *pyMatrix, *line;
    
    pyMatrix = PyList_New(height); 
    for (i = 0; i < height; i++)
    {
        line = PyList_New(width);  
        for (j = 0; j < width; j++)
        {
            PyList_SetItem(line, j, PyFloat_FromDouble(cMatrix[i][j]));
        }
        PyList_SetItem(pyMatrix, i, line);  
    }
    return pyMatrix;

}

static PyObject* symnmf(PyObject* self, PyObject* args){
    PyObject *W, *H, *line, *pyFinalH;
    double **cWMatrix, **cHMatrix, **cFinalH;
    int numOfPoints, dimension;

    if(!PyArg_ParseTuple(args, "OO", &W, &H)){
        printf("An Error Has Occurred\n");
        return NULL;
    }
    numOfPoints = PyList_Size(W);
    line = PyList_GetItem(W, 0);
    dimension = PyList_Size(line);
    cWMatrix = makeCMatrix(numOfPoints, dimension, W);
    cHMatrix = makeCMatrix(numOfPoints, dimension, H);
    cFinalH = optimizeH(numOfPoints, dimension, cHMatrix, cWMatrix);
    pyFinalH = makePyMatrix(numOfPoints, dimension, cFinalH);
    freeMatrix(cHMatrix, numOfPoints);
    freeMatrix(cWMatrix, numOfPoints);
    freeMatrix(cFinalH, numOfPoints);
    return pyFinalH;
}

static PyObject* sym(PyObject* self, PyObject* args){
    PyObject *pointsArr, *line, *pySymMatrix;
    double **cPointsArr, **cSymMatrix;
    int numOfPoints, dimension;

    if(!PyArg_ParseTuple(args, "O", &pointsArr)){
        printf("An Error Has Occurred\n");
        return NULL;
    }
    numOfPoints = PyList_Size(pointsArr);
    line = PyList_GetItem(pointsArr, 0);
    dimension = PyList_Size(line);
    cPointsArr = makeCMatrix(numOfPoints, dimension);
    cSymMatrix = computeSym(numOfPoints, dimension, cPointsArr);
    pySymMatrix = makePyMatrix(numOfPoints, dimension, cSymMatrix);
    freeMatrix(cPointsArr, numOfPoints);
    freeMatrix(cSymMatrix, numOfPoints);
    return pySymMatrix;
}

static PyObject* ddg(PyObject* self, PyObject* args){
    PyObject *pointsArr, *line, *pyDdgMatrix;
    double **cPointsArr, **cDdgMatrix;
    int numOfPoints, dimension;

    if(!PyArg_ParseTuple(args, "O", &pointsArr)){
        printf("An Error Has Occurred\n");
        return NULL;
    }
    numOfPoints = PyList_Size(pointsArr);
    line = PyList_GetItem(pointsArr, 0);
    dimension = PyList_Size(line);
    cPointsArr = makeCMatrix(numOfPoints, dimension);
    cDdgMatrix = computeDdg(numOfPoints, dimension, cPointsArr);
    pyDdgMatrix = makePyMatrix(numOfPoints, dimension, cDdgMatrix);
    freeMatrix(cPointsArr, numOfPoints);
    freeMatrix(cDdgMatrix, numOfPoints);
    return pyDdgMatrix;
}

static PyObject* norm(PyObject* self, PyObject* args){
    PyObject *pointsArr, *line, *pyNormMatrix;
    double **cPointsArr, **cNormMatrix;
    int numOfPoints, dimension;

    if(!PyArg_ParseTuple(args, "O", &pointsArr)){
        printf("An Error Has Occurred\n");
        return NULL;
    }
    numOfPoints = PyList_Size(pointsArr);
    line = PyList_GetItem(pointsArr, 0);
    dimension = PyList_Size(line);
    cPointsArr = makeCMatrix(numOfPoints, dimension);
    cNormMatrix = computeNorm(numOfPoints, dimension, cPointsArr);
    pyNormMatrix = makePyMatrix(numOfPoints, dimension, cNormMatrix);
    freeMatrix(cPointsArr, numOfPoints);
    freeMatrix(cNormMatrix, numOfPoints);
    return pyNormMatrix;
}

static PyMethodDef symnmfMethods [] = {
    {"symnmf", (PyCFunction) symnmf, METH_VARARGS, PyDoc_STR("compute final H") },
    {"sym", (PyCFunction) sym, METH_VARARGS, PyDoc_STR("compute similarity matrix") },
    {"ddg", (PyCFunction) ddg, METH_VARARGS, PyDoc_STR("compute diagonal degree matrix") },
    {"norm", (PyCFunction) norm, METH_VARARGS, PyDoc_STR("compute normalized similarity matrix") },
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef symnmfmodule = {
    PyModuleDef_HEAD_INIT,
    "mysymnmf", 
    NULL, 
    -1,
    symnmfMethods
};

PyMODINIT_FUNC PyInit_mysymnmf(void)
{
    PyObject *m;
    m = PyModule_Create(&symnmfmodule);
    if (!m) {
        return NULL;
    }
    return m;
}