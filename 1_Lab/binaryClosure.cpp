#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

map<int, set<int>> getData(int numberOfElements, int numberOfPairs, map<int, set<int>> binaryRelation)
{
    int i, placeholderEl, firstEl, secondEl;

    cout << "NOW INPUT YOUR ELEMENTS:\n";

    for (i = 0; i < numberOfElements; ++i)
    {
        cin >> placeholderEl;

        set<int> placeholder;
        binaryRelation[placeholderEl] = placeholder;
    }

    cout << "NOW INPUT YOUR PAIRS:\n";

    for (i = 0; i < numberOfPairs; ++i)
    {
        cin >> firstEl >> secondEl;
        binaryRelation[firstEl].insert(secondEl);

        if (binaryRelation.count(secondEl) == 0)
        {
            set<int> placeholder;
            binaryRelation[secondEl] = placeholder;
        }
    }

    return binaryRelation;
}

void displayBinaryRelation(map<int, set<int>> binaryRelation)
{
    int i;
    set<int> ::iterator it;

    for (auto element : binaryRelation)
    {
        it = element.second.begin();

        for (i = 0 ; it != element.second.end(); ++it, ++i)
            printf("(%d; %d)%c ", element.first, *it, (i == element.second.size() - 1) ? '.' : ',');
    }
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

    /*for (auto element : binaryRelation)
    {
        it = element.second.begin();

        for ( ; it != element.second.end(); ++it)
        {
            placeholder = *it;

            if (binaryRelation[placeholder].empty())
                binaryRelation[placeholder].insert(placeholder);
        }
    }*/

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

bool isReflexive(map<int, set<int>> binaryRelation)
{
    bool isReflexive = false;
    set<int> ::iterator it;
    int i;

    for (auto element : binaryRelation)
    {
        isReflexive = false;
        it = element.second.begin();

        for (; it != element.second.end(); ++it)
            if (element.first == *it)
            {
                isReflexive = !isReflexive;
                break;
            }

        if (!isReflexive)
            break;
    }

    cout << (isReflexive ? "BINARY RELATION IS REFLEXIVE.\n" : "BINARY RELATION IS NOT REFLEXIVE.\n");
    return isReflexive;
}

bool isSymmetric(map<int, set<int>> binaryRelation)
{
    bool isSymmetric = false;
    set<int> ::iterator it, itHelper;

    for (auto element : binaryRelation)
    {
        it = element.second.begin();

        for (; it != element.second.end(); ++it)
        {
            isSymmetric = false;

            if (!binaryRelation[*it].empty())
            {
                itHelper = binaryRelation[*it].begin();

                for (; itHelper != binaryRelation[*it].end(); ++itHelper)
                    if (element.first == *itHelper)
                        isSymmetric = !isSymmetric;
            }
            
            if (!isSymmetric)
            {
                cout << "BINARY RELATION IS NOT SYMMETRIC.\n";
                return false;
            }
        }
    }

    cout << "BINARY RELATION IS SYMMETRIC.\n";
    return true;
}

bool isAntisymmetric(map<int, set<int>> binaryRelation)
{
    bool isAntisymmetric = false;
    set<int> ::iterator it, itHelper;

    for (auto element : binaryRelation)
    {
        it = element.second.begin();

        for (; it != element.second.end(); ++it)
        {
            isAntisymmetric = true;

            if (!binaryRelation[*it].empty() && *it != element.first)
            {
                itHelper = binaryRelation[*it].begin();

                for (; itHelper != binaryRelation[*it].end(); ++itHelper)
                    if (*itHelper == element.first)
                        isAntisymmetric = false;
            }

            if (!isAntisymmetric)
            {
                cout << "BINARY RELATION IS NOT ANTISYMMETRIC.\n";
                return false;
            }            
        }
    }

    cout << "BINARY RELATION IS ANTISYMMETRIC.\n";
    return true;
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
                    {
                        cout << "BINARY RELATION IS NOT TRANSITIVE.\n";
                        return false;
                    }
                }
            }
        }
    }

    cout << "BINARY RELATION IS TRANSITIVE.\n";
    return true;
}

void isEquivalence(map<int, set<int>> binaryRelation)
{
    if (isReflexive(binaryRelation) && isSymmetric(binaryRelation) && isTransitive(binaryRelation))
        cout << "BINARY RELATION IS AN EQUIVALENT RELATION.\n";
    else
        cout << "BINARY RELATION IS NOT AN EQUIVALENT RELATION.\n";
}

void isOrder(map<int, set<int>> binaryRelation)
{
    if (isReflexive(binaryRelation) && isAntisymmetric(binaryRelation) && isTransitive(binaryRelation))
        cout << "BINARY RELATION IS AN ORDER RELATION.\n";
    else
        cout << "BINARY RELATION IS NOT AN ORDER RELATION.\n";
}

void isQuasi(map<int, set<int>> binaryRelation)
{
    if (isReflexive(binaryRelation) && isTransitive(binaryRelation))
        cout << "BINARY RELATION IS A QUASI-ORDER RELATION.\n";
    else
        cout << "BINARY RELATION IS NOT A QUASI-ORDER RELATION.\n";
}

map<int, set<int>> transitiveClosure(map<int, set<int>> binaryRelation)
{
    while (!isTransitive(binaryRelation))
        binaryRelation = transitiveClosureMachinery(binaryRelation);

    return binaryRelation;
}

