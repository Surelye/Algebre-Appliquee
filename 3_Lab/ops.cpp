#include <iostream>
#include <vector>

using namespace std;

int matrixDimension;
vector<int> objectSet;

void opSelect ();

void displayCayleyTable (vector<vector<int>> CayleyTable)
{
    int i, j;

    cout << "* ";
    for (i = 0; i < matrixDimension; ++i)
        cout << objectSet[i] << " ";
    cout << "\n";

    for (i = 0; i < matrixDimension; ++i)
    {
        cout << objectSet[i] << " ";

        for (j = 0; j < matrixDimension; ++j)
            cout << CayleyTable[i][j] << " ";

        cout << '\n';
    }
}

void getMatrix (vector<vector<int>>& CayleyTable)
{
    int i, j;
    int product;

    for (i = 0; i < matrixDimension; ++i)
    {
        vector<int> row;

        for (j = 0; j < matrixDimension; ++j)
        {
            cin >> product;
            row.push_back (product);
        }

        CayleyTable.push_back (row);
    }
}

void getObjectSet ()
{
    int i;
    int object;

    for (i = 0; i < matrixDimension; ++i)
    {
        cin >> object;
        objectSet.push_back (object);
    }
}

pair<vector<vector<int>>, vector<vector<int>>> constructTables (vector<vector<int>> CayleyTable, int object)
{
    int i, j;
    vector<vector<int>> leftTable (matrixDimension, vector<int>(matrixDimension, 0)), rightTable (matrixDimension, vector<int>(matrixDimension, 0));

    for (i = 0; i < matrixDimension; ++i)
        for (j = 0; j < matrixDimension; ++j)
        {
            leftTable[i][j] = CayleyTable[CayleyTable[i][object - 1] - 1][j];
            rightTable[i][j] = CayleyTable[i][CayleyTable[object - 1][j] - 1];
        }

    /*cout << "LEFT TABLE:\n";
    displayCayleyTable (leftTable);
    cout << '\n';

    cout << "RIGHT TABLE:\n";
    displayCayleyTable (rightTable);
    cout << '\n';*/

    return (make_pair (leftTable, rightTable));
}

bool checkAssociativity (vector<vector<int>> CayleyTable)
{
    int i;
    pair<vector<vector<int>>, vector<vector<int>>> tables;

    for (i = 0; i < objectSet.size (); ++i)
    {
        tables = constructTables (CayleyTable, objectSet[i]);

        if (tables.first != tables.second)
            return (false);
    }

    return (true);
}

bool checkCommutativity (vector<vector<int>> CayleyTable)
{
    int i, j;

    for (i = 0; i < matrixDimension; ++i)    
        for (j = i; j < matrixDimension; ++j)
            if (CayleyTable[i][j] != CayleyTable[j][i])
                return (false);

    return (true);    
}

bool checkIdempotency (vector<vector<int>> CayleyTable)
{
    int i;
    vector<int> idempotents;

    for (i = 0; i < matrixDimension; ++i)
        if (CayleyTable[i][i] == objectSet[i])
            idempotents.push_back (objectSet[i]);

    int idSize = idempotents.size ();

    cout << "IDEMPOTENTS OF THIS OPERATION ";
    if (idSize == 0)
        cout << "IS: EMPTY SET.\n";
    else if (idSize == 1)
        cout << "IS: " << idempotents[0] << ".\n";
    else if (idSize == objectSet.size ())
        cout << "IS: OBJECT SET. ";
    else 
    {
        cout << "ARE: ";

        for (i = 0; i < idSize; ++i)
            cout << idempotents[i] << (i == idSize - 1 ? ". " : ", ");
    }

    return (idSize == objectSet.size ());
}

void checkProperties ()
{
    int i;
    vector<vector<int>> CayleyTable;

    cout << "INPUT MATRIX DIMENSION:\n";
    cin >> matrixDimension;

    cout << "INPUT AN OBJECT SET:\n";
    getObjectSet ();

    cout << "INPUT MATRIX ELEMENTS:\n";
    getMatrix (CayleyTable);

    if (checkAssociativity (CayleyTable))
        cout << "OPERATION IS ASSOCIATIVE.\n";
    else cout << "OPERATION IS NOT ASSOCIATIVE.\n";

    if (checkCommutativity (CayleyTable))
        cout << "OPERATION IS COMMUTATIVE.\n";
    else cout << "OPERATION IS NOT COMMUTATIVE.\n";

    if (checkIdempotency (CayleyTable))
        cout << "OPERATION IS IDEMPOTENT.\n";
    else cout << "OPERATION IS NOT IDEMPOTENT.\n";


}

