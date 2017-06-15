//Programmed by Thishan D Pathmanathan
//Last Modified: N/A

#include "display.h"
#include <iostream>
#include <GL/glew.h>
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

using namespace std;

int main(int argc, char **argv)
{
	
	Display display(800, 600, "thishandp7");
	Vertex vertices[] = { Vertex(glm::vec3(-1, 1, 0), glm::vec2(0.0, 0.0)),
						  Vertex(glm::vec3(1, 1, 0), glm::vec2(0.5, 1.0)),
						  Vertex(glm::vec3(1, -1, 0), glm::vec2(1.0, 0.0)) };

	unsigned int indices[] = {0, 1, 2};

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Mesh mesh2("./res/drone5.obj");
	Shader shader("./res/basicShader");
	Texture texture("./res/mainUV.jpg");

	Camera camera(vec3(0, 0.3f, -1.5f), 70.0f, ((float)800 / (float)600), 0.001f, 1000.0f);

	Transform transform;

	float counter = 0.0f;

	cout << "Physics engine_ Test_v08" << endl;

	while (!display.isClosed())
	{
		display.Clear(0.5f, 0.5f, 0.5f, 1.0f);

		//transform.GetRot().x = sinf(counter);
		transform.GetRot().y = counter;
		//transform.GetRot().z = cosf(counter);
		//transform.GetScale().x = 0.75f;
		//transform.GetScale().y = 0.75f;
		//transform.GetScale().z = 0.75f;
		//transform.GetPos().x = sinf(counter);

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh.Draw();
		mesh2.Draw();

		display.Update();

		counter += 0.0005f;

	}
	//system("pause");
	return 0;
}