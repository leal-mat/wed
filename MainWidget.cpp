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
    connect(tableDialog, &TableDialog::passingWedSignal, this, &MainWidget::getWedContent);
    connect(tableDialog, &TableDialog::passingVertexSignal, this, &MainWidget::getVertexContent);
    connect(tableDialog, &TableDialog::passingFaceSignal, this, &MainWidget::getFaceContent);
    connect(this, &MainWidget::adjOperatorDone, mygl, &MyGLWidget::updateRender);
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


void getTableValues(std::string tempVal, std::vector<int> *vec)
{

    std::stringstream ss(tempVal);
    std::string result = "";
    int pos = 0;
    while (std::getline(ss, result, ','))
    {
        vec->at(pos) = std::stoi(result, 0);
        pos++;
    }

}

void MainWidget::getWedContent(std::string currentVal, int currentCol, int currentRow, int actionId){
    std::cout << "VALOR ATUAL: "<< currentVal<<"\n";
    std::cout << "COLUNA ATUAL: "<< currentCol<<"\n";
    std::cout << "LINHA ATUAL: "<< currentRow<<"\n";
    currentMesh->clearMarkedEdges();
    currentMesh->updateMesh();
    switch(actionId) {
        case 0:
            std::cout<<"EV\n";
            if (currentCol == 7 || currentCol == 8){
                std::string tempVal = currentVal;
                tempVal.erase(remove(tempVal.begin(), tempVal.end(), '<'), tempVal.end());
                tempVal.erase(remove(tempVal.begin(), tempVal.end(), '>'), tempVal.end());
                tempVal.erase(remove(tempVal.begin(), tempVal.end(), ' '), tempVal.end());
                std::cout <<"Valor: " << tempVal << "\n";
                std::vector<int> vec;
                vec.reserve(3);
                vec.resize(3);
                getTableValues(tempVal, &vec);
                std::cout <<"Primeiro valor: " << vec.at(0) << "\n";
                std::cout <<"Segundo valor: " << vec.at(1) << "\n";
                std::cout <<"Terceiro valor: " << vec.at(2) << "\n";
                auto vertexVal = currentMesh->consultVertexesVector(vec.at(2));
                if(vertexVal != nullptr){
                    //currentMesh->clearMarkedEdges();
                    currentMesh->EV(vertexVal);
                }
            }
            break;
        case 1:
            std::cout<<"EE\n";
            if (currentCol>=0 && currentCol<=4)
            {
                std::cout << "VAMOS OPERAR NO SEGUINTE VALOR: " << currentVal << "\n";
                std::string tempVal = currentVal;
                tempVal.erase(remove(tempVal.begin(), tempVal.end(), '<'), tempVal.end());
                tempVal.erase(remove(tempVal.begin(), tempVal.end(), '>'), tempVal.end());
                std::cout <<"Valor: " << tempVal << "\n";
                std::vector<int> vec;
                vec.reserve(2);
                vec.resize(2);
                getTableValues(tempVal, &vec);
                std::cout <<"Primeiro valor: " << vec.at(0) << "\n";
                std::cout <<"Segundo valor: " << vec.at(1) << "\n";

                pair<int, int> pairToSearch = pair(vec.at(0), vec.at(1));
                //currentMesh->clearMarkedEdges();
                currentMesh->EE(currentMesh->consultEdgeCreationMap(pairToSearch));
                emit adjOperatorDone();
            }
            
            break;
        case 2:
            std::cout<<"FE\n";
            if (currentCol>=0 && currentCol<=4)
            {
                std::cout << "VAMOS OPERAR NO SEGUINTE VALOR: " << currentVal << "\n";
                std::string tempVal = currentVal;
                tempVal.erase(remove(tempVal.begin(), tempVal.end(), '<'), tempVal.end());
                tempVal.erase(remove(tempVal.begin(), tempVal.end(), '>'), tempVal.end());
                std::cout <<"Valor: " << tempVal << "\n";
                std::vector<int> vec;
                vec.reserve(2);
                vec.resize(2);
                getTableValues(tempVal, &vec);
                std::cout <<"Primeiro valor: " << vec.at(0) << "\n";
                std::cout <<"Segundo valor: " << vec.at(1) << "\n";

                pair<int, int> pairToSearch = pair(vec.at(0), vec.at(1));
                //currentMesh->clearMarkedEdges();
                currentMesh->FE(currentMesh->consultEdgeCreationMap(pairToSearch));
                emit adjOperatorDone();
            }
            break;
        case 3:
            std::cout<<"VE\n";
            if (currentCol>=0 && currentCol<=4)
            {
                std::cout << "VAMOS OPERAR NO SEGUINTE VALOR: " << currentVal << "\n";
                std::string tempVal = currentVal;
                tempVal.erase(remove(tempVal.begin(), tempVal.end(), '<'), tempVal.end());
                tempVal.erase(remove(tempVal.begin(), tempVal.end(), '>'), tempVal.end());
                std::cout <<"Valor: " << tempVal << "\n";
                std::vector<int> vec;
                vec.reserve(2);
                vec.resize(2);
                getTableValues(tempVal, &vec);
                std::cout <<"Primeiro valor: " << vec.at(0) << "\n";
                std::cout <<"Segundo valor: " << vec.at(1) << "\n";

                pair<int, int> pairToSearch = pair(vec.at(0), vec.at(1));
                //currentMesh->clearMarkedEdges();
                currentMesh->VE(currentMesh->consultEdgeCreationMap(pairToSearch));
                emit adjOperatorDone();
            }
            break;
        case 4:
            std::cout<<"EF\n";
            if (currentCol==5 && currentCol==6)
            {
                std::cout << "VAMOS OPERAR NO SEGUINTE VALOR: " << currentVal << "\n";
                std::string tempVal = currentVal;
                tempVal.erase(remove(tempVal.begin(), tempVal.end(), '<'), tempVal.end());
                tempVal.erase(remove(tempVal.begin(), tempVal.end(), '>'), tempVal.end());
                std::cout <<"Valor: " << tempVal << "\n";
                std::vector<int> vec;
                vec.reserve(2);
                vec.resize(2);
                getTableValues(tempVal, &vec);
                std::cout <<"Primeiro valor: " << vec.at(0) << "\n";
                std::cout <<"Segundo valor: " << vec.at(1) << "\n";

                pair<int, int> pairToSearch = pair(vec.at(0), vec.at(1));
                auto faceVal = currentMesh->consultFaceVector(pairToSearch);
                if(faceVal != nullptr){
                    //currentMesh->clearMarkedEdges();
                    currentMesh->EF(faceVal);
                    emit adjOperatorDone();
                }
            }
            break;
    }

    return;
}



