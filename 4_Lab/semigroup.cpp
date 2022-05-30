#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
#include <algorithm>

using namespace std;

void opSelect ();

int CayleyTableDimension;
unsigned short matrixDimension;
set<int> semigroupSubset;

void getSemigroupSubset ()
{
  int i = 0, semigroupSize;
  char eltPlaceholder;

  cout << "INPUT SUBSET SIZE:\n";
  cin >> semigroupSize;

  cout << "INPUT SUBSET ELEMENTS:\n";
  while (i < semigroupSize)
    {
      unsigned short currentSize = semigroupSubset.size ();
      cin >> eltPlaceholder;
      eltPlaceholder -= 97;
      if (eltPlaceholder >= CayleyTableDimension || eltPlaceholder < 0)
        {
          cout << "WRONG INPUT. TRY AGAIN.\n";
          continue;
        }
      else semigroupSubset.insert (eltPlaceholder);

      if (semigroupSubset.size () - currentSize > 0)
        ++i;
      else cout << "ELEMENT IS ALREADY IN THE SET. TRY ANOTHER ONE.\n";
    }
}

void getCayleyTable (vector<vector<int>>& CayleyTable)
{
  int i, j;
  vector<vector<char>> charCayleyTable (CayleyTableDimension, vector<char> (CayleyTableDimension, '0'));

  for (i = 0; i < CayleyTableDimension; ++i)
    for (j = 0; j < CayleyTableDimension; ++j)
      cin >> charCayleyTable[i][j];

  for (i = 0; i < CayleyTableDimension; ++i)
    for (j = 0; j < CayleyTableDimension; ++j)
      CayleyTable[i][j] = charCayleyTable[i][j] - 97;
}

void getSubsemigroupMachinerie (vector<vector<int>> CayleyTable, set<int>& subsemigroup)
{
  set<int> ::iterator i, j;
  set<int> newElements, X_i = semigroupSubset;

  while (true)
    {
      unsigned short curSize = X_i.size ();

      for (i = X_i.begin (); i != X_i.end (); ++i)
        for (j = X_i.begin (); j != X_i.end (); ++j)
          newElements.insert (CayleyTable[*i][*j]);
      for (i = newElements.begin (); i != newElements.end (); ++i)
        X_i.insert (*i);
      if (X_i.size () - curSize == 0)
        break;
      newElements.clear ();
    }
  subsemigroup = X_i;
}

void getSubsemigroup ()
{
  cout << "INPUT CAYLEY TABLE DIMENSION:\n";
  cin >> CayleyTableDimension;
  set<int> subsemigroup;
  vector<vector<int>> CayleyTable (CayleyTableDimension, vector<int> (CayleyTableDimension, 0));

  cout << "INPUT ELEMENTS OF THE CAYLEY TABLE:\n";
  getCayleyTable (CayleyTable);

  getSemigroupSubset ();

  getSubsemigroupMachinerie (CayleyTable, subsemigroup);

  cout << "RESULTING SEMIGROUP IS:\n<";
  for (set<int> ::iterator it = subsemigroup.begin (); it != subsemigroup.end (); ++it)
    cout << (char)(*it + 97) << (it == --subsemigroup.end () ? "" : ", ");
  cout << ">\n";
}

void getMatrix (vector<vector<unsigned short>>& binaryRelationMatrix)
{
  unsigned short i, j;

  for (i = 0; i < matrixDimension; ++i)
    for (j = 0; j < matrixDimension; ++j)
      cin >> binaryRelationMatrix[i][j];
}

vector<vector<unsigned short>> boolMatricesMultiplication (vector<vector<unsigned short>> fM, vector<vector<unsigned short>> sM)
{
  unsigned short i, j, k, matSize = fM.size (), product = 0;
  vector<vector<unsigned short>> resM (matSize, vector<unsigned short> (matSize, 0));

  for (i = 0; i < matSize; ++i)
    for (j = 0; j < matSize; ++j)
      {
        for (k = 0; k < matSize; ++k)
          product += fM[i][k] * sM[k][j];

        resM[i][j] = (product > 0 ? 1 : 0);
        product = 0;
      }

  return (resM);
}

vector<pair<vector<vector<unsigned short>>, char>> matrixMappings;
char symbolToMap = 'a';

