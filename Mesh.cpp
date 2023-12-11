#include "Mesh.hpp"
#include "renderer/MyGLWidget.hpp"


void __findDuplicateFaces(std::vector<Face*> a){
  int cont=0;
  for (int i=0; i < a.size(); i++){
    for (int j=0; j<a.size(); j++){
      if (i!=j && a[i]->edge->edge.first == a[j]->edge->edge.first &&  a[i]->edge->edge.second == a[j]->edge->edge.second ){
        std::cout<<"duplicado!: <" <<  a[i]->edge->edge.first << ", " << a[i]->edge->edge.second << ">\n";
        cont++;
      }
    }
  }
  std::cout<<"numero de duplicados (ele conta 2 vezes o mesmo): "<<cont<<std::endl;
}

void getValues(const char &t, std::vector<float> *vec, std::string str)
{

    if (t == 'v')
    {

        std::stringstream ss(str);
        std::string result = "";
        int pos = 0;
        while (std::getline(ss, result, ' '))
        {
            vec->at(pos) = std::stof(result, 0);
            pos++;
        }
    }
    else if (t == 'f')
    {
        std::stringstream ss(str);
        std::string result = "";
        int pos = 0;
        int index = 0;
        while (std::getline(ss, result, ' '))
        {
            std::stringstream new_stream(result);
            std::string face;
            std::getline(new_stream, face, '/');
            vec->at(pos++) = std::stof(face) - 1;
        }
        std::reverse(vec->begin(), vec->end());
    }
}


Mesh::Mesh(QOpenGLContext * context) {
  if(context == nullptr){
    std::cout<<"null context\n";
  }
  else{
    currentContext = context;
    f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_3_Core>(context);
  }
}

Wed* Mesh::getBaseWed(){
    return base_wed;
}

void Mesh::getMeshProperties(std::string fileName)
{ 
    QDir dir(QDir::currentPath());
    dir.cdUp();

    QString path = dir.path();
    std::string result = "";
    std::fstream myObj;
    myObj.open(path.toStdString() + "/objects/" + fileName, std::ios::in);
    std::cout << std::fixed;
    std::cout << std::setprecision(4);
    int vec_counter = 0;
    if (myObj.is_open())
    {
        std::vector<float> points;
        std::vector<float> faces;
        points.reserve(3);
        points.resize(3);
        faces.reserve(3);
        faces.resize(3);
        while (std::getline(myObj, result))
        {
            if (result[0] == 'v' && result[1] == ' ')
            {
                getValues(result[0], &points, result.substr(2, result.size() - 1));
                glm::vec3 vertex(points.at(0), points.at(1), points.at(2));
                vertex_vector.emplace_back(std::make_pair(vertex, nullptr));
            }
            else if (result[0] == 'f' && result[1] == ' ')
            {
                getValues(result[0], &faces, result.substr(2, result.size() - 1));
                pair<int, int> edge1(faces.at(0), faces.at(1));
                pair<int, int> edge2(faces.at(1), faces.at(2));
                pair<int, int> edge3(faces.at(2), faces.at(0));
                glm::vec3 indexes(faces.at(0), faces.at(1), faces.at(2));
                edge_face_map.insert({edge1, indexes});
                edge_face_map.insert({edge2, indexes});
                edge_face_map.insert({edge3, indexes});

            }
        }
    }
    // Para mostrar o que temos nos mapas, descomente essa secao; //

    // unordered multimap:
    //std::cout << "Indices\n";
    //for (auto elem : edge_face_map) {
    //  // std::cout << "(" << elem.first.first << ", " << elem.first.second << "); "<<
    //  // "face: " << elem.second.x << " " << elem.second.y<< " " << elem.second.z << std::endl;
    //}
    //std::cout<<"Teste\n";
    //pair<int,int> t1(4,2);
    //auto v = edge_face_map.find(t1);
    //std::cout<<"Quantidade de valores nessa key: " << edge_face_map.count(t1)<<std::endl;
    //while(v != edge_face_map.end()) {
    //    auto i = *v;
    //    // std::cout<< "face: " << i.second.x << " " << i.second.y<< " " << i.second.z << std::endl;
    //    v++;
    //}

    //exit(-1);
    return;
}

