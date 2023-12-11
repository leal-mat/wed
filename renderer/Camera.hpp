#ifndef CAMERA_H
#define CAMERA_H
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <QObject>

static float speed = .2f;
static float xsens = .001f;
static float ysens = .001f;

class Camera : public QObject{
Q_OBJECT
public:
    Camera(glm::vec3 pos = glm::vec3(0.,0.,0.), glm::vec3 at = glm::vec3(0.,0.,0.));
    void setAt(glm::vec3 _at);
    void setPos(glm::vec3 _pos);

    void setFov(float _fov);
    void setViewPlanes(float _near, float _far);
    void setCanvasDimensions(float _w , float _h);

    glm::vec3 getAt() const;
    glm::vec3 getPos() const;

    glm::mat4 & getViewMatrix();
    glm::mat4 & getProjMatrix();

    void walkRight();
    void walkLeft();
    void walkFront();
    void walkBack();

    void cameraShake(float x, float y);

    void resetView();


private:
    void updateView();
    void updateProj();

private:       

    glm::mat4 viewMatrix;
    glm::mat4 projMatrix;

    glm::vec3 at;
    glm::vec3 pos;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;
    float yaw;
    float pitch;

    float fov;
    float near;
    float far;
    float w;
    float h;
};

#endif // CAMERA_HPP
