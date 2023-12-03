#ifndef MESH_HPP
#define MESH_HPP

#include "Wed.hpp"

#include <set>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include "Utils.hpp"
#include <numeric>
#include "renderer/GLObject.hpp"


class Mesh : public GLObject{
public:
  Mesh(QOpenGLContext * context = nullptr);
  void buildMesh();
  void getMeshProperties(std::string fileName);
  void createWedVector();
  void createFaceVector();
  void createVertexesVector();
  std::vector<Wed *> getWedVector();
  std::vector<Face *> getFaceVector();
  std::vector<Vertex*> getVertexesVector();
  Wed* getBaseWed();
  void markFace(Face* face);
  void markEdge(Wed* edge);
  void markVertex(Vertex* vertex);
  void EV(Vertex* v);
  void EE(Wed* e);
  void FE(Wed* e);
  void VE(Wed* e);
  void EF(Face* face);
  void draw() override;
  void init() override;
private:
  std::vector<Wed *> wed_vector;
  std::vector<Face *> face_vector;
  std::vector<Vertex *> vertexes_vector;
  Wed *base_wed;

  // Mapa de indice aresta<int,int> para vec3 de indices face 
  std::unordered_multimap<pair<int,int>, glm::vec3, KeyHasher> edge_face_map;
  
  // Mapa de indice aresta para objetos Wed
  std::unordered_multimap<pair<int,int>, Wed*, KeyHasher> edge_creation_map;

  // Mapa de vec3 indices de face para objetos Face
  std::unordered_multimap<glm::vec3, Face*, KeyHasher2> face_map;

  // Array de par <Coordenadas de vertice, Vertex*>
  std::vector<std::pair<glm::vec3, Vertex*>> vertex_vector;

  // Index Vector
  std::vector<uint> idxVector;
};

#endif //MESH_HPP