void Mesh::updateMesh(){
  raw_vertexes_vector.clear();
  edges_idx_vector.clear();
  for(auto p : vertex_vector){
    Vertex v = *(p.second);
    raw_vertexes_vector.push_back(v);
  }
  for(auto q : wed_vector){
    edges_idx_vector.push_back(q->edge.first);
    edges_idx_vector.push_back(q->edge.second);
  } 
}

void Mesh::setGLWidget(MyGLWidget * mgl){
  glWidget = mgl;
}

void Mesh::init() {
 
  //pontos e linhas, por enquanto...
  VAO.reserve(4);
  VAO.resize(4);


  VBO.reserve(4);
  VBO.resize(4);

  EBO.reserve(4);
  EBO.resize(4);

  program.reserve(4);
  program.resize(4);

  idxVector.reserve(vertex_vector.size());
  idxVector.resize(vertex_vector.size());
  std::iota(idxVector.begin(),idxVector.end(),0);

  if(currentContext == nullptr){
    std::cout<<"null context 2\n";
  }
  for(int i = 0; i < 4; i++){
    f->glGenVertexArrays(1,&VAO[i]);
    f->glGenBuffers(1,&VBO[i]);
    f->glGenBuffers(1,&EBO[i]);
    program[i] = GLProgram(currentContext);
  }

  //meshProgram
  program[0].createShaderFromFile("polShader.vert","polShader.frag");
  
  //markedProgram
  program[1].createShaderFromFile("markedShader.vert","markedShader.frag");

  //unMarkedProgram
  program[2].createShaderFromFile("unMarkedShader.vert","unMarkedShader.frag");
  //std::cout<<"Criou Shader\n";

  std::cout<<"gerou buffers\n";
  //Points initialization, index 0

  f->glBindVertexArray(VAO[0]);
  
  f->glBindBuffer(GL_ARRAY_BUFFER,VBO[0]);
  f->glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_vector.size()*10, raw_vertexes_vector.data(), GL_DYNAMIC_DRAW);




  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
  f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * idxVector.size()*10, idxVector.data(), GL_DYNAMIC_DRAW);



  GLint position_attribute = f->glGetAttribLocation(program[0].getProgramId(), "position");
  GLint color_attribute = f->glGetAttribLocation(program[0].getProgramId(), "color_a");


  f->glVertexAttribPointer(position_attribute, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), 0);
  f->glVertexAttribPointer(color_attribute, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));

  f->glEnableVertexAttribArray(position_attribute);
  f->glEnableVertexAttribArray(color_attribute);

  f->glBindBuffer(GL_ARRAY_BUFFER, 0); //unbid current VBO
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbid current EBO
  f->glBindVertexArray(0); //unbind current VAO




  //lines
  f->glBindVertexArray(VAO[1]);
  
  f->glBindBuffer(GL_ARRAY_BUFFER,VBO[1]);
  f->glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_vector.size()*10, raw_vertexes_vector.data(), GL_DYNAMIC_DRAW);
//
//
//
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
  f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 10000 ,edges_idx_vector.data(),GL_DYNAMIC_DRAW);
  
//
//
//
  GLint position_attribute1 = f->glGetAttribLocation(program[0].getProgramId(), "position");
  GLint color_attribute1 = f->glGetAttribLocation(program[0].getProgramId(), "color_a");
//
  f->glVertexAttribPointer(position_attribute1, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), 0);
  f->glVertexAttribPointer(color_attribute1, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)));
//
  f->glEnableVertexAttribArray(position_attribute1);
  f->glEnableVertexAttribArray(color_attribute1);
//

  f->glBindBuffer(GL_ARRAY_BUFFER, 0); //unbid current VBO
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbid current EBO
  f->glBindVertexArray(0); //unbind current VAO

  //markedEdges
  //f->glUseProgram(program[1].getProgramId());
  f->glBindVertexArray(VAO[2]);
  
  f->glBindBuffer(GL_ARRAY_BUFFER,VBO[2]);
  f->glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_vector.size()*10, raw_vertexes_vector.data(), GL_DYNAMIC_DRAW);
//
//
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
  f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 10000 ,marked_idx_vector_edge.data(),GL_DYNAMIC_DRAW);
  
//
//
//
  GLint position_attribute2 = f->glGetAttribLocation(program[1].getProgramId(), "position");
//
  f->glVertexAttribPointer(position_attribute2, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), 0);
