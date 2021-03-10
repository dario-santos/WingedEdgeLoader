#include "Mesh.hpp"


Mesh::Mesh(vector<Vertex*> vertices, vector<Edge*> edges, vector<Face*> faces)
{
  this->vertices = vertices;
  this->edges = edges;
  this->faces = faces;

}





string Mesh::ToString()
{
  string s = "Mesh = [\n ";

  //for (Face* f : faces)
  //  s += f->ToString();



  s += "\n\n\Edges:\n";

  for (Edge* e : edges)
    s += e->ToString();

  s += "\n\n\nVertices:\n";

  for (Vertex* v : vertices)
    s += v->ToString() + "\n ";


  return s + "]";
}