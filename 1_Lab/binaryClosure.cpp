#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

map<int, set<int>> getData(int numberOfPairs, map<int, set<int>> binaryRelation)
{
    int i, firstEl, secondEl;

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

    for (auto element : binaryRelation)
    {
        it = element.second.begin();

        for ( ; it != element.second.end(); ++it)
        {
            placeholder = *it;

            if (binaryRelation[placeholder].empty())
                binaryRelation[placeholder].insert(placeholder);
        }
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

map<int, set<int>> transitiveClosure(map<int, set<int>> binaryRelation)
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

map<int, set<int>> equivalenceClosure(map<int, set<int>> binaryRelation)
{
    return transitiveClosure(symmetricClosure(reflexiveClosure(binaryRelation)));
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

    cout << "\n" << (isReflexive ? "\nBINARY RELATION IS REFLEXIVE.\n" : "\nBINARY RELATION IS NOT REFLEXIVE.\n");
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
                cout << "\nBINARY RELATION IS NOT SYMMETRIC.\n";
                return false;
            }
        }
    }

    cout << "\nBINARY RELATION IS SYMMETRIC.\n";
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
                cout << "\nBINARY RELATION IS NOT ANTISYMMETRIC.\n";
                return false;
            }            
        }
    }

    cout << "\nBINARY RELATION IS ANTISYMMETRIC.\n";
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
                        cout << "\nBINARY RELATION IS NOT TRANSITIVE.\n";
                        return false;
                    }
                }
            }
        }
    }

    cout << "\nBINARY RELATION IS TRANSITIVE.\n";
    return true;
}

void isEquivalence(map<int, set<int>> binaryRelation)
{
    if (isReflexive(binaryRelation) && isSymmetric(binaryRelation) && isTransitive(binaryRelation))
        cout << "\nBINARY RELATION IS AN EQUIVALENT RELATION.\n";
    else
        cout << "\nBINARY RELATION IS NOT AN EQUIVALENT RELATION.\n";
}

void isOrder(map<int, set<int>> binaryRelation)
{
    if (isReflexive(binaryRelation) && isAntisymmetric(binaryRelation) && isTransitive(binaryRelation))
        cout << "\BINARY RELATION IS AN ORDER RELATION.\n";
    else
        cout << "\BINARY RELATION IS NOT AN ORDER RELATION.\n";
}

void isQuasi(map<int, set<int>> binaryRelation)
{
    if (isReflexive(binaryRelation) && isTransitive(binaryRelation))
        cout << "\nBINARY RELATION IS A QUASI-ORDER RELATION.\n";
    else
        cout << "\nBINARY RELATION IS NOT A QUASI-ORDER RELATION.\n";
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

int main()
{
    int numberOfPairs, range = 3;
    map<int, set<int>> binaryRelation;

    cout << "INPUT THE NUMBER OF PAIRS:\n";
    cin >> numberOfPairs;
    cout << "NOW INPUT THE PAIRS:\n";

    binaryRelation = generateBinaryRelation(numberOfPairs, range, binaryRelation);
    displayBinaryRelation(binaryRelation);
    
    /*binaryRelation = getData(numberOfPairs, binaryRelation); 
    cout << "\n\nTHE ELEMENTS OF YOUR BINARY RELATION ARE:\n";
    displayBinaryRelation(binaryRelation);*/

    /*binaryRelation = reflexiveClosure(binaryRelation);
    cout << "\n\nTHE ELEMENTS OF YOUR BINARY RELATION AFTER REFLEXIVE CLOSURE ARE:\n";
    displayBinaryRelation(binaryRelation);

    binaryRelation = symmetricClosure(binaryRelation);
    cout << "\n\nTHE ELEMENTS OF YOUR BINARY RELATION AFTER SYMMETRIC CLOSURE ARE:\n";
    displayBinaryRelation(binaryRelation);

    binaryRelation = transitiveClosure(binaryRelation);
    cout << "\n\nTHE ELEMENTS OF YOUR BINARY RELATION AFTER TRANSITIVE CLOSURE ARE:\n";
    displayBinaryRelation(binaryRelation);*/
    
    isReflexive(binaryRelation);

    /*isAntisymmetric(binaryRelation);

    isSymmetric(binaryRelation);
    
    isTransitive(binaryRelation);*/

    return (EXIT_SUCCESS);
}