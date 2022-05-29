#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

int matrixDimension;
vector<char> attributeSet;

void getMatrix(vector<vector<int>>& adjMatrix)
{
	int i, j, placeholderEl;

	cout << "INPUT THE ELEMENTS OF YOUR MATRIX:\n";

	for (i = 0; i < matrixDimension; ++i)
	{
		vector<int> rowPlaceholder;

		for (j = 0; j < matrixDimension; ++j)
		{
			cin >> placeholderEl;
			rowPlaceholder.push_back(placeholderEl);
		}

		adjMatrix.push_back(rowPlaceholder);
	}
}

void displayMatrix(vector<vector<int>> adjMatrix)
{
	int i, j;

	for (i = 0; i < adjMatrix.size(); ++i)
	{
		for (j = 0; j < adjMatrix[i].size(); ++j)
			cout << adjMatrix[i][j] << " ";

		cout << "\n";
	}

	cout << "\n";
}

map<int, set<int>> convertToAdjList(vector<vector<int>> adjMatrix)
{
	int i, j;
	map<int, set<int>> adjList;

	for (i = 0; i < matrixDimension; ++i)
	{
		set<int> placeholderSet;
		adjList[i + 1] = placeholderSet;

		for (j = 0; j < matrixDimension; ++j)
			if (adjMatrix[i][j] == 1)
				adjList[i + 1].insert(j + 1);
	}

	return (adjList);
}

void displayAdjList(map<int, set<int>> adjList)
{
	int i;
	set<int> ::iterator it;

	cout << "YOUR BINARY RELATION IS:\n";

	for (auto element : adjList)
	{
		it = element.second.begin();

		for (i = 0; it != element.second.end(); ++it, ++i)
			printf("(%d; %d)%c ", element.first, *it, (i == element.second.size() - 1) ? '.' : ',');
	}

	cout << "\n";
}

vector<vector<int>> convertToMatrix(map<int, set<int>> adjList)
{
	int i;
	vector<vector<int>> adjMatrix;
	set<int> ::iterator it;
	
	for (auto element : adjList)
	{
		it = element.second.begin();
		vector<int> rowPlaceholder(matrixDimension, 0);

		for (; it != element.second.end(); ++it)
			rowPlaceholder[*it - 1] = 1;

		adjMatrix.push_back(rowPlaceholder);
	}

	return (adjMatrix);
}

map<int, set<int>> reflexiveClosure(map<int, set<int>> binaryRelation)
{
	int i, placeholder;
	set<int> ::iterator it;

	for (auto element : binaryRelation)
	{
		placeholder = element.first;

		binaryRelation[element.first].insert(element.first);
	}

	return binaryRelation;
}

map<int, set<int>> symmetricClosure(map<int, set<int>> binaryRelation)
{
	int i;
	set<int> ::iterator it;

	for (auto element : binaryRelation)
	{
		it = element.second.begin();

		for (; it != element.second.end(); ++it)
			binaryRelation[*it].insert(element.first);
	}

	return binaryRelation;
}

map<int, set<int>> transitiveClosureMachinery(map<int, set<int>> binaryRelation)
{
	set<int> ::iterator it, itHelper;

	for (auto element : binaryRelation)
	{
		it = element.second.begin();

		for (; it != element.second.end(); ++it)
		{
			itHelper = binaryRelation[*it].begin();

			for (; itHelper != binaryRelation[*it].end(); ++itHelper)
				binaryRelation[element.first].insert(*itHelper);
		}
	}

	return binaryRelation;
}

bool isTransitive(map<int, set<int>> binaryRelation)
{
	bool isTransitive = false;
	set<int> ::iterator it, itHelper, itSup;

	for (auto element : binaryRelation)
	{
		it = element.second.begin();

		for (; it != element.second.end(); ++it)
		{
			if (!binaryRelation[*it].empty())
			{
				itHelper = binaryRelation[*it].begin();

				for (; itHelper != binaryRelation[*it].end(); ++itHelper)
				{
					itSup = element.second.begin();
					isTransitive = false;

					for (; itSup != element.second.end(); ++itSup)
						if (*itHelper == *itSup)
							isTransitive = !isTransitive;

					if (!isTransitive)						
						return false;
					
				}
			}
		}
	}

	return true;
}

