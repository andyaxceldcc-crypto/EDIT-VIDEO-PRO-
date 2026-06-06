# Build Instructions

## Quick Start

```bash
git clone https://github.com/andyaxceldcc-crypto/EDIT-VIDEO-PRO-.git
cd EDIT-VIDEO-PRO-
git checkout develop/vfx-compositor
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_CUDA=ON ..
cmake --build . -j$(nproc)
./bin/nuke-pro
```

## Detailed Build Process

### Prerequisites Installation

#### Ubuntu 22.04
```bash
sudo apt-get update
sudo apt-get install -y \
    cmake \
    git \
    build-essential \
    python3-dev \
    python3-pip \
    libqt6core6 \
    libqt6gui6 \
    libqt6opengl6 \
    libqt6openglwidgets6 \
    qt6-tools \
    libopenexr-dev \
    libopencolorio-dev \
    libopencv-dev

# CUDA (optional)
wget https://developer.nvidia.com/downloads/cuda-11-8-0-local_linux-x86_64.rpm
sudo dpkg -i cuda-11-8-0-local_linux-x86_64.deb
```

#### macOS
```bash
brew install cmake python@3.11 qt6 openexr opencolorio opencv
```

#### Windows (Visual Studio 2022)
- Visual Studio 2022 Community Edition
- CMake 3.20+ (include in PATH)
- Python 3.11
- Qt 6.5 Online Installer
- CUDA Toolkit 11.8 (optional)

### Build Configuration

#### CPU Only
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release -j$(nproc)
```

#### With CUDA
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_CUDA=ON -DCUDA_ARCH_BIN="75;86;89" ..
cmake --build . --config Release -j$(nproc)
```

#### Debug Build
```bash
mkdir build-debug && cd build-debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug
```

### Running Tests

```bash
cd build
ctest --verbose

# Or individual test
./tests/core_tests
./tests/ui_tests
```

### Installation

```bash
cmake --install . --prefix /opt/nuke-pro
# or
sudo make install
```

## Troubleshooting

### Qt6 Not Found
```bash
cmake -DCMAKE_PREFIX_PATH=/opt/qt6 ..
```

### CUDA Build Errors
```bash
# Check CUDA installation
nvcc --version

# Check compute capabilities
./deviceQuery
```

### Memory Issues During Build
```bash
# Build with less parallelism
cmake --build . -j 1
```

## CI/CD Pipeline

See `.github/workflows/` for GitHub Actions configuration.

- Build on: Linux (GCC/Clang), macOS (Clang), Windows (MSVC)
- Test on every commit
- Release builds on tags
