#ifndef WED_HPP
#define WED_HPP
#include "Vertex.hpp"
#include "Face.hpp"

class Wed{
  public:
    Vertex *start, *end;
    Face *left, *right;
    Wed *left_prev, *left_next;
    Wed *right_prev, *right_next;
};

#endif // WED_HPP