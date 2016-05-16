#include "GLNPC.h"

int GLNPC::GetCurrentState()
{
	return currentState;
}

void GLNPC::SetCurrentState()
{
	this->currentState = NPC_STANDSTILL;
}

void GLNPC::makePowerUp(FSHData::material* powerMaterial)
{
	this->meshes.at(0)->SetMaterial(powerMaterial);
	
	isPowerUp = true;
	
}

GLNPC::GLNPC(FishBox * FSH_Loader, unsigned int modelID) : GLModel(FSH_Loader,modelID)
{
	originalMaterial = this->meshes[0]->GetMaterial();
	this->blendWeights = new float[NUM_ANIMATION];
	for (int i = 0; i < NUM_ANIMATION; i++)
	{
		blendWeights[i] = 0.0f;
		animationFactors[i] = 0.0f;
	}
	this->npc_emitter = nullptr;
	this->timeSinceUpdate = 0;
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
	if (this->npc_emitter != nullptr)
		delete npc_emitter;
}
