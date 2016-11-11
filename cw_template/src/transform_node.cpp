#include "transform_node.h"

void TransformNode::update()
{
	mesh objectCopy;

	objectCopy.get_transform().translate(translation);
	objectCopy.get_transform().scale *= scale;
	objectCopy.get_transform().rotate(rotation);

	currentTransform = objectCopy.get_transform().get_transform_matrix();
	this->parent->setCurrentTransform(currentTransform);

	SceneNode::update();
}
