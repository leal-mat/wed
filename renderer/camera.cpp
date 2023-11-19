#include "camera.hpp"

Camera::Camera(glm::vec3 _pos = glm::vec3(0.,0.,0.), glm::vec3 _at = glm::vec3(0.,0.,0.)){
    pos = _pos;
    at = _at;
    up = glm::vec3(0.,1.,0.);
    updateCamera();
}

void Camera::setAt(glm::vec3 _at){
    at = _at;
    updateCamera();
}

void Camera::setPos(glm::vec3 _pos){
    pos = _pos;
    updateCamera();
}

void Camera::setFov(float _fov){
    fov = _fov;
    updateCamera();
}

void Camera::setViewPlanes(float _near, float _far){
    near = _near;
    far = _far;
    updateCamera();
}

void Camera::setCanvasDimensions(float _w , float _h){
    w = _w;
    h = _h;
    updateCamera();
}

glm::vec3 Camera::getPos() const{
    return pos;
}

glm::vec3 Camera::getAt() const{
    return at;
}

void Camera::updateCamera(){
    viewMatrix = glm::lookAt(pos,at,up);
    projMatrix = glm::perspectiveFov(fov,w,h,near,far);
}
