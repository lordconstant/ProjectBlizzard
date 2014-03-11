#pragma once

class Scene{
public:
	Scene();
	~Scene();

	virtual void initialise() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual void processKey(int key) = 0;
};

