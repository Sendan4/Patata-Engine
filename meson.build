project('Patata_Engine',
  'cpp', 'c',
  version : '1',
  meson_version : '>=1.3.0',
  default_options : [
    'buildtype=release',
    'cpp_std=c++20',
    'warning_level=3'],
  subproject_dir : 'externals',
  license : 'MIT',
  license_files : 'LICENSE.txt')

# Version Macros
add_project_arguments(
  '-DPATATA_ENGINE_VERSION_MAYOR=1',
  '-DPATATA_ENGINE_VERSION_MINOR=0',
  '-DPATATA_ENGINE_VERSION_PATCH=0',
  language : 'cpp')

cpp = meson.get_compiler('cpp')

if cpp.get_id() == 'gcc' or cpp.get_id() == 'clang'
  cpp.has_argument('-Wall')
  cpp.has_argument('-Wextra')
  cpp.has_argument('-Wpedantic')
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

uint16_t = cpp.has_type('uint16_t', prefix : '#include <cstdint>', required : true)
uint32_t = cpp.has_type('uint32_t', prefix : '#include <cstdint>', required : true)
uint64_t = cpp.has_type('uint64_t', prefix : '#include <cstdint>', required : true)
int16_t = cpp.has_type('int16_t', prefix : '#include <cstdint>', required : true)
int32_t = cpp.has_type('int32_t', prefix : '#include <cstdint>', required : true)
int64_t = cpp.has_type('int64_t', prefix : '#include <cstdint>', required : true)
size_t = cpp.has_type('size_t', prefix : '#include <iterator>', required : true)
const_char_p = cpp.has_type('const char *', required : true)
const_char_p = cpp.has_type('bool', required : true)
string = cpp.has_type('std::string', prefix : '#include <string>', required : true)
cpp.check_header('cstring', required : true)
cpp.has_function('strcmp', required : true)
cpp.check_header('cstdlib', required : true)
if build_machine.system() == 'linux'
  cpp.has_function('getenv', required : true)
  cpp.has_function('setenv', required : true)
endif

if get_option('use_git')
  git = find_program('git', native: true, required : false)
endif

if get_option('use_git') and git.found()
  # commit macro
  # Git Commit Hashes
  get_commit_hash_long = run_command('git', 'rev-parse', 'HEAD', check: true)
  git_commit_long_hash = get_commit_hash_long.stdout().strip()

  get_commit_hash_short = run_command('git', 'rev-parse', '--short', 'HEAD', check: true)
  git_commit_short_hash = get_commit_hash_short.stdout().strip()

  add_project_arguments('-DPATATA_GIT_HASH_LONG="'+git_commit_long_hash+'"', language : 'cpp')
  add_project_arguments('-DPATATA_GIT_HASH_SHORT="'+git_commit_short_hash+'"', language : 'cpp')

  # Git Branch
  branchCommand = run_command('git', 'branch', '--show-current', check : true)
  branchCOutput = branchCommand.stdout().strip()
  message('Branch:', branchCOutput)

  add_project_arguments('-DPATATA_GIT_BRANCH="'+branchCOutput+'"', language : 'cpp')

  # The commit is Dirty?
  git_work_dir_is_clean_command = run_command('git', 'diff', 'HEAD', '--shortstat', check : true)
  git_work_dir_is_clean_text_out = git_work_dir_is_clean_command.stdout().strip()

  git_work_dir_is_clean = ''
  if git_work_dir_is_clean_text_out != ''
    git_work_dir_is_clean = 'Dirty'
  else
    git_work_dir_is_clean = 'Clean'
  endif

  add_project_arguments('-DPATATA_GIT_WORK_DIR_IS_CLEAN="'+git_work_dir_is_clean+'"', language : 'cpp')

  # The Changes are in the stage?
  git_commit_stage_command = run_command('git', 'diff', 'HEAD', '--shortstat', '--staged', check : true)
  git_commit_stage_text_out = git_commit_stage_command.stdout().strip()

  git_is_commit_in_the_stage = ''
  if git_commit_stage_text_out != ''
    git_is_commit_in_the_stage = 'Staged'
  else
    git_is_commit_in_the_stage = 'Not Staged'
  endif

  add_project_arguments('-DPATATA_GIT_WORK_DIR_IS_STAGED="'+git_is_commit_in_the_stage+'"', language : 'cpp')
endif

if get_option('default_library') == 'shared' or get_option('default_library') == 'both'
  add_project_arguments('-DSHARED_LIBRARY_EXPORT_DEFINE=1', language : 'cpp')
endif

ninja = find_program('ninja', native: true, required : true)

if cpp.get_id() == 'gcc'
  compiler = find_program('g++', native: true, required : true)
elif cpp.get_id() == 'clang'
  compiler = find_program('clang++', native: true, required : true)
elif cpp.get_id() == 'msvc'
  compiler = find_program('cl', native: true, required : true)
endif

fs = import('fs')
compiler_name = fs.name(compiler.full_path())

# Macros
add_project_arguments(
  '-DPATATA_BUILD_SYSTEM="Meson"',
  '-DPATATA_BUILD_SYSTEM_VERSION="'+meson.version()+'"',
  '-DPATATA_BUILD_SYSTEM_GENERATOR="Ninja"',
  '-DPATATA_BUILD_SYSTEM_GENERATOR_VERSION="'+ninja.version()+'"',
  '-DPATATA_ENGINE_VERSION="'+meson.project_version()+'"',
  '-DPATATA_ENGINE_NAME="'+meson.project_name()+'"',
  '-DPATATA_COMPILER_PROGRAM="'+compiler_name+'"',
  '-DPATATA_COMPILER_VERSION="'+compiler.version()+'"',
  '-DPATATA_ARCH="'+build_machine.cpu_family()+'"',
  '-DPATATA_LINUX_XORG_SUPPORT=1',
  language : 'cpp')

