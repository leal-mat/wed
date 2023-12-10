#ifndef FACE_TABLE_HPP
#define FACE_TABLE_HPP

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


class FaceTable : public QWidget
{
    Q_OBJECT
public:
    FaceTable(MenuCreator *);
    ~FaceTable();
    void makeFaceTable(std::vector<Face*> * faces);
    QTableWidget * getFaceTable();
private:
    QTableWidget * faceTable;
    QStringList faceLabels;
    int currentIndex;
    std::string currentVal;
    MenuCreator *menuCreator;

public slots:
    void popupContextMenuFace(QPoint pos);

signals:
  void faceSignal(std::string currentVal);
};


#endif // FACE_TABLE_HPP