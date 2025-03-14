#include "GameObject.h"

unsigned int GameObject::nextId = 0;

GameObject::GameObject()
{
	name = "defaultObject";
	id = 0;
}

GameObject::~GameObject()
{
	for (auto component : components)
	{
		delete component;
	}
}

void GameObject::init()
{
	std::cout << "GameObject init" << std::endl;
	position = { (float)GetScreenWidth()/2,(float)GetScreenHeight()/2};
	velocity = { 0,0 };
	//init(position, velocity);
	color = RED;
}

void GameObject::init(Vector2 pos, Vector2 vel)
{
	position = pos;
	velocity = vel;
	color = RED;
}

void GameObject::init(Vector2 pos, Vector2 vel, Color col)
{
	position = pos;
	velocity = vel;
	color = col;
}

void GameObject::update()
{
	position.x += velocity.x * GetFrameTime();
	position.y += velocity.y* GetFrameTime();
	if (position.x > GetScreenWidth())
	{
		position.x = 0;
	}
	if (position.x < 0)
	{
		position.x = GetScreenWidth();
	}
	if (position.y > GetScreenHeight())
	{
		position.y = 0;
	}
	if (position.y < 0)
	{
		position.y = GetScreenHeight();
	}

	for (auto component : components)
	{
		component->Update();
	}
}

void GameObject::draw()
{
	DrawCircle(position.x, position.y, 10, color);

	for (auto component : components)
	{
		component->Draw();
	}
}

void GameObject::addComponent(Component* component)
{
	components.push_back(component);
}

void GameObject::removeComponent(Component* component)
{
	components.erase(std::remove(components.begin(), components.end(), component), components.end());
}

void GameObject::setVelocity(Vector2 vel)
{
	velocity = vel;
}



GameObject* GameObject::Spawn(Vector2 pos, Vector2 vel, std::string _name)
{
	std::cout << "GameObject Create" << std::endl;

	GameObject* obj = new GameObject();
	obj->init(pos, vel);
	obj->name = _name;
	obj->color = RED;
	obj->id = nextId;
	nextId++;
	return obj;

}
