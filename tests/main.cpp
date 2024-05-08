// #include <xenyke/core.hpp>
// #include <xenyke/gl.hpp>
// #include <xenyke/eng/camera.hpp>
// #include <xenyke/core/bitset.hpp>
// #include <xenyke/logger/debug.hpp>
#include <xenyke/core/debug.hpp>

int main()
{
    bool b = true;
    float pi = 3.1415886980;
    xkeDebug() << xke::boolalpha << b << "\n"
               << xke::noboolalpha << b << "\n"
               << pi << "\n";
    // xkeDebug("Bonjour moi j'ai {} ans", age) << " Hahaha";

    return 0;

    // xke::xkeinit();
    // std::cout << std::fixed << std::numeric_limits<float>::max() << std::endl;

    // xke::Bitset b2(4);
    // b2.set(0, true);
    // // b2.set(1, true);
    // b2.set(2, true);
    // b1.print();
    // b2.print();

    // b1 &= b2;
    // b1.print();

    // auto b3 = b1 & b2;
    // b3.print();

    // auto b4 = b1 | b2;
    // b4.print();

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

    // return xke::xkeTerminate();
}
