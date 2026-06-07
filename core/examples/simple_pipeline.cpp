#include <iostream>
#include <memory>
#include "../core/src/nodes/readnode.h"
#include "../core/src/nodes/blur_effect.h"
#include "../core/src/nodes/writenode.h"
#include "../core/src/node_graph.h"

int main_example_simple_pipeline() {
    auto read = std::make_shared<ReadNode>("ReadClip");
    read->setParameter("path", QVariant("/media/video.mp4"));

    auto blur = std::make_shared<BlurEffect>("Blur1");
    blur->setParameter("radius", QVariant("5"));

    auto write = std::make_shared<WriteNode>("WriteOut");
    write->setParameter("outpath", QVariant("/tmp/out.mp4"));

    NodeGraph graph;
    graph.addNode(read);
    graph.addNode(blur);
    graph.addNode(write);

    graph.connect(read, 0, blur, 0);
    graph.connect(blur, 0, write, 0);

    graph.execute();

    std::cout << "Pipeline ejecutado. Salida escrita (simulada)." << std::endl;
    return 0;
}

// Nota: Este archivo es un ejemplo y no está integrado automáticamente en la build.
