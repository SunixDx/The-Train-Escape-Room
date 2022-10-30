#include "Crosshair.h"

void Crosshair::mostrar(glm::mat4 MatriuVista, glm::mat4 MatriuTG)
{
	Transform tr = Transform::blank();

	tr.scale = vec3(0.1, 0.1, 0.1);

	MatriuVista = mat4(1.0f);
	MatriuTG = mat4(1.0f);

	MatriuTG = tr.apply(MatriuTG);

	my_mesh->Draw(MatriuVista, MatriuTG, tr, my_shader_id);
}
