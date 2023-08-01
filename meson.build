project('Patata Engine',
  'cpp', 'c',
  version: '0',
  default_options: [
    'buildtype=release'])

if meson.get_compiler('cpp').get_id() == 'gcc' or meson.get_compiler('cpp').get_id() == 'clang'
  if (meson.get_compiler('cpp').has_argument('-Wall') and meson.get_compiler('cpp').has_argument('-Wextra'))
    warning_level = 3
  elif meson.get_compiler('cpp').has_argument('-Wall') and not meson.get_compiler('cpp').has_argument('-Wextra')
    warning_level = 3
  endif
endif

if (meson.get_compiler('cpp').has_argument('-std=c++20'))
  cpp_std = 'c++20'
endif

# commit macro
get_commit_hash_long = run_command('git', 'rev-parse', 'HEAD', check: true)
git_commit_long_hash = get_commit_hash_long.stdout().strip()

get_commit_hash_short = run_command('git', 'rev-parse', '--short', 'HEAD', check: true)
git_commit_short_hash = get_commit_hash_short.stdout().strip()

add_project_arguments('-DGIT_HASH_LONG="'+git_commit_long_hash+'"', language : 'cpp')
add_project_arguments('-DGIT_HASH_SHORT="'+git_commit_short_hash+'"', language : 'cpp')

# Build Type macro
if (get_option('buildtype') == 'release')
  add_project_arguments('-DBUILD_TYPE="Release"', language : 'cpp')
elif (get_option('buildtype') == 'debug')
  add_project_arguments(
    '-DBUILD_TYPE="Debug"',
    '-DDEBUG=1',
    language : 'cpp')
elif (get_option('buildtype') == 'debugoptimized')
  add_project_arguments(
    '-DBUILD_TYPE="Debug Optimized"',
    '-DDEBUG=1',
    language : 'cpp')
elif (get_option('buildtype') == 'minsize')
  add_project_arguments('-DBUILD_TYPE="Minimal Size Release"', language : 'cpp')
endif

branchCommand = run_command('git', 'branch', '--show-current', check: true)
branchCOutput = branchCommand.stdout().strip()
message('Branch:', branchCOutput)

# Macros
add_project_arguments('-DPATATAVERSION=0', '-DGIT_BRANCH="'+branchCOutput+'"', '-DBUILDSYS="Meson"', language : 'cpp') 

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
  'src/Log/Vulkan_Info.cpp',
  'src/Log/Mapache.cpp',
  'src/Log/Start_Patata_Log_Info.cpp'])

features = {
    'Vulkan' : Vulkan.found(),
    'OpenGL' : Glad2.found(),
    'SDL2' : sdl2_dep.found()
}

summary({'OpenGL': features['OpenGL'],
         'Vulkan': features['Vulkan'],
          'SDL2' : features['SDL2']},
         bool_yn : true)

if target_machine.system() == 'windows'
  windows = import('windows')

  Patata_icon = windows.compile_resources('src/Core/patata.rc')

  executable('Patata Engine',
    source,
    Patata_icon,
    win_subsystem : 'console',
    include_directories : [include_main],
    dependencies : [sdl2_dep, Vulkan, Glad2])
else
  executable('Patata Engine',
    source,
    include_directories : [include_main],
    dependencies : [sdl2_dep, Vulkan, Glad2])
endif
