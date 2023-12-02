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
class MyGLWidget : public QOpenGLWidget{

  Q_OBJECT
public:
  MyGLWidget(QWidget * parent = 0);
  ~MyGLWidget();
  bool event(QEvent *event) override;

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

signals:
  

public slots:
  void updateScene();
  void initTimer();

//private:

private:

  QOpenGLFunctions_3_3_Core * f;

  private:

};


#endif