#include "GLProgram.hpp"
#include <iostream>


GLProgram::GLProgram(QOpenGLContext * _context){
    if(_context != nullptr){
        context = _context;
        f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_3_Core>(_context);    
    }
} 

GLProgram::~GLProgram(){}

char * GLProgram::readFile(const std::string & fileName) const{
    std::ifstream file;
    long unsigned length;
    file.open(fileName);
    file.seekg(0,std::ios::end);
    length = file.tellg();
    file.seekg(0,std::ios::beg);
    char * buffer = new char[length+1];
    file.read(buffer,length);
    buffer[length] = '\0';
    file.close();
    return buffer;

}



void GLProgram::createShaderFromFile(const std::string & vertexShaderFileSource, const std::string & fragmentShaderFileSource)  {


    QDir dir(QDir::currentPath());
    dir.cdUp();
    dir.cd("shaders");

    const std::string vertexPath = dir.path().toStdString()+ "/" + vertexShaderFileSource;

    const std::string frag_path = dir.path().toStdString() + "/" + fragmentShaderFileSource;
    uint vertexShader = compileShader(readFile(vertexPath), GL_VERTEX_SHADER);
    uint fragmentShader = compileShader( readFile(frag_path) , GL_FRAGMENT_SHADER);
    program = f->glCreateProgram();
    f->glAttachShader(program,vertexShader);
    f->glAttachShader(program,fragmentShader);
    f->glLinkProgram(program);
    f->glValidateProgram(program);

    f->glDetachShader(program, vertexShader);
    f->glDetachShader(program, fragmentShader);
    f->glDeleteShader(vertexShader);
    f->glDeleteShader(fragmentShader);


}


void GLProgram::createShaderFromString(const char * vertex ,const  char * frag) {
    uint vertexShader = compileShader(vertex, GL_VERTEX_SHADER);
    uint fragmentShader = compileShader( frag, GL_FRAGMENT_SHADER);
    program = f->glCreateProgram();
    f->glAttachShader(program,vertexShader);
    f->glAttachShader(program,fragmentShader);
    f->glLinkProgram(program);
    f->glValidateProgram(program);

    f->glDetachShader(program, vertexShader);
    f->glDetachShader(program, fragmentShader);
    f->glDeleteShader(vertexShader);
    f->glDeleteShader(fragmentShader);




}

uint GLProgram::compileShader(const char * shader, uint type){
    uint id = f->glCreateShader(type);
    f->glShaderSource(id,1,&shader,nullptr);
    f->glCompileShader(id);

    int result;
    f->glGetShaderiv(id , GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int length;
        f->glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char * message = (char *)alloca(length * sizeof(char));
        f->glGetShaderInfoLog(id , length , &length , message);  
        std::cout<< "Failed to compile shader " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader\n";
        std::cout << message << std::endl;
    }

    return id;


}


uint GLProgram::getProgramId() const{
    return program;
}