//******** PRACTICA VISUALITZACI� GR�FICA INTERACTIVA (EE-UAB)
//******** Entorn basic VS2019 amb interf�cie MFC i Status Bar
//******** Enric Marti (Maig 2022)
// phong_shdrML.vert: Vertex Program en GLSL en versi� OpenGL 3.3 o 4.00 per a implementar:
//     a) Iluminaci� de Gouraud
//     b) Fonts de llum puntuals o direccionals
//     c) Fonts de llum restringides
//     d) Atenuaci� de fonts de llum
//     e) Modus d'assignaci� de textura MODULATE o DECAL

#version 330 core
//#version 400 core

// --- L38- Variables in
layout (location = 0) in vec2 in_Vertex; 	// Coordenades (x,y,z) posicio Vertex
layout (location = 1) in vec2 in_TexCoord; 	// Coordenades (s,t) Coordenada textura
layout (location = 2) in vec4 in_Color; 	// Coordenades (r,g,b,a) Color

// --- L44- Variables uniform
uniform mat4 normalMatrix;	// �the transpose of the inverse of the gl_ModelViewMatrix.� 
uniform mat4 projectionMatrix;	// Projection Matrix
uniform mat4 viewMatrix; 	// View Matrix
uniform mat4 modelMatrix;	// Model Matrix

uniform sampler2D texture0;	// Imatge textura

// --- L60- Variables out
out vec3 vertexPV;
out vec2 vertexTexCoord;
out vec4 vertexColor;

void main()	// --- L66-
{
// --- L68- Calcul variables out.
    vertexPV = vec3(viewMatrix * modelMatrix * vec4(in_Vertex.x, in_Vertex.y, 0.0,1.0));

// --- L75- Textura
    vertexTexCoord = vec2(in_TexCoord.x,in_TexCoord.y);
    
// --- L79- Pas color del vertex al Fragent Shader
    vertexColor = in_Color;

// --- L82- Transformacio de Visualitzacio amb Matriu Projeccio (PMatrix), Matriu C�mera (VMatrix) i Matriu TG (MMatrix)
    gl_Position = vec4(projectionMatrix * viewMatrix * modelMatrix * vec4(in_Vertex, 0.0 ,1.0));
}