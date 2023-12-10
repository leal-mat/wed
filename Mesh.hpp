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
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility>
#include <filesystem>
#include <QString>
#include <QDir>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "renderer/GLObject.hpp"

class MyGLWidget;

class Mesh : public GLObject{
public:
  Mesh(QOpenGLContext * context = nullptr);
  void buildMesh();
  void getMeshProperties(std::string fileName);
  void createWedVector();
  void createFaceVector();
  void createVertexesVector();
  std::vector<Wed *> & getWedVector();
  std::vector<Face *> & getFaceVector();
  std::vector<Vertex*> & getVertexesVector();
  Wed* consultEdgeCreationMap(pair<int, int> _edge);
  Vertex* consultVertexesVector(int index);
  Vertex* consultVertexesVector(pair<int, int> _edge);
  Face* consultFaceVector(pair<int, int> _edge);
  void updateMesh();
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
  void setGLWidget(MyGLWidget *);
  void clearMarkedEdges();
private:
  std::vector<Wed *> wed_vector;
  std::vector<Face *> face_vector;
  std::vector<Vertex *> vertexes_vector;
  Wed *base_wed;
  std::vector<Vertex> raw_vertexes_vector;

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
  std::vector<uint> edges_idx_vector;
  std::vector<uint> marked_idx_vector;

  MyGLWidget * glWidget;
};

#endif //MESH_HPP
