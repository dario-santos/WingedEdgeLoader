#pragma once

class Edge;

class Face {

public:
  Edge* edge = nullptr;

  Face(Edge* edge);
};