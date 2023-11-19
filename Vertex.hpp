#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/vec3.hpp>

class Wed;

class Vertex{
  public:
    Vertex(int _index, Wed *_edge): index(_index), edge(_edge){
      
    }
    int index;
    Wed *edge;
};

#endif // VERTEX_HPP
