#include "stdafx.h"
#include "SettingsObj.h"
#include "boost\algorithm\string.hpp"

SettingsObj& SettingsObj::getInstance()
{
	static SettingsObj instance;
	return instance;
}

void SettingsObj::readFromFile(std::string path)
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
	boost::split(strs, buffer, boost::is_any_of("\t= \n\r"));
	for (std::vector<std::string>::iterator item = strs.begin(); item != strs.end(); ++item)
	{
		if (item->compare(0, 11, "CountTarget") == 0)
		{
			++item;
			_count = std::stoi(*item, nullptr);
			continue;
		}
		if (item->compare(0, 5, "Speed") == 0)
		{
			++item;
			_speed = std::stoi(*item, nullptr);
			continue;
		}
		if (item->compare(0, 4, "Time") == 0)
		{
			++item;
			_time = std::stoi(*item, nullptr);
			continue;
		}
	}
	///std::vector<std::string>().swap(strs);
}
