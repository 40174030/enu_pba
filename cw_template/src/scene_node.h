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
	mat4 nodeTransform;

public:
	SceneNode() { parent = nullptr; }
	virtual ~SceneNode() { destroy(); }

	void release() { delete this; }

	void destroy()
	{
		for (list<SceneNode*>::iterator i = children.begin(); i != children.end(); i++)
		{
			(*i)->release();
		}
		children.clear();
	}

	virtual void update()
	{
		for (list<SceneNode*>::iterator i = children.begin(); i != children.end(); i++)
		{
			(*i)->update();
		}
	}

	void addChild(SceneNode* newNode)
	{
		newNode->setNodeParent(this);
		children.push_back(newNode);
	}

	void setNodeParent(SceneNode* newParent)
	{
		this->parent = newParent;
	}

	void setNodeTransform(mat4 newTransform)
	{
		this->nodeTransform = newTransform;
	}

	list<SceneNode*> getNodeChildren() { return children; }
	mesh getNodeObject() { return object; }
	mat4 getNodeTransform() { return nodeTransform; }
};