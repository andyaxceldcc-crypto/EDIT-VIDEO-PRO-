# Guía de Desarrollo de Nodos

## Crear un Nodo Personalizado (C++)

### Estructura Base

```cpp
#pragma once
#include "../core/Node.h"
#include <memory>

class FrameBuffer;

/**
 * @class CustomNode
 * @brief Descripción del nodo
 */
class CustomNode : public Node {
public:
    CustomNode(const std::string& nodeName = "Custom");
    virtual ~CustomNode() = default;

    std::shared_ptr<FrameBuffer> compute(int frame) override;

private:
    // Parámetros privados
    float parameter1 = 0.5f;
    int parameter2 = 100;
};
```

### Implementación

```cpp
#include "CustomNode.h"
#include "../core/FrameBuffer.h"

CustomNode::CustomNode(const std::string& nodeName)
    : Node("Custom", nodeName) {
    
    // Definir inputs
    addInput("image", InputType::IMAGE);
    
    // Definir outputs
    addOutput("image", OutputType::IMAGE);
    
    // Definir propiedades (knobs)
    Knob param1;
    param1.name = "Intensity";
    param1.type = "float";
    param1.value = 1.0f;
    param1.minValue = 0.0f;
    param1.maxValue = 2.0f;
    knobs.push_back(param1);
}

std::shared_ptr<FrameBuffer> CustomNode::compute(int frame) {
    // Obtener input
    auto inputNode = getInputNode(0);
    if (!inputNode) {
        // Node sin conexión - retornar frame negro
        return std::make_shared<FrameBuffer>(1024, 1024, FrameBuffer::Format::RGBAF32);
    }
    
    // Compute input
    auto inputFrame = inputNode->compute(frame);
    if (!inputFrame) return nullptr;
    
    // Crear output frame
    auto outputFrame = std::make_shared<FrameBuffer>(
        inputFrame->getWidth(),
        inputFrame->getHeight(),
        FrameBuffer::Format::RGBAF32
    );
    
    // Obtener parámetro
    auto intensityIt = std::find_if(knobs.begin(), knobs.end(),
        [](const Knob& k) { return k.name == "Intensity"; });
    
    float intensity = 1.0f;
    if (intensityIt != knobs.end()) {
        intensity = std::get<float>(intensityIt->value);
    }
    
    // Procesar frame (CPU)
    const uint8_t* inputData = inputFrame->getData();
    uint8_t* outputData = outputFrame->getData();
    int width = inputFrame->getWidth();
    int height = inputFrame->getHeight();
    
    #pragma omp parallel for collapse(2)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int pixelIndex = (y * width + x) * 4;
            
            for (int c = 0; c < 4; ++c) {
                float value = inputData[pixelIndex + c] / 255.0f;
                value *= intensity;
                outputData[pixelIndex + c] = static_cast<uint8_t>(value * 255.0f);
            }
        }
    }
    
    return outputFrame;
}
```

## Crear un Nodo Personalizado (Python)

```python
from edit_video_pro.plugin import Node, Input, Output
from edit_video_pro.api import InputType, OutputType
import numpy as np

class CustomPythonNode(Node):
    def __init__(self, name="CustomPython"):
        super().__init__("CustomPython", name)
        
        # Inputs
        self.add_input("image", InputType.IMAGE)
        
        # Outputs
        self.add_output("image", OutputType.IMAGE)
        
        # Knobs
        self.set_knob("intensity", 1.0)
        self.set_knob("contrast", 1.0)
    
    def compute(self, frame):
        # Get input
        input_frame = self.inputs[0].connected_node.compute(frame)
        if not input_frame:
            return None
        
        # Convert to numpy
        data = input_frame.to_numpy()  # Shape: (H, W, 4)
        
        # Process
        intensity = self.get_knob("intensity")
        contrast = self.get_knob("contrast")
        
        # Apply effect
        output = data.copy().astype(np.float32)
        output = output * intensity
        output = np.power(output, 1.0 / contrast)
        output = np.clip(output, 0, 255).astype(np.uint8)
        
        # Create output frame
        return FrameBuffer.from_numpy(output)
```

## Registro de Nodos

### En C++

```cpp
// src/nodes/NodeFactory.h
#include <map>
#include <memory>
#include <functional>

class NodeFactory {
public:
    static NodeFactory& instance() {
        static NodeFactory factory;
        return factory;
    }
    
    using Creator = std::function<std::shared_ptr<Node>(const std::string&)>;
    
    void registerNodeType(const std::string& type, Creator creator) {
        creators[type] = creator;
    }
    
    std::shared_ptr<Node> create(const std::string& type, const std::string& name) {
        auto it = creators.find(type);
        if (it != creators.end()) {
            return it->second(name);
        }
        return nullptr;
    }
    
private:
    std::map<std::string, Creator> creators;
};

// Registrar nodos
NodeFactory::instance().registerNodeType(
    "CustomNode",
    [](const std::string& name) { return std::make_shared<CustomNode>(name); }
);
```

### En Python

```python
# plugins/custom_nodes.py
from edit_video_pro.api import Node

class CustomNode(Node):
    pass

# Auto-register
__all__ = ['CustomNode']
```

## GPU Acceleration (CUDA)

```cpp
// GPU kernel
__global__ void customKernel(
    const float* input,
    float* output,
    int width, int height,
    float intensity
) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;
    
    if (x < width && y < height) {
        int pixelIdx = (y * width + x) * 4;
        
        for (int c = 0; c < 4; ++c) {
            output[pixelIdx + c] = input[pixelIdx + c] * intensity;
        }
    }
}

// Host code en compute()
void* d_input = inputFrame->getCUDADevicePtr();
void* d_output = outputFrame->getCUDADevicePtr();

dim3 blockSize(16, 16);
dim3 gridSize(
    (width + blockSize.x - 1) / blockSize.x,
    (height + blockSize.y - 1) / blockSize.y
);

customKernel<<<gridSize, blockSize>>>(
    (float*)d_input, (float*)d_output,
    width, height, intensity
);

cudaDeviceSynchronize();
outputFrame->copyFromGPU();
```

## Testing de Nodos

```cpp
// tests/test_custom_node.cpp
#include <gtest/gtest.h>
#include "src/nodes/CustomNode.h"

class CustomNodeTest : public ::testing::Test {
protected:
    CustomNode node{"Test"};
};

TEST_F(CustomNodeTest, ComputeValidInput) {
    // Mock input frame
    auto inputFrame = std::make_shared<FrameBuffer>(100, 100, FrameBuffer::Format::RGBAF32);
    inputFrame->clear(0.5f, 0.5f, 0.5f, 1.0f);
    
    // Mock input node
    // ...
    
    // Compute
    auto output = node.compute(1);
    
    // Assert
    EXPECT_NE(output, nullptr);
    EXPECT_EQ(output->getWidth(), 100);
    EXPECT_EQ(output->getHeight(), 100);
}
```

## Distribución de Plugins

```
plugins/
├── my_plugin/
│   ├── CMakeLists.txt
│   ├── src/
│   │   ├── MyNode.h
│   │   └── MyNode.cpp
│   ├── python/
│   │   └── my_node.py
│   └── plugin.json
│       {
│         "name": "My Custom Plugin",
│         "version": "1.0.0",
│         "author": "Your Name",
│         "nodes": ["MyNode"],
│         "requirements": []
│       }
```

---

**Última Actualización**: 2026-06-06
