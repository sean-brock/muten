muten
-----

A small tensor library. Supports HIP and CPU backend.

## Structure

Mutiple types, one for each backend

Tensor:

    - http://blog.ezyang.com/2019/05/pytorch-internals/
    - Created on CPU or device (optionally, in constructor(device=CPU))
    - to(device) to transfer to a different compute context
        - tensor_gpu = tensor_cpu.to(hip_context)
    - All operations on tensors must be on the same context
    - Operations:
        - tensor = muten::add(tensor, tensor)
        - Depending on device, use device specific impl

Autograd:

    - Required to handle backwards passes for NN
    - https://en.wikipedia.org/wiki/Automatic_differentiation
