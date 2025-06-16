//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (EE-UAB)
//******** Entorn basic amb interfície MFC i Status Bar
//******** Enric Marti (Maig 2020)
// phong_shdrML.frag: Vertex Program en GLSL per implementar il.luminacio de Phong


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

// ---- L33 Variables in
in vec3 vertexCM;
in vec4 vertexColor;
in vec2 vertexTexCoord;
in vec3 vertexNormal;

// Variables uniform
uniform mat4 normalMatrix;	// “the transpose of the inverse of the gl_ModelViewMatrix.” 
uniform mat4 projectionMatrix;	// Projection Matrix
uniform mat4 viewMatrix; 	// View Matrix
uniform mat4 modelMatrix;	// Model Matrix

uniform sampler2D texture0;
uniform bool textur;
uniform bool modulate;
uniform bool fixedLight;
uniform bvec4 sw_intensity;
uniform vec4 LightModelAmbient;
uniform Light LightSource[MaxLights];
uniform Material material;

// ---- L54 out Variables
out vec4 FragColor;

void main ()
{

//-L60- Calcul variables previes
    //mat4 NormalMatrix = transpose(inverse(viewMatrix * modelMatrix));
    vec3 N = vec3(normalMatrix * vec4(vertexNormal,1.0));
    N = normalize(N);
    vec3 vertexPV = vec3(viewMatrix * modelMatrix * vec4(vertexCM,1.0));
    vec3 V = normalize(-vertexPV);
  
//-L66- Multiples llums
    float diffuseLight = 0.0;
    vec3 Idiffuse = vec3 (0.0,0.0,0.0);
    vec3 R = vec3 (0.0,0.0,0.0);
    float specularLight = 0.0;
    vec3 Ispecular = vec3 (0.0,0.0,0.0);
    vec3 ILlums = vec3 (0.0,0.0,0.0);
    vec4 lightPosition = vec4(0.0,0.0,0.0,1.0);
    vec3 L = vec3 (0.0,0.0,0.0);

//-L72- Compute emissive term
    vec3 Iemissive = vec3 (0.0,0.0,0.0);
    if (sw_intensity[0])  Iemissive = material.emission.rgb;
    
//-L76- Compute ambient term
    vec3 Iambient = vec3 (0.0,0.0,0.0);
    if (sw_intensity[1]) {  
    	//Iambient = material.ambient.rgb * vertexColor.rgb * LightModelAmbient.rgb;
	Iambient = material.ambient.rgb * LightModelAmbient.rgb;
    	Iambient = clamp(Iambient, 0.0, 1.0);
    }

//-L83- Multiples llums
    for (int i=0;i<MaxLights;i++) {
	if (LightSource[i].sw_light) { 

		//-L88- Compute light position (fixed in WC of attached to camera)
		if (fixedLight) lightPosition = viewMatrix * LightSource[i].position;
			else lightPosition = vec4(-vertexPV,1.0);
		// Compute point light source (w=1) or direccional light (w=0)
		if (LightSource[i].position.w == 1) {	//L = normalize(lightPosition.xyz - vertexPV);
							L = lightPosition.xyz - vertexPV;
							L = normalize(L);
						    }
                     else L = normalize(lightPosition.xyz);
		//vec3 L = normalize(LightSource[i].position.xyz - vertexPV);

		//-L96- Compute the diffuse term
    		Idiffuse = vec3 (0.0,0.0,0.0);
     		if (sw_intensity[2]) {
    			diffuseLight = max(dot(L, N), 0.0);
    			//Idiffuse = material.diffuse.rgb * vertexColor.rgb * LightSource[i].diffuse.rgb * diffuseLight;
			Idiffuse = material.diffuse.rgb * LightSource[i].diffuse.rgb * diffuseLight;
    			Idiffuse = clamp(Idiffuse, 0.0, 1.0);
    			}

		//-104- Compute the specular term
    		Ispecular = vec3 (0.0,0.0,0.0);
    		if (sw_intensity[3]) {
			R = normalize (-reflect(L,N));
    			specularLight = pow(max(dot(R, V), 0.0), material.shininess);
    			//Ispecular = material.specular.rgb * vertexColor.rgb * LightSource[i].specular.rgb * specularLight;
			Ispecular = material.specular.rgb * LightSource[i].specular.rgb * specularLight;
    			Ispecular = clamp(Ispecular, 0.0, 1.0);
			}
		ILlums += Idiffuse + Ispecular;
		}
   }

//-L116- Calcul intensitat final del pixel
   vec3 IColor = Iemissive + Iambient + ILlums;

if (textur) {	// Intensitat amb textura
		vec4 colorT = texture(texture0,vertexTexCoord);
		// Textura modulada amb intensitat llum
	    	if (modulate) FragColor = colorT * vertexColor;
       			else FragColor=colorT; // textura sense modular intensitat llum
    	    }
    else { // Intensitat sense textura
           FragColor = vertexColor;   
         }
}
