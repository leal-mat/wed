#include "Mesh.hpp"
#include <utility>
#include <filesystem>
#include <QString>
#include <QDir>
#include <fstream>
#include <iostream>
#include <algorithm>

Wed* Mesh::getBaseWed(){
    return base_wed;
}

void getValues(const char &t, std::vector<float> *vec, std::string str)
{

    if (t == 'v')
    {

        std::stringstream ss(str);
        std::string result = "";
        int pos = 0;
        while (std::getline(ss, result, ' '))
        {
            vec->at(pos) = std::stof(result, 0);
            pos++;
        }
    }
    else if (t == 'f')
    {
        std::stringstream ss(str);
        std::string result = "";
        int pos = 0;
        int index = 0;
        while (std::getline(ss, result, ' '))
        {
            std::stringstream new_stream(result);
            std::string face;
            std::getline(new_stream, face, '/');
            vec->at(pos++) = std::stof(face) - 1;
        }
        std::reverse(vec->begin(), vec->end());
    }
}


Mesh::Mesh() {

}

void Mesh::getMeshProperties(std::string fileName)
{ 
    QDir dir(QDir::currentPath());
    dir.cdUp();

    QString path = dir.path();
    std::string result = "";
    std::fstream myObj;
    myObj.open(path.toStdString() + "/objects/" + fileName, std::ios::in);
    std::cout << std::fixed;
    std::cout << std::setprecision(4);
    int vec_counter = 0;
    if (myObj.is_open())
    {
        std::vector<float> points;
        std::vector<float> faces;
        points.reserve(3);
        points.resize(3);
        faces.reserve(3);
        faces.resize(3);
        while (std::getline(myObj, result))
        {
            if (result[0] == 'v' && result[1] == ' ')
            {
                getValues(result[0], &points, result.substr(2, result.size() - 1));
                glm::vec3 vertex(points.at(0), points.at(1), points.at(2));
                vertex_vector.emplace_back(std::make_pair(vertex, nullptr/*new Vertex(vec_counter++)*/));
            }
            else if (result[0] == 'f' && result[1] == ' ')
            {
                getValues(result[0], &faces, result.substr(2, result.size() - 1));
                pair<int, int> edge1(faces.at(0), faces.at(1));
                pair<int, int> edge2(faces.at(1), faces.at(2));
                pair<int, int> edge3(faces.at(2), faces.at(0));
                glm::vec3 indexes(faces.at(0), faces.at(1), faces.at(2));
                edge_face_map.insert({edge1, indexes});
                edge_face_map.insert({edge2, indexes});
                edge_face_map.insert({edge3, indexes});

            }
        }
    }
    //unordered multimap:
    std::cout << "Indices\n";
    for (auto elem : edge_face_map) {
      std::cout << "(" << elem.first.first << ", " << elem.first.second << "); "<<
      "face: " << elem.second.x << " " << elem.second.y<< " " << elem.second.z << std::endl;
    }
    std::cout<<"Teste\n";
    pair<int,int> t1(4,2);
    auto v = edge_face_map.find(t1);
    std::cout<<"Quantidade de valores nessa key: " << edge_face_map.count(t1)<<std::endl;
    while(v != edge_face_map.end()) {
        auto i = *v;
        std::cout<< "face: " << i.second.x << " " << i.second.y<< " " << i.second.z << std::endl;
        v++;
    }
    //exit(-1);
    return;
}

