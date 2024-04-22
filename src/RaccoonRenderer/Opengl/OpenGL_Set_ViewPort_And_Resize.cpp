#include "OpenGL_Set_ViewPort_And_Resize.hpp"

void
Patata::Graphics::RaccoonRenderer::OpenGLBackend::OpenGLSetViewPort (
    uint32_t WINDOW_INITIAL_WIDTH, uint32_t WINDOW_INITIAL_HEIGHT)
{
  glViewport (0, 0, WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT);
}

void
Patata::Graphics::RaccoonRenderer::OpenGLBackend::OpenGLResizeViewPort (
    SDL_Window * WINDOW)
{
  int width = 0, height = 0;
  SDL_GetWindowSize (WINDOW, &width, &height);

  glViewport (0, 0, width, height);
}
