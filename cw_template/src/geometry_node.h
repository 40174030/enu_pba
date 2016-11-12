#pragma once
#include "scene_node.h"

class GeometryNode : public SceneNode
{
private:
	vector<vec3> positions;
	vector<vec4> colours;

public:
	GeometryNode(vector<vec3> p, vector<vec4> c) 
	{
		positions = p;
		colours = c;
	}
	~GeometryNode() {}
	void update();
};