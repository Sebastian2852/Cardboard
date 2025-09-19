#include "glad/glad.h"
#include <Cardboard.hpp>

#include<iostream>

#include "ChessBoardLayer.hpp"

class TestLayer : public Cardboard::Layer
{
public:
    TestLayer()
        : Layer("Test Layer"),
        m_v1(0.25f, 0.75f, 0.0f),
        m_v2(0.75f, 0.75f, 0.0f),
        m_v3(0.5f, 0.25f, 0.0f),
        m_Triangle(m_v1, m_v2, m_v3, Cardboard::Vector3(1, 0, 0))
    {
        LOG_TRACE("Created testing layer");
    }

    virtual void OnUpdate(float deltaTime) override
    {
        m_v1.y += 0.01f * deltaTime;
        m_v2.y += 0.01f * deltaTime;
        m_v3.y += 0.01f * deltaTime;

        m_Triangle.UpdateVertexPositions(m_v1, m_v2, m_v3);
    }

    virtual void OnRender() override
    {
        m_Triangle.Render();
    }

    virtual bool OnEvent(Cardboard::BaseEvent& event)
    {
        CARDBOARD_WARN(event.ToString());
        return true;
    }

private:
    Cardboard::Vector3 m_v1, m_v2, m_v3;
    Cardboard::Triangle m_Triangle;
};

int main()
{
	Cardboard::ApplicationSpec spec;
	spec.WindowName = "Game";
	spec.WindowWidth = 500;
	spec.WindowHeight = 500;

	Cardboard::Application app(spec);
	app.PushLayer<ChessBoardLayer>();
	app.PushLayer<TestLayer>();
	app.Run();
}