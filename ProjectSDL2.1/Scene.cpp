#include "Scene.h"
#include "obj_loader.h"
#include "LoadMesh.h"


Scene::Scene() {
	for (int i = 0; i < 1; i++) {
		this->players.push_back(GLPlayer());
	}
	shaders[MODELS] = new GLShader("test");
	shaders[PASS] = new GLShader("pass");

	//FishBox FishBoxController;
	//std::vector<FSHVertexData> FSHVertexes = FishBoxController.GetModelList()[0].GetMeshList()[0].GetVertices();
	//std::vector<Vertex> Vertices = ModelDataConvert::convertFSHVertex(FSHVertexes);

	//FSHMaterial Material = FishBoxController.GetModelList()[0].GetMaterialList()[0];
	//GL::Mesh GLMaterial = ModelDataConvert::convertFSHMaterial(Material);
	
	//new GLMesh(Vertices, Vertices.size(), /*indices*/, FishBoxController.GetModelList()[0].GetMeshList()[0].getIndexCount(), GLMaterial)

	//float hello = Material.getAmbient()[0];
	//printf("%f", hello);
	//std::vector<Vertex> vertices;

	//vertices.push_back(Vertex(glm::vec3(-.5, .5, 0), glm::vec2(0, 1), glm::vec3(0, 0, 1)));
	//vertices.push_back(Vertex(glm::vec3(-.5, -.5, 0), glm::vec2(0, 0), glm::vec3(0, 0, 1)));
	//vertices.push_back(Vertex(glm::vec3(.5, -.5, 0), glm::vec2(1, 0), glm::vec3(0, 0, 1)));
	//vertices.push_back(Vertex(glm::vec3(.5, .5, 0), glm::vec2(1, 1), glm::vec3(0, 0, 1)));

	//std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0};
	//
	//tempMesh = GLMesh(vertices, vertices.size(), indices, indices.size(), GLMesh::Material());
	tempMesh = objLoadFromFile("./res/OBJ/box2.obj");
	this->frameBuffer = new FrameBuffer();
	this->frameBuffer->CreateFrameBuffer(1);
	this->frameBuffer->UnbindFrameBuffer();
	tempModel = new GLModel();
	testProj = new GLProjectile();
	//first make vertex for all vertexes
	this->cs = this->genComputeProg();
	fcs = new FilterComputeShader("derp");
	fcs->LoadShader("blueFilter.glsl");
}


Scene::~Scene(){
	for (int i = 0; i < NUM_SHADERS; i++) {
		delete shaders[i];
	}
	delete tempMesh;
	delete this->frameBuffer;
	delete tempModel;
	delete testProj;
	delete this->fcs;
}

void Scene::Update(float& deltaTime) {
	//for (int i = 0; i < this->player.count(); i++) {
		//this->player.at(i).update(deltTime);
	//}
	//std::cout << deltaTime << std::endl;
	testProj->TestUpdate(deltaTime);
}

//Loads the scene, models, matrices
void Scene::LoadScene() {

}

//Calls the models.draw
void Scene::DrawScene() {
	for (int i = 0; i < this->players.size(); i++) {
		//Set viewport
		//glViewport(0, window::HEIGHT / (i + 1), window::WIDTH, window::HEIGHT / 2);
		//for(int j = 0; j<this->models.count();j++){
		shaders[MODELS]->Bind();
		shaders[MODELS]->Update(players.at(i).GetCamera());
		this->frameBuffer->BindFrameBuffer();
		//tempModel->Draw(*shaders[MODELS]);
		tempModel->Draw(*shaders[MODELS]);
		testProj->TestDraw(*shaders[MODELS]);
		//tempModel->Draw(*shaders[MODELS]);
		//shaders[PASS]->Bind();
		this->frameBuffer->UnbindFrameBuffer();
		
		
		glUseProgram(this->cs);
		this->count += 0.1f;
		this->frameBuffer->BindImageTexturesToProgram(glGetUniformLocation(this->cs, "destTex"), 0);
		glDispatchCompute(1024 / 16, 768 / 16, 1);
		checkErrors("Dispatch compute shader");
		//this->frameBuffer->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture"), 0);
		//this->frameBuffer->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture2"), 1);
		//this->frameBuffer->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture3"), 2);
		
		shaders[PASS]->Bind();
		this->frameBuffer->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture"), 0);
		this->RenderQuad();
		
		//shaders[MODELS].update(models.at(j), player.at(i).getCamera()); 
		//	models.at(j).draw(player.at(i).getCamera());
		//}
	}
	
}

void Scene::RenderQuad()
{
	if (quadVAO == 0) //init
	{
		GLfloat quadVertices[] = {
			// Positions        // Texture Coords
			-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// Setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void Scene::HandleEvenet(SDL_Event* e) {
	
}

GLuint Scene::genComputeProg() {
	// Creating the compute shader, and the program object containing the shader
	GLuint progHandle = glCreateProgram();
	GLuint cs = glCreateShader(GL_COMPUTE_SHADER);

	// In order to write to a texture, we have to introduce it as image2D.
	// local_size_x/y/z layout variables define the work group size.
	// gl_GlobalInvocationID is a uvec3 variable giving the global ID of the thread,
	// gl_LocalInvocationID is the local index within the work group, and
	// gl_WorkGroupID is the work group's index
	const char *csSrc[] = {
		"#version 430\n",
		"layout(rgba32f) uniform image2D destTex;\
		 layout (local_size_x = 16, local_size_y = 16) in;\
		 void main() {\
			 ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);\
			 imageStore(destTex, storePos, imageLoad(destTex,storePos) + vec4(0.0, 0.0, 0.1, 0.0) );\
			memoryBarrier();\
		 }"
	};

	glShaderSource(cs, 2, csSrc, NULL);
	glCompileShader(cs);
	int rvalue;
	glGetShaderiv(cs, GL_COMPILE_STATUS, &rvalue);
	if (!rvalue) {
		fprintf(stderr, "Error in compiling the compute shader\n");
		GLchar log[10240];
		GLsizei length;
		glGetShaderInfoLog(cs, 10239, &length, log);
		fprintf(stderr, "Compiler log:\n%s\n", log);
		exit(40);
	}
	glAttachShader(progHandle, cs);

	glLinkProgram(progHandle);
	glGetProgramiv(progHandle, GL_LINK_STATUS, &rvalue);
	if (!rvalue) {
		fprintf(stderr, "Error in linking compute shader program\n");
		GLchar log[10240];
		GLsizei length;
		glGetProgramInfoLog(progHandle, 10239, &length, log);
		fprintf(stderr, "Linker log:\n%s\n", log);
		exit(41);
	}
	glUseProgram(progHandle);

	//glUniform1i(glGetUniformLocation(progHandle, "destTex"), 0);
	return progHandle;
}

void Scene::checkErrors(std::string desc) {
	GLenum e = glGetError();
	if (e != GL_NO_ERROR) {
		//fprintf(stderr, "OpenGL error in \"%s\": %s (%d)\n", desc.c_str(), gluErrorString(e), e);
		exit(20);
	}
}