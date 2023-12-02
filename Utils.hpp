#ifndef UTILS_HPP
#define UTILS_HPP

#include <unordered_map>
#include <functional>
#include <glm/vec3.hpp>

template <typename T,typename Q>
struct pair{
    T first;
    T second;

    pair(T _first, Q _second){
      first = _first;
      second = _second;
    }
    
    bool operator==(const pair &other) const
    { 
        return (first == other.first && second == other.second) || (first == other.second && second == other.first);
    }
};

struct KeyHasher
{
  std::size_t operator()(const pair<int,int>& k) const
  {
    return (std::hash<int>()(k.first) ^ std::hash<int>()(k.second));
  }
};


struct KeyHasher2
{
  std::size_t operator()(const glm::vec3& k) const
  {
    return ( ( std::hash<float>() (k.x) ^ (std::hash<float>()(k.y) << 1)) >> 1) ^ (std::hash<float>()(k.z) << 1);
  }
};


#endif //UTILS_HPP
