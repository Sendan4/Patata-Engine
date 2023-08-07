source = files([
  'Core/main.cpp',
  'Core/Main_Loop.cpp',
  'Core/Start_And_End.cpp',
  'Core/API_Graphics_Switch.cpp',
  'Window/Window.cpp',
  'Window/Window_Icon.cpp',
  'Opengl/Opengl_Context.cpp',
  'Vulkan/Setup_Vulkan.cpp',
  'Log/OpenGL_Info.cpp',
  'Log/Mapache.cpp',
  'Log/Start_Patata_Log_Info.cpp',
  'Log/Vulkan_Info.cpp'])

if target_machine.system() == 'windows'
  windows = import('windows')
  Patata_icon = windows.compile_resources('Core/patata.rc')
endif
