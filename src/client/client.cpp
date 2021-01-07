
#include "../networking/common.h"
#include "client.h"

//OpenGl loader libraries and the glfw for windows creation and easy user input
//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//graphics includes (includes also some of the common c++ h files and the gl maths headers)
#include "../graphics/Player.h"
#include "../graphics/Camera.h"
#include "../graphics/Character.h"
#include "../graphics/Area.h"
#include "../graphics/ObjectLoader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLenum glCheckError_(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
        case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
        case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
        case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
        case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
        case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
        case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
        case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__) 

void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}


Player peluri;
int screenWidth;
int screenHeight;
glm::mat4 proj;
Client client;




float lastX = 320, lastY = 240;
bool leftButtonDown = false;

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    float xoffset = lastX - (float) xpos;
    float yoffset = lastY - (float) ypos;
    lastX = (float) xpos;
    lastY = (float) ypos;

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    if (state == GLFW_PRESS) {
        leftButtonDown = true;
    }

    if (state == GLFW_RELEASE) {
        leftButtonDown = false;
    }

    if (leftButtonDown)
    {
        float sensitivity = 0.2f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        peluri.Yaw(xoffset);
        peluri.Pitch(yoffset);
    }
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{

    float sensitivity = 0.3f;
    peluri.camera.ZoomIn((float)yoffset * sensitivity);
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        double norm_x = 2 * xPos / screenWidth - 1;
        double norm_y = 1 - 2 * yPos / screenHeight;

        glm::vec4 ray = glm::vec4(norm_x, norm_y, -1.0, 1.0);
        glm::vec2 coordinate = peluri.getMouseRayCoordinate(ray, proj);

        int x = int(coordinate.x);
        int y = int(coordinate.y);
        
        client.Move(x, y, peluri.GetId());
    }
}

