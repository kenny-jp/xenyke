# include <xenyke/eng/camera.hpp>

# include <xenyke/gl/init.hpp>
# include <xenyke/gl/window.hpp>
# include <xenyke/gl/shader_program.hpp>
# include <xenyke/gl/vertex_array.hpp>
# include <xenyke/gl/vertex_buffer.hpp>
# include <xenyke/gl/texture.hpp>

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

    xke::Vec2f camPos {0.f, 0.f};
    xke::Transform rectTr;
    rectTr.size = {50, 50};
    rectTr.position = {50, 50, 0};

    xke::Texture tx;
    // tx.loadFromFile("../../../data/textures/box.jpg");

    while (window.isOpen()) {
        program.use();
        if (tx.isLoaded()) {
            program.setBool("hasTexture", true);
            tx.use();
        } else {
            program.setBool("hasTexture", false);
        }

        const xke::Vec2u windowSize = window.getSize();
        const glm::mat4 mvp = xke::Camera<xke::CameraType2D>::mvpMat(windowSize, camPos, rectTr);
        program.setMat4("mvp", mvp);

        window.clear(xke::Color::White);

        buff.draw();
        program.stopUse();

        window.display();
    }

    program.destroy();
    buff.destroy();

    return xke::xkeTerminate();
}
