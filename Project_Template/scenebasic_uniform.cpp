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



SceneBasic_Uniform::SceneBasic_Uniform(): angle (0.0f), tPrev(0.0f), rotSpeed(glm::pi<float>()/8.0f)
{
    ogre = ObjMesh::loadWithAdjacency("../Project_Template/media/bs_ears.obj");       
}






void SceneBasic_Uniform::initScene()
{
   //Sprite implementation
   
    //compile();
    //glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    //glEnable(GL_DEPTH_TEST);
    //numSprites = 80;
    //locations = new float[numSprites * 3];
    //srand((unsigned int)time(0));
    //for (int i = 0; i < numSprites; i++)
    //{
    //    vec3 p(((float)rand() / RAND_MAX * 2.0f) - 1.0f,
    //        ((float)rand() / RAND_MAX * 2.0f) - 1.0f,
    //        ((float)rand() / RAND_MAX * 2.0f) - 1.0f);
    //    locations[i * 3] = p.x;
    //    locations[i * 3 + 1] = p.y;
    //    locations[i * 3 + 2] = p.z;
    //}
    //GLuint handle;
    //glGenBuffers(1, &handle);
    //glBindBuffer(GL_ARRAY_BUFFER, handle);
    //glBufferData(GL_ARRAY_BUFFER, numSprites * 3 * sizeof(float), locations, GL_STATIC_DRAW);
    //delete[] locations;
    //glGenVertexArrays(1, &sprites);
    //glBindVertexArray(sprites);
    //glBindBuffer(GL_ARRAY_BUFFER, handle);
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, ((GLubyte*)NULL + (0)));
    //glEnableVertexAttribArray(0); //Vertex pos
    //glBindVertexArray(0);
    ////tex file
    //const char* texName = "../Project_Template/media/texture/bubz.jpg";
    //Texture::loadTexture(texName);
    //prog.setUniform("SpriteTex", 0);
    //prog.setUniform("Size2", 0.15f);

    //WireFrame implementation

    //compile();
    //glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    //glEnable(GL_DEPTH_TEST);
    //float c = 1.5f;
    //projection = glm::ortho(-0.4f * c, 0.4f * c, -0.3f * c, 0.3f * c, 0.1f, 100.0f);
    ////Set uniform
    //prog.setUniform("Line.Width", 0.55f);
    //prog.setUniform("Line.Color", vec4(0.5f, 0.0f, 0.00f, 1.0f));
    //prog.setUniform("Material.Kd", 0.7f, 0.7f, 0.7f);
    //prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
    //prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    //prog.setUniform("Material.Shine", 10.0f);
    //prog.setUniform("Light.Position", vec4(0.0f, 0.0f, 0.0f, 1.0f));
    //prog.setUniform("Light.Intensity", 1.0f, 1.0f, 1.0f);

    //Toon and Silo highlights imp
    compile();

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    glEnable(GL_DEPTH_TEST);

    angle = glm::half_pi<float>();

    prog.setUniform("EdgeWidth", 0.02f);
    prog.setUniform("PctExtend", 0.25f);
    prog.setUniform("Line.Color", vec4(0.5f, 0.0f, 0.00f, 1.0f));
    prog.setUniform("Material.Kd", 0.7f, 0.7f, 0.7f);
    prog.setUniform("Material.Ka", 0.2f, 0.2f, 0.2f);
    prog.setUniform("Material.Ks", 0.8f, 0.8f, 0.8f);
    prog.setUniform("Material.Shine", 10.0f);
    prog.setUniform("Light.Position", vec4(1.0f, 1.0f, 0.2f, 1.0f));
    prog.setUniform("Light.Intensity", 0.0f, 1.0f, 1.0f);

    
}

void SceneBasic_Uniform::compile()
{
	try {
        
        prog.compileShader("shader/OLD TO DELETE/Lab 6/siloLine.vert");
        prog.compileShader("shader/OLD TO DELETE/Lab 6/siloLine.frag");
        prog.compileShader("shader/OLD TO DELETE/Lab 6/siloLine.geom");
		prog.link();
		prog.use();
	} catch (GLSLProgramException &e) {
		cerr << e.what() << endl;
		exit(EXIT_FAILURE);
	}
}

void SceneBasic_Uniform::setupFBO()
{
    

}


void SceneBasic_Uniform::update( float t )
{
    float deltaT = t - tPrev;
    if (tPrev == 0.0f)
        deltaT = 0.0f;

    tPrev = t;
    angle += 0.25f * deltaT;
    if (angle > glm::two_pi<float>())
        angle -= glm::two_pi<float>();
     


}

void SceneBasic_Uniform::render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vec3 cameraPos(1.5f * cos(angle), 0.0f, 1.5f * sin(angle));
    view = glm::lookAt(cameraPos,
        vec3(0.0f, -1.2f, 0.0f),
        vec3(0.0f, 1.0f, 0.0f));

    model = mat4(1.0f);
    setMatrices();
    ogre->render();

    glFinish();

    





    
    
}

void SceneBasic_Uniform::resize(int w, int h)
{
    glViewport(0, 0, w, h);

    //Sprite impl
    /*width = w;
    height = h;
    projection = glm::perspective(glm::radians(70.0f), (float)w / h, 0.3f, 100.0f);*/

    //Wireframe impl
    /*float w2 = w / 2.0f;
    float h2 = h / 2.0f;
    viewport = mat4(vec4(w2, 0.0f, 0.0f, 0.0f),
        vec4(0.0f, h2, 0.0f, 0.0f),
        vec4(0.0f, 0.0f, 1.0f, 0.0f),
        vec4(w2 + 0, h2 + 0, 0.0f, 1.0f));*/

    //Silo impl
    float c = 1.5f;
    projection = glm::ortho(-0.4f * c, 0.4f * c, -0.3f * c, 0.3f * c, 0.1f, 100.0f);

}

void SceneBasic_Uniform::setMatrices()
{
    mat4 mv = view * model;

    prog.setUniform("ModelViewMatrix", mv);
    prog.setUniform("NormalMatrix",
        glm::mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2])));
    prog.setUniform("MVP", projection * mv);
    //Wireframe imp
    //prog.setUniform("ViewportMatrix", viewport);


}