//
  f->glEnableVertexAttribArray(position_attribute2);
  f->glBindBuffer(GL_ARRAY_BUFFER,0); //unbid current VBO
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); //unbid current EBO
  f->glBindVertexArray(0); //unbind current VAO





























  f->glBindVertexArray(VAO[3]);
  
  f->glBindBuffer(GL_ARRAY_BUFFER,VBO[3]);
  f->glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_vector.size()*10, raw_vertexes_vector.data(), GL_DYNAMIC_DRAW);




  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[3]);
  f->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * idxVector.size()*10, marked_idx_vector_point.data(), GL_DYNAMIC_DRAW);


  GLint position_attribute3 = f->glGetAttribLocation(program[0].getProgramId(), "position");

  f->glVertexAttribPointer(position_attribute3, 3, GL_FLOAT,GL_FALSE, sizeof(Vertex), 0);

  f->glEnableVertexAttribArray(position_attribute3);

  f->glBindBuffer(GL_ARRAY_BUFFER, 0); //unbid current VBO
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbid current EBO
  f->glBindVertexArray(0); //unbind current VAO

}



void Mesh::draw() {
  
  f->glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
  f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  f->glBindBuffer(GL_ARRAY_BUFFER,0); //unbid current VBO
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); //unbid current EBO
  f->glBindVertexArray(0); //unbind current VAO

  uint p0ID = program[0].getProgramId();

  f->glUseProgram(p0ID);
  GLuint vmatrix = f->glGetUniformLocation(p0ID, "m_view");
  GLuint pmatrix = f->glGetUniformLocation(p0ID, "m_proj");
  //GLuint pointsize = f->glGetUniformLocation(p0ID, "gl_PointSize");
  f->glUniformMatrix4fv(vmatrix, 1, GL_FALSE, glm::value_ptr(glWidget->getCamera()->getViewMatrix()));
  f->glUniformMatrix4fv(pmatrix, 1, GL_FALSE, glm::value_ptr(glWidget->getCamera()->getProjMatrix()));
  //f->glUniform1f(pointsize, 10.f);



  uint p2ID = program[2].getProgramId();

  f->glUseProgram(p2ID);
  GLuint vmatrix2 = f->glGetUniformLocation(p2ID, "m_view");
  GLuint pmatrix2 = f->glGetUniformLocation(p2ID, "m_proj");
  //GLuint pointsize = f->glGetUniformLocation(p0ID, "gl_PointSize");
  f->glUniformMatrix4fv(vmatrix2, 1, GL_FALSE, glm::value_ptr(glWidget->getCamera()->getViewMatrix()));
  f->glUniformMatrix4fv(pmatrix2, 1, GL_FALSE, glm::value_ptr(glWidget->getCamera()->getProjMatrix()));
  //f->glUniform1f(pointsize, 10.f);



  f->glBindBuffer(GL_ARRAY_BUFFER,VBO[0]);


  void * ptrPoint = f->glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
  memcpy(ptrPoint, raw_vertexes_vector.data(), raw_vertexes_vector.size() * (sizeof(Vertex)));
  f->glUnmapBuffer(GL_ARRAY_BUFFER);


  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO[0]);

  void * ptrPointEle = f->glMapBuffer(GL_ELEMENT_ARRAY_BUFFER,GL_WRITE_ONLY);
  memcpy(ptrPointEle,idxVector.data(), idxVector.size()* sizeof(uint));
  f->glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);


  f->glBindVertexArray(VAO[0]);

  f->glUseProgram(program[2].getProgramId());
  f->glDrawElements(GL_POINTS,idxVector.size(), GL_UNSIGNED_INT, idxVector.data());

  f->glBindBuffer(GL_ARRAY_BUFFER,0); //unbid current VBO
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); //unbid current EBO
  f->glBindVertexArray(0); //unbind current VAO


  f->glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);

  f->glBindBuffer(GL_ARRAY_BUFFER,VBO[1]);


  void * ptrPoint1 = f->glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
  memcpy(ptrPoint1, raw_vertexes_vector.data(), raw_vertexes_vector.size() * (sizeof(Vertex)));
  f->glUnmapBuffer(GL_ARRAY_BUFFER);

  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO[1]);

  void * ptrPointEle1 = f->glMapBuffer(GL_ELEMENT_ARRAY_BUFFER,GL_WRITE_ONLY);
  memcpy(ptrPointEle1,edges_idx_vector.data(), edges_idx_vector.size()* sizeof(uint));
  f->glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);



  f->glBindVertexArray(VAO[1]);

  f->glUseProgram(program[0].getProgramId());
  f->glDrawElements(GL_LINES,edges_idx_vector.size(), GL_UNSIGNED_INT, edges_idx_vector.data());

  f->glClear(GL_DEPTH_BUFFER_BIT);


  f->glBindBuffer(GL_ARRAY_BUFFER,0); //unbid current VBO
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); //unbid current EBO
  f->glBindVertexArray(0); //unbind current VAO





  f->glClear( GL_DEPTH_BUFFER_BIT);

  //Drawing Marked Edges
  std::cout<< "Drawing marked edges: " << "\n";

  uint p1ID = program[1].getProgramId();

  //f->glBindVertexArray(VAO[2]);
  f->glUseProgram(p1ID);
  GLuint vmatrix1 = f->glGetUniformLocation(p1ID, "m_view");
  GLuint pmatrix1 = f->glGetUniformLocation(p1ID, "m_proj");
  //GLuint pointsize1 = f->glGetUniformLocation(p1ID, "gl_PointSize");
  f->glUniformMatrix4fv(vmatrix1, 1, GL_FALSE, glm::value_ptr(glWidget->getCamera()->getViewMatrix()));
  f->glUniformMatrix4fv(pmatrix1, 1, GL_FALSE, glm::value_ptr(glWidget->getCamera()->getProjMatrix()));
  //f->glUniform1f(pointsize, 10.f);

  f->glBindBuffer(GL_ARRAY_BUFFER,VBO[2]);


  void * ptrPoint2 = f->glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
  memcpy(ptrPoint2, raw_vertexes_vector.data(), raw_vertexes_vector.size() * (sizeof(Vertex)));
  f->glUnmapBuffer(GL_ARRAY_BUFFER);


  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO[2]);


  void * ptrPointEle2 = f->glMapBuffer(GL_ELEMENT_ARRAY_BUFFER,GL_WRITE_ONLY);
  memcpy(ptrPointEle2, marked_idx_vector_edge.data(), marked_idx_vector_edge.size()* sizeof(uint));
  f->glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);



  //f->glBindVertexArray(VAO[2]);
  f->glBindVertexArray(VAO[2]);
  f->glUseProgram(program[1].getProgramId());
  f->glDrawElements(GL_LINES, marked_idx_vector_edge.size(), GL_UNSIGNED_INT, marked_idx_vector_edge.data());


  f->glBindBuffer(GL_ARRAY_BUFFER,0); //unbid current VBO
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); //unbid current EBO
  f->glBindVertexArray(0); //unbind current VAO




















  f->glBindBuffer(GL_ARRAY_BUFFER,VBO[3]);


  void * ptrPoint3 = f->glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
  memcpy(ptrPoint3, raw_vertexes_vector.data(), raw_vertexes_vector.size() * (sizeof(Vertex)));
  f->glUnmapBuffer(GL_ARRAY_BUFFER);


  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO[3]);

  void * ptrPointEle3 = f->glMapBuffer(GL_ELEMENT_ARRAY_BUFFER,GL_WRITE_ONLY);
  memcpy(ptrPointEle3,marked_idx_vector_point.data(), marked_idx_vector_point.size()* sizeof(uint));
  f->glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);


  f->glBindVertexArray(VAO[3]);

  f->glUseProgram(program[1].getProgramId());
  f->glDrawElements(GL_POINTS,marked_idx_vector_point.size(), GL_UNSIGNED_INT, marked_idx_vector_point.data());

  f->glBindBuffer(GL_ARRAY_BUFFER,0); //unbid current VBO
  f->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); //unbid current EBO
  f->glBindVertexArray(0); //unbind current VAO

  
}



