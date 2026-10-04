#include <vector>

class Vertex;
class Face;
class HalfEdge;

class Vertex {
public:
    float x, y, z;
    HalfEdge* he;
    int id;
};

class Face {
public:
    HalfEdge* he;
};

class HalfEdge {
public:
    Vertex* target;
    Face* face;
    HalfEdge* next;
    HalfEdge* twin;
};

class Mesh {
public:
    std::vector<Vertex*>   vertices;
    std::vector<HalfEdge*> halfEdges;
    std::vector<Face*>     faces;
};