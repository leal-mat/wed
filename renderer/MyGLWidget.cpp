#include "MyGLWidget.hpp"
#include <iostream>

using qtime = QDateTime;


MyGLWidget::MyGLWidget(QWidget * parent) : QOpenGLWidget(parent){
    setFocusPolicy(Qt::TabFocus);
    setFixedSize(900,600);
}

MyGLWidget::~MyGLWidget(){
    
    //f->glDeleteBuffers(1,&pointsVBO);
}

void MyGLWidget::initializeGL() {

    //f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_3_Core>();
    f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_3_Core>(context());
    f->initializeOpenGLFunctions();
    f->glEnable(GL_DEPTH_TEST);
	  f->glEnable(GL_DEPTH_CLAMP);
    f->glEnable(GL_BLEND);
    f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	  f->glEnable(GL_LINE_SMOOTH);
	  f->glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    f->glEnable(GL_PROGRAM_POINT_SIZE);
    f->glPointSize(2);
    f->glLineWidth(1);



    f->glClearColor(45.0/255., 63/255., 133/255.,1.0f);

}

void MyGLWidget::paintGL(){
  

}


void MyGLWidget::resizeGL(int w, int h){


}

void MyGLWidget::initTimer(){
}


void MyGLWidget::updateScene(){

    makeCurrent();

    doneCurrent();
}

bool MyGLWidget::event(QEvent *event)
{

	if (event->type() == QEvent::KeyPress)
	{

		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		if (keyEvent->key() == Qt::Key_P)
		{
            std::cout<< "Paused\n";
            //timer.stop();
        }

        if (keyEvent->key() == Qt::Key_S)
		{
            std::cout<<"Started\n";
            //timer.start();
        }

        if(keyEvent->key() == Qt::Key_R){
            std::cout<<"Reseted\n";
        }
    }




	return QOpenGLWidget::event(event);

}