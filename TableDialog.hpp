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

#define COLUMN_WIDTH 100
#define NUM_COLS_WED 9
#define NUM_COLS_VERT 1
#define NUM_COLS_FACE 1


class TableDialog : public QDialog{
  public:
  TableDialog(QWidget * parent = nullptr);
  ~TableDialog();
  void makeTable(std::vector<Wed*> * weds);
  void makeTable(std::vector<Face*> * faces);
  void makeTable(std::vector<std::pair<glm::vec3,Vertex*>> * vertexes);
  void showTables();

  public:
  QHBoxLayout * layout;
  QTableWidget * WedTable;
  QTableWidget * FaceTable;
  QTableWidget * VertexTable;
  QStringList WedLabels;
  QStringList FaceLabels;
  QStringList VertexLabels;


};

#endif //TABLE_DIALOG