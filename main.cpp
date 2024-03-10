#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <SDL2/SDL.h>
using namespace std;

void draw_rect(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
{
    for (int y = y1; y <= y2; y++)
    {
        SDL_RenderDrawLine(renderer, x1, y, x2, y);
    }
}

vector<int> make_range(int n)
{
    vector<int> result(n);
    
    for (int i = 0; i < n; i++)
        result[i] = i + 1;

    return result;
}

const int WIDTH = 800, HEIGHT = 600;
int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window *window = SDL_CreateWindow("Bubble sort visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event windowEvent;

    vector<int> a = make_range(40);
    auto rng = default_random_engine {Uint32(time(0))};
    
    shuffle(begin(a), end(a), rng);

    int place_counter = 0;
    int change_counter = 1;
    int wait;
    while (true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        for (int i = 0; i < a.size(); i++)
        {
            if (i == place_counter || i == change_counter)
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            else 
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            draw_rect(renderer, i * 20 + 1, HEIGHT - a[i] * 10, (i + 1) * 20 - 1, HEIGHT);
        }
        SDL_RenderPresent(renderer);

        if (a[place_counter] > a[change_counter])
            swap(a[place_counter], a[change_counter]);
        
        change_counter++;
        if (change_counter >= a.size())
        {
            place_counter++;
            change_counter = place_counter + 1;
        }
        if (place_counter >= a.size())
            break;
        
        SDL_Delay(20);
    }

    while(true)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (SDL_QUIT == windowEvent.type)
            {
                break;
            }
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}