map<int, set<int>> transitiveClosure(map<int, set<int>> binaryRelation)
{
	while (!isTransitive(binaryRelation))
		binaryRelation = transitiveClosureMachinery(binaryRelation);

	return binaryRelation;
}

map<int, set<int>> equivalenceClosureMachinery(map<int, set<int>> binaryRelation)
{
	return transitiveClosure(symmetricClosure(reflexiveClosure(binaryRelation)));
}

void equivalenceClosure(vector<vector<int>>& adjMatrix)
{	
	map<int, set<int>> adjList = convertToAdjList(adjMatrix);
	adjList = equivalenceClosureMachinery(adjList);
	adjMatrix = convertToMatrix(adjList);
}

vector<bool> visited;
vector<int> exitOrder, component;

vector<vector<int>> convertMatrixToAdjVector(vector<vector<int>> adjMatrix)
{
	int i, j;
	vector<vector<int>> adjVector;
	
	for (i = 0; i < adjMatrix.size(); ++i)
	{
		vector<int> rowPlaceholder;

		for (j = 0; j < adjMatrix[i].size(); ++j)
			if (adjMatrix[i][j] == 1)
				rowPlaceholder.push_back(j);

		adjVector.push_back(rowPlaceholder);
	}

	return (adjVector);
}

void orderDFS(vector<vector<int>> adjVector, int vertexNum)
{
	visited[vertexNum] = true;

	for (int i = 0; i < adjVector[vertexNum].size(); ++i)
		if (!visited[adjVector[vertexNum][i]])
			orderDFS(adjVector, adjVector[vertexNum][i]);

	exitOrder.push_back(vertexNum);
}

void getComponentDFS(vector<vector<int>> adjMatrixTransposed, int vertexNum) 
{
	visited[vertexNum] = true;
	component.push_back(vertexNum);

	for (int i = 0; i < adjMatrixTransposed[vertexNum].size(); ++i)
		if (!visited[adjMatrixTransposed[vertexNum][i]])
			getComponentDFS(adjMatrixTransposed, adjMatrixTransposed[vertexNum][i]);
}

vector<vector<int>> transposeMatrix(vector<vector<int>> adjMatrix)
{
	int i, j;
	vector<vector<int>> transposedMatrix;

	for (i = 0; i < adjMatrix.size(); ++i)
	{
		vector<int> columnPlaceholder;

		for (j = 0; j < adjMatrix[i].size(); ++j)
			columnPlaceholder.push_back(adjMatrix[j][i]);

		transposedMatrix.push_back(columnPlaceholder);
	}

	return transposedMatrix;
}

vector<vector<int>> getEquivalenceClasses(vector<vector<int>> adjMatrix)
{
	int i;
	vector<vector<int>> adjVectorTransposed, connectedComponents;
	vector<vector<int>> adjVector = convertMatrixToAdjVector (adjMatrix);
	visited.assign(matrixDimension, false);

	for (i = 0; i < matrixDimension; ++i)
		if (!visited[i])
			orderDFS(adjVector, i);

	adjVectorTransposed = convertMatrixToAdjVector (transposeMatrix (adjMatrix));
	visited.assign (matrixDimension, false);
	reverse (exitOrder.begin (), exitOrder.end ());

	for (i = 0; i < matrixDimension; ++i)
	{
		if (!visited[exitOrder[i]])
		{
			getComponentDFS (adjVectorTransposed, exitOrder[i]);
			connectedComponents.push_back (component);
			component.clear ();
		}
	}

	return (connectedComponents);
}

int getMin(vector<int> component)
{
	int i, min = INT_MAX;

	for (i = 0; i < component.size (); ++i)
		if (component[i] < min)
			min = component[i];

	return (min);
}

