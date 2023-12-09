#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <glm/vec3.hpp>
#include <QComboBox>
#include <QDir>
#include <QStringList>

#include "TableDialog.hpp"
#include "renderer/MyGLWidget.hpp"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
public slots:
    void fileChosen(int idx);

private:
    TableDialog * tableDialog;
    MyGLWidget * mygl;
    QVBoxLayout *layout;
    QComboBox * chooseFile;
    Mesh * currentMesh;
};

#endif // MAIN_WIDGET_H