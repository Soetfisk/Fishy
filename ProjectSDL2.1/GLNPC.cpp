#include "GLNPC.h"

int GLNPC::GetCurrentState()
{
	return currentState;
}

void GLNPC::SetCurrentState()
{
	this->currentState = NPC_STANDSTILL;
}

void GLNPC::makePowerUp()
{
	/*this->meshes.at(0)->GetMaterial()->diffuse[0] = 1.0f;
	this->meshes.at(0)->GetMaterial()->diffuse[1] = 0.0f;
	this->meshes.at(0)->GetMaterial()->diffuse[2] = 0.0f;
	
	this->meshes.at(0)->GetMaterial()->spec[0] = 1.0f;
	this->meshes.at(0)->GetMaterial()->spec[1] = 1.0f;
	this->meshes.at(0)->GetMaterial()->spec[2] = 1.0f;*/
	
	

	//this->powerUpMaterial = this->meshes.at(0)->GetMaterial();

	this->meshes.at(0)->SetMaterial(this->powerUpMaterial);
	//printf("%d\n", this->meshes.at(0)->GetMaterial().spec[0]);
	isPowerUp = true;
	
}

GLNPC::GLNPC(FishBox * FSH_Loader, unsigned int modelID) : GLModel(FSH_Loader,modelID)
{
	this->blendWeights = new float[NUM_ANIMATION];
	for (int i = 0; i < NUM_ANIMATION; i++)
	{
		blendWeights[i] = 0.0f;
		animationFactors[i] = 0.0f;
	}
	this->npc_emitter = nullptr;
	this->timeSinceUpdate = 0;
	
	
	
	
	this->powerUpMaterial = new FSHData::material;

	this->powerUpMaterial->diffuse[0] = 1;
	this->powerUpMaterial->diffuse[1] = 1;
	this->powerUpMaterial->diffuse[2] = 0.4;

	this->powerUpMaterial->ambient[0] = 0.7f;
	this->powerUpMaterial->ambient[1] = 0.3f;
	this->powerUpMaterial->ambient[2] = 0;

	this->powerUpMaterial->shinyness = 100;
	this->powerUpMaterial->spec[0] = 1;
	this->powerUpMaterial->spec[1] = 0.2f;
	this->powerUpMaterial->spec[2] = 0.2f;

	

	//this->powerUpMaterial->materialName = "Power";
}

void GLNPC::UpdateParticles(float &deltaTime) {
	if (this->npc_emitter != nullptr) {
		this->timeSinceUpdate++;
		if (this->timeSinceUpdate >= this->updateFrames) {
		
			this->npc_emitter->updateEmitterData(glm::vec4(this->transform->GetPos(), 1),
				glm::vec4(this->forward, 0), glm::vec4(this->GetRight(), 0), glm::vec4(this->GetUp(), 0), this->transform->GetScale().z);
			//this->player_PartcileEmitter->updateDirection(glm::vec4(this->forward, 0));
			//this->player_PartcileEmitter->updatePosition(glm::vec4(this->transform->GetPos(), 1));
			//this->player_PartcileEmitter->updateSpawnRate(2/speed);
			this->npc_emitter->UpdateEmitter(deltaTime);
		}
	}
}

void GLNPC::DrawParticles(GLShader* shader) {
	if (this->npc_emitter != nullptr) {
		this->npc_emitter->Draw(shader);
	}
}

void GLNPC::moveAnimation(float deltaTime, float speedFactor)
{
	float speed = abs(deltaTime * speedFactor), y;

	animationFactors[AONE] += speed;

	y = sin(animationFactors[AONE]);

	if (y > 0.0)
		this->blendWeights[AONE] = y;
	if (y < 0.0)
		this->blendWeights[ATWO] = abs(y);

}
void GLNPC::AddEmitter(ParticleEmitter* emitter) {
	this->npc_emitter = emitter;

	this->npc_emitter->updateEmitterData(glm::vec4(this->transform->GetPos(), 1),
		glm::vec4(this->forward, 0), glm::vec4(this->GetRight(), 0), glm::vec4(this->GetUp(), 0), this->transform->GetScale().z);
}

GLNPC::~GLNPC() {
	delete blendWeights;
	delete powerUpMaterial;
	if (this->npc_emitter != nullptr)
		delete npc_emitter;
}