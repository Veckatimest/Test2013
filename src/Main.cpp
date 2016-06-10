#include "stdafx.h"
#include "TestAppDelegate.h"
#include "boost\algorithm\string.hpp"
#include "boost\property_tree\ptree.hpp"
#include "boost\property_tree\ini_parser.hpp"

#define MYAPPLICATION_NAME "Test"

void getSettingsFromFile(std::string path, int &read, int &write)
{
	IO::InputStreamPtr istr = Core::fileSystem.OpenRead(path);
	istr->Seek(0, IO::Origin::End);
	size_t size = istr->Tell();
	char* buffer = new char[size + 1];
	istr->Seek(0, IO::Origin::Beginning);
	istr->Read(buffer, size + 1);
	istr.detach();
	istr.~intrusive_ptr();
	buffer[size] = '\0';
	std::vector<std::string> strs;
	boost::split(strs, buffer, boost::is_any_of("\t \n\r"));
	for (std::vector<std::string>::iterator item = strs.begin(); item != strs.end(); ++item)
	{
		if (item->compare(0, 4, "Read") == 0)
		{
			++item;
			read = std::stoi(*item, nullptr);
			continue;
		}
		if (item->compare(0, 5, "Write") == 0)
		{
			++item;
			read = std::stoi(*item, nullptr);
			continue;
		}
	}

	std::vector<std::string>().swap(strs);
	//empty.swap(strs);
	strs.clear();
	strs.shrink_to_fit();

}

void getSettingsFromIniFile(std::string path, int &read, int &write)
{
	boost::property_tree::ptree pt;
	boost::property_tree::ini_parser::read_ini(path + ".ini", pt);
	read = pt.get<int>("Read");
	write = std::stoi(pt.get<std::string>("Write"));
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int readparam, writeparam;
	getSettingsFromIniFile("myconf", readparam, writeparam);
	ParticleSystem::SetTexturesPath("textures/Particles");

	Core::fileSystem.SetWriteDirectory("./write_directory");
	Core::fileSystem.MountDirectory("base_p");

	Log::log.AddSink(new Log::HtmlFileLogSink("log.htm", true));

	Core::Application::APPLICATION_NAME = MYAPPLICATION_NAME;

	Core::RunApplicationWithDelegate(new TestAppDelegate());
	
	return 0;
}
