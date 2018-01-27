#include <string>
#include <vector>
#include <iostream>

#include <SDL2/SDL.h>

#include "example.hpp"

void sdl_fail(std::string desc) {
	std::string msg = desc + ": " + SDL_GetError();
	std::cerr << msg << std::endl;
	throw new std::runtime_error(msg);
}

class SDL_Started {
	public:
		SDL_Started() {
			if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
				sdl_fail("SDL_Init failed");
			}
		}
		
		~SDL_Started() {
			SDL_Quit();
		}
};

int main(int argc, char* argv[]) {
	std::vector<std::string> args(argv, argv+argc);
	
	SDL_Started started;
	
	auto window = std::shared_ptr<SDL_Window>
		(SDL_CreateWindow(args[0].c_str(),
		                  SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		                  640, 480,
		                  0),
		 SDL_DestroyWindow);
	if(window == nullptr) {
		sdl_fail("SDL_CreateWindow failed");
	}
	
	auto renderer = std::shared_ptr<SDL_Renderer>
		(SDL_CreateRenderer(window.get(),
		                    -1,
		                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE),
		 SDL_DestroyRenderer);
	if(renderer == nullptr) {
		sdl_fail("SDL_CreateRenderer failed");
	}
	
	SDL_SetRenderDrawColor(renderer.get(),
	                       0x10,
	                       0xb0,
	                       0x10,
	                       SDL_ALPHA_OPAQUE);
	
	// Fill whole window.
	SDL_RenderFillRect(renderer.get(),
	                   NULL);
	
	// Apply rendering.
	SDL_RenderPresent(renderer.get());
	
	SDL_Event event;
	while (SDL_WaitEvent(&event) >= 0) {
		switch (event.type) {
			case SDL_QUIT:
				return(0);
				break;
			default: break;
		}
	}
	
	
	return 0;
}

