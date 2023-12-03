#include "VertexTable.hpp"

VertexTable::VertexTable()
{
  vertexTable = new QTableWidget();
  vertexTable->horizontalHeader()->setStretchLastSection(true);
  vertexLabels << "Vertex";
}

VertexTable::~VertexTable(){}

void VertexTable::makeVertexTable(std::vector<std::pair<glm::vec3,Vertex*>> * vertexes) {
  vertexTable->setColumnCount(NUM_COLS_VERT);
  vertexTable->setRowCount(vertexes->size());
  vertexTable->setHorizontalHeaderLabels(vertexLabels);
  for(int k = 0;k<NUM_COLS_VERT;k++){
    vertexTable->setColumnWidth(k, 160);
  } 
  vertexTable->setFixedSize((NUM_COLS_VERT+1)*COLUMN_WIDTH,600);


  for(int i = 0; i<vertexes->size();i++){
    if(vertexes->at(i).second==nullptr){
      vertexTable->setItem(i, 0, new QTableWidgetItem(QString("null")));
    }
    else{
      if(vertexes->at(i).second->edge != nullptr){
        vertexTable->setItem(i, 0, new QTableWidgetItem(vertexes->at(i).second->edge->debugWed()));
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

