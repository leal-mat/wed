#include "FaceTable.hpp"
#include <QMenu>
#include <QAction>
#include <QPoint>

FaceTable::FaceTable(MenuCreator * menuc = nullptr)
{
  faceTable = new QTableWidget();
  faceTable->setContextMenuPolicy(Qt::CustomContextMenu);
  faceTable->horizontalHeader()->setStretchLastSection(true);
  faceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  faceLabels << "Faces";
  menuCreator = menuc;



  QAction *EFAction = menuCreator->getEFAction();
  connect(EFAction, &QAction::triggered, this, [this]() -> void
                {
                    std::cout << "Calling EF\n";
                    emit faceSignal(currentVal);
                });


  connect(faceTable, &QTableWidget::customContextMenuRequested, this, &FaceTable::popupContextMenuFace);
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
  //faceTable->setFixedSize((NUM_COLS_FACE+1)*COLUMN_WIDTH,600);
  faceTable->setFixedWidth((NUM_COLS_FACE+1)*COLUMN_WIDTH);
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


  QTableWidget::connect(faceTable, &QAbstractItemView::clicked, this, [this](const QModelIndex& idx) -> void
                        {
                          std::cout << "Clicked: " << idx.row()<<", "<<idx.column()<<"\n";
                          currentIndex = idx.row();
                        });

  QTableWidget::connect(faceTable, &QTableWidget::itemPressed, this, [this](QTableWidgetItem *content) -> void
                        {
                          std::cout << "CONTEUDO: " << content->text().toStdString() << "row: " << content->row() << "column: " << content->column() << "\n";
                          currentVal = content->text().toStdString();
                        });

}

QTableWidget * FaceTable::getFaceTable() {
  return faceTable;
}


void FaceTable::popupContextMenuFace(QPoint pos)
{

  std::cout << "CONTEUDO Face Menu: " << currentVal << "\n";
  QMenu *menu = menuCreator->getFaceMenu();
  menu->popup(faceTable->mapToGlobal(pos));
  return;
}