//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (EE-UAB)
//******** Entorn basic amb interfície MFC i Status Bar
//******** Enric Marti (Maig 2020)
// phong_shdrML.vert: Vertex Program en GLSL per implementar il.luminacio de Phong

#version 330 core
//#version 400 core

#define MaxLights 8

struct Light
{	bool sw_light;
	vec4 position;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 attenuation;
	bool restricted;
	vec3 spotdirection;
	float cutoff;
	float exponent;
};

struct Material
{	vec4 emission;
	vec4 ambient;
        vec4 diffuse;
	vec4 specular;
	float shininess;
};

// --- L30
// in Variables
layout (location = 0) in vec3 in_Vertex; 	// Coordenades (x,y,z) posicio Vertex
layout (location = 1) in vec3 in_Normal; 	// Coordenades (x,y,z) Vector Normal
layout (location = 2) in vec2 in_TexCoord; 	// Coordenades (s,t) Coordenada textura
layout (location = 3) in vec4 in_Color; 	// Coordenades (r,g,b,a) Color

// Variables uniform
uniform mat4 normalMatrix;	// “the transpose of the inverse of the gl_ModelViewMatrix.” 
uniform mat4 projectionMatrix;	// Projection Matrix
uniform mat4 viewMatrix; 	// View Matrix
uniform mat4 modelMatrix;	// Model Matrix

uniform sampler2D texture0;
uniform bool textur;
uniform bool fixedLight;
uniform bvec4 sw_intensity;
uniform vec4 LightModelAmbient;
uniform Light LightSource[MaxLights];
uniform Material material;

// ---- L21 Variables out
out vec3 vertexCM;
out vec4 vertexColor;
out vec2 vertexTexCoord;
out vec3 vertexNormal;

void main()
{
// --- L30- Calcul variables previes.
    //mat4 NormalMatrix = transpose(inverse(viewMatrix * modelMatrix));
    //vertexNormal = vec3(normalize(normalMatrix * vec4(in_Normal,1.0)));
    //vec3 N = vec3(normalMatrix * vec4(in_Normal,1.0));
    //vertexNormal = normalize(N);
    vertexNormal = in_Normal;
    //vertexPV = vec3(viewMatrix * modelMatrix * vec4(in_Vertex,1.0));
    vertexCM = in_Vertex;

// ---- L35 Textura
    vertexTexCoord = vec2(in_TexCoord.x,1.0-in_TexCoord.y); // SOIL_FLAG_INVERT_Y
    
// --- L38- Transformacio de Visualitzacio amb Matriu Projeccio (PMatrix), Matriu Càmera (VMatrix) i Matriu TG (MMatrix)
    gl_Position = vec4(projectionMatrix * viewMatrix * modelMatrix * vec4(in_Vertex,1.0));

// ---L41- Pas color del vertex al Fragent Shader
    vertexColor = in_Color;
}

