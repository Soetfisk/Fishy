#include "Scene.h"


void Scene::Init()
{
	//DEBUG MODE?
	debug = false;

	// set player position and rotation to the correct startpositions
	this->players.at(1)->GetTransform().SetPos(glm::vec3(100, 0, 0));
	this->players.at(1)->GetTransform().SetRot(glm::vec3(0, -1.58, 0));
	this->players.at(0)->GetTransform().SetPos(glm::vec3(-100, 0, 0));
	this->players.at(0)->GetTransform().SetRot(glm::vec3(0, 1.58, 0));
	this->staticMeshes.at(0)->GetTransform().SetPos(glm::vec3(0, 0, 0));

	// load the shaders
	shaders[MODELS] = new GLShader("test", true);
	shaders[PASS] = new GLShader("pass");
	shaders[TEXT] = new GLShader("text");
	shaders[WAVY] = new GLShader("wavy");
	shaders[BORDER] = new GLShader("post");
	shaders[LIGHTING] = new GLShader("lighting");
	shaders[BLEND_SHAPE] = new GLShader("blend_shape", true);
	shaders[PARTICLE] = new GLShader("Particle", true);

	// init all the framebuffers
	this->frameBuffer = new FrameBuffer();
	this->frameBuffer->CreateFrameBuffer(6, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA16F);
	this->frameBuffer->UnbindFrameBuffer();

	this->frameBuffer2 = new FrameBuffer();
	this->frameBuffer2->CreateFrameBuffer(1, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB);
	this->frameBuffer2->UnbindFrameBuffer();

	this->frameBuffer3 = new FrameBuffer();
	this->frameBuffer3->CreateFrameBuffer(1, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB);
	this->frameBuffer3->UnbindFrameBuffer();

	this->frameBuffer4 = new FrameBuffer();
	this->frameBuffer4->CreateFrameBuffer(1, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB);
	this->frameBuffer4->UnbindFrameBuffer();

	this->frameBuffer5 = new FrameBuffer();
	this->frameBuffer5->CreateFrameBuffer(1, SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGB);
	this->frameBuffer5->UnbindFrameBuffer();

	// computeshader off cus crash
	/*filterComputeShader = new FilterComputeShader("derp");
	filterComputeShader->LoadShader("blueFilter.glsl");
	filterComputeShader->CreateShader(filterComputeShader->LoadShader("blueFilter.glsl"));*/

	// lights
	PointLight light1;
	light1.ambient = glm::vec3(0.0f, 0.1f, 0.0f);
	light1.diffuse = glm::vec3(0.65f, 0.0f, 1.0f);
	light1.position = glm::vec3(-3, 0, -3);
	light1.specular = glm::vec3(0.5f, 0.0f, 0.0f);
	light1.constant = 1.0f;
	light1.linear = 0.045f;
	light1.quadratic = 0.0075f;

	

	PointLight light2;
	light2.ambient = glm::vec3(0.0f, 0.1f, 0.0f);
	light2.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	light2.position = glm::vec3(0, 0, 0);
	light2.specular = glm::vec3(0.5f, 0.0f, 0.0f);
	light2.constant = 1.0f;
	light2.linear = 0.045f;
	light2.quadratic = 0.0075f;

	this->pointLights.push_back(light1);
	this->pointLights.push_back(light2);

	dirLight.ambient = glm::vec3(0.25, 0.61, 1);
	dirLight.diffuse = glm::vec3(0.25, 0.61, 1);
	dirLight.specular = glm::vec3(0.25, 0.61, 1);
	dirLight.dir = glm::vec3(0.01, 1, 0.01);

	this->deltaTime = 0;
	// border shader variables
	this->borderThreshold1 = 0.9f; // variable one must be the bigger otherwise the second will just overwrite it
	this->borderThreshold2 = 0.9f; // values should be between 0-1
	this->borderColor1 = glm::vec3(0, 0, 0);
	// wavy variables
	this->wavyAmount = 0.3f; // how fast the waves will go, higher = faster. Standard = 1
	this->wavyLength = 1.0f; // how long the waves are. Lower = longer waves. standard = 1
							 //fog variables
	this->fogStart = 50.f;
	this->fogEnd = 210.f;
	this->fogColor = glm::vec3(0.1, 0.1, 0.8);
	//player
	this->currentPowerUp = GLPlayer::POWER_NEUTRAL;
	// Ending game options
	this->endTimer = 300;
	this->endScore = 1000;

	this->seaWeedHandler = new SeaWeedHandler(&FSH_Loader, SeaWeedLeaf);
	this->seaWeedHandler->SetXLimit(-110, 110);
	this->seaWeedHandler->SetZLimit(-70, 70);
	this->seaWeedHandler->SetLeafAmount(2, 5);
	this->seaWeedHandler->SetAmountOfPlants(9);
	this->seaWeedHandler->SetScale(3, 6);
	this->seaWeedHandler->SetOffset(0, 0);
	this->seaWeedHandler->LoadSeaWeed();

	this->TallSeaWeedHandler = new SeaWeedHandler(&FSH_Loader, SeaWeedTall);
	this->TallSeaWeedHandler->SetIsBlendShape(true);
	this->TallSeaWeedHandler->SetXLimit(-110, 110);
	this->TallSeaWeedHandler->SetZLimit(-70, 70);
	this->TallSeaWeedHandler->SetLeafAmount(1, 4);
	this->TallSeaWeedHandler->SetAmountOfPlants(9);
	this->TallSeaWeedHandler->SetScale(2.0f, 5.0f);
	this->TallSeaWeedHandler->SetOffset(4,10 );
	this->TallSeaWeedHandler->SetRandomRotation(0);
	this->TallSeaWeedHandler->LoadSeaWeed();

	this->stoneHandler = new SeaWeedHandler(&FSH_Loader, roughRock);
	this->stoneHandler->SetXLimit(-90, 90);
	this->stoneHandler->SetZLimit(-50, 50);
	this->stoneHandler->SetLeafAmount(1, 4);
	this->stoneHandler->SetAmountOfPlants(10);
	this->stoneHandler->SetScale(2, 6);
	this->stoneHandler->SetOffset(40, 40);
	this->stoneHandler->LoadSeaWeed();

	this->stoneHandler2 = new SeaWeedHandler(&FSH_Loader, smoothRock);
	this->stoneHandler2->SetXLimit(-90, 90);
	this->stoneHandler2->SetZLimit(-50, 50);
	this->stoneHandler2->SetLeafAmount(1, 3);
	this->stoneHandler2->SetAmountOfPlants(15);
	this->stoneHandler2->SetScale(1, 5);
	this->stoneHandler2->SetOffset(30, 30);
	this->stoneHandler2->SetRandomRotation(0.3f);
	this->stoneHandler2->LoadSeaWeed();


	particleHandler = new ParticleHandler(shaders[PARTICLE], &this->FSH_Loader);
	

	for (int i = 0; i < players.size(); i++)
	{
		players.at(i)->addParticleHandleRefernce(particleHandler);
	}

	//for (int z = 0; z < 5; z++) {
	//	for (int x = 0; x < 5; x++) {
	//		particleHandler->AddEmiter(EmitterType::STATICSTREAM, glm::vec4((float)x* RNG::range(-4.f, 4.f), -50.f, (float)z* RNG::range(-6.f, 6.f), 1));
	//	}
	//}
	for (int z = -85; z < 85; z+=40) {
		for (int x = -125; x < 125; x+= 40) {
			float xe = x + RNG::range(-20, 20);
			float ze = z + RNG::range(-20, 20);
			particleHandler->AddEmiter(EmitterType::STATICSTREAM, glm::vec4((xe>-125 && xe<125) ? xe : x, -50.f, (ze>-85 && ze<85) ? ze : z, 1));
		}
	}

	this->collisionHandler.AddParticleHandlerReference(this->particleHandler);

	//for (int i = 0; i <  players.size(); i++) {
	//	particleHandler->AddEmiter(EmitterType::PLAYERFOLLOW, players.at(i)->getParticleFollowPlayer());
	//}
	//for (int z = 0; z < 3; z++) {
	//	particleHandler->AddEmiter(EmitterType::GOLDSTREAM, glm::vec4(2, 1, 3 + (z % 2 == 0) ? z * 2 : -z * 2, 1));
	//}
	
	//this->FSH_Loader.freeTextures();
}


