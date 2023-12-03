#include "FaceTable.hpp"

FaceTable::FaceTable()
{
  faceTable = new QTableWidget();
  faceTable->horizontalHeader()->setStretchLastSection(true);
  faceLabels << "Faces";
}

FaceTable::~FaceTable()
{
}


void FaceTable::makeFaceTable(std::vector<Face*> * faces) {
  faceTable->setColumnCount(NUM_COLS_FACE);
  faceTable->setRowCount(faces->size());
  faceTable->setHorizontalHeaderLabels(faceLabels);
  for(int k = 0;k<NUM_COLS_FACE;k++){
      faceTable->setColumnWidth(k, COLUMN_WIDTH);
  } 
  //FaceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
  faceTable->setFixedSize((NUM_COLS_FACE+1)*COLUMN_WIDTH,600);
  std::cout<<faces->size()<<std::endl;
  for(int i = 0; i<faces->size();i++) {
    if(faces->at(i)==nullptr){
      faceTable->setItem(i, 0, new QTableWidgetItem(QString("null")));
    }
    else {
      if(faces->at(i)->edge != nullptr){
        faceTable->setItem(i, 0, new QTableWidgetItem(faces->at(i)->edge->debugWed()));
      }
      else {
        faceTable->setItem(i, 0, new QTableWidgetItem(QString("null")));
      }
    }
  }
}

QTableWidget * FaceTable::getFaceTable() {
  return faceTable;
}
