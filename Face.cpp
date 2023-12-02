#include "Face.hpp"
#include "Wed.hpp"

Face::Face(Wed *_wed): edge(_wed), visit(false) {
}

QString Face::debugFace(){
  if(edge != nullptr){
      return edge->debugWed();
    }
    return "null";
}