void Scene::LoadModels()
{

	FSH_Loader.LoadScene("Models/fishy.FSH"); //PlayerFish
	FSH_Loader.LoadScene("Models/GoldFishBlend.FSH"); //GoldFish
	FSH_Loader.LoadScene("Models/bluetangblend.FSH"); //BlueTang
	FSH_Loader.LoadScene("Models/Bubble2.FSH"); //Bubble
	FSH_Loader.LoadScene("Models/AquariumRedux.FSH"); //Aquarium
	FSH_Loader.LoadScene("Models/weed2.FSH"); //SeaWeedLeaf
	FSH_Loader.LoadScene("Models/seaweed1Blend.FSH");//SeaWeedTall
	FSH_Loader.LoadScene("Models/roughRock.FSH"); //roughRock
	FSH_Loader.LoadScene("Models/smoothRock.FSH"); //smoothRock

	for (int i = 0; i < 2; i++) {
		this->players.push_back(new GLPlayer(&FSH_Loader, PlayerFish, Bubble));
		this->players.at(i)->SetBoundingBox(glm::vec3(0), glm::vec3(1));
	}
	for (int i = 0; i < 10; i++) {
		this->NPCs.push_back(new GLNPC_GoldFish(&FSH_Loader, GoldFish));
		this->NPCs.at(i)->SetBoundingBox(glm::vec3(0), glm::vec3(1));
	}
	for (int i = 0; i < 10; i++) {
		this->NPCs.push_back(new GLNPC_BlueTang(&FSH_Loader, BlueTang));
		this->NPCs.at(NPCs.size()-1)->SetBoundingBox(glm::vec3(0), glm::vec3(1.25));
	}

	this->staticMeshes.push_back(new GLModel(&FSH_Loader, Aquarium));
	//this->staticMeshes.push_back(new GLModel(&FSH_Loader, SeaWeedTall));
	//staticMeshes.at(0)->GetTransform().SetPos(glm::vec3(3, 3, 3));
	//staticMeshes.at(0)->GetTransform().SetScale(glm::vec3(1, -1, 1));
	
	this->staticMeshes.push_back(new GLModel(&FSH_Loader, BlueTang));
	//this->staticMeshes.at(1)->GetTransform().SetScale(glm::vec3(2));
	//this->staticMeshes.at(1)->SetBoundingBox(glm::vec3(0), glm::vec3(1.25));
	this->staticMeshes.push_back(new GLModel(&FSH_Loader, Bubble));

	this->collisionHandler.AddNPC(NPCs);
	this->collisionHandler.AddPlayer(players);
	this->collisionHandler.AddModel(models);
	this->collisionHandler.InitiatePowerUpHandler();
}

