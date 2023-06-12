#include "viewer.hpp"
#include "ds.hpp"
#include <bits/stdc++.h>
#include <math.h>

namespace V = COL781::Viewer;
using namespace glm;

int square(int m , int n){

    // triangles 2*m*n
    // vertices (m+1)*(n+1)

    vec3 normal = {0.0 , 0.0 , 1.0};
    vec3 position = {0.0 , 0.0 , 0.0};
    ivec3 index ;

    std::vector<Vertex*> vertex_;
    std::vector<Triangle*> triangle_;

    float mm = 1.0/m;
    float nn = 1.0/n;
    // std::cout << mm << " " << nn << std::endl;
    for(int i = 0; i < m+1; i++){
        for(int j = 0; j< n+1; j++){
            Vertex* vertex = new Vertex();
            position[0] = i*mm - 0.5;
            position[1] = j*nn - 0.5;

            vertex->position = position;
            vertex->normal = normal;
            vertex_.push_back(vertex);
        }
    }

    for(int i = 0; i<m ; i++){
        for(int j = 0; j<n ; j++){
            int i1 = i*(n+1) + j;
            int i2 = i1+1;
            int i3 = i1+n+1;
            int i4 = i3+1;

            Triangle* triangle = new Triangle();
            index = {i1, i4, i3};
            triangle->index = index;
            triangle_.push_back(triangle);

            triangle = new Triangle();
            index = {i1, i2, i4};
            triangle->index = index;
            triangle_.push_back(triangle);
        }
    }

    int s1 = vertex_.size();
    int s2 = triangle_.size();

    // std::cout << s1 << " " << s2 << std::endl;

    vec3 vertices[s1];
    vec3 normals[s1];

    // std::cout << "Vertices : " << std::endl;
    for(int i = 0; i<s1; i++){
        vertices[i] = vertex_[i]->position;
    }

    // for(int i = 0; i<s1; i++){
    //     std::cout << vertices[i][0] << " " << vertices[i][1] << " " << vertices[i][2] << std::endl;
    // }
    // std::cout << "Normals : " << std::endl;
    for(int i = 0; i<s1; i++){
        normals[i] = vertex_[i]->normal;
    }
    // for(int i = 0; i<s1; i++){
    //     std::cout << normals[i][0] << " " << normals[i][1] << " " << normals[i][2] << std::endl;
    // }

	ivec3 triangles[s2];

    // std::cout << "Triangles : " << std::endl;
    for(int i = 0; i<s2; i++){
        triangles[i] = triangle_[i]->index;
    }
    // for(int i = 0; i<s2; i++){
    //     std::cout << triangles[i][0] << " " << triangles[i][1] << " " << triangles[i][2] << std::endl;
    // }


	V::Viewer v;
	if (!v.initialize("Mesh viewer", 640, 480)) {
		return EXIT_FAILURE;
	}

	v.setVertices(s1, vertices);

	v.setNormals(s1, normals);
	v.setTriangles(s2, triangles);
	v.view();
    return 0;
}

