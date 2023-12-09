#include "VertexTable.hpp"
#include <QMenu>
#include <QAction>
#include <QPoint>


VertexTable::VertexTable()
{
  vertexTable = new QTableWidget();
  vertexTable->horizontalHeader()->setStretchLastSection(true);
  vertexTable->setContextMenuPolicy(Qt::CustomContextMenu);
  vertexTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  vertexLabels << "Vertex";

  connect(vertexTable, &QTableWidget::customContextMenuRequested, this, &VertexTable::popupContextMenuVertex);
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


  QTableWidget::connect(vertexTable, &QAbstractItemView::clicked, this, [this](const QModelIndex& idx) -> void
                        {
                          std::cout << "Clicked: " << idx.row()<<", "<<idx.column()<<"\n";
                          currentIndex = idx.row();
                        });

  QTableWidget::connect(vertexTable, &QTableWidget::itemPressed, this, [this](QTableWidgetItem *content) -> void
                        {
                          std::cout << "CONTEUDO: " << content->text().toStdString() << "row: " << content->row() << "column: " << content->column() << "\n";
                          currentVal = content->text().toStdString();
                        });

}

QTableWidget * VertexTable::getVertexTable(){
  return vertexTable;
}


void VertexTable::popupContextMenuVertex(QPoint pos)
{

  std::cout << "CONTEUDO: " << currentVal << "\n";


  QAction *pAddAction = new QAction("Add",this);
  connect(pAddAction, &QAction::triggered, this, [this]() -> void
                        {
                          std::cout << "Adding something at vertexTable\n";
                        });

  QAction *pRemoveAction = new QAction("Remove", this);
  connect(pRemoveAction, &QAction::triggered, this, [this]() -> void
                        {
                          std::cout << "Removing something at vertexTable\n";
                        });

  QAction *pUpdateAction = new QAction("Update", this);
  connect(pUpdateAction, &QAction::triggered, this, [this]() -> void
                        {
                          std::cout << "Updating something at vertexTable\n";
                        });

  QMenu *menu = new QMenu(this);
  menu->addAction(pAddAction);
  menu->addAction(pRemoveAction);
  menu->addAction(pUpdateAction);
  // menu->popup(wedTable->treeWidget->header()->mapToGlobal(pos));
  menu->popup(vertexTable->mapToGlobal(pos));
  return;
}
