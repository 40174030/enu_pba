#pragma once
#include "scene_node.h"

class RenderNode : public SceneNode
{
private:
	mat4 currentTransform;
	vec3 translation;
	vec3 scale;
	vec3 rotation;
	effect eff;

public:
	RenderNode(effect e)
	{
		translation = vec3(0.0f);
		scale = vec3(1.0f);
		rotation = vec3(0.0f);
		eff = e;
	}
	RenderNode(vec3 t, vec3 s, vec3 r, effect e)
	{
		translation = t;		
		scale = s;		
		rotation = r;
		eff = e;
	}
	~RenderNode() {}
	void update();
};