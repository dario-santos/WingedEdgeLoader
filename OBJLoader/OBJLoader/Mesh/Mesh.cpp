#include "Mesh.hpp"

Mesh::Mesh(vector<Vertex*> vertices, vector<Edge*> edges, vector<Face*> faces)
{
  this->vertices = vertices;
  this->edges = edges;
  this->faces = faces;


  this->StoreVBO();
}

void Mesh::StoreVBO()
{
  float* v = new float[2 * 3 * faces.size()];

  int idx = 0;

  //Get face verts
  for (Face* f : this->faces)
  {
    // Vert1
    Edge* curr_edge = f->edge;

    v[idx] = curr_edge->v1->point.x;
    v[idx + 1] = curr_edge->v1->point.y;
    v[idx + 2] = curr_edge->v1->point.z;
    idx += 3;
    curr_edge = curr_edge->l_next;

    v[idx] = curr_edge->v1->point.x;
    v[idx + 1] = curr_edge->v1->point.y;
    v[idx + 2] = curr_edge->v1->point.z;
    idx += 3;
    curr_edge = curr_edge->l_next;

    v[idx] = curr_edge->v1->point.x;
    v[idx + 1] = curr_edge->v1->point.y;
    v[idx + 2] = curr_edge->v1->point.z;
    idx += 3;
  }


  /*int idx = 0;
  for (GLuint i = 0; i < nVerts; ++i)
  {
    v[idx] = points[i].x;
    v[idx + 1] = points[i].y;
    v[idx + 2] = points[i].z;

    n[idx] = normals[i].x;
    n[idx + 1] = normals[i].y;
    n[idx + 2] = normals[i].z;

    idx += 3;
   }
  */

  // Move vertex data to video memory; specifically to VBO called vertexbuffer
  glGenVertexArrays(1, &meshVAO);
  glGenBuffers(1, &verticeBufferId);
  glBindVertexArray(meshVAO);

  // Sets the verticeBufferId with the ID of the generated buffer
  glBindBuffer(GL_ARRAY_BUFFER, verticeBufferId);
  // Create a new data store for the buffer object, using the buffer object currently bound to target.
  glBufferData(GL_ARRAY_BUFFER, sizeof(v) * sizeof(GLfloat), v, GL_STATIC_DRAW);


  // position attribute
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  // Clean up
  // delete[] v;
  //delete[] n;
}



void Mesh::Render() 
{
  glBindVertexArray(this->meshVAO);
  glDrawArrays(GL_TRIANGLES, 0, 36);
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