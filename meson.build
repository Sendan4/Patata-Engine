project('Patata_Engine',
  'cpp', 'c',
  version : '0',
  meson_version : '>=1.2.0',
  default_options : [
    'buildtype=release',
    'cpp_std=c++20',
    'warning_level=0'],
  subproject_dir : 'externals',
  license : 'MIT',
  license_files : 'LICENSE.txt')

if get_option('use_git')
  git = find_program('git', native: true, required: false)
endif

cpp = meson.get_compiler('cpp')

if cpp.get_id() == 'gcc' or cpp.get_id() == 'clang'
  #if (cpp.has_argument('-Wall') and cpp.has_argument('-Wextra') and cpp.has_argument('-Wpedantic'))
  #  warning_level = 3
  #elif (cpp.has_argument('-Wall') and c++.has_argument('-Wextra'))
  #  warning_level = 2
  #elif (cpp.has_argument('-Wall'))
  #  warning_level = 1
  #else
  #  warning_level = 0
  #endif
  warning_level = 0
endif

cpp.has_argument('-std=c++20')
cpp.has_argument('-std=gnu++20')

link_arguments = []

if get_option('default_library') == 'static' or get_option('prefer_static') == true
  cpp.has_argument('-static-libgcc')
  cpp.has_argument('-static-libstdc++')

  link_arguments += ['-static-libgcc', '-static-libgcc'] 
endif

cpp.has_link_argument('-Wl,-rpath')

if (cpp.has_link_argument('-ffast-math'))
  link_arguments += ['-ffast-math']
endif

if get_option('use_git') and git.found()
  # commit macro
  get_commit_hash_long = run_command('git', 'rev-parse', 'HEAD', check: true)
  git_commit_long_hash = get_commit_hash_long.stdout().strip()

  get_commit_hash_short = run_command('git', 'rev-parse', '--short', 'HEAD', check: true)
  git_commit_short_hash = get_commit_hash_short.stdout().strip()

  add_project_arguments('-DPATATA_GIT_HASH_LONG="'+git_commit_long_hash+'"', language : 'cpp')
  add_project_arguments('-DPATATA_GIT_HASH_SHORT="'+git_commit_short_hash+'"', language : 'cpp')

  # Build Type macro
  if (get_option('buildtype') == 'release')
    add_project_arguments('-DPATATA_BUILD_TYPE="Release"', language : 'cpp')
  elif (get_option('buildtype') == 'debug')
    add_project_arguments(
      '-DPATATA_BUILD_TYPE="Debug"',
      '-DDEBUG=1',
      language : 'cpp')
  elif (get_option('buildtype') == 'debugoptimized')
    add_project_arguments(
      '-DPATATA_BUILD_TYPE="Debug Optimized"',
      '-DDEBUG=1',
      language : 'cpp')
  elif (get_option('buildtype') == 'minsize')
    add_project_arguments('-DPATATA_BUILD_TYPE="Minimal Size Release"', language : 'cpp')
  endif

  branchCommand = run_command('git', 'branch', '--show-current', check: true)
  branchCOutput = branchCommand.stdout().strip()
  message('Branch:', branchCOutput)

  add_project_arguments('-DPATATA_GIT_BRANCH="'+branchCOutput+'"', language : 'cpp')
endif

if get_option('default_library') == 'shared' or get_option('default_library') == 'both'
  add_project_arguments('-DSHARED_LIBRARY_EXPORT_DEFINE=1', language : 'cpp')
endif

# Macros
add_project_arguments(
  '-DPATATA_VERSION=0',
  '-DPATATA_BUILD_SYSTEM="Meson (Ninja Build)"',
  '-DPATATA_COMPILER_PROGRAM="Undefined"',
  '-DPATATA_ENGINE_NAME="Patata Engine"',
  language : 'cpp')

cpp.check_header('vector', required : true)
cpp.check_header('algorithm', required : true)
cpp.check_header('cstdint', required : true)
cpp.check_header('cstring', required : true)
cpp.check_header('tuple', required : true)

c = meson.get_compiler('c')
if target_machine.system() == 'windows'
  c.check_header('windows.h', required : true)
endif

Glad2_dep = subproject('Glad2').get_variable('Glad2_dep')

Fast_io_dep = subproject('fast_io').get_variable('fast_io_dep')

sdl2_dep = dependency('sdl2',
  required : true,
  static : false,
  #version : '>=2.28.4',
  modules : ['SDL2::SDL2'])

if sdl2_dep.found()
  c.check_header('SDL.h', dependencies : sdl2_dep, required : true)
  c.check_header('SDL_vulkan.h', dependencies : sdl2_dep, required : true)
  c.check_header('SDL_opengl.h', dependencies : sdl2_dep, required : true)
endif

Vulkan = dependency('Vulkan',
  static : false,
  required : true)

if Vulkan.found()
  cpp.check_header('vulkan/vulkan.hpp', dependencies : Vulkan, required : true)
endif

yamlcpp = dependency('yaml-cpp',
  static : false,
  required : true)

if yamlcpp.found()
  cpp.check_header('yaml-cpp/yaml.h', dependencies : yamlcpp, required : true)
endif

dependencies = [Vulkan, Fast_io_dep, sdl2_dep, yamlcpp, Glad2_dep]

if (get_option('buildtype') == 'debug' or get_option('buildtype') == 'debugoptimized')
  imgui_dep = subproject('imgui').get_variable('imgui_dep')

  dependencies += [imgui_dep]
endif

features = {
  'Vulkan' : Vulkan.found(),
  'OpenGL' : Glad2_dep.found(),
  'SDL2' : sdl2_dep.found(),
  'Yaml-cpp' : yamlcpp.found()
}

summary({
  'OpenGL': features['OpenGL'],
  'Vulkan': features['Vulkan'],
  'SDL2' : features['SDL2'],
  'Yaml-cpp' : features['Yaml-cpp']},
  bool_yn : true)

#Game name
if get_option('game_name') != ''
  message('Game Name: ' + get_option('game_name'))
  add_project_arguments('-DGAME_NAME="'+get_option('game_name')+'"', language : 'cpp')
endif

subdir('data/assets')
subdir('data')

include = include_directories('include/')
subdir('src')
