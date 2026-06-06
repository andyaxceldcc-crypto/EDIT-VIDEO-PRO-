"""Node base class and utilities"""

from enum import Enum
from typing import Any, Dict, List, Tuple
import ctypes

class InputType(Enum):
    IMAGE = 0
    FLOAT = 1
    INT = 2
    BOOL = 3
    COLOR = 4
    CURVE = 5

class OutputType(Enum):
    IMAGE = 0
    FLOAT = 1
    INT = 2
    BOOL = 3
    COLOR = 4

class Input:
    def __init__(self, name: str, type_: InputType):
        self.name = name
        self.type = type_
        self.connected_node = None
        self.connected_output = 0
    
    def connect(self, node: 'Node', output_index: int = 0) -> bool:
        self.connected_node = node
        self.connected_output = output_index
        return True
    
    def disconnect(self):
        self.connected_node = None
        self.connected_output = 0

class Output:
    def __init__(self, name: str, type_: OutputType):
        self.name = name
        self.type = type_
        self.connections = []  # List of (target_node, target_input_index)
    
    def connect(self, target_node: 'Node', target_input_index: int) -> bool:
        self.connections.append((target_node, target_input_index))
        return target_node.inputs[target_input_index].connect(self.node, self.index)

class Node:
    """Base class for all compositor nodes"""
    
    def __init__(self, node_type: str, node_name: str = ""):
        self.node_id = self._generate_id()
        self.node_type = node_type
        self.node_name = node_name or node_type
        
        self.inputs: List[Input] = []
        self.outputs: List[Output] = []
        self.knobs: Dict[str, Any] = {}
        
        self.position_x = 0.0
        self.position_y = 0.0
    
    def add_input(self, name: str, type_: InputType) -> Input:
        input_conn = Input(name, type_)
        self.inputs.append(input_conn)
        return input_conn
    
    def add_output(self, name: str, type_: OutputType) -> Output:
        output_conn = Output(name, type_)
        output_conn.node = self
        output_conn.index = len(self.outputs)
        self.outputs.append(output_conn)
        return output_conn
    
    def set_knob(self, name: str, value: Any):
        """Set a parameter value"""
        self.knobs[name] = value
    
    def get_knob(self, name: str) -> Any:
        """Get a parameter value"""
        return self.knobs.get(name)
    
    def compute(self, frame: int):
        """Override to implement node computation"""
        raise NotImplementedError(f"compute() not implemented for {self.node_type}")
    
    def _generate_id(self) -> str:
        import uuid
        return str(uuid.uuid4())[:8]
    
    def __repr__(self) -> str:
        return f"<{self.node_type}({self.node_name}) id={self.node_id}>"
