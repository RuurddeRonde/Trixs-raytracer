#pragma once
#include "Ray.h"
#include "KeyFrame.h"
#include <vector>
namespace Trixs
{

	class Material;
	struct hitRecord
	{
		float t;
		vec3 p;
		vec3 normal;
		Material* matPtr;
	};

	class Hittable
	{
	public:
		Hittable()
		{
			keyframes = std::vector<KeyFrame>();
			keyframes.push_back(KeyFrame(Transform(vec3(0.1f, 0.1f, 0.1f), vec3(0.1f, 0.1f, 0.1f), vec3(0.1f, 0.1f, 0.1f))));

		}
		virtual bool hit(const Ray& r, float t_min, float t_max, hitRecord& rec) const = 0;
		virtual std::string getWritable() { return ""; }
		virtual void draw()const {}
		Transform* getTransform()
		{
			return keyframes.at(0).getTransformPtr();
		}
		Transform* getTransform(int frame)
		{
			if (keyframes.size() == 1) //only 1 transform
			{
				return keyframes.at(0).getTransformPtr();
			}
			else//more than 1
			{
				//find closest keyframes
				int closestSmallest = INT_MAX;
				int closestHighest = -1;
				int prevselection = 0;
				int nextselection = 0;
				for (size_t i = 0; i < keyframes.size(); i++)
				{
					int distance = frame - keyframes.at(i).getFrame();
					if (distance < closestSmallest)
					{
						closestSmallest = distance;
						prevselection = i;
					}
					else if (distance > closestHighest)
					{
						closestHighest = distance;
						nextselection = i;
					}
				}
				//get transform
				if (prevselection != nextselection && closestSmallest != INT_MAX && closestHighest != -1)//between
				{
					//interpolate
					return&(keyframes.at(prevselection).getTransform(keyframes.at(nextselection), frame));
				}
				else if (closestSmallest == INT_MAX && closestHighest != -1)//only 1 after
				{
					return keyframes.at(nextselection).getTransformPtr();
				}
				else if (closestSmallest != INT_MAX && closestHighest == -1)//only 1 before
				{
					return keyframes.at(prevselection).getTransformPtr();
				}
			}
		}
		Material* getMaterial() { return matPtr; }
		bool addKeyFrame(Transform t, int frame)
		{
			for (auto i = 0; i < keyframes.size(); i++)
			{
				if (keyframes.at(i).getFrame() == frame)
				{
					keyframes.at(i).setTransform(t);
					return true;
				}
			}
			keyframes.push_back(KeyFrame(t, frame));
			return true;
		}
		//only use this function on creation of object
		void setStartTransform(Transform t)
		{
			keyframes[0].setTransform(t);
		}
	protected:
		Material* matPtr;
	private:
		std::vector<KeyFrame> keyframes;
	};
}