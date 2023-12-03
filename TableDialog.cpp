#include "TableDialog.hpp"

TableDialog::TableDialog(QWidget * parent) : QDialog(parent){
  layout = new QHBoxLayout(this);
  //layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

  wedTable = new WedTable();
  vertexTable = new VertexTable();
  faceTable = new FaceTable();

  // WedTable->horizontalHeader()->setStretchLastSection(true);
  // WedLabels << "edge" << "rn" << "rp" << "ln" << "lp" <<"fr" <<"fl" << "vs" <<"ve";

  // VertexTable->horizontalHeader()->setStretchLastSection(true);
  // VertexLabels << "Vertex";

  // FaceTable->horizontalHeader()->setStretchLastSection(true);
  // FaceLabels << "Faces";

  setFixedSize((NUM_COLS_WED+NUM_COLS_VERT+NUM_COLS_FACE+3)*COLUMN_WIDTH,600);

  //setSizePolicy(((NUM_COLS_WED+1)+NUM_COLS_VERT)*COLUMN_WIDTH , 600);
  //setSizePolicy()

}

TableDialog::~TableDialog(){}

void TableDialog::makeTable(std::vector<Wed*> * weds, std::vector<Face*> * faces, std::vector<Vertex*> * vertexes)
{
  wedTable->makeWedTable(weds);
  vertexTable->makeVertexTable(vertexes);
  faceTable->makeFaceTable(faces);
  layout->addWidget(wedTable->getWedTable());
  layout->addWidget(vertexTable->getVertexTable());
  layout->addWidget(faceTable->getFaceTable());
}

void TableDialog::showTables(){
  setLayout(layout);
  show();
}