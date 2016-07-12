#pragma once
#include "AppDelegate.h"
#include "HelloWorldScene.h"

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
	auto engine = Engine::getInstance();

	engine->init();
	engine->setWindowSize(768, 480);

	BP_Event e;
	HelloWorldScene h;
	h.push(&h);
	mainLoop(e);
	h.pop();
	return true;
}

void AppDelegate::mainLoop(BP_Event & e)
{
	auto engine = Engine::getInstance();
	auto loop = true;
	while (loop && engine->pollEvent(e) >= 0)
	{
		for (auto b : Base::baseVector)
		{
			if (b->visible)
				b->draw();
		}
		if (Base::baseVector.size() > 0)
			Base::baseVector.back()->dealEvent(e);
		switch (e.type)
		{
		case BP_QUIT:
			if (engine->showMessage("Quit"))
				loop = false;
			break;
		default:
			break;
		}
		engine->renderPresent();
		engine->delay(25);
	}
}
