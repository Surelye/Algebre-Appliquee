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

    cout << '\n';

    displayCayleyTable (CayleyTable);

    cout << '\n';

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

            case 7:
                matrixAddition ();
                break;

            case 8:
                matrixMultiplication ();
                break;

            case 9:
                transposeMatrix ();
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
    cout << " 2 - RELATION UNION\n";
    cout << " 3 - RELATION INTERSECT\n";
    cout << " 4 - RELATION COMPLEMENT\n";
    cout << " 5 - RELATION MULTIPLICATION\n";
    cout << " 6 - RELATION INVERSE\n";
    cout << " 7 - MATRIX ADDITION\n";
    cout << " 8 - MATRIX MULTIPLICATION\n";
    cout << " 9 - TRANSPOSE MATRIX\n";
    cout << "10 - INVERT MATRIX\n";
	cout << " 0 - EXIT\n\n";

	while (input != 0)
	{
		cin >> input;
		ops.push_back(input);
	}
	cout << "\n";

	opSwitch(ops);
}

int main ()
{
    opSelect ();

    return (EXIT_SUCCESS);
}