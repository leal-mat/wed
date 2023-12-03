#ifndef TABLE_DIALOG_H
#define TABLE_DIALOG_H

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
#include "WedTable.hpp"
#include "VertexTable.hpp"
#include "FaceTable.hpp"

#define COLUMN_WIDTH 100
#define NUM_COLS_WED 9
#define NUM_COLS_VERT 1
#define NUM_COLS_FACE 1


class TableDialog : public QDialog{
  Q_OBJECT
  public:
  TableDialog(QWidget * parent = nullptr);
  ~TableDialog();
  void makeTable(std::vector<Wed*> * weds, std::vector<Face*> * faces, std::vector<Vertex*> * vertexes);
  // void makeTable();
  // void makeTable();
  // void setTables(QTableWidget * wedTable, QTableWidget * FaceTable, QTableWidget * VertexTable);
  void showTables();

  public:
  QHBoxLayout * layout;
  WedTable * wedTable;
  VertexTable * vertexTable;
  FaceTable * faceTable;
};

#endif //TABLE_DIALOG