void Scene::LoadModels(char * folder)
{
}

// update currentPowerup variable with value from player i
void Scene::UpdatePlayerPowerUp(int player)
{
	this->currentPowerUp = this->players.at(player)->GetPowerUp();
	// fix gui powerup text
	if (player == 0)
	{
		switch (this->currentPowerUp)
		{
		case GLPlayer::POWER_NEUTRAL:
			guih->Player1SetPowerUp(GLGUIHandler::PlayerPowerUpText::NOTHING);
			break;
		case GLPlayer::POWER_BUBBLEBIG:
			guih->Player1SetPowerUp(GLGUIHandler::PlayerPowerUpText::BIG);
			break;
		case GLPlayer::POWER_BUBBLESHOTGUN:
			guih->Player1SetPowerUp(GLGUIHandler::PlayerPowerUpText::SHOTGUN);
			break;
		case GLPlayer::POWER_HIGH:
			guih->Player1SetPowerUp(GLGUIHandler::PlayerPowerUpText::HIGH);
			break;
		default:
			guih->Player1SetPowerUp(GLGUIHandler::PlayerPowerUpText::NOTHING);
			break;
		}
	}
	else
	{
		switch (this->currentPowerUp)
		{
		case GLPlayer::POWER_NEUTRAL:
			guih->Player2SetPowerUp(GLGUIHandler::PlayerPowerUpText::NOTHING);
			break;
		case GLPlayer::POWER_BUBBLEBIG:
			guih->Player2SetPowerUp(GLGUIHandler::PlayerPowerUpText::BIG);
			break;
		case GLPlayer::POWER_BUBBLESHOTGUN:
			guih->Player2SetPowerUp(GLGUIHandler::PlayerPowerUpText::SHOTGUN);
			break;
		case GLPlayer::POWER_HIGH:
			guih->Player2SetPowerUp(GLGUIHandler::PlayerPowerUpText::HIGH);
			break;
		default:
			guih->Player2SetPowerUp(GLGUIHandler::PlayerPowerUpText::NOTHING);
			break;
		}

	}
}

// do stuff with curentPowerup variable
void Scene::HandlePlayerPowerUp()
{
	if (this->currentPowerUp == GLPlayer::POWER_HIGH)
	{
		this->wavyAmount = 10;
		this->wavyLength = 0.5f; // how long the waves are. Lower = longer waves. standard = 1
		this->fogColor = glm::vec3(0.3, 0.7, 0.3);
		this->fogStart = 1.0f;
		this->fogEnd = 35.0f;
	}
	else
	{
		this->wavyAmount = 0.3f; // how fast the waves will go, higher = faster. Standard = 1
		this->wavyLength = 1.0f; // how long the waves are. Lower = longer waves. standard = 1
		this->fogColor = glm::vec3(0.1, 0.1, 0.8);
		this->fogStart = 50.f;
		this->fogEnd = 210.f;
	}
}

