#include "Terreny.h"

Terreny::Terreny(Transform transform, Model* model_rail, GLuint shader_id, float speed) : speed(speed), GameEntity(transform, nullptr, shader_id)
{
	n_terrenys = 6;
	longitud_terreny = 500;

	float offset_rail = 0 - n_terrenys / 2 * longitud_terreny;

	for (int i = 0; i < n_terrenys; i++)
	{
		Transform tr;
		tr.translate({ offset_rail, 0, 0 });
		//tr.rotate(glm::pi<float>() / 2, vec3(1.0f, 0.0f, 0.0f));
		tr.rotate(glm::pi<float>() / 2, vec3(0.0f, 0.0f, 1.0f));
		tr.scale(0.025f);

		GameEntity* rail = new GameEntity(tr, model_rail, shader_id);
		addChild(rail);

		offset_rail += longitud_terreny;
	}
}

void Terreny::update(float delta_time)
{
	for (auto terreny : my_children)
	{
		terreny->my_transform.position().x -= delta_time * speed;

		if (terreny->my_transform.position().x < -(n_terrenys / 2 * longitud_terreny))
			terreny->my_transform.position().x += n_terrenys / 2 * longitud_terreny * 2;
	}
}
