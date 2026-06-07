

---

## 🔗 Sistema node-based (Nuke-like)

He añadido un sistema básico de nodos inspirado en Foundry Nuke para empezar a construir pipelines de composición y efectos.

Qué incluye:
- `core/src/node.h/cpp` : Clase base Node (parámetros, conexiones, posición, interfaz virtual process/getOutput)
- `core/src/connection.h/cpp` : Clase Connection (conecta nodos entre puertos)
- `core/src/node_graph.h/cpp` : NodeGraph para gestionar nodos y ejecutar el pipeline (orden topológico simple)
- `core/src/nodes/` : Nodos de ejemplo
  - `readnode` : Nodo de entrada (simula lectura de frames)
  - `blur_effect` : Nodo de ejemplo que simula un desenfoque
  - `writenode` : Nodo de salida (simula escritura a disco)
- `core/examples/simple_pipeline.cpp` : Ejemplo mínimo de cómo construir un grafo Read -> Blur -> Write (archivo de ejemplo no integrado automáticamente en la build)

Cómo compilar (ya agregado al CMakeLists.txt):

Windows / macOS / Linux (con Qt6 y CMake configurados):

```bash
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="/ruta/a/Qt/6.6.2" 
cmake --build . --config Release
```

El ejecutable principal `FilmoraEditor` incluirá los módulos del sistema node-based. El ejemplo `core/examples/simple_pipeline.cpp` es una utilidad de referencia; puedes integrarlo como ejecutable de pruebas si lo deseas.

Ejemplo rápido (en código) de cómo construir un pipeline (ver `core/examples/simple_pipeline.cpp`):

1. Crear nodos: ReadNode, BlurEffect, WriteNode
2. Conectar: read -> blur -> write
3. Ejecutar: llamar a `NodeGraph::execute()` para procesar en orden

Notas y limitaciones actuales:
- Implementación de ejemplo y didáctica: las operaciones de E/S (lectura/escritura) y procesamiento son simuladas (placeholders). Para producción, integrar FFmpeg/libav o APIs de GPU.
- El sistema permite añadir nodos personalizados heredando de `Node`.
- El orden de ejecución se resuelve con un algoritmo simple; puede mejorarse con un ordenamiento topológico robusto y detección de ciclos.

Si quieres que integre lectura/escritura real con FFmpeg, o que añada un ejecutable de test que compile automáticamente, lo hago en el siguiente cambio.

---
