#include "scenebasic_uniform.h"


#include <cstdio>
#include <cstdlib>


#include <string>
using std::string;

#include <iostream>
using std::cerr;
using std::endl;

#include <sstream>

#include "helper/glutils.h"
#include "helper/texture.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

//Attempt at GLFW game loop

//Globals for camera system
//vec3 cameraPos = vec3(0.0f, 0.0f, 3.0f);
//vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
//vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
//float yaw = -90.0f;
//float pitch = 0.0f;
//float lastX = 800.0f / 2.0;
//float lastY = 600.0 / 2.0;
//float fov = 45.0f;
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;

//scene set up for objects, vars etc
SceneBasic_Uniform::SceneBasic_Uniform() : angle(0.0f), tPrev(0.0f), rotSpeed(glm::pi<float>() / 16.0f), time(0), water(150.0f, 147.0f, 100, 2), sky(100.0f)
{
    box = ObjMesh::loadWithAdjacency("media/box.obj", true);
    oil = ObjMesh::loadWithAdjacency("media/oil.obj", true);
    wall = ObjMesh::loadWithAdjacency("media/wallz.obj", true);
}


// scene set
void SceneBasic_Uniform::initScene()
{

    
    compile();

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    //attempts at GLFW for game loop
    /*glfwInit();
    window = glfwCreateWindow(640, 480, "Control", NULL, NULL);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);*/
    //glfwSetCursorPosCallback(window, mouse_callback);
    camAngle, angle = glm::half_pi<float>();
    
    

    // texture for scene objects 
    GLuint Tex1 = Texture::loadTexture("media/texture/mega-drive-blue.png");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Tex1);
    
    // diffuse texture for water
    GLuint Tex2 = Texture::loadTexture("media/texture/water.png");

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, Tex2);


    //https://opengameart.org/content/space-skybox-1
    // Used with public permisson
    //Sky box texture
    GLuint cubeTex =
        Texture::loadCubeMap("media/texture/night/space");
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTex);

    

}



