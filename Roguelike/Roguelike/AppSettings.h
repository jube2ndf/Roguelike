#pragma once
#include <string>

namespace Settings {
	class AppSettings {
	private:
		AppSettings() = default;

	public:
		static AppSettings& Instance() {
			static AppSettings appSettings;
			return appSettings;
		}

		//Resourse path
		const std::string RESOURCES_PATH = "";

		// Window screen settings
		const int WINDOW_HEIGTH = 600;
		const int WINDOW_WIDTH = 800;
		const float TIME_PER_FRAME = 1.f / 60.f;

	};
}

#define SETTINGS AppSettings::Instance();