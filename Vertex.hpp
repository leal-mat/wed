#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/vec3.hpp>
#include <QString>

class Wed;

class Vertex{
  public:
    Vertex(int _index, Wed *_edge);
    Vertex(int _index);
    QString debugVertex();
    
  public:
    int index;
    Wed *edge;
};

#endif // VERTEX_HPP
