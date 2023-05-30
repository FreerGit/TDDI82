#include <utility>
#include <vector>
#include <list>
#include <forward_list>
#include <string>
#include <iostream>

template <typename It1, typename It2>
class zip_iterator
{
public:
    zip_iterator(It1 begin1, It1 end1, It2 begin2, It2 end2)
	: begin1  { begin1 } , end1  { end1 },
	  begin2 { begin2 }, end2 { end2 } {}

    auto operator*() const {
	    return std::make_pair(*begin1, *begin2);
    }

    bool operator==(zip_iterator const& other) const  {
        if (begin1 == end1 && other.begin1 == other.end1)
            return true;

        if (begin2 == end2 && other.begin2 == other.end2)
            return true;
	    return begin1 == other.begin1 && begin2 == other.begin2;
    }

    bool operator!=(zip_iterator const& other) const {
	    return !(*this == other);
    }
    
    zip_iterator& operator++() {
        ++begin1;
        ++begin2;
        return *this;
    }

    zip_iterator operator++(int) {
        zip_iterator tmp { *this };
        ++*this;
        return tmp;
    }
    
private:
    It1 begin1;
    It1 end1;
    
    It2 begin2;
    It2 end2;
    
};