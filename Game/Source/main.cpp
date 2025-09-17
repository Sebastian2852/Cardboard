#include <Cardboard.hpp>

#include <iostream>

class TestLayer : public Cardboard::Layer
{
public:
	TestLayer()
	{
		//std::cout << "Created Layer" << std::endl;
		LOG_TRACE("Created testing layer");
	}

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
	}

private:
	std::string m_DebugName = "Testing Layer";
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