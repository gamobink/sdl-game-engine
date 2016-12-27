#include <sge/initializers/sdl-window.hpp>

namespace sge
{
    SDLWindowInitializer::SDLWindowInitializer(int width, int height, bool fullscreen, bool resizable)
        : width(width), height(height), fullscreen(fullscreen), resizable(resizable), _window(NULL), _renderer(NULL)
    {}

    void SDLWindowInitializer::do_initialize()
    {
        Uint32 flags = 0;

        if (fullscreen) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        if (resizable) flags |= SDL_WINDOW_RESIZABLE;

        if (SDL_CreateWindowAndRenderer(width, height, flags, &_window, &_renderer) != 0)
        {
            throw SGEInitError("SDL", SDL_GetError());
        }
    }

    void SDLWindowInitializer::do_shutdown()
    {
        if (_renderer != NULL)
        {
            SDL_DestroyRenderer(_renderer);
        }

        if (_window != NULL)
        {
            SDL_DestroyWindow(_window);
        }
    }

    SDL_Window *SDLWindowInitializer::window() const
    {
        return _window;
    }

    SDL_Renderer *SDLWindowInitializer::renderer() const
    {
        return _renderer;
    }
}
