#ifndef WED_TABLE_HPP
#define WED_TABLE_HPP

#include <QDialog>
#include <QHBoxLayout>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QStringList>
#include <iostream>
#include <vector>
#include "Wed.hpp"


#define COLUMN_WIDTH 100
#define NUM_COLS_WED 9
#define NUM_COLS_VERT 1
#define NUM_COLS_FACE 1


class WedTable : public QWidget
{
  Q_OBJECT
public:
  WedTable();
  ~WedTable();
  void makeWedTable(std::vector<Wed*> * weds);
  QTableWidget * getWedTable();
  
private:
  QTableWidget * wedTable;
  QStringList wedLabels;
};




#endif // WED_TABLE_HPP