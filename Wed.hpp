#ifndef WED_HPP
#define WED_HPP
#include "Vertex.hpp"
#include "Utils.hpp"
#include "Face.hpp"
#include <QString>
#include <string>

enum STATUS{
  CREATED,
  NOT_CREATED
};

class Wed{
  public:
    Wed(pair<int, int> _edge = pair<int,int>(-1,-1));
    ~Wed();
    pair<int, int> edge;
    Vertex *start, *end;
    Face *left, *right;
    Wed *left_prev, *left_next;
    Wed *right_prev, *right_next;
    STATUS status;
    bool visit;


    void rightNext(std::unordered_multimap<pair<int,int>, glm::vec3, KeyHasher> *edge_face_map,
                    std::unordered_multimap<pair<int,int>, Wed*, KeyHasher> *edge_creation_map, 
                    std::unordered_multimap<glm::vec3, Face*, KeyHasher2> *face_map,
                    std::vector<std::pair<glm::vec3, Vertex*>> *vertex_vector);

    void leftNext(std::unordered_multimap<pair<int,int>, glm::vec3, KeyHasher> *edge_face_map,
                  std::unordered_multimap<pair<int,int>, Wed*, KeyHasher> *edge_creation_map,
                  std::unordered_multimap<glm::vec3, Face*, KeyHasher2> *face_map, 
                  std::vector<std::pair<glm::vec3, Vertex*>> *vertex_vector);

    Vertex* checkVertexVector(int index, 
                             std::vector<std::pair<glm::vec3, Vertex*>> *vertex_vector);
    std::pair<Face*, Face*> checkFaceMap(glm::vec3 face1, glm::vec3 face2, 
                                         std::unordered_multimap<glm::vec3, Face*, KeyHasher2> *face_map);
    Wed * checkWedMap(pair<int,int>,
                      std::unordered_multimap<pair<int,int>, Wed*, KeyHasher> *edge_creation_map,
                      std::vector<std::pair<glm::vec3, Vertex*>> *vertex_vector);

    QString debugWed();

    
};
#endif // WED_HPP
