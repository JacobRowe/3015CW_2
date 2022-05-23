#ifndef SCENEBASIC_UNIFORM_H
#define SCENEBASIC_UNIFORM_H

#include "helper/scene.h"
#include "helper/torus.h"
#include "helper/teapot.h"
#include "helper/plane.h"
#include "helper/objmesh.h"
#include "helper/cube.h"



#include <glad/glad.h>
#include "helper/glslprogram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "helper/skybox.h"


class SceneBasic_Uniform : public Scene
{
private:
    GLSLProgram prog, postProg, skyProg;
   
    std::unique_ptr<ObjMesh> box;
    std::unique_ptr<ObjMesh> oil;
    std::unique_ptr<ObjMesh> wall;

    Plane water;
    SkyBox sky;



    float camAngle, tPrev, rotSpeed;

    float angle, time;
    //Wireframe imp
    //glm::mat4 viewport;

    


    void compile();
    void drawScene();
    void drawObjs();
    void drawWater();





public:
    SceneBasic_Uniform();

    void initScene();
    void update( float t );
    void render();
    void resize(int, int);
    void setMatrices();
};

#endif // SCENEBASIC_UNIFORM_H
