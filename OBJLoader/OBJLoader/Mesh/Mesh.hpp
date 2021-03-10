#pragma once

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

  Mesh(vector<Vertex*> vertices, vector<Edge*> edges, vector<Face*> faces);

  string ToString();
};