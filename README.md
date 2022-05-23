# COMP3015 CW 2: Simple Toon Shader Pipeline
 
## Status: In Progress, Prototype
![working](https://user-images.githubusercontent.com/55706787/169790422-0238329d-2420-4238-a11b-b478244a28e6.png)

Created using Microsoft Visual Studio Community 2019 Version 16.11.5 using Visual C++, GLUT and OpenGL version 4.3

## Running and using the Project
For a build of the project, navigate to x64->Debug->Project_Template.exe and simply run it

For the project itself, all project dependecies are set up for use. Pull the project, and set the relevant dependencies to the packaged "lib" and "include" folder in the repo.

The project hinges off of the scene_basic_uniform cpp file to run and manage everything. It uses three instances of a GLSLProgram object to operate and run three shaders: 
- The Toon Geometry Shaders (vertex, geom, frag)
- The Wave vertex animation and texture shaders (vertex and frag)
- The simple Sky Box shaders (vertex and frag)

## Project basis
The basis of this project was to create a solid cell shading/toon shading pipeline. This was inspired by games like Telltale games like

The Wolf Among Us

![download](https://user-images.githubusercontent.com/55706787/169790217-7d884a6d-cce7-45cd-b6b1-3c842abcb5ed.jpg)

https://indianexpress.com/article/technology/gaming/the-wolf-among-us-2-trailer-coming-this-wednesday-7761954/

This is all based on the Lab work done in the university module 3015 with a modifications to improve the visual quality

## Video Link
https://youtu.be/bGq1yTrVWVs
