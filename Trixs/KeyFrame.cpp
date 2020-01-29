#pragma once
#include "KeyFrame.h"

namespace Trixs
{
	KeyFrame::KeyFrame(vec3 pos, vec3 rot, vec3 scale)
	{
		t = Transform(pos, rot, scale);
		frame = 0;
	}
	KeyFrame::KeyFrame(Transform t)
	{
		this->t = t;
		frame = 0;
	}
	KeyFrame::KeyFrame(vec3 pos, vec3 rot, vec3 scale, int frame)
	{
		t = Transform(pos, rot, scale);
		this->frame = frame;
	}
	KeyFrame::KeyFrame(Transform t, int frame)
	{
		this->t = t;
		this->frame = frame;
	}
	void KeyFrame::setTransform(Transform t)
	{
		this->t = t;
	}
	void KeyFrame::setTransform(vec3 pos, vec3 rot, vec3 scale)
	{
		this->t = Transform(pos, rot, scale);
	}
	void KeyFrame::reset()
	{
		this->t = Transform();
		frame = 0;
	}
	void KeyFrame::setFrame(int frame)
	{
		this->frame = frame;
	}
	//calculates transform between two keyframes
	//only liniar for now
	Transform KeyFrame::getTransform(KeyFrame& other, int frame)
	{
		vec3 newPos = vec3(
			getInterpolatedFloat(t.getPos().x(), other.getTransform().getPos().x(), this->frame - other.getFrame(),frame),
			getInterpolatedFloat(t.getPos().y(), other.getTransform().getPos().y(), this->frame - other.getFrame(), frame),
			getInterpolatedFloat(t.getPos().z(), other.getTransform().getPos().z(), this->frame - other.getFrame(), frame));
		vec3 newRot = vec3(
			getInterpolatedFloat(t.getRot().x(), other.getTransform().getRot().x(), this->frame - other.getFrame(), frame),
			getInterpolatedFloat(t.getRot().y(), other.getTransform().getRot().y(), this->frame - other.getFrame(), frame),
			getInterpolatedFloat(t.getRot().z(), other.getTransform().getRot().z(), this->frame - other.getFrame(), frame));
		vec3 newScale = vec3(
			getInterpolatedFloat(t.getScale().x(), other.getTransform().getScale().x(), this->frame - other.getFrame(), frame),
			getInterpolatedFloat(t.getScale().y(), other.getTransform().getScale().y(), this->frame - other.getFrame(), frame),
			getInterpolatedFloat(t.getScale().z(), other.getTransform().getScale().z(), this->frame - other.getFrame(), frame));

		return Transform(newPos, newRot, newScale);
	}
	Transform KeyFrame::getTransform()
	{
		return t;
	}
	Transform* KeyFrame::getTransformPtr()
	{
		return &t;
	}
	int KeyFrame::getFrame()
	{
		return frame;
	}

	float KeyFrame::linearInterpolate(float xOne, float xTwo, float frames)
	{
		float diff = xTwo - xOne;
		return diff / frames;
	}

	float KeyFrame::getInterpolatedFloat(float xOne, float xTwo, int maxFrames, int frame)
	{
		float dist = linearInterpolate(xOne, xTwo, maxFrames);
		return dist * frame;
	}
}