# Build Type macro
if (get_option('buildtype') == 'release')
  add_project_arguments('-DPATATA_BUILD_TYPE="Release"', language : 'cpp')
elif (get_option('buildtype') == 'debug')
  add_project_arguments('-DPATATA_BUILD_TYPE="Debug"', '-DDEBUG=1', language : 'cpp')
elif (get_option('buildtype') == 'debugoptimized')
  add_project_arguments('-DPATATA_BUILD_TYPE="Debug Optimized"', '-DDEBUG=1', language : 'cpp')
elif (get_option('buildtype') == 'minsize')
  add_project_arguments('-DPATATA_BUILD_TYPE="Minimal Size Release"', language : 'cpp')
endif

if cpp.get_id() == 'gcc'
  cpp.check_header('cxxabi.h', required : true)
endif

cpp.check_header('algorithm', required : true)
cpp.check_header('cstring', required : true)
cpp.check_header('tuple', required : true)

c = meson.get_compiler('c')
if target_machine.system() == 'windows'
  c.check_header('windows.h', required : true)
endif

Glad2_dep = subproject('Glad2').get_variable('Glad2_dep')

if Glad2_dep.found()
  cpp.has_header('glad/gl.h', include_directories : include_directories('externals/Glad2/include'), required : true)
  cpp.has_header_symbol('glad/gl.h', 'GLADloadfunc', include_directories : include_directories('externals/Glad2/include'), required : true)
  cpp.has_header_symbol('glad/gl.h', 'gladLoadGL', include_directories : include_directories('externals/Glad2/include'), required : true)
endif

Fast_io_dep = subproject('fast_io').get_variable('fast_io_dep')

if Fast_io_dep.found()
  cpp.check_header('fast_io.h', dependencies : Fast_io_dep, required : true)
  cpp.has_header_symbol('fast_io.h', 'fast_io::io::print', dependencies : Fast_io_dep, required : true)
  cpp.has_header_symbol('fast_io.h', 'fast_io::io::println', dependencies : Fast_io_dep, required : true)
  cpp.has_header_symbol('fast_io.h', 'fast_io::io::perr', dependencies : Fast_io_dep, required : true)
  cpp.has_header_symbol('fast_io.h', 'fast_io::io::perrln', dependencies : Fast_io_dep, required : true)
  cpp.has_header_symbol('fast_io.h', 'fast_io::mnp::hex', dependencies : Fast_io_dep, required : true)
endif

sdl2_dep = dependency('sdl2',
  required : true,
  static : false,
  #version : '>=2.28.4',
  modules : ['SDL2::SDL2'])

if sdl2_dep.found()
  c.check_header('SDL.h', dependencies : sdl2_dep, required : true)
  c.check_header('SDL_vulkan.h', dependencies : sdl2_dep, required : true)
  c.check_header('SDL_opengl.h', dependencies : sdl2_dep, required : true)
  c.has_function('SDL_Vulkan_CreateSurface', dependencies : sdl2_dep, required : true)
  c.has_function('SDL_GL_CreateContext', dependencies : sdl2_dep, required : true)
endif

Vulkan = dependency('Vulkan',
  static : false,
  required : true)

if Vulkan.found()
  cpp.check_header('vulkan/vulkan.hpp', dependencies : Vulkan, required : true)
  cpp.has_header_symbol('vulkan/vulkan.hpp', 'vk::createInstance', dependencies : Vulkan, required : true)
  cpp.has_header_symbol('vulkan/vulkan.hpp', 'vkCreateDevice', dependencies : Vulkan, required : true)
  cpp.has_header_symbol('vulkan/vulkan.hpp', 'vkEnumeratePhysicalDevices', dependencies : Vulkan, required : true)
  cpp.has_header_symbol('vulkan/vulkan.hpp', 'vkCreateSwapchainKHR', dependencies : Vulkan, required : true)
  cpp.has_header_symbol('vulkan/vulkan.hpp', 'vkGetSwapchainImagesKHR', dependencies : Vulkan, required : true)
  cpp.has_header_symbol('vulkan/vulkan.hpp', 'vk::to_string', dependencies : Vulkan, required : true)
endif

yamlcpp = dependency('yaml-cpp',
  static : false,
  required : true)

if yamlcpp.found()
  cpp.check_header('yaml-cpp/yaml.h', dependencies : yamlcpp, required : true)
  cpp.has_header_symbol('yaml-cpp/yaml.h', 'YAML::LoadFile', dependencies : yamlcpp, required : true)
endif

add_project_arguments(
  '-DPATATA_FAST_IO_GIT_COMMIT_HASH_SHORT="'+Fast_io_dep.version()+'"',
  '-DPATATA_YAML_CPP_VERSION="'+yamlcpp.version()+'"',
  '-DPATATA_VULKAN_LOADER_VERSION="'+Vulkan.version()+'"',
  language : 'cpp')

dependencies = [Vulkan, Fast_io_dep, sdl2_dep, yamlcpp, Glad2_dep]

if (get_option('buildtype') == 'debug' or get_option('buildtype') == 'debugoptimized')
  imgui_dep = subproject('imgui').get_variable('imgui_dep')

  add_project_arguments('-DPATATA_IMGUI_VERSION="'+imgui_dep.version()+'"', language : 'cpp')

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
  add_project_arguments('-DPATATA_GAME_NAME="'+get_option('game_name')+'"', language : 'cpp')
endif

subdir('data/assets')
subdir('data')

include = include_directories('include/')
subdir('src')
