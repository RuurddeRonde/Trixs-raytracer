#pragma once
#include "ImGuiWindow.h"
struct MySequence;
namespace Trixs
{
	class IGTimeLineWindow : public ImGuiWindow
	{
	public:
		IGTimeLineWindow();
		void update() override;
		bool begin(std::string name) override;
	private:
		MySequence* mySequence;
		int selectedEntry = -1;
		int firstFrame = 0; //todo move to scene
		bool expanded = true;
		int currentFrame = 100; //todo move to scene
	};

}