void getMatrixFiniteField (vector<vector<int>>& matrix, int fieldOrder, int fDim, int sDim)
{
    int i, j, elt;

    for (i = 0; i < fDim; ++i)
    {
        vector<int> row;

        for (j = 0; j < sDim; ++j)
        {
            cin >> elt;
            row.push_back (elt % fieldOrder);
        }

        matrix.push_back (row);
    }
}

void displayMatrix (vector<vector<int>> matrix)
{
    int i, j;

    for (i = 0; i < matrix.size (); ++i)
    {
        for (j = 0; j < matrix[i].size (); ++j)
            cout << matrix[i][j] << " ";

        cout << '\n';
    }
}

vector<vector<int>> addMatricesMachinerie (vector<vector<int>> lM, vector<vector<int>> rM, int fieldOrder)
{
    int i, j;
    vector<vector<int>> resM (lM.size (), vector<int> (lM[0].size (), 0));

    for (i = 0; i < lM.size (); ++i)    
        for (j = 0; j < lM[i].size (); ++j)
            resM[i][j] = (lM[i][j] + rM[i][j]) % fieldOrder;

    return (resM);
}

void matrixAddition ()
{
    int i, j, fieldOrder, firstDimension, secondDimension;
    vector<vector<int>> lMatrix, rMatrix, resMatrix;

    cout << "INPUT MATRIX FIRST DIMENSION:\n";
    cin >> firstDimension;

    cout << "INPUT MATRIX SECOND DIMENSION:\n";
    cin >> secondDimension;

    cout << "INPUT THE ORDER OF A FINITE FIELD:\n";
    cin >> fieldOrder;

    cout << "INPUT THE ELEMENTS OF THE FIRST MATRIX:\n";
    getMatrixFiniteField (lMatrix, fieldOrder, firstDimension, secondDimension);
    cout << "INPUT THE ELEMENTS OF THE SECOND MATRIX:\n";
    getMatrixFiniteField (rMatrix, fieldOrder, firstDimension, secondDimension);

    resMatrix = addMatricesMachinerie (lMatrix, rMatrix, fieldOrder);

    cout << "THE RESULT OF MATRIX ADDITION IS:\n";
    displayMatrix (resMatrix);
}

vector<vector<int>> multiplyMatricesMachinerie (vector<vector<int>> lM, vector<vector<int>> rM, int fieldOrder)
{
    int i, j, k;
    vector<vector<int>> resM (lM.size (), vector<int> (rM[0].size (), 0));

    for (i = 0; i < lM.size (); ++i)
        for (j = 0; j < rM[0].size (); ++j)
        {
            int product = 0;

            for (k = 0; k < lM[0].size (); ++k)
                product += (lM[i][k] * rM[k][j]);

            resM[i][j] = (product % fieldOrder);
        }

    return (resM);
}

void matrixMultiplication ()
{
    int i, j, fieldOrder, fMatrixFDim, fMatrixSDim, sMatrixFDim, sMatrixSDim;
    vector<vector<int>> lMatrix, rMatrix, resMatrix;

    cout << "INPUT THE FIRST DIMENSION OF THE FIRST MATRIX:\n";
    cin >> fMatrixFDim;

    cout << "INPUT THE SECOND DIMENSION OF THE FIRST MATRIX:\n";
    cin >> fMatrixSDim;

    cout << "INPUT THE FIRST DIMENSION OF THE SECOND MATRIX:\n";
    cin >> sMatrixFDim;

    cout << "INPUT THE SECOND DIMENSION OF THE SECOND MATRIX:\n";
    cin >> sMatrixSDim;

    if (fMatrixSDim != sMatrixFDim)
    {
        cout << "WRONG INPUT. THE SECOND DIMENSION OF THE FIRST MATRIX DOES NOT CORRESPOND TO THE FIRST DIMENSION OF THE SECOND MATRIX.\n";
        return;
    }

    cout << "INPUT THE ORDER OF A FINITE FIELD:\n";
    cin >> fieldOrder;

    cout << "INPUT THE ELEMENTS OF THE FIRST MATRIX:\n";
    getMatrixFiniteField (lMatrix, fieldOrder, fMatrixFDim, fMatrixSDim);
    cout << "INPUT THE ELEMENTS OF THE SECOND MATRIX:\n";
    getMatrixFiniteField (rMatrix, fieldOrder, sMatrixFDim, sMatrixSDim);    

    resMatrix = multiplyMatricesMachinerie (lMatrix, rMatrix, fieldOrder);

    cout << "THE RESULT OF MATRIX MULTIPLICATION IS:\n";
    displayMatrix (resMatrix);
}

