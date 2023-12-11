#include "Vertex.hpp"
#include "Wed.hpp"

Vertex::Vertex(int _index, Wed *_edge) : index(_index), edge(_edge){
    visit = false;
}

Vertex::Vertex(int _index)  : index(_index) {
    edge = nullptr;
    visit = false;
}

QString Vertex::debugVertex(){
    std::string s = std::to_string(index);
    if(edge != nullptr){
        return edge->debugWed() + QString(", ") + QString::fromStdString(std::to_string(index));
    }
    return "null";
}
