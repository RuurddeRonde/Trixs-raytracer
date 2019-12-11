#pragma once
#include "RenderManager.h"
#include "UIManager.h"
namespace Trixs
{
	class MainManager
	{

	public:
		MainManager();
		void run();
		~MainManager();
	private:
		RenderManager* renderManager;
		UIManager* uiManager;
	};

}