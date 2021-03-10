#pragma once

#include <string>
using std::string;


#include <vector>
using std::vector;

#include "Face.hpp"
#include "Vertex.hpp"


/*
*  This class represents the edge e1:
*  r_next = e5
*  r_prev = e2
*  l_next = e3
*  l_prev = e4
* 
*     e3 \   / e2
*         \ /
*          + v1
*          |
*   f1     | e1    f2
*          |
*          + v2
*         / \
*     e4 /   \ e5
* 
*/


class Edge {

public:

  Edge* l_prev = nullptr;
  Edge* l_next = nullptr;
  Edge* r_prev = nullptr;
  Edge* r_next = nullptr;

  Vertex* v1 = nullptr;
  Vertex* v2 = nullptr;

  Face* f1 = nullptr;
  Face* f2 = nullptr;

  Edge(Vertex* v1, Vertex* v2);

  inline static bool IsEqual(Edge* e1, Edge* e2)
  {
    return ((Vertex::IsEqual(e1->v1, e2->v1) && Vertex::IsEqual(e1->v2, e2->v2))
      || (Vertex::IsEqual(e1->v1, e2->v2) && Vertex::IsEqual(e1->v2, e2->v1)));
  }

  string ToString();
};