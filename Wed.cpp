#include "Wed.hpp"
#include <iostream>


Wed::Wed(pair<int, int> _edge): edge(_edge) {
    start = nullptr;
    end = nullptr;
    left = nullptr;
    right = nullptr;
    left_prev = nullptr;
    left_next = nullptr;
    right_prev = nullptr;
    right_next = nullptr;
    status = STATUS::NOT_CREATED;
}

Wed::~Wed(){}

void Wed::rightNext(std::unordered_multimap<pair<int,int>, glm::vec3, KeyHasher> *edge_face_map,
                    std::unordered_multimap<pair<int,int>, Wed*, KeyHasher> *edge_creation_map, 
                    std::unordered_multimap<glm::vec3, Face*, KeyHasher2> *face_map,
                    std::vector<std::pair<glm::vec3, Vertex*>> *vertex_vector) {
    
std::cout<<"entrou no right\n";
    // Primeiro passo:
    // Verificar se já foi encontrado um right next previamente.
    // if (right_next != nullptr){
    //     // coisas
    // }
    // Descobrir a face(talvez, não sei) e qual é o próximo
    std::cout<< "Edge: " << edge.first << ", " << edge.second << "\n";
    auto it = edge_face_map->find(edge);
    //std::cout<<"Edge debug: "<<edge.first<< ", " << edge.second << "\n"; 
    //std::cout<<"Pegou o iterator\n";
    //std::cout<<"Edge: "<<edge.first << " " <<edge.second<<std::endl;
    
    if((it)==edge_face_map->end()){
        std::cout<<"meu mano era end()\n";
    }
    glm::vec3 face_right = (*it).second;
    pair<int,int> par_right = (*it).first;
    
    glm::vec3 face_left = glm::vec3(0.);
    std::cout<<"testando 1\n";
    if((++it )!=edge_face_map->end()){
        std::cout<<"testando 2\n";
        face_left = (*it).second;
    }
    
    

    pair<int,int> par_left(-1, -1);



    // Checando se face_left é diferente de (0,0,0) para que possamos obter o par_left
    std::cout << "Face Left: " << face_left.x << ", " << face_left.y << ", " << face_left.z << "\n";
    if(face_left != glm::vec3(0.))
    {
        par_left = (*it).first;
    }
    
    auto face_pair = checkFaceMap(face_right, face_left, face_map);
    std::cout << "debug 2\n";
    right = face_pair.first;
    left = face_pair.second;
    end = checkVertexVector(edge.second, vertex_vector);
    std::cout << "debug 3\n";

    pair<int, int> next_pair(-10,-10);
    // esses ifs não sei se estão corretos ou se bastam
    if(edge.first == par_right.first && edge.second == par_right.second) {
        // sei lá
        if(par_right.first == face_right.x){
            next_pair.first=face_right.y;
            next_pair.second=face_right.z;
        }
        else if(par_right.first == face_right.y){
            next_pair.first=face_right.z;
            next_pair.second=face_right.x;
        }
        else if(par_right.first == face_right.z){
            next_pair.first=face_right.x;
            next_pair.second=face_right.y;
        }
    }
    else if(face_left != glm::vec3(0.) && edge.first == par_left.first && edge.second == par_left.second) {
        // sei lá
        if(par_left.first == face_left.x){
            next_pair.first=face_left.y;
            next_pair.second=face_left.z;
        }
        else if(par_left.first == face_left.y){
            next_pair.first=face_left.z;
            next_pair.second=face_left.x;
        }
        else if(par_left.first == face_left.z){
            next_pair.first=face_left.x;
            next_pair.second=face_left.y;
        }
    }
    std::cout<< "ParRight: " << par_right.first << ", " << par_right.second << "\n";
    std::cout<< "ParLeft: " << par_left.first << ", " << par_left.second << "\n";
    std::cout<< "Next: " << next_pair.first << ", " << next_pair.second << "\n";

    // Segundo Passo:
    // Achado a aresta rn, alteramos seus parâmetros corretamente

    Wed *rn = checkWedMap(next_pair, edge_creation_map, vertex_vector);
    this->right_next = rn;

    // Terceiro Passo
    // Chamar a recursão do rn
    if (rn->right_next == nullptr)
    {
        rn->rightNext(edge_face_map, edge_creation_map, face_map, vertex_vector);
        rn->leftNext(edge_face_map, edge_creation_map, face_map, vertex_vector);
    }
}



