#include "Via.h"

Via::Via(Transform transform, Model* model_rail, GLuint shader_id, float speed): speed(speed), GameEntity(transform, nullptr, shader_id)
{
	n_rails = 80;
	longitud_rail = 8.7;

	float offset_rail = 0 - n_rails / 2 * longitud_rail;

	for (int i = 0; i < n_rails; i++)
	{
		Transform tr;
		tr.translate({offset_rail, 0, 0});
		tr.scale(0.002175f);
		tr.rotate(glm::pi<float>() / 2, vec3(1.0f, 0.0f, 0.0f));

		GameEntity* rail = new GameEntity(tr, model_rail, shader_id);
		addChild(rail);

		offset_rail += longitud_rail;
	}
}

void Via::update(float delta_time)
{
	for (auto rail : my_children)
	{
		rail->my_transform.position().x -= delta_time * speed;

		if (rail->my_transform.position().x < -(n_rails / 2 * longitud_rail))
			rail->my_transform.position().x += n_rails / 2 * longitud_rail * 2;
	}
}