void Scene::CheckWinner()
{
	// if the timer is out or either player has winning amount of points and no one has won yet
	if (!this->winner && (this->guih->GetTime() >= this->endTimer || this->players.at(0)->GetTotalPoints() >= this->endScore || this->players.at(1)->GetTotalPoints() >= this->endScore))
	{
		this->winner = true;

		if (this->players.at(0)->GetTotalPoints() == this->players.at(1)->GetTotalPoints())
			this->guih->Tie();
		else if (this->players.at(0)->GetTotalPoints() > this->players.at(1)->GetTotalPoints())
			this->guih->Player1Won();
		else
			this->guih->Player2Won();
	}

	// if we have a winner
	if (this->winner)
	{
		// add to endSceneTimer which will end the scene in a certain amount of time
		this->endSceneTimer += this->deltaTime;
		if (this->endSceneTimer > 3)
		{
			*this->gameState = GLOBAL_GameState::MENU;
			this->ResetScene();
		}
	}
}

void Scene::AddScore()
{
	this->CheckWinner();
	for (unsigned int i = 0; i < this->players.size(); i++) {
		this->players.at(i)->Update(GLPlayer::NOTHING, glm::vec3(deltaTime));
		if (i == 0)
		{
			guih->AddScorePlayer1(this->players.at(i)->GetPoints());
		}
		else
		{
			guih->AddScorePlayer2(this->players.at(i)->GetPoints());
		}
	}
}

void Scene::setDebugTimer(bool debug)
{
	if (debug)
	{
		this->currentDTime = SDL_GetTicks();
		this->dTime = (currentDTime - prevDTime) / 1000.0f;
		this->prevDTime = currentDTime;
		this->combinedDtime += dTime;
	}
}



void Scene::printDebugTimer(bool debug, std::string name)
{
	if (debug)
		printf("\nTime: %f, %s", dTime, name.c_str());
}

void Scene::PrintAndResetCombinedDTimer(bool debug)
{
	if (debug)
	{
		printf("\nCombinded frame time: %f\n", combinedDtime);
		combinedDtime = 0.0f;
	}
}

Scene::Scene(GLOBAL_GameState* gameState) {
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_VolumeMusic(20);
	music[COMBAT_BACKGROUND_MUSIC] = Mix_LoadMUS("./res/Sounds/background.wav");
	music[ATTACK_BACKGROUND_MUSIC] = Mix_LoadMUS("./res/Sounds/attack.wav");
	music[ARCADE_BACKGROUND_MUSIC] = Mix_LoadMUS("./res/Sounds/arcade.wav");
	LoadModels();
	Init();

	guih = new GLGUIHandler();
	this->gameState = gameState;
}

Scene::Scene(GUI* textToScreen, GLOBAL_GameState* gameState)
{
	LoadModels();
	Init();

	guih = new GLGUIHandler(shaders[TEXT], textToScreen);
	this->gameState = gameState;
}


Scene::~Scene() {
	for (int i = 0; i < NUM_SHADERS; i++) {
		delete shaders[i];
	}

	delete this->frameBuffer;
	delete this->frameBuffer2;
	delete this->frameBuffer3;
	delete this->frameBuffer4;
	delete this->frameBuffer5;
	//delete this->filterComputeShader;
	for (size_t i = 0; i < models.size(); i++)
	{
		delete models.at(i);
	}

	for (size_t i = 0; i < players.size(); i++)
	{
		delete players.at(i);
	}

	for (size_t i = 0; i < NPCs.size(); i++)
	{
		delete NPCs.at(i);
	}
	for (size_t i = 0; i < staticMeshes.size(); i++)
	{
		delete staticMeshes.at(i);
	}
	delete guih;
	delete particleHandler;
	delete seaWeedHandler;
	delete TallSeaWeedHandler;
	delete stoneHandler;
	delete stoneHandler2;
	for (int i = 0; i < NUM_MUSIC; i++)
	{
		Mix_FreeMusic(music[i]);
	}
	Mix_CloseAudio();
}

void Scene::Update(float& deltaTime) {

	if (debug)
		printf("\n\n##UPDATE DEBUG##");

	setDebugTimer(debug);
	if (Mix_PlayingMusic() == 0)
	{
		srand(time(0));
		int num = rand() % NUM_MUSIC;
		//Play the music
		currentSong = num;
		Mix_PlayMusic(music[num], -1);
	}
	setDebugTimer(debug);
	printDebugTimer(debug, "music");
	
	this->deltaTime = deltaTime;

	guih->Update(deltaTime);
	setDebugTimer(debug);
	printDebugTimer(debug, "gui");

	this->collisionHandler.CheckCollisions(deltaTime);
	setDebugTimer(debug);
	printDebugTimer(debug, "collision");

	this->AddScore();
	setDebugTimer(debug);
	printDebugTimer(debug, "score");

	this->particleHandler->UpdateParticles(deltaTime);
	for (size_t i = 0; i < this->NPCs.size(); i++) {
		this->NPCs.at(i)->NPCUpdate(deltaTime);
		this->NPCs.at(i)->UpdateModel();
		if (this->NPCs.at(i)->GetIsPowerUp()) {
			this->NPCs.at(i)->UpdateParticles(this->deltaTime);
		}	
	}
	TallSeaWeedHandler->Update(deltaTime);//OskarAddsSeaWeedUpdate
	setDebugTimer(debug);
	printDebugTimer(debug, "Npc");
		

	for (size_t i = 0; i < this->players.size(); i++) {
		this->players.at(i)->Update(this->deltaTime);
		this->players.at(i)->UpdateParticles(this->deltaTime);
		if (this->players.at(i)->GetBoundingBox().containsAABB(staticMeshes.at(1)->GetBoundingBox()))
		{
			std::cout << "HIT" << std::endl;
		}
	}
	setDebugTimer(debug);
	printDebugTimer(debug, "players");

}

