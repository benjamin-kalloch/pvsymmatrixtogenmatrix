# PVSymMatrixToGenMatrx

A ParaView plugin to convert field data containing symmetric (6-component) matrices/tensors to full (9-component) matrices/tensors.

## How to compile
1. Set up the ParaView environment as described in [1] 
2. Create a folder `build`
3. In the build folder execute `cmake ..`
4. Run make
5. In ParaView, load the compiled plugin dynamic library (the so-file) under `Tools -> Manage Plugins -> Load New`

###### Useful links
[1] Set up the ParaView environment: https://openfoam.org/download/source/third-party-software/