#include "geometry_node.h"

void GeometryNode::update(vector<vec3> positions, vector<vec4> colours)
{
	geometry object_geom;

	object_geom.add_buffer(positions, BUFFER_INDEXES::POSITION_BUFFER);
	object_geom.add_buffer(colours, BUFFER_INDEXES::COLOUR_BUFFER);

	

	SceneNode::update();
}
