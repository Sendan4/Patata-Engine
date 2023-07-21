#include <iostream>
#include <glad/gl.h>

// Patata Engine
#include "Core/Log.hpp"
#include "Core/terminal_colors.hpp"

void Patata::Log::OpenGLInfo(void) {
	std::cout << FSteelBlue1 << Bold << "OpenGL Info:\n" << Reset;
	std::cout << Bold << "  Vendor:\t" << Reset << glGetString(GL_VENDOR) << "\n";
	std::cout << Bold << "  Version:\t" << Reset << glGetString(GL_VERSION) << "\n";
	std::cout << Bold << "  GPU:  \t" << Reset << glGetString(GL_RENDERER) << "\n";
	std::cout << Bold << "  GLSL Version:\t" << Reset << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
}
