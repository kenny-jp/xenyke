// #include <xenyke/gl/init.hpp>
// #include <xenyke/gl/shader_program.hpp>
// #include <xenyke/gl/texture.hpp>
// #include <xenyke/gl/vertex_buffer.hpp>
// #include <xenyke/gl/window.hpp>

// #include <xenyke/gl/ext/glm/gtc/matrix_transform.hpp>

// #include <xenyke/eng/camera.hpp>
// #include <xenyke/eng/transform.hpp>

#include <xenyke/core/debug.hpp>
#include <xenyke/eng/ecs/entity.hpp>

int main()
{
    using namespace xke;
    using namespace xke::ecs;

    xkeDebug() << std::is_trivial<Entity>::value << xke::flush;

    uint32_t n(0);

    // n |= (1 << 0);
    // n |= (1 << 1);
    n |= (1 << 2);
    n ^= (1 << 2);
    // n |= (1 << 3);
    // n |= 3;

    xkeDebug() << "n value: " << n << xke::endl;

    return 0;


    {
        // xkeinit();

        // Window window(800, 800, "MyWin");

        // ShaderProgram program("../../../data/shaders/shader.glsl");


        // xke::EVertexBuffer<xke::BufferUsage::STATIC, xke::Primitive::TRIANGLES, 6> buff;
        // xke::VertexArray vertices(4, xke::Primitive::TRIANGLES);
        // vertices.setVertex(0, xke::Vertex(xke::Vec3d(-0.5, -0.5,  0.0), xke::Color::Red, xke::Vec2d(0, 0)));
        // vertices.setVertex(1, xke::Vertex(xke::Vec3d(-0.5,  0.5,  0.0), xke::Color::Red, xke::Vec2d(0, 1)));
        // vertices.setVertex(2, xke::Vertex(xke::Vec3d( 0.5,  0.5, 0.0),  xke::Color::Red, xke::Vec2d(1, 1)));
        // vertices.setVertex(3, xke::Vertex(xke::Vec3d( 0.5, -0.5, 0.0),  xke::Color::Red, xke::Vec2d(1, 0)));

        // buff.setIndexes({0, 1, 2, 0, 2, 3});
        // buff.writeIndexes();
        // buff.write(vertices);

        // Transform tr;
        // tr.size = {50, 50};
        // tr.position = {100,0,0};
        // Camera2D camera;
        // Vec2f cameraPos;


        // program.use();
        // program.setBool("hasTexture", false);

        // while(window.isOpen()) {
        //     program.setMat4("mvp", camera.mvpMat(window.getSize(), cameraPos, tr));

        //     window.clear(Color::Black);

        //     buff.draw();

        //     window.display();
        // }

        // program.unuse();

        // program.destroy();
        // buff.destroy();


        // return xkeTerminate();
    }
}
