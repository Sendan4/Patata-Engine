project('Patata_Engine',
  'cpp', 'c',
version : '0',
  default_options : [
    'buildtype=release'],
  subproject_dir : 'externals',
  license: 'MIT')

if get_option('use_git')
  git = find_program('git', native: true, required: false)
endif

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

if (meson.get_compiler('cpp').has_argument('-std=gnu++20'))
  cpp_std = 'c++20'
endif

if get_option('use_git') and git.found()
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

  add_project_arguments('-DGIT_BRANCH="'+branchCOutput+'"', language : 'cpp')
endif

# Macros
add_project_arguments(
  '-DPATATAVERSION=0',
  '-DBUILDSYS="Meson"',
  '-DENGINE_NAME="Patata Engine"',
  language : 'cpp')

meson.get_compiler('cpp').check_header('iostream', required : true)
meson.get_compiler('cpp').check_header('ios', required : true)
meson.get_compiler('cpp').check_header('iomanip', required : true)
meson.get_compiler('cpp').check_header('vector', required : true)
meson.get_compiler('cpp').check_header('algorithm', required : true)
meson.get_compiler('cpp').check_header('cstdint', required : true)
meson.get_compiler('cpp').check_header('cstring', required : true)
meson.get_compiler('cpp').check_header('tuple', required : true)

if target_machine.system() == 'windows'
  meson.get_compiler('c').check_header('windows.h', required : true)
endif

Glad2_dep = subproject('Glad2').get_variable('Glad2_dep')

sdl2_dep = dependency('sdl2',
  required : true,
  static : false,
  version : '>=2.24.1',
  modules : ['SDL2::SDL2'])

if sdl2_dep.found()
  meson.get_compiler('c').check_header('SDL.h', dependencies : sdl2_dep, required : true)
  meson.get_compiler('c').check_header('SDL_vulkan.h', dependencies : sdl2_dep, required : true)
  meson.get_compiler('c').check_header('SDL_opengl.h', dependencies : sdl2_dep, required : true)
endif

Vulkan = dependency('Vulkan',
  static : false,
  required : true)

if Vulkan.found()
  meson.get_compiler('cpp').check_header('vulkan/vulkan.hpp', dependencies : Vulkan, required : true)
endif

yamlcpp = dependency('yaml-cpp',
  static : false,
  required : true)

if yamlcpp.found()
  meson.get_compiler('cpp').check_header('yaml-cpp/yaml.h', dependencies : yamlcpp, required : true)
endif

dependencies = [Vulkan, sdl2_dep, yamlcpp, Glad2_dep]

if (get_option('buildtype') == 'debug' or get_option('buildtype') == 'debugoptimized')
  imgui_dep = subproject('Imgui').get_variable('Imgui_dep')

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

subdir('assets')

# posiblemente mueva esta parte del icono a otra parte
# Icon
if get_option('enable_icon')
  add_project_arguments('-DUSE_ICON=1', language : 'cpp')
  message('Icon: Yes')

  if get_option('use_custom_icon')
    if get_option('icon_path') != ''
      message('Custom Icon: Yes')
      message('Icon Path: ' + get_option('icon_path'))

      run_command('cp', get_option('icon_path'), meson.build_root(), check : true)

      if get_option('game_name') != ''
        run_command('mv', meson.build_root() + '/icon.bmp', meson.build_root() + '/' + get_option('game_name') + '.bmp', check : true)
      endif
    endif
  else
    message('Custom Icon: No')

    run_command('cp', 'assets/icon/patata.bmp', meson.build_root(), check : true)

    if get_option('game_name') != ''
      run_command('mv', meson.build_root() + '/icon.bmp', meson.build_root() + get_option('game_name') + '.bmp', check : true)
    endif
  endif
else
  message('Icon: No')
endif

run_command('cp', 'patata.yaml', meson.build_root(), check : true)

if get_option('game_name') != ''
  run_command('mv', meson.build_root() + '/patata.yaml', meson.build_root() + '/' + get_option('game_name') + '.yaml', check : true)
endif

include = include_directories('include/')
subdir('src')

lib = library(meson.project_name(),
  source,
  include_directories : [include],
  d_import_dirs : [include],
  dependencies : [dependencies],
  build_by_default : true)

project_dep = declare_dependency(
  include_directories : [include],
  d_import_dirs : [include],
  link_with : lib)

set_variable(meson.project_name() + '_dep', project_dep)
