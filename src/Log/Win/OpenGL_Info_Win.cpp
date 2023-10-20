#include <cstring>
#include <windows.h>

#include <fast_io.h>
#include <yaml-cpp/yaml.h>
#include <glad/gl.h>

// Patata Engine
#include "PatataEngine/PatataEngine.hpp"
#include "PatataEngine/Log.hpp"

void Patata::Log::OpenGLInfo(YAML::Node CONFIG) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Terminal, 9);
	fast_io::io::println(fast_io::out(), "OpenGL Info :");
	SetConsoleTextAttribute(Terminal, 7);

	fast_io::io::println(fast_io::out(), "    Vendor                  : ", std::string_view{ reinterpret_cast<const char *>(glGetString(GL_VENDOR)) });

	fast_io::io::println(fast_io::out(), "    Renderer                : ", std::string_view{ reinterpret_cast<const char *>(glGetString(GL_RENDERER)) });

	{
		GLint glmayorversion = 0, glminorversion = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &glmayorversion);
		glGetIntegerv(GL_MINOR_VERSION, &glminorversion);
		std::string glversion = std::to_string(glmayorversion) + '.' + std::to_string(glminorversion);

		fast_io::io::println(fast_io::out(), "    Version                 : ", glversion);
	}

	fast_io::io::println(fast_io::out(), "    GLSL Version            : ", std::string_view{ reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION)) });

	fast_io::io::println(fast_io::out(), "    GLAD Version            : ", GLAD_GENERATOR_VERSION);

	fast_io::io::print(fast_io::out(), "    Profile                 : ");
	{
		GLint contextflags = 0;
		glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &contextflags);

		switch (contextflags) {
			case GL_CONTEXT_CORE_PROFILE_BIT :
				fast_io::io::println(fast_io::out(), "Core");
				break;

			case GL_CONTEXT_COMPATIBILITY_PROFILE_BIT :
				fast_io::io::println(fast_io::out(), "Compatibility");
				break;

			default :
				fast_io::io::println(fast_io::out(), "Unknown");
				break;
		}
	}

	fast_io::io::print(fast_io::out(), "    Accelerated Visual      : ");
	{
		int accel = 0;
		SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &accel);

		if (accel == 1)
			fast_io::io::println(fast_io::out(), "Hardware");
		else if (accel == 0)
			fast_io::io::println(fast_io::out(), "Software");
	}

	fast_io::io::print(fast_io::out(), "    Buffer                  : ");
	{
		int buff = 0;
		SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &buff);

		if (buff == 1)
			fast_io::io::println(fast_io::out(), "Double");
		else if (buff == 0)
			fast_io::io::println(fast_io::out(), "Double");
	}

	fast_io::io::print(fast_io::out(), "    Vsync                   : ");
	if (CONFIG["vsync"].as<bool>())
		fast_io::io::println(fast_io::out(), "Yes");
	else
		fast_io::io::println(fast_io::out(), "No");

	fast_io::io::println(fast_io::out(), "\n    Used Extensions");

	if (strcmp(reinterpret_cast<const char *>(glGetString(GL_VENDOR)), reinterpret_cast<const char *>("ATI Technologies Inc")) != 0) {
		if (GL_AMD_performance_monitor) {
			SetConsoleTextAttribute(Terminal, 2);
			fast_io::io::println(fast_io::out(), "        GL_AMD_perfomance_monitor");
			SetConsoleTextAttribute(Terminal, 7);
		}
	}

	#if DEBUG
		fast_io::io::println(fast_io::out(), "\n    Available Extensions :");
		{
			GLint NumberOfExtensions = 0;
			glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);

			for (GLint i = 0; i < NumberOfExtensions; i++)
				fast_io::io::println(fast_io::out(), "        ", std::string_view{ reinterpret_cast<const char *>(glGetStringi(GL_EXTENSIONS, i)) });
		}
	#endif	

	fast_io::io::println(fast_io::out());
}
