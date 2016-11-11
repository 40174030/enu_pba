#pragma once
#include "scene_node.h"
#include "geometry_node.h"

class TransformNode : public SceneNode
{
private:
	vec3 translation;
	vec3 scale;
	vec3 rotation;

public:
	TransformNode()
	{
		translation = vec3(0.0f);
		scale = vec3(1.0f);
		rotation = vec3(0.0f);
	}
	
	TransformNode(vec3 t, vec3 s, vec3 r)
	{
		translation = t;		
		scale = s;		
		rotation = r;
	}

	~TransformNode() {}

	void update();
};