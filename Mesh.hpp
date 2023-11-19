#ifndef MESH_HPP
#define MESH_HPP

#include "Wed.hpp"

#include <set>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include "Utils.hpp"

// template <typename T,typename Q>
// struct pair{
//     T first;
//     T second;

//     pair(T _first, Q _second){
//       first = _first;
//       second = _second;
//     }
    
//     bool operator==(const pair &other) const
//     { 
//         return (first == other.first && second == other.second) || (first == other.second && second == other.first);
//     }
// };

// struct KeyHasher
// {
//   std::size_t operator()(const pair<int,int>& k) const
//   {
//     return (std::hash<int>()(k.first) ^ std::hash<int>()(k.second));
//   }
// };

class Mesh{
public:
  void buildMesh();
  void getMeshProperties(std::string fileName);
private:
  std::vector<Wed> wed_vector;
  Wed *base_wed;
  std::unordered_multimap<pair<int,int>, glm::vec3, KeyHasher> edge_face_map;
  std::unordered_multimap<pair<int,int>, Wed*, KeyHasher> edge_creation_map;
  std::unordered_multimap<glm::vec3, Face*, KeyHasher2> face_map;
  std::vector<std::pair<glm::vec3, Vertex*>> vertex_vector;
};

#endif //MESH_HPP
