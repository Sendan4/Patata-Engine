project('Patata Engine',
  'cpp', 'c',
  default_options: ['buildtype=release', 'cpp_std=c++20'],
  version : '0')

branchCommand = run_command('git', 'branch', '--show-current', check: true)
branchCOutput = branchCommand.stdout().strip()
message('Branch:', branchCOutput)
# Macros
add_project_arguments('-DPatataVersion=0', '-DGIT_BRANCH="'+branchCOutput+'"', '-DBuildSys="Meson"', language : 'cpp') 

sdl2_dep = dependency('sdl2',
  required : true,
  static : false,
  version : '>=2.24.1',
  modules : ['SDL2::SDL2'])

Vulkan = dependency('Vulkan',
  static : false,
  required : true)

# GLAD
Glad2 = declare_dependency(
  sources : 'externals/Glad2/src/gl.c',
  include_directories : 'externals/Glad2/include/',
  d_import_dirs : 'externals/Glad2/include/')

# Archivos (Source y Include)
include_main = include_directories('include')

source = files([
  'src/Core/main.cpp',
  'src/Core/Main_Loop.cpp',
  'src/Core/Start_And_End.cpp',
  'src/Window/Window.cpp',
  'src/Window/Window_Icon.cpp',
  'src/Core/API_Graphics_Switch.cpp',
  'src/Opengl/Opengl_Context.cpp',
  'src/Log/OpenGL_Info.cpp',
  'src/Vulkan/Setup_Vulkan.cpp',
  'src/Log/Mapache.cpp',
  'src/Log/Start_Patata_Log_Info.cpp'])

if target_machine.system() == 'windows'
  windows = import('windows')

  Patata_icon = windows.compile_resources('src/Core/patata.rc')

  executable('Patata Engine',
    source,
    Patata_icon,
    include_directories : [include_main],
    dependencies : [sdl2_dep, Vulkan, Glad2])
else
  executable('Patata Engine',
    source,
    include_directories : [include_main],
    dependencies : [sdl2_dep, Vulkan, Glad2])
endif
