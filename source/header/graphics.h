#ifndef GRAPHICS_H
#define GRAPHICS_H

/*  Graphics class
 *  Holds all graphics information for the game
 */

#include <SDL.h>

#include <map>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
	Graphics();
	~Graphics();

	/* SDL_Surface* loadImage
	*  Loads an image into the _spriteSheets map if it doesn't already exist
	*  Each image will only be loaded once
	*/
	SDL_Surface* loadImage(const std::string &filePath);

	/* void blitSurface
	*  Draws a texture to a certain part of the screen
	*/
	void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	/* void flip
	 *  Renders to the screen
	 */
	void flip();

	/* void clear
	 *  Clears the screen
	 */
	void clear();

	/* SDL_Renderer* getRenderer
	 * Returns the renderer for use elsewhere
	 */
	SDL_Renderer* getRenderer() const;
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Surface*> _spriteSheets;
};

#endif
