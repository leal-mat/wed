#include "Mesh.hpp"

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



void Mesh::buildMesh(std::string fileName)
{ 
    QDir dir(QDir::currentPath());
    dir.cdUp();

    QString path = dir.path();
    std::string result = "";
    std::fstream myObj;
    myObj.open(path.toStdString() + "/objects/" + fileName, std::ios::in);
    std::cout << std::fixed;
    std::cout << std::setprecision(4);
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
                point_vec.emplace_back(vertex);
            }
            else if (result[0] == 'f' && result[1] == ' ')
            {
                getValues(result[0], &faces, result.substr(2, result.size() - 1));
                pair<int, int> edge1(faces.at(0),faces.at(1));
                pair<int, int> edge2(faces.at(1),faces.at(2));
                pair<int, int> edge3(faces.at(2),faces.at(0));
                glm::vec3 indexes(faces.at(0), faces.at(1), faces.at(2));
                edge_face_map.insert({edge1, indexes});
                edge_face_map.insert({edge2, indexes});
                edge_face_map.insert({edge3, indexes});
                // face_set.insert(indexes);
            }
        }
    }
    std::cout << "Vertices\n";
    for (int i = 0; i < point_vec.size(); i++)
    {
        std::cout << point_vec.at(i).x << " " << point_vec.at(i).y << " " << point_vec.at(i).z << "\n";
    }
    //unordered multimap:
    std::cout << "Indices\n";
    for (auto elem : edge_face_map){
      std::cout << "(" << elem.first.first << ", " << elem.first.second << "); "<<
      "face: " << elem.second.x << " " << elem.second.y<< " " << elem.second.z << std::endl;
    }
    std::cout<<"Teste\n";
    pair<int,int> t1(4,2);
    auto v = edge_face_map.find(t1);
    std::cout<<"Quantidade de valores nessa key: " << edge_face_map.count(t1)<<std::endl;
    while(v != edge_face_map.end()){
        auto i = *v;
        std::cout<< "face: " << i.second.x << " " << i.second.y<< " " << i.second.z << std::endl;
        v++;
    }
    return;
}
