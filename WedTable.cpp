#include "WedTable.hpp"
#include <QMenu>
#include <QPoint>
#include <QAction>


WedTable::WedTable(MenuCreator * menuc = nullptr)
{
  wedTable = new QTableWidget();
  wedTable->setContextMenuPolicy(Qt::CustomContextMenu);
  wedTable->horizontalHeader()->setStretchLastSection(true);
  wedTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  wedLabels << "edge" << "rn" << "rp" << "ln" << "lp" <<"fr" <<"fl" << "vs" <<"ve";
  menuCreator = menuc;

  connect(wedTable, &QTableWidget::customContextMenuRequested, this, &WedTable::popupContextMenuWed);

  QAction *EEAction = menuCreator->getEEAction();
  connect(EEAction, &QAction::triggered, this, [this]() -> void
              {
                  std::cout << "Calling EE\n";
                  emit wedSignal(currentVal, currentCol, currentRow, 1);
              });

  QAction *FEAction = menuCreator->getFEAction();
  connect(FEAction, &QAction::triggered, this, [this]() -> void
                {
                        std::cout << "Calling FE\n";
                        emit wedSignal(currentVal, currentCol, currentRow, 2);
              });

  QAction *VEAction = menuCreator->getVEAction();
  connect(VEAction, &QAction::triggered, this, [this]() -> void
                {
                    std::cout << "Calling VE\n";
                    emit wedSignal(currentVal, currentCol, currentRow, 3);
                });
  QAction *EFAction = menuCreator->getEFAction();
  connect(EFAction, &QAction::triggered, this, [this]() -> void
                {
                    std::cout << "Calling EF\n";
                    emit wedSignal(currentVal, currentCol, currentRow, 4);
                });
                
  QAction *EVAction = menuCreator->getEVAction();
  connect(EVAction, &QAction::triggered, this, [this]() -> void
                {
                  std::cout << "Calling EV\n";
                  emit wedSignal(currentVal, currentCol, currentRow, 0);
                });
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
      auto item0 = new QTableWidgetItem(QString(weds->at(i)->debugWed()));
      wedTable->setItem(i, 0, item0);
      auto edgeMenu = menuCreator->getEdgeMenu();
      auto eeAction = menuCreator->getEEAction();
      auto feAction = menuCreator->getFEAction();
      auto veAction = menuCreator->getVEAction();

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
                          currentVal = content->text().toStdString();
                          currentCol = content->column();
                          currentRow = content->row();
                        });
}

QTableWidget * WedTable::getWedTable(){
  return wedTable;
}


void WedTable::popupContextMenuWed(QPoint pos)
{ 
  QMenu *menu = nullptr;

  if (currentCol<=4 && currentCol>=0)
  {
    menu = menuCreator->getEdgeMenu();
  }
  

  else if(currentCol==5 || currentCol==6){
    menu = menuCreator->getFaceMenu();
  }


  else if(currentCol==7 || currentCol==8){
    menu = menuCreator->getVertexMenu();
  }

  menu->popup(wedTable->mapToGlobal(pos));
  return;
}
