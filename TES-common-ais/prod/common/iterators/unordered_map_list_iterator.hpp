
#ifndef UNODERED_MAP_LIST_ITERATOR
#define UNODERED_MAP_LIST_ITERATOR

#include <list>
#include <unordered_map>

// An iterator over an unordered_map of lists
template <typename K, typename T>
class unordered_map_list_iterator : public std::iterator<std::bidirectional_iterator_tag, T>
{
public:
  static unordered_map_list_iterator<K, T> begin(std::unordered_map<K, std::list<T>> &container)
  {
    return unordered_map_list_iterator(container, container.begin());
  }

  static unordered_map_list_iterator<K, T> end(std::unordered_map<K, std::list<T>> &container)
  {
    return unordered_map_list_iterator(container, container.end());
  }

  unordered_map_list_iterator() = default;
  // ++prefix operator
  unordered_map_list_iterator &operator++()
  {
    // If we haven't reached the end of the sub-list
    if (countInner < itOuter->second.size())
    {
      // Go to the next element.
      ++countInner;
      ++itInner;
    }
    else if (countOuter == container.size())
    {
      // If we've reached the end of the container, set itOuter to end
      itOuter = container.end();
    }
    else
    {
      // Otherwise skip to the next sub-vector, and keep skipping over empty
      // ones until we reach a non-empty one or the end.
      do
      {
        ++countOuter;
        ++itOuter;
      } while ((countOuter < container.size()) && itOuter->second.empty());

      // Go to the start of this vector.
      countInner = 1;
      itInner = itOuter->second.begin();
    }
    return *this;
  }
  // --prefix operator
  unordered_map_list_iterator &operator--()
  {
    // If we haven't reached the start of this sub-vector.
    if (countInner > 1)
    {
      // Go to the previous element.
      --countInner;
      --itInner;
    }
    else if (countOuter > 1)
    {
      // Otherwise skip to the previous sub-vector, and keep skipping over empty
      // ones until we reach a non-empty one.
      do
      {
        --countOuter;
        --itOuter;
      } while (itOuter->second.empty());

      // Go to the end of this vector.
      itInner = itOuter->second.end();
      countInner = itInner->size();
    }
    return *this;
  }
  // postfix++ operator
  unordered_map_list_iterator operator++(int)
  {
    auto temp(*this);
    ++(*this);
    return temp;
  }
  // postfix-- operator
  unordered_map_list_iterator operator--(int)
  {
    auto temp(*this);
    --(this);
    return temp;
  }
  bool operator==(const unordered_map_list_iterator &other) const
  {
    if (other.itOuter == itOuter)
    {
      return (itOuter == container.end()) || (other.itInner == itInner);
    }
    return false;
  }
  bool operator!=(const unordered_map_list_iterator &other) const
  {
    return !(*this == other);
  }
  const T &operator*() const
  {
    return *this;
  }
  T &operator*()
  {
    return *itInner;
  }
  const T &operator->() const
  {
    return *this;
  }
  T &operator->()
  {
    return *this;
  }

private:
  unordered_map_list_iterator(std::unordered_map<K, std::list<T>> &container,
                              typename std::unordered_map<K, std::list<T>>::iterator itOuter)
      : container(container), itOuter(itOuter)
  {
    if (itOuter == container.begin())
    {
      countOuter = 1;
      itInner = itOuter->second.begin();
      countInner = 1;
    }
    else
    {
      countOuter = container.size();
    }
  }

  std::unordered_map<K, std::list<T>> &container;
  typename std::unordered_map<K, std::list<T>>::iterator itOuter;
  typename std::list<T>::iterator itInner;
  std::size_t countOuter = 0;
  std::size_t countInner = 0;
};

#endif
