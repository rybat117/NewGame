#include "graphics.h"
#include <SDL.h>

/*  Graphics class
 *  Holds all graphics information for the game
 */

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(640, 480, 0, &this->_window, &this->_renderer); // Create window; specify resolution
	SDL_SetWindowTitle(this->_window, "New Game");
}

Graphics::~Graphics() {
	SDL_DestroyWindow(this->_window);
}