void Mesh::buildMesh() {
    base_wed = new Wed((*edge_face_map.begin()).first);
    base_wed->status = STATUS::CREATED;
    pair<int, int> firstEdge = (*edge_face_map.begin()).first;
    edge_creation_map.insert({firstEdge, base_wed});
    std::cout << "base wed: " << "<" << base_wed->edge.first <<", " << base_wed->edge.second <<">\n";
    base_wed->rightNext(&edge_face_map, &edge_creation_map, &face_map, &vertex_vector);
    base_wed->leftNext(&edge_face_map, &edge_creation_map, &face_map, &vertex_vector);
    return;
}

void Mesh::createWedVector(){
    int cont=0;
    for (auto elem : edge_creation_map) {
        
        wed_vector.push_back(elem.second);
        // 352, 307
        if(elem.second->edge.first == 352 && elem.second->edge.second == 307) {
            std::cout << "A POSICAO DO BASE WED EH ESSA: " << cont+1 << "\n";
        }
        cont++;
    }
}

void Mesh::createVertexesVector(){
    for (auto elem : vertex_vector) {
        vertexes_vector.push_back(elem.second);
    }
}

void Mesh::createFaceVector(){
    for (auto elem : face_map) {
        face_vector.push_back(elem.second);
    }
    //debug das faces
    __findDuplicateFaces(face_vector);
}

