#include "Wed.hpp"


Wed::Wed(pair<int, int> _edge): edge(_edge){
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


void Wed::rightNext(std::unordered_multimap<pair<int,int>, glm::vec3, KeyHasher> *edge_face_map,
                    std::unordered_multimap<pair<int,int>, Wed*, KeyHasher> *edge_creation_map, 
                    std::unordered_multimap<glm::vec3, Face*, KeyHasher2> *face_map,
                    std::vector<std::pair<glm::vec3, Vertex*>> *vertex_vector){
    // Primeiro passo:
    // Descobrir a face(talvez, não sei) e qual é o próximo
    auto it = edge_face_map->find(edge);

    glm::vec3 face1 = (*it).second;
    pair<int,int> par1 = (*it).first;

    glm::vec3 face2 = (*++it).second;
    pair<int,int> par2(0, 0);

    // Checando se face2 é diferente de (0,0,0) para que possamos obter o par2
    if(face2 != glm::vec3(0.)){
        par2 = (*it).first;
    }

    auto face_pair = checkFaceMap(face1, face2, face_map);
    right = face_pair.second;
    left = face_pair.first;
    end = checkVertexVector(edge.second, vertex_vector);



    pair<int, int> next_pair(0,0);
    // esses ifs não sei se estão corretos ou se bastam
    if(edge.first == par1.first && edge.second == par1.second) {
        // sei lá
        if(par1.first == face1.x){
            next_pair.first=face1.y;
            next_pair.second=face1.z;
        }
        else if(par1.first == face1.y){
            next_pair.first=face1.z;
            next_pair.second=face1.x;
        }
        else if(par1.first == face1.z){
            next_pair.first=face1.x;
            next_pair.second=face1.y;
        }
    }
    else if(face2 != glm::vec3(0.) && edge.first == par2.first && edge.second == par2.second) {
        // sei lá
        if(par2.first == face2.x){
            next_pair.first=face2.y;
            next_pair.second=face2.z;
        }
        else if(par2.first == face2.y){
            next_pair.first=face2.z;
            next_pair.second=face2.x;
        }
        else if(par2.first == face2.z){
            next_pair.first=face2.x;
            next_pair.second=face2.y;
        }
    }
    // Segundo Passo:
    // Achado a aresta rn, alteramos seus parâmetros corretamente


    
    // TODO
    // Falta adicionar a verificação se o valor da face e Wed já foram criados previamente, caso não tenha sido criar em alguma condição


    auto it_edge = edge_creation_map->find(next_pair);
    Wed *rn = (*it_edge).second;
    this->right_next = rn;
    if (rn->status == STATUS::NOT_CREATED){
      rn->status == STATUS::CREATED;
      rn->right_prev = this;
      rn->start = checkVertexVector(edge.first, vertex_vector);
    }
    else{
        if (rn->right_prev == nullptr) {
          rn->right_prev = this;
          rn->start = checkVertexVector(edge.first, vertex_vector);
        }
        else {
          rn->left_prev = this;
        }
    }
    // Terceiro Passo
    // Chamar a recursão do rn
    rn->rightNext(edge_face_map, edge_creation_map, face_map, vertex_vector);
    rn->leftNext(edge_face_map, edge_creation_map, face_map, vertex_vector);
}



void Wed::leftNext(std::unordered_multimap<pair<int,int>, glm::vec3, KeyHasher> *edge_face_map,
                    std::unordered_multimap<pair<int,int>, Wed*, KeyHasher> *edge_creation_map,
                    std::unordered_multimap<glm::vec3, Face*, KeyHasher2> *face_map,
                    std::vector<std::pair<glm::vec3, Vertex*>> *vertex_vector){
    return;
}



Vertex* Wed::checkVertexVector(int index, std::vector<std::pair<glm::vec3, Vertex*>> *vertex_vector){
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

std::pair<Face*, Face*> Wed::checkFaceMap(glm::vec3 face1, glm::vec3 face2, 
                                            std::unordered_multimap<glm::vec3, Face*, KeyHasher2> *face_map){
    std::pair<Face *, Face *> return_face;

    auto face1_iterator = face_map->find(face1);
    auto face2_iterator = face_map->find(face2);
    if(face1_iterator != face_map->end()) {
        return_face.second = (*face1_iterator).second;
    }
    else{
        return_face.second = new Face(this);
        face_map->insert({face1, return_face.second});
    }

    if(face2_iterator != face_map->end()) {
        return_face.first = (*face2_iterator).second;
    }
    else{
        return_face.first = new Face(this);
        face_map->insert({face2, return_face.first});
    }

    return return_face;
}




