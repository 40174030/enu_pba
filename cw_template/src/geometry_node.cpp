#define GLM_ENABLE_EXPERIMENTAL

#include "geometry_node.h"

void GeometryNode::update()
{
	if (this->parent != nullptr)
	{
		setNodeTransform(this->parent->getNodeTransform());
	}
	else
	{
		setNodeTransform(mat4(1.0f));
	}

	SceneNode::update();
}

