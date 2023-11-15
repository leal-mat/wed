#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/vec3.hpp>

class Wed;

class Vertex{
  public:
    glm::vec3 point;
    Wed *edge;
};

#endif // VERTEX_HPP