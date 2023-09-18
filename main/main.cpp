#include "LinaMath.h"
#include "LinaGraphics.h"
#define GL_PI 3.1415f
int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
    Lina::Graphics::Shapes::Icosphere ico(0.2f);
    Lina::Events Dispatcher d;
    ico.subdivide(3);
	Lina::Graphics::Window mainWindow("Lina Graphics Window", 720, 720);
    Lina::Graphics::Renderer renderer;
    renderer.enableBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    const std::vector<float>vertices2 = ico.getFullVertex();
    const std::vector<unsigned int>indices3 = ico.getIndices();
	Lina::Graphics::VertexArray va;
    Lina::Graphics::Texture myTex("../Assets/Universe/SolarSystem/2k_earth_daymap.jpg", true);
	Lina::Graphics::VertexBufferLayout layout;
	Lina::Graphics::VertexBuffer vb(&vertices2[0], vertices2.size() * sizeof(vertices2[0]));
    Lina::Graphics::IndexBuffer ib(&indices3[0], indices3.size() * sizeof(indices3[0]));
	Lina::Graphics::Shader shader("../Graphics/shaders/basic.shader");
	layout.push<float>(3);
	layout.push<float>(2);
	shader.bind();
	vb.bind();
	va.addBuffer(vb, layout);
	va.bind();
    ib.bind();
    myTex.bind();
	Lina::Graphics::clearGL();
    float red = 0.0f;
    float count = 0.01f;
    float speed = 0.25f;
    float theta = 0;
    Lina::Matrix3D rotMat;
    Lina::Transform4D fullRotMat;
    renderer.enableCulling();
    renderer.setFrontFace(GL_CCW);
    Lina::Graphics::IndexedDrawingSpecifications ispec;
    ispec.primitive = GL_TRIANGLES;
    ispec.size = indices3.size();
    ispec.dataType = GL_UNSIGNED_INT;
    ispec.dataPointer = nullptr;
	while (!mainWindow.closed())
	{
		mainWindow.clear();
        vb.bind();
        va.bind();
        shader.bind();
        ib.bind();
        myTex.bind();
         rotMat = Lina::MathUtil::rotationMatrix(theta, Lina::Vector3D(0.0,1.0,0).normalise())
                    * Lina::MathUtil::rotationMatrix(3.14159, Lina::MathUtil::zAxis());
        fullRotMat = Lina::MathUtil::transMatrix(rotMat, Lina::Vector3D(0,0,0));
        shader.setUniformMat4("rotationMat", fullRotMat);
        if (red >= 1.0f || red < 0.0f)
            count = -count;
        red += count;
        theta+=0.05f * speed;
	    renderer.drawIndexed(ispec);

		mainWindow.update();
	}
	return 0;
}
