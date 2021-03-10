#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include <string>
using std::string;

class Edge;

class Vertex {
public:
  vec3 point;
  Edge* edge = nullptr;

  Vertex(float x, float y, float z);
  
  Vertex(vec3 point);

  inline static bool IsEqual(Vertex* v1, Vertex* v2)
  {
    return v1->point == v2->point;
  }

  string ToString();
};