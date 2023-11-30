#include "Mesh.hpp"
#include <iostream>
#include <QApplication>
#include "TableDialog.hpp"

void print_(glm::vec3 v){
    std::cout<< v.x << " " << v.y << " " << v.z<<"\n";
}

int main(int argc, char ** argv){
    QApplication app(argc,argv);
    Mesh m = Mesh();
    m.getMeshProperties("orisso.obj");
    m.buildMesh();
    m.createWedVector();
    TableDialog table;
    auto s = m.getWedVector();
    table.makeTable(&s);

    app.exec();
    
}
