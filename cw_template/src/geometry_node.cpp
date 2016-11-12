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

	geometry objectGeom;
	objectGeom.add_buffer(positions, BUFFER_INDEXES::POSITION_BUFFER);
	objectGeom.add_buffer(colours, BUFFER_INDEXES::COLOUR_BUFFER);
	object = mesh(objectGeom);

	SceneNode::update();
}

