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
    glm::vec3 pos;
    glm::vec3 color;
    int index;
    Wed *edge;
    bool visit;
};

#endif // VERTEX_HPP
