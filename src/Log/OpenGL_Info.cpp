#include <iostream>
#include <iomanip>
#include <ios>
#include <cstring>

#include <yaml-cpp/yaml.h>
#include <glad/gl.h>

// Patata Engine
#include "PatataEngine/TerminalColors.hpp"
#include "PatataEngine/Log.hpp"

void Patata::Log::OpenGLInfo(YAML::Node CONFIG) {
	std::cout << Bold << FSteelBlue1 << "OpenGL Info" << std::setw(3) << ":\n" << Reset;

	std::cout << Bold << std::setw(4) << ' '  << "Vendor"  << std::setw(20) << ": " << Reset << glGetString(GL_VENDOR) << "\n";

	std::cout << Bold << std::setw(4) << ' '  << "Renderer" << std::setw(18) << ": " << Reset << glGetString(GL_RENDERER) << "\n";

	{
		GLint glmayorversion = 0, glminorversion = 0;
		glGetIntegerv(GL_MAJOR_VERSION, &glmayorversion);
		glGetIntegerv(GL_MINOR_VERSION, &glminorversion);
		std::string glversion = std::to_string(glmayorversion) + '.' + std::to_string(glminorversion);

		std::cout << Bold << std::setw(4) << ' '  << "Version" << std::setw(19) << ": " << Reset << glversion << "\n";
	}

	std::cout << Bold << std::setw(4) << ' '  << "GLSL Version" << std::setw(14) << ": " << Reset << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

	std::cout << Bold << std::setw(4) << ' '  << "GLAD Version" << std::setw(14) << ": " << Reset << GLAD_GENERATOR_VERSION << "\n";

	std::cout << Bold << std::setw(4) << ' '  << "Profile" << std::setw(19) << ": " << Reset;
	{
		GLint contextflags = 0;
		glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &contextflags);

		switch (contextflags) {
			case GL_CONTEXT_CORE_PROFILE_BIT :
				std::cout << "Core\n";
				break;

			case GL_CONTEXT_COMPATIBILITY_PROFILE_BIT :
				std::cout << "Compatibility\n";
				break;

			default :
				std::cout << "Unknown\n";
				break;
		}
	}

	std::cout << Bold << std::setw(4) << ' '  << "Accelerated Visual" << std::setw(8) << ": " << Reset;
	{
		int accel = 0;
		SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &accel);

		if (accel == 1)
			std::cout << "Hardware\n";
		else if (accel == 0)
			std::cout << "Software\n";
	}

	std::cout << Bold << std::setw(4) << ' '  << "Buffer" << std::setw(20) << ": " << Reset;
	{
		int buff = 0;
		SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &buff);

		if (buff == 1)
			std::cout << "Double\n";
		else if (buff == 0)
			std::cout << "Single\n";
	}

	std::cout << Bold << std::setw(4) << ' '  << "Vsync" << std::setw(21) << ": " << Reset;
	if (CONFIG["vsync"].as<bool>())
		std::cout << Chartreuse1 << "Yes\n";
	else
		std::cout << BLightGoldenRod1 << "No\n";

	std::cout << "\n" << Bold << FSteelBlue1 << std::setw(4) << ' '  << "Used Extensions" << std::setw(3) << ":\n" << Reset << Dim;

	if (strcmp(reinterpret_cast<const char *>(glGetString(GL_VENDOR)), reinterpret_cast<const char *>("ATI Technologies Inc")) != 0) {
		if (GL_AMD_performance_monitor)
			std::cout << std::setw(10) << ' ' << "GL_AMD_perfomance_monitor\n";
	}
	std::cout << Reset;

	#if DEBUG
		std::cout << "\n" << Bold << FSteelBlue1 << std::setw(4) << ' '  << "Available Extensions" << std::setw(3) << ":\n" << Reset << Dim;
		{
			GLint NumberOfExtensions = 0;
			glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);

			for (GLint i = 0; i <= NumberOfExtensions; i++)
				std::cout << std::setw(10) << ' ' << glGetStringi(GL_EXTENSIONS, i) << "\n";
		}
	#endif	

	std::cout << Reset << "\n";
}
