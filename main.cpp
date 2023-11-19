#include "Mesh.hpp"
#include <iostream>

void print_(glm::vec3 v){
    std::cout<< v.x << " " << v.y << " " << v.z<<"\n";
}

int main(){

    glm::vec3 v(2.);
    std::vector<glm::vec3> v2;
    v2.push_back(v);

    auto it = v2.begin();
    print_(*it);
    print_(*++it);
    return 0;
}
