#ifndef MUTEN_HPP
#define MUTEN_HPP

// Backend specific implementations
#ifdef MUTEN_BACKEND_HIP
#include "muten/devices/hip.hpp"
#endif
#ifdef MUTEN_BACKEND_CUDA
#include "muten/devices/cuda.hpp"
#endif

#include "backend/cpu.hpp"
#include "tensor.hpp"

#endif
