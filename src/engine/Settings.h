#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
public:
	Settings();
	~Settings();

	void loadSettings();
	void saveSettings();

private:
	int m_musicLevel, m_effectsLevel;
	bool m_subtitles;

	void setDefaultValues();
};

#endif SETTINGS_H