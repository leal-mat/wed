#include "Camera.hpp"

Camera::Camera(glm::vec3 _pos, glm::vec3 _at){
    pos = _pos;
    at = _at;
    up = glm::vec3(0.,1.,0.);
    yaw = 0.;
    pitch = 0.;

    fov = 90.;
    near = 0.1;
    far = 100.;
    w = 200;
    h = 200;
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

glm::mat4 & Camera::getViewMatrix(){
    return viewMatrix;
}

glm::mat4 & Camera::getProjMatrix(){
    return projMatrix;
}

void Camera::updateCamera(){
    viewMatrix = glm::lookAtRH(pos,at,up);
    projMatrix = glm::perspectiveFovRH(glm::radians(fov),w,h,near,far);
}
