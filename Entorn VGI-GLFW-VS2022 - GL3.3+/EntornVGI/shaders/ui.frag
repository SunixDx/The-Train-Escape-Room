//******** PRACTICA VISUALITZACI� GR�FICA INTERACTIVA (EE-UAB)
//******** Entorn basic amb interf�cie MFC/GLFW i Status Bar
//******** Enric Marti (Maig 2022)
// flat_shdrML.frag: Fragment Program en GLSL per en versi� OpenGL 3.3 o 4.00 per a implementar:
//     a) Iluminaci� plana
//     b) Fonts de llum puntuals o direccionals
//     c) Fonts de llum restringides
//     d) Atenuaci� de fonts de llum
//     e) Modus d'assignaci� de textura MODULATE o DECAL

#version 330 core
//#version 400 core

// ---- L14- in Variables
flat in vec4 VertexColor;     // Color del v�rtex
in vec2 VertexTexCoord;	 // Coordenades textura del v�rtex

// ---- L18- uniform Variables
uniform sampler2D texture0;	// Imatge textura
uniform bool textur;		// Booleana d�activaci� (TRUE) de textures o no (FALSE).
uniform bool modulate;		// Booleana d'activaci� de barreja color textura- color intensitat llum (TRUE) o nom�s color textura (FALSE)

// ---- L23- out Variables
out vec4 FragColor;		// Color fragment (r,g,b,a)

void main ()
{
	vec4 colorT = texture(texture0,VertexTexCoord);
	FragColor = colorT * VertexColor;

	//if (textur) {	// Intensitat amb textura
	//	
	//	// Textura modulada amb intensitat llum
	//	if (modulate) {
	//		
	//	} else {
	//		FragColor = colorT; // textura sense modular intensitat llum
	//	}
    //} else { // Intensitat sense textura
    //    FragColor = VertexColor;   
	//}
}