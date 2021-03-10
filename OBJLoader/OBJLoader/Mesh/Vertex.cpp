#include "Vertex.hpp"

Vertex::Vertex(float x, float y, float z)
{
  this->point = vec3(x, y, z);
}

Vertex::Vertex(vec3 point)
{
  this->point = point;
}

string Vertex::ToString()
{
  return "Vertex(" + std::to_string(point.x) + ", " + std::to_string(point.y) + ", " + std::to_string(point.z) + ")";
}
