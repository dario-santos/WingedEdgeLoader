#include "Mesh/Loader.hpp"

#include "Mesh/Mesh.hpp"

#include <iostream>

int main() 
{ 
  Loader* l = new Loader();
  Mesh* mesh = l->LoadOBJ("Cube.obj");

  std::cout << mesh->ToString() << std::endl;
  return 1; 
}