map<int, set<int>> equivalenceClosure(map<int, set<int>> binaryRelation)
{
    return transitiveClosure(symmetricClosure(reflexiveClosure(binaryRelation)));
}

map<int, set<int>> generateBinaryRelation(int numberOfPairs, int range, map<int, set<int>> binaryRelation)
{
    srand(time(0));
    int i, firstEl, secondEl;
    double multiplyingFactor;

    for (i = 0; i < numberOfPairs; ++i)
    {
        multiplyingFactor = ((double)rand()) / RAND_MAX;
        firstEl = floor(multiplyingFactor * range);
        multiplyingFactor = ((double)rand()) / RAND_MAX;
        secondEl = floor(multiplyingFactor * range);

        binaryRelation[firstEl].insert(secondEl);

        if (binaryRelation.count(secondEl) == 0)
        {
            set<int> placeholder;
            binaryRelation[secondEl] = placeholder;
        }
    }

    return binaryRelation;
}

map<int, set<int>> invokeFunction(int opNum, map<int, set<int>> binaryRelation)
{
    switch (opNum)
    {
        case 1:
            cout << "RESULT OF OPERATION 1:\n";
            isReflexive(binaryRelation);
            cout << "\n";
            break;

        case 2:
            cout << "RESULT OF OPERATION 2:\n";
            isSymmetric(binaryRelation);
            cout << "\n";
            break;

        case 3:
            cout << "RESULT OF OPERATION 3:\n";
            isAntisymmetric(binaryRelation);
            cout << "\n";
            break;

        case 4:
            cout << "RESULT OF OPERATION 4:\n";
            isTransitive(binaryRelation);
            cout << "\n";
            break;

        case 5:
            cout << "RESULT OF OPERATION 5:\n";
            isEquivalence(binaryRelation);
            cout << "\n";
            break;

        case 6:
            cout << "RESULT OF OPERATION 6:\n";
            isOrder(binaryRelation);
            cout << "\n";
            break;

        case 7:
            cout << "RESULT OF OPERATION 7:\n";
            isQuasi(binaryRelation);
            cout << "\n";
            break;

        case 8:
            cout << "RESULT OF OPERATION 8:\n";
            binaryRelation = reflexiveClosure(binaryRelation);
            cout << "ELEMENTS OF YOUR BINARY RELATION AFTER REFLEXIVE CLOSURE:\n";
            displayBinaryRelation(binaryRelation);
            cout << "\n\n";
            break;

        case 9:
            cout << "RESULT OF OPERATION 9:\n";
            binaryRelation = symmetricClosure(binaryRelation);
            cout << "ELEMENTS OF YOUR BINARY RELATION AFTER SYMMETRIC CLOSURE:\n";
            displayBinaryRelation(binaryRelation);
            cout << "\n\n";
            break;

        case 10:
            cout << "RESULT OF OPERATION 10:\n";
            binaryRelation = transitiveClosure(binaryRelation);
            cout << "ELEMENTS OF YOUR BINARY RELATION AFTER TRANSITIVE CLOSURE:\n";
            displayBinaryRelation(binaryRelation);
            cout << "\n\n";
            break;

        case 11:
            cout << "RESULT OF OPERATION 11:\n";
            binaryRelation = equivalenceClosure(binaryRelation);
            cout << "ELEMENTS OF YOUR BINARY RELATION AFTER EQUIVALENCE CLOSURE:\n";
            displayBinaryRelation(binaryRelation);
            cout << "\n\n";
            break;

        default:
            break;
    }

    return binaryRelation;
}

void opSwitch(map<int, set<int>> binaryRelation)
{
    vector<int> ops;
    int i, placeholder = -1;

    cout << " 1 - REFLEXIVE CHECK\n";
    cout << " 2 - SYMMETRIC CHECK\n";
    cout << " 3 - ANTISYMMETRIC CHECK\n";
    cout << " 4 - TRANSITIVE CHECK\n";
    cout << " 5 - EQUIVALENCE CHECK\n";
    cout << " 6 - ORDER CHECK\n";
    cout << " 7 - QUASI-ORDER CHECK\n";
    cout << " 8 - REFLEXIVE CLOSURE\n";
    cout << " 9 - SYMMETRIC CLOSURE\n";
    cout << "10 - TRANSITIVE CLOSURE\n";
    cout << "11 - EQUIVALENCE CLOSURE\n";
    cout << " 0 - EXIT\n\n";

    while (placeholder != 0)
    {
        cin >> placeholder;
        ops.push_back(placeholder);
    }

    cout << "\n";

    for (i = 0; i < ops.size(); ++i)
        binaryRelation = invokeFunction(ops[i], binaryRelation);
}

int main()
{
    int numberOfPairs, numberOfElements, range = 100;
    map<int, set<int>> binaryRelation;

    cout << "INPUT THE NUMBER OF ELEMENTS IN YOUR BINARY RELATION:\n";
    cin >> numberOfElements;
    
    cout << "INPUT THE NUMBER OF PAIRS:\n";
    cin >> numberOfPairs;

    /*binaryRelation = generateBinaryRelation(numberOfPairs, range, binaryRelation);
    displayBinaryRelation(binaryRelation);*/
    
    binaryRelation = getData(numberOfElements, numberOfPairs, binaryRelation); 
    cout << "\nTHE ELEMENTS OF YOUR BINARY RELATION ARE:\n";
    displayBinaryRelation(binaryRelation);
    cout << "\n\n";

    opSwitch(binaryRelation);

    return (EXIT_SUCCESS);
}