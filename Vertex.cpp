#include "Vertex.hpp"

Vertex::Vertex(int _index, Wed *_edge) : index(_index), edge(_edge){

}

Vertex::Vertex(int _index)  : index(_index) {
    edge = nullptr;
}

QString Vertex::debugVertex(){
    std::string s = std::to_string(index);
    return QString::fromStdString(s);
}
