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
#include <tuple>


typedef std::tuple<ImVec4, ImVec4, ImVec4 , ImVec4, ImVec4 , ImVec4> color_sheme_t;
// Dark theme color values
#define DARK_THEME color_sheme_t(ImVec4(0.1f, 0.1f, 0.1f, 1.0f), ImVec4(0.2f, 0.2f, 0.2f, 1.0f), ImVec4(0.25f, 0.25f, 0.25f, 1.0f), ImVec4(0.4f, 0.4f, 0.4f, 1.0f), ImVec4(0.8f, 0.8f, 0.8f, 1.0f),ImVec4(0.041f, 0.041f, 0.044f, 0.00f))
#define LIGHT_THEME color_sheme_t(ImVec4(0.9f, 0.9f, 0.9f, 1.0f), ImVec4(0.8f, 0.8f, 0.8f, 1.0f), ImVec4(0.7f, 0.7f, 0.7f, 1.0f), ImVec4(0.6f, 0.6f, 0.6f, 1.0f), ImVec4(0.2f, 0.2f, 0.2f, 1.0f),ImVec4(0.5f, 0.5f, 0.5f, 1.0f))
#define BLUE_THEME color_sheme_t(ImVec4(0.1f, 0.1f, 0.3f, 1.0f), ImVec4(0.2f, 0.2f, 0.6f, 1.0f), ImVec4(0.25f, 0.25f, 0.3f, 1.0f), ImVec4(0.4f, 0.4f, 0.4f, 1.0f), ImVec4(0.8f, 0.8f, 0.8f, 1.0f), ImVec4(0.041f, 0.041f, 0.044f, 0.00f))
#define CUSTOM_THEME color_sheme_t(ImVec4(0.3f, 0.3f, 0.3f, 1.0f), ImVec4(0.4f, 0.4f, 0.4f, 1.0f), ImVec4(0.35f, 0.35f, 0.35f, 1.0f),  ImVec4(0.7f, 0.7f, 0.7f, 1.0f), ImVec4(0.9f, 0.9f, 0.9f, 1.0f), ImVec4(0.1f, 0.1f, 0.1f, 1.0f))
#define PINK_THEME color_sheme_t(ImVec4(0.3f, 0.1f, 0.1f, 1.0f), ImVec4(0.6f, 0.2f, 0.2f, 1.0f), ImVec4(0.3f, 0.25f, 0.25f, 1.0f), ImVec4(0.4f, 0.4f, 0.4f, 1.0f), ImVec4(0.8f, 0.8f, 0.8f, 1.0f), ImVec4(0.044f, 0.041f, 0.041f, 0.00f))
#define CYAN_THEME color_sheme_t(ImVec4(0.0f, 0.2f, 0.2f, 1.0f), ImVec4(0.0f, 0.4f, 0.4f, 1.0f), ImVec4(0.0f, 0.5f, 0.5f, 1.0f), ImVec4(0.0f, 0.8f, 0.8f, 1.0f), ImVec4(0.8f, 0.8f, 0.8f, 1.0f), ImVec4(0.0f, 0.0f, 0.0f, 0.0f))
#define ORANGE_THEME color_sheme_t(ImVec4(0.8f, 0.4f, 0.1f, 1.0f), ImVec4(1.0f, 0.5f, 0.2f, 1.0f), ImVec4(1.0f, 0.6f, 0.3f, 1.0f), ImVec4(1.0f, 0.7f, 0.4f, 1.0f), ImVec4(0.8f, 0.8f, 0.8f, 1.0f), ImVec4(0.0f, 0.0f, 0.0f, 0.0f))
#define GREEN_THEME color_sheme_t(ImVec4(0.1f, 0.3f, 0.1f, 1.0f), ImVec4(0.2f, 0.5f, 0.2f, 1.0f), ImVec4(0.25f, 0.6f, 0.25f, 1.0f), ImVec4(0.4f, 0.7f, 0.4f, 1.0f), ImVec4(0.8f, 0.8f, 0.8f, 1.0f), ImVec4(0.0f, 0.0f, 0.0f, 0.0f))
#define NORDIC_THEME color_sheme_t(ImVec4(0.05f, 0.05f, 0.05f, 1.0f), ImVec4(0.16f, 0.23f, 0.24f, 1.0f), ImVec4(0.20f, 0.29f, 0.30f, 1.0f), ImVec4(0.26f, 0.35f, 0.36f, 1.0f), ImVec4(0.85f, 0.85f, 0.85f, 1.0f), ImVec4(0.0f, 0.0f, 0.0f, 0.0f))
#define GITHUB_STYLE_THEME color_sheme_t(ImVec4(0.13f, 0.17f, 0.23f, 1.0f), ImVec4(0.18f, 0.22f, 0.28f, 1.0f), ImVec4(0.22f, 0.26f, 0.32f, 1.0f), ImVec4(0.28f, 0.32f, 0.38f, 1.0f), ImVec4(0.8f, 0.8f, 0.8f, 1.0f), ImVec4(0.0f, 0.0f, 0.0f, 0.0f))
#define INTELLIJ_STYLE_THEME color_sheme_t(ImVec4(0.95f, 0.95f, 0.95f, 1.0f), ImVec4(0.25f, 0.27f, 0.30f, 1.0f), ImVec4(0.2f, 0.22f, 0.25f, 1.0f), ImVec4(0.12f, 0.14f, 0.17f, 1.0f), ImVec4(0.38f, 0.40f, 0.43f, 1.0f), ImVec4(0.6f, 0.63f, 0.66f, 1.0f))
#define CHATGPT_LIGHT_THEME color_sheme_t(ImVec4(0.95f, 0.95f, 0.95f, 1.0f), ImVec4(1.0f, 1.0f, 1.0f, 1.0f), ImVec4(0.9f, 0.9f, 0.9f, 1.0f), ImVec4(0.8f, 0.8f, 0.8f, 1.0f), ImVec4(0.2f, 0.2f, 0.2f, 1.0f), ImVec4(0.1f, 0.1f, 0.1f, 1.0f))
#define SUNSET_THEME color_sheme_t(ImVec4(0.95f, 0.85f, 0.80f, 1.0f), ImVec4(0.54f, 0.29f, 0.31f, 1.0f), ImVec4(0.45f, 0.22f, 0.25f, 1.0f), ImVec4(0.35f, 0.16f, 0.20f, 1.0f), ImVec4(0.68f, 0.41f, 0.31f, 1.0f), ImVec4(0.89f, 0.56f, 0.41f, 1.0f))
#define OCEANIC_THEME color_sheme_t(ImVec4(0.15f, 0.20f, 0.25f, 1.0f), ImVec4(0.23f, 0.35f, 0.42f, 1.0f), ImVec4(0.19f, 0.28f, 0.35f, 1.0f), ImVec4(0.16f, 0.22f, 0.28f, 1.0f), ImVec4(0.37f, 0.54f, 0.63f, 1.0f), ImVec4(0.48f, 0.71f, 0.84f, 1.0f))
#define VINTAGE_THEME color_sheme_t(ImVec4(0.95f, 0.92f, 0.82f, 1.0f), ImVec4(0.51f, 0.39f, 0.31f, 1.0f), ImVec4(0.42f, 0.32f, 0.25f, 1.0f), ImVec4(0.35f, 0.26f, 0.20f, 1.0f), ImVec4(0.66f, 0.50f, 0.40f, 1.0f), ImVec4(0.82f, 0.64f, 0.51f, 1.0f))
#define MINTY_FRESH_THEME color_sheme_t(ImVec4(0.87f, 0.98f, 0.93f, 1.0f), ImVec4(0.21f, 0.55f, 0.40f, 1.0f), ImVec4(0.17f, 0.46f, 0.33f, 1.0f), ImVec4(0.13f, 0.36f, 0.26f, 1.0f), ImVec4(0.31f, 0.73f, 0.56f, 1.0f), ImVec4(0.48f, 0.85f, 0.65f, 1.0f))
#define ROYAL_PURPLE_THEME color_sheme_t(ImVec4(0.85f, 0.80f, 0.95f, 1.0f), ImVec4(0.37f, 0.20f, 0.54f, 1.0f), ImVec4(0.31f, 0.22f, 0.45f, 1.0f), ImVec4(0.25f, 0.16f, 0.35f, 1.0f), ImVec4(0.47f, 0.41f, 0.68f, 1.0f), ImVec4(0.61f, 0.56f, 0.89f, 1.0f))


