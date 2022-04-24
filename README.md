# acoustic-demos

1) Volumetric meshing of surface mesh using tetgen


## Install

```Shell
git clone git@github.com:Dawars/acoustic-demos.git --recursive
```
```Shell
cd acoustic-demos
cmake -S . -B build  # creates and runs cmake in 'build' directory
cmake --build build  # runs make in 'build'
```

## Run

```Shell
./build/app/app
```


## Dependencies
- Tetgen
- geometry-central
- polyscope
- libigl
- fmt
