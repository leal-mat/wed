#ifndef GL_OBJECT_H
#define GL_OBJECT_H

#include <stdlib.h>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLContext>
#include <glm/vec3.hpp>
#include "GLProgram.hpp"
#include <vector>
#include <QObject>



//struct Vertex{
//  glm::vec3 position;
//  glm::vec3 color;
//};

class GLObject : public QObject{
  Q_OBJECT
  public:
  GLObject() : QObject(){}
  virtual ~GLObject() = default;
  virtual void draw() = 0;
  virtual void init() = 0;
  GLProgram & getProgram(uint idx){
    return program[idx];
  }

  protected:
  std::vector<GLProgram> program;
  QOpenGLFunctions_3_3_Core * f;
  std::vector<uint> VBO;
  std::vector<uint> VAO;
  std::vector<uint> EBO;
  QOpenGLContext * currentContext;
  //std::vector<Vertex> vertexVector;

};

#endif