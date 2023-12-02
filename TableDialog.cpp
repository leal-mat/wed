#include "TableDialog.hpp"

TableDialog::TableDialog(QWidget * parent) : QDialog(parent){
  layout = new QHBoxLayout(this);
  //layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
  WedTable = new QTableWidget();
  VertexTable = new QTableWidget();
  FaceTable = new QTableWidget();

  WedTable->horizontalHeader()->setStretchLastSection(true);
  WedLabels << "edge" << "rn" << "rp" << "ln" << "lp" <<"fr" <<"fl" << "vs" <<"ve";

  VertexTable->horizontalHeader()->setStretchLastSection(true);
  VertexLabels << "Vertex";

  FaceTable->horizontalHeader()->setStretchLastSection(true);
  FaceLabels << "Faces";

  setFixedSize((NUM_COLS_WED+NUM_COLS_VERT+NUM_COLS_FACE+3)*COLUMN_WIDTH,600);

  //setSizePolicy(((NUM_COLS_WED+1)+NUM_COLS_VERT)*COLUMN_WIDTH , 600);
  //setSizePolicy()

}

TableDialog::~TableDialog(){}

void TableDialog::makeTable(std::vector<Wed*> * weds){
  WedTable->setColumnCount(NUM_COLS_WED);
  std::cout<< "Size weds: "<< weds->size() <<"\n";
  WedTable->setRowCount(weds->size());
  WedTable->setHorizontalHeaderLabels(WedLabels);
  //WedTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  WedTable->setFixedSize((NUM_COLS_WED+1)*COLUMN_WIDTH,600);
  for(int k = 0;k<NUM_COLS_WED+1;k++){
      WedTable->setColumnWidth(k, COLUMN_WIDTH);
  } 

  for(int i = 0; i<weds->size();i++){
    if(weds->at(i)==nullptr){
      WedTable->setItem(i, 0, new QTableWidgetItem(QString("null")));
      WedTable->setItem(i, 1, new QTableWidgetItem(QString("null")));
      WedTable->setItem(i, 2, new QTableWidgetItem(QString("null")));
      WedTable->setItem(i, 3, new QTableWidgetItem(QString("null")));
      WedTable->setItem(i, 4, new QTableWidgetItem(QString("null")));
      WedTable->setItem(i, 5, new QTableWidgetItem(QString("null")));
      WedTable->setItem(i, 6, new QTableWidgetItem(QString("null")));
      WedTable->setItem(i, 7, new QTableWidgetItem(QString("null")));
      WedTable->setItem(i, 8, new QTableWidgetItem(QString("null")));
    }
    else{
      WedTable->setItem(i, 0, new QTableWidgetItem(QString(weds->at(i)->debugWed())));

      if(weds->at(i)->right_next != nullptr){
        WedTable->setItem(i, 1, new QTableWidgetItem(QString(weds->at(i)->right_next->debugWed())));
      }
      else{
        WedTable->setItem(i, 1, new QTableWidgetItem(QString("null")));
      }

      if(weds->at(i)->right_prev != nullptr){
        WedTable->setItem(i, 2, new QTableWidgetItem(QString(weds->at(i)->right_prev->debugWed())));
      }
      else{
        WedTable->setItem(i, 2, new QTableWidgetItem(QString("null")));
      }
      
      if(weds->at(i)->left_next != nullptr){
        WedTable->setItem(i, 3, new QTableWidgetItem(QString(weds->at(i)->left_next->debugWed())));
      }
      else{
        WedTable->setItem(i, 3, new QTableWidgetItem(QString("null")));
      }

      if(weds->at(i)->left_prev != nullptr){
        WedTable->setItem(i, 4, new QTableWidgetItem(QString(weds->at(i)->left_prev->debugWed())));
      }
      else{
        WedTable->setItem(i, 4, new QTableWidgetItem(QString("null")));
      }

      if(weds->at(i)->right != nullptr){
        WedTable->setItem(i, 5, new QTableWidgetItem(QString(weds->at(i)->right->debugFace())));
      }
      else{
        WedTable->setItem(i, 5, new QTableWidgetItem(QString("null")));
      }
      
      if(weds->at(i)->left != nullptr){
        WedTable->setItem(i, 6, new QTableWidgetItem(QString(weds->at(i)->left->debugFace())));
      }
      else{
        WedTable->setItem(i, 6, new QTableWidgetItem(QString("null")));
      }
      
      if(weds->at(i)->start != nullptr){
        WedTable->setItem(i, 7, new QTableWidgetItem(QString(weds->at(i)->start->debugVertex())));
      }
      else{
        WedTable->setItem(i, 7, new QTableWidgetItem(QString("null")));
      }
      if(weds->at(i)->end != nullptr){
        WedTable->setItem(i, 8, new QTableWidgetItem(QString(weds->at(i)->end->debugVertex())));
      }
      else{
        WedTable->setItem(i, 8, new QTableWidgetItem(QString("null")));
      }
    }
  }
  layout->addWidget(WedTable);
}

void TableDialog::makeTable(std::vector<std::pair<glm::vec3,Vertex*>> * vertexes){
  VertexTable->setColumnCount(NUM_COLS_VERT);
  VertexTable->setRowCount(vertexes->size());
  VertexTable->setHorizontalHeaderLabels(VertexLabels);
  for(int k = 0;k<NUM_COLS_VERT;k++){
      VertexTable->setColumnWidth(k, 160);
  } 
  VertexTable->setFixedSize((NUM_COLS_VERT+1)*COLUMN_WIDTH,600);


  for(int i = 0; i<vertexes->size();i++){
    if(vertexes->at(i).second==nullptr){
      VertexTable->setItem(i, 0, new QTableWidgetItem(QString("null")));
    }
    else{
      if(vertexes->at(i).second->edge != nullptr){
        VertexTable->setItem(i, 0, new QTableWidgetItem(vertexes->at(i).second->edge->debugWed()));
      }
      else{
        VertexTable->setItem(i, 0, new QTableWidgetItem(QString("null")));
      }
    }
  }
  layout->addWidget(VertexTable);
}

void TableDialog::makeTable(std::vector<Face*> * faces){
  FaceTable->setColumnCount(NUM_COLS_FACE);
  FaceTable->setRowCount(faces->size());
  FaceTable->setHorizontalHeaderLabels(FaceLabels);
  for(int k = 0;k<NUM_COLS_FACE;k++){
      FaceTable->setColumnWidth(k, COLUMN_WIDTH);
  } 
  //FaceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  FaceTable->setFixedSize((NUM_COLS_FACE+1)*COLUMN_WIDTH,600);
  std::cout<<faces->size()<<std::endl;
  for(int i = 0; i<faces->size();i++){
    if(faces->at(i)==nullptr){
      FaceTable->setItem(i, 0, new QTableWidgetItem(QString("null")));
    }
    else{
      if(faces->at(i)->edge != nullptr){
        FaceTable->setItem(i, 0, new QTableWidgetItem(faces->at(i)->edge->debugWed()));
      }
      else{
        FaceTable->setItem(i, 0, new QTableWidgetItem(QString("null")));
      }
    }
  }
  layout->addWidget(FaceTable);
}

void TableDialog::showTables(){
  setLayout(layout);
  show();
}