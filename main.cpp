#include "Mesh.hpp"
#include <iostream>
#include <QApplication>
#include "TableDialog.hpp"
#include "renderer/MyGLWidget.hpp"
#include "MainWidget.hpp"

void print_(glm::vec3 v){
    std::cout<< v.x << " " << v.y << " " << v.z<<"\n";
}

int main(int argc, char ** argv){
    QApplication app(argc,argv);


    MainWidget mw = MainWidget();
    

    app.exec();
    
}
