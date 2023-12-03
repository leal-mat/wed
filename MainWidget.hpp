#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <glm/vec3.hpp>

#include "TableDialog.hpp"
#include "renderer/MyGLWidget.hpp"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
public slots:
    void someSlot();

private:
    TableDialog * tableDialog;
    MyGLWidget * mygl;
    QHBoxLayout *layout;
};

#endif // MAIN_WIDGET_H