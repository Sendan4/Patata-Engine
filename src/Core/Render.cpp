// Patata Engine
#include "Render.hpp"

void
Patata::Engine::EngineImpl::Render (void)
{
  if (*RaccoonRenderer->Backend == Patata::Graphics::Backend::Vulkan)
    {
    }
  else
    {
// OpenGL
#if defined(DEBUG)
      ImGuiStartFrame ();
      DrawDebugUI ();
#else
      glClearColor (0.113f, 0.578f, 0.810f, 0.5f);
#endif

      glClear (GL_COLOR_BUFFER_BIT);

#if defined(DEBUG)
      ImGuiEndFrame ();
#endif

      SDL_GL_SwapWindow (GameWindow);
    }
}
