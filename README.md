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

Design:
    Device:
        DeviceType:
            Desc: Enum for device types
        Allocator:
            Desc: Pure virtual, Provides memory alloc/free for a device
            Methods:
                - allocate: Virtual, Returns Unique void pointer
                - ?get_allocator:Returns allocator object pointer for a DeviceType
        CPUAllocator:
            Desc: CPU allocator
        Device:
            Desc: Has DeviceType and Index
    Tensor:
        Desc: Holds tensor data from Allocator, templated on Dtype
        Attributes: Device, allocator ptr, data unique ptr
        Notes: Explicitly instantiate the avaialble types per Device
        Example:
            Tensor<int> t1, t2
            auto t3 = t1+t2
            Tensor<T> operator+:
                op, size = get_op2("add", t1.device, t1, t2)
                t3 = new Tensor(size)
                op(device, t1, t2, t3) 
                return t3
        Registry:
            template <typename T>
            std::function<Tensor<T>(device, Tensor<T>, Tensor<T>, Tensor<T>)> get_op2(string op_name, device, t1.size(), t2.size()) {
                if op_name == "add":
                    auto size = ...
                    return {backend::add<T>, size}
                ...
            }
    Operations:
        Example:
            Tensor<T> backend::add<T>(device, a, b, res) {
                switch device.type:
                case CPU: CPU::add<T>(device.index, a, b, res)
                case HIP: HIP::add<T>(device.index, a, b, res)
                case default: throw "No implementation for {device.type}"
            }

            
