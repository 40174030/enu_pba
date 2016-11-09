#include "transform_node.h"

void TransformNode::update()
{
	object = this->parent->getNodeObject();
	object.get_transform().translate(translation);
	object.get_transform().scale *= scale;
	object.get_transform().rotate(rotation);

	renderNode(object, eff);

	SceneNode::update();
}
