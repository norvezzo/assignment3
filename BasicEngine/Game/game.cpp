#include "game.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

static void printMat(const glm::mat4 mat)
{
	std::cout<<" matrix:"<<std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout<< mat[j][i]<<" ";
		std::cout<<std::endl;
	}
}

Game::Game() : Scene()
{
	rubi = nullptr;
}

Game::Game(float angle ,float relationWH, float near1, float far1) : Scene(angle,relationWH,near1,far1)
{
	rubi = nullptr;
}

void Game::Init(int size)
{		

	AddShader("../res/shaders/pickingShader");	
	AddShader("../res/shaders/basicShader");
	
	AddTexture("../res/textures/plane.png", false);

	
	float distance = size/2;
	int index = 0;

	if (size % 2 == 0)
	{
		for (float i = -distance; i < distance; i += 1)
		{
			for (float j = -distance; j < distance; j += 1)
			{
				for (float k = -distance; k < distance; k += 1)
				{
					AddShape(Scene::Cube, -1, Scene::TRIANGLES);
					SetShapeTex(index, 0);
					shapes[index]->MyTranslate(glm::vec3(i + 0.5f, j + 0.5f, k + 0.5f), 0);
					shapes[index]->MyScale(glm::vec3(0.5f, 0.5f, 0.5f));
					index++;
				}
			}
		}
	}
	else {
		for (float i = -distance; i <= distance; i += 1)
		{
			for (float j = -distance; j <= distance; j += 1)
			{
				for (float k = -distance; k <= distance; k += 1)
				{
					AddShape(Scene::Cube, -1, Scene::TRIANGLES);
					SetShapeTex(index, 0);
					shapes[index]->MyTranslate(glm::vec3(i, j, k), 0);
					shapes[index]->MyScale(glm::vec3(0.5f, 0.5f, 0.5f));
					index++;
				}
			}
		}
	}

	MoveCamera(0, zTranslate, 10);

	rubi = new RubiksCube(size, shapes);

}

void Game::Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx)
{
	Shader *s = shaders[shaderIndx];
	int r = ((pickedShape+1) & 0x000000FF) >>  0;
	int g = ((pickedShape+1) & 0x0000FF00) >>  8;
	int b = ((pickedShape+1) & 0x00FF0000) >> 16;
	s->Bind();
	s->SetUniformMat4f("MVP", MVP);
	s->SetUniformMat4f("Normal",Model);
	s->SetUniform4f("lightDirection", 0.0f , 0.0f, -1.0f, 0.0f);
	if(shaderIndx == 0)
		s->SetUniform4f("lightColor",r/255.0f, g/255.0f, b/255.0f,1.0f);
	else 
		s->SetUniform4f("lightColor",0.7f,0.8f,0.1f,1.0f);
	s->Unbind();
}

void Game::WhenRotate()
{
}

void Game::WhenTranslate()
{
}

void Game::Motion()
{
	if(isActive)
	{
	}
}

Game::~Game(void)
{
}