void getSystemOfRepresentatives (vector<vector<int>> adjMatrix)
{
	int i, j;
	vector<int> systemOfRepresentatives;
	vector<vector<int>> connectedComponents = getEquivalenceClasses (adjMatrix);

	cout << "FACTOR SET OF THIS BINARY RELATION IS:\n";

	for (i = 0; i < connectedComponents.size (); ++i)
	{
		cout << "{ ";

		for (j = 0; j < connectedComponents[i].size(); ++j)
			cout << connectedComponents[i][j] + 1 << (j == connectedComponents[i].size() - 1 ? " " : ", ");

		cout << "}" << (i == connectedComponents.size() - 1 ? "." : ", ");
	}

	for (i = 0; i < connectedComponents.size(); ++i)
		systemOfRepresentatives.push_back(getMin (connectedComponents[i]));

	cout << "\nSYSTEM OF REPRESENTATIVES OF THIS BINARY RELATION IS:\n";

	for (i = 0; i < systemOfRepresentatives.size(); ++i)
		cout << "{ " << systemOfRepresentatives[i] + 1<< " }" << (i == systemOfRepresentatives.size() - 1 ? "." : ", ");
}

void opSelect();

vector<int> getDivisors(int numberX)
{
	int i, numberOfDivisors = 0;
	char includeOne = '.', includeX = '.';
	vector<int> divisors;

	for (i = 2; i * i < numberX; ++i)
		if (numberX % i == 0)
			++numberOfDivisors;

	while (includeOne != 'y' && includeOne != 'n')
	{
		cout << "INCLUDE ONE ? (y/n):\n";
		cin >> includeOne;
	}

	if (includeOne == 'y')
		divisors.push_back(1);

	while (includeX != 'y' && includeX != 'n')
	{
		cout << "INCLUDE " << numberX << " ? (y/n):\n";
		cin >> includeX;
	}

	if (includeX == 'y')
		divisors.push_back(numberX);

	if (numberOfDivisors == 0 && includeOne == 'n' && includeX == 'n')
	{
		cout << "YOU CAN'T REMOVE THE NUMBER ITSELF AND NUMBER ONE FOR A PRIME NUMBER.";
		exit(0);
	}

	for (i = 2; i <= numberX / 2; ++i)
		if (numberX % i == 0)
			divisors.push_back(i);

	return (divisors);
}

vector<int> getMins(vector<int> divisors)
{
	int i;
	map<int, vector<int>> divisibilityRelation;
	vector<int> mins;

	for (int divisor : divisors)
	{
		vector<int> placeholder;
		divisibilityRelation[divisor] = placeholder;
	}

	for (int divisor : divisors)
	{
		for (int divisorToCheck : divisors)
			if (divisor != divisorToCheck && divisorToCheck % divisor == 0)
				divisibilityRelation[divisor].push_back(divisorToCheck);
	}

	for (int divisor : divisors)
	{
		bool found = false;

		for (auto divisElements : divisibilityRelation)
			for (i = 0; i < divisElements.second.size(); ++i)
			{
				if (divisor == divisElements.second[i])
				{
					found = true;
					break;
				}

				if (found)
					break;
			}

		if (!found)
			mins.push_back(divisor);
	}

	/*for (auto elt : divisibilityRelation)
	{
		cout << elt.first << ": ";
		for (int i = 0; i < elt.second.size(); ++i)
			cout << elt.second[i] << " ";

		cout << "\n";
	}*/

	return (mins);
}

void removeMins (vector<int>& divisors, vector<int> mins)
{
	int i;

	for (int min : mins)
	{
		auto it = divisors.cbegin();

		for (i = 0; i < divisors.size(); ++i)
			if (divisors[i] == min)
				divisors.erase (it + i);
	}
}

void getHasseConnectionsMachinerie(vector<vector<pair<int, int>>>& HasseLevelConnections, vector<int> lowerLevel, vector<int> upperLevel)
{
	int i;
	vector<pair<int, int>> levelRelations;

	for (int lowerLevelElt : lowerLevel)
	{
		for (int upperLevelElt : upperLevel)
			if (upperLevelElt % lowerLevelElt == 0)
				levelRelations.push_back(make_pair(lowerLevelElt, upperLevelElt));
	}

	HasseLevelConnections.push_back(levelRelations);
}

vector<vector<pair<int, int>>> getHasseConnections(vector<vector<int>> HasseLevels)
{
	int i;
	vector<vector<pair<int, int>>> HasseLevelConnections;

	for (i = 0; i < HasseLevels.size() - 1; ++i)
		getHasseConnectionsMachinerie(HasseLevelConnections, HasseLevels[i], HasseLevels[i + 1]);

	return (HasseLevelConnections);
}

