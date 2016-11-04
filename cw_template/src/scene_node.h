#pragma once

using namespace std;

class SceneNode
{
protected:
	vector<SceneNode*> children;

public:
	SceneNode() {}
	virtual ~SceneNode() { destroy(); }

	void release() { delete this; }

	virtual void update()
	{
		for (vector<SceneNode*>::iterator i = children.begin(); i != children.end(); i++)
		{
			(*i)->update();
		}
	}

	void destroy()
	{
		for (vector<SceneNode*>::iterator i = children.begin(); i != children.end(); i++)
		{
			(*i)->release();
		}
		children.clear();
	}

	void addChild(SceneNode* newNode)
	{
		children.push_back(newNode);
	}
};