#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <graphics_framework.h>
#include <phys_utils.h>

using namespace std;
using namespace graphics_framework;
using namespace glm;

map<string, mesh> meshes;

bool load_content() {
	phys::Init();

	const double playfield_width = 20.0;
	const double playfield_length = 42.0;

	geometry playfield_geom;
	playfield_geom.set_type(GL_QUADS);
	vector<vec3> playfield_positions
	{
		vec3(0.0, 0.0, 5.0),
		vec3(playfield_width, 0.0, 5.0),
		vec3(playfield_width, playfield_length, 5.0),
		vec3(0.0, playfield_length, 5.0)
	};
	playfield_geom.add_buffer(playfield_positions, BUFFER_INDEXES::POSITION_BUFFER);
	meshes["playfield"] = mesh(playfield_geom);

	return true;
}

bool update(float delta_time) {
	phys::SetCameraPos(vec3(0.0f, 40.0f, 0.1f));
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

	for (auto &e : meshes)
	{
		auto m = e.second;


	}

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