void printHasseDiagram(vector<vector<int>> HasseLevels, vector<vector<pair<int, int>>> HasseLevelConnections)
{
	int i, j;

	for (i = HasseLevels.size() - 1; i >= 0; --i)
	{
		for (j = 0; j < HasseLevels[i].size(); ++j)
			cout << HasseLevels[i][j] << " ";

		cout << "\n";
	}

	for (i = HasseLevelConnections.size() - 1; i >= 0; --i)
	{
		for (j = 0; j < HasseLevelConnections[i].size(); ++j)
			printf("(%d, %d)%c ", HasseLevelConnections[i][j].first,
				HasseLevelConnections[i][j].second,
				(j == HasseLevelConnections[i].size() - 1 ? '.' : ','));

		cout << "\n";
	}

	cout << "LEAST ELEMENT: ";
	if (HasseLevels[0].size() > 1)
	{
		cout << "NONE.\n";
		cout << "MINIMAL ELEMENTS: ";

		for (int i = 0; i < HasseLevels[0].size(); ++i)
			cout << HasseLevels[0][i] << (i == HasseLevels[0].size() - 1 ? "." : ", ");

		cout << "\n";
	}
	else
	{
		cout << HasseLevels[0][0] << ".\n";
		cout << "MINIMAL ELEMENT: " << HasseLevels[0][0] << ".\n";
	}

	int idx = HasseLevels.size() - 1;
	cout << "GREATEST ELEMENT: ";
	if (HasseLevels[idx].size() > 1)
	{
		cout << "NONE.\n";
		cout << "MAXIMAL ELEMENTS: ";

		for (int i = 0; i < HasseLevels[idx].size(); ++i)
			cout << HasseLevels[idx][i] << (i == HasseLevels[idx].size() - 1 ? "." : ", ");
	}
	else
	{
		cout << HasseLevels[idx][0] << ".\n";
		cout << "MAXIMAL ELEMENT: " << HasseLevels[idx][0] << ".\n";
	}
}

void HasseDiagram ()
{
	int numberX, i;
	vector<int> divisors, mins;
	vector<vector<int>> HasseLevels;
	vector<vector<pair<int, int>>> HasseLevelConnections;

	cout << "INPUT YOU NUMBER:\n";
	cin >> numberX;

	divisors = getDivisors (numberX);

	while (!divisors.empty ())
	{
		mins = getMins (divisors);
		HasseLevels.push_back (mins);
		removeMins (divisors, mins);
	}
	HasseLevelConnections = getHasseConnections (HasseLevels);
	printHasseDiagram (HasseLevels, HasseLevelConnections);
}

void cleanRows (vector<vector<int>>& matrix, vector<int> mins)
{
	int i;

	for (int min : mins)
		for (i = 0; i < matrixDimension; ++i)
			if (matrix[min][i] == 1)
				matrix[min][i] = 0;
}

void removeMinElts (vector<int>& elts, vector<int> mins)
{
	int i;

	for (int min : mins)
	{
		auto it = elts.cbegin ();

		for (i = 0; i < elts.size (); ++i)
			if (elts[i] == min)
				elts.erase (it + i);
	}
}

bool inElements (vector<int> elements, int i)
{
	int j;

	for (j = 0; j < elements.size (); ++j)
		if (elements[j] == i)
			return (true);

	return (false);
}

vector<int> getMinsMatrix (vector<vector<int>> matrix, vector<int> elements)
{
	int i, j;
	vector<int> mins;

	for (i = 0; i < matrixDimension; ++i)
	{
		bool isMin = true;

		for (j = 0; j < matrixDimension; ++j)
			if (matrix[j][i] == 1 && i != j)
			{
				isMin = false;
				break;
			}

		if (isMin && inElements (elements, i))
			mins.push_back (i);
	}

	return (mins);
}

void getHasseConnectionsMatrix (vector<vector<int>> matrix, vector<int> pLevel, vector<int> nLevel, vector<vector<pair<int, int>>>& levelsConnections)
{
	int i, j;
	vector<pair<int, int>> levelConnections;

	for (int pLvlElt : pLevel)	
		for (int nLvlElt : nLevel)
			if (matrix[pLvlElt][nLvlElt] == 1)
				levelConnections.push_back (make_pair (pLvlElt + 1, nLvlElt + 1));	

	levelsConnections.push_back (levelConnections);
}

