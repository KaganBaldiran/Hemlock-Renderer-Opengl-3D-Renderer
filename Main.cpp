#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <bitset>
#include "initialize.h"
//#include "Mesh.h"
#include "Model.h"
#include "Camera.h"
#include "Buffers.h"
#include "glm/glm.hpp"
#include "Mesh.h"
#include "Scene.h"
#include "PickingTexture.h"
#include "post_process.h"

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_opengl3.h"
#include "Imgui/imgui_impl_glfw.h"
#include "nativefiledialog-extended-master/src/include/nfd.h"

#include"UI.h"


const int windowwidth = 1000;
const int windowheight = 1000;


int main()
{
    
	GLFWwindow*window = initializeWindow(windowwidth,windowheight , "Hemlock Standalone Renderer");

    glViewport(0, 0, windowwidth, windowheight);

    Shader defaultshader("vertsource.vert", "fragsource.frag");

    Shader lightshader("light.vert", "light.frag");

    Shader Outlineshader("Outlinefrag.vert", "Outlinefrag.frag");

    Shader pickingshader("picking.vert", "picking.frag");

    Shader ShadowMapShader("ShadowMap.vert", "ShadowMap.frag");

    Shader FrameBufferShader("framebuffer.vert", "framebuffer.frag");

    scene scene;

    FBO screen_fbo;

    CreateCustomFrameBuffer(&screen_fbo , 1920 , 1000);

    // Enables Cull Facing
    //glEnable(GL_CULL_FACE);
    // Keeps front faces
    //glCullFace(GL_BACK);
    // Uses counter clock-wise standard
    //glFrontFace(GL_CCW);

    NFD_Init();
    
    glUniform4f(glGetUniformLocation(defaultshader.GetID(), "colorpr"), 1.0f, 0.0f, 0.0f, 1.0f);

    Meshs grid = scene.SetGrid(pickingshader.GetID());
    Meshs cursor = scene.SetCursorObject(pickingshader.GetID());

    //Model gizmo_arrow("C:/Users/kbald/Desktop/gizmo_arrow.obj",defaultshader.GetID());


    std::vector<std::pair<Textures*, uint>> textures_imported;
    

   
   
    glm::vec3 lightpos = glm::vec3(-0.5f, 0.9f, 0.5f);
    

    glm::vec4 lightcolor = glm::vec4(1.0f,1.0f,1.0f,1.0f);

    glm::vec3 lightpos2 = glm::vec3(0.75f, 1.5f, 0.0f);


    glm::vec4 lightcolor2 = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

    glm::vec3 lightpos3 = glm::vec3(-1.0f, 0.9f, -2.0f);
    glm::vec4 lightcolor3 = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    scene.Addlight(lightpos, glm::vec3(2.0f, 2.0f, 2.0f), lightcolor, lightshader.GetID(), CUBE_LIGHT, DIRECTIONAL_LIGHT);
    scene.Addlight(lightpos2, glm::vec3(1.0f, 1.0f, 1.0f), lightcolor2, lightshader.GetID(), CUBE_LIGHT, SPOT_LIGHT);
    //scene.Addlight(-glm::vec3(0.5f, 0.9f, 0.5f), glm::vec3(1.0f, 1.0f, 1.0f), lightcolor, lightshader.GetID(), CUBE_LIGHT,DIRECTIONAL_LIGHT);
    //scene.Addlight(lightpos3, glm::vec3(1.0f, 1.0f, 1.0f), lightcolor3, lightshader.GetID(), CUBE_LIGHT, POINT_LIGHT);


    for (size_t i = 0; i < scene.GetModelCount(); i++)
    {
        scene.GetModel(i)->transformation.scale(glm::vec3(0.05f, 0.05f, 0.05f));
    }
   
    

    scene.handlelights(defaultshader.GetID());

    UseShaderProgram(defaultshader.GetID());

    //glUniformMatrix4fv(glGetUniformLocation(defaultshader.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(pyramidmodel));
    glUniform4f(glGetUniformLocation(defaultshader.GetID(), "lightColor1"), lightcolor.x, lightcolor.y, lightcolor.z, lightcolor.w);
    glUniform3f(glGetUniformLocation(defaultshader.GetID(), "lightpos1"), lightpos.x, lightpos.y, lightpos.z);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);




    float degree = NULL;
    
    pickingtexture pickingtex;
    picking_technique pickingteq;
    pickingtex.Init(windowwidth, windowheight);


    Camera camera(windowwidth, windowheight, glm::vec3(0.0f, 0.0f, 2.0f));

    int selection = NULL;
    int index = NULL;
    int currentselectedobj = NULL;
    int currentselectedlight = NULL;

    bool allowclick = true;
    //bool enablehighlight = false;
    bool starttime = false;

    float time = NULL;

    

    UI::InitNewUIwindow();

    UI::SetStyle();
    
    UI::SetPlatformBackEnd("#version 130", window);

    

    Model* selected_model = nullptr;
    int  selectedobjlock = NULL;

    UI::UIdataPack data;



    std::vector<std::string> logs;

    UI::InitLogs(logs);




    shadowmap ShadowMap(4096, 4096);

    ShadowMap.LightProjection(lightpos,ShadowMapShader.GetID(),window,scene.models,scene.globalscale);




    scene.SetScreenQuads();


    std::vector<uint> auto_rotate_on;

    
	while (!glfwWindowShouldClose(window))
	{
       
        
        WindowSizeRecall(window,UI::current_win_size);
        
       // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

		glClearColor(data.clear_color.x, data.clear_color.y, data.clear_color.z, data.clear_color.w);
        glClearStencil(0); // this is the default value
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        UI::CreateNewFrame();


        camera.HandleInputs(window, UI::current_win_size);

        camera.updateMatrix(45.0f, 0.1f, 100.0f, window,UI::current_win_size);

        
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            if (data.moveamount.x == data.newtreshold.x)
            {
                data.maxmove.x = 2.0f * data.newtreshold.x;
                data.newtreshold.x = data.maxmove.x;
            }
            if (data.moveamount.y == data.newtreshold.y)
            {
                data.maxmove.y = 2.0f * data.newtreshold.y;
                data.newtreshold.y = data.maxmove.y;
            }
            if (data.moveamount.z == data.newtreshold.z)
            {
                data.maxmove.z = 2.0f * data.newtreshold.z;
                data.newtreshold.z = data.maxmove.z;
            }
            if (data.scaleamount == data.maxscale)
            {
                data.maxscale = 2.0f * data.maxscale;
                //maxscale = scaleamount;
            }
        }
        
      

        std::cout << "CURRENT SELECTED OBJECT: " << currentselectedobj << "\n";
       

        UI::ConfigureUI(currentselectedobj, data, scene, logs, defaultshader.GetID(), lightcolor, lightpos,window,auto_rotate_on , ShadowMap.GetShadowMapImage());

        //UI::DemoUI(window);


        if (glfwGetKey(window,GLFW_KEY_DELETE) == GLFW_PRESS && currentselectedobj >= 2)
        {
            uint* tempptr = scene.GetModel(scene.GetModelCount() - 1)->GetModelIDcounterptr();

            *scene.GetModel(scene.GetModelCount() - 1)->GetModelIDcounterptr() -= 1;

           scene.DeleteModel(currentselectedobj - 2);

           if (scene.GetModelCount() >= 1)
           {
               for (size_t i = 0; i < scene.GetModelCount(); i++)
               {
                   if (scene.GetModel(i)->GetModelID() > 2 && scene.GetModel(currentselectedobj - 3)->GetModelID() != scene.GetModelCount() + 1)
                   {
                       *scene.GetModel(i)->GetModelIDptr() -= 1;
                       
                   }
                  
               }
           }
           
           std::cout << "NEW MODEL ID COUNTER: " << *tempptr << "\n";

           std::string logtemp = "A new object is deleted!";

           logs.push_back(logtemp);
           
           currentselectedobj = 0;

        }

        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && currentselectedobj >= 2)
        {
            
            static int counterf = NULL;

            if (counterf < 1)
            {

                scene.CopyModel(currentselectedobj - 2);

                scene.handlelights(defaultshader.GetID());

                UseShaderProgram(defaultshader.GetID());

                //glUniformMatrix4fv(glGetUniformLocation(defaultshader.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(pyramidmodel));
                glUniform4f(glGetUniformLocation(defaultshader.GetID(), "lightColor1"), lightcolor.x, lightcolor.y, lightcolor.z, lightcolor.w);
                glUniform3f(glGetUniformLocation(defaultshader.GetID(), "lightpos1"), lightpos.x, lightpos.y, lightpos.z);

                std::string logtemp = "A new object is duplicated!";

                logs.push_back(logtemp);

            }

            
            counterf++;
        }
        
        //if (selected_model != nullptr)
        //{

		if (data.autorotate)
		{
			data.degree += 0.1f;

			if (data.degree >= 360.0f)
			{
                data.degree = NULL;
			}

            data.rotationamount = data.degree;
		}
		if (!data.autorotate)
		{
            data.degree = data.rotationamount;
		}


        for (size_t i = 0; i < auto_rotate_on.size();i++)
        {
            if (auto_rotate_on.at(i) != CURRENT_OBJECT(currentselectedobj))
            {
                scene.GetModel(auto_rotate_on.at(i))->UIprop.degree = scene.GetModel(auto_rotate_on.at(i))->UIprop.rotationamount;

                scene.GetModel(auto_rotate_on.at(i))->UIprop.degree += 0.1f;

                if (scene.GetModel(auto_rotate_on.at(i))->UIprop.degree >= 360.0f)
                {
                    scene.GetModel(auto_rotate_on.at(i))->UIprop.degree = NULL;
                }

                scene.GetModel(auto_rotate_on.at(i))->UIprop.rotationamount = scene.GetModel(auto_rotate_on.at(i))->UIprop.degree;
            }
           
        }



		if (currentselectedobj >= 2)
		{


			scene.GetModel(currentselectedobj - 2)->transformation.translate(glm::vec3(data.moveamount.x, data.moveamount.y, data.moveamount.z));



			scene.GetModel(currentselectedobj - 2)->transformation.translate(glm::vec3(0.0f, 0.0f, 0.0f));




			if (data.scaleamount != 0.0f)
			{
				scene.GetModel(currentselectedobj - 2)->transformation.scale(glm::vec3(data.scaleamount, data.scaleamount, data.scaleamount));

                scene.RecalculateObjectScales(currentselectedobj, glm::vec3(data.scaleamount, data.scaleamount, data.scaleamount));

			}


			scene.GetModel(currentselectedobj - 2)->transformation.rotate(data.rotationamount, glm::vec3(0.0f, 1.0f, 0.0f));





			scene.GetModel(currentselectedobj - 2)->transformation.translate(-glm::vec3(0.0f, 0.0f, 0.0f));


		}
        

		for (size_t i = 0; i < auto_rotate_on.size(); i++)
		{
            if (auto_rotate_on.at(i) != CURRENT_OBJECT(currentselectedobj))
            {
                scene.GetModel(auto_rotate_on.at(i))->transformation.translate(glm::vec3(0.0f, 0.0f, 0.0f));

                scene.GetModel(auto_rotate_on.at(i))->transformation.rotate(scene.GetModel(auto_rotate_on.at(i))->UIprop.rotationamount, glm::vec3(0.0f, 1.0f, 0.0f));

                scene.GetModel(auto_rotate_on.at(i))->transformation.translate(-glm::vec3(0.0f, 0.0f, 0.0f));

            }

		}
            
        
        

        

        ShadowMap.LightProjection(lightpos, ShadowMapShader.GetID(),window,scene.models,scene.globalscale);
        
        

        //std::cout << "index ID " << index << "\n";
        scene.DrawShadowMap(&ShadowMap, ShadowMapShader.GetID(), camera, window, glm::vec4(data.clear_color.x, data.clear_color.y, data.clear_color.z, data.clear_color.w));

        glBindFramebuffer(GL_FRAMEBUFFER, *screen_fbo.GetFBO());

        WindowSizeRecall(window,UI::current_win_size);

        

        glClearColor(data.clear_color.x, data.clear_color.y, data.clear_color.z, data.clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        
        glEnable(GL_STENCIL_TEST);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        if (currentselectedobj >= 2)
        {
            scene.DrawModelsWithOutline(defaultshader.GetID(), Outlineshader.GetID(), camera, currentselectedobj - 2, currentselectedobj,ShadowMap.GetShadowMapImage());
           
        }



        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        scene.RenderGrid(pickingshader.GetID(), grid, camera);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        if (data.takesreenshot)
        {
            glClearColor(data.clear_color.x, data.clear_color.y, data.clear_color.z, data.clear_color.w);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        }
        
        UseShaderProgram(defaultshader.GetID());


       


        for (int i = 0; i < scene.GetModelCount()+1; i++) {
            glStencilFunc(GL_ALWAYS, i + 1, -1);
            if (i == 0)
            {

                
            }
            if (i >= 1)
            {
                
				ShadowMap.LightProjection(lightpos, defaultshader.GetID(), window, scene.models, scene.globalscale);

				glUniform1i(glGetUniformLocation(defaultshader.GetID(), "enablehighlight"), data.enablehighlight);


				scene.GetModel(i - 1)->transformation.SendUniformToShader(defaultshader.GetID(), "model");
				scene.DrawModels(defaultshader.GetID(), camera, i - 1, ShadowMap.GetShadowMapImage());

				glActiveTexture(GL_TEXTURE0);

				UseShaderProgram(0);
            }

            
        }

        if (data.renderlights)
        {

            for (int i = 0; i < scene.lights.size(); i++) {
                glStencilFunc(GL_ALWAYS, i + 1 + scene.GetModelCount() + 1, -1);

                    scene.lights[i]->Draw(lightshader.GetID(), camera);

            }
        }
        for (int i = 0; i < 1; i++) 
        {
            glStencilFunc(GL_ALWAYS, i + 1 + scene.GetModelCount() + 1 + scene.lights.size(), -1);

            //scene.DrawGizmo(defaultshader.GetID(), gizmo_arrow, camera,ShadowMap.GetShadowMapImage());
        }



        //glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);

        if (data.takesreenshot)
        {
            vec2<int> screensize;
            glfwGetWindowSize(window, &screensize.x, &screensize.y);

         
            scene.Takescreenshot(&ShadowMap,screensize.x , screensize.y , data.screenshotPathstr.c_str());
            data.takesreenshot = false;
        }
       
        
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE  && !allowclick)
        {
            index = 0;
        }

        if (index == 0)
        {
            allowclick = true;
        }


        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && allowclick)
        {
            if (currentselectedobj >= 2)
            {
                UI::ReturnSelectedObjectData(data, scene.GetModel(CURRENT_OBJECT(currentselectedobj))->UIprop);

            }

            allowclick = false;
            //std::cout << "PRESSED!" << "\n";
            vec2<double> mousepos;
            glfwGetCursorPos(window, &mousepos.x, &mousepos.y);

            vec2<double> virtual_mouse_pos;

            virtual_mouse_pos.x = (mousepos.x - UI::current_win_size.x) / UI::image_ratio_divisor;
            virtual_mouse_pos.y = (mousepos.y + 75) / UI::image_ratio_divisor - 100;

            //std::cout << "VIRTUAL MOUSE POS X: " << virtual_mouse_pos.x << "VIRTUAL MOUSE POS Y: " << virtual_mouse_pos.y << "\n";


            mousepos.x = virtual_mouse_pos.x;
            mousepos.y = virtual_mouse_pos.y;


            vec2<double> mp = UI::CalculateVirtualMouse(window);


            index = pickingtex.onMouse(mp.x, mp.y, { windowwidth,windowheight });

            //std::cout << "index ID " << index << "\n";
            glUniform1i(glGetUniformLocation(defaultshader.GetID(), "stencilindex"), index);

            if (index - 1 <= scene.GetModelCount())
            {
                currentselectedobj = index;
                currentselectedlight = NULL;
            }
            else if(index - 1 >= scene.GetModelCount())
            {
                currentselectedlight = index;
                currentselectedobj = NULL;


            }

            std::cout << "Current selected light: " << currentselectedlight << "\n";
            std::cout << "Current selected obj: " << currentselectedobj << "\n";


            
            if (currentselectedobj >= 2)
            {
                UI::UseSelectedObjectData(data, scene.GetModel(CURRENT_OBJECT(currentselectedobj))->UIprop);
            }

        }

       /* vec2<double> mousepos;
        glfwGetCursorPos(window, &mousepos.x, &mousepos.y);

        vec2<double> virtual_mouse_pos;

        virtual_mouse_pos.x = (mousepos.x - UI::current_win_size.x ) / UI::image_ratio_divisor;
        virtual_mouse_pos.y = (mousepos.y + 75 ) / UI::image_ratio_divisor  - 100;

        std::cout << "VIRTUAL MOUSE POS X: " << virtual_mouse_pos.x << "VIRTUAL MOUSE POS Y: " << virtual_mouse_pos.y << "\n";
        */

        UI::CalculateVirtualMouse(window);


        glBindFramebuffer(GL_FRAMEBUFFER, NULL);

        UI::DrawFrameBuffer(*screen_fbo.GetScreenImage(), window);

        std::cout << "Current selected light: " << currentselectedlight << "\n";
       
        //scene.DrawScreenQuad(FrameBufferShader.GetID(), ShadowMap.GetShadowMapImage());
        //scene.DrawCursor(cursor, pickingshader.GetID(), camera);
        
        
        UI::Render();


		glfwSwapBuffers(window);
		glfwPollEvents();

       
        
		// if (selected_model != nullptr)
		// {
		if (currentselectedobj >= 2)
		{



			scene.GetModel(currentselectedobj - 2)->transformation.translate(glm::vec3(0.0f, 0.0f, 0.0f));



			scene.GetModel(currentselectedobj - 2)->transformation.scale(glm::vec3(1 / data.scaleamount, 1 / data.scaleamount, 1 / data.scaleamount));


			scene.GetModel(currentselectedobj - 2)->transformation.rotate(-data.rotationamount, glm::vec3(0.0f, 1.0f, 0.0f));

			scene.GetModel(currentselectedobj - 2)->transformation.translate(-glm::vec3(0.0f, 0.0f, 0.0f));



			scene.GetModel(currentselectedobj - 2)->transformation.translate(-glm::vec3(data.moveamount.x, data.moveamount.y, data.moveamount.z));



		}
       
		for (size_t i = 0; i < auto_rotate_on.size(); i++)
		{
			if (auto_rotate_on.at(i) != CURRENT_OBJECT(currentselectedobj))
			{

				scene.GetModel(auto_rotate_on.at(i))->transformation.translate(glm::vec3(0.0f, 0.0f, 0.0f));

				scene.GetModel(auto_rotate_on.at(i))->transformation.rotate(-scene.GetModel(auto_rotate_on.at(i))->UIprop.rotationamount, glm::vec3(0.0f, 1.0f, 0.0f));

				scene.GetModel(auto_rotate_on.at(i))->transformation.translate(-glm::vec3(0.0f, 0.0f, 0.0f));

			}
		}
        
		// }
        
	}

    BindVAONull();
    BindVBONull();
    BindEBONull();
    UseShaderProgram(NULL);

    NFD_FreePath(data.outPath);

    DeleteShaderProgram(defaultshader.GetID());
    DeleteShaderProgram(lightshader.GetID());
    DeleteShaderProgram(Outlineshader.GetID());
    DeleteShaderProgram(pickingshader.GetID());
    DeleteShaderProgram(ShadowMapShader.GetID());
    DeleteShaderProgram(FrameBufferShader.GetID());

    for (size_t i = 0; i < textures_imported.size(); i++)
    {
        if (textures_imported.at(i).first != nullptr)
        {
            delete textures_imported.at(i).first;

        }

    }

    UI::EndUI();

    NFD_Quit();
    DeinitializeWindow();
	return 0;
}