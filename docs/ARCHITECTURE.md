# NUKE-PRO Architecture

## System Overview

NUKE-PRO es una arquitectura nodal profesional de composición VFX con los siguientes componentes principales:

```
┌─────────────────────────────────────────┐
│          Main Application (Qt)          │
└─────────────────────────────────────────┘
        ↓              ↓              ↓
  ┌──────────┐  ┌───────────┐  ┌──────────┐
  │ Viewer   │  │ Node      │  │Timeline  │
  │ Panel    │  │ Graph     │  │ Panel    │
  └──────────┘  │ Panel     │  └──────────┘
                └───────────┘
        ↓              ↓              ↓
  ┌──────────────────────────────────────┐
  │       Node Graph Core Engine         │
  │  ┌──────────────────────────────┐   │
  │  │   Node System                │   │
  │  │  • NodeBase                  │   │
  │  │  • NodeInput/Output          │   │
  │  │  • Connection Management     │   │
  │  └──────────────────────────────┘   │
  │                                      │
  │  ┌──────────────────────────────┐   │
  │  │   Evaluation Engine          │   │
  │  │  • Topological Sort          │   │
  │  │  • Frame Evaluation          │   │
  │  │  • Caching System            │   │
  │  └──────────────────────────────┘   │
  └──────────────────────────────────────┘
        ↓              ↓              ↓
  ┌──────────┐  ┌───────────┐  ┌──────────┐
  │   CPU    │  │    GPU    │  │ I/O      │
  │Processing│  │Processing │  │Operations│
  └──────────┘  └───────────┘  └──────────┘
        ↓              ↓              ↓
  ┌──────────────────────────────────────┐
  │    OpenCV | CUDA | OpenEXR | OCIO   │
  └──────────────────────────────────────┘
```

## Core Components

### Node System (C++)

#### NodeBase
- Clase base para todos los nodos
- Gestión de inputs/outputs
- Sistema de propiedades
- Ejecución y caché
- Serialización

#### Node Types
- **Read**: Lectura de medios
- **Write**: Escritura de secuencias
- **Merge**: Composición (15+ blend modes)
- **Transform**: Transformaciones 2D
- **Blur**: Desenfoque profesional
- **Grade**: Corrección de color
- **Keyer**: Extracción de alpha
- **Roto**: Rotoscopia
- **Tracker**: Motion tracking

### Node Graph (C++)

#### NodeGraph
- Gestión de red de nodos
- Detección de ciclos
- Ordenamiento topológico
- Evaluación de frames
- Gestión de dependencias

### Processing Engine (C++)

#### Image Processor
- Procesamiento de imágenes
- Operaciones pixel-level
- Blend modes
- Filtros

#### Color Manager
- OpenColorIO integration
- Color space management
- LUT applications

### GPU Acceleration (C++/CUDA)

#### CUDA Kernels
- Operaciones vectoriales
- Transformaciones
- Filtros
- Blend modes

### UI System (Qt/PySide6)

#### Main Window
- Interfaz principal
- Gestor de paneles
- Menús y toolbars

#### Panels
- **Node Graph Panel**: Visualización de nodos
- **Properties Panel**: Edición de propiedades
- **Timeline Panel**: Navegación temporal
- **Viewer Panel**: Vista previa
- **Media Panel**: Gestor de medios

### Python Scripting (Python)

#### Bindings
- Acceso a nodos vía Python
- Automatización
- Plugins

## Execution Flow

1. **User Input**: Usuario conecta nodos en el graph
2. **Graph Analysis**: El sistema detecta ciclos y ordena topológicamente
3. **Frame Request**: Se solicita renderizado de un frame
4. **Dependency Resolution**: Se ejecutan nodos en orden de dependencias
5. **Node Execution**: Cada nodo procesa su input
6. **Cache Management**: Resultados se cachean
7. **Viewer Update**: La vista previa se actualiza
8. **Export**: Opcionalmente exportar a disco

## Performance Optimization

### Caching Strategy
- Frame cache con LRU eviction
- Tile-based caching
- GPU texture caching

### GPU Processing
- CUDA for heavy operations
- OpenGL for real-time preview
- Async processing

### Multithreading
- Thread pool para node execution
- Parallel frame evaluation
- Non-blocking UI

## Data Flow

```
Read Node
    ↓ (cv::Mat 4-channel float)
Merge Node  ← Merge Node inputs
    ↓ (cv::Mat 4-channel float)
Blur Node
    ↓ (cv::Mat 4-channel float)
Grade Node
    ↓ (cv::Mat 4-channel float)
Write Node
    ↓ (Save to disk)
```

## File Structure

```
src/
├── core/           # C++ core engine
│   ├── nodes/      # Node implementations
│   ├── graph/      # Node graph system
│   ├── processing/ # Image processing
│   ├── cache/      # Caching system
│   └── engine/     # Evaluation engine
├── gpu/            # GPU acceleration
│   ├── cuda/       # CUDA kernels
│   └── opengl/     # OpenGL utilities
├── ui/             # Qt/PySide6 interface
│   ├── panels/     # UI panels
│   ├── widgets/    # Custom widgets
│   └── theme/      # Theming system
├── python/         # Python bindings
└── plugins/        # Plugin system
```

## Design Patterns

### Factory Pattern
- Node creation via factory

### Observer Pattern
- Property change notifications
- UI updates

### Decorator Pattern
- GPU processing decorators

### Chain of Responsibility
- Node execution chain
- Event handling

## Thread Model

- **Main Thread**: UI event loop
- **Worker Threads**: Node processing
- **GPU Thread**: CUDA operations
- **I/O Thread**: File operations

## Memory Management

- Smart pointers (std::shared_ptr, std::unique_ptr)
- Automatic cleanup
- Memory pooling for node execution
- LRU cache eviction
