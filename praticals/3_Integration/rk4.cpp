#include "main.h"
#include <glm/glm.hpp>
using namespace std;
using namespace glm;

static dvec3 gravity = dvec3(0, -10.0, 0);
double current_weave_dir = 1.0;

struct Derivative {
  dvec3 dx, dv;
};

dvec3 acceleration(const sBall &body, dvec3 x, dvec3 v, double t) {
	// We could be summing accelerations, or doing other cool things here
	if (t > 10.0) {
		double weave_factor = 2.0;
		dvec3 weave;
		if (body.position.x >= 1)
		{
			weave_factor *= -1.0;
			current_weave_dir = -1.0;
		}
		else if (body.position.x <= -4)
		{
			weave_factor *= 1.0;
			current_weave_dir = 1.0;
		}
		else
		{
			weave_factor *= current_weave_dir;
		}
		weave = dvec3(weave_factor, 0, 0);

		dvec3 total_acc = gravity + weave;
		return total_acc;
	}
	else
	{
		return gravity;
	}
}

Derivative compute(const sBall &body, const double t, const double dt, const Derivative &d) {
  // Where would we be and how fast at dt 
  dvec3 x = body.position + d.dx * dt;
  dvec3 v = body.velocity + d.dv * dt;

  Derivative output;
  output.dx = v;
  // What would the acceleration be at this point?
  // *********************************
  dvec3 acc = acceleration(body, x, v, t);
  output.dv = acc;
  return output;
}

void UpdatePhysics_rk4(const double t, const double dt) {
  for (size_t i = 0; i < balls.size(); i++) {
    Derivative a, b, c, d;

    // Incrementally compute for various dt
	// *********************************
	a = compute(balls[i], t, 0.0f, {dvec3(0), dvec3(0)});
    b = compute(balls[i], t, dt * 0.5f, a);
    c = compute(balls[i], t, dt * 0.5f, b);
    d = compute(balls[i], t, dt, c);

    // Compute the final derivative
    // *********************************
	dvec3 final_pos = a.dx + (2.0 * b.dx) + (2.0 * c.dx) + d.dx;
	dvec3 final_vel = a.dv + (2.0 * b.dv) + (2.0 * c.dv) + d.dv;

    // Apply against dt and get final outputs
    // *********************************
	balls[i].position += final_pos * (dt / 6.0);
	balls[i].velocity += final_vel * (dt / 6.0);

    if (balls[i].position.y <= 0.0f) {
      balls[i].velocity.y = -balls[i].velocity.y;
    }
  }
}