int renderSphere(int m, int n) {
    std::vector<Vertex*> vertexList;
    std::vector<Triangle*> triangleList;

    // Define vertex positions and normals using spherical coordinates
    for (int j = 0; j <= m; j++) {
        float phi = j * 2 * M_PI / m;
        float sinPhi = sin(phi);
        float cosPhi = cos(phi);
        // if(sinTheta < 1e-7 && sinTheta > -1e7){
        //     sinTheta = 0;
        // }
        // if(cosTheta < 1e-7 && cosTheta > -1e7){
        //     cosTheta = 0;
        // }

        for (int i = 0; i <= n; i++) {
            float theta = i * M_PI / n;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);


            // if(sinPhi < 1e-7 && sinPhi > -1e7){
            //     sinPhi = 0;
            // }
            // if(cosPhi < 1e-7 && cosPhi > -1e7){
            //     cosPhi = 0;
            // }

            float h1 = sinTheta * cosPhi;
            float h2 = sinTheta * sinPhi;
            float h3 = cosTheta;
            // if(abs(h1) < 1e-7  && abs(h1) >= -0){
            //     h1 = 0;
            // }
            // if(abs(h2) < 1e-7  && abs(h2) >= -0){
            //     h2 = 0;
            // }
            // if(abs(h3) < 1e-7  && abs(h3) >= -0){
            //     h3 = 0;
            // }
            vec3 position = vec3(h1, h2, h3);
            vec3 normal = normalize(position);
            Vertex* vertex = new Vertex();
            vertex->position = position;
            vertex->normal = normal;
            vertexList.push_back(vertex);
        }
    }

    int si1 = vertexList.size();

    // for(int i = 0; i< si1 ; i++){
    //     std::cout << "vertexlist " << i << std::endl;
    //     std::cout << vertexList[i]->position[0] << " " << vertexList[i]->position[1] << " " << 
    //     vertexList[i]->position[2] << "\n";

    // }

    // Define triangles using indices into the vertex list
    for(int i = 0; i<m ;i++){
        for(int j = 0; j<n ; j++){
            int i1 = i*(n+1) + j;
            int i2 = i1 + 1;
            int i3 = (i+1)*(n+1) + j;
            int i4 = i3 + 1;

            // std::cout << i << " " << j << " " << i1  << " " << i2 << " " << i3 << " " << i4 << "\n";

            if (j == 0) {
                Triangle* triangle = new Triangle();
                triangle->vertices[0] = vertexList[i1];
                triangle->vertices[1] = vertexList[i2];
                triangle->vertices[2] = vertexList[i4];
                ivec3 tem = {i1,i2,i4};
                triangle->index = tem;
                triangleList.push_back(triangle);
            } else if (j == n-1) {
                Triangle* triangle = new Triangle();
                triangle->vertices[0] = vertexList[i3];
                triangle->vertices[1] = vertexList[i1];
                triangle->vertices[2] = vertexList[i2];
                ivec3 tem = {i3,i1,i2};
                triangle->index = tem;
                triangleList.push_back(triangle);
            } else {
                Triangle* triangle1 = new Triangle();
                triangle1->vertices[0] = vertexList[i1];
                triangle1->vertices[1] = vertexList[i2];
                triangle1->vertices[2] = vertexList[i4];
                ivec3 tem = {i1,i2,i4};
                triangle1->index = tem;
                triangleList.push_back(triangle1);

                Triangle* triangle2 = new Triangle();
                triangle2->vertices[0] = vertexList[i4];
                triangle2->vertices[1] = vertexList[i3];
                triangle2->vertices[2] = vertexList[i1];
                tem = {i4,i3,i1};
                triangle2->index = tem;
                triangleList.push_back(triangle2);
            }

        }
    }
    

    // std::cout << sin(M_PI) << std::endl;
    int si = triangleList.size();

    // for(int i = 0; i< si ; i++){
    //     std::cout << "triangle " << i << std::endl;
    //     std::cout << triangleList[i]->vertices[0]->position[0] << " " << triangleList[i]->vertices[0]->position[1] << " " << 
    //     triangleList[i]->vertices[0]->position[2] << "\n";
    //     std::cout << triangleList[i]->vertices[1]->position[0] << " " << triangleList[i]->vertices[1]->position[1] << " " << 
    //     triangleList[i]->vertices[1]->position[2] << "\n";
    //     std::cout << triangleList[i]->vertices[2]->position[0] << " " << triangleList[i]->vertices[2]->position[1] << " " << 
    //     triangleList[i]->vertices[2]->position[2] << "\n";

    //     std::cout << triangleList[i]->index[0] << triangleList[i]->index[1] << triangleList[i]->index[2] << std::endl;

    // }

    // Convert vertex and triangle lists to arrays for Viewer
    int numVertices = vertexList.size();
    int numTriangles = triangleList.size();
    vec3 vertices[numVertices];
    vec3 normals[numVertices];
    ivec3 triangles[numTriangles];
    for (int i = 0; i < numVertices; i++) {
        vertices[i] = vertexList[i]->position;
        normals[i] = {0.0,0.0,0.0};
    }
    for (int i = 0; i < numTriangles; i++) {
        triangles[i] = ivec3(triangleList[i]->index);
    }

    V::Viewer v;
	if (!v.initialize("Mesh viewer", 640, 480)) {
		return EXIT_FAILURE;
	}

	v.setVertices(numVertices, vertices);

	v.setNormals(numVertices, normals);
	v.setTriangles(numTriangles, triangles);
	v.view();
    return 0;
}

int loadMeshFromObjFile(const std::string& filename) {

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::ivec3> triangles;

    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;  // skip comments and empty lines
        }

        std::istringstream iss(line);
        std::string token;
        iss >> token;

        // std::cout << token << std::endl;

        if (token == "v") {
            glm::vec3 vertex;
            iss >> vertex[0] >> vertex[1] >> vertex[2];
            // std::cout << vertex[0] << " " << vertex[1] << " " << vertex[2] << std::endl;
            vertices.push_back(vertex);
        } else if (token == "vn") {
            glm::vec3 normal;
            iss >> normal[0] >> normal[1] >> normal[2];
            normals.push_back(normal);
        } else if (token == "f") {
            std::vector<int> vertex_indices;
            while (iss >> token) {
                std::istringstream index_stream(token);
                int vertex_index, normal_index;
                char slash;
                index_stream >> vertex_index >> slash >> slash >> normal_index;
                // std::cout << vertex_index  << " ";
                vertex_indices.push_back(vertex_index - 1);   // convert to 0-based indexing
            }
            // std::cout << std::endl;
            for (int i = 2; i < vertex_indices.size(); i++) {
                triangles.push_back(glm::ivec3(
                    vertex_indices[0], vertex_indices[1], vertex_indices[2]
                ));
                // std::cout << vertex_indices[0] << " " << vertex_indices[1] << " " << vertex_indices[2] << std::endl;
            }
        }
    }

    int numVertices = vertices.size();
    int numnormals = normals.size();
    int numTriangles = triangles.size();
    vec3 vertices2[numVertices];
    vec3 normals2[numVertices];
    ivec3 triangles2[numTriangles];
    for (int i = 0; i < numVertices; i++) {
        vertices2[i] = vertices[i];
    }

    if(numnormals == 0){
        for (int i = 0; i < numVertices; i++) {
            normals2[i] = {0.0,0.0,0.0};
        }
    }
    else{
        for (int i = 0; i < numVertices; i++) {
            normals2[i] = normals[i];
        }
    }

    for (int i = 0; i < numTriangles; i++) {
        triangles2[i] = triangles[i];
    }

    V::Viewer v;
	if (!v.initialize("Mesh viewer", 640, 480)) {
		return EXIT_FAILURE;
	}

	v.setVertices(numVertices, vertices2);

	v.setNormals(numVertices, normals2);
	v.setTriangles(numTriangles, triangles2);
	v.view();
    return 0;

}

