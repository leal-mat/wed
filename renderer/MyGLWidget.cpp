#include "MyGLWidget.hpp"
#include <iostream>

using qtime = QDateTime;


MyGLWidget::MyGLWidget(QWidget * parent) : QOpenGLWidget(parent){
    setFocusPolicy(Qt::ClickFocus);
    mesh = nullptr;
    //setFixedSize(600,400);
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
    //f->glDisable(GL_CULL_FACE);
    f->glPointSize(3);
    f->glLineWidth(2);


    camera = new Camera(glm::vec3(0,0.,4.),glm::vec3(0.,0.,-1.));
    camera->setFov(45);
    camera->setViewPlanes(0.01,100.);
    camera->setCanvasDimensions(this->width(),this->height());

    f->glClearColor(45.0/255., 63/255., 133/255.,1.0f);

}

void MyGLWidget::paintGL(){
    if(mesh != nullptr){
        mesh->updateMesh();
        std::cout<<"Painting\n";
        mesh->draw();
    }
}


void MyGLWidget::resizeGL(int w, int h){


}

Camera * MyGLWidget::getCamera(){
    return camera;
}


void MyGLWidget::setMesh(Mesh * _mesh){
    makeCurrent();    
    mesh = _mesh;

    update();
    doneCurrent();
    
    
}


void MyGLWidget::keyPressEvent(QKeyEvent * keyEvent){
    makeCurrent();

	if (keyEvent->key() == Qt::Key_W){
        camera->walkFront();
    }

    else if (keyEvent->key() == Qt::Key_S){
       camera->walkBack(); 
    }

    else if (keyEvent->key() == Qt::Key_D){
       camera->walkRight(); 
    }

    else if (keyEvent->key() == Qt::Key_A){
       camera->walkLeft(); 
    }
    update();
    doneCurrent();
}

void MyGLWidget::mousePressEvent(QMouseEvent* evt)
{
    virtualPos = evt->pos();
    setCursor(Qt::BlankCursor);
    QCursor::setPos(mapToGlobal(rect().center()));
    update();
    // sceneManager->callMousePressEventHandler(virtual_pos);
    QWidget::mousePressEvent(evt);
    
    std::cout<<"CLICADO\n";
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent* evt){
    std::cout<<"SOLTADO\n";
    QCursor::setPos(mapToGlobal(virtualPos));
    setCursor(Qt::ArrowCursor);
    // sceneManager->callMouseReleaseEventHandler(virtual_pos);
    QWidget::mouseReleaseEvent(evt);
}

void MyGLWidget::mouseMoveEvent(QMouseEvent* evt){
if (evt->buttons() & Qt::LeftButton && evt->pos() != rect().center())
    {
        virtualPos += (evt->pos() - rect().center());

        //uncomment if you want wrap behavior
        //virtual_pos.setX((virtual_pos.x() + width()) % width());
        //virtual_pos.setY((virtual_pos.y() + height()) % height());

        virtualPos.setX(qBound(0, virtualPos.x(), width()));
        virtualPos.setY(qBound(0, virtualPos.y(), height()));
        QCursor::setPos(mapToGlobal(rect().center()));
        update();
        // sceneManager->callMouseMoveEventHandler(virtual_pos);
    }
    QWidget::mouseMoveEvent(evt);
}


Mesh * MyGLWidget::createMesh(QString fileName)
{
    makeCurrent();
    mesh = new Mesh(context());
    mesh->setGLWidget(this);
    mesh->getMeshProperties(fileName.toStdString());
    mesh->init();

    
    GLProgram p0 = mesh->getProgram(0);
    uint p0ID = p0.getProgramId();
    f->glUseProgram(p0ID);
    GLuint vmatrix = f->glGetUniformLocation(p0ID, "m_view");
    GLuint pmatrix = f->glGetUniformLocation(p0ID, "m_proj");
    f->glUniformMatrix4fv(vmatrix, 1, GL_FALSE, glm::value_ptr(camera->getViewMatrix()));
    f->glUniformMatrix4fv(pmatrix, 1, GL_FALSE, glm::value_ptr(camera->getProjMatrix()));
    
    
    mesh->buildMesh();
    mesh->createWedVector();
    mesh->createVertexesVector();
    mesh->createFaceVector();



    update();
    doneCurrent();
    return mesh;
}