vector<vector<int>> transposeMatrixMachinerie (vector<vector<int>> matrix)
{
    int i, j;
    vector<vector<int>> rM (matrix[0].size (), vector<int> (matrix.size (), 0));

    for (i = 0; i < matrix[0].size (); ++i)
    {
        vector<int> column;

        for (j = 0; j < matrix.size (); ++j)
            column.push_back (matrix[j][i]);

        rM[i] = column;
    }

    return (rM);
}

void transposeMatrix ()
{
    int i, j, fieldOrder, fDim, sDim;
    vector<vector<int>> matrix, resMatrix;

    cout << "INPUT THE FIRST DIMENSION OF THE MATRIX:\n";
    cin >> fDim;

    cout << "INPUT THE SECOND DIMENSION OF THE MATRIX:\n";
    cin >> sDim;

    cout << "INPUT THE ORDER OF A FINITE FIELD:\n";
    cin >> fieldOrder;

    cout << "INPUT THE ELEMENTS OF THE MATRIX:\n";
    getMatrixFiniteField (matrix, fieldOrder, fDim, sDim);

    resMatrix = transposeMatrixMachinerie (matrix);

    cout << "THE RESULT OF MATRIX TRANSPOSITION IS:\n";
    displayMatrix (resMatrix);
}

void getBinaryRelationMatrix (vector<vector<int>>& binRelMat)
{
    int i, j;

    for (i = 0; i < binRelMat.size (); ++i)
        for (j = 0; j < binRelMat[i].size (); ++j)
            cin >> binRelMat[i][j];
}

vector<vector<int>> getBinaryRelationIntersection (vector<vector<int>> fM, vector<vector<int>> sM)
{
    int i, j, rowsNum = fM.size (), colsNum = fM[0].size ();
    vector<vector<int>> intersectionMatrix (rowsNum, vector<int> (colsNum, 0));

    for (i = 0; i < rowsNum; ++i)
        for (j = 0; j < colsNum; ++j)
            intersectionMatrix[i][j] = ((fM[i][j] == 1) && (sM[i][j] == 1) ? 1 : 0);

    return (intersectionMatrix);
}

void binaryRelationIntersect ()
{
    unsigned short fDim, sDim;

    cout << "INPUT THE FIRST DIMENSION OF YOUR BINARY RELATION MATRIX:\n";
    cin >> fDim;

    cout << "INPUT THE SECOND DIMENSION OF YOUR BINARY RELATION MATRIX:\n";
    cin >> sDim;

    vector<vector<int>> fBinRel (fDim, vector<int> (sDim, 0)),
                        sBinRel (fDim, vector<int> (sDim, 0)),
                        intersectMatrix;

    cout << "INPUT THE FIRST BINARY RELATION MATRIX:\n";
    getBinaryRelationMatrix (fBinRel);

    cout << "INPUT THE SECOND BINARY RELATION MATRIX:\n";
    getBinaryRelationMatrix (sBinRel);

    intersectMatrix = getBinaryRelationIntersection (fBinRel, sBinRel);
    
    cout << "THE RESULT OF INTERSECTION OF YOUR BINARY RELATIONS IS:\n";
    displayMatrix (intersectMatrix);
}

vector<vector<int>> getBinaryRelationUnion (vector<vector<int>> fM, vector<vector<int>> sM)
{
    int i, j, rowsNum = fM.size (), colsNum = fM[0].size ();
    vector<vector<int>> unionMatrix (rowsNum, vector<int> (colsNum, 0));

    for (i = 0; i < rowsNum; ++i)
        for (j = 0; j < colsNum; ++j)
            unionMatrix[i][j] = ((fM[i][j] == 1) || (sM[i][j] == 1) ? 1 : 0);

    return (unionMatrix);
}

