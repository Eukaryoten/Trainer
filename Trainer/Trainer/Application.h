#pragma once
#include "Framework.h"
#include "GeometryManager.h"

class Application : public Framework
{
public:
	Application(HINSTANCE hInstance);

	bool InitializeGame();
	void Update(float dt);
	void Render();

	~Application();

private:

	GeometryManager* gManager;

};

