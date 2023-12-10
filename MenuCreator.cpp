#include "MenuCreator.hpp"

MenuCreator::MenuCreator() : QObject(){
	edgeMenu = new QMenu();
	faceMenu = new QMenu();
	vertexMenu = new QMenu();

    EEAction = new QAction("EE", this);
    FEAction = new QAction("FE", this);
    VEAction = new QAction("VE", this);
	EVAction = new QAction("EV", this);
	EFAction = new QAction("EF", this);

	edgeMenu->addAction(EEAction);
  	edgeMenu->addAction(FEAction);
  	edgeMenu->addAction(VEAction);
	faceMenu->addAction(EFAction);
	vertexMenu->addAction(EVAction);

}

MenuCreator::~MenuCreator(){}


QAction * MenuCreator::getEVAction(){
    return EVAction;
}
QAction * MenuCreator::getEEAction(){
    return EEAction;
}
QAction * MenuCreator::getFEAction(){
    return FEAction;
}
QAction * MenuCreator::getVEAction(){
    return VEAction;
}
QAction * MenuCreator::getEFAction(){
    return EFAction;
}


QMenu * MenuCreator::getVertexMenu(){
	return vertexMenu;
}
QMenu * MenuCreator::getFaceMenu(){
	return faceMenu;
}
QMenu * MenuCreator::getEdgeMenu(){
	return edgeMenu;
}
