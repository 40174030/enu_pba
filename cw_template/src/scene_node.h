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
	mat4 currentTransform;

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

	void addChild(SceneNode* newNode)
	{
		newNode->setParent(this);
		children.push_back(newNode);
	}

	void setCurrentTransform(mat4 cT)
	{
		currentTransform = cT;
	}

	void setParent(SceneNode* newParent)
	{
		this->parent = newParent;
	}

	mat4 getCurrentTransform() { return currentTransform; }

	list<SceneNode*> getChildren() { return children; }

};