//Loads the scene, models, matrices
void Scene::LoadScene() {

}

//Calls the models.draw
void Scene::DrawScene() {

	if (debug)
		printf("\n\n### DRAW DEBUG ###");

	setDebugTimer(debug);
	printDebugTimer(debug, "between draw and update");

	guih->Draw();
	setDebugTimer(debug);
	printDebugTimer(debug, "gui");

	for (size_t i = 0; i < this->players.size(); i++) {
		// handle player powerup
		if (debug)
			printf("\n\n#SCREEN: %d:", i);

		this->UpdatePlayerPowerUp(i);
		this->HandlePlayerPowerUp();
		this->players.at(i)->UpdateModel();
		setDebugTimer(debug);
		printDebugTimer(debug, "playerpowerup");
		//Set viewport
		glViewport(0, 0, window::WIDTH, window::HEIGHT / 2);

		shaders[BLEND_SHAPE]->Bind();
		shaders[BLEND_SHAPE]->Update(players.at(i)->GetCamera());
		this->frameBuffer->BindFrameBuffer();
		setDebugTimer(debug);
		printDebugTimer(debug, "bind blendshape, get playercamera, bind framebuffer");

		for (size_t j = 0; j < this->players.size(); j++)
		{
			shaders[BLEND_SHAPE]->Uniform1ui("BlendShapeCount", (GLuint)players.at(j)->GetBlendShapeCount());
			shaders[BLEND_SHAPE]->Uniform1fv("Weights", players.at(j)->GetBlendWeights());
			players.at(j)->TestDraw(*shaders[BLEND_SHAPE]);
		}

		setDebugTimer(debug);
		printDebugTimer(debug, "player");
		
		for (size_t j = 0; j < NPCs.size(); j++)
		{
			shaders[BLEND_SHAPE]->Uniform1ui("BlendShapeCount", (GLuint)NPCs.at(j)->GetBlendShapeCount());
			shaders[BLEND_SHAPE]->Uniform1fv("Weights", NPCs.at(j)->GetBlendWeights());
			NPCs.at(j)->NPCDraw(*shaders[BLEND_SHAPE]);
		}
		setDebugTimer(debug);
		printDebugTimer(debug, "npc's");

		shaders[BLEND_SHAPE]->Uniform1ui("BlendShapeCount", (GLuint)TallSeaWeedHandler->GetBlendShapeCount());
		shaders[BLEND_SHAPE]->Uniform1fv("Weights", TallSeaWeedHandler->GetBlendWeights());
		TallSeaWeedHandler->Draw(shaders[BLEND_SHAPE]);

		shaders[MODELS]->Bind();
		shaders[MODELS]->Update(players.at(i)->GetCamera());
		setDebugTimer(debug);
		printDebugTimer(debug, "bind models, get playercamera");
		this->seaWeedHandler->Draw(shaders[MODELS]);
		this->stoneHandler->Draw(shaders[MODELS]);
		this->stoneHandler2->Draw(shaders[MODELS]);
		
		setDebugTimer(debug);
		printDebugTimer(debug, "seaweed handler");
		for (int j = 0; j < this->players.size(); j++)
		{
			players.at(j)->DrawProjectile(*shaders[MODELS]);
		}
		setDebugTimer(debug);
		printDebugTimer(debug, "projectiles");
		
		for (size_t i = 0; i < staticMeshes.size(); i++)
		{
			staticMeshes.at(i)->Draw(*shaders[MODELS]);
		}
		setDebugTimer(debug);
		printDebugTimer(debug, "static meshes");

		//Drawing All Particles
		this->DrawParticles(players.at(i)->GetCamera());
		setDebugTimer(debug);
		printDebugTimer(debug, "Particles");

		this->frameBuffer->UnbindFrameBuffer();
		this->frameBuffer2->BindFrameBuffer();
		shaders[LIGHTING]->Bind();

		setDebugTimer(debug);
		printDebugTimer(debug, "bind lighting, framebuffer 2");
		for (size_t i = 0; i < pointLights.size(); i++)
		{
			glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(i) + "].ambient"), 1, glm::value_ptr(pointLights.at(i).ambient));
			glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(i) + "].diffuse"), 1, glm::value_ptr(pointLights.at(i).diffuse));
			glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(i) + "].position"), 1, glm::value_ptr(pointLights.at(i).position));
			glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(i) + "].specular"), 1, glm::value_ptr(pointLights.at(i).specular));
			glUniform1f(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(i) + "].constant"), pointLights.at(i).constant);
			glUniform1f(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(i) + "].linear"), pointLights.at(i).linear);
			glUniform1f(shaders[LIGHTING]->GetUnifromLocation("pointLights[" + std::to_string(i) + "].quadratic"), pointLights.at(i).quadratic);
		}

		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("dirLight.dir"), 1, glm::value_ptr(dirLight.dir));
		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("dirLight.ambient"), 1, glm::value_ptr(dirLight.ambient));
		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("dirLight.diffuse"), 1, glm::value_ptr(dirLight.diffuse));
		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("dirLight.specular"), 1, glm::value_ptr(dirLight.specular));

		glUniform3fv(shaders[LIGHTING]->GetUnifromLocation("ViewPos"), 1, glm::value_ptr(players.at(i)->GetCamera().Position()));

		shaders[LIGHTING]->Uniform1f("fogStartFloat", this->fogStart);
		shaders[LIGHTING]->Uniform1f("fogEndFloat", this->fogEnd);
		shaders[LIGHTING]->UniformVec3("fogColorVector", this->fogColor);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("colorTexture"), 0);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("posTexture"), 1);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("normalTexture"), 2);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("distTexture"), 3);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("ambientTexture"), 4);
		this->frameBuffer->BindTexturesToProgram(shaders[LIGHTING]->GetUnifromLocation("specularTexture"), 5);

		setDebugTimer(debug);
		printDebugTimer(debug, "lighting");

		this->RenderQuad();
		setDebugTimer(debug);
		printDebugTimer(debug, "renderQuad");

		this->frameBuffer2->UnbindFrameBuffer();

		this->frameBuffer3->BindFrameBuffer();
		shaders[BORDER]->Bind();
		shaders[BORDER]->Uniform1f("width", (float)window::WIDTH);
		shaders[BORDER]->Uniform1f("height", (float)(window::HEIGHT / 2));
		shaders[BORDER]->Uniform1f("thresholdFloat", this->borderThreshold1);
		shaders[BORDER]->UniformVec3("borderColor", this->borderColor1);
		this->frameBuffer2->BindTexturesToProgram(shaders[BORDER]->GetUnifromLocation("texture"), 0);
		this->RenderQuad();
		this->frameBuffer3->UnbindFrameBuffer();

		this->frameBuffer4->BindFrameBuffer();
		shaders[BORDER]->Bind();
		shaders[BORDER]->Uniform1f("width", (float)window::WIDTH);
		shaders[BORDER]->Uniform1f("height", (float)(window::HEIGHT / 2));
		shaders[BORDER]->Uniform1f("thresholdFloat", this->borderThreshold2);
		shaders[BORDER]->UniformVec3("borderColor", this->borderColor1);
		this->frameBuffer3->BindTexturesToProgram(shaders[BORDER]->GetUnifromLocation("texture"), 0);
		this->RenderQuad();
		this->frameBuffer4->UnbindFrameBuffer();

		this->count[i] += this->wavyAmount * this->deltaTime;
		this->frameBuffer5->BindFrameBuffer();
		shaders[WAVY]->Bind();
		shaders[WAVY]->Uniform1f("offset", count[i]);
		shaders[WAVY]->Uniform1f("waveLength", this->wavyLength);
		this->frameBuffer4->BindTexturesToProgram(shaders[WAVY]->GetUnifromLocation("texture"), 0);
		this->RenderQuad();
		this->frameBuffer5->UnbindFrameBuffer();


		shaders[PASS]->Bind();
		this->frameBuffer5->BindTexturesToProgram(shaders[PASS]->GetUnifromLocation("texture"), 0);
		glViewport(0, (GLint)(window::HEIGHT - (window::HEIGHT *(.5*(i + 1)))), (GLint)window::WIDTH, (GLint)(window::HEIGHT / 2));
		this->RenderQuad();

		setDebugTimer(debug);
		printDebugTimer(debug, "all the way to framebuffer5");
	}

	setDebugTimer(debug);
	printDebugTimer(debug, "end screen loop");

	//PrintAndResetCombinedDTimer(debug);
}

