#include "WedTable.hpp"
#include <QMenu>
#include <QPoint>
#include <QAction>


WedTable::WedTable()
{
  wedTable = new QTableWidget();
  wedTable->setContextMenuPolicy(Qt::CustomContextMenu);
  wedTable->horizontalHeader()->setStretchLastSection(true);
  wedTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  wedLabels << "edge" << "rn" << "rp" << "ln" << "lp" <<"fr" <<"fl" << "vs" <<"ve";

  connect(wedTable, &QTableWidget::customContextMenuRequested, this, &WedTable::popupContextMenuWed);
}

WedTable::~WedTable()
{
}

void WedTable::makeWedTable(std::vector<Wed*> * weds)
{
  wedTable->setColumnCount(NUM_COLS_WED);
  wedTable->setRowCount(weds->size());
  wedTable->setHorizontalHeaderLabels(wedLabels);
  wedTable->setFixedWidth((NUM_COLS_WED+1)*COLUMN_WIDTH);
  for(int k = 0;k<NUM_COLS_WED+1;k++){
    wedTable->setColumnWidth(k, COLUMN_WIDTH);
  } 

  for(int i = 0; i<weds->size();i++){
    if(weds->at(i)==nullptr){
      wedTable->setItem(i, 0, new QTableWidgetItem(QString("null")));
      wedTable->setItem(i, 1, new QTableWidgetItem(QString("null")));
      wedTable->setItem(i, 2, new QTableWidgetItem(QString("null")));
      wedTable->setItem(i, 3, new QTableWidgetItem(QString("null")));
      wedTable->setItem(i, 4, new QTableWidgetItem(QString("null")));
      wedTable->setItem(i, 5, new QTableWidgetItem(QString("null")));
      wedTable->setItem(i, 6, new QTableWidgetItem(QString("null")));
      wedTable->setItem(i, 7, new QTableWidgetItem(QString("null")));
      wedTable->setItem(i, 8, new QTableWidgetItem(QString("null")));
    }
    else {
      wedTable->setItem(i, 0, new QTableWidgetItem(QString(weds->at(i)->debugWed())));

      if(weds->at(i)->right_next != nullptr){
        wedTable->setItem(i, 1, new QTableWidgetItem(QString(weds->at(i)->right_next->debugWed())));
      }
      else{
        wedTable->setItem(i, 1, new QTableWidgetItem(QString("null")));
      }

      if(weds->at(i)->right_prev != nullptr){
        wedTable->setItem(i, 2, new QTableWidgetItem(QString(weds->at(i)->right_prev->debugWed())));
      }
      else{
        wedTable->setItem(i, 2, new QTableWidgetItem(QString("null")));
      }
      
      if(weds->at(i)->left_next != nullptr){
        wedTable->setItem(i, 3, new QTableWidgetItem(QString(weds->at(i)->left_next->debugWed())));
      }
      else{
        wedTable->setItem(i, 3, new QTableWidgetItem(QString("null")));
      }

      if(weds->at(i)->left_prev != nullptr){
        wedTable->setItem(i, 4, new QTableWidgetItem(QString(weds->at(i)->left_prev->debugWed())));
      }
      else{
        wedTable->setItem(i, 4, new QTableWidgetItem(QString("null")));
      }

      if(weds->at(i)->right != nullptr){
        wedTable->setItem(i, 5, new QTableWidgetItem(QString(weds->at(i)->right->debugFace())));
      }
      else{
        wedTable->setItem(i, 5, new QTableWidgetItem(QString("null")));
      }
      
      if(weds->at(i)->left != nullptr){
        wedTable->setItem(i, 6, new QTableWidgetItem(QString(weds->at(i)->left->debugFace())));
      }
      else{
        wedTable->setItem(i, 6, new QTableWidgetItem(QString("null")));
      }
      
      if(weds->at(i)->start != nullptr){
        wedTable->setItem(i, 7, new QTableWidgetItem(QString(weds->at(i)->start->debugVertex())));
      }
      else{
        wedTable->setItem(i, 7, new QTableWidgetItem(QString("null")));
      }
      if(weds->at(i)->end != nullptr){
        wedTable->setItem(i, 8, new QTableWidgetItem(QString(weds->at(i)->end->debugVertex())));
      }
      else{
        wedTable->setItem(i, 8, new QTableWidgetItem(QString("null")));
      }
    }
  }
  QTableWidget::connect(wedTable, &QTableWidget::itemPressed, this, [this](QTableWidgetItem *content) -> void
                        {
                          std::cout << "CONTEUDO: " << content->text().toStdString() << "row: " << content->row() << "column: " << content->column() << "\n";
                          currentVal = content->text().toStdString();
                        });
}

QTableWidget * WedTable::getWedTable(){
  return wedTable;
}


void WedTable::popupContextMenuWed(QPoint pos)
{

  std::cout << "CONTEUDO: " << currentVal << "\n";


  QAction *pAddAction = new QAction("Add",this);
  connect(pAddAction, &QAction::triggered, this, [this]() -> void
                        {
                          std::cout << "Adding something\n";
                        });

  QAction *pRemoveAction = new QAction("Remove", this);
  connect(pRemoveAction, &QAction::triggered, this, [this]() -> void
                        {
                          std::cout << "Removing something\n";
                        });

  QAction *pUpdateAction = new QAction("Update", this);
  connect(pUpdateAction, &QAction::triggered, this, [this]() -> void
                        {
                          std::cout << "Updating something\n";
                        });

  QMenu *menu = new QMenu(this);
  menu->addAction(pAddAction);
  menu->addAction(pRemoveAction);
  menu->addAction(pUpdateAction);
  // menu->popup(wedTable->treeWidget->header()->mapToGlobal(pos));
  menu->popup(wedTable->mapToGlobal(pos));
  return;
}
