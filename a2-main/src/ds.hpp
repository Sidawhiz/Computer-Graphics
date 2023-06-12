#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Edge;
class Triangle;

class Vertex {
public:
    Vertex(){

    }
    glm::vec3 position;
    Edge *edge;
    glm::vec3 normal;
    std::vector<Triangle*> btriangle;
};

class Edge {
public:
    Edge(){

    }
    Triangle *triangle;
    int index;
};

class Triangle {
public:
    Triangle(){

    }
    Vertex* vertices[3];
    Edge* neighbors[3];
    glm::ivec3 index;
};