void binaryRelationUnion ()
{
    unsigned short fDim, sDim;

    cout << "INPUT THE FIRST DIMENSION OF YOUR BINARY RELATION MATRIX:\n";
    cin >> fDim;

    cout << "INPUT THE SECOND DIMENSION OF YOUR BINARY RELATION MATRIX:\n";
    cin >> sDim;

    vector<vector<int>> fBinRel (fDim, vector<int> (sDim, 0)),
                        sBinRel (fDim, vector<int> (sDim, 0)),
                        unionMatrix;

    cout << "INPUT THE FIRST BINARY RELATION MATRIX:\n";
    getBinaryRelationMatrix (fBinRel);

    cout << "INPUT THE SECOND BINARY RELATION MATRIX:\n";
    getBinaryRelationMatrix (sBinRel);

    unionMatrix = getBinaryRelationUnion (fBinRel, sBinRel);

    cout << "THE RESULT OF UNION OF YOUR BINARY RELATIONS IS:\n";
    displayMatrix (unionMatrix);
}

vector<vector<int>> getBinaryRelationComplement (vector<vector<int>> binRelMat)
{
    int i, j, rowsNum = binRelMat.size (), colsNum = binRelMat[0].size ();
    vector<vector<int>> complementMatrix (rowsNum, vector<int> (colsNum, 0));

    for (i = 0; i < rowsNum; ++i)
        for (j = 0; j < colsNum; ++j)
            complementMatrix[i][j] = 1 - binRelMat[i][j];

    return (complementMatrix);
}

void binaryRelationComplement ()
{
    unsigned short fDim, sDim;

    cout << "INPUT THE FIRST DIMENSION OF YOUR BINARY RELATION MATRIX:\n";
    cin >> fDim;

    cout << "INPUT THE SECOND DIMENSION OF YOUR BINARY RELATION MATRIX:\n";
    cin >> sDim;

    vector<vector<int>> binRel (fDim, vector<int> (sDim, 0)),
                        complementMatrix;

    cout << "INPUT THE BINARY RELATION MATRIX:\n";
    getBinaryRelationMatrix (binRel);

    complementMatrix = getBinaryRelationComplement (binRel);

    cout << "THE COMPLEMENT OF YOUR BINARY RELATIONS IS:\n";
    displayMatrix (complementMatrix);
}

vector<vector<int>> transposeBinaryRelationMatrix (vector<vector<int>> binRelMat)
{
    int i, j;
    vector<vector<int>> transposedMatrix;

    for (i = 0; i < binRelMat[0].size (); ++i)
    {
        vector<int> column;

        for (j = 0; j < binRelMat.size (); ++j)
            column.push_back (binRelMat[j][i]);

        transposedMatrix.push_back (column);
    }

    return (transposedMatrix);
}

void binaryRelationInverse ()
{
    unsigned short fDim, sDim;

    cout << "INPUT THE FIRST DIMENSION OF YOUR BINARY RELATION MATRIX:\n";
    cin >> fDim;

    cout << "INPUT THE SECOND DIMENSION OF YOUR BINARY RELATION MATRIX:\n";
    cin >> sDim;

    vector<vector<int>> binRel (fDim, vector<int> (sDim, 0)),
                        transposedMatrix;

    cout << "INPUT THE BINARY RELATION MATRIX:\n";
    getBinaryRelationMatrix (binRel);

    transposedMatrix = transposeBinaryRelationMatrix (binRel);

    cout << "THE COMPLEMENT OF YOUR BINARY RELATIONS IS:\n";
    displayMatrix (transposedMatrix);
}

vector<vector<int>> getBinaryRelationMultiplication (vector<vector<int>> fBinRel, vector<vector<int>> sBinRel)
{
    int i, j, k, product, rowsNum = fBinRel.size (), colsNum = sBinRel[0].size ();
    vector<vector<int>> boolMultiplicationMatrix (rowsNum, vector<int> (colsNum, 0));

    for (i = 0; i < rowsNum; ++i)
        for (j = 0; j < colsNum; ++j)
        {
            product = 0;

            for (k = 0; k < fBinRel[0].size (); ++k)
                product += fBinRel[i][k] * sBinRel[k][j];

            boolMultiplicationMatrix[i][j] = (product > 0 ? 1 : 0);
        }

    return (boolMultiplicationMatrix);
}