void Wed::leftNext(std::unordered_multimap<pair<int,int>, glm::vec3, KeyHasher> *edge_face_map,
                    std::unordered_multimap<pair<int,int>, Wed*, KeyHasher> *edge_creation_map,
                    std::unordered_multimap<glm::vec3, Face*, KeyHasher2> *face_map,
                    std::vector<std::pair<glm::vec3, Vertex*>> *vertex_vector) {
    std::cout<<"Entrou no left\n";
    if (edge_face_map->count(edge) == 1){
        return;
    }
    auto it = edge_face_map->find(edge);

    // Verificar se já foi encontrado um right next previamente.
    // if (right_next != nullptr){
    //     // coisas
    // }
    glm::vec3 face_right = (*it).second;
    pair<int,int> par_right = (*it).first;

    glm::vec3 face_left = (*++it).second;
    pair<int,int> par_left(-1, -1);

    // Checando se face_left é diferente de (0,0,0) para que possamos obter o par_left
    if(face_left != glm::vec3(0.)){
        par_left = (*it).first;
    }

    auto face_pair = checkFaceMap(face_right, face_left, face_map);
    right = face_pair.first;
    left = face_pair.second;
    end = checkVertexVector(edge.second, vertex_vector);

    pair<int, int> next_pair(0,0);
    // esses ifs não sei se estão corretos ou se bastam
    if(edge.first == par_right.second && edge.second == par_right.first) {
        // sei lá
        if(par_right.first == face_right.x){
            next_pair.first=face_right.y;
            next_pair.second=face_right.z;
        }
        else if(par_right.first == face_right.y){
            next_pair.first=face_right.z;
            next_pair.second=face_right.x;
        }
        else if(par_right.first == face_right.z){
            next_pair.first=face_right.x;
            next_pair.second=face_right.y;
        }
    }
    else if(face_left != glm::vec3(0.) && edge.first == par_left.second && edge.second == par_left.first) {
        // sei lá
        if(par_left.first == face_left.x){
            next_pair.first=face_left.y;
            next_pair.second=face_left.z;
        }
        else if(par_left.first == face_left.y){
            next_pair.first=face_left.z;
            next_pair.second=face_left.x;
        }
        else if(par_left.first == face_left.z){
            next_pair.first=face_left.x;
            next_pair.second=face_left.y;
        }
    }

     
    // Segundo Passo:
    // Achado a aresta ln, alteramos seus parâmetros corretamente

    Wed *ln = checkWedMap(next_pair, edge_creation_map, vertex_vector);
    this->left_next = ln;
    
    // Terceiro Passo
    // Chamar a recursão do ln
    if (ln->right_next == nullptr)
    {
        
        ln->rightNext(edge_face_map, edge_creation_map, face_map, vertex_vector);
        
        ln->leftNext(edge_face_map, edge_creation_map, face_map, vertex_vector);
    }

    return;
}



Vertex* Wed::checkVertexVector(int index, std::vector<std::pair<glm::vec3, Vertex*>> *vertex_vector) {
    Vertex * return_vertex;
    if(vertex_vector->at(index).second != nullptr){
        return_vertex = vertex_vector->at(index).second;
    }
    else{
        return_vertex = new Vertex(index, this);
        vertex_vector->at(index).second = return_vertex;
    }
    return return_vertex;
}

std::pair<Face*, Face*> Wed::checkFaceMap(glm::vec3 face_right, glm::vec3 face_left, 
                                        std::unordered_multimap<glm::vec3, Face*, KeyHasher2> *face_map) {
                                            
    std::pair<Face *, Face *> return_face;

    auto face_right_iterator = face_map->find(face_right);
    auto face_left_iterator = face_map->find(face_left);
    
    if(face_right_iterator != face_map->end()) {
        return_face.first = (*face_right_iterator).second;
    }
    else{
        return_face.first = new Face(this);
        face_map->insert({face_right, return_face.first});
    }

    if(face_left_iterator != face_map->end()) {
        return_face.second = (*face_left_iterator).second;
    }
    else{
        if (face_left == glm::vec3(0.))
        {
            return_face.second = nullptr;
        }
        else {
            return_face.second = new Face(this);
            face_map->insert({face_left, return_face.second});
        }
    }
    return return_face;
}

Wed * Wed::checkWedMap(pair<int,int> next_pair, 
                        std::unordered_multimap<pair<int,int>, Wed*, KeyHasher> *edge_creation_map,
                        std::vector<std::pair<glm::vec3, Vertex*>> *vertex_vector) {
    auto it_edge = edge_creation_map->find(next_pair);

    Wed * return_wed;

    if (it_edge != edge_creation_map->end())
    {
        return_wed = (*it_edge).second;
        // Completando volta na face
        if (return_wed->right_prev == nullptr) {
          return_wed->right_prev = this;
        //   if(edge.first == return_wed->edge.first || edge.first == return_wed->edge.second){
        //     return_wed->start = checkVertexVector(edge.first, vertex_vector);
        //   }
        //   else{
        //     return_wed->start = checkVertexVector(edge.second, vertex_vector);
        //   }
        return_wed->start = checkVertexVector(edge.second, vertex_vector);
        }
        // return_wed ja tinha sido feita na outra face
        else {
          return_wed->left_prev = this;
        }
    }
    else {
        return_wed = new Wed(next_pair);
        return_wed->status == STATUS::CREATED;
        return_wed->right_prev = this;
        if(edge.first == return_wed->edge.first || edge.first == return_wed->edge.second){
            return_wed->start = checkVertexVector(edge.first, vertex_vector);
        }
        else{
          return_wed->start = checkVertexVector(edge.second, vertex_vector);
        }
        edge_creation_map->insert({next_pair, return_wed});
    }
    
    return return_wed;
}

QString Wed::debugWed(){
    std::string s = "<"+std::to_string(edge.first)+","+std::to_string(edge.second)+">";
    return QString::fromStdString(s);
}




