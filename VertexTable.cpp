#include "VertexTable.hpp"

VertexTable::VertexTable()
{
  vertexTable = new QTableWidget();
  vertexTable->horizontalHeader()->setStretchLastSection(true);
  vertexLabels << "Vertex";
}

VertexTable::~VertexTable(){}

void VertexTable::makeVertexTable(std::vector<Vertex*> * vertexes) {
  vertexTable->setColumnCount(NUM_COLS_VERT);
  vertexTable->setRowCount(vertexes->size());
  vertexTable->setHorizontalHeaderLabels(vertexLabels);
  for(int k = 0;k<NUM_COLS_VERT;k++){
    vertexTable->setColumnWidth(k, 160);
  } 
  vertexTable->setFixedWidth((NUM_COLS_VERT+1)*COLUMN_WIDTH);


  for(int i = 0; i<vertexes->size();i++){
    if(vertexes->at(i)==nullptr){
      vertexTable->setItem(i, 0, new QTableWidgetItem(QString("null")));
    }
    else{
      if(vertexes->at(i)->edge != nullptr){
        vertexTable->setItem(i, 0, new QTableWidgetItem(vertexes->at(i)->edge->debugWed()));
      }
      else{
        vertexTable->setItem(i, 0, new QTableWidgetItem(QString("null")));
      }
    }
  }
}

QTableWidget * VertexTable::getVertexTable(){
  return vertexTable;
}

