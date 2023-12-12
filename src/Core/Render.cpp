#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif

#include <glad/gl.h>
#include <fast_io.h>
#if defined(_WIN64)
#include <windows.h>
#else
#include "TerminalColors.hpp"
#endif

// Patata Engine
#include "PatataEngine/PatataEngine.hpp"
#include "Log.hpp"

void Patata::Engine::InitRenderer(void) {
	Patata::Log::WindowLog(Info->pWindow);

	#if defined(_WIN64)
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);
	#endif

	if (bGraphicsAPI == Patata::GraphicsAPI::Vulkan) {
		pVulkanRenderer = new Patata::Graphics::VulkanRenderer(Info->pWindow, Config);
	}
	else if (bGraphicsAPI == Patata::GraphicsAPI::OpenGL) {
		// OpenGL
		Info->pOpenGLContext = new SDL_GLContext;
		*Info->pOpenGLContext = SDL_GL_CreateContext(Info->pWindow);

		if (Config["patata-engine"]["raccoon-renderer"]["vsync"].as<bool>()) {
			if (Config["patata-engine"]["raccoon-renderer"]["opengl-adaptative-vsync"].as<bool>())
				SDL_GL_SetSwapInterval(-1);
			else
				SDL_GL_SetSwapInterval(1);
		}
		else SDL_GL_SetSwapInterval(0);

		#if defined(DEBUG)
		SetupImGUIBackend();
		#endif

		pGlLoadProc = reinterpret_cast<GLADloadfunc>(SDL_GL_GetProcAddress);
		if (pGlLoadProc == nullptr) {
			#if defined(_WIN64)
			SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);
			#if defined(__GNUC__) || defined(__MINGW64__)
			fast_io::io::print(fast_io::out(), "[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ");
			#else
			fast_io::io::print(fast_io::out(), "[", std::string_view{ typeid(pGlLoadProc).name() }, "] ");
			#endif
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			fast_io::io::print(fast_io::out(), "Obtaining The SDL Process Address For Glad Loader :");
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_INTENSITY);
			fast_io::io::println(fast_io::out(), "Fail");
			#else			
			fast_io::io::println(Dim, CGREY66, "[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ", Reset, Bold, "Obtaining The SDL Process Address For Glad Loader : ", Reset, BLightGoldenRod1, "Fail", Reset);
			#endif
		}
		else {
			#if defined(_WIN64)
			SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);
			#if defined(__GNUC__) || defined(__MINGW64__)
			fast_io::io::print(fast_io::out(), "[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ");
			#else
			fast_io::io::print(fast_io::out(), "[", std::string_view{ typeid(pGlLoadProc).name() }, "] ");
			#endif
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			fast_io::io::print(fast_io::out(), "Obtaining The SDL Process Address For Glad Loader : ");
			SetConsoleTextAttribute(Terminal, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			fast_io::io::println(fast_io::out(), "Success");
			#else			
			fast_io::io::println(Dim, CGREY66, "[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ", Reset, Bold, "Obtaining The SDL Process Address For Glad Loader : ", Reset, Chartreuse1, "Success", Reset);
			#endif
		}
	    
		if (!gladLoadGL(pGlLoadProc)) {
			#if defined(_WIN64)
			SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);
			#if defined(__GNUC__) || defined(__MINGW64__)
			fast_io::io::print(fast_io::out(), "[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ");
			#else
			fast_io::io::print(fast_io::out(), "[", std::string_view{ typeid(pGlLoadProc).name() }, "] ");
			#endif
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			fast_io::io::print(fast_io::out(), "Glad Loader Load OpenGL Functions : ");
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_INTENSITY);
			fast_io::io::println(fast_io::out(), "Fail");
			#else			
			fast_io::io::println(Dim, CGREY66, "[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ", Reset, Bold, "Glad Loader Load OpenGL Functions : ", Reset, BLightGoldenRod1, "Fail", Reset);
			#endif
		}
		else {
			#if defined(_WIN64)
			SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);
			#if defined(__GNUC__) || defined(__MINGW64__)
			fast_io::io::print(fast_io::out(), "[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ");
			#else
			fast_io::io::print(fast_io::out(), "[", std::string_view{ typeid(pGlLoadProc).name() }, "] ");
			#endif
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			fast_io::io::print(fast_io::out(), "Glad Loader Load OpenGL Functions : ");
			SetConsoleTextAttribute(Terminal, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			fast_io::io::println(fast_io::out(), "Success");
			fast_io::io::println(fast_io::out());
			#else
			#if defined(__GNUC__) || defined(__MINGW64__)
				fast_io::io::println(Dim, CGREY66, "[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ", Reset, Bold, "Glad Loader Load OpenGL Functions : ", Reset, Chartreuse1, "Success", Reset);
			#else
			fast_io::io::println(Dim, "[", std::string_view{ typeid(pGlLoadProc).name() }, "] ", Bold, "Glad Loader-Generator Load OpenGL Functions : ", Reset, Chartreuse1, "Success", Reset);
			#endif
			fast_io::io::println("");
			#endif
		}

		pOpenGLRenderer = new Patata::Graphics::OpenGLRenderer(Config);
	}
}

#if defined(DEBUG)
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#endif

void Patata::Engine::Render(void) {
	switch(bGraphicsAPI) {
		case Patata::GraphicsAPI::Vulkan:
			break;

		case Patata::GraphicsAPI::OpenGL:
			#if defined(DEBUG)
			ImGuiStartFrame();
			DrawDebugUI();
			#else
			glClearColor(0.113f, 0.578f, 0.810f, 0.5f);
			#endif

			glClear(GL_COLOR_BUFFER_BIT);

			#if defined(DEBUG)	
			ImGuiEndFrame();
			#endif

			SDL_GL_SwapWindow(Info->pWindow);
			break;
	}
}
