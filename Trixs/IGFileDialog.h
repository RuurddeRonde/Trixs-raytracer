#pragma once
#include "imgui.h"



#include <vector>
#include <string>
#include <experimental/filesystem>
#include <filesystem>

// With Visual Studio compiler, filesystem is still "experimental"
namespace Trixs
{

	namespace fs = std::experimental::filesystem;

	static constexpr int modal_flags =
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoScrollbar |
		ImGuiWindowFlags_AlwaysAutoResize;
	namespace imgui_ext {

		const struct file {
			std::string alias;
			fs::path path;
		};

		class file_browser_modal final {

			static const int modal_flags =
				ImGuiWindowFlags_NoResize |
				ImGuiWindowFlags_NoCollapse |
				ImGuiWindowFlags_NoScrollbar |
				ImGuiWindowFlags_AlwaysAutoResize;;

			const char* m_title;

			bool m_oldVisibility;

			int m_selection;

			fs::path m_currentPath;
			bool m_currentPathIsDir;

			std::vector<file> m_filesInScope;

		public:

			file_browser_modal(const char* title);

			const bool render(const bool isVisible, std::string& outPath);

		};

	};
}