void addnormaltovertex(Vertex* v){
    int n = v->btriangle.size();
    vec3 sum_normals = {0.0,0.0,0.0};
    for(int i = 0; i<n ; i++){
        Triangle* temp = v->btriangle[i];
        glm::vec3 a = temp->vertices[0]->position;
        glm::vec3 b = temp->vertices[1]->position;
        glm::vec3 c = temp->vertices[2]->position;

        glm::vec3 r1 = b-a;
        glm::vec3 r2 = c-a;
        vec3 normal = cross(r1, r2);
        normal[0] = normal[0]/length(normal);
        normal[1] = normal[1]/length(normal);
        normal[2] = normal[2]/length(normal);
        sum_normals = sum_normals + normal;
    }
    sum_normals[0] = sum_normals[0]/n;
    sum_normals[1] = sum_normals[1]/n;
    sum_normals[2] = sum_normals[2]/n;
    v->normal = sum_normals;
}

int loadMeshFromObjFile2(const std::string& filename) {

    std::vector<Vertex*> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::ivec3> triangles;

    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            continue;  // skip comments and empty lines
        }

        std::istringstream iss(line);
        std::string token;
        iss >> token;

        // std::cout << token << std::endl;

        if (token == "v") {
            glm::vec3 vertex;
            iss >> vertex[0] >> vertex[1] >> vertex[2];
            Vertex* tmp = new Vertex();
            tmp->position = vertex;
            // std::cout << vertex[0] << " " << vertex[1] << " " << vertex[2] << std::endl;
            vertices.push_back(tmp);
        } else if (token == "vn") {
            glm::vec3 normal;
            iss >> normal[0] >> normal[1] >> normal[2];
            normals.push_back(normal);
        } else if (token == "f") {
            std::vector<int> vertex_indices;
            while (iss >> token) {
                std::istringstream index_stream(token);
                int vertex_index, normal_index;
                char slash;
                index_stream >> vertex_index >> slash >> slash >> normal_index;
                // std::cout << vertex_index  << " ";
                vertex_indices.push_back(vertex_index - 1);   // convert to 0-based indexing
            }
            // std::cout << std::endl;

            vec3 ind = glm::ivec3(
                vertex_indices[0], vertex_indices[1], vertex_indices[2]
            );
            Triangle* tri = new Triangle();
            tri->index = ind;
            tri->vertices[0] = vertices[ind[0]];
            tri->vertices[1] = vertices[ind[1]];
            tri->vertices[2] = vertices[ind[2]];

            vertices[vertex_indices[0]]->btriangle.push_back(tri);
            vertices[vertex_indices[1]]->btriangle.push_back(tri);
            vertices[vertex_indices[2]]->btriangle.push_back(tri);
            triangles.push_back(ind);
        }
    }



    int numVertices = vertices.size();
    for(int i = 0; i<numVertices ; i++){
        addnormaltovertex(vertices[i]);
    }

    

    int numnormals = normals.size();

    int numTriangles = triangles.size();

    vec3 vertices2[numVertices];
    vec3 normals2[numVertices];
    ivec3 triangles2[numTriangles];

    for (int i = 0; i < numVertices; i++) {
        vertices2[i] = vertices[i]->position;
    }

    if(numnormals == 0){
        for (int i = 0; i < numVertices; i++) {
            normals2[i] = vertices[i]->normal;
        }
    }
    else{
        for (int i = 0; i < numVertices; i++) {
            normals2[i] = normals[i];
        }
    }

    for (int i = 0; i < numTriangles; i++) {
        triangles2[i] = triangles[i];
    }

    V::Viewer v;
	if (!v.initialize("Mesh viewer", 640, 480)) {
		return EXIT_FAILURE;
	}

	v.setVertices(numVertices, vertices2);

	v.setNormals(numVertices, normals2);
	v.setTriangles(numTriangles, triangles2);
	v.view();
    return 0;

}


int main(){
    // return square(4,5);
    // return renderSphere(16,16);

    // return loadMeshFromObjFile("../meshes/bunny-1k.obj");

    return loadMeshFromObjFile2("../meshes/teapot.obj");
    return 0;
}