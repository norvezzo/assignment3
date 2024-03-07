#pragma once
#include "display.h"
#include "game.h"


	void mouse_callback(GLFWwindow* window,int button, int action, int mods)
	{	
		if(action == GLFW_PRESS )
		{
			Game *scn = (Game*)glfwGetWindowUserPointer(window);
			double x2,y2;
			glfwGetCursorPos(window,&x2,&y2);
			scn->Picking((int)x2,(int)y2);
		}
	}
	
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Game *scn = (Game*)glfwGetWindowUserPointer(window);
		scn->MoveCamera(0, 2, -yoffset);
		
	}
	
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Game *scn = (Game*)glfwGetWindowUserPointer(window);

		if(action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			switch (key)
			{
				case GLFW_KEY_ESCAPE:			
					glfwSetWindowShouldClose(window,GLFW_TRUE);
				break;

				case GLFW_KEY_UP:
					scn->rubi->rotateRubiksCube(glm::vec3(1, 0, 0), -5.0f);
					break;
				case GLFW_KEY_DOWN:
					scn->rubi->rotateRubiksCube(glm::vec3(1, 0, 0), 5.0f);
					break;
				case GLFW_KEY_LEFT:
					scn->rubi->rotateRubiksCube(glm::vec3(0, 1, 0), -5.0f);
					break;
				case GLFW_KEY_RIGHT:
					scn->rubi->rotateRubiksCube(glm::vec3(0, 1, 0), 5.0f);
					break;
				case GLFW_KEY_R:
					scn->rubi->rotateFace(Side::Right);
					break;
				case GLFW_KEY_L:
					scn->rubi->rotateFace(Side::Left);
					break;
				case GLFW_KEY_U:
					scn->rubi->rotateFace(Side::Up);
					break;
				case GLFW_KEY_D:
					scn->rubi->rotateFace(Side::Down);
					break;
				case GLFW_KEY_B:
					scn->rubi->rotateFace(Side::Back);
					break;
				case GLFW_KEY_F:
					scn->rubi->rotateFace(Side::Front);
					break;
				case GLFW_KEY_SPACE:
					scn->rubi->flipRotation();
					break;
				case GLFW_KEY_Z:
					scn->rubi->decreaseAngle();
					break;
				case GLFW_KEY_A:
					scn->rubi->increaseAngle();
					break;
			default:
				break;
			}
		}
	}
	
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Game *scn = (Game*)glfwGetWindowUserPointer(window);

		scn->UpdatePosition((float)xpos,(float)ypos);
		if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			scn->MouseProccessing(GLFW_MOUSE_BUTTON_RIGHT, scn->rubi);
		}
		else if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			scn->MouseProccessing(GLFW_MOUSE_BUTTON_LEFT, scn->rubi);
		}

	}

	void window_size_callback(GLFWwindow* window, int width, int height)
	{
		Game *scn = (Game*)glfwGetWindowUserPointer(window);

		scn->Resize(width,height);
		
	}

	void Init(Display &display)
	{
		display.AddKeyCallBack(key_callback);
		display.AddMouseCallBacks(mouse_callback,scroll_callback,cursor_position_callback);
		display.AddResizeCallBack(window_size_callback);
	}
