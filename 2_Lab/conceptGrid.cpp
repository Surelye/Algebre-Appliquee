#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

int matrixDimension;

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
	vector<vector<int>> adjVector = convertMatrixToAdjVector(adjMatrix);
	visited.assign(matrixDimension, false);

	for (i = 0; i < matrixDimension; ++i)
		if (!visited[i])
			orderDFS(adjVector, i);

	adjVectorTransposed = convertMatrixToAdjVector(transposeMatrix(adjMatrix));
	visited.assign(matrixDimension, false);
	reverse(exitOrder.begin(), exitOrder.end());

	for (i = 0; i < matrixDimension; ++i)
	{
		if (!visited[exitOrder[i]])
		{
			getComponentDFS(adjVectorTransposed, exitOrder[i]);
			connectedComponents.push_back(component);
			component.clear();
		}
	}

	return (connectedComponents);
}

int getMin(vector<int> component)
{
	int i, min = INT_MAX;

	for (i = 0; i < component.size(); ++i)
		if (component[i] < min)
			min = component[i];

	return (min);
}

void getSystemOfRepresentatives(vector<vector<int>> adjMatrix)
{
	int i, j;
	vector<int> systemOfRepresentatives;
	vector<vector<int>> connectedComponents = getEquivalenceClasses(adjMatrix);

	cout << "FACTOR SET OF THIS BINARY RELATION IS:\n";

	for (i = 0; i < connectedComponents.size(); ++i)
	{
		cout << "{ ";

		for (j = 0; j < connectedComponents[i].size(); ++j)		
			cout << connectedComponents[i][j] + 1 << (j == connectedComponents[i].size() - 1 ? " " : ", ");
		
		cout << "}" << (i == connectedComponents.size() - 1 ? "." : ", ");
	}
	
	for (i = 0; i < connectedComponents.size(); ++i)
		systemOfRepresentatives.push_back(getMin(connectedComponents[i]));

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

void removeMins(vector<int>& divisors, vector<int> mins)
{
	int i;

	for (int min : mins)
	{
		auto it = divisors.cbegin();

		for (i = 0; i < divisors.size(); ++i)
			if (divisors[i] == min)
				divisors.erase(it + i);
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

void HasseDiagram()
{
	int numberX, i;
	vector<int> divisors, mins;
	vector<vector<int>> HasseLevels;
	vector<vector<pair<int, int>>> HasseLevelConnections;

	cout << "INPUT YOU NUMBER:\n";
	cin >> numberX;

	divisors = getDivisors(numberX);

	while (!divisors.empty())
	{
		mins = getMins(divisors);
		HasseLevels.push_back(mins);
		removeMins(divisors, mins);
	}
	
	HasseLevelConnections = getHasseConnections(HasseLevels);
	printHasseDiagram(HasseLevels, HasseLevelConnections);
}

void opSwitch(vector<int> ops)
{
	int i;
	char choice = '.';
	vector<vector<int>> adjMatrix;

	for (i = 0; i < ops.size(); ++i)
	{
		switch (ops[i])
		{
			case 1:				
				cout << "INPUT MATRIX DIMENSION:\n";
				cin >> matrixDimension;
				getMatrix(adjMatrix);				
				equivalenceClosure(adjMatrix);
				cout << "THE ELEMENTS OF YOUR MATRIX AFTER CLOSURE ARE:\n";
				displayMatrix(adjMatrix);
				break;

			case 2:
				cout << "INPUT MATRIX DIMENSION:\n";
				cin >> matrixDimension;
				getMatrix(adjMatrix);
				equivalenceClosure(adjMatrix);
				cout << "THE ELEMENTS OF YOUR MATRIX AFTER CLOSURE ARE:\n";
				displayMatrix(adjMatrix);				
				getSystemOfRepresentatives(adjMatrix);
				cout << "\n\n";
				break;

			case 3:
				HasseDiagram();
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
	cout << "3 - HASSE DIAGRAM\n";
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