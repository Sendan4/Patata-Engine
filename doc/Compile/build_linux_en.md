This project uses Cmake and Meson to compile itself.

# Linux
### Meson
Before configuring the project make sure you have the necessary packages to compile.

### Fedora
```bash
sudo dnf install meson gcc gcc-c++ ninja-build git
```
### Debian

```bash
sudo apt install build-essential ninja-build g++ gcc meson git
```

and now get the libraries.

### Fedora
```bash
sudo dnf install SDL2-devel SDL2_image-devel vulkan-headers vulkan-loader-devel vulkan-validation-layers-devel
```

## Debian
```bash
sudo apt install libsdl2-dev libsdl2-image-2.0-0 libvulkan-dev vulkan-validationlayers vulkan-validationlayers-dev
```

Clone the repository

```bash
git clone https://gitlab.com/448L/patata-engine && cd "patata-engine"
```

if the `build` folder is not present create it.

```bash
mkdir build
```

configure the project. `Release` is selected by default.

```bash
meson setup build && cd build
```

and compile with `ninja` using several cores.

```bash
ninja -j$(nproc)
```

or using a single core.

```bash
ninja
```

you will find the executable in `build/`.

## Cmake

Before configuring the project make sure you have the necessary packages to compile.

### Fedora
```bash
sudo dnf install cmake gcc gcc-c++ make.x86_64 git
```
### Debian

```bash
sudo apt install build-essential make g++ gcc cmake git
```

and now get the libraries.

### Fedora
```bash
sudo dnf install SDL2-devel SDL2_image-devel vulkan-headers vulkan-loader-devel vulkan-validation-layers-devel
```

## Debian
```bash
sudo apt install libsdl2-dev libsdl2-image-2.0-0 libvulkan-dev vulkan-validationlayers vulkan-validationlayers-dev
```

Clone the repository

```bash
git clone https://gitlab.com/448L/patata-engine && cd "patata-engine"
```

if the `build` folder is not present create it.

```bash
mkdir build && cd build
```

configure the project. `Release` is selected by default.

```bash
cmake ..
```

Alternatively you can use ninja with cmake, make sure you have `ninja-build` installed.

```bash
cmake .. -G ninja
```

to compile with ninja using all the cores

```bash
ninja -j$(nproc)
```

Compile with `make` using several cores.
```bash
make -j$(nproc)
```

or using a single core.

```bash
make
```

will find the executable in `bin`

If you want to compile the libraries together with Patata Engine, you must clone the repository and its submodules.

```bash
git clone --recurse-submodules https://gitlab.com/448L/patata-engine.git


```

you must create the build and bin folder if they are not there.

```bash
mkdir build
mkdir bin
cd build
```

configure the project with cmake.

```bash
cmake -DUSE_SYSTEM_LIBS=OFF ..
```

you will have to satisfy the dependencies to compile libraries such as `SDL2`, `SDL2_Image`, `SDL2_TTF`, `libconfig`.

### Static or Dynamic Linking
By default it is dynamically linked, you can use `-DBUILD_TYPE=OFF` to try to link the libraries that allow it statically.

This will not link all libraries statically, because there are libraries that do not support it, such as `libvulkan`.

### Building
```bash
git clone --recurse-submodules https://gitlab.com/448L/patata-engine.git && cd patata-engine
mkdir build && mkdir bin && cd build
cmake .. -DUSE_SYSTEM_LIBS=OFF
make -j$(nproc)
```
