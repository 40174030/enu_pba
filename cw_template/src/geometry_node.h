#pragma once
#include "scene_node.h"

class GeometryNode : public SceneNode
{
private:
	vector<vec3> positions;
	vector<vec4> colours;
	effect eff;

public:
	GeometryNode(vector<vec3> p, vector<vec4> c, effect e) 
	{
		positions = p;
		colours = c;
		eff = e;
	}
	~GeometryNode() {}
	void update();
};