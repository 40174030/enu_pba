#pragma once
#include "list"
#include <graphics_framework.h>
#include <phys_utils.h>
#include <glm/glm.hpp>

using namespace std;
using namespace graphics_framework;
using namespace glm;

class SceneNode
{
protected:
	list<SceneNode*> children;
	SceneNode* parent;
	mesh object;

public:
	SceneNode() { parent = nullptr; }
	virtual ~SceneNode() { destroy(); }

	void release() { delete this; }

	virtual void update()
	{
		for (list<SceneNode*>::iterator i = children.begin(); i != children.end(); i++)
		{
			(*i)->update();
		}
	}

	void destroy()
	{
		for (list<SceneNode*>::iterator i = children.begin(); i != children.end(); i++)
		{
			(*i)->release();
		}
		children.clear();
	}

	void setParent(SceneNode* newParent)
	{
		this->parent = newParent;
	}

	void addChild(SceneNode* newNode)
	{
		newNode->setParent(this);
		children.push_back(newNode);
	}

	mesh getNodeObject() { return object; }

	void renderNode(mesh object, effect eff)
	{


		auto M = object.get_transform().get_transform_matrix();
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
	}
};