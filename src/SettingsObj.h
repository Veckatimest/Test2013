#pragma once

class SettingsObj
{
public:
	static SettingsObj& getInstance();

	void readFromFile(std::string path);
	int getCount() { return _count; }
	int getTime() { return _time; }
	int getSpeed() { return _speed; }
private:
	SettingsObj() {};
	SettingsObj(SettingsObj const&) = delete;
	SettingsObj& operator= (SettingsObj const&) = delete;

private:
	int _count = 9;
	int _speed = 200;
	int _time = 25;
};