void getSemigroupMachinerie (set<vector<vector<unsigned short>>> binaryRelationSet, set<vector<vector<unsigned short>>>& semigroup)
{
  set<vector<vector<unsigned short>>> ::iterator i, j;
  set<vector<vector<unsigned short>>> newElements, X_i = binaryRelationSet;

  while (true)
    {
      unsigned short curSize = X_i.size ();

      for (i = X_i.begin (); i != X_i.end (); ++i)
        for (j = X_i.begin (); j != X_i.end (); ++j)
          newElements.insert (boolMatricesMultiplication (*i, *j));
      for (i = newElements.begin (); i != newElements.end (); ++i)
        X_i.insert (*i);
      if (X_i.size () - curSize == 0)
        break;
      newElements.clear ();
    }
  semigroup = X_i;
}

char find_corresponding_letter (vector<pair<vector<vector<unsigned short>>, char>> matMaps, vector<vector<unsigned short>> matToCheck)
{
  int i;
  for (i = 0; i < matMaps.size (); ++i)
    if (matMaps[i].first == matToCheck)
      return (matMaps[i].second);
  return ('.');
}

void display_matrix_Cayley_table (vector<pair<vector<vector<unsigned short>>, char>> matMaps)
{
  int i, j;

  cout << endl << "CAYLEY TABLE:\n";
  cout << "    ";
  for (i = 0; i < matMaps.size (); ++i)
    cout << setw (4) << matMaps[i].second;
  cout << "\n";

  for (i = 0; i < matMaps.size (); ++i)
    {
      cout << setw (4) << matMaps[i].second << setw (4);
      for (j = 0; j < matMaps.size (); ++j)
        cout << find_corresponding_letter (matMaps, boolMatricesMultiplication (matMaps[i].first, matMaps[j].first)) << setw (4);
      cout << endl;
    }
  cout << endl;
}

void getSemigroup ()
{
  unsigned short i = 0, j, k = 0, binaryRelationsNumber;
  set<vector<vector<unsigned short>>> ::iterator it;
  set<vector<vector<unsigned short>>> binaryRelationSet, semigroup;

  cout << "INPUT THE NUMBER OF BINARY RELATIONS:\n";
  cin >> binaryRelationsNumber;

  cout << "INPUT THE DIMENSION OF MATRICES:\n";
  cin >> matrixDimension;

  while (i < binaryRelationsNumber)
    {
      vector<vector<unsigned short>> binaryRelationMatrix (matrixDimension, vector<unsigned short> (matrixDimension, 0));

      cout << "INPUT THE BINARY RELATION MATRIX:\n";
      getMatrix (binaryRelationMatrix);

      if (binaryRelationSet.empty ())
        {
          binaryRelationSet.insert (binaryRelationMatrix);
          ++i;
          continue;
        }

      for (it = binaryRelationSet.begin (); it != binaryRelationSet.end (); ++it)
        if (*it == binaryRelationMatrix)
          ++k;
          // cout << "THIS MATRIX IS ALREADY IN THE SET. TRY ANOTHER ONE.\n";
        else
          {
            binaryRelationSet.insert (binaryRelationMatrix);
            ++i;
          }
      // getSemigroupMachinerie (binaryRelationSet, semigroup);
    }
  getSemigroupMachinerie (binaryRelationSet, semigroup);

  cout << "THE RESULTING SEMIGROUP IS:\n";

  for (it = semigroup.begin (); it != semigroup.end (); ++it)
    {
      cout << symbolToMap << ":\n";
      matrixMappings.push_back (make_pair (*it, symbolToMap++));
      for (i = 0; i < matrixDimension; ++i)
        {
          for (j = 0; j < matrixDimension; ++j)
            cout << (*it)[i][j] << " ";
          cout << '\n';
        }
      cout << '\n';
    }
  display_matrix_Cayley_table (matrixMappings);
}

set <string> setOfR;
map <string, string> R;
set <string> S_cur, S, Scopy;
int maxRel = 0;
string cur_word;
vector <vector <string>> cayley;


vector <string> split(string word) {
	vector <string> splitedWord;
	for (int i = 0; i < word.size(); i++)
		splitedWord.push_back(word.substr(i, 1));

	return(splitedWord);
}


bool comp(string A, string B) {
	return (A.size() < B.size()) || (A.size() == B.size() && A < B);
}


