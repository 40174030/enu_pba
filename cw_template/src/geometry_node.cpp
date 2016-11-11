#include "geometry_node.h"

void GeometryNode::update()
{
	geometry object_geom;

	object_geom.add_buffer(positions, BUFFER_INDEXES::POSITION_BUFFER);
	object_geom.add_buffer(colours, BUFFER_INDEXES::COLOUR_BUFFER);
	object = mesh(object_geom);

	if (parent != nullptr)
	{
		currentTransform = parent->getCurrentTransform();
	}
	else
	{
		currentTransform = mat4(1.0f);
	}
	
	SceneNode::update();
}