namespace UI
{
	struct UIcolorShemePack
	{
		ImVec4 MenuBackgroundColor;
		ImVec4 ChildMenuColor;
		ImVec4 MidMenuColor;
		ImVec4 BorderColor;
		ImVec4 TextColor;
		ImVec4 ViewportBackgroundColor;

		void SetMenuBackgroundColor(ImVec4 mbgcolor)
		{
			MenuBackgroundColor = mbgcolor;
		}

		void SetChildMenuColor(ImVec4 cmcolor)
		{
			ChildMenuColor = cmcolor;
		}

		void operator()(const color_sheme_t &color_sh) 
		{
			MenuBackgroundColor = std::get<0>(color_sh);
			ChildMenuColor = std::get<1>(color_sh);
			MidMenuColor = std::get<2>(color_sh);
			BorderColor = std::get<3>(color_sh);
			TextColor = std::get<4>(color_sh);
			ViewportBackgroundColor = std::get<5>(color_sh);
		}

	};

	vec2<int> current_win_size = { (1000/5.4f),1000-18 };
	vec2<int> current_viewport_size;
	vec2<float> ApplicationSettingSizes;
	vec2<float> viewport_size;
	float image_ratio_divisor = NULL;

	UIcolorShemePack current_color_sheme;
	color_sheme_t chosen_color_sheme = DARK_THEME;

	
    struct UIdataPack
    {
        bool renderlights = false;
        ImVec4 clear_color = ImVec4(0.041f, 0.041f, 0.044f, 0.00f);

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

