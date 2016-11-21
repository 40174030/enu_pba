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

		geometry objectGeom;
		objectGeom.add_buffer(positions, BUFFER_INDEXES::POSITION_BUFFER);
		objectGeom.add_buffer(colours, BUFFER_INDEXES::COLOUR_BUFFER);
		object = mesh(objectGeom);
	}
	~GeometryNode() {}
	void update();
};