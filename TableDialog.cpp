#include "TableDialog.hpp"

TableDialog::TableDialog(QWidget * parent) : QWidget(parent){
  layout = new QHBoxLayout(this);
  //layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

  wedTable = new WedTable(new MenuCreator());
  vertexTable = new VertexTable(new MenuCreator());
  faceTable = new FaceTable(new MenuCreator());
  layout->setContentsMargins(0,0,0,0);
  layout->setSpacing(0);


  connect(wedTable, &WedTable::wedSignal, this, &TableDialog::passingWedSignal);
  connect(vertexTable, &VertexTable::vertexSignal, this, &TableDialog::passingVertexSignal);
  connect(faceTable, &FaceTable::faceSignal, this, &TableDialog::passingFaceSignal);

  // WedTable->horizontalHeader()->setStretchLastSection(true);
  // WedLabels << "edge" << "rn" << "rp" << "ln" << "lp" <<"fr" <<"fl" << "vs" <<"ve";

  // VertexTable->horizontalHeader()->setStretchLastSection(true);
  // VertexLabels << "Vertex";

  // FaceTable->horizontalHeader()->setStretchLastSection(true);
  // FaceLabels << "Faces";

  setFixedSize((NUM_COLS_WED+NUM_COLS_VERT+NUM_COLS_FACE+4)*COLUMN_WIDTH,400);

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