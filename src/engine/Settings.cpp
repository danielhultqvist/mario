#include "Settings.h"
#include <fstream>
#include <string>
#include "../helpers/StringUtils.h"
#include <iostream>

std::string MUSIC_SETTING = "MUSIC_LEVEL";
const std::string EFFECTS_LEVEL = "EFFECTS_LEVEL";
const std::string SUBTITLES = "SUBTITLES";

Settings::Settings()
{
	setDefaultValues();
}

Settings::~Settings()
{
	
}

void Settings::setDefaultValues()
{
	m_musicLevel = 5;
	m_effectsLevel = 5;
	m_subtitles = true;
}

void Settings::loadSettings()
{
	std::string line;
	std::ifstream fileStream("settings.txt");
	if(fileStream.is_open())
	{
		while(getline(fileStream, line))
		{
			if (StringUtils::startsWith(line, MUSIC_SETTING))
			{
				std::cout << "MUUUSIC!";
			}
			else if (StringUtils::startsWith(line, EFFECTS_LEVEL))
			{
				std::cout << "SOUND EFFECTS LEVEL";
			}
			else if (StringUtils::startsWith(line, SUBTITLES))
			{
				std::cout << "SUBTITLES!";
			}
		}
		fileStream.close();
	}
}

void Settings::saveSettings()
{
	
}