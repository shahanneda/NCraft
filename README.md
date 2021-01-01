# NCraft
## A 3D Voxel Game written with Pure OpenGl and C++, using my own game engine.

## Features :
* A world made up of 16x16x16 Chunks
* Optimised 3D rendering of voxels using my own rendering engine which does batching and tries to limit draw calls. The renderer also hides any faces that are not facing an air block.  
* Infinite Chunk generation in all directions
* Simple and efficient lighting using normals for each face.
* Block Placing and Breaking
* Hotbar/inventory system
* Advanced World Generator which uses SimplexNoise and has features such as multiple biomes, and procidurally generated trees.
* Culling
* Texture Atlas

---
No extra libraries or tools were used other that OpenGl, GLM(for math), GLFW(windows), and FastNoise. **Everything** else was written by Shahan Neda.

## Videos
[![video image](https://img.youtube.com/vi/5EfJ2s7asK8/0.jpg)](https://www.youtube.com/watch?v=5EfJ2s7asK8)

## Images

![demo image](https://github.com/shahanneda/NCraft/raw/master/DemoImages/NCraftDemoImg1.png )

## Building
 * Use CMake.
 