void MainWidget::getVertexContent(std::string currentVal)
{
    currentMesh->clearMarkedEdges();
    currentMesh->updateMesh();
    std::string tempVal = currentVal;
    tempVal.erase(remove(tempVal.begin(), tempVal.end(), '<'), tempVal.end());
    tempVal.erase(remove(tempVal.begin(), tempVal.end(), '>'), tempVal.end());
    std::cout <<"Valor: " << tempVal << "\n";
    std::vector<int> vec;
    vec.reserve(2);
    vec.resize(2);
    getTableValues(tempVal, &vec);
    std::cout <<"Primeiro valor: " << vec.at(0) << "\n";
    std::cout <<"Segundo valor: " << vec.at(1) << "\n";
    pair<int, int> pairToSearch = pair(vec.at(0), vec.at(1));
    auto vertexVal = currentMesh->consultVertexesVector(pairToSearch);
    if(vertexVal != nullptr){
        currentMesh->EV(vertexVal);
        emit adjOperatorDone();
    }
    return;
}


void MainWidget::getFaceContent(std::string currentVal)
{
    currentMesh->clearMarkedEdges();
    currentMesh->updateMesh();
    std::cout << "VAMOS OPERAR NO SEGUINTE VALOR: " << currentVal << "\n";
    std::string tempVal = currentVal;
    tempVal.erase(remove(tempVal.begin(), tempVal.end(), '<'), tempVal.end());
    tempVal.erase(remove(tempVal.begin(), tempVal.end(), '>'), tempVal.end());
    std::cout <<"Valor: " << tempVal << "\n";
    std::vector<int> vec;
    vec.reserve(2);
    vec.resize(2);
    getTableValues(tempVal, &vec);
    std::cout <<"Primeiro valor: " << vec.at(0) << "\n";
    std::cout <<"Segundo valor: " << vec.at(1) << "\n";

    pair<int, int> pairToSearch = pair(vec.at(0), vec.at(1));
    auto faceVal = currentMesh->consultFaceVector(pairToSearch);
    if(faceVal != nullptr){
        currentMesh->EF(faceVal);
        emit adjOperatorDone();
    }
    return;
}