void binaryRelationMultiplication ()
{
    unsigned short fMatFDim, fMatSDim, sMatFDim, sMatSDim;

    cout << "INPUT THE FIRST DIMENSION OF YOUR FIRST BINARY RELATION MATRIX:\n";
    cin >> fMatFDim;

    cout << "INPUT THE SECOND DIMENSION OF YOUR FIRST BINARY RELATION MATRIX:\n";
    cin >> fMatSDim;

    cout << "INPUT THE FIRST DIMENSION OF YOUR SECOND BINARY RELATION MATRIX:\n";
    cin >> sMatFDim;

    cout << "INPUT THE SECOND DIMENSION OF YOUR SECOND BINARY RELATION MATRIX:\n";
    cin >> sMatSDim;

    if (fMatSDim != sMatFDim)
    {
        cout << "THE SECOND DIMENSION OF YOUR FIRST BINARY RELATION MATRIX DOES NOT CORRESPOND TO THE FIRST DIMENSION OF YOUR SECOND BINARY RELATION MATRIX. MATRIX MULTIPLICATION CANNOT BE FOUND.\n";
        return;
    }

    vector<vector<int>> fBinRel (fMatFDim, vector<int> (fMatSDim, 0)),
                        sBinRel (sMatFDim, vector<int> (sMatSDim, 0)),
                        boolMultiplicationMatrix;

    cout << "INPUT THE FIRST BINARY RELATION MATRIX:\n";
    getBinaryRelationMatrix (fBinRel);

    cout << "INPUT THE SECOND BINARY RELATION MATRIX:\n";
    getBinaryRelationMatrix (sBinRel);

    boolMultiplicationMatrix = getBinaryRelationMultiplication (fBinRel, sBinRel);

    cout << "THE RESULT OF BINARY RELATION MULTIPLICATION IS:\n";
    displayMatrix (boolMultiplicationMatrix);
}

vector<vector<int>> getMinor (int columnIdx, vector<vector<int>> matrix)
{
    int i, j;
    vector<vector<int>> minor;

    for (i = 1; i < matrix.size(); ++i)
    {
        vector<int> row;

        for (j = 0; j < matrix.size(); ++j)
            if (j != columnIdx)
                row.push_back (matrix[i][j]);

        minor.push_back (row);
    }

    return (minor);
}

int computeDet (vector<vector<int>> matrix)
{
    if (matrix.size() == 1)
        return (matrix[0][0]);

    int det = 0, multiplier = 1, i;

    for (i = 0; i < matrix.size(); ++i)
    {
        int elt = matrix[0][i];

        if (elt != 0)
            det += multiplier * elt * computeDet (getMinor (i, matrix));
        
        multiplier *= -1;
    }

    return (det);
}

void gcdExtended (int a, int b, int& x, int& y)
{
    if (a == 0) { x = 0; y = 1; return; }

    int x_1, y_1;
    gcdExtended (b % a, a, x_1, y_1);

    x = y_1 - (b / a) * x_1;
    y = x_1;

    return;
}

vector<vector<int>> getMinorExtended (vector<vector<int>> matrix, int rowIdx, int colIdx)
{
    int i, j, matrixSize = matrix.size ();
    vector<vector<int>> minor;

    for (i = 0; i < matrixSize; ++i)
    {
        if (i == rowIdx) continue;
        vector<int> row;

        for (j = 0; j < matrixSize; ++j)
        {
            if (j == colIdx) continue;
            row.push_back (matrix[i][j]);
        }

        minor.push_back (row);
    }

    return (minor);
}

vector<vector<int>> getConjugateMatrix (vector<vector<int>> matrix)
{
    int i, j;
    short sign = 1;
    bool evenDimensionFlag = (matrix.size () % 2 == 0);
    vector<vector<int>> conjugateMatrix (matrixDimension, vector<int> (matrixDimension, 0));

    for (i = 0; i < matrixDimension; ++i)
    {
        for (j = 0; j < matrixDimension; ++j)
        {
            conjugateMatrix[i][j] = sign * computeDet (getMinorExtended (matrix, i, j));
            sign *= -1;
        }
        sign *= (evenDimensionFlag ? -1 : 1);
    }

    return (transposeMatrixMachinerie (conjugateMatrix));
}

