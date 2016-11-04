#pragma once
#include "scene_node.h"
#include <glm/glm.hpp>
#include <graphics_framework.h>

using namespace graphics_framework;
using namespace glm;

class GeometryNode : public SceneNode
{
public:
	GeometryNode() {}
	~GeometryNode() {}
	void update(vector<vec3> positions, vector<vec4> colours);
};