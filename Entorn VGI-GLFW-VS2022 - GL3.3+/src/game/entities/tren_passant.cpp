#include "tren_passant.h"

Tren_passant::Tren_passant(Transform transform, Model* model_rail, GLuint shader_id, float speed) : speed(speed), GameEntity(transform, nullptr, shader_id)
{
	n_trens = 7;
	longitud_tren = 45;

	float offset_exterior_passant = 0 - n_trens / 2 * longitud_tren;

	for (int i = 0; i < n_trens; i++)
	{
		Transform trExterior_passant;
		trExterior_passant.translate({ offset_exterior_passant, 0, 0 });
		//tr.rotate(glm::pi<float>() / 2, vec3(1.0f, 0.0f, 0.0f));
		trExterior_passant.scale() = vec3(0.022f);
		trExterior_passant.rotate(glm::pi<float>() / 2, vec3(1.0f, 0.0f, 0.0f));
		GameEntity* exterior_passant = new GameEntity(trExterior_passant, model_rail, shader_id);
		addChild(exterior_passant);

		offset_exterior_passant += longitud_tren;
	}
}

void Tren_passant::update(float delta_time)
{
	for (auto exterior : my_children)
	{
		exterior->my_transform.position().x -= delta_time * speed;

		if (exterior->my_transform.position().x < -(n_trens / 2 * longitud_tren)*7)
			exterior->my_transform.position().x = 500;
	}
}