int main() 
{
    bool fullscreen = false;
    bool useScreenData = false;

    screenWidth = 1366;
    screenHeight = 768;


    //Stack allocated window
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    auto mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    if(useScreenData)screenWidth = mode->width;
    if (useScreenData)screenHeight = mode->height;
    /* Create a windowed mode window and its OpenGL context */
    if (fullscreen) { window = glfwCreateWindow(screenWidth, screenHeight, "MMORPG", glfwGetPrimaryMonitor(), NULL); }
    else { window = glfwCreateWindow(screenWidth, screenHeight, "MMORPG", NULL, NULL); }

   
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
   
    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    
    //glewExperimental = GL_TRUE;
    //After context creation, we can initialize GLEW
    if (glewInit() != GLEW_OK) std::cout << "Error initializing GLEW" << std::endl;
    
    

    // During init, enable debug output for checking errors
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, 0);

    //Enable the use of z buffer
    glEnable(GL_DEPTH_TEST);

   
    //Trying to load some images to see if this thing works
    int width, height, nchannels;
    unsigned char* data = stbi_load("src/graphics/textures/textuuri1.png",&width,&height,&nchannels,0);
    if (data) std::cout << "image loading succeeded!" << std::endl;
    else std::cout << "Error loading image :(" << std::endl;
    

    //Some testing data for our testcube
    ObjectLoader loader;


    //Load vertices for the model
    auto pelaajavertexarray = loader.loadOBJ("src/graphics/models/ukko.obj");
    auto pineVertices = loader.loadOBJ("src/graphics/models/simpleSpruce.obj");
    auto pineStump = loader.loadOBJ("src/graphics/models/pineTrump.obj"); 
    auto orc1 = loader.loadOBJ("src/graphics/models/orc1.obj");
    auto houseVertices = loader.loadOBJ("src/graphics/models/house.obj");

    Mesh* pelaajamodel = new Mesh(pelaajavertexarray);
    pelaajamodel->addTexture("src/graphics/textures/ukkotextuuri1.png");
   pelaajamodel->SetRelativePosition(glm::vec3(0.0, 0.0, -0.2));

    //Player initializations
    peluri.AddMesh(pelaajamodel);
    peluri.SetScaling(glm::vec3((float)0.05));
    peluri.Pitch(-45);
   /*Player initializations end here*/
       
    //Controls
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetMouseButtonCallback(window,mouse_button_callback);

    

    
    //Terrain generation
    Terrain* terde = new Terrain();
    terde->setBlendmap("src/graphics/textures/lumbridge.png");
    //So far, the order has been: black, red, green and blue.
    terde->addTexture("src/graphics/textures/grass.jpg");
    terde->addTexture("src/graphics/textures/sand.png");
    terde->addTexture("src/graphics/textures/dirt.png");
    terde->addTexture("src/graphics/textures/lumbupath.png");

    //Skybox filepaths
    /*IMPORTANT!!!!
    THE ORDER IN WHICH THE IMAGES SHALL BE LOADED IS AS FOLLOWS:
    right->left->top->bottom->front->back
    (where back is positive z and front is negative z)
    */
    std::vector<std::string> skyboxfilupathit = {
  "src/graphics/textures/daylightskybox/Daylight_Right.bmp",
  "src/graphics/textures/daylightskybox/Daylight_Left.bmp",
  "src/graphics/textures/daylightskybox/Daylight_Top.bmp",
   "src/graphics/textures/daylightskybox/Daylight_Bottom.bmp",
   "src/graphics/textures/daylightskybox/Daylight_Front.bmp",
  "src/graphics/textures/daylightskybox/Daylight_Back.bmp"
    };

    std::vector<std::string> arcticskyboxfilupathit = {
      "src/graphics/textures/arcticskybox/right.jpg",
      "src/graphics/textures/arcticskybox/left.jpg",
      "src/graphics/textures/arcticskybox/top.jpg",
       "src/graphics/textures/arcticskybox/bottom.jpg",
       "src/graphics/textures/arcticskybox/front.jpg",
      "src/graphics/textures/arcticskybox/back.jpg"
    };
    //Load skyboxes
    int skywidth, skyheight, skychannels;
    auto skyboxkuvat = loader.loadCubemap(skyboxfilupathit, skywidth, skyheight, skychannels);

    int arcskywidth, arcskyheight, arcskychannels;
    auto arcticskyboxkuvat = loader.loadCubemap(arcticskyboxfilupathit, arcskywidth, arcskyheight, arcskychannels);
    //Create them
    Cubemap* skybox = new Cubemap(skyboxkuvat, skywidth, skyheight, skychannels);
    Cubemap* arctic = new Cubemap(arcticskyboxkuvat, arcskywidth, arcskyheight, arcskychannels);

    //Shader creation
    Shader varjostin("src/graphics/shaders/VertexShader.glsl", "src/graphics/shaders/FragmentShader.glsl");
    Shader terdeShader("src/graphics/shaders/TerrainVertexShader.glsl", "src/graphics/shaders/TerrainFragmentShader.glsl");
    Shader skyboxShader("src/graphics/shaders/CubemapVertexShader.glsl", "src/graphics/shaders/CubemapFragmentShader.glsl");
    //Uniforms for the shaders
    glm::mat4 view;
    proj = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f,100.0f);
    

    //Area creations.
    Area* perusArea = new Area(terde,skybox);
    
    //Creating objects for the areas.
    std::vector<glm::vec3> vectors = {
        glm::vec3(8.5, 0.1, 2.5),
        glm::vec3(9.5, 0.1, 7.5),
        glm::vec3(8.5, 0.1, 11.5),
        glm::vec3(8.5, 0.1, 17.5),
        glm::vec3(9.5, 0.1, 23.5),
        glm::vec3(21.5, 0.1, 50.5),
        glm::vec3(16.5, 0.1, 54.5),
        glm::vec3(15.5, 0.1, 58.5),
        glm::vec3(2.5, 0.1, 61.5),
        glm::vec3(9.5, 0.1, 61.5),
        glm::vec3(20.5, 0.1, 61.5),
        glm::vec3(6.5, 0.1, 57.5),
        glm::vec3(8.5, 0.1, 53.5)
    };

    //Adding objects to the areas.
    std::for_each(vectors.begin(), vectors.end(),
        [&](const glm::vec3& vec)
        {
            Mesh* pineMesh = new Mesh(pineVertices, vec);
            Mesh* choppedPine = new Mesh(pineStump, vec);

            auto pinetree = new AreaObject(pineMesh, choppedPine, "src/graphics/textures/pinetexture.jpg", "tree");

            perusArea->AddObject(pinetree);
        }
     );
    Mesh* house = new Mesh(houseVertices, glm::vec3(34, -0.5, 39));
    house->SetRotation(glm::vec3(0.0, 180, 0.0));
    house->SetScaling(glm::vec3((float)0.8));

    auto house1 = new AreaObject(house, house, "src/graphics/textures/housetexture.png", "house");
    perusArea->AddObject(house1);
    /* And the initializations end here*/

    std::vector<Character*> characters;
    std::vector<Model*> entities;


    /* Loop until the user closes the window */
    bool ekakerta = true;
    

    //client.Connect("82.130.46.181", 3002);
     client.Connect("127.0.0.1", 3002);

    bool key[3] = { false, false, false };
    bool old_key[3] = { false, false, false };

    bool bQuit = false;

    while (!glfwWindowShouldClose(window) && !bQuit)
    {



        if (GetForegroundWindow() == GetConsoleWindow())
        {
            key[0] = GetAsyncKeyState('1') & 0x8000;
            key[1] = GetAsyncKeyState('2') & 0x8000;
            key[2] = GetAsyncKeyState('3') & 0x8000;
        }

        if (key[0] && !old_key[0]) client.PingServer();
        if (key[1] && !old_key[1]) client.Move(2, 2, peluri.GetId());
        if (key[2] && !old_key[2]) client.Move(0, 0, peluri.GetId());

        for (int i = 0; i < 3; i++) old_key[i] = key[i];

        if (client.isConnected())
        {
            if (!client.Incoming().empty())
            {


                auto msg = client.Incoming().pop_front();
                std::cout << msg.GetHeader().id << std::endl;

                switch (msg.GetHeader().id)
                {
                case 999:
                {
                    // Server has responded to a ping request				
                    std::cout << "Server Accepted Connection\n";
                }
                break;
                case 123:
                {
                    std::cout << "Server responded to Ping" << std::endl;
                }
                break;
                case 5:
                {
                    std::cout << "Player location received: " << msg.GetBody() << std::endl;
                    std::string a;
                    std::string b;
                    std::string id;
                   // if (a.empty() || b.empty() || id.empty()) break;

                    std::stringstream ss(msg.GetBody());
                    std::getline(ss, a, '/');
                    std::getline(ss, b, '/');
                    std::getline(ss, id, '/');

                    float x = std::stof(a);
                    float y = std::stof(b);
                    int ID = std::stoi(id);
                   
                    auto iter = find_if(characters.begin(), characters.end(), [&](Character* c) {return c->GetId() == ID; });
                   
                    if (peluri.GetId() == -1 && ekakerta)
                    {
                      peluri.SetId(ID);
                      peluri.SetPosition(glm::vec3(x, 0.0, y));
                      ekakerta = false;
                    }
                    else if(peluri.GetId()== ID) {
                      peluri.SetPosition(glm::vec3(x,0.0,y));
                      }
                    else if (iter != characters.end()) {
                      (*iter)->SetPosition(glm::vec3(x, 0.0, y));
                    }
                    else {
                        Mesh* uus = new Mesh(pelaajavertexarray);
                       Character* hahmo = new Character(uus,"player",glm::vec3(x,0.0,y),ID);
                      hahmo->AddCharacterTexture("src/graphics/textures/ukkotextuuri1.png");
                      hahmo->SetScaling(glm::vec3(0.05f));
                      characters.push_back(hahmo);
                    }
                }
                break;
                case 6:
                {
                    std::string a;
                    std::string b;
                    std::string id;
                    std::stringstream ss(msg.GetBody());
                    std::getline(ss, a, '/');
                    std::getline(ss, b, '/');
                    std::getline(ss, id, '/');
                   
                    float x = std::stof(a);
                    float y = std::stof(b);
                    int monsterID = std::stoi(id);
                   
                    auto iter = find_if(entities.begin(), entities.end(), [&](Model* c) {return c->GetId() == monsterID; });
                   
                    if (iter != entities.end()) {
                      (*iter)->SetPosition(glm::vec3(x, 0.0, y));
                    }
                    else {
                       Model* monsu = new Model(glm::vec3(x,0.0,y),monsterID);
                       
                       Mesh* olio = new Mesh(orc1);
                       olio->addTexture("src/graphics/textures/orctexture1.png");
                       monsu->AddMesh(olio);
                       monsu->SetScaling(glm::vec3((float)0.01));
                     entities.push_back(monsu);
                     std::cout << "NPC ADDED" << std::endl;
                    }

                }
                break;
                case 7:
                {
                    std::string id;
                    std::stringstream ss(msg.GetBody());

                    std::getline(ss, id, '/');

                    int ID = std::stoi(id);

                    auto iter = find_if(characters.begin(), characters.end(), [&](Character* c) {return c->GetId() == ID; });

                    if (iter != characters.end()) {
                        characters.erase(iter);
                    }
                }
                break;
                }
            }
        }
        else
        {
            std::cout << "Server Down\n";
            bQuit = true;

        }
        /* Render here */

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        //Update the view
        view = peluri.camera.GetCurrentView();



        //draw calls


       peluri.Draw(varjostin, proj);

       std::for_each(entities.begin(), entities.end(), [&](auto i) {i->Draw(varjostin, proj, view); });
       std::for_each(characters.begin(), characters.end(), [&](auto i) {i->Draw(varjostin, proj, view); });

       perusArea->DrawArea(varjostin,terdeShader,skyboxShader,proj,view);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
  


    return 0; 
}

