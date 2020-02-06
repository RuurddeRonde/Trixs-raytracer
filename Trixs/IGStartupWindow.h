#pragma once
#include "ImGuiWindow.h"
#include "MainManager.h"
namespace Trixs
{

	class IGStartupWindow : public ImGuiWindow
	{
	public:
		bool begin(std::string name) override;
		void update() override;
	private:
		bool newprojectPressed = false;

		void showStart();
		void showNew();
	};

}