void Scene::DrawParticles(GLCamera& playerCamera) {

	shaders[PARTICLE]->Bind();
	shaders[PARTICLE]->Update(playerCamera);
	for (size_t j = 0; j < this->players.size(); j++)
	{
		players.at(j)->DrawParticles(shaders[PARTICLE]);
	}

	for (size_t i = 0; i < NPCs.size(); i++)
	{
		if (this->NPCs.at(i)->GetIsPowerUp())
			NPCs.at(i)->DrawParticles(shaders[PARTICLE]);
	}

	this->particleHandler->DrawParticles(shaders[PARTICLE]);
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

void Scene::ResetScene()
{
	for (size_t i = 0; i < NPCs.size(); i++)
	{
		NPCs.at(i)->ResetFish();
	}
	guih->Reset();
	for (size_t i = 0; i < players.size(); i++)
	{
		players.at(i)->ResetPlayer();
	}
	this->players.at(1)->GetTransform().SetPos(glm::vec3(100, 0, 0));
	this->players.at(1)->GetTransform().SetRot(glm::vec3(0, -1.58, 0));
	this->players.at(0)->GetTransform().SetPos(glm::vec3(-100, 0, 0));
	this->players.at(0)->GetTransform().SetRot(glm::vec3(0, 1.58, 0));
	this->staticMeshes.at(0)->GetTransform().SetPos(glm::vec3(0, 0, 0));
	this->endSceneTimer = 0;
	this->endGame = false;
	this->winner = false;
	this->seaWeedHandler->Reset();
	this->stoneHandler->Reset();
	this->stoneHandler2->Reset();
	this->TallSeaWeedHandler->Reset();
}

void Scene::HandleEvenet(SDL_Event* e) {

	if (e->type == SDL_CONTROLLERDEVICEADDED)
	{
		players.at(e->cdevice.which)->Update(GLPlayer::JOY_ADDED, glm::vec3((float)e->cdevice.which));
	}
	else if (e->type == SDL_CONTROLLERDEVICEREMOVED)
	{
		players.at(e->cdevice.which)->Update(GLPlayer::JOY_REMOVED, glm::vec3((float)e->cdevice.which));
	}
	else if (e->type == SDL_CONTROLLERAXISMOTION)
	{
		switch (e->caxis.axis)
		{
		case SDL_CONTROLLER_AXIS_RIGHTX:
			players.at(e->caxis.which)->Update(GLPlayer::PLAYER_MOVE_RIGHT, glm::vec3(e->caxis.value, 0, 0));
			break;
		case SDL_CONTROLLER_AXIS_RIGHTY:
			players.at(e->caxis.which)->Update(GLPlayer::PLAYER_MOVE_RIGHT, glm::vec3(0, e->caxis.value, 0));
			break;
		case  SDL_CONTROLLER_AXIS_LEFTX:
			players.at(e->caxis.which)->Update(GLPlayer::PLAYER_MOVE_LEFT, glm::vec3(e->caxis.value, 0, 0));
			break;
		case SDL_CONTROLLER_AXIS_LEFTY:
			players.at(e->caxis.which)->Update(GLPlayer::PLAYER_MOVE_LEFT, glm::vec3(0, e->caxis.value, 0));
			break;
		case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
			players.at(e->caxis.which)->Update(GLPlayer::PLAYER_MOVE_LEFT, glm::vec3(0, 0, e->caxis.value));
			break;
		case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
			players.at(e->caxis.which)->Update(GLPlayer::PLAYER_MOVE_LEFT, glm::vec3(0, 0, -e->caxis.value));
			break;
		default:
			break;
		}
	}
	else if (e->type == SDL_CONTROLLERBUTTONDOWN)
	{
		switch (e->cbutton.button)
		{
		case SDL_CONTROLLER_BUTTON_A:
			players.at(e->cbutton.which)->Update(GLPlayer::PLAYER_SHOOT, glm::vec3(0));
			break;
		case SDL_CONTROLLER_BUTTON_B:
			players.at(e->cbutton.which)->Update(GLPlayer::PLAYER_DASH, glm::vec3(0));
			break;
		default:
			break;
		}
	}
	else if (e->type == SDL_KEYUP)
	{
		switch (e->key.keysym.scancode)
		{
		case SDL_SCANCODE_UP:
			players.at(1)->Update(GLPlayer::PLAYER_MOVE_RIGHT, glm::vec3(0, 1, 0));
			break;
		case SDL_SCANCODE_DOWN:
			players.at(1)->Update(GLPlayer::PLAYER_MOVE_RIGHT, glm::vec3(0, 1, 0));
			break;
		case SDL_SCANCODE_LEFT:
			players.at(1)->Update(GLPlayer::PLAYER_MOVE_RIGHT, glm::vec3(1, 0, 0));
			break;
		case SDL_SCANCODE_RIGHT:
			players.at(1)->Update(GLPlayer::PLAYER_MOVE_RIGHT, glm::vec3(1, 0, 0));
			break;
		case SDL_SCANCODE_W:
			players.at(1)->Update(GLPlayer::PLAYER_MOVE_LEFT, glm::vec3(0, 1, 0));
			break;
		case SDL_SCANCODE_S:
			players.at(1)->Update(GLPlayer::PLAYER_MOVE_LEFT, glm::vec3(0, 1, 0));
			break;
		case SDL_SCANCODE_A:
			players.at(1)->Update(GLPlayer::PLAYER_MOVE_LEFT, glm::vec3(1, 0, 0));
			break;
		case SDL_SCANCODE_D:
			players.at(1)->Update(GLPlayer::PLAYER_MOVE_LEFT, glm::vec3(1, 0, 0));
			break;
		case SDL_SCANCODE_LSHIFT:
			players.at(1)->Update(GLPlayer::PLAYER_MOVE_LEFT, glm::vec3(0, 0, 1));
			break;
		case SDL_SCANCODE_E:
			players.at(1)->Update(GLPlayer::PLAYER_DASH, glm::vec3(0, 0, 1));
			break;
		case SDL_SCANCODE_H:
			players.at(1)->SetPowerUp(GLPlayer::POWER_HIGH);
			guih->Player2SetPowerUp(GLGUIHandler::PlayerPowerUpText::HIGH);
			break;
		case SDL_SCANCODE_Y:
			players.at(1)->SetPowerUp(GLPlayer::POWER_NEUTRAL);
			guih->Player2SetPowerUp(GLGUIHandler::PlayerPowerUpText::NOTHING);
			break;
		case SDL_SCANCODE_J:
			players.at(1)->SetPowerUp(GLPlayer::POWER_BUBBLESHOTGUN);
			guih->Player2SetPowerUp(GLGUIHandler::PlayerPowerUpText::SHOTGUN);
			break;
		case SDL_SCANCODE_K:
			players.at(1)->SetPowerUp(GLPlayer::POWER_BUBBLEBIG);
			guih->Player2SetPowerUp(GLGUIHandler::PlayerPowerUpText::BIG);
			break;
		case SDL_SCANCODE_L:
			ResetScene();
			break;
		default:
			break;
		}
	}
	else if (e->type == SDL_KEYDOWN)
	{
		switch (e->key.keysym.scancode)
		{
		case SDL_SCANCODE_SPACE:
			players.at(1)->Update(GLPlayer::PLAYER_SHOOT, glm::vec3(0));
			break;
		case SDL_SCANCODE_N:
			currentSong = (currentSong + 1) % NUM_MUSIC;
			Mix_PlayMusic(music[currentSong], -1);
			break;
		}

	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_UP])
	{
		players.at(1)->Update(GLPlayer::PLAYER_MOVE_RIGHT, glm::vec3(0, -(glm::pow(2, 15)), 0));
	}
	if (keyState[SDL_SCANCODE_DOWN])
	{
		players.at(1)->Update(GLPlayer::PLAYER_MOVE_RIGHT, glm::vec3(0, (glm::pow(2, 15)), 0));
	}
	if (keyState[SDL_SCANCODE_LEFT])
	{
		players.at(1)->Update(GLPlayer::PLAYER_MOVE_RIGHT, glm::vec3((glm::pow(2, 15)), 0, 0));
	}
	if (keyState[SDL_SCANCODE_RIGHT])
	{
		players.at(1)->Update(GLPlayer::PLAYER_MOVE_RIGHT, glm::vec3(-(glm::pow(2, 15)), 0, 0));
	}
	if (keyState[SDL_SCANCODE_W])
	{
		players.at(1)->Update(GLPlayer::PLAYER_MOVE_LEFT, glm::vec3(0, (glm::pow(2, 15)), 0));
	}
	if (keyState[SDL_SCANCODE_A])
	{
		players.at(1)->Update(GLPlayer::PLAYER_MOVE_LEFT, glm::vec3(-(glm::pow(2, 15)), 0, 0));
	}
	if (keyState[SDL_SCANCODE_S])
	{
		players.at(1)->Update(GLPlayer::PLAYER_MOVE_LEFT, glm::vec3(0, -(glm::pow(2, 15)), 0));
	}
	if (keyState[SDL_SCANCODE_D])
	{
		players.at(1)->Update(GLPlayer::PLAYER_MOVE_LEFT, glm::vec3((glm::pow(2, 15)), 0, 0));
	}
	if (keyState[SDL_SCANCODE_E])
	{
		players.at(1)->Update(GLPlayer::PLAYER_DASH, glm::vec3(0, 0, (glm::pow(2, 15))));
	}
	if (keyState[SDL_SCANCODE_LSHIFT])
	{
		players.at(1)->Update(GLPlayer::PLAYER_MOVE_LEFT, glm::vec3(0, 0, (glm::pow(2, 15))));
	}
}