This project uses Cmake and Meson to compile itself

# Linux
Before setting up the project make sure you have the necessary packages to compile.

### Fedora
```bash
sudo dnf install meson gcc gcc-c++ ninja-build git
```
### Debian

```bash
sudo apt install build-essential ninja-build g++ gcc gcc meson git
```

and now get the libraries.

### Fedora
```bash
sudo dnf install SDL2-devel SDL2_image-devel vulkan-headers vulkan-loader-devel vulkan-validation-layers-devel vulkan-validation-layers-devel
```

### Debian
```bash
sudo apt install libsdl2-dev libsdl2-image-2.0-0 libvulkan-dev vulkan-validationlayers vulkan-validationlayers-dev
```

Clone the repository

```bash
git clone https://gitlab.com/448L/patata-engine && cd "patata-engine"
```

if the `build` folder is not there create it.

```bash
mkdir build
```

### Meson

configure the project. `Release` is selected by default.

```bash
meson setup build
```

and compile with `ninja` using multiple cores.

```bash
meson compile -C build -j$(nproc)
```

or using a single core.

```bash
meson compile -C build
```

will find the executable in `build/`.

### Cmake

if the `build` folder is not there create it.

```bash
mkdir build
```

configure the project. `Release` is selected by default.

```bash
cmake -B build
```

Alternatively you can use ninja with cmake, make sure you have `ninja-build` installed.

```bash
cmake -B build -G ninja
```

to compile and link to multiple cores

```bash
cmake --build build --config Release -j$(nproc)
```

or using a single kernel.

```bash
meson compile -C build
```

will find the executable in ``build/`.

alternatively you can compile the libraries together with potato engine and link them. if you do this, you must satisfy the dependencies of the third party libraries.

but first, clone the repository with its submodules.

```bash
git clone --recurse-submodules https://gitlab.com/Sendan/patata-engine.git
```

if you already have the repository and you don't have the submodules

```bash
git submodule update --init --recursive
```
configure the project

```bash
cmake -B build -DUSE_EXTERNAL_LIBS=ON
```

you can also try to do static linking if possible (not all libraries can be statically linked)

```bash
cmake -B build -DUSE_EXTERNAL_LIBS=ON -DSHARED_BUILD=OFF
```