void SceneBasic_Uniform::compile()
{
	try {
        //visual object shaders
        prog.compileShader("shader/ToonPBR.vert");
        prog.compileShader("shader/ToonPBR.frag");
        prog.compileShader("shader/ToonPBR.geom");
		prog.link();
		prog.use();

        //sea shader
        postProg.compileShader("shader/Waves.frag");
        postProg.compileShader("shader/Waves.vert");
        postProg.link();

        //skybox shader
        skyProg.compileShader("shader/Skybox.frag");
        skyProg.compileShader("shader/Skybox.vert");
        skyProg.link();

	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::drawObjs()
{
    prog.use();
    //oil rig
    prog.setUniform("EdgeWidth", 0.0025f);
    prog.setUniform("PctExtend", 0.00008f);
    prog.setUniform("Material.Kd", vec3(1.0f, 0.2f, 0.6f));
    prog.setUniform("Material.Ka", vec3(1.0f, 0.2f, 0.6f));
    prog.setUniform("Material.Ks", vec3(1.0f, 0.2f, 0.6f));
    prog.setUniform("Material.Shine", 100.0f);
    prog.setUniform("Light.Position", vec4(1.0f, 1.8f, 1.0f, 1.0f));
    prog.setUniform("Light.Intensity", vec3(0.3f, 0.3f, 0.5f));
    model = mat4(1.0f);
    model = glm::scale(model, vec3(1.5f, 1.5f, 1.5f));
    model = glm::translate(model, vec3(0.0f, 3.0f, 0.0f));
    setMatrices();
    oil->render();

    //deck boxes
    prog.setUniform("EdgeWidth", 0.0029f);
    prog.setUniform("Material.Kd", vec3(1.0f, 0.3f, 0.3f));
    prog.setUniform("Material.Ka", vec3(1.0f, 0.3f, 0.3f));
    prog.setUniform("Material.Ks", vec3(1.0f, 0.3f, 0.3f));
    prog.setUniform("Material.Shine", 20.0f);
    model = mat4(1.0f);
    model = glm::scale(model, vec3(1.5f, 1.5f, 1.5f));
    model = glm::translate(model, vec3(-0.6f, 2.8f, 0.0f));
    setMatrices();
    box->render();

    prog.setUniform("Material.Kd", vec3(0.6f, 0.6f, 0.6f));
    prog.setUniform("Material.Ka", vec3(0.6f, 0.6f, 0.6f));
    prog.setUniform("Material.Ks", vec3(0.6f, 0.6f, 0.6f));
    model = mat4(1.0f);
    model = glm::scale(model, vec3(1.4f, 1.4f, 1.4f));
    model = glm::translate(model, vec3(-0.0f, 2.8f, 1.5f));
    setMatrices();
    box->render();

    prog.setUniform("Material.Kd", vec3(0.6f, 0.6f, 0.6f));
    prog.setUniform("Material.Ka", vec3(0.6f, 0.6f, 0.6f));
    prog.setUniform("Material.Ks", vec3(0.6f, 0.6f, 0.6f));
    model = mat4(1.0f);
    model = glm::translate(model, vec3(-0.0f, 4.9f, 2.0f));
    model = glm::rotate(model, glm::radians(30.0f), vec3(0.0f, 1.0f, 0.0f));
    setMatrices();
    box->render();

    prog.setUniform("EdgeWidth", 0.0f);
    prog.setUniform("PctExtend", 0.0f);
    prog.setUniform("Material.Shine", 120.0f);
    model = mat4(1.0f);
    model = glm::scale(model, vec3(0.7f, 0.7f, 0.7f));
    model = glm::translate(model, vec3(0.0f, -0.7f, 0.0f));

    setMatrices();
    wall->render();

    glFlush();
}

void SceneBasic_Uniform::drawWater()
{
    //water draw
    postProg.use();
    postProg.setUniform("Time", time);

    postProg.setUniform("Light.Position", vec4(1.0f, 1.8f, 1.0f, 1.0f));

    postProg.setUniform("Light.L", vec3(0.2f, 0.2f, 0.2f));
    postProg.setUniform("Light.La", vec3(0.2f, 0.8f, 0.2f));
    postProg.setUniform("Material.Kd", vec3(0.4f, 0.6f, 0.6f));
    postProg.setUniform("Material.Ka", vec3(1.0f, 0.4f, 0.4f));
    postProg.setUniform("Material.Ks", vec3(1.0f, 0.6f, 0.6f));
    postProg.setUniform("Material.Shine", 100.0f);

    model = mat4(1.0f);
    model = glm::translate(model, vec3(0.0f, -1.0f, 0.0f));

    setMatrices();
    water.render();
}

void SceneBasic_Uniform::drawScene()
{

    drawObjs();
    
    drawWater();
}


//void SceneBasic_Uniform::input(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//    {
//        glfwSetWindowShouldClose(window, true);
//    }
//    const float cameraSpeed = 2.5f * deltaTime;
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//    {
//        cameraPos += cameraSpeed * cameraFront;
//    }
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//    {
//        cameraPos -= cameraSpeed * cameraFront;
//    }
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//    {
//        cameraPos -= normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//    }
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//    {
//        cameraPos += normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
//    }
//}
//
//void SceneBasic_Uniform::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
//{
//    float xpos = static_cast<float>(xposIn);
//    float ypos = static_cast<float>(yposIn);
//
//    
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//    lastX = xpos;
//    lastY = ypos;
//
//    float sensitivity = 0.1f; // change this value to your liking
//    xoffset *= sensitivity;
//    yoffset *= sensitivity;
//
//    yaw += xoffset;
//    pitch += yoffset;
//
//    // make sure that when pitch is out of bounds, screen doesn't get flipped
//    if (pitch > 89.0f)
//        pitch = 89.0f;
//    if (pitch < -89.0f)
//        pitch = -89.0f;
//
//    glm::vec3 front;
//    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
//    front.y = sin(glm::radians(pitch));
//    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
//    cameraFront = glm::normalize(front);
//}



void SceneBasic_Uniform::update( float t )
{
    //camera anim
    float deltaT = t - tPrev;
    //time for wave animation
    time = t;
    if (tPrev == 0.0f)
    {
        deltaT = 0.0f;

    }

    tPrev = t;
    camAngle += 0.25f * deltaT;

    if (camAngle > glm::two_pi<float>())
        camAngle -= glm::two_pi<float>();
     
}







void SceneBasic_Uniform::render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //input(window);

    vec3 cameraPos(5.5f * cos(camAngle), 8.0f, 5.5f * sin(camAngle));

    view = glm::lookAt(cameraPos, vec3(0.0f, 4.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));

    projection = glm::perspective(glm::radians(80.0f), (float)width / height, 0.3f, 100.0f);


    //draws whole scene and skybox
    drawScene();
    skyProg.use();
    model = mat4(1.0f);
    setMatrices();
    sky.render();

    
    

    glFinish();
    
}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);
    
    width = w;
    height = h;
    projection = glm::perspective(glm::radians(80.0f), (float)w / h, 0.3f, 100.0f);

    

}

void SceneBasic_Uniform::setMatrices()
{
    mat4 mv = view * model;

    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
        glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    prog.setUniform("MVP", projection * mv);

    postProg.setUniform("ModelViewMatrix", mv);
    postProg.setUniform("NormalMatrix",
        glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    postProg.setUniform("MVP", projection * mv);

    skyProg.setUniform("MVP", projection * mv);



}
