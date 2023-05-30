#include <algorithm>
#include <string>
#include <iterator>
#include <iostream>
#include <vector>

using namespace std;

bool are_anagrams(string const& word1, string const& word2)
{
  if (word1.size() != word2.size())
    return false;
  return is_permutation(begin(word1), end(word1), begin(word2));
}

int main()
{
  cout << "Mata in ett ord: ";
  string word;
  cin >> word;
  cout << "Mata in en text: ";
  vector<string> words {istream_iterator<string>{cin},
                        istream_iterator<string>{}};
  
  words.erase(remove_if(begin(words), end(words),
                        [&word](string const& other)
                        {
                          return are_anagrams(word, other);
                        }), end(words));

  copy(begin(words), end(words), ostream_iterator<string>{cout, " "});
  cout << endl;
}