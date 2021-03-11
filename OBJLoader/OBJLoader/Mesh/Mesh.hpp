#pragma once

#include <GL/glew.h>

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "Edge.hpp"
#include "Face.hpp"
#include "Vertex.hpp"


class Mesh {
public:
  vector<Vertex*> vertices;
  vector<Edge*> edges;
  vector<Face*> faces;


  // Mesh VAO
  GLuint meshVAO = 0;
  GLuint verticeBufferId = 0;


  Mesh(vector<Vertex*> vertices, vector<Edge*> edges, vector<Face*> faces);

  void StoreVBO();

  void Render();


  string ToString();
};