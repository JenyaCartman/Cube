#include <iostream>
#include <SDL.h>
#include "Cube.h"

#include <vector>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool Init();
void Exit();
void DrawCube(Cube& cube);
void OnKeyDown(Uint32 key, std::vector<Cube>& cubes);

int main(int argc, char *argv[])
{
	if (!Init())
	{
		std::cout << "Could not init\n";
		return 1;
	}

	SDL_Event windowEvent;
	bool run = true;

    std::vector<Cube> cubes;
    cubes.push_back(Cube({ 0, 0, 1000, 1 }, { 400, 400, 400, 0 }, 0));
    cubes.push_back(Cube({ 0, 0, 1000, 1 }, { 200, 200, 200, 0 }, 0, {255, 128, 128, 255}));

	while (run)
	{
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        for (auto& cube : cubes)
        {
            cube.RenderCube();
            DrawCube(cube);
            cube.SetAngle(cube.GetAngle() + 0.01);
        }
        SDL_RenderPresent(renderer);

		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT)
			{
				run = false;
			}

			if (windowEvent.type == SDL_KEYDOWN)
			{
                OnKeyDown(windowEvent.key.keysym.sym, cubes);
			}
		}
	}

	Exit();

	return EXIT_SUCCESS;
}

void DrawCube(Cube& cube)
{
    Vector color = cube.GetColor();
	SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);

    SDL_RenderDrawLine(renderer, cube[0][0], cube[0][1], cube[1][0], cube[1][1]);
    SDL_RenderDrawLine(renderer, cube[1][0], cube[1][1], cube[2][0], cube[2][1]);
    SDL_RenderDrawLine(renderer, cube[2][0], cube[2][1], cube[3][0], cube[3][1]);
    SDL_RenderDrawLine(renderer, cube[3][0], cube[3][1], cube[0][0], cube[0][1]);

    SDL_RenderDrawLine(renderer, cube[4][0], cube[4][1], cube[5][0], cube[5][1]);
    SDL_RenderDrawLine(renderer, cube[5][0], cube[5][1], cube[6][0], cube[6][1]);
    SDL_RenderDrawLine(renderer, cube[6][0], cube[6][1], cube[7][0], cube[7][1]);
    SDL_RenderDrawLine(renderer, cube[7][0], cube[7][1], cube[4][0], cube[4][1]);

    SDL_RenderDrawLine(renderer, cube[0][0], cube[0][1], cube[4][0], cube[4][1]);
    SDL_RenderDrawLine(renderer, cube[1][0], cube[1][1], cube[5][0], cube[5][1]);
    SDL_RenderDrawLine(renderer, cube[2][0], cube[2][1], cube[6][0], cube[6][1]);
    SDL_RenderDrawLine(renderer, cube[7][0], cube[7][1], cube[3][0], cube[3][1]);
}

void OnKeyDown(Uint32 key, std::vector<Cube>& cubes)
{
    switch (key)
    {
    case SDLK_w:
    {
        for (auto& cube : cubes)
        {
            Vector cubePosition = cube.GetPosition();
            cubePosition[2] -= 15;
            cube.SetPosition(cubePosition);
        }
        break;
    }
    case SDLK_a:
    {
        for (auto& cube : cubes)
        {
            Vector cubePosition = cube.GetPosition();
            cubePosition[0] += 15;
            cube.SetPosition(cubePosition);
        }
        break;
    }
    case SDLK_s:
    {
        for (auto& cube : cubes)
        {
            Vector cubePosition = cube.GetPosition();
            cubePosition[2] += 15;
            cube.SetPosition(cubePosition);
        }
        break;
    }
    case SDLK_d:
    {
        for (auto& cube : cubes)
        {
            Vector cubePosition = cube.GetPosition();
            cubePosition[0] -= 15;
            cube.SetPosition(cubePosition);
        }
        break;
    }
    }
}

bool Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	if (window == nullptr)
	{
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr) 
	{
		std::cout << "Can't create renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void Exit()
{
	SDL_DestroyWindow(window);
	window = nullptr;

	SDL_DestroyRenderer(renderer);
	renderer = nullptr;

	SDL_Quit();
}