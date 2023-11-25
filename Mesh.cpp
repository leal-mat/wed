#include "Mesh.hpp"
#include <utility>
#include <filesystem>
#include <QString>
#include <QDir>
#include <fstream>
#include <iostream>
#include <algorithm>

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
    }
}


Mesh::Mesh(){

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
        faces.reserve(6);
        faces.resize(6);
        while (std::getline(myObj, result))
        {
            if (result[0] == 'v' && result[1] == ' ')
            {
                // std::cout << result << "\n";
                getValues(result[0], &points, result.substr(2, result.size() - 1));
                glm::vec3 vertex(points.at(0), points.at(1), points.at(2));
                vertex_vector.emplace_back(std::make_pair(vertex, new Vertex(vec_counter++)));
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
                // Wed* e1 = new Wed(edge1);
                // Wed* e2 = new Wed(edge2);
                // Wed* e3 = new Wed(edge3);
                // auto it = face_map.find(indexes);
                // if(it != face_map.end()){
                //     face_map.insert({indexes, new Face(e1)});
                // }
                // edge_creation_map.insert({edge1, e1});
                // edge_creation_map.insert({edge2, e2});
                // edge_creation_map.insert({edge3, e3});
            }
        }
    }
    // std::cout << "Vertices\n";
    // for (int i = 0; i < point_vec.size(); i++)
    // {
    //     std::cout << point_vec.at(i).x << " " << point_vec.at(i).y << " " << point_vec.at(i).z << "\n";
    // }
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
    return;
}


void Mesh::buildMesh() {
    base_wed = new Wed((*edge_face_map.begin()).first);
    base_wed->status = STATUS::CREATED;
    pair<int, int> firstEdge = (*edge_face_map.begin()).first;
    edge_creation_map.insert({firstEdge, base_wed});
    base_wed->rightNext(&edge_face_map, &edge_creation_map, &face_map, &vertex_vector);
    base_wed->leftNext(&edge_face_map, &edge_creation_map, &face_map, &vertex_vector);
    return;
}

void Mesh::createWedVector(){
    for (auto elem : edge_creation_map) {
        wed_vector.push_back(elem.second);
    }
}

std::vector<Wed *> Mesh::getWedVector(){
    return wed_vector;
}