void reduceMatrix (vector<vector<int>>& matrix, int fieldOrder, int detInverse)
{
    int i, j;

    for (i = 0; i < matrix.size (); ++i)
        for (j = 0; j < matrix.size (); ++j)
        {
            matrix[i][j] *= detInverse;
            matrix[i][j] %= fieldOrder;

            if (matrix[i][j] < 0)
                matrix[i][j] += fieldOrder;
        }
}

void invertMatrix ()
{
    unsigned int fieldOrder;
    int det, detInverse = 0, dummyVariable = 0;
    vector<vector<int>> inputMatrix, conjugateMatrix;

    cout << "INPUT THE DIMENSION OF YOUR MATRIX:\n";
    cin >> matrixDimension;

    cout << "INPUT THE FIELD ORDER:\n";
    cin >> fieldOrder;

    cout << "INPUT YOUR MATRIX:\n";
    getMatrix (inputMatrix);

    det = computeDet (inputMatrix);

    if (det % fieldOrder == 0)
    {
        cout << "MATRIX HAS ZERO DETERMINANT. INVERSE MATRIX CANNOT BE FOUND.\n";
        return;
    }

    while (det < 0)
        det += fieldOrder;

    gcdExtended (det, fieldOrder, detInverse, dummyVariable);
    conjugateMatrix = getConjugateMatrix (inputMatrix);
    reduceMatrix (conjugateMatrix, fieldOrder, detInverse);

    cout << "INVERSE MATRIX IS:\n";
    displayMatrix (conjugateMatrix);
}

void displayLeftCayleyTablesDistrib (vector<vector<int>> lT, vector<vector<int>> rT, int curEl)
{
    int i, j;

    cout << "x * (b + c) TABLE FOR ELEMENT " << curEl << ":\n";
    for (i = 0; i < matrixDimension; ++i)
    {
        for (j = 0; j < matrixDimension; ++j)
            cout << lT[i][j] << " ";
        cout << '\n';
    }

    cout << "(x * b) + (x * c) TABLE FOR ELEMENT " << curEl << ":\n";
    for (i = 0; i < matrixDimension; ++i)
    {
        for (j = 0; j < matrixDimension; ++j)
            cout << rT[i][j] << " ";
        cout << '\n';
    }
}

bool constructLeftTables (vector<vector<int>> mCT, vector<vector<int>> aCT, int curEl)
{
    int j, k;
    vector<vector<int>> lTable (matrixDimension, vector<int> (matrixDimension, 0)), 
                        rTable (matrixDimension, vector<int> (matrixDimension, 0));

    for (j = 0; j < matrixDimension; ++j)
        for (k = 0; k < matrixDimension; ++k)
        {
            lTable[j][k] = mCT[curEl][aCT[j][k]];
            rTable[j][k] = aCT[mCT[curEl][j]][mCT[curEl][k]];
        }

    // displayLeftCayleyTablesDistrib (lTable, rTable, curEl);

    return (lTable == rTable);
}

void displayRightCayleyTablesDistrib (vector<vector<int>> lT, vector<vector<int>> rT, int curEl)
{
    int i, j;

    cout << "(b + c) * x TABLE FOR ELEMENT " << curEl << ":\n";
    for (i = 0; i < matrixDimension; ++i)
    {
        for (j = 0; j < matrixDimension; ++j)
            cout << lT[i][j] << " ";
        cout << '\n';
    }

    cout << "(b * x) + (c * x) TABLE FOR ELEMENT " << curEl << ":\n";
    for (i = 0; i < matrixDimension; ++i)
    {
        for (j = 0; j < matrixDimension; ++j)
            cout << rT[i][j] << " ";
        cout << '\n';
    }
}

bool constructRightTables (vector<vector<int>> mCT, vector<vector<int>> aCT, int curEl)
{
    int j, k;
    vector<vector<int>> lTable (matrixDimension, vector<int> (matrixDimension, 0)), 
                        rTable (matrixDimension, vector<int> (matrixDimension, 0));

    for (j = 0; j < matrixDimension; ++j)
        for (k = 0; k < matrixDimension; ++k)
        {
            lTable[j][k] = mCT[aCT[j][k]][curEl];
            rTable[j][k] = aCT[mCT[j][curEl]][mCT[k][curEl]];
        }

    // displayRightCayleyTablesDistrib (lTable, rTable, curEl);

    return (lTable == rTable);
}

