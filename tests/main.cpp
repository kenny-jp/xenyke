#include <xenyke/core.hpp>
#include <xenyke/gl.hpp>
#include <xenyke/eng/camera.hpp>
#include <xenyke/core/bitset.hpp>

int main()
{
    xke::xkeinit();

    xke::Bitset b1(8);
    b1.set(4, true);
    b1.set(7, true);
    xke::Bitset b2(8);
    b2.set(0, true);
    b2.set(2, true);
    b2.set(3, true);
    b1.print();
    b2.print();

    b1 |= b2;
    b1.print();

    // xke::Window window(800, 800, "MyWin");

    // xke::ShaderProgram program("../../../data/shaders/shader.glsl");

    // xke::EVertexBuffer<xke::BufferUsage::STATIC, xke::Primitive::TRIANGLES, 6> buff;
    // xke::VertexArray vertices(4, xke::Primitive::TRIANGLES);
    // vertices.setVertex(0, xke::Vertex(xke::Vec3d(-0.5, -0.5,  0.0), xke::Color(255, 0, 0), xke::Vec2d(0, 0)));
    // vertices.setVertex(1, xke::Vertex(xke::Vec3d(-0.5,  0.5,  0.0), xke::Color(255, 0, 0), xke::Vec2d(0, 1)));
    // vertices.setVertex(2, xke::Vertex(xke::Vec3d( 0.5,  0.5, 0.0),  xke::Color(255, 0, 0), xke::Vec2d(1, 1)));
    // vertices.setVertex(3, xke::Vertex(xke::Vec3d( 0.5, -0.5, 0.0),  xke::Color(255, 0, 0), xke::Vec2d(1, 0)));

    // buff.setIndexes({0, 1, 2, 0, 2, 3});
    // buff.writeIndexes();
    // buff.write(vertices);

    // xke::Vec2f camPos {0.f, 0.f};
    // xke::Transform rectTr;
    // rectTr.size = {25, 52};
    // rectTr.position = {0, 0, 0};

    // xke::Texture tx;
    // // tx.loadFromFile("../../../data/textures/box.jpg");

    // while (window.isOpen()) {
    //     program.use();
    //     if (tx.isLoaded()) {
    //         program.setBool("hasTexture", true);
    //         tx.use();
    //     } else {
    //         program.setBool("hasTexture", false);
    //     }

    //     const xke::Vec2u windowSize = window.getSize();
    //     const glm::mat4 mvp = xke::Camera<xke::CameraType2D>::mvpMat(windowSize, camPos, rectTr);
    //     program.setMat4("mvp", mvp);

    //     window.clear(xke::Color::White);

    //     buff.draw();
    //     program.stopUse();

    //     window.display();
    // }

    // program.destroy();
    // buff.destroy();

    return xke::xkeTerminate();
}
