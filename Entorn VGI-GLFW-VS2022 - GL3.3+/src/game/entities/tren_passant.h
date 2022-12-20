#pragma once
#include "GameEntity.h"
#include "../audio/AudioFunctions.h"

class Tren_passant : public GameEntity
{
public:
	Tren_passant(Transform transform, Model* model_terreny, GLuint shader_id, float speed);
	void update(float delta_time);

	irrklang::ISound* my_snd = Audio::AUDIO_FUNCTIONS.play3D("./media/train_pass.wav", irrklang::vec3df(0,0,0), true, true);

private:
	int n_trens;
	float longitud_tren;
	float speed;
	bool playing_sound = false;
};