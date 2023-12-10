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
#include "MenuCreator.hpp"


#define COLUMN_WIDTH 100
#define NUM_COLS_WED 9
#define NUM_COLS_VERT 1
#define NUM_COLS_FACE 1


class WedTable : public QWidget
{
  Q_OBJECT
public:
  WedTable(MenuCreator *);
  ~WedTable();
  void makeWedTable(std::vector<Wed*> * weds);
  QTableWidget * getWedTable();
  
private:
  QTableWidget * wedTable;
  QStringList wedLabels;
  std::string currentVal;
  int currentCol;
  int currentRow;
  MenuCreator *menuCreator;

public slots:
  void popupContextMenuWed(QPoint pos);

signals:
  void wedSignal(std::string currentVal, int currentCol, int currentRow, int actionId);
  
};




#endif // WED_TABLE_HPP