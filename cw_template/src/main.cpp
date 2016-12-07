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
//map<string, texture> texes;

bool load_content() 
{
	phys::Init();

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
	const float off_the_ground = 5.0f;

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
/*	vec4 playfield_colour = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	vec4 outer_walls_colour = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	vec4 top_walls_colour = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	vec4 inner_walls_colour = vec4(0.0f, 0.0f, 0.0f, 1.0f);
*/	
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


/*	// *************
	// LOAD TEXTURES
	// *************
	texes["red"] = texture("../../../enu_pba/cw_template/red.jpg");
	texes["black"] = texture("../../../enu_pba/cw_template/black.jpg");
*/

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
	phys::Update(delta_time);
	return true;
}

bool render() {
	phys::DrawScene();
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