#include "MainWidget.hpp"
#include "Mesh.hpp"


MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    tableDialog = new TableDialog();
    setFixedSize((NUM_COLS_WED+NUM_COLS_VERT+NUM_COLS_FACE+4)*COLUMN_WIDTH,1000);
    setContentsMargins(0, 0, 0, 0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    mygl = new MyGLWidget(this);
    mygl->setFixedSize(width(),height()-tableDialog->height());
    currentMesh = nullptr;


    QDir dir(QDir::currentPath());
    dir.cdUp();
    dir.cd(QString("objects"));
    

    QString path = dir.path();
    QStringList files = dir.entryList(QDir::Files);
    std::cout<<"O PATH ATUAL EH ESSE: " << path.toStdString() <<"\n";

    chooseFile = new QComboBox(this);
    chooseFile->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    chooseFile->setContentsMargins(0, 0, 0, 0);
    chooseFile->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    chooseFile->setMaximumSize(150, 30);
    chooseFile->addItems(files);


    layout->addWidget(mygl);
    layout->addWidget(tableDialog);
    setLayout(layout);
    connect(chooseFile, &QComboBox::activated,this,&MainWidget::fileChosen);
    show();
}


MainWidget::~MainWidget(){
}


void MainWidget::fileChosen(int idx){
    QString fileName = chooseFile->itemText(idx);    
    currentMesh = mygl->createMesh(fileName);

    auto w = currentMesh->getWedVector();
    auto f = currentMesh->getFaceVector();
    auto v = currentMesh->getVertexesVector();
    tableDialog->makeTable(&w, &f, &v);
    tableDialog->showTables();
}

