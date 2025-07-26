
#include <stdio.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <stdbool.h>

struct Circle {
    int x;
    int y;
    int r;
};

struct ray {
    double startX;
    double startY;
    double endX;
    double endY;
    double angle;
};

void FillCircle(SDL_Surface* surface, struct Circle circle, Uint32 color) {
    int x_start = circle.x - circle.r;
    int x_end = circle.x + circle.r;
    int y_start = circle.y - circle.r;
    int y_end = circle.y + circle.r;

    int radius_squared = circle.r * circle.r;

    for (int x = x_start; x <= x_end; x++) {
        for (int y = y_start; y <= y_end; y++) {

            if (distance_squared <= radius_squared) {
                SDL_Rect pixel = { x_draw, y_draw, 1, 1 };
                SDL_FillRect(surface, &pixel, color);

            }
        }
    }
}

void emmit_rays(struct Circle circle, struct ray rays[100]) {
    for (int i = 0; i < 100; i++) {
        double angle = ((double)i / 100) * 2 * M_PI;

        printf("Ray %d: angle=%.2f end=(%.2f, %.2f)\n", i, angle, endX, endY);
    }
}


void FillRays(SDL_Surface* surface, struct Ray rays[100], Uint32 color){
    for(int i=0; i<100; i++){
        struct Ray ray=rays[i];
        int end_of_screen=0;
        int object_hit=0;
            while(end_of_screen && !object_hit)//and{
            double x_draw=ray.x_start +i*cos(ray.angle);
            double y_draw=ray.y_start +i*cos(ray.angle);

        if(x_draw <0||
}}
int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Raytracer",
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

    struct Circle circle = { 200, 200, 80 };
    struct Circle shadow_circle = { 200, 20, 200 };

    struct ray rays[100];
    emmit_rays(circle, rays);

    Uint32 white = SDL_MapRGB(surface->format, 255, 255, 255);
    Uint32 black = SDL_MapRGB(surface->format, 0, 0, 0);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_MOUSEMOTION) {
                circle.x = event.motion.x;
                circle.y = event.motion.y;
                emmit_rays(circle, rays);
            }
        }

        SDL_FillRect(surface, NULL, black);

        FillCircle(surface, circle, white);
        FillCircle(surface, shadow_circle, white);
        Fillrays(surface, rays, 0xff0000);

        SDL_UpdateWindowSurface(window);
        SDL_Delay(16);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
