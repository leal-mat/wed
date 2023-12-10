#include "Camera.hpp"
#include <iostream>

Camera::Camera(glm::vec3 _pos, glm::vec3 _at){
    pos = _pos;
    at = _at;
    worldUp = glm::vec3(0.,1.,0.);
    up = worldUp;
    right = glm::vec3(1.);
    yaw = -90.;
    pitch = 0.;

    fov = 90.;
    near = 0.1;
    far = 100.;
    w = 200;
    h = 200;
    updateProj();
    updateView();
}

void Camera::setAt(glm::vec3 _at){
    at = _at;
    updateView();
}

void Camera::setPos(glm::vec3 _pos){
    pos = _pos;
    updateView();
}

void Camera::setFov(float _fov){
    fov = _fov;
    updateView();
}

void Camera::setViewPlanes(float _near, float _far){
    near = _near;
    far = _far;
    updateProj();
}

void Camera::setCanvasDimensions(float _w , float _h){
    w = _w;
    h = _h;
    updateProj();
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

void Camera::walkRight(){
    //pos.x += speed;
    pos += right*speed;
    updateView();
}

void Camera::walkLeft(){
    pos -= right*speed;
    updateView();
}

void Camera::walkFront(){
    pos += at*speed;
    updateView();
}

void Camera::walkBack(){
    pos -= at*speed;
    updateView();
}

void Camera::cameraShake(float xoffset, float yoffset){
    xoffset *= xsens;
    yoffset *= (ysens);

    yaw   += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;


    // update Front, Right and Up Vectors using the updated Euler angles
    updateView();
}

void Camera::updateView(){

    glm::vec3 frontTemp;
    frontTemp.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontTemp.y = sin(glm::radians(pitch));
    frontTemp.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    at = glm::normalize(frontTemp);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(at, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up = glm::normalize(glm::cross(right, at));

    viewMatrix = glm::lookAtRH(pos,pos+at,up);

}

void Camera::updateProj(){
    projMatrix = glm::perspectiveFovRH(glm::radians(fov),w,h,near,far);
}
