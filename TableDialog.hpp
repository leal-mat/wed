#ifndef TABLE_DIALOG_H
#define TABLE_DIALOG_H

#include <QDialog>
#include <QHBoxLayout>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QStringList>
#include <iostream>
#include <vector>
#include "Wed.hpp"


class TableDialog : public QDialog{
  public:
  TableDialog(QWidget * parent = nullptr);
  ~TableDialog();
  void makeTable(std::vector<Wed*> * weds);

  public:
  QHBoxLayout * layout;
  QTableWidget * table;
  QStringList labels;


};

#endif //TABLE_DIALOG