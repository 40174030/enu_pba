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

/*	directional_light light;
	light.set_ambient_intensity(vec4(0.9f, 0.9f, 0.9f, 1.0f));
	light.set_direction(vec3(0.1f, 0.6f, 0.1f));
	renderer::bind(light, "light");

	material mat;
	mat.set_emissive(vec4(0.0f, 0.0f, 0.0f, 0.0f));
	mat.set_diffuse(object.get_material().get_diffuse());
	mat.set_specular(object.get_material().get_specular());
	mat.set_shininess(object.get_material().get_shininess());
	renderer::bind(mat, "mat");
*/
	auto M = getNodeTransform();
	auto PV = phys::GetPV();
	auto MVP = PV * M;
//	auto N = object.get_transform().get_normal_matrix() * (mat3)currentTransform;

	renderer::bind(eff);

	// Set MVP matrix uniform
	glUniformMatrix4fv(
		eff.get_uniform_location("MVP"),
		1,
		GL_FALSE,
		value_ptr(MVP)
	);
/*	// Set M matrix uniform
	glUniformMatrix4fv(
		eff.get_uniform_location("M"),
		1,
		GL_FALSE,
		value_ptr(M));
	// Set N matrix uniform
	glUniformMatrix3fv(
		eff.get_uniform_location("N"),
		1,
		GL_FALSE,
		value_ptr(N));

	// Set eye position
	if (phys::IsFreeCamEnabled)
	{
		glUniform3fv(
			eff.get_uniform_location("eye_pos"),
			1,
			value_ptr(phys::GetCamera2Pos()));
	}
	else
	{
		glUniform3fv(
			eff.get_uniform_location("eye_pos"),
			1,
			value_ptr(phys::GetCamera1Pos()));
	}
*/
	renderer::render(object);

	SceneNode::update();
}
