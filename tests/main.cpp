#include <xenyke/gl/init.hpp>
#include <xenyke/gl/shader_program.hpp>
#include <xenyke/gl/texture.hpp>
#include <xenyke/gl/vertex_buffer.hpp>
#include <xenyke/gl/window.hpp>

#include <xenyke/gl/ext/glm/gtc/matrix_transform.hpp>

int main()
{
    using namespace xke;

    xkeinit();

    Window window(800, 800, "MyWin");

    ShaderProgram program("../../../data/shaders/shader.glsl");


    xke::EVertexBuffer<xke::BufferUsage::STATIC, xke::Primitive::LINES, 6> buff;
    xke::VertexArray vertices(4, xke::Primitive::TRIANGLES);
    vertices.setVertex(0, xke::Vertex(xke::Vec3d(-0.5, -0.5,  0.0), xke::Color::Red, xke::Vec2d(0, 0)));
    vertices.setVertex(1, xke::Vertex(xke::Vec3d(-0.5,  0.5,  0.0), xke::Color::Red, xke::Vec2d(0, 1)));
    vertices.setVertex(2, xke::Vertex(xke::Vec3d( 0.5,  0.5, 0.0),  xke::Color::Red, xke::Vec2d(1, 1)));
    vertices.setVertex(3, xke::Vertex(xke::Vec3d( 0.5, -0.5, 0.0),  xke::Color::Red, xke::Vec2d(1, 0)));

    buff.setIndexes({0, 1, 2, 0, 2, 3});
    buff.writeIndexes();
    buff.write(vertices);

    program.use();
    program.setBool("hasTexture", false);
    program.setMat4("mvp", glm::mat4(1.f));


    while(window.isOpen()) {
        window.clear(Color::Black);

        buff.draw();

        window.display();
    }



    return xkeTerminate();
}
