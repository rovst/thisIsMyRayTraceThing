#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>

#define COLOR_WHITE 0xFFFFFF

// Structure to represent a circle
struct Circle {
    double x;
    double y;
    double r;
};

// Function to fill a circle on an SDL surface
void FillCircle(SDL_Surface* surface, struct Circle circle, Uint32 color) {
    double radius_squared = pow(circle.r, 2);

    // Iterate over a square bounding box around the circle
    for (int x = (int)(circle.x - circle.r); x <= (int)(circle.x + circle.r); x++) {
        for (int y = (int)(circle.y - circle.r); y <= (int)(circle.y + circle.r); y++) {
            // Calculate the squared distance from the center of the circle to the current pixel
            double distance_squared = pow(x - circle.x, 2) + pow(y - circle.y, 2);

            // If the pixel is inside or on the boundary of the circle, fill it
            if (distance_squared <= radius_squared) {
                // Ensure the pixel is within the surface boundaries
                if (x >= 0 && x < surface->w && y >= 0 && y < surface->h) {
                    // Get the pixel format to map the color correctly
                    Uint32* pixels = (Uint32*)surface->pixels;
                    pixels[y * surface->w + x] = color;
                }
            }
        }
    }
}

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create an SDL window
    SDL_Window* window = SDL_CreateWindow("Raytrace Circle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 700, 0);
    if (window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Get the surface of the window
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    if (surface == NULL) {
        fprintf(stderr, "Could not get window surface! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Fill the entire surface with black (or any background color)
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0)); // Black background

    // Define a circle
    struct Circle myCircle = {
        .x = 450, // Center X
        .y = 350, // Center Y
        .r = 100  // Radius
    };

    // Call FillCircle with the correct arguments
    // Use SDL_MapRGB to get the correct pixel format for the color
    FillCircle(surface, myCircle, SDL_MapRGB(surface->format, 255, 255, 255)); // White circle

    // Update the window surface to show the changes
    SDL_UpdateWindowSurface(window);

    // Keep the window open for 5 seconds
    SDL_Delay(5000);

    // Clean up SDL resources
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}