void displayLevelsAndConnections (vector<vector<int>> HasseLevels, vector<vector<pair<int, int>>> HasseLevelConnections)
{
	int i, j;

	cout << "\nHASSE DIAGRAM LEVELS:\n";

	for (i = HasseLevels.size () - 1; i >= 0; --i)
	{
		for (j = 0; j < HasseLevels[i].size (); ++j)
			cout << HasseLevels[i][j] + 1 << " ";

		cout << "\n";
	}

	cout << "\nHASSE DIAGRAM CONNECTIONS:\n";

	for (i = HasseLevelConnections.size () - 1; i >= 0; --i)
	{
		int levelSize = HasseLevelConnections[i].size ();

		for (j = 0; j < HasseLevelConnections[i].size (); ++j)
		{
			pair<int, int> lvlElt = HasseLevelConnections[i][j];

			cout << "(" << lvlElt.first << ", " << lvlElt.second << ")" << (j == levelSize - 1 ? "." : ", ");
		}

		cout << "\n";
	}
}

void HasseDiagramMatrix ()
{
	int i;
	vector<vector<int>> matrix, matrixCopy, HasseLevels;
	vector<vector<pair<int, int>>> HasseLevelConnections;
	vector<int> elements, mins;
	cout << "INPUT MATRIX DIMENSION:\n";
	cin >> matrixDimension;

	getMatrix (matrix);

	matrixCopy = matrix;

	for (i = 0; i < matrix.size (); ++i)
		elements.push_back (i);

	while (!elements.empty ())
	{
		mins = getMinsMatrix (matrix, elements);
		HasseLevels.push_back (mins);
		removeMinElts (elements, mins);
		cleanRows (matrix, mins);
	}

	for (i = 0; i < HasseLevels.size () - 1; ++i)	
		getHasseConnectionsMatrix (matrixCopy, HasseLevels[i], HasseLevels[i + 1], HasseLevelConnections);

	displayLevelsAndConnections (HasseLevels, HasseLevelConnections);
}

void getObjectSet (vector<int>& objectSet)
{
	int i, elt;

	for (i = 0; i < matrixDimension; ++i)
	{
		cin >> elt;
		objectSet.push_back (elt);
	}		
}

void getAttributeSet ()
{
	int i;
	char elt;

	for (i = 0; i < matrixDimension; ++i)
	{
		cin >> elt;
		attributeSet.push_back (elt);
	}
}

bool inGrid (vector<vector<int>> setGrid, vector<int> rowToCheck)
{
	int i;

	for (i = 0; i < setGrid.size (); ++i)
		if (rowToCheck == setGrid[i])
			return (true);
		
	return (false);
}

vector<int> intersect (vector<int> lSet, vector<int> rSet)
{
	int i, j;
	vector<int> intersection;

	for (i = 0; i < lSet.size (); ++i)
	{
		for (j = 0; j < rSet.size (); ++j)
			if (lSet[i] == rSet[j])
				intersection.push_back (lSet[i]);
	}

	if (intersection.size () == 0)
		intersection.push_back (-1);

	return (intersection);
}

void getIntersects (vector<vector<int>>& setGrid)
{
	int i, j;

	for (i = 1; i < setGrid.size (); ++i)
	{
		for (j = 1; j < setGrid.size (); ++j)
		{
			vector<int> intersection = intersect (setGrid[i], setGrid[j]);

			if (i != j && !inGrid (setGrid, intersection))
				setGrid.push_back (intersection);
		}				
	}
}

bool isSubset (vector<int> set, vector<int> possibleSubset)
{
	int i, j;

	if (possibleSubset[0] == -1)
		return (true);

	for (i = 0; i < possibleSubset.size (); ++i)
	{
		bool flag = false;

		for (j = 0; j < set.size (); ++j)
			if (possibleSubset[i] == set[j])
				flag = true;

		if (!flag)
			return (false);
	}

	return (true);
}

