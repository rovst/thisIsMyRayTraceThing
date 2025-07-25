#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>  // For bool

struct Circle {
    int x;
    int y;
    int r;
};


struct ray{
    double startY;
    double angle;
    double startX;
    double endX;
    double endY;
};


void FillCircle(SDL_Surface* surface, struct Circle circle, Uint32 color) {
    int x_start = circle.x - circle.r;
    int x_end = circle.x + circle.r;
    int y_start = circle.y - circle.r;
    int y_end = circle.y + circle.r;

    int radius_squared = circle.r * circle.r;

    for (int x = x_start; x <= x_end; x++) {
        for (int y = y_start; y <= y_end; y++) {
            int dx = x - circle.x;
            int dy = y - circle.y;
            int distance_squared = dx * dx + dy * dy;

            if (distance_squared <= radius_squared) {
                SDL_Rect pixel = { x, y, 1, 1 };
                SDL_FillRect(surface, &pixel, color);
            }
        }
    }
}

void emmit_Ray(struct Circle circle, struct ray rayarr[100]){

    for(int i=1; i<=100;i++){
        double angle=(i/100.0)*360.0;
        rayarr[i].angle=angle;
        printf("%f\n", angle);
    }
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "this is my raytrace thing", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        900, 700, 
        0);

    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *surface = SDL_GetWindowSurface(window);
    if (!surface) {
        printf("SDL_GetWindowSurface Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    // Define the circle
    struct Circle circle = { 200, 200, 80 };
    struct Circle shadow_circle = { 200, 20, 200 };

    struct ray rays[100];
    emmit_Ray(circle, rays);

    Uint32 white = SDL_MapRGB(surface->format, 255, 255, 255);
    Uint32 black = SDL_MapRGB(surface->format, 0, 0, 0);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if(event.type ==SDL_MOUSEMOTION && event.motion.state !=0){
                circle.x=event.motion.x;
                circle.y=event.motion.y;
            }
    }
        //background
        SDL_FillRect(surface, NULL, black);
        // circle
        FillCircle(surface, circle, white);
        FillCircle(surface, shadow_circle, white);

        SDL_UpdateWindowSurface(window);
        SDL_Delay(16); // frames
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
