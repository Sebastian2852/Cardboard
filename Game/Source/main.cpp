#include "glad/glad.h"
#include <Cardboard.hpp>

#include<iostream>

class TestLayer : public Cardboard::Layer
{
public:
	TestLayer()
	{
		//std::cout << "Created Layer" << std::endl;
		LOG_TRACE("Created testing layer");

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float verticies[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indicies[3] = {
			0, 1, 2
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

		std::string vertexSource = R"(
			#version 460 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 o_Position;

			void main()
			{
				gl_Position = vec4(a_Position, 1.0);
				o_Position = a_Position;
			}
		)";

		std::string fragmentSource = R"(
			#version 460 core
			
			layout(location = 0) out vec4 color;

			in vec3 o_Position;

			void main()
			{
				color = vec4(o_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Cardboard::Shader(vertexSource, fragmentSource));
	};

	virtual ~TestLayer()
	{
		//std::cout << "Destroyed Layer" << std::endl;
	}

	virtual void OnUpdate(float deltaTime) override
	{
		//std::cout << "On update (delta time = " << deltaTime << ")" << std::endl;
	}

	virtual void OnRender() override
	{
		//std::cout << "On Render" << std::endl;

		m_Shader->Bind();
		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
	}

private:
	std::string m_DebugName = "Testing Layer";

	unsigned int m_VertexArray;
	unsigned int m_VertexBuffer;
	unsigned int m_IndexBuffer;
	std::unique_ptr<Cardboard::Shader> m_Shader;
};

int main()
{
	Cardboard::ApplicationSpec spec;
	spec.WindowName = "Game";
	spec.WindowWidth = 1920;
	spec.WindowHeight = 1080;

	Cardboard::Application app(spec);
	app.PushLayer<TestLayer>();
	app.Run();
}