void getSubsetRelation (map<vector<int>, vector<vector<int>>>& subsetRelation, vector<vector<int>> setGrid)
{
	int i, j;

	for (auto setAndSubsets : subsetRelation)
	{
		vector<vector<int>> subsets;

		for (j = 0; j < setGrid.size (); ++j)
			if (isSubset (setAndSubsets.first, setGrid[j]) && setAndSubsets.first != setGrid[j])
				subsets.push_back (setGrid[j]);
		subsetRelation[setAndSubsets.first] = subsets;
	}
}

void displaySubsetRelation (map<vector<int>, vector<vector<int>>> subsetRelation)
{
	int i, j;

	for (auto subsRelation : subsetRelation)
	{
		cout << "<";
		int setSize = subsRelation.first.size ();

		for (i = 0; i < setSize; ++i)
			cout << subsRelation.first[i] << (i == setSize - 1 ? ">" : ", ");

		cout << ": ";

		for (i = 0; i < subsRelation.second.size (); ++i)
		{
			cout << "{";

			int subsetSize = subsRelation.second[i].size ();

			for (j = 0; j < subsetSize; ++j)
				cout << subsRelation.second[i][j] << (j == subsetSize - 1 ? "}" : ", ");

			cout << (i == subsRelation.second.size () - 1 ? "." : ", ");
		}

		cout << "\n";
	}
}

vector<vector<int>> getMinsConcept (map<vector<int>, vector<vector<int>>> subsetRelation)
{
	int i;
	vector<vector<int>> mins;

	for (auto setAndSubsets : subsetRelation)
	{
		vector<int> set = setAndSubsets.first;

		if (subsetRelation[set].empty ())
			mins.push_back (set);
	}

	return (mins);
}

void removeMinsConcept (map<vector<int>, vector<vector<int>>>& subsetRelation, vector<vector<int>>& setGrid, vector<vector<int>> mins)
{
	int i;

	for (vector<int> min : mins)
	{
		auto it = setGrid.cbegin ();

		for (i = 0; i < setGrid.size (); ++i)
			if (setGrid[i] == min)
				setGrid.erase (it + i);
	}

	for (i = 0; i < mins.size (); ++i)
		subsetRelation.erase (subsetRelation.find (mins[i]));
}

vector<char> getAttributeSetConceptMachinerie (int objectNum, vector<vector<int>> matrix)
{
	int i;
	vector<char> objectAttributes;

	for (i = 0; i < matrix.size (); ++i)
		if (matrix[objectNum][i] == 1)
			objectAttributes.push_back (attributeSet[i]);

	if (objectAttributes.empty ())
		objectAttributes.push_back ('!');

	return (objectAttributes);
}

vector<char> charIntersect (vector<char> lSet, vector<char> rSet)
{
	int i, j;
	vector<char> intersection;

	for (i = 0; i < lSet.size (); ++i)
	{
		for (j = 0; j < rSet.size (); ++j)
			if (lSet[i] == rSet[j])
				intersection.push_back (lSet[i]);
	}

	if (intersection.size () == 0)
		intersection.push_back ('!');

	return (intersection);
}

vector<char> getAttributeSetConcept (vector<int> HasseLevelSet, vector<vector<int>> matrix)
{
	int i;
	vector<char> objectAttributeSet;

	if (HasseLevelSet[0] == -1)
		return (attributeSet);

	for (i = 0; i < matrix.size (); ++i)
		if (matrix[HasseLevelSet[0]][i] == 1)
			objectAttributeSet.push_back (attributeSet[i]);

	if (objectAttributeSet.empty ())
	{
		objectAttributeSet.push_back ('!');
		return (objectAttributeSet);
	}

	for (i = 1; i < HasseLevelSet.size (); ++i)
		objectAttributeSet = charIntersect (objectAttributeSet, getAttributeSetConceptMachinerie (HasseLevelSet[i], matrix));

	if (objectAttributeSet.empty ())
	{
		objectAttributeSet.push_back ('!');
		return (objectAttributeSet);
	}

	return (objectAttributeSet);
}

