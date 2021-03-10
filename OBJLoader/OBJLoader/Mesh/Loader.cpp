#include "Loader.hpp"

#include <cstdlib>

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <fstream>
using std::ifstream;

#include <sstream>
using std::istringstream;

Mesh* Loader::LoadOBJ(const char* fileName)
{
  vector <Vertex *> vertices;
  vector <Edge*> edges;

  vector <Face*> faces;

  int nFaces = 0;

  ifstream objStream(fileName, std::ios::in);

  if (!objStream)
  {
    cerr << "The OBJ file does not exist: " << fileName << endl;
    exit(1);
  }

  string line, token;
  vector<int> face;

  getline(objStream, line);

  while(!objStream.eof())
  {
    // Remove white space
    TrimString(line);

    // Ignore empty and comment lines
    if(line.length() > 0 && line.at(0) != '#')
    {
      istringstream lineStream(line);

      lineStream >> token;

      if(token == "v") // Vertice 
      {
        float x, y, z;
        lineStream >> x >> y >> z;

        vertices.push_back(new Vertex(x, y, z));
      }
      else if (token == "f") // Face
      {
        nFaces++;

        // Process face
        face.clear();
        size_t slash1, slash2;
        while(lineStream.good())
        {
          string vertString;
          lineStream >> vertString;
          int pIndex = -1, nIndex = -1;

          slash1 = vertString.find("/");
          if (slash1 == string::npos)
          {
            pIndex = atoi(vertString.c_str()) - 1;
          }
          else
          {
            slash2 = vertString.find("/", slash1 + 1);
            pIndex = atoi(vertString.substr(0, slash1).c_str()) - 1;
            nIndex = atoi(vertString.substr(slash2 + 1, vertString.length()).c_str()) - 1;
          }

          if (pIndex == -1)
            printf("Missing point index!!!");
          else
            face.push_back(pIndex);

          if (nIndex != -1 && nIndex != pIndex)
            printf("Normal and point indices are not consistent.\n");
        }

        /*
        * 
        *               v1
        *              /\
        *             /  \
        *         e2 /    \ e1
        *           /  f   \
        *          /        \
        *      v3 +----------+ v2
        *              e3
        */
        Face* f = nullptr;

        Edge* face_edges[3] = { nullptr, nullptr, nullptr };

        for (int i = 0; i < 3; i++)
        {
          int i2 = (i + 1) % 3;

          Edge* e = nullptr;
          // 1 - Get or make edge
          if (MakeEdge(edges, vertices[face[i]], vertices[face[i2]], &face_edges[i]))
            edges.push_back(face_edges[i]);

          // 2 - Add Edge to vertices
          if (vertices[face[i]]->edge != nullptr)
            vertices[face[i]]->edge = face_edges[i];
          if (vertices[face[i2]]->edge != nullptr)
            vertices[face[i2]]->edge = face_edges[i];

          if (i == 0)
          {   
            f = new Face(face_edges[0]);
            faces.push_back(f);
          }
          // 3 - Add new face with this edge
          //   Add face to edge
          if (face_edges[i]->f1 == nullptr)
             face_edges[i]->f1 = f;
          else
             face_edges[i]->f2 = f;
          
        }
        
        // Add edges
        for (int i = 0; i < 3; i++)
        {
          // Get direction r or l?
          if (face_edges[i]->f2 == nullptr)
          {
            face_edges[i]->l_prev = GetPrevEdge(face_edges, face_edges[i]);
            face_edges[i]->l_next = GetNextEdge(face_edges, face_edges[i]);
          }
          else
          {
            // Because it's face 2 we change the next and prev
            // this is a causality of the way the functions are implemented
            // next compares vert v2
            // prev compares vert v1
            // Todo: Change GetNextEdge and GetPrevEdge to be universall
            face_edges[i]->r_prev = GetNextEdge(face_edges, face_edges[i]);
            face_edges[i]->r_next = GetPrevEdge(face_edges, face_edges[i]);
          }
        }
      }
    }
    getline(objStream, line);
  }

  objStream.close();

  // If there are no normals, calculate them storeVBO(points, normals, faces);

  return new Mesh(vertices, edges, faces);
}

void Loader::TrimString(string& str)
{
  const char* whiteSpace = " \t\n\r";

  size_t location;

  location = str.find_first_not_of(whiteSpace);
  str.erase(0, location);

  location = str.find_last_not_of(whiteSpace);
  str.erase(location + 1);
}


bool Loader::MakeEdge(vector<Edge*> edges, Vertex* v1, Vertex* v2, Edge** edge_out)
{
  // 1 - Verify if there's an edge with there two verticesse a aresta já foi criada
  for(Edge* e : edges)
  {
    if((Vertex::IsEqual(e->v1, v1) && Vertex::IsEqual(e->v2, v2)) 
      || (Vertex::IsEqual(e->v1, v2) && Vertex::IsEqual(e->v2, v1)))
    {
      // e is our edge
      *edge_out = e;
      return false;
    }
  }
  
  *edge_out = new Edge(v1, v2);
  return true;
}


Edge* Loader::GetPrevEdge(Edge* face_edges[], Edge* edge)
{
  // A aresta anterior é a aresta que tem o vertice V2 em comum
  for (int i = 0 ; i < 3 ; i++)
  {
    if (Edge::IsEqual(face_edges[i], edge))
      continue;

    if (Vertex::IsEqual(face_edges[i]->v2, edge->v2) || Vertex::IsEqual(face_edges[i]->v1, edge->v2))
      return face_edges[i];
  }

  return nullptr;
}


Edge* Loader::GetNextEdge(Edge* face_edges[], Edge* edge)
{
   // A aresta seguinte é a aresta que tem o vertice V1 em comum
  for (int i = 0; i < 3; i++)
  {
    if(Edge::IsEqual(face_edges[i], edge))
      continue;

    if (Vertex::IsEqual(face_edges[i]->v1, edge->v1) || Vertex::IsEqual(face_edges[i]->v2, edge->v1))
      return face_edges[i];
  }

  return nullptr;
}

vector<Edge*> Loader::GetEdges(vector<Edge*> edges, Edge* edge, bool toExclude)
{
  vector <Edge*> vertex_edges;

  // 1 - Verify if there's an edge with there two verticesse a aresta já foi criada
  for(Edge* e : edges)
  {
    if(toExclude)
      if(Edge::IsEqual(e, edge))
        continue;

    if(Vertex::IsEqual(e->v1, edge->v1) || Vertex::IsEqual(e->v2, edge->v2)
      || Vertex::IsEqual(e->v2, edge->v1) || Vertex::IsEqual(e->v1, edge->v2))
      vertex_edges.push_back(e);
  }

  return vertex_edges;
}
