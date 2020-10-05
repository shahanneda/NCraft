# NCraft
## A 3D Voxel Game written with Pure OpenGl and C++, using my own game engine.

## Features :
* A world made up of 16x16x16 Chunks
* Optimised 3D rendering of voxels using my own rendering engine which does batching and tries to limit drawclass. The renderer also hides any faces that are not facing an air block.  
* Infinite Chunk generation in all directions
* Simple and efficient lighting using normals for each face.
* Block Placing and Breaking
* Hotbar/inventory system
* Advanced World Generator which uses SimplexNoise and has features such as multiple biomes, and procidurally generated trees.
* Culling
* Texture Atlas

---
No extra libraies or tools were used other that OpenGl, GLM(for math), GLFW(windows), and FastNoise. **Everything** else was written by Shahan Neda.

## Building
 * Use CMake.
 
