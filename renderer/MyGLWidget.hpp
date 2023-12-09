#ifndef GL_WIDGET_H
#define GL_WIDGET_H

#include <QOpenGLWidget>
#include <QWidget>
#include <QOpenGLFunctions_3_3_Core>

#include <QOpenGLVersionFunctionsFactory>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLContext>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QDateTime>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>
#include <QDir>
#include <vector>
#include <cmath>
#include "GLProgram.hpp"
#include <stdlib.h>
#include <glm/vec3.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QtGlobal>
#include "Camera.hpp"
#include "../Mesh.hpp"
class MyGLWidget : public QOpenGLWidget{

  Q_OBJECT
public:
  MyGLWidget(QWidget * parent = 0);
  ~MyGLWidget();
  void keyPressEvent(QKeyEvent *event) override;

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void mousePressEvent(QMouseEvent* evt) override;
  void mouseReleaseEvent(QMouseEvent* evt) override;
  void mouseMoveEvent(QMouseEvent* evt) override;

  void setMesh(Mesh * _mesh);

  Mesh * createMesh(QString fileName);

  Camera * getCamera();

signals:
  

public slots:

  

//private:

  private:

  QOpenGLFunctions_3_3_Core * f;
  

  private:
  Mesh * mesh;
  Camera * camera;

  QPoint virtualPos;

};


#endif