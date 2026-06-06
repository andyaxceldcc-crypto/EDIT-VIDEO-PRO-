#pragma once

#include <memory>
#include <cstring>

/**
 * @class FrameBuffer
 * @brief Almacenamiento de frame/imagen
 */
class FrameBuffer {
public:
    enum class Format {
        RGBA8,      // 8-bit per channel
        RGBA16,     // 16-bit per channel (half)
        RGBAF32,    // 32-bit float per channel
    };

    FrameBuffer(int width, int height, Format format);
    ~FrameBuffer();

    // Propiedades
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    Format getFormat() const { return format; }
    int getChannels() const { return 4; } // RGBA
    size_t getDataSize() const { return dataSize; }

    // Datos
    uint8_t* getData() { return data.get(); }
    const uint8_t* getData() const { return data.get(); }
    
    // GPU handle (para OpenGL/CUDA)
    unsigned int getGLTexture() const { return glTexture; }
    void setGLTexture(unsigned int texture) { glTexture = texture; }
    void* getCUDADevicePtr() const { return cudaDevicePtr; }
    void setCUDADevicePtr(void* ptr) { cudaDevicePtr = ptr; }

    // Utilidades
    float getPixel(int x, int y, int channel) const;
    void setPixel(int x, int y, int channel, float value);
    void clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
    
    // Copy
    void copyFrom(const FrameBuffer& other);
    void copyFromGPU();
    void copyToGPU();

private:
    int width, height;
    Format format;
    size_t dataSize;
    std::unique_ptr<uint8_t[]> data;
    
    unsigned int glTexture = 0;
    void* cudaDevicePtr = nullptr;

    int getBytesPerPixel() const;
};