void displayConceptGrid (vector<vector<pair<vector<int>, vector<int>>>> HasseLevelsConnections, 
						 vector<vector<pair<vector<int>, vector<char>>>> alignedAttributeSets)
{
	int i, j, k;

	cout << "\nHASSE DIAGRAM:\n";

	for (i = alignedAttributeSets.size () - 1; i >= 0; --i)
	{
		for (j = 0; j < alignedAttributeSets[i].size (); ++j)
		{	
			cout << "<";
			for (k = 0; k < alignedAttributeSets[i][j].first.size (); ++k)
				if (alignedAttributeSets[i][j].first[k] == -1)
					cout << "EMPTY SET>";
					else cout << alignedAttributeSets[i][j].first[k] + 1 << (k == alignedAttributeSets[i][j].first.size () - 1 ? ">" : ", ");

			cout << " -> (";

			for (k = 0; k < alignedAttributeSets[i][j].second.size (); ++k)
				if (alignedAttributeSets[i][j].second[k] == '!')
					cout << "EMPTY SET)";
					else cout << alignedAttributeSets[i][j].second[k] << (k == alignedAttributeSets[i][j].second.size () - 1 ? ")" : ", ");

			cout << (j == alignedAttributeSets[i].size () - 1 ? "." : ", ");
		}

		cout << '\n';
	}

	cout << "\nHASSE DIAGRAM CONNECTIONS:\n";

	for (i = HasseLevelsConnections.size () - 1; i >= 0; --i)
	{
		for (j = 0; j < HasseLevelsConnections[i].size (); ++j)
		{	
			cout << "<";
			for (k = 0; k < HasseLevelsConnections[i][j].first.size (); ++k)
				if (HasseLevelsConnections[i][j].first[k] == -1)
					cout << "EMPTY SET>";
					else cout << HasseLevelsConnections[i][j].first[k] + 1 << (k == HasseLevelsConnections[i][j].first.size () - 1 ? ">" : ", ");

			cout << " -> <";

			for (k = 0; k < HasseLevelsConnections[i][j].second.size (); ++k)
				if (HasseLevelsConnections[i][j].second[k] == -1)
					cout << "EMPTY SET>";
					else cout << HasseLevelsConnections[i][j].second[k] + 1 << (k == HasseLevelsConnections[i][j].second.size () - 1 ? ">" : ", ");

			cout << (j == HasseLevelsConnections[i].size () - 1 ? "." : ", ");
		}

		cout << '\n';
	}
}

void HasseAttributeSet (vector<vector<vector<int>>> HasseLevels, vector<vector<pair<vector<int>, vector<int>>>> HasseLevelsConnections,
					    vector<vector<int>> matrix)
{
	int i, j;
	vector<vector<pair<vector<int>, vector<char>>>> alignedAttributeSets;
	vector<pair<vector<pair<vector<int>, vector<char>>>, vector<pair<vector<int>, vector<char>>>>> HasseConnections;

	for (auto HasseLevel : HasseLevels)
	{
		vector<pair<vector<int>, vector<char>>> levelAlignedAttributeSets;

		for (vector<int> set : HasseLevel)
			levelAlignedAttributeSets.push_back (make_pair (set, getAttributeSetConcept (set, matrix)));

		alignedAttributeSets.push_back (levelAlignedAttributeSets);
	}

	displayConceptGrid (HasseLevelsConnections, alignedAttributeSets);
}

vector<pair<vector<int>, vector<int>>> getHasseConnectionsConceptMachinerie (vector<vector<int>> pLevel, vector<vector<int>> nLevel)
{
	int i, j;
	vector<pair<vector<int>, vector<int>>> levelConnections;

	for (i = 0; i < pLevel.size (); ++i)
	{
		for (j = 0; j < nLevel.size (); ++j)
			if (isSubset (nLevel[j], pLevel[i]))
				levelConnections.push_back (make_pair (pLevel[i], nLevel[j]));
	}

	return (levelConnections);
}

void getHasseConnectionsConcept (vector<vector<vector<int>>> HasseLevels, vector<vector<pair<vector<int>, vector<int>>>>& HasseLevelsConnections)
{
	int i;

	for (i = 0; i < HasseLevels.size () - 1; ++i)
		HasseLevelsConnections.push_back (getHasseConnectionsConceptMachinerie (HasseLevels[i], HasseLevels[i + 1]));
}