void Mesh::init(){
 
  //pontos e linhas, por enquanto...
  VAO.reserve(2);
  VAO.resize(2);


  VBO.reserve(2);
  VBO.resize(2);

  EBO.reserve(2);
  EBO.resize(2);

  program.reserve(2);
  program.resize(2);

  idxVector.reserve(vertex_vector.size());
  idxVector.resize(vertex_vector.size());
  std::iota(idxVector.begin(),idxVector.end(),0);

  
  for(int i = 0; i < 4; i++){
    f->glGenVertexArrays(1,&VAO[i]);
    f->glGenBuffers(1,&VBO[i]);
    f->glGenBuffers(1,&EBO[i]);
    program[i] = GLProgram(currentContext);
  }

  //gpe
  program[0].createShaderFromFile("polShader.vert","polShader.frag");
  //fill
  //program[1].createShaderFromFile("fill_vertex.vert","fill_frag.frag");
  //std::cout<<"Criou Shader\n";

  std::cout<<"gerou buffers\n";
  //Points initialization, index 0

  f->glBindVertexArray(VAO[0]);
  
  f->glBindBuffer(GL_ARRAY_BUFFER,VBO[0]);
  f->glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3) * vertex_vector.size(), vertex_vector.data(),GL_DYNAMIC_DRAW);




  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
  f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * idxVector.size(),idxVector.data(),GL_DYNAMIC_DRAW);



  GLint position_attribute = f->glGetAttribLocation(program[0].getProgramId(), "position");

  f->glVertexAttribPointer(position_attribute,3,GL_FLOAT,GL_FALSE,sizeof(glm::vec3),0);

  f->glEnableVertexAttribArray(position_attribute);

  f->glBindBuffer(GL_ARRAY_BUFFER,0); //unbid current VBO
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); //unbid current EBO
  f->glBindVertexArray(0); //unbind current VAO


  //lines
  f->glBindVertexArray(VAO[1]);
  
  f->glBindBuffer(GL_ARRAY_BUFFER,VBO[1]);
  f->glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3) * vertex_vector.size(), vertex_vector.data(),GL_DYNAMIC_DRAW);



  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
  f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::pair<uint,uint>) * wed_vector.size() ,wed_vector.data(),GL_DYNAMIC_DRAW);



  GLint position_attribute1 = f->glGetAttribLocation(program[0].getProgramId(), "position");

  ///////////////////////////f->glVertexAttribPointer(position_attribute1,3,GL_FLOAT,GL_FALSE,sizeof(Vec3),0);

  f->glEnableVertexAttribArray(position_attribute1);

  
  //f->glVertexAttribPointer(position_attribute11,3,GL_FLOAT,GL_FALSE,sizeof(Vec3),0);

  //f->glEnableVertexAttribArray(position_attribute11);

  f->glBindBuffer(GL_ARRAY_BUFFER,0); //unbid current VBO
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); //unbid current EBO
  f->glBindVertexArray(0); //unbind current VAO


  //grid triangles
  f->glBindVertexArray(VAO[2]);
  
  f->glBindBuffer(GL_ARRAY_BUFFER,VBO[2]);
  //////////////////////////////////f->glBufferData(GL_ARRAY_BUFFER,sizeof(Triangle) * 1000000, gridTriangles.data(),GL_DYNAMIC_DRAW);
  // p1x | p1y | p1z | r | g | b | p2x | p2y | p2z | r | g | b | p3x | p3y | p3z | r | g | b |
  // <      12     >



  //f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
  //f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::pair<uint,uint>) * handHull.lVec().size() ,handHull.lVec().data(),GL_DYNAMIC_DRAW);



  GLint position_attribute2 = f->glGetAttribLocation(program[0].getProgramId(), "position");

  f->glVertexAttribPointer(position_attribute2,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),0);

  f->glEnableVertexAttribArray(position_attribute2);

  


  f->glBindBuffer(GL_ARRAY_BUFFER,0); //unbid current VBO
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); //unbid current EBO
  f->glBindVertexArray(0); //unbind current VAO


  //fill triangles
  f->glBindVertexArray(VAO[3]);
  
  f->glBindBuffer(GL_ARRAY_BUFFER,VBO[3]);
  ///////////////////////////f->glBufferData(GL_ARRAY_BUFFER,sizeof(Triangle) * 1000000, triangles.data(),GL_DYNAMIC_DRAW);
  // p1x | p1y | p1z | r | g | b | p2x | p2y | p2z | r | g | b | p3x | p3y | p3z | r | g | b |
  // <      12     >



  //f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
  //f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::pair<uint,uint>) * handHull.lVec().size() ,handHull.lVec().data(),GL_DYNAMIC_DRAW);



  GLint position_attribute3 = f->glGetAttribLocation(program[1].getProgramId(), "position");
  GLint position_attribute31 = f->glGetAttribLocation(program[1].getProgramId(), "color_a");

  f->glVertexAttribPointer(position_attribute3,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),0);

  f->glEnableVertexAttribArray(position_attribute3);

  
  //////////////////////////f->glVertexAttribPointer(position_attribute31,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)(sizeof(Vec3)));

  f->glEnableVertexAttribArray(position_attribute31);

  f->glBindBuffer(GL_ARRAY_BUFFER,0); //unbid current VBO
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); //unbid current EBO
  f->glBindVertexArray(0); //unbind current VAO

}


