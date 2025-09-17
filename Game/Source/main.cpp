#include <Cardboard.hpp>

int main()
{
	Cardboard::ApplicationSpec spec;
	spec.WindowName = "Game";
	spec.WindowHeight = 1920;
	spec.WindowWidth = 1080;

	Cardboard::Application app(spec);
	app.Run();
}