#pragma once
#include "Prerequisites.h"
#include "UserInterface.h"

class Window;
class SwapChain;
class Texture;

class 
Screenshot {
public:
	Screenshot() = default;
	~Screenshot() {};

	void
	captureScreenshot(Window window, SwapChain swapChain, Texture& backBuffer);

	void
	ui(Window window, SwapChain swapChain, Texture& backBuffer);
private:

};