void checkDistributivityMachinerie (vector<vector<int>> mCT, vector<vector<int>> aCT) // multiplication Cayley table, addition Cayley table
{
    int i, j, k;
    bool flagL = true, flagR = true;

    if (checkCommutativity (mCT))
    {
        for (i = 0; i < matrixDimension; ++i)
            if (!constructLeftTables (mCT, aCT, i))
            {
                cout << "OPERATION IS NOT DISTRIBUTIVE.\n";
                return;
            }

        cout << "OPERATION IS DISTRIBUTIVE.\n";
    }
    else 
    {
        for (i = 0; i < matrixDimension; ++i)
            if (!constructLeftTables (mCT, aCT, i))
            {
                cout << "OPERATION IS NOT LEFT-DISTRIBUTIVE.\n";
                flagL = false;
                break;
            }
        
        if (flagL)
            cout << "OPERATION IS LEFT-DISTRIBUTIVE.\n";

        for (i = 0; i < matrixDimension; ++i)
            if (!constructRightTables (mCT, aCT, i))
            {
                cout << "OPERATION IS NOT RIGHT-DISTRIBUTIVE.\n";
                flagR = false;
                break;
            }

        if (flagR)
            cout << "OPERATION IS RIGHT-DISTRIBUTIVE.\n";

        if (flagL && flagR)
            cout << "OPERATION IS DISTRIBUTIVE.\n";
    }
}

/*1 1 1 1 1 
1 2 3 4 5
1 3 5 2 4
1 4 2 5 3
1 5 4 3 2*/

void checkDistributivity ()
{
    int i;
    vector<vector<int>> multOpCayleyTable, addOpCayleyTable;

    cout << "INPUT MATRIX DIMENSION:\n";
    cin >> matrixDimension;

    cout << "INPUT THE CAYLEY TABLE OF THE MULTIPLICATION (*) OPERATION:\n"; // x * (y + z)
    getMatrix (multOpCayleyTable);

    cout << "INPUT THE CAYLEY TABLE OF THE ADDITION (+) OPERATION:\n";
    getMatrix (addOpCayleyTable);

    checkDistributivityMachinerie (multOpCayleyTable, addOpCayleyTable);
}

void opSwitch (vector<int> ops)
{
    int i;
	char choice = '.';

	for (i = 0; i < ops.size (); ++i)
	{
		switch (ops[i])
		{
			case 1:				
				checkProperties ();
				break;

            case 2:
                checkDistributivity ();
                break;

            case 3:
                binaryRelationUnion ();
                break;

            case 4:
                binaryRelationIntersect ();
                break;

            case 5:
                binaryRelationComplement ();
                break;

            case 6:
                binaryRelationMultiplication ();
                break;

            case 7:
                binaryRelationInverse ();
                break;

            case 8:
                matrixAddition ();
                break;

            case 9:
                matrixMultiplication ();
                break;

            case 10:
                transposeMatrix ();
                break;

            case 11:
                invertMatrix ();
                break;

			default:
				break;
		}
	}

	cout << "Again ? y/n:\n";
	while (choice != 'y' && choice != 'n')
	{
		cin >> choice;
		cout << "\n";
	}

	if (choice == 'y')
		opSelect ();
}

void opSelect ()
{
    int input = -1;
	vector<int> ops;

	cout << " 1 - CHECK PROPERTIES\n";
    cout << " 2 - CHECK DISTRIBUTIVITY\n";
    cout << " 3 - RELATION UNION\n";
    cout << " 4 - RELATION INTERSECT\n";
    cout << " 5 - RELATION COMPLEMENT\n";
    cout << " 6 - RELATION MULTIPLICATION\n";
    cout << " 7 - RELATION INVERSE\n";
    cout << " 8 - MATRIX ADDITION\n";
    cout << " 9 - MATRIX MULTIPLICATION\n";
    cout << "10 - TRANSPOSE MATRIX\n";
    cout << "11 - INVERT MATRIX\n";
	cout << " 0 - EXIT\n\n";

	while (input != 0)
	{
		cin >> input;
		ops.push_back (input);
	}
	cout << "\n";

	opSwitch (ops);
}

int main ()
{
    opSelect ();

    return (EXIT_SUCCESS);
}