void Mesh::buildMesh() {
    base_wed = new Wed((*edge_face_map.begin()).first);
    base_wed->status = STATUS::CREATED;
    pair<int, int> firstEdge = (*edge_face_map.begin()).first;
    edge_creation_map.insert({firstEdge, base_wed});
    base_wed->rightNext(&edge_face_map, &edge_creation_map, &face_map, &vertex_vector);
    // std::cout<<"saiu do rightnext\n";
    base_wed->leftNext(&edge_face_map, &edge_creation_map, &face_map, &vertex_vector);
    return;
}

void Mesh::createWedVector(){
    int cont=0;
    for (auto elem : edge_creation_map) {
        
        wed_vector.push_back(elem.second);
        // 337, 352
        if(elem.second->edge.first == 337 && elem.second->edge.second == 352) {
            std::cout << "A POSICAO DO BASE WED EH ESSA: " << cont+1 << "\n";
        }
        cont++;
    }
}

void Mesh::createFaceVector(){
    for (auto elem : face_map) {
        face_vector.push_back(elem.second);
    }
}

std::vector<Wed *> Mesh::getWedVector() {
    return wed_vector;
}

std::vector<Face *> Mesh::getFaceVector() {
    return face_vector;
}

std::vector<std::pair<glm::vec3, Vertex*>> Mesh::getVertexVector() {
    return vertex_vector;
}

// dado vértice, encontrar arestas adjacentes
void Mesh::EV(Vertex* v) {
    Wed* e0 = v->edge;
    Wed* edge = e0;
    do
    {
        if (edge->end == v) {
            edge = edge->right_next; 
        }
        else {
            edge = edge->left_next; 
        }
        markEdge(edge);
    } while (edge != e0);
    return;
}


// dado aresta, encontrar arestas adjacentes
void Mesh::EE(Wed* e) {
    EV(e->start);
    EV(e->end);
    return;
}

// dado aresta, encontrar faces adjacentes
void Mesh::FE(Wed* e) {
    markFace(e->right);
    markFace(e->left);
    return;
}

// dado aresta, encontrar vértices adjacentes
void Mesh::VE(Wed* e){
     markVertex(e->start);
     markVertex(e->end);
}

// dado face, encontrar arestas adjacentes
void Mesh::EF(Face* face){
    Wed* e0 = face->edge;
    Wed* edge = e0;
    do
    {
        if (edge->right == face){
            std::cout<<"EF==\n";
            edge=edge->right_prev;
        }
        else {
            edge=edge->left_prev;
        }
        markEdge(edge);
    } while (edge!=e0);
}

void Mesh::markFace(Face* face){
    face->visit = true;
    std::cout<<"Visitei face da aresta: " << "<" << face->edge->edge.first << ", "<< face->edge->edge.second<<">\n";
}

void Mesh::markEdge(Wed* edge){
    edge->visit = true;
    std::cout << "Visitei a aresta: " << "<" << edge->edge.first << ", "<< edge->edge.second << ">\n";
}

void Mesh::markVertex(Vertex* vertex){
    vertex->visit = true;
    std::cout << "Visitei o vértice: " << "<" << vertex->edge->edge.first << ", "<< vertex->edge->edge.second << ">\n";
}

void Mesh::Draw(){

}