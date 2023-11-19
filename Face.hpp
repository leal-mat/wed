#ifndef FACE_H
#define FACE_H

class Wed;

class Face{
  public:
    Face(Wed *_wed): wed(_wed){
    };
    Wed * wed;
};


#endif //FACE_H
