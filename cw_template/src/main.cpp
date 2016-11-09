#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <graphics_framework.h>
#include <phys_utils.h>
#include "scene_graph.h"

using namespace std;
using namespace graphics_framework;
using namespace glm;

mesh playfield;
effect basic_eff;

bool load_content() 
{
	phys::Init();
	phys::SetCamera1Pos(vec3(0.0f, 55.0f, 0.1f));
	phys::SetCamera1Target(vec3(0.0f, 0.0f, 0.0f));
	phys::SetCamera2Pos(vec3(0.0f, 8.0f, 30.0f));

	basic_eff.add_shader("shaders/basic.vert", GL_VERTEX_SHADER);
	basic_eff.add_shader("shaders/basic.frag", GL_FRAGMENT_SHADER);
	basic_eff.build();

	return true;
}

bool update(double delta_time) {
	phys::Update(delta_time);
	return true;
}

bool render() {
/*	phys::DrawSphere(glm::vec3(4.0f, 4.0f, 0), 1.0f, RED);
	phys::DrawSphere(glm::vec3(-4.0f, 4.0f, 0), 1.0f, RED);
	phys::DrawSphere(glm::vec3(0, 8.0f, 0), 0.2f, YELLOW);
	phys::DrawSphere(glm::vec3(0), 1.0f, GREEN);
	phys::DrawSphere(glm::vec3(0, 4.0f, 4.0f), 1.0f, BLUE);
	phys::DrawSphere(glm::vec3(0, 4.0f, -4.0f), 1.0f, BLUE);
	phys::DrawCube(glm::vec3(0, 4.0f, 0));
	phys::DrawLine(glm::vec3(0, 4.0f, 4.0f), glm::vec3(0, 8.0f, 0));
	phys::DrawLine(glm::vec3(0, 4.0f, -4.0f), glm::vec3(0, 8.0f, 0));
	phys::DrawLine(glm::vec3(4.0f, 4.0f, 0), glm::vec3(0), true, ORANGE);
	phys::DrawLine(glm::vec3(-4.0f, 4.0f, 0), glm::vec3(0), true, PINK);
	phys::DrawLineCross(glm::vec3(0, 8.0f, 0), 1.0f, false);
	phys::DrawArrow(glm::vec3(0, 4.0f, 0), glm::vec3(0, 8.0f, 0), 1.0f, GREY);
*/
	phys::DrawScene();

	const unsigned int playfield_width = 20;
	const unsigned int playfield_length = 42;

	const float playfield_x = (float)playfield_width / 2.0f;
	const float playfield_z = (float)playfield_length / 2.0f;

	vector<vec3> playfield_positions
	{
		vec3(playfield_x, 5.0f, -playfield_z),
		vec3(-playfield_x, 5.0f, -playfield_z),
		vec3(playfield_x, 5.0f, playfield_z),

		vec3(-playfield_x, 5.0f, playfield_z),
		vec3(playfield_x, 5.0f, playfield_z),
		vec3(-playfield_x, 5.0f, -playfield_z)
	};
	vector<vec4> playfield_colours
	{
		vec4(1.0f, 0.0f, 0.0f, 1.0f),
		vec4(1.0f, 0.0f, 0.0f, 1.0f),
		vec4(1.0f, 0.0f, 0.0f, 1.0f),
		vec4(1.0f, 0.0f, 0.0f, 1.0f),
		vec4(1.0f, 0.0f, 0.0f, 1.0f),
		vec4(1.0f, 0.0f, 0.0f, 1.0f)
	};
	const float playfield_angle = 0.122173f;

	GeometryNode* playfield = new GeometryNode(playfield_positions, playfield_colours, basic_eff);
	TransformNode* rotate_playfield = new TransformNode( vec3(0.0f, 0.0f, 0.0f),
														 vec3(1.0f, 1.0f, 1.0f),
														 vec3(playfield_angle, 0.0f, 0.0f),
														 basic_eff);
	playfield->addChild(rotate_playfield);
	playfield->update();

	return true;
}

void main() {
	// Create application
	app application;
	// Set load content, update and render methods
	application.set_load_content(load_content);
	application.set_update(update);
	application.set_render(render);
	// Run application
	application.run();
}