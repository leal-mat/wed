#ifndef MENU_CREATOR_HPP
#define MENU_CREATOR_HPP

#include <QMenu>
#include <QPoint>
#include <QAction>
#include <QObject>

class MenuCreator : public QObject{
  Q_OBJECT
    public:
    MenuCreator();
    ~MenuCreator();
    
    QMenu * getVertexMenu();
    QMenu * getFaceMenu();
    QMenu * getEdgeMenu();

    QAction * getEVAction();
    QAction * getEEAction();
    QAction * getFEAction();
    QAction * getVEAction();
    QAction * getEFAction();

    private:
    //Menus
    QMenu * vertexMenu;
    QMenu * faceMenu;
    QMenu * edgeMenu;

    //Actions
    QAction * EVAction;
    QAction * EEAction;
    QAction * FEAction;
    QAction * VEAction;
    QAction * EFAction;

};



#endif //MENU_CREATOR_HPP
