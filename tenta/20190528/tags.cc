#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
using namespace std;

int main()
{
    ifstream ifs{"names.txt"};
    map<string, set<string>> tags;
    for ( string line; getline(ifs, line); ) {
        istringstream iss {line};
        string name;
        getline(iss, name, ':');
        for_each(istream_iterator<string>{iss}, istream_iterator<string>{},
                [&tags, name](string tag){ tags[tag].insert(name); });
    }
    set<string> input_tags;
    
    copy(istream_iterator<string>{cin}, istream_iterator<string>{},
            inserter(input_tags, begin(input_tags)));
    
    set<string> common_names{tags[*begin(input_tags)]};
    
    for_each(next(begin(input_tags)), end(input_tags),
            [&common_names, &tags](string tag){
                set<string> common;
                set_intersection(begin(tags[tag]), end(tags[tag]),
                                 begin(common_names), end(common_names),
                                 inserter(common, common.begin()));
                common_names = common;
            });
    copy(begin(common_names), end(common_names), ostream_iterator<string>{cout, "\n"});

}