#pragma once
#include <iostream>
#include <vector>
#include "raylib.h"
#include "Component.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	void init();
	void init(Vector2 pos, Vector2 vel);
	void init(Vector2 pos, Vector2 vel,Color col);
	void update();
	void draw();

	void addComponent(Component* component);  
	void removeComponent(Component* component);

	bool enabled;

	Vector2 position;
	Vector2 velocity;
	Color color;
	void setVelocity(Vector2 vel);

	static GameObject* Spawn(Vector2 pos, Vector2 vel, std::string _name);
	

private:
	unsigned int id;
	std::string name;
	static unsigned int nextId;
	std::vector<Component*> components;


};

