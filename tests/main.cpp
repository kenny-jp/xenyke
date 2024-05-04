#include <xenyke/core.hpp>
#include <xenyke/gl.hpp>
#include <xenyke/gl/ext/glm/mat4x4.hpp>
#include <xenyke/gl/ext/glm/gtc/matrix_transform.hpp>

class Camera
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

int main()
{
    xke::xkeinit();

    xke::Window window(800, 800, "MyWin");

    xke::ShaderProgram program("../../../data/shaders/shader.glsl");

    xke::EVertexBuffer<xke::BufferUsage::STATIC, xke::Primitive::TRIANGLES, 6> buff;
    xke::VertexArray vertices(4, xke::Primitive::TRIANGLES);
    vertices.setVertex(0, xke::Vertex(xke::Vec3d(-0.5, -0.5,  0.0), xke::Color(255, 0, 0), xke::Vec2d(0, 0)));
    vertices.setVertex(1, xke::Vertex(xke::Vec3d(-0.5,  0.5,  0.0), xke::Color(255, 0, 0), xke::Vec2d(0, 1)));
    vertices.setVertex(2, xke::Vertex(xke::Vec3d( 0.5,  0.5, 0.0),  xke::Color(255, 0, 0), xke::Vec2d(1, 1)));
    vertices.setVertex(3, xke::Vertex(xke::Vec3d( 0.5, -0.5, 0.0),  xke::Color(255, 0, 0), xke::Vec2d(1, 0)));

    buff.setIndexes({0, 1, 2, 0, 2, 3});
    buff.writeIndexes();
    buff.write(vertices);

    xke::Vec2f rectPos {0, 0};
    xke::Vec2f camPos {0.f, 0.f};
    constexpr int rectSize = 100;

    const glm::vec3 modelTranslation(rectPos.x + rectSize * 0.5, rectPos.y + rectSize * 0.5, 0.f);

    glm::mat4 model_mat = glm::translate(glm::mat4(1.f), modelTranslation);
    model_mat = glm::scale(model_mat, glm::vec3(rectSize, rectSize, 1.f));
    glm::mat4 vp_mat = Camera::getMat(window.getSize(), camPos);

    while (window.isOpen()) {
        program.use();
        program.setMat4("model", model_mat);
        program.setMat4("vp",    vp_mat);
        program.setBool("hasTexture", false);

        window.clear(xke::Color::White);

        buff.draw();
        program.stopUse();

        window.display();
    }

    program.destroy();
    buff.destroy();

    return xke::xkeTerminate();
}
