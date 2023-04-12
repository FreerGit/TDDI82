#include <iostream>
#include <algorithm>
#include <iterator>
#include <list>

using namespace std;

template<typename collection>
void read(collection& c)
{
  typename collection::value_type number;
  while ( cin >> number )
  {
    c.push_back(number);
  }
}

template<typename collection>
void sort(collection& c)
{
  for ( auto& i : c )
  {
    for ( auto& j : c )
    {
      if ( i < j )
        swap( i, j );
    }
  }
}

template<typename collection>
void print(collection const& c)
{
  for ( auto& i : c )
  {
    cout << i << endl;
  }
}


template<typename collection>
void uniq(collection& c)
{
  auto adj = c.begin();
  for(auto it = c.begin(); it != --c.end();) {
    ++adj;
    if(*it == *adj) {
      it = c.erase(it);
    } else {
       it++;
    }
  }
}

template<typename T>
void input() {
  list<T> v;
  
  cout << "Filter unique type by hand" << endl;
  
  read(v);
  sort(v);
  uniq(v);
  print(v);
}


int main()
{
  input<int>();
  
  // cin.ignore();
  // cin.clear();
  
  // input<string>();

  // cin.ignore();
  // cin.clear();
  
  // input<double>();


}
