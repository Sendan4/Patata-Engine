#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
#include <cxxabi.h>
#endif

#include <glad/gl.h>
#include <fast_io.h>
#if defined(_WIN64)
#include <windows.h>
#endif

// Patata Engine
#include "PatataEngine/PatataEngine.hpp"
#include "Log.hpp"
#include "TerminalColors.hpp"

void Patata::Engine::InitRenderer(void) {
	Patata::Log::WindowLog(Info->pWindow);

	#if defined(_WIN64)
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(Terminal, &mode);
	SetConsoleMode(Terminal, ENABLE_VIRTUAL_TERMINAL_PROCESSING | mode);
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

		GLADloadfunc pGlLoadProc = reinterpret_cast<GLADloadfunc>(SDL_GL_GetProcAddress);
		if (pGlLoadProc == nullptr) {
			#if defined(_WIN64)
			fast_io::io::println(fast_io::out(),
				PATATA_TERM_COLOR_GRAY0,
			#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
				"[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ",
			#else
				"[", std::string_view{ typeid(pGlLoadProc).name() }, "] ",
			#endif
				PATATA_TERM_COLOR_WHITE,
				"Obtaining The SDL Process Address For Glad Loader :",
				PATATA_TERM_COLOR_YELLOW,
				"Fail");
			#else			
			fast_io::io::println(PATATA_TERM_DIM,
				PATATA_TERM_COLOR_GRAY0,
				#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
				"[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ",
				#else
				"[", std::string_view{ typeid(pGlLoadProc).name() }, "] ",
				#endif
				PATATA_TERM_RESET,
				PATATA_TERM_BOLD,
				"Obtaining The SDL Process Address For Glad Loader : ",
				PATATA_TERM_RESET,
				PATATA_TERM_COLOR_YELLOW,
				"Fail",
				PATATA_TERM_RESET);
			#endif
		}
		else {
			#if defined(_WIN64)
			fast_io::io::println(fast_io::out(),
				PATATA_TERM_COLOR_GRAY0,
			#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
				"[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ",
			#else
				"[", std::string_view{ typeid(pGlLoadProc).name() }, "] ",
			#endif
				PATATA_TERM_COLOR_WHITE,
				"Obtaining The SDL Process Address For Glad Loader : ",
				PATATA_TERM_COLOR_GREEN,
				"Success");
			#else			
			fast_io::io::println(PATATA_TERM_DIM,
				PATATA_TERM_COLOR_GRAY0,
				#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
				"[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ",
				#else
				"[", std::string_view{ typeid(pGlLoadProc).name() }, "] ",
				#endif
				PATATA_TERM_RESET,
				PATATA_TERM_BOLD,
				"Obtaining The SDL Process Address For Glad Loader : ",
				PATATA_TERM_RESET,
				PATATA_TERM_COLOR_GREEN,
				"Success",
				PATATA_TERM_RESET);
			#endif
		}
	    
		if (!gladLoadGL(pGlLoadProc)) {
			#if defined(_WIN64)
			fast_io::io::println(fast_io::out(),
				PATATA_TERM_COLOR_GRAY0,
			#if defined(__GNUC__) || defined(__MINGW64__)
				"[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ",
			#else
				"[", std::string_view{ typeid(pGlLoadProc).name() }, "] ",
			#endif
				PATATA_TERM_COLOR_WHITE,
				"Glad Loader Load OpenGL Functions : ",
				PATATA_TERM_COLOR_YELLOW,
				"Fail",
				PATATA_TERM_RESET, "\n");
			#else			
			fast_io::io::println(PATATA_TERM_DIM,
				PATATA_TERM_COLOR_GRAY0,
				#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
				"[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ",
				#else
				"[", std::string_view{ typeid(pGlLoadProc).name() }, "] ",
				#endif
				PATATA_TERM_RESET,
				PATATA_TERM_BOLD,
				"Glad Loader Load OpenGL Functions : ",
				PATATA_TERM_RESET,
				PATATA_TERM_COLOR_YELLOW,
				"Fail",
				PATATA_TERM_RESET);
			#endif
		}
		else {
			#if defined(_WIN64)
			fast_io::io::println(fast_io::out(),
				PATATA_TERM_COLOR_GRAY0,
			#if defined(__GNUC__) || defined(__MINGW64__)
				"[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ",
			#else
				"[", std::string_view{ typeid(pGlLoadProc).name() }, "] ",
			#endif
				PATATA_TERM_COLOR_WHITE,
				"Glad Loader Load OpenGL Functions : ",
				PATATA_TERM_COLOR_GREEN,
				"Success",
				PATATA_TERM_RESET, "\n");
			#else
			fast_io::io::println(PATATA_TERM_DIM,
				PATATA_TERM_COLOR_GRAY0,
				#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
				"[", std::string_view{ abi::__cxa_demangle(typeid(pGlLoadProc).name(), nullptr, nullptr, nullptr) }, "] ",
				#else
				"[", std::string_view{ typeid(pGlLoadProc).name() }, "] ",
				#endif
				PATATA_TERM_RESET,
				PATATA_TERM_BOLD,
				"Glad Loader Load OpenGL Functions : ",
				PATATA_TERM_RESET,
				PATATA_TERM_COLOR_GREEN,
				"Success",
				PATATA_TERM_RESET, "\n");
			#endif	
		}

		pOpenGLRenderer = new Patata::Graphics::OpenGLRenderer(Config);
	}

	#if defined(_WIN64)
	SetConsoleMode(Terminal, mode);
	#endif
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