std::vector<Wed *> & Mesh::getWedVector() {
    return wed_vector;
}

std::vector<Face *> & Mesh::getFaceVector() {
    return face_vector;
}

std::vector<Vertex*> & Mesh::getVertexesVector() {
    return vertexes_vector;
}

Wed* Mesh::consultEdgeCreationMap(pair<int, int> _edge){
    auto it_edge = edge_creation_map.find(_edge);
    return (*it_edge).second;
}


Vertex* Mesh::consultVertexesVector(int index){
    for (auto val: vertexes_vector)
    {
        if(val->index == index){
            return val;
        }
    }
    return nullptr;
}


Vertex* Mesh::consultVertexesVector(pair<int, int> _edge){
  for (auto val: vertexes_vector)
  {
    if(val->edge->edge == _edge){
      return val;
    }
  }
  return nullptr;
}


Face* Mesh::consultFaceVector(pair<int, int> _edge){
    for (auto val: face_vector)
    {
        if(val->edge->edge == _edge){
            return val;
        }
    }
    return nullptr;
}

// dado vértice, encontrar arestas adjacentes
void Mesh::EV(Vertex* v) {
    Wed* e0 = v->edge;
    Wed* edge = e0;
    do
    {
        if (edge->end == v) {
            edge = edge->right_next; 
        }
        else {
            edge = edge->left_next; 
        }
        markEdge(edge);
    } while (edge != e0 && edge != nullptr);
    return;
}


// dado aresta, encontrar arestas adjacentes
void Mesh::EE(Wed* e) {
    EV(e->start);
    EV(e->end);
    return;
}

// dado aresta, encontrar faces adjacentes
void Mesh::FE(Wed* e) {
    markFace(e->right);
    markFace(e->left);
    return;
}

// dado aresta, encontrar vértices adjacentes
void Mesh::VE(Wed* e){
     markVertex(e->start);
     markVertex(e->end);
}

// dado face, encontrar arestas adjacentes
void Mesh::EF(Face* face){
    Wed* e0 = face->edge;
    Wed* edge = e0;
    do
    {
        if (edge->right == face){
            std::cout<<"EF==\n";
            edge=edge->right_prev;
        }
        else {
            edge=edge->left_prev;
        }
        markEdge(edge);
    } while (edge!=e0);
}

void Mesh::markFace(Face* face){
  if (face != nullptr)
  {
    face->visit = true;
    std::cout<<"Visitei face da aresta: " << "<" << face->edge->edge.first << ", "<< face->edge->edge.second<<">\n";
    // marked_idx_vector_edge.push_back((uint)face->edge->edge.first);
    // marked_idx_vector_edge.push_back((uint)face->edge->edge.second);
    EF(face);
  }
}

void Mesh::markEdge(Wed* edge){
  if (edge != nullptr)
  {
    edge->visit = true;
    std::cout << "Visitei a aresta: " << "<" << edge->edge.first << ", "<< edge->edge.second << ">\n";
    marked_idx_vector_edge.push_back((uint)edge->edge.first);
    marked_idx_vector_edge.push_back((uint)edge->edge.second);
  }
}

void Mesh::markVertex(Vertex* vertex){
  if (vertex != nullptr)
  {
    vertex->visit = true;
    std::cout << "Visitei o vértice "<<vertex->index<<": " << "<" << vertex->edge->edge.first << ", "<< vertex->edge->edge.second << ">\n";
    marked_idx_vector_point.push_back((uint)vertex->index);
  }
}

void Mesh::clearMarkedEdges(){
  std::cout<<"Cleaning marked_idx_vector_edge and marked_idx_vector_point\n" ;
  marked_idx_vector_edge.clear();
  marked_idx_vector_point.clear();
}

