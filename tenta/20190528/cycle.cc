using namespace std;

template <typename Container>
class Cycle
{
public:
  using value_type = typename Container::value_type;
  
  Cycle(Container& container) : container{container}
  { }

  size_t size() const {
    return container.size();
  }

  value_type const& at(int index) const {
    if (index < 0)
      throw out_of_range{"negative index"};
    return container.at(index % size());
  }

  value_type& at(int index) {
    if (index < 0)
      throw out_of_range{"negative index"};
    return container.at(index % size());
  }
  
private:
  Container& container;
  
};