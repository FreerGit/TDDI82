#include <vector>
#include <list>
#include <iostream>
#include <cctype>
#include <iterator>

// PAIRS
template <typename It>
auto get_pairs(It begin, It end)
{
    using value_type = typename It::value_type;
    
    std::vector<std::pair<value_type, value_type>> pairs { };
    for (It current { begin }; current != end; ++current) {
        for (It next { std::next(current) }; next != end; ++next) {
            pairs.emplace_back(*current, *next);
        }
    }
    return pairs;
}
