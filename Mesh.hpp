#ifndef MESH_HPP
#define MESH_HPP

#include <set>
#include "Wed.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

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

class Mesh{

public:
  void buildMesh(std::string fileName);
private:
  std::vector<glm::vec3> point_vec;
  std::unordered_multimap<pair<int,int>, glm::vec3, KeyHasher> edge_face_map;

};

#endif //MESH_HPP
