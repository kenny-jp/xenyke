#include <xenyke/core.hpp>
#include <xenyke/gl.hpp>
#include <xenyke/gl/ext/glm/mat4x4.hpp>
#include <xenyke/gl/ext/glm/gtc/matrix_transform.hpp>

struct XKE2D;
struct XKE3D;

template<class CameraType_>
class Camera;

template<>
class Camera<XKE2D>
{
public:
    static glm::mat4 getMat(const xke::Vec2u& windowSize, const xke::Vec2f& cameraPos)
    {
        return projection(windowSize) * view(cameraPos);
    }

private:
    static glm::mat4 projection(const xke::Vec2u& size)
    {
        return glm::ortho(0.f, static_cast<float>(size.x),
                          static_cast<float>(size.y), 0.f);
    }

    static glm::mat4 view(const xke::Vec2f& pos)
    {
        static constexpr glm::mat4 identityMat(1.f);
        return glm::translate(identityMat, glm::vec3(pos.x, pos.y, 1.f));
    }
};

template<>
class Camera<XKE3D>
{
public:
    static glm::mat4 getMat(const xke::Vec2u& windowSize, const xke::Vec2f& cameraPos)
    {
        return projection(windowSize) * view(cameraPos);
    }

private:
    static glm::mat4 projection(const xke::Vec2u& size)
    {
        const float aspectRatio {static_cast<float>(size.x) / static_cast<float>(size.y)};
        return glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    }

    static glm::mat4 view(const xke::Vec2f& pos)
    {
        static constexpr glm::vec3 cameraFront = glm::vec3(0.0f, -0.6f, -1.0f);
        static constexpr glm::vec3 cameraUp    = glm::vec3(0.0f, -1.0f,  0.0f);
        glm::vec3 cameraPos(pos.x, pos.y-1.5, -3.f);
        return glm::lookAt(cameraPos, cameraPos - cameraFront, cameraUp);
    }
};

int main()
{
    xke::xkeinit();

    xke::Window window(800, 800, "MyWin");

    xke::ShaderProgram program("../../../data/shaders/shader.glsl");

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

    xke::VertexArray va(36, xke::Primitive::TRIANGLES);

    for (int i = 0; i < 36; ++i) {
        int vertexIndex = i * 3;
        int texCoordIndex = (i % 4) * 2;
        va.setVertex(i,
            xke::Vec3d(vertices[vertexIndex], vertices[vertexIndex + 1], vertices[vertexIndex + 2]),
            xke::Color(255, 0, 0), // White color for simplicity
            xke::Vec2d(texCoords[texCoordIndex], texCoords[texCoordIndex + 1]));
    }

    xke::EVertexBuffer<xke::BufferUsage::STATIC, xke::Primitive::TRIANGLES, 36> buff;
    buff.setIndexes({0, 1, 2,  // Front
                     2, 3, 0,
                     4, 5, 6,  // Back
                     6, 7, 4,
                     8, 9, 10, // Left
                     10, 11, 8,
                     12, 13, 14, // Right
                     14, 15, 12,
                     16, 17, 18, // Top
                     18, 19, 16,
                     20, 21, 22, // Bottom
                     22, 23, 20});
    buff.writeIndexes();
    buff.write(va);


    // xke::EVertexBuffer<xke::BufferUsage::STATIC, xke::Primitive::TRIANGLES, 6> buff;
    // xke::VertexArray vertices(4, xke::Primitive::TRIANGLES);
    // vertices.setVertex(0, xke::Vertex(xke::Vec3d(-0.5, -0.5,  0.0), xke::Color(255, 0, 0), xke::Vec2d(0, 0)));
    // vertices.setVertex(1, xke::Vertex(xke::Vec3d(-0.5,  0.5,  0.0), xke::Color(255, 0, 0), xke::Vec2d(0, 1)));
    // vertices.setVertex(2, xke::Vertex(xke::Vec3d( 0.5,  0.5, 0.0),  xke::Color(255, 0, 0), xke::Vec2d(1, 1)));
    // vertices.setVertex(3, xke::Vertex(xke::Vec3d( 0.5, -0.5, 0.0),  xke::Color(255, 0, 0), xke::Vec2d(1, 0)));

    // buff.setIndexes({0, 1, 2, 0, 2, 3});
    // buff.writeIndexes();
    // buff.write(vertices);

    // xke::Vec2f rectPos {0, 0};
    xke::Vec2f camPos {0.f, 0.f};
    constexpr int rectSize = 1;

    // const glm::vec3 modelTranslation(rectPos.x + rectSize * 0.5, rectPos.y + rectSize * 0.5, 0.f);

    xke::Texture tx;
    tx.loadFromFile("../../../data/textures/box.jpg");


    while (window.isOpen()) {
        // glm::mat4 model_mat = glm::translate(glm::mat4(1.f), modelTranslation);
        // model_mat = glm::scale(model_mat, glm::vec3(rectSize, rectSize, 1.f));

        // glm::mat4 vp_mat = Camera<XKE3D>::getMat(window.getSize(), camPos);

        auto model_mat = glm::scale(glm::mat4(1.f), glm::vec3(rectSize, rectSize, 1.f));
        float angle = glm::radians(45.f);
        // model_mat = glm::rotate(model_mat, angle, glm::vec3(0.f, 1.f, 0.f));
        // auto model_mat = glm::mat4(1.f);
        auto vp_mat = Camera<XKE3D>::getMat(window.getSize(), camPos);

        program.use();
        if (tx.isLoaded()) {
            program.setBool("hasTexture", true);
            tx.use();
        } else {
            program.setBool("hasTexture", false);
        }

        program.setMat4("model", model_mat);
        program.setMat4("vp",    vp_mat);

        window.clear(xke::Color::White);

        buff.draw();
        program.stopUse();

        window.display();
    }

    program.destroy();
    buff.destroy();

    return xke::xkeTerminate();
}
