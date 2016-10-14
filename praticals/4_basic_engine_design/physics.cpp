#include "physics.h"
#include <glm/glm.hpp>
#include <time.h>
using namespace std;
using namespace glm;
static vector<cPhysics *> physicsScene;

static dvec3 gravity = dvec3(0, -10.0, 0);
dvec3 launch = dvec3(80.0, 200.0, 0.0);
dvec3 wind = dvec3(0.0, 0.0, 0.0);

cPhysics::cPhysics() : pm(POINT), Component("Physics") { physicsScene.push_back(this); }

cPhysics::~cPhysics() {
  auto position = std::find(physicsScene.begin(), physicsScene.end(), this);
  if (position != physicsScene.end()) {
    physicsScene.erase(position);
  }
}

void cPhysics::Update(double delta) {
  for (auto &e : physicsScene) {
    e->GetParent()->SetPosition(e->position);
  }
}

void cPhysics::SetParent(Entity *p) {
  Component::SetParent(p);
  position = Ent_->GetPosition();
  prev_position = position;
}

dvec3 acceleration(cPhysics *e, const double t)
{
	dvec3 total_accel = vec3(0.0, 0.0, 0.0);

	if (t < 0.1) 
		total_accel += gravity + launch;
	else 
		total_accel += gravity;

	return total_accel;
}

void UpdatePhysics(const double t, const double dt) {
  for (auto &e : physicsScene) {
    e->Render();
    // calcualte velocity from current and previous position
    dvec3 velocity = e->position - e->prev_position;
    // set previous position to current position
    e->prev_position = e->position;
    // position += v + a * (dt^2)
    e->position += velocity + acceleration(e,t) * pow(dt, 2);

    if (e->position.y <= 0.0f) {
		// Continued trajectory
		e->prev_position.y = e->position.y + (e->position.y - e->prev_position.y);
		// Back and forth
		//e->prev_position = e->position + (e->position - e->prev_position);
    }
  }
}

void InitPhysics() {}

void ShutdownPhysics() {}
