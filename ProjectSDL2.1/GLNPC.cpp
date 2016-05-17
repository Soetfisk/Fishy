#include "GLNPC.h"

void GLNPC::RespawnCountdown(float deltaTime)
{
	timeUntilRespawn -= deltaTime;
	if (timeUntilRespawn < 0)
	{
		timeUntilRespawn = 10.0f;
		fishSize += 1.0f;
		this->ResetFish(fishSize);
	}
}

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
	this->timeUntilRespawn = 10.0f;
}

void GLNPC::UpdateParticles(float &deltaTime) {
	this->timeSinceUpdate++;
	if(this->isBleeding)
		this->bloodTimeCurrent += deltaTime;

	if (this->timeSinceUpdate >= this->updateFrames) {

		if (this->npc_emitter != nullptr) {
			this->npc_emitter->updateEmitterData(glm::vec4(this->transform->GetPos(), 1),
				glm::vec4(this->forward, 0), glm::vec4(this->GetRight(), 0), glm::vec4(this->GetUp(), 0), this->transform->GetScale().z);

			
		}

		if (this->npc_blood_emitter != nullptr) {
			if (this->isBleeding) {
				this->npc_blood_emitter->updatePosition(glm::vec4(this->transform->GetPos(), 1));
				this->npc_blood_emitter->UpdateEmitter(deltaTime);

				if (this->bloodTimeCurrent >= this->bloodTime) {
					this->isBleeding = false;
					this->bloodTimeCurrent = 0;
				}
			}
		}
	}
	
}

void GLNPC::DrawParticles(GLShader* shader) {
	if (this->npc_emitter != nullptr) {
		this->npc_emitter->Draw(shader);
	}

	if (this->npc_blood_emitter != nullptr) {
		this->npc_blood_emitter->Draw(shader);
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

bool GLNPC::hasEmitter() {
	return this->npc_emitter != nullptr;
}

void GLNPC::enableBlood() {
	this->isBleeding = true;
	this->bloodTimeCurrent = 0.f;

}