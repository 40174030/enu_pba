#define GLM_ENABLE_EXPERIMENTAL

#include "render_node.h"

void RenderNode::update()
{
	object = this->parent->getNodeObject();
	currentTransform = this->parent->getNodeTransform();

	object.get_transform().translate(translation);
	object.get_transform().scale *= scale;
	object.get_transform().rotate(rotation);

	setNodeTransform(object.get_transform().get_transform_matrix() * currentTransform);

	auto M = getNodeTransform();
	auto PV = phys::GetPV();
	auto MVP = PV * M;

	renderer::bind(eff);

	glUniformMatrix4fv(
		eff.get_uniform_location("MVP"),
		1,
		GL_FALSE,
		value_ptr(MVP)
	);

	renderer::render(object);

	SceneNode::update();
}
