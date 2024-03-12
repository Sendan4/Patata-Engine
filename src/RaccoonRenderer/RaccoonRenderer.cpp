#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
#include <cxxabi.h>
#endif

#if defined(_WIN64)
#include <windows.h>
#endif

#include <glad/gl.h>
#include <fast_io.h>

// Patata Engine
#include "PatataEngineImpl.hpp"
#include "TerminalColors.hpp"

void Patata::Graphics::RaccoonRenderer::RaccoonBackendInit(YAML::Node & Config, SDL_Window *& Window) {
	#if defined(_WIN64)
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(Terminal, &mode);
	SetConsoleMode(Terminal, ENABLE_VIRTUAL_TERMINAL_PROCESSING | mode);
	#endif

	if (backend == Patata::Graphics::Backend::Vulkan) {
		// Vulkan
		pVulkanBackend = new Patata::Graphics::RaccoonRenderer::VulkanBackend(Window, Config);
	}
	else if (backend == Patata::Graphics::Backend::OpenGL) {
		// OpenGL
		GameGLContext = new SDL_GLContext;
		*GameGLContext = SDL_GL_CreateContext(Window);

		if (Config["patata-engine"]["raccoon-renderer"]["vsync"].as<bool>()) {
			if (Config["patata-engine"]["raccoon-renderer"]["opengl-adaptative-vsync"].as<bool>())
				SDL_GL_SetSwapInterval(-1);
			else
				SDL_GL_SetSwapInterval(1);
		}
		else SDL_GL_SetSwapInterval(0);

		GLADloadfunc pGlLoadProc = reinterpret_cast<GLADloadfunc>(SDL_GL_GetProcAddress);
		// GLad Process Adress
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

	    // Load OpenGL Functions
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

		pOpenGLBackend = new Patata::Graphics::RaccoonRenderer::OpenGLBackend(Config);
	}

	#if defined(_WIN64)
	SetConsoleMode(Terminal, mode);
	#endif
}

#include "ExitLog.hpp"

Patata::Graphics::RaccoonRenderer::RaccoonRenderer(YAML::Node & Config, SDL_Window *& Window, const bool & _Backend) {
	backend = _Backend;
	RaccoonBackendInit(Config, Window);
}

Patata::Graphics::RaccoonRenderer::~RaccoonRenderer(void) {
	if (backend) {
		// Vulkan
		Patata::Log::DeleteAndLogPtr("Vulkan Backend", pVulkanBackend);
	} 
	else {		
		// OpenGL
		Patata::Log::DeleteAndLogPtr("OpenGL Backend", pOpenGLBackend);
		SDL_GL_DeleteContext(*GameGLContext);
		Patata::Log::DeleteAndLogPtr("OpenGL Context", GameGLContext);
	}
}
