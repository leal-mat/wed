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
    glm::vec3 color;
    Wed *edge;
    bool visit;
};

#endif // VERTEX_HPP
