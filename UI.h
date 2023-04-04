#ifndef UI_HEADER
#define UI_HEADER

#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <filesystem>
#include <string>

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_opengl3.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Texture.h"

namespace UI
{


	vec2<int> current_win_size = { (1000/5.4f),1000-18 };
	vec2<float> viewport_size;
	float image_ratio_divisor = NULL;


    struct UIdataPack
    {
        bool renderlights = false;
        ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);

        bool autorotate = false;
        float rotationamount = NULL;
        float keepoldrotation = NULL;
        vec3<float> moveamount = { NULL,NULL,NULL };
        vec3<float> maxmove = { 20.0f,20.0f,20.0f };
        vec3<float> newtreshold = { 20.0f,20.0f,20.0f };
        float scaleamount = 1.0f;
        float maxscale = 2.0f;


        bool logbutton = false;
        bool propertiesbutton = false;

        nfdchar_t* outPath = nullptr;
        nfdchar_t* screenshotPath = nullptr;
        std::string screenshotPathstr;
        bool takesreenshot = false;


        char filepath[200];
        bool imported = false;

        bool enablehighlight = false;


        float degree = NULL;

    };

	

	void InitNewUIwindow()
	{
		ImGui::CreateContext();
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
	}

	void SetPlatformBackEnd(const char* version , GLFWwindow *window)
	{
		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(version);
	}

	void CreateNewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void SetStyle()
	{
		ImGuiStyle &style = ImGui::GetStyle();

		// Modify the style properties
		style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Set the text color to white
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
		style.FrameRounding = 5.0f;
		style.ItemSpacing = ImVec2(20, 10);
		style.ChildBorderSize = 1.3f;
		style.FrameBorderSize = 1.3f;
		style.Alpha = 0.9f;// Set the rounding of frame corners to 5.0f
		style.ScrollbarSize = 10.0f;
		style.WindowMinSize = ImVec2(0, 0);
        
        
	}

    void Render()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void EndUI()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

    void UseSelectedObjectData(UIdataPack &data , UIproperties &obj_data)
    {
        data.autorotate = obj_data.autorotate;
        data.keepoldrotation = obj_data.keepoldrotation;
        data.maxmove = obj_data.maxmove;
        data.moveamount = obj_data.moveamount;
        data.newtreshold = obj_data.newtreshold;
        data.scaleamount = obj_data.scaleamount;
        data.maxscale = obj_data.maxscale;
        data.rotationamount = obj_data.rotationamount;
        data.degree = obj_data.degree;
       
    }

    void ReturnSelectedObjectData(UIdataPack& data, UIproperties& obj_data)
    {
        obj_data.autorotate = data.autorotate;
        obj_data.keepoldrotation = data.keepoldrotation;
        obj_data.maxmove = data.maxmove;
        obj_data.moveamount = data.moveamount;
        obj_data.newtreshold = data.newtreshold;
        obj_data.scaleamount = data.scaleamount;
        obj_data.maxscale = data.maxscale;
        obj_data.rotationamount = data.rotationamount;
        obj_data.degree = data.degree;
    }

	void InitLogs(std::vector<std::string>& logs)
	{
		int major, minor;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);

		std::string vendor = (const char*)glGetString(GL_VENDOR);
		vendor = "Vendor: " + vendor;

		std::string renderer = (const char*)glGetString(GL_RENDERER);
		renderer = "Renderer: " + renderer;

		std::string GLversion = "OpenGL Version: " + std::to_string(major) + "." + std::to_string(minor);

		std::string GLSLversion = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
		GLSLversion = "GLSL version: " + GLSLversion;

		logs.push_back(vendor);
		logs.push_back(renderer);
		logs.push_back(GLversion);
		logs.push_back(GLSLversion);

	}

    void FrameBufferSizeCallBack(GLFWwindow* window)
    {
        vec2<int> winsize;

        glfwGetWindowSize(window, &winsize.x, &winsize.y);

        int main_menu_height = 18;

        current_win_size.x = winsize.x / 5.4f;
        current_win_size.y = winsize.y - main_menu_height;

        ImGui::SetNextWindowSize(ImVec2(current_win_size.x,current_win_size.y));
        
        ImGui::SetNextWindowPos(ImVec2(0, main_menu_height));

    }

	vec2<double> CalculateVirtualMouse(GLFWwindow* window)
	{
		vec2<double> mousepos;
		glfwGetCursorPos(window, &mousepos.x, &mousepos.y);

		vec2<double> virtual_mouse_pos;

		virtual_mouse_pos.x = (mousepos.x ) - current_win_size.x;
		virtual_mouse_pos.y = (mousepos.y + 75) / UI::image_ratio_divisor - 100;

		
		vec2<double> ratio = { (virtual_mouse_pos.x / ((1920 / image_ratio_divisor) - current_win_size.x)) ,  mousepos.y / 1080 };

		mousepos = { mousepos.x * ratio.x, mousepos.y * (virtual_mouse_pos.y / ((1000 - 175) / image_ratio_divisor)) };

		//mousepos = {virtual_mouse_pos.x * (virtual_mouse_pos.x / 1920), mousepos.y * (virtual_mouse_pos.y / ((1000 - 175) / image_ratio_divisor)) };


		std::cout << "RATIO X: " << ratio.x << "RATIO Y: " << ratio.y << "\n";

		std::cout << "VIRTUAL MOUSE POS X: " << mousepos.x << "VIRTUAL MOUSE POS Y: " << mousepos.y << "\n";


		return mousepos;
	}


	void DrawFrameBuffer(GLuint screen_image , GLFWwindow* window)
	{

		vec2<int> winsize;

		glfwGetWindowSize(window, &winsize.x, &winsize.y);


		ImGui::SetNextWindowPos(ImVec2(current_win_size.x, 18));
		ImGui::SetNextWindowSize(ImVec2(winsize.x - current_win_size.x, current_win_size.y));


		ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar);

		image_ratio_divisor = 1.1f;

		viewport_size = { 1920 / image_ratio_divisor,1000 / image_ratio_divisor };



		vec2<double> mousepos;

		glfwGetCursorPos(window, &mousepos.x, &mousepos.y);

		std::cout << "MOUSE POS X: " << mousepos.x << "MOUSE POS Y: " << mousepos.y << "\n";



		float image_aspect_ratio = 1920.0f / 1000.0f;
		

		ImGui::SetCursorPos(ImVec2(0, 0));

		
		ImVec2 uv0(0, 1); // Bottom-left corner of texture
		ImVec2 uv1(1, 0);

		
	
		ImGui::Image((void*)(intptr_t)screen_image, ImVec2(viewport_size.x, viewport_size.y), uv0, uv1);



		ImGui::End();

	}

	void ConfigureUI(size_t currentselectedobj ,UIdataPack &data , scene &scene , std::vector<std::string>& logs ,GLuint import_shader , glm::vec4 lightcolor , glm::vec3 lightpos , GLFWwindow* window , std::vector<uint> &auto_rotate_on , GLuint screen_image)
	{

		static bool importmodel_menu = false;

		

		//DrawFrameBuffer(screen_image,window);

		

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // Add File menu items here
               // if (ImGui::MenuItem("Open", "Ctrl+O")) { /* Do something */ }
                //if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do something */ }
				//if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) { /* Do something */ }

				if (ImGui::MenuItem("Import Model", "Ctrl+M"))
				{
					if (!importmodel_menu)
					{

						importmodel_menu = true;
						data.imported = false;

						nfdfilteritem_t filterItem[3] = { { "3D object files", "obj,fbx" }, { "obj", "obj" } , {"fbx","fbx"} };
						nfdresult_t result = NFD_OpenDialog(&data.outPath, filterItem, 3, NULL);
						if (result == NFD_OKAY)
						{
							puts("Success!");
							puts(data.outPath);
						}
						else if (result == NFD_CANCEL)
						{
							puts("User pressed cancel.");
							data.imported = true;
							importmodel_menu = false;
						}
						else
						{
							printf("Error: %s\n", NFD_GetError());
						}



						// The user clicked cancel -- typically do nothing.
					}
				}

				if (importmodel_menu)
				{

					if (data.outPath != nullptr)
					{
						std::string path(data.outPath);

						for (size_t i = 0; i < path.size(); i++)
						{
							if (path.at(i) == '\\')
							{
								path.at(i) = '/';
							}
						}

						std::cout << "NEW PATH: " << path << "\n";

						std::string temp(path);
						scene.ImportModel(temp, import_shader);
						scene.handlelights(import_shader);

						UseShaderProgram(import_shader);

						//glUniformMatrix4fv(glGetUniformLocation(defaultshader.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(pyramidmodel));
						glUniform4f(glGetUniformLocation(import_shader, "lightColor1"), lightcolor.x, lightcolor.y, lightcolor.z, lightcolor.w);
						glUniform3f(glGetUniformLocation(import_shader, "lightpos1"), lightpos.x, lightpos.y, lightpos.z);


						scene.GetModel(scene.GetModelCount() - 1)->transformation.scale(glm::vec3(0.05f, 0.05f, 0.05f));

						std::string logtemp = "A new object is imported!";

						logs.push_back(logtemp);

						data.imported = true;
						importmodel_menu = false;
					}


				}
				if (ImGui::MenuItem("Save Screenshot", "Ctrl + C"))
				{

					if (!data.takesreenshot)
					{

						
					    data.takesreenshot = true;
						

					}
					if (data.takesreenshot)
					{
						nfdfilteritem_t filterItem[2] = { { "Image Files", "png" }, { "png", "png" } };
						nfdresult_t result = NFD_SaveDialog(&data.screenshotPath, filterItem, 2, NULL, NULL);
						if (result == NFD_OKAY)
						{
							puts("Success!");
							puts(data.screenshotPath);
						}
						else if (result == NFD_CANCEL)
						{
							puts("User pressed cancel.");
							data.takesreenshot = false;
						}
						else
						{
							printf("Error: %s\n", NFD_GetError());
						}

						if (data.screenshotPath != nullptr)
						{

							std::string path(data.screenshotPath);

							for (size_t i = 0; i < path.size(); i++)
							{
								if (path.at(i) == '\\')
								{
									path.at(i) = '/';
								}
							}

							data.screenshotPathstr = path;
						}

					}


				}


                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Edit"))
            {
                // Add Edit menu items here
                if (ImGui::MenuItem("Undo", "Ctrl+Z")) { /* Do something */ }
                if (ImGui::MenuItem("Redo", "Ctrl+Y")) { /* Do something */ }
                ImGui::EndMenu();
            }

            // Add additional menus here

            ImGui::EndMainMenuBar();
        }



        FrameBufferSizeCallBack(window);
        



        ImGui::Begin("Settings", (bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse);

       
        ImGui::SetCursorPos(ImVec2(current_win_size.x / 16, current_win_size.y / 20));

        if (ImGui::Button("Object Properties", ImVec2(current_win_size.x / 2.5f, current_win_size.y / 15)))
        {
            data.propertiesbutton = true;
            data.logbutton = false;
        }
		

		if (data.propertiesbutton)
		{
			if (currentselectedobj >= 2)
			{

				if (currentselectedobj == scene.GetModel(currentselectedobj - 2)->GetModelID())
				{
					ImGui::SetCursorPos(ImVec2(current_win_size.x / 18, current_win_size.y / 20 + (current_win_size.y / 12)));


					ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(ImVec4(45 / 255.0, 55 / 255.0, 71 / 255.0, 28 / 255.0)));

					ImGui::BeginChildFrame(66, ImVec2(current_win_size.x / 1.1f, current_win_size.y / 1.3f), ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_AlwaysAutoResize);

					ImGui::PopStyleColor();



					ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(ImVec4(72 / 255.0, 89 / 255.0, 115 / 255.0, 45 / 255.0)));
					ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 40.0f);
					ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 3.0f);

					if (ImGui::CollapsingHeader("General Settings", ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_Framed))
					{
						ImGui::BeginChildFrame(3, ImVec2(380, 150), ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_AlwaysAutoResize);


						static float f = 0.0f;
						static int counter = 0;


						ImGui::SetCursorPos(ImVec2(10, 10));
						ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
						// Edit bools storing our window open/close state
						ImGui::SetCursorPos(ImVec2(10, 20));
						ImGui::Checkbox("Show light meshes", &data.renderlights);

						ImGui::Checkbox("Auto Rotate", &data.autorotate);

						if (data.autorotate)
						{
							bool permitted = true;

							for (size_t i = 0; i < auto_rotate_on.size(); i++)
							{
								if (auto_rotate_on.at(i) == CURRENT_OBJECT(currentselectedobj))
								{
									permitted = false;
								}

							}

							if (permitted)
							{
								auto_rotate_on.push_back(CURRENT_OBJECT(currentselectedobj));
							}

						}
						else
						{

							for (size_t i = 0; i < auto_rotate_on.size(); i++)
							{
								if (auto_rotate_on.at(i) == CURRENT_OBJECT(currentselectedobj))
								{
									auto_rotate_on.erase(auto_rotate_on.begin() + i);
								}

							}

						}

						ImGui::SliderFloat("Rotate object", &data.rotationamount, 0.0f, 360.0f);
						ImGui::SliderFloat("Translate object(x axis)", &data.moveamount.x, 0.0f, data.maxmove.x);
						ImGui::SliderFloat("Translate object(y axis)", &data.moveamount.y, 0.0f, data.maxmove.y);
						ImGui::SliderFloat("Translate object(z axis)", &data.moveamount.z, 0.0f, data.maxmove.z);
						ImGui::SliderFloat("Scale object", &data.scaleamount, 0.1f, data.maxscale);// Edit 1 float using a slider from 0.0f to 1.0f
						ImGui::ColorEdit3("Background color", (float*)&data.clear_color); // Edit 3 floats representing a color
						ImGui::Text("Selected Object: %d", currentselectedobj);



						if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
							counter++;
						ImGui::SameLine();
						ImGui::Text("counter = %d", counter);

						ImGui::EndChildFrame();

					}



					if (ImGui::CollapsingHeader("Input Manuel", ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_Framed))
					{
						ImGui::BeginChildFrame(16, ImVec2(380, 150), ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_AlwaysAutoResize);


						ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
						ImGui::Text("Rotate the camera: Middle mouse button");
						ImGui::Text("Move the camera: W,A,S,D keys");
						ImGui::Text("Faster browsing: Left shift key");
						ImGui::Text("Go up and down: Space and right ctrl keys");
						ImGui::Text("Delete object: Delete key");
						ImGui::Text("Duplicate object: Left ctrl + D keys");

						ImGui::EndChildFrame();

					}



					if (ImGui::CollapsingHeader("Material Settings", ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_Framed))
					{
						ImGui::BeginChildFrame(10, ImVec2(380, 400), ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_AlwaysAutoResize);

						static bool allow_import_texture = false;
						nfdchar_t* texture_path = nullptr;
						int Map_count = 3;





						// Set the background color for the button
						ImVec4 bgColor = ImVec4(0.2f, 0.2f, 0.2f, 1.0f);

						// Push the background color to the Imgui style stack
						ImGui::PushStyleColor(ImGuiCol_Button, bgColor);

						const char* button_info = nullptr;

						int map_type = NULL;
						std::string map_type_string;
						static std::vector<int> button_number;
						static bool button_exists = false;




						for (size_t i = 0; i < scene.models.at(currentselectedobj - 2)->meshes.size(); i++)
						{

							std::vector<int> image_import_buttons;

							for (size_t s = 0; s < Map_count; s++)
							{

								int button_type = NULL;


								if (s % Map_count == 0)
								{
									button_info = "Diffuse Map";
									image_import_buttons.push_back(DIFFUSE_TEXTURE);
									button_type = DIFFUSE_TEXTURE;
									map_type_string = "texture_diffuse";
								}
								else if (s % Map_count == 1)
								{
									button_info = "Specular Map";
									image_import_buttons.push_back(SPECULAR_TEXTURE);
									button_type = SPECULAR_TEXTURE;
									map_type_string = "texture_specular";

								}
								else if (s % Map_count == 2)
								{
									button_info = "Normal Map";
									image_import_buttons.push_back(NORMAL_TEXTURE);
									button_type = NORMAL_TEXTURE;
									map_type_string = "texture_normal";

								}

								uint button_image_id = NULL;
								bool image_button_enabled = false;

								button_info = (scene.models.at(currentselectedobj - 2)->meshes.at(i).meshname + " " + std::string(button_info)).c_str();

								for (size_t v = 0; v < scene.models.at(currentselectedobj - 2)->meshes.at(i).textures.size(); v++)
								{
									if (std::strcmp(scene.models.at(currentselectedobj - 2)->meshes.at(i).textures.at(v).type.data(), map_type_string.data()) == 0)
									{
										button_image_id = scene.models.at(currentselectedobj - 2)->meshes.at(i).textures.at(v).id;
										image_button_enabled = true;
									}

								}


								std::cout << "BUTTON TYPE: " << map_type_string << "\n";
								std::cout << "image_button_enabled: " << image_button_enabled << "\n";



								if (image_button_enabled)
								{
									if (ImGui::ImageButton((void*)(intptr_t)button_image_id, ImVec2(200, 200)))
									{
										button_exists = true;
									}
								}
								else
								{
									if (ImGui::Button(button_info, ImVec2(200, 200)))
									{
										button_exists = true;
										std::cout << "CLICKED ON BUTTON: " << i + 1 << " " << s + 1 << "\n";
									}


								}




								if (button_exists)
								{

									nfdfilteritem_t filterItem[3] = { { "Image files", "PNG,JPG" }, { "PNG", "PNG" } , {"JPG","JPG"} };
									nfdresult_t result = NFD_OpenDialog(&texture_path, filterItem, 3, NULL);

									if (result == NFD_OKAY)
									{
										puts("Success!");
										puts(texture_path);
										allow_import_texture = true;

									}
									else if (result == NFD_CANCEL)
									{
										puts("User pressed cancel.");

									}
									else
									{
										printf("Error: %s\n", NFD_GetError());
									}

									button_exists = false;
								}


								if (allow_import_texture)
								{

									allow_import_texture = false;

									if (texture_path != nullptr)
									{

										Textures newtexture(texture_path, s, GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE, button_type, map_type_string);

										Texture texture;
										texture.id = *newtexture.GetTexture();
										texture.type = newtexture.GetTexturePbrType_str();
										texture.path = newtexture.GetPathData();


										//if (!skip)
										//{   // if texture hasn't been loaded already, load it
										if (scene.models.at(currentselectedobj - 2)->meshes[i].textures.size() >= s + 1)
										{
											if (std::strcmp(scene.models.at(currentselectedobj - 2)->meshes.at(i).textures.at(s).type.data(), texture.type.data()) == 0)
											{
												Texture temp = scene.models.at(currentselectedobj - 2)->meshes[i].textures.at(s);
												scene.models.at(currentselectedobj - 2)->meshes[i].textures.at(s) = texture;
												scene.models.at(currentselectedobj - 2)->textures_loaded.at(s) = texture;  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
												glDeleteTextures(1, &temp.id);
											}
											else
											{
												scene.models.at(currentselectedobj - 2)->meshes[i].textures.push_back(texture);
												scene.models.at(currentselectedobj - 2)->textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.

											}


										}
										else
										{

											scene.models.at(currentselectedobj - 2)->meshes[i].textures.push_back(texture);
											scene.models.at(currentselectedobj - 2)->textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.


										}

										std::cout << "SIZE OF TEXTURES: " << scene.models.at(currentselectedobj - 2)->meshes[i].textures.size() << "\n";
									}


								}





							}

						}


						// Pop the background color from the Imgui style stack
						ImGui::PopStyleColor();


						//}


						ImGui::EndChildFrame();

					}
					ImGui::PopStyleColor();
					ImGui::PopStyleVar();
					ImGui::PopStyleVar();

					ImGui::EndChildFrame();

				}
				// }

			}
			else
			{
				ImGui::BeginGroup();


				static float f = 0.0f;
				static int counter = 0;
				static bool importmodel = false;

				ImGui::SetCursorPos(ImVec2(current_win_size.x / 18, current_win_size.y / 20 + (current_win_size.y / 12)));


				ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(ImVec4(45 / 255.0, 55 / 255.0, 71 / 255.0, 28 / 255.0)));
				ImGui::BeginChildFrame(66, ImVec2(current_win_size.x / 1.1f, current_win_size.y / 1.3f), ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_AlwaysAutoResize);

				ImGui::PopStyleColor();
				//ImGui::PushStyleColor(ImGuiCol_Header | , ImGui::ColorConvertFloat4ToU32(ImVec4(80 / 255.0, 40 / 255.0, 250 / 255.0, 98 / 255.0)));
				//ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.2f, 0.2f, 1.0f)); // Set the background color of the header
				//ImGui::PushStyleVar(Imguistylevarbackground, ImVec2(0, 0)); // Set the background color of what's under the header to be the same as the window
				ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(ImVec4(72 / 255.0, 89 / 255.0, 115 / 255.0, 45 / 255.0)));
				ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 40.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 3.0f);

				if (ImGui::CollapsingHeader("General Settings", ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_Framed))
				{
					ImGui::BeginChildFrame(33, ImVec2(380, 150), ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_AlwaysAutoResize);

					//ImGui::SetCursorPos(ImVec2(10, 10));
					ImGui::Checkbox("selection highlight", &data.enablehighlight);
					//ImGui::SetCursorPos(ImVec2(10, 40));
					ImGui::ColorEdit3("Background color", (float*)&data.clear_color); // Edit 3 floats representing a color
					//ImGui::SetCursorPos(ImVec2(10, 70));
					ImGui::Text("Selected Object: %d", currentselectedobj);
					//ImGui::SetCursorPos(ImVec2(10, 100));
					ImGui::Text("Current existing object count: %d", scene.GetModelCount());
					//ImGui::SetCursorPos(ImVec2(10, 130));
					if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
						counter++;
					ImGui::SameLine();
					ImGui::Text("counter = %d", counter);

					ImGui::EndChildFrame();




				}
				ImGui::PopStyleColor();
				ImGui::PopStyleVar();
				ImGui::PopStyleVar();


				ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(ImVec4(72 / 255.0, 89 / 255.0, 115 / 255.0, 45 / 255.0)));
				ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 40.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 3.0f);

				if (ImGui::CollapsingHeader("Input manuel", ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_Framed))
				{
					ImGui::BeginChildFrame(7, ImVec2(380, 150), ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_AlwaysAutoResize);

					//ImGui::SetCursorPos(ImVec2(10, 160));
					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
					//ImGui::SetCursorPos(ImVec2(10, 190));
					ImGui::Text("Rotate the camera: Middle mouse button");
					//ImGui::SetCursorPos(ImVec2(10, 205));
					ImGui::Text("Move the camera: W,A,S,D keys");
					//ImGui::SetCursorPos(ImVec2(10, 220));
					ImGui::Text("Faster browsing: Left shift key");
					//ImGui::SetCursorPos(ImVec2(10, 235));
					ImGui::Text("Go up and down: Space and right ctrl keys");
					//ImGui::SetCursorPos(ImVec2(10, 250));
					ImGui::Text("Delete object: Delete key");
					//ImGui::SetCursorPos(ImVec2(10, 265));
					ImGui::Text("Duplicate object: Left ctrl + D keys");

					ImGui::EndChildFrame();

				}
				ImGui::PopStyleColor();
				ImGui::PopStyleVar();
				ImGui::PopStyleVar();

				if (!importmodel)
				{
					//ImGui::SetCursorPos(ImVec2(10, 300));

					ImGui::Text("Import 3D model: ");

					//ImGui::SetCursorPos(ImVec2(130, 290));

					ImGui::SameLine();

					if (ImGui::Button("Import Model", ImVec2(100, 40)))
					{
						importmodel = true;
						data.imported = false;

						nfdfilteritem_t filterItem[3] = { { "3D object files", "obj,fbx" }, { "obj", "obj" } , {"fbx","fbx"} };
						nfdresult_t result = NFD_OpenDialog(&data.outPath, filterItem, 3, NULL);
						if (result == NFD_OKAY)
						{
							puts("Success!");
							puts(data.outPath);
						}
						else if (result == NFD_CANCEL)
						{
							puts("User pressed cancel.");
							data.imported = true;
							importmodel = false;
						}
						else
						{
							printf("Error: %s\n", NFD_GetError());
						}
					}


					// The user clicked cancel -- typically do nothing.
				}

				if (importmodel)
				{

					if (data.outPath != nullptr)
					{
						std::string path(data.outPath);

						for (size_t i = 0; i < path.size(); i++)
						{
							if (path.at(i) == '\\')
							{
								path.at(i) = '/';
							}
						}

						std::cout << "NEW PATH: " << path << "\n";

						std::string temp(path);
						scene.ImportModel(temp, import_shader);
						scene.handlelights(import_shader);

						UseShaderProgram(import_shader);

						//glUniformMatrix4fv(glGetUniformLocation(defaultshader.GetID(), "model"), 1, GL_FALSE, glm::value_ptr(pyramidmodel));
						glUniform4f(glGetUniformLocation(import_shader, "lightColor1"), lightcolor.x, lightcolor.y, lightcolor.z, lightcolor.w);
						glUniform3f(glGetUniformLocation(import_shader, "lightpos1"), lightpos.x, lightpos.y, lightpos.z);


						scene.GetModel(scene.GetModelCount() - 1)->transformation.scale(glm::vec3(0.05f, 0.05f, 0.05f));

						std::string logtemp = "A new object is imported!";

						logs.push_back(logtemp);

						data.imported = true;
						importmodel = false;
					}


				}


				if (!data.takesreenshot)
				{

					//ImGui::SetCursorPos(ImVec2(10, 360));
					ImGui::Text("");
					ImGui::Text("Save screenshot: ");

					//ImGui::SetCursorPos(ImVec2(130, 350));
					ImGui::SameLine();

					if (ImGui::Button("Save Screenshot", ImVec2(120, 40)))
					{
						data.takesreenshot = true;
					}

				}
				if (data.takesreenshot)
				{
					nfdfilteritem_t filterItem[2] = { { "Image Files", "png" }, { "png", "png" } };
					nfdresult_t result = NFD_SaveDialog(&data.screenshotPath, filterItem, 2, NULL, NULL);
					if (result == NFD_OKAY)
					{
						puts("Success!");
						puts(data.screenshotPath);
					}
					else if (result == NFD_CANCEL)
					{
						puts("User pressed cancel.");
						data.takesreenshot = false;
					}
					else
					{
						printf("Error: %s\n", NFD_GetError());
					}

					if (data.screenshotPath != nullptr)
					{

						std::string path(data.screenshotPath);

						for (size_t i = 0; i < path.size(); i++)
						{
							if (path.at(i) == '\\')
							{
								path.at(i) = '/';
							}
						}

						data.screenshotPathstr = path;
					}

				}


				ImGui::EndChildFrame();

				ImGui::PopStyleColor();

				ImGui::EndGroup();

			}
		}


        ImGui::SetCursorPos(ImVec2(current_win_size.x / 1.8f, current_win_size.y / 20));

        //ImGui::SameLine();

        if (ImGui::Button("Logs", ImVec2(current_win_size.x / 2.5f, current_win_size.y / 15)))
        {
            data.propertiesbutton = false;;
            data.logbutton = true;
        }

        if (data.logbutton)
        {

			ImGui::SetCursorPos(ImVec2(current_win_size.x / 18, current_win_size.y / 20 + (current_win_size.y / 12)));


			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(ImVec4(150 / 255.0, 188 / 255.0, 250 / 255.0, 98 / 255.0)));
			ImGui::BeginChildFrame(88, ImVec2(current_win_size.x / 1.1f, current_win_size.y / 1.3f), ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_AlwaysAutoResize);

			ImGui::Text("THIS IS LOG TAB");

			if (logs.size() >= 1)
			{
				for (size_t i = 0; i < logs.size(); i++)
				{
					ImGui::Text(logs.at(i).c_str());
				}
			}

			ImGui::EndChildFrame();

			ImGui::PopStyleColor();

			ImGui::EndTabItem();


        }



        ImGui::End();



	}

}

#endif // !UI