		bool render_cube_map = false;

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

	void SetStyle(UI::UIdataPack &data)
	{
		ImGuiStyle &style = ImGui::GetStyle();

		current_color_sheme(chosen_color_sheme);

		data.clear_color = current_color_sheme.ViewportBackgroundColor;

		style.Colors[ImGuiCol_Text] = current_color_sheme.TextColor; 
		style.Colors[ImGuiCol_WindowBg] = current_color_sheme.MenuBackgroundColor;
		style.Colors[ImGuiCol_Border] = current_color_sheme.BorderColor;
		style.Colors[ImGuiCol_MenuBarBg] = current_color_sheme.MenuBackgroundColor;

	

		style.FrameRounding = 5.0f;
		style.ItemSpacing = ImVec2(20, 10);
		style.ChildBorderSize = 1.3f;
		style.FrameBorderSize = 1.3f;
		style.Alpha = 0.9f;
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

	void FindCurrentViewportSize(GLFWwindow* window)
	{
		int height = NULL, width = NULL;
		glfwGetWindowSize(window, &width, &height);

		current_viewport_size = { width - current_win_size.x , current_win_size.y};

	}

	vec2<double> CalculateVirtualMouse(GLFWwindow* window)
	{
		vec2<double> mousepos;
		glfwGetCursorPos(window, &mousepos.x, &mousepos.y);

		vec2<double> virtual_mouse_pos;

		virtual_mouse_pos.x = (mousepos.x ) - current_win_size.x;
		virtual_mouse_pos.y = (mousepos.y - 37);

		std::cout << "VIRTUAL MOUSE POS X: " << virtual_mouse_pos.x << "VIRTUAL MOUSE POS Y: " << mousepos.y << "\n";

		int height = NULL, width = NULL;
		glfwGetWindowSize(window, &width, &height);
		

		mousepos = { (current_viewport_size.x *virtual_mouse_pos.x) / current_viewport_size.x, (current_viewport_size.y * virtual_mouse_pos.y) / current_viewport_size.y};

		std::cout << "MOUSE POS X: " << mousepos.x << "MOUSE POS Y: " << mousepos.y << "\n";


		return mousepos;
	}


	void DrawFrameBuffer(GLuint screen_image , GLFWwindow* window)
	{

		static float max_viewport_size_y = -std::numeric_limits<float>::infinity();

		vec2<int> winsize;

		glfwGetWindowSize(window, &winsize.x, &winsize.y);

		max_viewport_size_y = std::max(max_viewport_size_y, (float)current_viewport_size.y);


		ImGui::SetNextWindowPos(ImVec2(current_win_size.x, 18));
		ImGui::SetNextWindowSize(ImVec2(winsize.x - current_win_size.x, current_win_size.y));

		//ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.MidMenuColor));

		ImGui::Begin("Viewport", (bool*)0, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		
		image_ratio_divisor = 1.1f;

		viewport_size = { 1920/image_ratio_divisor ,1000/image_ratio_divisor};


		float image_aspect_ratio = 1920.0f / 1000.0f;

		

		ImGui::SetCursorPos(ImVec2(0, current_win_size.y - max_viewport_size_y ));

		
		ImVec2 uv0(0, 1); // Bottom-left corner of texture
		ImVec2 uv1(1, 0);

		//glEnable(GL_FRAMEBUFFER_SRGB);
		//ImGui::Image((void*)(intptr_t)screen_image, ImVec2(viewport_size.x, viewport_size.y), uv0, uv1);
		ImGui::Image((void*)(intptr_t)screen_image, ImVec2(1920, 1080), uv0, uv1);

		//glDisable(GL_FRAMEBUFFER_SRGB);

		
		ImGui::SetCursorPos(ImVec2(winsize.x / 1.3f, winsize.y / 30.0f));

		ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);



		ImGui::End();

		//ImGui::PopStyleColor();

	}

	void DoUIobjectTransformations(size_t currentselectedobj, scene& scene, UI::UIdataPack& data)
	{
		if (currentselectedobj >= 2)
		{


			scene.GetModel(currentselectedobj - 2)->transformation.translate(glm::vec3(data.moveamount.x, data.moveamount.y, data.moveamount.z));

			scene.GetModel(CURRENT_OBJECT(currentselectedobj))->dynamic_origin += glm::vec3(data.moveamount.x, data.moveamount.y, data.moveamount.z);


			if (data.scaleamount != 0.0f)
			{
				scene.GetModel(currentselectedobj - 2)->transformation.scale(glm::vec3(data.scaleamount, data.scaleamount, data.scaleamount));

				scene.RecalculateObjectScales(currentselectedobj, glm::vec3(data.scaleamount, data.scaleamount, data.scaleamount));

			}


			scene.GetModel(currentselectedobj - 2)->transformation.rotate(data.rotationamount, glm::vec3(0.0f, 1.0f, 0.0f));




			scene.GetModel(currentselectedobj - 2)->transformation.translate(glm::vec3(0.0f, 0.0f, 0.0f));




			scene.GetModel(currentselectedobj - 2)->transformation.translate(-glm::vec3(0.0f, 0.0f, 0.0f));


		}

	}

	void DoUIobjectReTransformations(size_t currentselectedobj , scene &scene , UI::UIdataPack &data)
	{
		if (currentselectedobj >= 2)
		{

			scene.GetModel(currentselectedobj - 2)->transformation.translate(glm::vec3(0.0f, 0.0f, 0.0f));


			scene.GetModel(currentselectedobj - 2)->transformation.rotate(-data.rotationamount, glm::vec3(0.0f, 1.0f, 0.0f));

			scene.GetModel(currentselectedobj - 2)->transformation.translate(-glm::vec3(0.0f, 0.0f, 0.0f));


			scene.GetModel(currentselectedobj - 2)->transformation.scale(glm::vec3(1 / data.scaleamount, 1 / data.scaleamount, 1 / data.scaleamount));


			scene.GetModel(currentselectedobj - 2)->transformation.translate(-glm::vec3(data.moveamount.x, data.moveamount.y, data.moveamount.z));

			scene.GetModel(CURRENT_OBJECT(currentselectedobj))->dynamic_origin -= glm::vec3(data.moveamount.x, data.moveamount.y, data.moveamount.z);


		}

	}

	void HandleSliderMaxValues(UI::UIdataPack &data , GLFWwindow *window)
	{

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


	}

	void HandleAutoRotation(int &currentselectedobj , scene &scene ,std::vector<uint> &auto_rotate_on)
	{
		for (size_t i = 0; i < auto_rotate_on.size(); i++)
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

		for (size_t i = 0; i < auto_rotate_on.size(); i++)
		{
			if (auto_rotate_on.at(i) != CURRENT_OBJECT(currentselectedobj))
			{
				scene.GetModel(auto_rotate_on.at(i))->transformation.translate(glm::vec3(0.0f, 0.0f, 0.0f));

				scene.GetModel(auto_rotate_on.at(i))->transformation.rotate(scene.GetModel(auto_rotate_on.at(i))->UIprop.rotationamount, glm::vec3(0.0f, 1.0f, 0.0f));

				scene.GetModel(auto_rotate_on.at(i))->transformation.translate(-glm::vec3(0.0f, 0.0f, 0.0f));

			}

		}

	}

	void HandleReverseAutoTranslation(size_t currentselectedobj , scene &scene , std::vector<uint>& auto_rotate_on)
	{

		for (size_t i = 0; i < auto_rotate_on.size(); i++)
		{
			if (auto_rotate_on.at(i) != CURRENT_OBJECT(currentselectedobj))
			{

				scene.GetModel(auto_rotate_on.at(i))->transformation.translate(glm::vec3(0.0f, 0.0f, 0.0f));

				scene.GetModel(auto_rotate_on.at(i))->transformation.rotate(-scene.GetModel(auto_rotate_on.at(i))->UIprop.rotationamount, glm::vec3(0.0f, 1.0f, 0.0f));

				scene.GetModel(auto_rotate_on.at(i))->transformation.translate(-glm::vec3(0.0f, 0.0f, 0.0f));

			}
		}

	}

	void IncrementRotationDegree(UI::UIdataPack &data)
	{
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

	}


	void ConfigureUI(size_t currentselectedobj ,UIdataPack &data , scene &scene , std::vector<std::string>& logs ,GLuint import_shader , glm::vec4 lightcolor , glm::vec3 lightpos , GLFWwindow* window , std::vector<uint> &auto_rotate_on , GLuint screen_image,GLuint light_shader, int currentselectedlight)
	{

		static bool importmodel_menu = false;
		static bool ApplicationMenuEnabled = false;

		//current_color_sheme(DARK_THEME);
		

		//DrawFrameBuffer(screen_image,window);

		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.MidMenuColor));


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

