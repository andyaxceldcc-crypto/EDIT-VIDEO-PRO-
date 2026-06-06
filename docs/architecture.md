# Arquitectura del Compositor VFX

## Visión General

La aplicación utiliza una arquitectura modular basada en:
1. **Core Engine (C++)**: Motor de composición y gestión de nodos
2. **Rendering Pipeline**: GPU-accelerated processing
3. **UI Layer (Qt/PySide)**: Interfaz gráfica profesional
4. **Python API**: Scripting y extensión

## Componentes Principales

### 1. Node Graph (src/core/NodeGraph.h)

Gestor central del DAG (Directed Acyclic Graph):

```
┌─────────────┐
│  ReadNode   │
└──────┬──────┘
       │
       ▼
┌─────────────┐     ┌─────────────┐
│ TransNode   │────▶│ MergeNode   │
└─────────────┘     └──────┬──────┘
       │                   │
       ▼                   ▼
┌─────────────┐     ┌─────────────┐
│ GradeNode   │────▶│ WriteNode   │
└─────────────┘     └─────────────┘
```

**Responsabilidades**:
- Almacenar y gestionar nodos
- Validar conexiones (sin ciclos)
- Evaluar grafo en orden topológico
- Caché de resultados
- Serialización (save/load)

### 2. Node Base Class (src/core/Node.h)

Clase abstracta para todos los nodos:

```cpp
class Node {
    // Identidad
    virtual std::shared_ptr<FrameBuffer> compute(int frame) = 0;
    
    // Conectores
    void addInput(const std::string& name, InputType type);
    void addOutput(const std::string& name, OutputType type);
    
    // Propiedades (Knobs)
    void setKnob(const std::string& name, const std::variant<...>& value);
    
    // Conexiones
    bool connectInput(int index, Node* source, int sourceOutput);
};
```

**Tipos de Nodos**:
- **Source Nodes**: Read, Generator
- **Process Nodes**: Transform, Grade, Blur
- **Composite Nodes**: Merge, Keyer
- **Sink Nodes**: Write

### 3. Frame Buffer (src/core/FrameBuffer.h)

Almacenamiento de imágenes/frames:

**Formatos Soportados**:
- RGBA8: 8-bit per channel
- RGBA16: 16-bit half-float
- RGBAF32: 32-bit float (default)

**Memoria**:
- CPU: Direct access
- GPU: OpenGL texture / CUDA device pointer
- Lazy transfer: CPU ↔ GPU on demand

### 4. Node Implementations

#### ReadNode
```cpp
- Inputs: (none)
- Outputs: image
- Knobs: filepath, startFrame, endFrame, missingFrameMode
- Logic: Load EXR/TIFF from disk
```

#### WriteNode
```cpp
- Inputs: image
- Outputs: (none)
- Knobs: filepath, format, bitDepth
- Logic: Write composite to disk
```

#### MergeNode
```cpp
- Inputs: A (image), B (image)
- Outputs: image
- Knobs: operation (over, add, multiply...), mix
- Logic: Blend two images
```

#### TransformNode
```cpp
- Inputs: image
- Outputs: image
- Knobs: translate(x,y), rotate, scale, pivot
- Logic: 2D transformation matrix
```

#### BlurNode
```cpp
- Inputs: image
- Outputs: image
- Knobs: radius, type (gaussian, box, motion)
- Logic: GPU-accelerated blur kernel
```

### 5. UI Layer

#### MainWindow (src/ui/MainWindow.h)
Ventana principal con:
- Menu bar (File, Edit, View, Help)
- Dockable panels
- Drag-and-drop files
- Project auto-save

#### NodeGraphWidget (src/ui/NodeGraphWidget.h)
Editor visual:
- Representación gráfica de nodos
- Edición interactiva (drag, connect, delete)
- Context menu (add node, delete, properties)
- Zoom y pan
- Selection y highlighting

