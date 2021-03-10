#include "Edge.hpp"

Edge::Edge(Vertex* v1, Vertex* v2) 
{
  this->v1 = v1;
  this->v2 = v2;
}


string Edge::ToString()
{
  return "Edge(\n  v1: " + this->v1->ToString() + ",\n  v2: " +this->v2->ToString() + "\n)";
}
