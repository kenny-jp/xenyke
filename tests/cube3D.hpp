#ifndef TESTS_CUBE3D_HPP
#define TESTS_CUBE3D_HPP

#include <xenyke/gl/vertex_buffer.hpp>

using namespace xke;

template<class Buff> // Buff = EVertexBuffer<xke::BufferUsage::STATIC, xke::Primitive::TRIANGLES, 36>
void newCube3D(Buff& buff)
{
    float vertices[] = {
        // Front face
        -0.5f, -0.5f, 0.5f,  // Bottom-left
         0.5f, -0.5f, 0.5f,  // Bottom-right
         0.5f,  0.5f, 0.5f,  // Top-right
        -0.5f,  0.5f, 0.5f,  // Top-left
        // Back face
        -0.5f, -0.5f, -0.5f, // Bottom-left
         0.5f, -0.5f, -0.5f, // Bottom-right
         0.5f,  0.5f, -0.5f, // Top-right
        -0.5f,  0.5f, -0.5f, // Top-left
        // Left face
        -0.5f, -0.5f, -0.5f, // Bottom-back
        -0.5f, -0.5f,  0.5f, // Bottom-front
        -0.5f,  0.5f,  0.5f, // Top-front
        -0.5f,  0.5f, -0.5f, // Top-back
        // Right face
        0.5f, -0.5f, -0.5f, // Bottom-back
        0.5f, -0.5f,  0.5f, // Bottom-front
        0.5f,  0.5f,  0.5f, // Top-front
        0.5f,  0.5f, -0.5f, // Top-back
        // Top face
        -0.5f,  0.5f,  0.5f, // Front-left
        0.5f,  0.5f,  0.5f, // Front-right
        0.5f,  0.5f, -0.5f, // Back-right
        -0.5f,  0.5f, -0.5f, // Back-left
        // Bottom face
        -0.5f, -0.5f,  0.5f, // Front-left
        0.5f, -0.5f,  0.5f, // Front-right
        0.5f, -0.5f, -0.5f, // Back-right
        -0.5f, -0.5f, -0.5f  // Back-left
    };

    // Texture coordinates
    float texCoords[] = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    VertexArray va(36, Primitive::TRIANGLES);

    for (int i = 0; i < 36; ++i) {
        int vertexIndex = i * 3;
        int texCoordIndex = (i % 4) * 2;
        va.setVertex(i,
            Vec3d(vertices[vertexIndex], vertices[vertexIndex + 1], vertices[vertexIndex + 2]),
            Color(255, 0, 0), // White color for simplicity
            Vec2d(texCoords[texCoordIndex], texCoords[texCoordIndex + 1]));
    }

    buff.setIndexes({0, 1, 2, 2, 3, 0,       // Front
                     4, 5, 6, 6, 7, 4,       // Back
                     8, 9, 10, 10, 11, 8,    // Left
                     12, 13, 14, 14, 15, 12, // Right
                     16, 17, 18, 18, 19, 16, // Top
                     20, 21, 22, 22, 23, 20  // Bottom
                    });
    buff.writeIndexes();
    buff.write(va);
}

#endif // TESTS_CUBE3D_HPP