void newEl(string word, bool flagCayley = false, int row = 0, int size = -1) {
	if (setOfR.find(word) != setOfR.end() && !flagCayley)
		return;

	vector <string> word_ = split(word);

	int substr = 2;
	while (substr <= maxRel) {
		for (int i = word_.size() - 1; i >= 0; i--) {
			if (substr > word.size() || substr > i + 1)
				break;

			string part = "";
			for (int j = i; j > i - substr; j--)
				part = word_[j] + part;

			if (R.find(part) != R.end()) {
				cur_word = "";
				vector <string> part_ = split(R[part]);

				if (!flagCayley)
					for (int k = 0; k < i - substr; k++)
						cur_word = cur_word + word_[k];
				else
					for (int k = 0; k < i - substr + 1; k++)
						cur_word = cur_word + word_[k];

				cur_word = cur_word + R[part];

				for (int k = i + 1; k < word_.size(); k++)
					cur_word = cur_word + word_[k];

				if (cur_word.size() < word.size() && !flagCayley) {
					setOfR.insert(word);
					setOfR.insert(cur_word);
					return;
				}
				else if (setOfR.find(cur_word) != setOfR.end() && !flagCayley)
					return;
				else if (flagCayley && Scopy.find(cur_word) != Scopy.end()) {
					if (cayley[row].size() < size)
						cayley[row].push_back(cur_word);
					return;
				}
				else {
					int check = cayley[row].size();
					newEl(cur_word, flagCayley, row, size);
					if (flagCayley && cayley[row].size() > check)
						return;
				}
			}

			if (setOfR.find(word) != setOfR.end() && !flagCayley)
				return;

			if (flagCayley && Scopy.find(word) != Scopy.end()) {
				if (cayley[row].size() <= size)
					cayley[row].push_back(word);
				return;
			}
		}
		substr++;
	}

	if (cur_word.size() == word.size() && cur_word < word && setOfR.find(word) == setOfR.end() && setOfR.find(cur_word) == setOfR.end()) {
		S.insert(cur_word);
		setOfR.insert(word);
		setOfR.insert(cur_word);
	}
	else {
		S.insert(word);
		setOfR.insert(word);
		setOfR.insert(cur_word);
	}
}

void get_semigroup_defining ()
{
	int N;
	cout << "INPUT THE NUMBER OF ALPHABET ELEMENTS:\n";
	cin >> N;

	set <string> A;
	cout << "INPUT YOUR ALPHABET:\n";
	for (int i = 0; i < N; i++)
    {
      string a;
      cin >> a;
      A.insert(a);
      S.insert(a);
      setOfR.insert(a);
    }

	int M;
	cout << "INPUT THE NUMBER OF DEFINING RELATIONS:\n";
	cin >> M;

	cout << "INPUT YOUR DEFINING RELATIONS:\n";
	for (int i = 0; i < M; i++)
    {
      string r1, r2;
      cin >> r1 >> r2;

      if (r1.size() > maxRel)
        maxRel = r1.size();
      if (r2.size() > maxRel)
        maxRel = r2.size();

      if (r1.size() < r2.size())
        R[r2] = r1;
      else if (r1.size() > r2.size())
        R[r1] = r2;
      else
        {
          if (r1 < r2)
            R[r2] = r1;
          else
            R[r1] = r2;
        }
    }

	int count = 1;
	S_cur = A;
	while (!S_cur.empty())
    {
      count++;

      for (string s : S_cur)
        for (string letter : A)
          newEl(s + letter);

      S_cur.clear();
      for (auto s : S)
        if (s.size() == count)
          S_cur.insert(s);
	}

	vector <string> halfgroup;
	for (string s : S)
		halfgroup.push_back(s);
	sort(halfgroup.begin(), halfgroup.end(), comp);
	int hSize = halfgroup.size();

	cout << "\nRESULTING SEMIGROUP IS:\n{";
	for (int i = 0; i < hSize; i++) {
		if (i == hSize - 1)
			cout << halfgroup[i] << "} \n";
		else cout << halfgroup[i] << ", ";
	}

	cayley.resize(hSize);
	Scopy = S;
	for (int i = 0; i < hSize; i++)
		for (int j = 0; j < hSize; j++)
			newEl(halfgroup[i] + halfgroup[j], true, i, hSize);

	cout << endl << "CAYLEY TABLE:\n";
	cout << "     ";
	for (int i = 0; i < hSize; i++)
		cout << setw(5) << halfgroup[i];
	cout << endl;
	for (int i = 0; i < hSize; i++) {
		cout << setw(5) << halfgroup[i] << setw(5);
		for (int j = 0; j < hSize; j++)
			cout << cayley[i][j] << setw(5);
		cout << endl;
	}

	cout << endl;
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
          getSubsemigroup ();
          break;

        case 2:
          getSemigroup ();
          break;

        case 3:
          get_semigroup_defining ();
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
    {
      semigroupSubset.clear ();
      opSelect ();
    }
}

void opSelect ()
{
  int input = -1;
	vector<int> ops;

	cout << "1 - GET SUBSEMIGROUP\n";
  cout << "2 - GET SEMIGROUP\n";
  cout << "3 - GET SEMIGROUP BY DEFINING RELATIONS\n";
	cout << "0 - EXIT\n\n";

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
