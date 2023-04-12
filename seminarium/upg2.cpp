#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;



int main()
{
    vector<int> c{};
    // 1. Skapa en lämplig behållare

    copy(istream_iterator<int>{cin},istream_iterator<int>{}, std::back_inserter(c));

    sort(c.begin(), c.end());
    int total = c.size();
    
    auto last = unique(c.begin(), c.end());
    c.erase(last, c.end());


    copy(c.begin(), c.end(), ostream_iterator<int>{cout, " "});
    cout << endl;
    // for(int i = 0; i < c.size(); i++) {
    //     cout << c[i] << " ";
    // }
    // cout << endl;
    cout << "Number of duplicates: " << total-c.size() << endl;
}
