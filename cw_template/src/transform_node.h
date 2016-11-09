#pragma once
#include "scene_node.h"

class TransformNode : public SceneNode
{
private:
	vec3 translation;
	vec3 scale;
	vec3 rotation;
	effect eff;

public:
	TransformNode(vec3 t, vec3 s, vec3 r, effect e)
	{
		translation = t;		
		scale = s;		
		rotation = r;
		eff = e;
	}

	~TransformNode() {}

	void update();
};