#include <xenyke/core.hpp>
#include <xenyke/gl.hpp>
#include <xenyke/gl/ext/glm/glm.hpp>

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

    while (window.isOpen()) {

        program.use();
        program.setMat4("model", glm::mat4(1.f));
        program.setMat4("view", glm::mat4(1.f));
        program.setMat4("projection", glm::mat4(1.f));
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
