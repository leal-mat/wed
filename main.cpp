#include "Mesh.hpp"
#include <iostream>
#include <QApplication>
#include "TableDialog.hpp"
#include "renderer/MyGLWidget.hpp"

void print_(glm::vec3 v){
    std::cout<< v.x << " " << v.y << " " << v.z<<"\n";
}

int main(int argc, char ** argv){
    QApplication app(argc,argv);
    Mesh m = Mesh();
    m.getMeshProperties("orisso.obj");
    m.buildMesh();
    m.createWedVector();
    m.createFaceVector();
    Wed* base_wed = m.getBaseWed();
    std::cout << "ARESTA BASE DO ORISSO: " << "<"<<base_wed->left_prev->edge.first << ", "<< base_wed->left_prev->edge.second<< ">\n";
    std::cout<<"----------------OPERADOR EV----------------\n";
    m.EV(base_wed->left_prev->start);
    std::cout<<"----------------OPERADOR EE----------------\n";
    m.EE(base_wed->left_prev);
    std::cout<<"----------------OPERADOR FE----------------\n";
    m.FE(base_wed->left_prev);
    std::cout<<"----------------OPERADOR VE----------------\n";
    m.VE(base_wed->left_prev);
    std::cout<<"----------------OPERADOR EF----------------\n";
    m.EF(base_wed->left_prev->right);
    TableDialog table;
    MyGLWidget mygl;
    auto w = m.getWedVector();
    auto f = m.getFaceVector();
    auto v = m.getVertexVector();
    
    table.makeTable(&w);
    table.makeTable(&v);
    table.makeTable(&f);
    table.showTables();
    //mygl.show();
    

    app.exec();
    
}
