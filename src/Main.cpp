#include "stdafx.h"
#include "TestAppDelegate.h"
#include "SettingsObj.h"
#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\ini_parser.hpp"

#define MYAPPLICATION_NAME "Test"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	std::srand(std::time_t(NULL));
	int CountTarget, Speed, Time;

	SettingsObj& set = SettingsObj::getInstance();
	set.readFromFile("input.txt");

	ParticleSystem::SetTexturesPath("textures/Particles");

	Core::fileSystem.SetWriteDirectory("./write_directory");
	Core::fileSystem.MountDirectory("base_p");

	Log::log.AddSink(new Log::HtmlFileLogSink("log.htm", true));

	Core::Application::APPLICATION_NAME = MYAPPLICATION_NAME;

	Core::RunApplicationWithDelegate(new TestAppDelegate());
	
	return 0;
}