			if (ImGui::BeginMenu("Add"))
			{
				if (ImGui::BeginMenu("Lights"))
				{

					if (ImGui::MenuItem("Directional Light", "Ctrl+L+D"))
					{
						scene.Addlight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), light_shader, CUBE_LIGHT, DIRECTIONAL_LIGHT);
						scene.handlelights(import_shader);
					}
					if (ImGui::MenuItem("Spot Light", "Ctrl+L+S"))
					{
						scene.Addlight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), light_shader, CUBE_LIGHT, SPOT_LIGHT);
						scene.handlelights(import_shader);
					}
					if (ImGui::MenuItem("Point Light", "Ctrl+L+P"))
					{
						scene.Addlight(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), light_shader, CUBE_LIGHT, POINT_LIGHT);
						scene.handlelights(import_shader);
					}

					ImGui::EndMenu();
				}

				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("About"))
			{
				if (ImGui::MenuItem("Application Settings", "Ctrl+A+S"))
				{

					ApplicationMenuEnabled = true;
					
				}


				ImGui::EndMenu();
			}

            // Add additional menus here

            ImGui::EndMainMenuBar();
        }

		ImGui::PopStyleColor();

		if (ApplicationMenuEnabled)
		{
			vec2<int> win_size = { NULL,NULL };

			glfwGetWindowSize(window, &win_size.x, &win_size.y);

			ApplicationSettingSizes = { win_size.x / 2.0f , win_size.y / 2.0f };
			ImVec2 ApplicationSettingPosition = ImVec2((win_size.x / 2) - (ApplicationSettingSizes.x / 2), (win_size.y / 2) - (ApplicationSettingSizes.y / 2));

			ImGui::SetNextWindowSize(ImVec2(ApplicationSettingSizes.x, ApplicationSettingSizes.y));
			ImGui::SetNextWindowPos(ApplicationSettingPosition , ImGuiCond_FirstUseEver);

			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.ChildMenuColor));

			ImGui::Begin("Application Settings", &ApplicationMenuEnabled, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse);

			ApplicationSettingPosition = ImGui::GetWindowPos();

			ImVec2 Max = ImVec2(ApplicationSettingPosition.x + (ApplicationSettingSizes.x ) , ApplicationSettingPosition.y + (ApplicationSettingSizes.y ));
			ImVec2 Min = ImVec2(ApplicationSettingPosition.x - (ApplicationSettingSizes.x ), ApplicationSettingPosition.y - (ApplicationSettingSizes.y ));

			//std::cout << "MAX WINDOW: " << Max.x << " "<<Max.y << "Hovered: "<< ImGui::IsMouseHoveringRect(Min, Max) << "\n";
			//std::cout << "MIN WINDOW: " << Min.x << " " << Min.y << "Hovered: " << ImGui::IsMouseHoveringRect(Min, Max) << "\n";

			if (!ImGui::IsMouseHoveringRect(Min, Max) && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			{
				
				ApplicationMenuEnabled = false;
				
			}

			static bool showDropdown = false; 

			
			
			if (ImGui::BeginCombo("Set Application Color Theme", "Select an option", ImGuiComboFlags_NoPreview))
			{
				
				if (ImGui::Selectable("DARK THEME"))
				{
					
					chosen_color_sheme = DARK_THEME;
					
					showDropdown = false; 
				}
				if (ImGui::Selectable("LIGHT THEME"))
				{
					
					chosen_color_sheme = LIGHT_THEME;
					
					showDropdown = false; 
				}
				if (ImGui::Selectable("BLUE THEME"))
				{
					
					chosen_color_sheme = BLUE_THEME;
					
					showDropdown = false; 
				}
				if (ImGui::Selectable("CUSTOM THEME"))
				{
					
					chosen_color_sheme = CUSTOM_THEME;
					
					showDropdown = false; 
				}
				if (ImGui::Selectable("PINK THEME"))
				{
					
					chosen_color_sheme = PINK_THEME;
					
					showDropdown = false; 
				}
				if (ImGui::Selectable("CYAN THEME"))
				{
					chosen_color_sheme = CYAN_THEME;
					showDropdown = false; 
				}
				if (ImGui::Selectable("ORANGE THEME"))
				{
					chosen_color_sheme = ORANGE_THEME;
					showDropdown = false;
				}
				if (ImGui::Selectable("GREEN THEME"))
				{
					chosen_color_sheme = GREEN_THEME;
					showDropdown = false;
				}
				if (ImGui::Selectable("NORDIC THEME"))
				{
					chosen_color_sheme = NORDIC_THEME;
					showDropdown = false;
				}
				if (ImGui::Selectable("GITHUB STYLED THEME"))
				{
					chosen_color_sheme = GITHUB_STYLE_THEME;
					showDropdown = false;
				}
				if (ImGui::Selectable("INTELLIJ STYLED THEME"))
				{
					chosen_color_sheme = INTELLIJ_STYLE_THEME;
					showDropdown = false;
				}
				if (ImGui::Selectable("CHATGPT LIGHT MODE STYLED THEME"))
				{
					chosen_color_sheme = CHATGPT_LIGHT_THEME;
					showDropdown = false;
				}
				if (ImGui::Selectable("SUNSET THEME"))
				{
					chosen_color_sheme = SUNSET_THEME;
					showDropdown = false;
				}
				if (ImGui::Selectable("OCEANIC THEME"))
				{
					chosen_color_sheme = OCEANIC_THEME;
					showDropdown = false;
				}
				if (ImGui::Selectable("VINTAGE THEME"))
				{
					chosen_color_sheme = VINTAGE_THEME;
					showDropdown = false;
				}
				if (ImGui::Selectable("MINTY FRESH THEME"))
				{
					chosen_color_sheme = MINTY_FRESH_THEME;
					showDropdown = false;
				}
				if (ImGui::Selectable("ROYAL PURPLE THEME"))
				{
					chosen_color_sheme = ROYAL_PURPLE_THEME;
					showDropdown = false;
				}
				
				
				ImGui::EndCombo();
			}

			
			if (!ImGui::IsPopupOpen("##Dropdown"))
			{
				showDropdown = false;
			}
		    



			ImGui::End();

			ImGui::PopStyleColor();
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


					//ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(ImVec4(45 / 255.0, 55 / 255.0, 71 / 255.0, 28 / 255.0)));

					ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.MidMenuColor));

					ImGui::BeginChildFrame(66, ImVec2(current_win_size.x / 1.1f, current_win_size.y / 1.3f), ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_AlwaysAutoResize);

					ImGui::PopStyleColor();



					//ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(ImVec4(72 / 255.0, 89 / 255.0, 115 / 255.0, 45 / 255.0)));
					//ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.MenuBackgroundColor));
					ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.ChildMenuColor));
					ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 40.0f);
					ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 3.0f);

					if (ImGui::CollapsingHeader("Model General Settings", ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_Framed))
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
						int Map_count = 4;





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
								else if (s % Map_count == 3)
								{
									button_info = "Metalic Map";
									image_import_buttons.push_back(METALIC_TEXTURE);
									button_type = METALIC_TEXTURE;
									map_type_string = "texture_metalic";

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

										Textures newtexture(texture_path, s, GL_TEXTURE_2D, GL_UNSIGNED_BYTE, button_type, map_type_string);

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
			else if (scene.CURRENT_LIGHT(currentselectedlight) >= NULL)
			{

				ImGui::BeginGroup();


				static float f = 0.0f;
				static int counter = 0;
				static bool importmodel = false;

				ImGui::SetCursorPos(ImVec2(current_win_size.x / 18, current_win_size.y / 20 + (current_win_size.y / 12)));


				//ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(ImVec4(45 / 255.0, 55 / 255.0, 71 / 255.0, 28 / 255.0)));
				//ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.MenuBackgroundColor));
				//ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.ChildMenuColor));

				ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.MidMenuColor));

				ImGui::BeginChildFrame(66, ImVec2(current_win_size.x / 1.1f, current_win_size.y / 1.3f), ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_AlwaysAutoResize);

				ImGui::PopStyleColor();
				//ImGui::PushStyleColor(ImGuiCol_Header | , ImGui::ColorConvertFloat4ToU32(ImVec4(80 / 255.0, 40 / 255.0, 250 / 255.0, 98 / 255.0)));
				//ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.2f, 0.2f, 1.0f)); // Set the background color of the header
				//ImGui::PushStyleVar(Imguistylevarbackground, ImVec2(0, 0)); // Set the background color of what's under the header to be the same as the window
				//ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(ImVec4(72 / 255.0, 89 / 255.0, 115 / 255.0, 45 / 255.0)));
				ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.ChildMenuColor));

				ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 40.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 3.0f);

				if (ImGui::CollapsingHeader("Light General Settings", ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_Framed))
				{
					ImGui::BeginChildFrame(33, ImVec2(380, 150), ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_AlwaysAutoResize);

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

				if (ImGui::CollapsingHeader("Light Settings", ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_Framed))
				{
					ImGui::BeginChildFrame(7, ImVec2(380, 150), ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_AlwaysAutoResize);





					ImGui::EndChildFrame();
				}

				ImGui::PopStyleColor();
				ImGui::PopStyleVar();
				ImGui::PopStyleVar();


				ImGui::EndChildFrame();

				ImGui::PopStyleColor();

				ImGui::EndGroup();


			}
			else
			{
				ImGui::BeginGroup();


				static float f = 0.0f;
				static int counter = 0;
				static bool importmodel = false;

				ImGui::SetCursorPos(ImVec2(current_win_size.x / 18, current_win_size.y / 20 + (current_win_size.y / 12)));


				//ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(ImVec4(45 / 255.0, 55 / 255.0, 71 / 255.0, 28 / 255.0)));
				//ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.ChildMenuColor));

				ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.MidMenuColor));

				ImGui::BeginChildFrame(66, ImVec2(current_win_size.x / 1.1f, current_win_size.y / 1.3f), ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_AlwaysAutoResize);

				ImGui::PopStyleColor();
				//ImGui::PushStyleColor(ImGuiCol_Header | , ImGui::ColorConvertFloat4ToU32(ImVec4(80 / 255.0, 40 / 255.0, 250 / 255.0, 98 / 255.0)));
				//ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.2f, 0.2f, 1.0f)); // Set the background color of the header
				//ImGui::PushStyleVar(Imguistylevarbackground, ImVec2(0, 0)); // Set the background color of what's under the header to be the same as the window
				//ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(ImVec4(72 / 255.0, 89 / 255.0, 115 / 255.0, 45 / 255.0)));
				ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.ChildMenuColor));
				ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 40.0f);
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 3.0f);

				if (ImGui::CollapsingHeader("General Settings", ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_Framed))
				{
					ImGui::BeginChildFrame(33, ImVec2(380, 150), ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_AlwaysAutoResize);

					//ImGui::SetCursorPos(ImVec2(10, 10));
					ImGui::Checkbox(" Enable Skybox", &data.render_cube_map);

					ImGui::Checkbox("Show light meshes", &data.renderlights);

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


				//ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(ImVec4(72 / 255.0, 89 / 255.0, 115 / 255.0, 45 / 255.0)));
				ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.ChildMenuColor));
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


			//ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(ImVec4(150 / 255.0, 188 / 255.0, 250 / 255.0, 98 / 255.0)));
			//ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.ChildMenuColor));

			ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::ColorConvertFloat4ToU32(current_color_sheme.MidMenuColor));
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

