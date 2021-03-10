#pragma once

#include <vector>
using std::vector;

#include "Vertex.hpp"
#include "Face.hpp"
#include "Edge.hpp"
#include "Mesh.hpp"

#include <string>
using std::string;

class Loader
{
private:
  void TrimString(string& str);


  bool MakeEdge(vector<Edge*> edges, Vertex* v1, Vertex* v2, Edge** edge_out);

  vector<Edge*> GetEdges(vector<Edge*> edges, Edge* edge, bool toExclude = true);

  Edge* GetPrevEdge(Edge* face_edges[], Edge* edge);

  Edge* GetNextEdge(Edge* face_edges[], Edge* edge);

public:
  Loader() {};

  Mesh* LoadOBJ(const char* fileName);
};