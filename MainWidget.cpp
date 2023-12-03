#include <QComboBox>
#include <QDir>
#include <QStringList>

#include "MainWidget.hpp"
#include "Mesh.hpp"


MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    tableDialog = new TableDialog(this);
    setFixedSize((NUM_COLS_WED+NUM_COLS_VERT+NUM_COLS_FACE+3)*COLUMN_WIDTH,1200);
    setContentsMargins(0, 0, 0, 0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    mygl = new MyGLWidget(this);



    // QDir path("objects");
    // std::cout<<"Testando o path: " <<  path <<"\n";
    // QStringList files = path.entryList(QDir::Files);

    QDir dir(QDir::currentPath());
    dir.cdUp();
    dir.cd(QString("objects"));
    

    QString path = dir.path();
    QStringList files = dir.entryList(QDir::Files);
    std::cout<<"O PATH ATUAL EH ESSE: " << path.toStdString() <<"\n";

    QComboBox *chooseFile = new QComboBox(this);
    chooseFile->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    chooseFile->setContentsMargins(0, 0, 0, 0);
    chooseFile->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    chooseFile->setMaximumSize(150, 30);
    chooseFile->addItems(files);
    // chooseFile->addItem(QString("ON"));

    layout->addWidget(mygl);
    layout->addWidget(tableDialog);
    setLayout(layout);
    // connect(inputWidget, &InputWidget::callSolidRequest, this, &MainWidget::solidRequest);
    // connect(inputWidget, &InputWidget::callOperationRequest, this, &MainWidget::operationRequest);
    // connect(inputWidget, &InputWidget::callTransformationRequest, this, &MainWidget::transformationRequest);
    // connect(inputWidget, &InputWidget::callCanvasParameters, glview, &GLView::setCanvasParameters);


    Mesh m = Mesh();
    m.getMeshProperties("cubo.obj");
    m.buildMesh();
    m.createWedVector();
    m.createVertexesVector();
    m.createFaceVector();
    auto w = m.getWedVector();
    auto f = m.getFaceVector();
    auto v = m.getVertexesVector();
    tableDialog->makeTable(&w, &f, &v);
    tableDialog->showTables();

    show();
}


MainWidget::~MainWidget(){
}


void MainWidget::someSlot(){
    std::cout<<"This will do something\n";
}

