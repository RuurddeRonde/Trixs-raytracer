#pragma once
#include "Transform.h"
namespace Trixs
{
	class KeyFrame
	{
	public:
		KeyFrame(vec3 pos, vec3 rot, vec3 scale);
		KeyFrame(Transform t);
		KeyFrame(vec3 pos, vec3 rot, vec3 scale, int frame);
		KeyFrame(Transform t, int frame);
		void setTransform(Transform t);
		void setTransform(vec3 pos, vec3 rot, vec3 scale);
		void reset();
		void setFrame(int frame);
		//calculates transform between two keyframes
		Transform getTransform(KeyFrame& other, int frame);
		Transform getTransform();
		Transform* getTransformPtr();
		int getFrame();
	private:
		Transform t;
		int frame;
		//returns a per frame delta linearly between x amount of frames
		float linearInterpolate(float xOne, float xTwo, float frames);
		float getInterpolatedFloat(float xOne, float xTwo, int maxFrames, int frame);
	};
}