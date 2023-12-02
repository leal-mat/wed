#ifndef GLPROGRAM_H
#define GLPROGRAM_H

#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLVersionFunctionsFactory>
#include <string>
#include <fstream>
#include <QDir>
class GLProgram{
    public:
    GLProgram(QOpenGLContext * context = 0);
    ~GLProgram();
    void createShaderFromFile(const std::string & vertexShaderFileSource , const std::string & fragmentShaderFileSource);
    void createShaderFromString(const char * vertex, const char * frag);

    uint getProgramId() const;
    


    private:
    char * readFile(const std::string & fileName) const; // do not delete allocated char *, not a big deal at this point, but still a memory leak
    uint compileShader(const char * shader, uint type);


    private:
    uint program;
    QOpenGLFunctions_3_3_Core * f;

    QOpenGLContext * context;
};

#endif