#ifndef FACE_H
#define FACE_H
#include <QString>

class Wed;

class Face{
  public:
    Face(Wed *_wed = nullptr);
    QString debugFace();
    Wed * edge;
    bool visit;
};


#endif //FACE_H