#### ViewerWidget (src/ui/ViewerWidget.h)
Visor de renderizado:
- OpenGL rendering
- Real-time display
- Zoom/pan controls
- Fit-to-window options
- Pixel inspection

#### PropertiesPanel (src/ui/PropertiesPanel.h)
Inspector de propiedades:
- Parámetros dinámicos
- Sliders y spinboxes
- Color pickers
- Timeline para animación
- Undo/Redo

## Evaluation Pipeline

```
1. USER ACTION (play frame, edit parameter)
   ↓
2. INVALIDATE CACHE
   ↓
3. TOPOLOGICAL SORT
   ↓
4. EVALUATE NODES (in order)
   ├─ Check inputs
   ├─ Compute (CPU or GPU)
   ├─ Cache result
   ├─ Update UI
   └─ Progress callback
   ↓
5. RENDER TO VIEWER
   ↓
6. DISPLAY FRAME
```

## GPU Acceleration

### OpenGL Pipeline
```
FrameBuffer (CPU) → OpenGL Texture → Shader Program → Display
```

### CUDA Pipeline (Optional)
```
FrameBuffer → CUDA Device Memory → CUDA Kernel → CUDA Device Memory → OpenGL Texture
```

### Kernel Examples
```cuda
// Gaussian Blur
__global__ void blur_kernel(const float* input, float* output,
                           int width, int height, float radius);

// Color Grade
__global__ void grade_kernel(const float* input, float* output,
                            int width, int height,
                            float lift, float gamma, float gain);

// Merge/Composite
__global__ void merge_kernel(const float* a, const float* b, float* output,
                            int width, int height, int blendMode, float mix);
```

## Memory Management

### Strategy
1. **Smart Pointers**: std::shared_ptr<> para referencia counting
2. **Frame Cache**: LRU cache de últimos N frames
3. **Lazy Loading**: CPU ↔ GPU transfer on demand
4. **Memory Pooling**: Pre-allocate buffer pools

### Ejemplo Cache
```cpp
std::unordered_map<std::string, // nodeId
    std::unordered_map<int,  // frame
        std::shared_ptr<FrameBuffer>>> frameCache;

// LRU eviction
const size_t MAX_CACHED_FRAMES = 100;
```

## Threading Model

### Main Thread
- UI events
- File I/O
- Composition evaluation

### Worker Thread(s)
- Render jobs
- File operations
- Heavy computations

### Thread-Safe Components
```cpp
class NodeGraph {
    std::mutex graphMutex;        // Protege DAG
    std::mutex cacheMutex;        // Protege cache
};
```

## Serialization Format

### JSON Project File
```json
{
  "version": "0.1.0",
  "frameRange": { "start": 1, "end": 100 },
  "nodes": [
    {
      "id": "Read_1",
      "type": "Read",
      "name": "Background",
      "position": { "x": 100, "y": 100 },
      "knobs": {
        "filepath": "/path/to/sequence.####.exr",
        "startFrame": 1
      }
    },
    {
      "id": "Merge_1",
      "type": "Merge",
      "name": "Composite",
      "position": { "x": 300, "y": 100 },
      "knobs": { "operation": "over", "mix": 1.0 }
    }
  ],
  "connections": [
    { "source": "Read_1", "sourceOutput": 0,
      "target": "Merge_1", "targetInput": 0 }
  ]
}
```

## Plugin System

### Plugin API
```cpp
class IPlugin {
    virtual std::string getName() = 0;
    virtual std::shared_ptr<Node> createNode(const std::string& name) = 0;
};
```

### Plugin Discovery
1. Escanear directorio `plugins/`
2. Cargar .dll/.so/.dylib
3. Validar ABI
4. Registrar en Node Factory

## Performance Targets

- 4K @ 24fps real-time
- Sub-16ms latency per node
- < 2GB memory for 4K sequences
- GPU acceleration > 2x speedup vs CPU

---

**Última Actualización**: 2026-06-06
