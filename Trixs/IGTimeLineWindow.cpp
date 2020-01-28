#include "IGTimeLineWindow.h"
#include "imGuizmoHelperFile.h"

namespace Trixs
{
	IGTimeLineWindow::IGTimeLineWindow()
	{
		mySequence = new MySequence();
		mySequence->mFrameMin = 0;
		mySequence->mFrameMax = 100;
		mySequence->myItems.push_back(MySequence::MySequenceItem{ 0, 10, 30, false });
		mySequence->myItems.push_back(MySequence::MySequenceItem{ 1, 20, 30, false });
		mySequence->myItems.push_back(MySequence::MySequenceItem{ 1, 12, 60, false });
		mySequence->myItems.push_back(MySequence::MySequenceItem{ 1, 61, 90, false });
		mySequence->myItems.push_back(MySequence::MySequenceItem{ 1, 90, 99, false });
	}

	bool IGTimeLineWindow::begin(std::string name)
	{
		return ImGui::Begin(name.c_str(), &show, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	}

	void IGTimeLineWindow::update()
	{
		if (!begin("timeline"))
		{
			end();
		}
		else
		{
			ImGui::PushItemWidth(130);
			ImGui::InputInt("Frame Min", &mySequence->mFrameMin);
			ImGui::SameLine();
			ImGui::InputInt("Frame ", &currentFrame);
			ImGui::SameLine();
			ImGui::InputInt("Frame Max", &mySequence->mFrameMax);
			ImGui::PopItemWidth();
			Sequencer(mySequence, &currentFrame, &expanded, &selectedEntry, &firstFrame, ImSequencer::SEQUENCER_EDIT_STARTEND | ImSequencer::SEQUENCER_ADD | ImSequencer::SEQUENCER_DEL | ImSequencer::SEQUENCER_COPYPASTE | ImSequencer::SEQUENCER_CHANGE_FRAME);
			// add a UI to edit that particular item
			if (selectedEntry != -1)
			{
				const MySequence::MySequenceItem &item = mySequence->myItems[selectedEntry];
				ImGui::Text("I am a %s, please edit me", SequencerItemTypeNames[item.mType]);
				// switch (type) ....
			}

			end();
		}
	}
}