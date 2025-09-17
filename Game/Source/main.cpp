#include <Cardboard.hpp>

int main()
{
	Cardboard::ApplicationSpec spec;
	spec.WindowName = "Game";
	spec.WindowWidth = 1920;
	spec.WindowHeight = 1080;

	Cardboard::Application app(spec);
	app.Run();
}