#!/usr/bin/env python3
"""Simple workflow example"""

from edit_video_pro.api import NodeGraph, Node
from edit_video_pro.nodes import ReadNode, WriteNode, MergeNode, GradeNode

def main():
    # Create node graph
    graph = NodeGraph()
    
    # Create nodes
    read1 = graph.add_node("Read", "Background")
    read1.set_knob("filepath", "/path/to/background.####.exr")
    read1.set_knob("startFrame", 1)
    read1.set_knob("endFrame", 100)
    
    read2 = graph.add_node("Read", "Foreground")
    read2.set_knob("filepath", "/path/to/foreground.####.exr")
    
    # Composite
    merge = graph.add_node("Merge", "Composite")
    merge.set_knob("operation", "over")
    merge.set_knob("mix", 1.0)
    
    # Grade
    grade = graph.add_node("Grade", "ColorCorrection")
    grade.set_knob("lift", 0.0)
    grade.set_knob("gamma", 1.0)
    grade.set_knob("gain", 1.0)
    
    # Write
    write = graph.add_node("Write", "Output")
    write.set_knob("filepath", "/path/to/output.####.exr")
    write.set_knob("format", "exr")
    write.set_knob("bitDepth", 16)
    
    # Connect
    graph.connect(read1.node_id, 0, merge.node_id, 0)  # bg to merge
    graph.connect(read2.node_id, 0, merge.node_id, 1)  # fg to merge
    graph.connect(merge.node_id, 0, grade.node_id, 0)  # merge to grade
    graph.connect(grade.node_id, 0, write.node_id, 0)  # grade to write
    
    # Evaluate for frame range
    for frame in range(1, 101):
        print(f"Processing frame {frame}/100...")
        graph.evaluate_all(frame)
    
    print("Done!")
    
    # Save project
    graph.save("/path/to/project.evp")

if __name__ == "__main__":
    main()