void getHasseDiagramConceptGrid (vector<vector<int>>& closuredSetGrid, vector<vector<int>> matrix)
{
	int i;
	vector<vector<int>> mins;
	vector<vector<vector<int>>> HasseLevels;
	vector<vector<pair<vector<int>, vector<int>>>> HasseLevelsConnections;
	map<vector<int>, vector<vector<int>>> subsetRelation;

	for (i = 0; i < closuredSetGrid.size (); ++i)
	{
		vector<vector<int>> subsets;
		subsetRelation[closuredSetGrid[i]] = subsets;
	}

	while (!closuredSetGrid.empty ())
	{
		getSubsetRelation (subsetRelation, closuredSetGrid);
		mins = getMinsConcept (subsetRelation);
		HasseLevels.push_back (mins);
		removeMinsConcept (subsetRelation, closuredSetGrid, mins);
	}
	getHasseConnectionsConcept (HasseLevels, HasseLevelsConnections);
	HasseAttributeSet (HasseLevels, HasseLevelsConnections, matrix);
}

void getInverse (vector<vector<int>> matrix, vector<vector<int>>& closuredSetGrid)
{
	int i, j;
	vector<int> inverseRow;

	for (i = 0; i < matrixDimension; ++i)
		inverseRow.push_back (i);

	closuredSetGrid.push_back (inverseRow);
	inverseRow.clear ();

	for (i = 0; i < matrixDimension; ++i)
	{
		for (j = 0; j < matrixDimension; ++j)
			if (matrix[j][i] == 1)
				inverseRow.push_back (j);

		if (closuredSetGrid[0] != inverseRow)
			closuredSetGrid.push_back (inverseRow);

		inverseRow.clear ();
	}

	getIntersects (closuredSetGrid);
}

void conceptGrid ()
{
	vector<int> objectSet;
	vector<vector<int>> matrix;
	vector<vector<int>> closuredSetGrid;

	cout << "INPUT MATRIX DIMENSION\n";
	cin >> matrixDimension;

	cout << "INPUT YOUR OBJECTS:\n";
	getObjectSet (objectSet);

	cout << "INPUT YOUR ATTRIBUTES:\n";
	getAttributeSet ();
	getMatrix (matrix);

	getInverse (matrix, closuredSetGrid);
	getHasseDiagramConceptGrid (closuredSetGrid, matrix);
}

void opSwitch (vector<int> ops)
{
	int i;
	char choice = '.';
	vector<vector<int>> adjMatrix;

	for (i = 0; i < ops.size (); ++i)
	{
		switch (ops[i])
		{
			case 1:
				cout << "INPUT MATRIX DIMENSION:\n";
				cin >> matrixDimension;
				getMatrix (adjMatrix);
				equivalenceClosure (adjMatrix);
				cout << "THE ELEMENTS OF YOUR MATRIX AFTER CLOSURE ARE:\n";
				displayMatrix (adjMatrix);
				break;

			case 2:
				cout << "INPUT MATRIX DIMENSION:\n";
				cin >> matrixDimension;
				getMatrix (adjMatrix);
				equivalenceClosure (adjMatrix);
				cout << "THE ELEMENTS OF YOUR MATRIX AFTER CLOSURE ARE:\n";
				displayMatrix (adjMatrix);
				getSystemOfRepresentatives (adjMatrix);
				cout << "\n\n";
				break;

			case 3:
				HasseDiagram ();
				cout << "\n";
				break;

			case 4:
				HasseDiagramMatrix ();
				cout << "\n";
				break;

			case 5:
				conceptGrid ();
				cout << "\n";

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
		opSelect();
}

void opSelect()
{
	int input = -1;
	vector<int> ops;

	cout << "1 - EQUIVALENCE CLOSURE\n";
	cout << "2 - SYSTEM OF REPRESENTATIVES\n";
	cout << "3 - HASSE DIAGRAM (NUMBER)\n";
	cout << "4 - HASSE DIAGRAM (MATRIX)\n";
	cout << "5 - CONCEPT GRID\n";
	cout << "0 - EXIT\n\n";

	while (input != 0)
	{
		cin >> input;
		ops.push_back(input);
	}
	cout << "\n";

	opSwitch(ops);
}

int main()
{
	opSelect();

	return (EXIT_SUCCESS);
}
