#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <graphics_framework.h>
#include <phys_utils.h>
#include "scene_graph.h"

using namespace std;
using namespace graphics_framework;
using namespace glm;

effect basic_eff;
effect phong_eff;
GeometryNode* playfield;

struct Ball
{
	dvec3 velocity;
	dvec3 position;
};
Ball pinball;
double realtime = 0.0;
dvec3 gravity = vec3(0.0f, -9.8, 0);

#define ticks_per_frame 10
#define physics_tick 1.0f / 600.0f
#define off_the_ground 5.0f

bool load_content() 
{
	phys::Init();
	pinball.position = vec3(0.0f, 10.0f, -17.0f);

	// ***********
	// SET CAMERA
	// ***********
	phys::SetCamera1Pos(vec3(0.0f, 55.0f, 0.1f));
	phys::SetCamera1Target(vec3(0.0f, 0.0f, 0.0f));
	phys::SetCamera2Pos(vec3(0.0f, 8.0f, 30.0f));


	// *************
	// BUILD SHADERS
	// *************
	basic_eff.add_shader("shaders/basic.vert", GL_VERTEX_SHADER);
	basic_eff.add_shader("shaders/basic.frag", GL_FRAGMENT_SHADER);
	basic_eff.build();

	phong_eff.add_shader("shaders/phys_phong.vert", GL_VERTEX_SHADER);
	phong_eff.add_shader("shaders/phys_phong.frag", GL_FRAGMENT_SHADER);
	phong_eff.build();


	// *************
	// DRAW GEOMETRY
	// *************
	const unsigned int playfield_width = 20;
	const unsigned int playfield_length = 42;
	const float playfield_x = (float)playfield_width / 2.0f;
	const float playfield_z = (float)playfield_length / 2.0f;
	const float playfield_angle = 0.122173f;
	const float wall_height = 2.0f;
	const float wall_width = 1.0f;

	vector<vec3> playfield_positions
	{
		vec3(playfield_x, off_the_ground, -playfield_z),
		vec3(-playfield_x, off_the_ground, -playfield_z),
		vec3(playfield_x, off_the_ground, playfield_z),

		vec3(-playfield_x, off_the_ground, playfield_z),
		vec3(playfield_x, off_the_ground, playfield_z),
		vec3(-playfield_x, off_the_ground, -playfield_z)
	};

	vector<vec3> outer_wall_positions
	{
		// Top
		vec3(-playfield_x, off_the_ground + wall_height, -playfield_z),
		vec3(playfield_x, off_the_ground, -playfield_z),
		vec3(-playfield_x, off_the_ground, -playfield_z),
		vec3(playfield_x, off_the_ground + wall_height, -playfield_z),
		vec3(playfield_x, off_the_ground, -playfield_z),
		vec3(-playfield_x, off_the_ground + wall_height, -playfield_z),

		// Left
		vec3(-playfield_x, off_the_ground + wall_height, playfield_z),
		vec3(-playfield_x, off_the_ground, -playfield_z),
		vec3(-playfield_x, off_the_ground, playfield_z),
		vec3(-playfield_x, off_the_ground + wall_height, -playfield_z),
		vec3(-playfield_x, off_the_ground, -playfield_z),
		vec3(-playfield_x, off_the_ground + wall_height, playfield_z),

		// Right
		vec3(playfield_x, off_the_ground + wall_height, playfield_z),
		vec3(playfield_x, off_the_ground, playfield_z),
		vec3(playfield_x, off_the_ground, -playfield_z),
		vec3(playfield_x, off_the_ground + wall_height, -playfield_z),
		vec3(playfield_x, off_the_ground + wall_height, playfield_z),
		vec3(playfield_x, off_the_ground, -playfield_z),
	};

	vector<vec3> top_wall_positions
	{
		// Left
		vec3(-playfield_x, off_the_ground + wall_height, -playfield_z),
		vec3(-playfield_x, off_the_ground + wall_height, playfield_z),
		vec3(-playfield_x + wall_width, off_the_ground + wall_height, playfield_z),
		vec3(-playfield_x + wall_width, off_the_ground + wall_height, -playfield_z),
		vec3(-playfield_x, off_the_ground + wall_height, -playfield_z),
		vec3(-playfield_x + wall_width, off_the_ground + wall_height, playfield_z),

		// Right
		vec3(playfield_x, off_the_ground + wall_height, playfield_z),
		vec3(playfield_x, off_the_ground + wall_height, -playfield_z),
		vec3(playfield_x - wall_width, off_the_ground + wall_height, playfield_z),
		vec3(playfield_x - wall_width, off_the_ground + wall_height, -playfield_z),
		vec3(playfield_x - wall_width, off_the_ground + wall_height, playfield_z),
		vec3(playfield_x, off_the_ground + wall_height, -playfield_z),

		// Top
		vec3(-playfield_x, off_the_ground + wall_height, -playfield_z),
		vec3(-playfield_x, off_the_ground + wall_height, -playfield_z + wall_width),
		vec3(playfield_x, off_the_ground + wall_height, -playfield_z + wall_width),
		vec3(playfield_x, off_the_ground + wall_height, -playfield_z),
		vec3(-playfield_x, off_the_ground + wall_height, -playfield_z),
		vec3(playfield_x, off_the_ground + wall_height, -playfield_z + wall_width)
	};

	vector<vec3> inner_wall_positions
	{
		// Left
		vec3(-playfield_x + wall_width, off_the_ground, -playfield_z + wall_width),
		vec3(-playfield_x + wall_width, off_the_ground + wall_height, playfield_z),
		vec3(-playfield_x + wall_width, off_the_ground, playfield_z),
		vec3(-playfield_x + wall_width, off_the_ground + wall_height, -playfield_z + wall_width),
		vec3(-playfield_x + wall_width, off_the_ground + wall_height, playfield_z),
		vec3(-playfield_x + wall_width, off_the_ground, -playfield_z + wall_width),

		// Right
		vec3(playfield_x - wall_width, off_the_ground, -playfield_z + wall_width),
		vec3(playfield_x - wall_width, off_the_ground, playfield_z),
		vec3(playfield_x - wall_width, off_the_ground + wall_height, playfield_z),
		vec3(playfield_x - wall_width, off_the_ground + wall_height, -playfield_z + wall_width),
		vec3(playfield_x - wall_width, off_the_ground, -playfield_z + wall_width),
		vec3(playfield_x - wall_width, off_the_ground + wall_height, playfield_z),

		// Top
		vec3(-playfield_x + wall_width, off_the_ground, -playfield_z + wall_width),
		vec3(playfield_x - wall_width, off_the_ground, -playfield_z + wall_width),
		vec3(playfield_x - wall_width, off_the_ground + wall_height, -playfield_z + wall_width),
		vec3(-playfield_x + wall_width, off_the_ground + wall_height, -playfield_z + wall_width),
		vec3(-playfield_x + wall_width, off_the_ground, -playfield_z + wall_width),
		vec3(playfield_x - wall_width, off_the_ground + wall_height, -playfield_z + wall_width)
	};


	// ********************
	// SET GEOMETRY COLOURS
	// ********************
	vector<vec4> playfield_colours;
	for (vec3 v : playfield_positions)
	{
		playfield_colours.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}

	vector<vec4> outer_wall_colours;
	for (vec3 v : outer_wall_positions)
	{
		outer_wall_colours.push_back(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}

	vector<vec4> top_wall_colours;
	for (vec3 v : top_wall_positions)
	{
		top_wall_colours.push_back(vec4(1.0f, 0.0f, 0.0f, 1.0f));
	}

	vector<vec4> inner_wall_colours;
	for (vec3 v : inner_wall_positions)
	{
		inner_wall_colours.push_back(vec4(0.0f, 0.0f, 0.0f, 1.0f));
	}


	// ******************
	// CREATE SCENE NODES
	// ******************
	playfield = new GeometryNode(playfield_positions, playfield_colours);
	GeometryNode* outer_walls = new GeometryNode(outer_wall_positions, outer_wall_colours);
	GeometryNode* top_walls = new GeometryNode(top_wall_positions, top_wall_colours);
	GeometryNode* inner_walls = new GeometryNode(inner_wall_positions, inner_wall_colours);

	RenderNode* transform_playfield = new RenderNode(basic_eff, 
													 vec3(0.0f, 0.0f, 0.0f),
													 vec3(1.0f, 1.0f, 1.0f),
													 vec3(playfield_angle, 0.0f, 0.0f));
	RenderNode* transform_outer_walls = new RenderNode(basic_eff);
	RenderNode* transform_top_walls = new RenderNode(basic_eff);
	RenderNode* transform_inner_walls = new RenderNode(basic_eff);


	// **********************
	// CONSTRUCT SCENE GRAPH
	// **********************
	playfield->addChild(transform_playfield);
		transform_playfield->addChild(outer_walls);
			outer_walls->addChild(transform_outer_walls);
		transform_playfield->addChild(top_walls);
			top_walls->addChild(transform_top_walls);
		transform_playfield->addChild(inner_walls);
			inner_walls->addChild(transform_inner_walls);

	return true;
}

bool update(double delta_time) {
	bool done = false;
	uint16_t frames = 0;
	uint16_t ticks = 0;
	double accum = 0.0;

	if (glfwGetKey(renderer::get_window(), GLFW_KEY_SPACE)) {
		pinball.position = vec3(0.0f, 10.0f, -17.0f);
		pinball.velocity = vec3(0.0f);
		done = false;
		accum = 0.0;
		ticks = 0;
		frames = 0;
	}

	if (!done)
	{
		frames++;
		for (int i = 0; i < ticks_per_frame; i++)
		{
			ticks++;
			pinball.velocity += gravity * (delta_time / ticks_per_frame);
			pinball.position += pinball.velocity * (delta_time / ticks_per_frame);
		}
		if (pinball.position.y <= 0.0f) {
			pinball.velocity.y = 0;
			done = true;
		}
	}

	phys::Update(delta_time);
	return true;
}

bool render() {
	phys::DrawScene();

	// **************
	// DRAW PLAYFIELD
	// **************
	playfield->update();

	// ************
	// DRAW PINBALL
	// ************
	phys::DrawSphere(pinball.position, 1.0f, GREEN);

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