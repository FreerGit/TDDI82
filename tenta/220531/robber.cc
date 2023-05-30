#include <algorithm>
#include <vector>
#include <iterator>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

std::string const vowels{"aeiouy"};

std::string encode(std::string word) {
  std::ostringstream oss{};
  std::transform(word.begin(), word.end(), 
	    std::ostream_iterator<string> { oss },
            [](char c) {
		if (std::isalpha(c)) {
		    auto it = std::find(vowels.begin(), vowels.end(), c);
		    if (it == vowels.end())
			return std::string { c, 'o', c };
		}
		return std::string { c };
            });
  
  return oss.str();
}

int main() {
    cout << "Mata in din text: ";

    std::vector<std::string> words { std::istream_iterator<std::string> { cin }, 
                    std::istream_iterator<std::string> { } };

    std::transform(words.begin(), words.end(), words.begin(), 
            [](std::string const& word) 
            { 
                return encode(word); 
            });

    std::copy(words.begin(), words.end(), 
        std::ostream_iterator<string>{std::cout, " "});
    std::cout << endl;
}