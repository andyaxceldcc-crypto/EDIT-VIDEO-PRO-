# Node API Reference

## NodeBase Class

### Propiedades

```cpp
QString getId() const;
QString getName() const;
NodeType getType() const;
ExecutionStatus getStatus() const;
float getX() const;
float getY() const;
```

### Gestión de Inputs/Outputs

```cpp
// Añadir conexiones
NodeInput* addInput(const QString& name, int channels = 4);
NodeOutput* addOutput(const QString& name, int channels = 4);

// Obtener conexiones
NodeInput* getInput(int index) const;
NodeInput* getInputByName(const QString& name) const;
NodeOutput* getOutput(int index) const;
NodeOutput* getOutputByName(const QString& name) const;

const QVector<NodeInput*>& getInputs() const;
const QVector<NodeOutput*>& getOutputs() const;
```

### Sistema de Propiedades

```cpp
void setProperty(const QString& name, const QVariant& value);
QVariant getProperty(const QString& name) const;
const QMap<QString, QVariant>& getProperties() const;
```

### Ejecución

```cpp
bool execute(int frame = 0);
bool isDirty() const;
void markDirty();
void invalidateCache();
```

### Rango de Frames

```cpp
void setFrameRange(int start, int end);
int getFrameStart() const;
int getFrameEnd() const;
```

## Node Types

### ReadNode

```cpp
void setFilePath(const QString& path);
void setFormat(const QString& format);  // "exr", "mov", "tiff"
void setFrameRange(int first, int last);
void setColorSpace(const QString& colorspace);
void setProxyMode(bool enabled);
void setProxyScale(float scale);
```

### WriteNode

```cpp
void setFilePath(const QString& path);
void setFormat(const QString& format);
void setCodec(const QString& codec);
void setBitrate(int bitrate);
void setFrameRate(float fps);
void setOverwrite(bool overwrite);
```

### MergeNode

```cpp
enum BlendMode {
    OVER, UNDER, SCREEN, MULTIPLY, ADD,
    SUBTRACT, DIVIDE, DIFFERENCE,
    COLOR_DODGE, COLOR_BURN, LIGHTEN, DARKEN,
    OVERLAY, SOFT_LIGHT, HARD_LIGHT
};

void setBlendMode(BlendMode mode);
void setOpacity(float opacity);
void setMaskInput(bool enabled);
```

### TransformNode

```cpp
void setTranslate(float tx, float ty);
void setRotate(float degrees);
void setScale(float scaleX, float scaleY);
void setPivot(float x, float y);
```

### BlurNode

```cpp
enum BlurType { GAUSSIAN, MOTION, RADIAL, BOX, MEDIAN };

void setBlurType(BlurType type);
void setSize(float size);
void setMotionAngle(float angle);
void setMotionLength(float length);
void setRadialCenter(float x, float y);
```

### GradeNode

```cpp
// Lift/Gamma/Gain
void setLift(float r, float g, float b);
void setGamma(float r, float g, float b);
void setGain(float r, float g, float b);

// Shadows/Midtones/Highlights
void setShadows(float r, float g, float b);
void setMidtones(float r, float g, float b);
void setHighlights(float r, float g, float b);

// Overall
void setContrast(float contrast);
void setSaturation(float saturation);
void setExposure(float exposure);
```

### KeyerNode

```cpp
enum KeyerType { CHROMA_KEY, LUMA_KEY, RANGE_KEY, DIFFERENCE_KEY };

void setKeyerType(KeyerType type);
void setKeyColor(float r, float g, float b);
void setThreshold(float threshold);
void setSoftness(float softness);
void setEdgeGrow(float grow);
```

## NodeGraph Class

### Gestión de Nodos

```cpp
void addNode(NodeBase* node);
void removeNode(NodeBase* node);
NodeBase* getNode(const QString& id) const;
NodeBase* getNodeByName(const QString& name) const;
const QVector<NodeBase*>& getAllNodes() const;
```

### Conexiones

```cpp
bool connect(NodeOutput* output, NodeInput* input);
bool disconnect(NodeOutput* output, NodeInput* input);
bool hasCycle() const;
bool wouldCreateCycle(NodeOutput* output, NodeInput* input) const;
```

### Evaluación

```cpp
bool evaluate(int frame);
bool executeNode(NodeBase* node, int frame);
QVector<NodeBase*> getExecutionOrder() const;
```

### Gestión de Output

```cpp
void setOutputNode(NodeBase* node);
NodeBase* getOutputNode() const;
```

### Frame Range

```cpp
void setFrameRange(int start, int end);
int getFrameStart() const;
int getFrameEnd() const;
int getCurrentFrame() const;
```

## Ejemplos de Uso

### Crear un Nodo Read

```cpp
ReadNode* readNode = new ReadNode("plate1");
readNode->setFilePath("/path/to/images/render_####.exr");
readNode->setFormat("exr");
readNode->setFrameRange(1, 100);
graph->addNode(readNode);
```

### Merge de Dos Nodos

```cpp
MergeNode* mergeNode = new MergeNode("composite");
mergeNode->setBlendMode(MergeNode::OVER);
mergeNode->setOpacity(0.8f);

graph->addNode(mergeNode);
graph->connect(readNode->getOutput(0), mergeNode->getInput(0));
```

### Evaluación

```cpp
graph->setOutputNode(mergeNode);
bool success = graph->evaluate(24);  // Frame 24
```
