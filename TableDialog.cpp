#include "TableDialog.hpp"

TableDialog::TableDialog(QWidget * parent) : QDialog(parent){
  layout = new QHBoxLayout(this);
  table = new QTableWidget(this);
  setFixedSize(1280,960);
  labels << "edge" << "rn" << "rp" << "ln" << "lp" <<"fr" <<"fl" << "vs" <<"ve";

}

TableDialog::~TableDialog(){}

void TableDialog::makeTable(std::vector<Wed*> * weds){
  table->setColumnCount(weds->size());
  std::cout<< "Size weds: "<< weds->size() <<"\n";
  table->setRowCount(9);
  table->setVerticalHeaderLabels(labels);

  for(int i = 0; i<weds->size();i++){
    if(weds->at(i)==nullptr){
      table->setItem(0, i, new QTableWidgetItem(QString("null")));
      table->setItem(1, i, new QTableWidgetItem(QString("null")));
      table->setItem(2, i, new QTableWidgetItem(QString("null")));
      table->setItem(3, i, new QTableWidgetItem(QString("null")));
      table->setItem(4, i, new QTableWidgetItem(QString("null")));
      table->setItem(5, i, new QTableWidgetItem(QString("null")));
      table->setItem(6, i, new QTableWidgetItem(QString("null")));
      table->setItem(7, i, new QTableWidgetItem(QString("null")));
      table->setItem(8, i, new QTableWidgetItem(QString("null")));
    }
    else{
      table->setItem(0,i, new QTableWidgetItem(QString(weds->at(i)->debugWed())));

      if(weds->at(i)->right_next != nullptr){
        table->setItem(1,i, new QTableWidgetItem(QString(weds->at(i)->right_next->debugWed())));
      }
      else{
        table->setItem(1,i, new QTableWidgetItem(QString("null")));
      }

      if(weds->at(i)->right_prev != nullptr){
        table->setItem(2,i, new QTableWidgetItem(QString(weds->at(i)->right_prev->debugWed())));
      }
      else{
        table->setItem(2,i, new QTableWidgetItem(QString("null")));
      }
      
      if(weds->at(i)->left_next != nullptr){
        table->setItem(3,i, new QTableWidgetItem(QString(weds->at(i)->left_next->debugWed())));
      }
      else{
        table->setItem(3,i, new QTableWidgetItem(QString("null")));
      }

      if(weds->at(i)->left_prev != nullptr){
        table->setItem(4,i, new QTableWidgetItem(QString(weds->at(i)->left_prev->debugWed())));
      }
      else{
        table->setItem(4,i, new QTableWidgetItem(QString("null")));
      }

      if(weds->at(i)->right != nullptr){
        table->setItem(5,i, new QTableWidgetItem(QString(weds->at(i)->right->debugFace())));
      }
      else{
        table->setItem(5,i, new QTableWidgetItem(QString("null")));
      }
      
      if(weds->at(i)->left != nullptr){
        table->setItem(6,i, new QTableWidgetItem(QString(weds->at(i)->left->debugFace())));
      }
      else{
        table->setItem(6,i, new QTableWidgetItem(QString("null")));
      }
      
      if(weds->at(i)->start != nullptr){
        table->setItem(7,i, new QTableWidgetItem(QString(weds->at(i)->start->debugVertex())));
      }
      else{
        table->setItem(7,i, new QTableWidgetItem(QString("null")));
      }
      if(weds->at(i)->end != nullptr){
        table->setItem(8,i, new QTableWidgetItem(QString(weds->at(i)->end->debugVertex())));
      }
      else{
        table->setItem(8,i, new QTableWidgetItem(QString("null")));
      }
      
    }
  }
  layout->addWidget(table);
  setLayout(layout);
  show();
}