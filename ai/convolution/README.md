# Convolution
- This directory includes convolution implementation with different languages, include python(pytorch, tensorflow, numpy), CPU sequential c/c++, and GPU CUDA version.
- Parameters stride, padding, dilation are also taken into account.
- 1D, 2D, and 3D convolution are all included.

# Docker
```
docker run --gpus all --rm -it -v $PWD:/work pytorch/pytorch:1.5.1-cuda10.1-cudnn7-devel
```

# Compile and Run
```
## install python extension
python setup install

## execute test.py
python test.py
```