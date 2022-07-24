#include <iostream>
#include <SDL.h>

#include "Point.hpp"
#include "Vector.hpp"
#include "Matrix.hpp"
#include "Ray.hpp"
#include "Material.hpp"
#include "Entity.hpp"
#include "Object.hpp"
#include "Camera.hpp"
#include "Cube.hpp"
#include "Sphere.hpp"
#include "Plan.hpp"
#include "Light.hpp"
#include "Scene.hpp"

#include "SDL_image.h"
#include "IMG_png.c"

#include <math.h>

struct App {

    SDL_Window* window;
    SDL_Surface* surface;
    SDL_Renderer* renderer;
    Scene* scene;

    int WIDTH = 500;
    int HEIGHT = 500;

    App() {};
    ~App();

    void init();
    void renderingScene();
    void loadScene();
};

App::~App() {
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void App::init()
{
    SDL_Init(SDL_INIT_VIDEO);
    window =  SDL_CreateWindow("scene", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,0);
    surface = SDL_GetWindowSurface(window);
    renderer = SDL_CreateRenderer(window, 0, 0);
}

void App::loadScene()
{
    scene = new Scene();

    scene->camera->focal = 1;

    scene->camera->translation(0, 0, 0);

    auto cube = new Cube();
    cube->translation(-1, 1, 2);
    cube->rotateZ(45);
    cube->rotateX(45);
    cube->rotateY(45);
    cube->scale(0.4f);
    cube->material.ka = Color(1, 0, 0);
    cube->material.kd = Color(1, 1, 1);
    cube->material.ks = Color(1, 1, 1);
    cube->material.shininess = 0.6f;
    scene->objects.push_back(cube);

    auto cube2 = new Cube();
    cube2->rotateX(180);
    cube2->rotateY(180);
    cube2->scale(1.f);
    cube2->translation(-5, 5, 12);
    cube2->material.ka = Color(1, 0, 0);
    cube2->material.kd = Color(1, 1, 1);
    cube2->material.ks = Color(0, 0, 0.6);
    cube2->material.shininess = 0.5f;
    scene->objects.push_back(cube2);

    auto plan = new Plan();
    plan->translation(5, 0, 50);
    plan->scale(1.0f);
    plan->material.ka = Color(1, 0, 0);
    plan->material.kd = Color(0.2, 0.2, 0.3);
    plan->material.ks = Color(0, 0, 0.6);
    plan->material.shininess = 0.8f;
    scene->objects.push_back(plan);

    auto sphere1 = new Sphere();
    sphere1->material.ka = Color(0, 1, 1);
    sphere1->material.kd = Color(0.7, 0.2, 0.6);
    sphere1->material.ks = Color(0.6, 0.2, 0.4);
    sphere1->translation(5, 5, 12);
    scene->objects.push_back(sphere1);

    auto sphere3 = new Sphere();
    sphere3->material.ka = Color(1, 0, 1);
    sphere3->material.kd = Color(0.5, 0.5, 0.5);
    sphere3->material.ks = Color(0, 0, 0);
    sphere3->translation(-2, 1, 5);
    sphere3->scale(1);
    scene->objects.push_back(sphere3);

    auto sphere2 = new Sphere();
    sphere2->material.ka = Color(1, 0, 1);
    sphere2->material.kd = Color(0.1, 0.4, 0.1);
    sphere2->material.ks = Color(0.4, 0.6, 0.4);
    sphere2->translation(2, 2, 0.6);
    sphere2->scale(1.f);
    scene->objects.push_back(sphere2);

    auto light1 = new Light(Color(0, 1, 0), Color(0.5, 0.4, 0.3));
    light1->translation(0.4, 0.4, 0);
    scene->lights.push_back(light1);

    auto light2 = new Light(Color(0.5, 0.4, 0.6), Color(0.8, 0.8, 0.8));
    light2->translation(-5, 0, 0);
    scene->lights.push_back(light2);
}

void App::renderingScene()
{
    Color backgroundColor = scene->getBackground();
    Camera* camera = scene->camera;
    SDL_RenderClear(renderer);

    for (float y = 0; y < HEIGHT; y++)
    {
        for (float x = 0; x < WIDTH; x++)
        {
            Color colorRendering;
            Point impact;
            Point impactIntersection;
            bool intersection;
            const Object* objectIntersected = nullptr;

            auto ray = camera->getRay(x / WIDTH, y / HEIGHT, 45);

            for each (const Object * object in scene->objects)
            {
                intersection = object->intersect(ray, impact);

                if (intersection) {
                    if (objectIntersected != nullptr) {
                        if (camera->nearest(*object, *objectIntersected)) {
                            impactIntersection = impact;
                            objectIntersected = object;
                        }
                    }
                    else {
                        impactIntersection = impact;
                        objectIntersected = object;
                    }
                }
            }

            if (objectIntersected != nullptr) {

                colorRendering = scene->getImpactColor(ray, *objectIntersected, impactIntersection);

                if (colorRendering.r > 1.f)
                    colorRendering.r = 1.f;

                if (colorRendering.g > 1.f)
                    colorRendering.g = 1.f;

                if (colorRendering.b > 1.f)
                    colorRendering.b = 1.f;

                colorRendering = colorRendering * 255;

                SDL_SetRenderDrawColor(renderer, colorRendering.r, colorRendering.g, colorRendering.b, 255);
            }
            else {
                SDL_SetRenderDrawColor(renderer, backgroundColor[0] * 255, backgroundColor[1] * 255, backgroundColor[2] * 255, 255);
            }
            SDL_RenderDrawPoint(renderer, x, y);
        }
        SDL_RenderPresent(renderer);
    }

}

int main(int argc, char* argv[])
{
    App* app = new App();
    app->init();
    app->loadScene();
    app->renderingScene();

    bool stop = false;
    SDL_Event event;

    while (!stop) {
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
            case SDL_QUIT:
                stop = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    stop = true;
                    break;
                case SDLK_f:
                    std::string fileName;
                    std::cin >> fileName;
                    std::cout << "file name is : " << fileName << std::endl;
                    break;
                }
                break;
            }
        }
    }

    return 0;
}