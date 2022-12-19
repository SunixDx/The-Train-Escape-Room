//******** PRACTICA VISUALITZACIï¿½ GRï¿½FICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn bï¿½sic VS2019 MONOFINESTRA amb OpenGL 3.3+, interfï¿½cie GLFW i imGUI amb llibreries GLM
//******** Ferran Poveda, Marc Vivet, Carme Juliï¿½, Dï¿½bora Gil, Enric Martï¿½ (Setembre 2022)
// main.cpp : Definiciï¿½ de main

//#include <GLFW/glfw3.h>
#include <iostream>
#include "stdafx.h"
#include "shader.h"
#include "visualitzacio.h"
#include "escena.h"
#include "main.h"
#include "game/graphics/Mesh.h"
#include "game/physics/BulletWorld.h"
#include "game/graphics/Model.h"
#include "game/graphics/Camera.h"
#include "game/Level.h"
#include "game/ui/UI.h"
#include "game/ui/InteractionIndicator.h"
#include "game/ui/menu.h"
#include "game/ui/Crosshair.h"

#include <bullet/btBulletDynamicsCommon.h>
#include <irrKlang/irrKlang.h>

glm::vec3 skybox_offset = {0, 0, 0};
glm::vec3 slenderman_offset = vec3(-1.8f, 0.0f, -0.1f);
glm::vec3 slenderman_offset_inicial = vec3(-1.8f, 0.0f, -0.1f);

glm::vec3 exterior_offset = vec3(7.0f, 0.0f, -0.1f);
glm::vec3 exterior_offset_inicial = vec3(0.0f, -15.0f, 0.0f);

void InitGL()
{
// TODO: agregar aquï¿½ el cï¿½digo de construcciï¿½n

//------ Entorn VGI: Inicialitzaciï¿½ de les variables globals de CEntornVGIView
	int i;

// Entorn VGI: Variable de control per a Status Bar (consola) 
	statusB = false;

// Entorn VGI: Variables de control per Menï¿½ Cï¿½mera: Esfï¿½rica, Navega, Mï¿½bil, Zoom, Satelit, Polars... 
	camera = CAM_ESFERICA;
	mobil = true;	zzoom = true;		zzoomO = false;		satelit = false;

// Entorn VGI: Variables de control de l'opciï¿½ Cï¿½mera->Navega?
	n[0] = 0.0;		n[1] = 0.0;		n[2] = 0.0;
	opvN.x = 10.0;	opvN.y = 0.0;		opvN.z = 0.0;
	angleZ = 0.0;
	ViewMatrix = glm::mat4(1.0);		// Inicialitzar a identitat

// Entorn VGI: Variables de control de l'opciï¿½ Cï¿½mera->Geode?
	OPV_G.R = 15.0;		OPV_G.alfa = 0.0;	OPV_G.beta = 0.0;	// Origen PV en esfï¿½riques per a Vista_Geode

// Entorn VGI: Variables de control per Menï¿½ Vista: Pantalla Completa, Pan, dibuixar eixos i grids 
	fullscreen = false;
	pan = false;
	eixos = true;	eixos_programID = 0;  eixos_Id = 0;
	sw_grid = false;
	grid.x = false;	grid.y = false;		grid.z = false;		grid.w = false;
	hgrid.x = 0.0;	hgrid.y = 0.0;		hgrid.z = 0.0;		hgrid.w = 0.0;

// Entorn VGI: Variables opciï¿½ Vista->Pan
	fact_pan = 1;
	tr_cpv.x = 0;	tr_cpv.y = 0;	tr_cpv.z = 0;		tr_cpvF.x = 0;	tr_cpvF.y = 0;	tr_cpvF.z = 0;

// Entorn VGI: Variables de control per les opcions de menï¿½ Projecciï¿½, Objecte
	projeccio = CAP;	// projeccio = PERSPECT;
	ProjectionMatrix = glm::mat4(1.0);	// Inicialitzar a identitat
	objecte = CAP;		// objecte = TETERA;

// Entorn VGI: Variables de control Skybox Cube
	SkyBoxCube = false;		skC_programID = 0;
	skC_VAOID.vaoId = 0;	skC_VAOID.vboId = 0;	skC_VAOID.nVertexs = 0;
	cubemapTexture = 0;

// Entorn VGI: Variables de control del menï¿½ Transforma
	transf = false;		trasl = false;		rota = false;		escal = false;
	fact_Tras = 1;		fact_Rota = 90;
	TG.VTras.x = 0.0;	TG.VTras.y = 0.0;	TG.VTras.z = 0;	TGF.VTras.x = 0.0;	TGF.VTras.y = 0.0;	TGF.VTras.z = 0;
	TG.VRota.x = 0;		TG.VRota.y = 0;		TG.VRota.z = 0;	TGF.VRota.x = 0;	TGF.VRota.y = 0;	TGF.VRota.z = 0;
	TG.VScal.x = 1;		TG.VScal.y = 1;		TG.VScal.z = 1;	TGF.VScal.x = 1;	TGF.VScal.y = 1;	TGF.VScal.z = 1;

	transX = false;		transY = false;		transZ = false;
	GTMatrix= glm::mat4(1.0);		// Inicialitzar a identitat

// Entorn VGI: Variables de control per les opcions de menï¿½ Ocultacions
	front_faces = true;	test_vis = false;	oculta = false;		back_line = false;

// Entorn VGI: Variables de control del menï¿½ Iluminaciï¿½		
	ilumina = FILFERROS;			ifixe = false;					ilum2sides = false;
	// Reflexions actives: Ambient [1], Difusa [2] i Especular [3]. No actives: Emission [0]. 
	sw_material[0] = false;			sw_material[1] = true;			sw_material[2] = true;			sw_material[3] = true;	sw_material[4] = false;
	sw_material_old[0] = false;		sw_material_old[1] = true;		sw_material_old[2] = true;		sw_material_old[3] = true;	sw_material_old[4] = true;
	textura = false;				t_textura = CAP;				textura_map = true;
	for (i = 0; i < NUM_MAX_TEXTURES; i++) texturesID[i] = -1;
	tFlag_invert_Y = false;

// Entorn VGI: Variables de control del menï¿½ Llums
// Entorn VGI: Inicialitzaciï¿½ variables Llums
	llum_ambient = true;
	for (i = 1; i < NUM_MAX_LLUMS; i++) llumGL[i].encesa = false;
	for (i = 0; i < NUM_MAX_LLUMS; i++) {
		llumGL[i].encesa = false;
		llumGL[i].difusa[0] = 1.0f;	llumGL[i].difusa[1] = 1.0f;	llumGL[i].difusa[2] = 1.0f;	llumGL[i].difusa[3] = 1.0f;
		llumGL[i].especular[0] = 1.0f; llumGL[i].especular[1] = 1.0f; llumGL[i].especular[2] = 1.0f; llumGL[i].especular[3] = 1.0f;
		}

// LLum 0: Atenuaciï¿½ constant (c=1), sobre l'eix Z, no restringida.
	llumGL[0].encesa = true;
	llumGL[0].difusa[0] = 1.0f;			llumGL[0].difusa[1] = 1.0f;			llumGL[0].difusa[2] = 1.0f;		llumGL[0].difusa[3] = 1.0f;
	llumGL[0].especular[0] = 1.0f;		llumGL[0].especular[1] = 1.0f;		llumGL[0].especular[2] = 1.0f;	llumGL[0].especular[3] = 1.0f;

	llumGL[0].posicio.R = 200.0;		llumGL[0].posicio.alfa = 90.0;		llumGL[0].posicio.beta = 0.0;		// Posiciï¿½ llum (x,y,z)=(0,0,200)
	llumGL[0].atenuacio.a = 0.0;		llumGL[0].atenuacio.b = 0.0;		llumGL[0].atenuacio.c = 1.0;		// Llum sense atenuaciï¿½ per distï¿½ncia (a,b,c)=(0,0,1)
	llumGL[0].restringida = false;
	llumGL[0].spotdirection[0] = 0.0;	llumGL[0].spotdirection[1] = 0.0;	llumGL[0].spotdirection[2] = 0.0;
	llumGL[0].spotcoscutoff = 0.0;		llumGL[0].spotexponent = 0.0;

// LLum 1: Atenuaciï¿½ constant (c=1), sobre l'eix X, no restringida.
	llumGL[1].encesa = false;
	llumGL[1].difusa[0] = 1.0f;			llumGL[1].difusa[1] = 1.0f;			llumGL[1].difusa[2] = 1.0f;		llumGL[1].difusa[3] = 1.0f;
	llumGL[1].especular[0] = 1.0f;		llumGL[1].especular[1] = 1.0f;		llumGL[1].especular[2] = 1.0f;	llumGL[1].especular[3] = 1;

	llumGL[1].posicio.R = 75.0;			llumGL[1].posicio.alfa = 0.0;		llumGL[1].posicio.beta = 0.0;// (x,y,z)=(75,0,0)
	llumGL[1].atenuacio.a = 0.0;		llumGL[1].atenuacio.b = 0.0;		llumGL[1].atenuacio.c = 1.0;
	llumGL[1].restringida = false;
	llumGL[1].spotdirection[0] = 0.0;	llumGL[1].spotdirection[1] = 0.0;	llumGL[1].spotdirection[2] = 0.0;
	llumGL[1].spotcoscutoff = 0.0;		llumGL[1].spotexponent = 0.0;

// LLum 2: Atenuaciï¿½ constant (c=1), sobre l'eix Y, no restringida.
	llumGL[2].encesa = false;
	llumGL[2].difusa[1] = 1.0f;			llumGL[2].difusa[1] = 1.0f;			llumGL[2].difusa[2] = 1.0f;		llumGL[2].difusa[3] = 1.0f;
	llumGL[2].especular[1] = 1.0f;		llumGL[2].especular[1] = 1.0f;		llumGL[2].especular[2] = 1.0f;	llumGL[2].especular[3] = 1;

	llumGL[2].posicio.R = 75.0;			llumGL[2].posicio.alfa = 0.0;		llumGL[2].posicio.beta = 90.0;	// (x,y,z)=(0,75,0)
	llumGL[2].atenuacio.a = 0.0;		llumGL[2].atenuacio.b = 0.0;		llumGL[2].atenuacio.c = 1.0;
	llumGL[2].restringida = false;
	llumGL[2].spotdirection[0] = 0.0;	llumGL[2].spotdirection[1] = 0.0;	llumGL[2].spotdirection[2] = 0.0;
	llumGL[2].spotcoscutoff = 0.0;		llumGL[2].spotexponent = 0.0;

// LLum 3: Atenuaciï¿½ constant (c=1), sobre l'eix Y=X, no restringida.
	llumGL[3].encesa = false;
	llumGL[3].difusa[0] = 1.0f;			llumGL[2].difusa[1] = 1.0f;			llumGL[3].difusa[2] = 1.0f;		llumGL[3].difusa[3] = 1.0f;
	llumGL[3].especular[0] = 1.0f;		llumGL[2].especular[1] = 1.0f;		llumGL[3].especular[2] = 1.0f;	llumGL[3].especular[3] = 1;

	llumGL[3].posicio.R = 75.0;			llumGL[3].posicio.alfa = 45.0;		llumGL[3].posicio.beta = 45.0;// (x,y,z)=(75,75,75)
	llumGL[3].atenuacio.a = 0.0;		llumGL[3].atenuacio.b = 0.0;		llumGL[3].atenuacio.c = 1.0;
	llumGL[3].restringida = false;
	llumGL[3].spotdirection[0] = 0.0;	llumGL[3].spotdirection[1] = 0.0;	llumGL[3].spotdirection[2] = 0.0;
	llumGL[3].spotcoscutoff = 0.0;		llumGL[3].spotexponent = 0.0;

// LLum 4: Atenuaciï¿½ constant (c=1), sobre l'eix -Z, no restringida.
	llumGL[4].encesa = false;
	llumGL[4].difusa[0] = 1.0f;			llumGL[4].difusa[1] = 1.0f;			llumGL[4].difusa[2] = 1.0f;		llumGL[4].difusa[3] = 1.0f;
	llumGL[4].especular[0] = 1.0f;		llumGL[4].especular[1] = 1.0f;		llumGL[4].especular[2] = 1.0f;	llumGL[4].especular[3] = 1;

	llumGL[4].posicio.R = 75.0;			llumGL[4].posicio.alfa = -90.0;		llumGL[4].posicio.beta = 0.0;// (x,y,z)=(0,0,-75)
	llumGL[4].atenuacio.a = 0.0;		llumGL[4].atenuacio.b = 0.0;		llumGL[4].atenuacio.c = 1.0;
	llumGL[4].restringida = false;
	llumGL[4].spotdirection[0] = 0.0;	llumGL[4].spotdirection[1] = 0.0;	llumGL[4].spotdirection[2] = 0.0;
	llumGL[4].spotcoscutoff = 0.0;		llumGL[4].spotexponent = 0.0;

// LLum #5:
	llumGL[5].encesa = false;
	llumGL[5].difusa[0] = 1.0f;			llumGL[5].difusa[1] = 1.0f;			llumGL[5].difusa[2] = 1.0f;		llumGL[5].difusa[3] = 1.0f;
	llumGL[5].especular[0] = 1.0f;		llumGL[5].especular[1] = 1.0f;		llumGL[5].especular[2] = 1.0f;	llumGL[5].especular[3] = 1;

	llumGL[5].posicio.R = 0.0;			llumGL[5].posicio.alfa = 0.0;		llumGL[5].posicio.beta = 0.0; // Cap posiciï¿½ definida
	llumGL[5].atenuacio.a = 0.0;		llumGL[5].atenuacio.b = 0.0;		llumGL[5].atenuacio.c = 1.0;
	llumGL[5].restringida = false;
	llumGL[5].spotdirection[0] = 0.0;	llumGL[5].spotdirection[1] = 0.0;	llumGL[5].spotdirection[2] = 0.0;
	llumGL[5].spotcoscutoff = 0.0;		llumGL[5].spotexponent = 0.0;

// LLum #6: Llum Vaixell, configurada a la funciï¿½ vaixell() en escena.cpp.
	llumGL[6].encesa = false;
	llumGL[6].difusa[0] = 1.0f;			llumGL[6].difusa[1] = 1.0f;			llumGL[6].difusa[2] = 1.0f;		llumGL[6].difusa[3] = 1.0f;
	llumGL[6].especular[0] = 1.0f;		llumGL[6].especular[1] = 1.0f;		llumGL[6].especular[2] = 1.0f;	llumGL[6].especular[3] = 1;

	llumGL[6].posicio.R = 0.0;			llumGL[6].posicio.alfa = 0.0;		llumGL[6].posicio.beta = 0.0; // Cap posiciï¿½ definida, definida en funciï¿½ vaixell() en escena.cpp
	llumGL[6].atenuacio.a = 0.0;		llumGL[6].atenuacio.b = 0.0;		llumGL[6].atenuacio.c = 1.0;
	llumGL[6].restringida = false;
	llumGL[6].spotdirection[0] = 0.0;	llumGL[6].spotdirection[1] = 0.0;	llumGL[6].spotdirection[2] = 0.0;
	llumGL[6].spotcoscutoff = 0.0;		llumGL[6].spotexponent = 0.0;

// LLum #7: Llum Far, configurada a la funciï¿½ faro() en escena.cpp.
	llumGL[7].encesa = false;
	llumGL[7].difusa[0] = 1.0f;			llumGL[7].difusa[1] = 1.0f;			llumGL[7].difusa[2] = 1.0f;		llumGL[7].difusa[3] = 1.0f;
	llumGL[7].especular[0] = 1.0f;		llumGL[7].especular[1] = 1.0f;		llumGL[7].especular[2] = 1.0f;	llumGL[7].especular[3] = 1;

	llumGL[7].posicio.R = 0.0;			llumGL[7].posicio.alfa = 0.0;		llumGL[7].posicio.beta = 0.0; // Cap posiciï¿½ definida, definida en funciï¿½ faro() en escena.cpp
	llumGL[7].atenuacio.a = 0.0;		llumGL[7].atenuacio.b = 0.0;		llumGL[7].atenuacio.c = 1.0;
	llumGL[7].restringida = false;
	llumGL[7].spotdirection[0] = 0.0;	llumGL[7].spotdirection[1] = 0.0;	llumGL[7].spotdirection[2] = 0.0;
	llumGL[7].spotcoscutoff = 0.0;		llumGL[7].spotexponent = 0.0;

// Entorn VGI: Variables de control del menï¿½ Shaders
	//InitAPI();
	shader_menu = CAP;		shader_programID = 0;
	//flat_programID = 0;		gouraud_programID = 0;		phong_programID = 0;


// Cï¿½rrega SHADERS
// Cï¿½rrega Shader Eixos
	fprintf(stderr, "Eixos: \n");
	eixos_programID = shaderEixos.initializeShaders(".\\shaders\\eixos");

// Cï¿½rrega Shader Skybox
	fprintf(stderr, "SkyBox: \n");
	skC_programID = shader_SkyBoxC.initializeShaders(".\\shaders\\skybox");

// Cï¿½rrega Shader de Gouraud
	sw_shader = true;				shader_menu = GOURAUD_SHADER;	shader_programID = 0;
	//shaderGouraud.loadFileShaders(".\\shaders\\gouraud_shdrML.vert", ".\\shaders\\gouraud_shdrML.frag");
	fprintf(stderr, "Gouraud_shdrML: \n");
	shader_programID = shaderGouraud.initializeShaders(".\\shaders\\gouraud_shdrML");

	fprintf(stderr, "ui: \n");
	Shader::UI.initializeShaders(".\\shaders\\ui");
	//shader_programID = shaderGouraud.getProgramID();
	//shader_programID = initializeShaders(".\\shaders\\gouraud_shdrML");

// Entorn VGI: Variables de control dels botons de mouse
	//m_PosEAvall = (0, 0);		m_PosDAvall = (0, 0);
	m_PosEAvall.x = 0;			m_PosEAvall.y = 0;			m_PosDAvall.x = 0;			m_PosDAvall.y = 0;
	m_ButoEAvall = false;		m_ButoDAvall = false;
	m_EsfeEAvall.R = 0.0;		m_EsfeEAvall.alfa = 0.0;	m_EsfeEAvall.beta = 0.0;
	m_EsfeIncEAvall.R = 0.0;	m_EsfeIncEAvall.alfa = 0.0;	m_EsfeIncEAvall.beta = 0.0;

// Entorn VGI: Variables que controlen parï¿½metres visualitzaciï¿½: Mides finestra Windows i PV
	w = 640;			h = 480;								// Mides finestra
	w_old = 640;		h_old = 480;							// Copia mides finestre per a FullScreen
	OPV.R = 15.0;		OPV.alfa = 0.0;		OPV.beta = 0.0;	// Origen PV en esfï¿½riques
	Vis_Polar = POLARZ;

// Entorn VGI: Color de fons i de l'objecte
	fonsR = true;		fonsG = true;		fonsB = true;
	c_fons.r = 0.0;		c_fons.g = 0.0;		c_fons.b = 0.0;
	sw_color = false;
	col_obj.r = 1.0;	col_obj.g = 1.0;	col_obj.b = 1.0;		col_obj.a = 1.0;

// Entorn VGI: Objecte 3DS
	//Ob3DS = NULL;		vao_3DS.vaoId = 0;		vao_3DS.vboId = 0;		vao_3DS.nVertexs = 0;

// Entorn VGI: Objecte OBJ
	ObOBJ = NULL;		vao_OBJ.vaoId = 0;		vao_OBJ.vboId = 0;		vao_OBJ.nVertexs = 0;

// Entorn VGI: OBJECTE --> Corba B-Spline i Bezier
	npts_T = 0;
	for (i = 0; i < MAX_PATCH_CORBA; i = i++)
	{	PC_t[i].x = 0.0;
		PC_t[i].y = 0.0;
		PC_t[i].z = 0.0;
	}

	pas_CS = PAS_BSPLINE;
	sw_Punts_Control = false;

// TRIEDRE DE FRENET / DARBOUX: VT: vector Tangent, VNP: Vector Normal Principal, VBN: vector BiNormal
	dibuixa_TriedreFrenet = false;
	VT = { 0.0, 0.0, 1.0 };		VNP = { 1.0, 0.0, 0.0 };	VBN = { 0.0, 1.0, 0.0 };

// Entorn VGI: Variables del Timer
	t = 0;			anima = false;

// Entorn VGI: Variables de l'objecte FRACTAL
	t_fractal = CAP;	soroll = 'C';
	pas = 64;			pas_ini = 64;
	sw_il = true;		palcolFractal = false;

// Entorn VGI: Altres variables
	mida = 1.0;			nom = "";		buffer = "";
	initVAOList();	// Inicialtzar llista de VAO'S.

// Entorn VGI: Inicialitzaciï¿½ de les llibreries DevIL per a la cï¿½rrega de textures i fitxers .3DS
	//ilInit();					// Inicialitzar llibreria IL
	//iluInit();					// Inicialitzar llibreria ILU
	//ilutRenderer(ILUT_OPENGL);	// Inicialitzar llibreria ILUT per a OpenGL
}




void InitAPI()
{
// Vendor, Renderer, Version, Shading Laguage Version i Extensions suportades per la placa grï¿½fica gravades en fitxer extensions.txt
	std::string nomf = "extensions.txt";
	char const* nomExt = "";
	const char* nomfitxer;
	nomfitxer = nomf.c_str();	// Conversiï¿½ tipus string --> char *
	int num_Ext;

	char* str = (char*)glGetString(GL_VENDOR);
	FILE* f = fopen(nomfitxer, "w");
	if(f)	{	fprintf(f,"VENDOR: %s\n",str);
				fprintf(stderr, "VENDOR: %s\n", str);
				str = (char*)glGetString(GL_RENDERER);
				fprintf(f, "RENDERER: %s\n", str);
				fprintf(stderr, "RENDERER: %s\n", str);
				str = (char*)glGetString(GL_VERSION);
				fprintf(f, "VERSION: %s\n", str);
				fprintf(stderr, "VERSION: %s\n", str);
				str = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
				fprintf(f, "SHADING_LANGUAGE_VERSION: %s\n", str);
				fprintf(stderr, "SHADING_LANGUAGE_VERSION: %s\n", str);
				glGetIntegerv(GL_NUM_EXTENSIONS, &num_Ext);
				fprintf(f, "EXTENSIONS: \n");
				fprintf(stderr, "EXTENSIONS: \n");
				for (int i = 0; i < num_Ext; i++)
				{	nomExt = (char const*)glGetStringi(GL_EXTENSIONS, i);
					fprintf(f, "%s \n", nomExt);
					//fprintf(stderr, "%s", nomExt);	// Displaiar extensions per pantalla
				}
				//fprintf(stderr, "\n");				// Displaiar <cr> per pantalla desprï¿½s extensions
//				str = (char*)glGetString(GL_EXTENSIONS);
//				fprintf(f, "EXTENSIONS: %s\n", str);
				//fprintf(stderr, "EXTENSIONS: %s\n", str);
				fclose(f);
			}

// Program
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	glUniform1iv = (PFNGLUNIFORM1IVPROC)wglGetProcAddress("glUniform1iv");
	glUniform2iv = (PFNGLUNIFORM2IVPROC)wglGetProcAddress("glUniform2iv");
	glUniform3iv = (PFNGLUNIFORM3IVPROC)wglGetProcAddress("glUniform3iv");
	glUniform4iv = (PFNGLUNIFORM4IVPROC)wglGetProcAddress("glUniform4iv");
	glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	glUniform1fv = (PFNGLUNIFORM1FVPROC)wglGetProcAddress("glUniform1fv");
	glUniform2fv = (PFNGLUNIFORM2FVPROC)wglGetProcAddress("glUniform2fv");
	glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)wglGetProcAddress("glVertexAttrib1f");
	glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)wglGetProcAddress("glVertexAttrib1fv");
	glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)wglGetProcAddress("glVertexAttrib2fv");
	glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)wglGetProcAddress("glVertexAttrib3fv");
	glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)wglGetProcAddress("glVertexAttrib4fv");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)wglGetProcAddress("glGetActiveUniform");

// Shader
	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");

// VBO
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	glBufferSubData = (PFNGLBUFFERSUBDATAPROC)wglGetProcAddress("glBufferSubData");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
}


void GetGLVersion(int* major, int* minor)
{
	// for all versions
	char* ver = (char*)glGetString(GL_VERSION); // ver = "3.2.0"

	*major = ver[0] - '0';
	if (*major >= 3)
	{
		// for GL 3.x
		glGetIntegerv(GL_MAJOR_VERSION, major);		// major = 3
		glGetIntegerv(GL_MINOR_VERSION, minor);		// minor = 2
	}
	else
	{
		*minor = ver[2] - '0';
	}

	// GLSL
	ver = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);	// 1.50 NVIDIA via Cg compiler
}

void OnSize(GLFWwindow* window, int width, int height)
{
// TODO: Agregue aquï¿½ su cï¿½digo de controlador de mensajes

// A resize event occured; cx and cy are the window's new width and height.
// Find the OpenGL change size function given in the Lab 1 notes and call it here

// Entorn VGI: MODIFICACIï¿½ ->Establim les mides de la finestra actual
	w = width;	h = height;

// Crida a OnPaint per a redibuixar la pantalla
//	OnPaint();
}


// OnPaint: Funciï¿½ de dibuix i visualitzaciï¿½ en frame buffer del frame
void OnPaint(GLFWwindow* window)
{
// TODO: Agregue aquï¿½ su cï¿½digo de controlador de mensajes
	GLdouble vpv[3] = { 0.0, 0.0, 1.0 };

// Cridem a les funcions de l'escena i la projecciï¿½ segons s'hagi 
// seleccionat una projecciï¿½ o un altra
	switch (projeccio)
	{
	case AXONOM:
// PROJECCIï¿½ AXONOMï¿½TRICA
// Activaciï¿½ del retall de pantalla
		glEnable(GL_SCISSOR_TEST);

// Retall
		glScissor(0, 0, w, h);
		glViewport(0, 0, w, h);

// Aquï¿½ farem les crides per a definir Viewport, Projecciï¿½ i Cï¿½mara: INICI -------------------------

// Aquï¿½ farem les cridesper a definir Viewport, Projecciï¿½ i Cï¿½mara:: FI -------------------------
		// Dibuixar Model (escena)
		configura_Escena();     // Aplicar Transformacions Geometriques segons persiana Transformacio i configurar objectes
		dibuixa_Escena(glm::vec3(0));		// Dibuix geometria de l'escena amb comandes GL.

	// Intercanvia l'escena al front de la pantalla
		glfwSwapBuffers(window);
		break;

	case ORTO:
// PROJECCIï¿½ ORTOGRï¿½FICA
// Activaciï¿½ del retall de pantalla
		glEnable(GL_SCISSOR_TEST);

// Retall
		glScissor(0, 0, w, h);
		glViewport(0, 0, w, h);

		// Fons condicionat al color de fons
		if ((c_fons.r < 0.5) || (c_fons.g < 0.5) || (c_fons.b < 0.5))
			FonsB();
		else
			FonsN();

// Aquï¿½ farem les quatre crides a ProjeccioOrto i Ortografica per obtenir 
// les quatre vistes ortogrï¿½fiques
// ---------- Entorn VGI: DESCOMENTAR QUAN S'IMPLEMENTI PROJECCIO ORTOGRï¿½FICA
// PLANTA (Inferior Esquerra)
		// Definiciï¿½ de Viewport, Projecciï¿½ i Cï¿½mara
		ProjectionMatrix = Projeccio_Orto();
		ViewMatrix = Vista_Ortografica(shader_programID, 0, OPV.R, c_fons, col_obj, objecte, mida, pas, front_faces, oculta,
			test_vis, back_line, ilumina, llum_ambient, llumGL, ifixe, ilum2sides,
			eixos, grid, hgrid);
		// Dibuix de l'Objecte o l'Escena
		configura_Escena();     // Aplicar Transformacions Geometriques segons persiana Transformacio i configurar objectes
		dibuixa_Escena(glm::vec3(0));		// Dibuix geometria de l'escena amb comandes GL.

// ISOMï¿½TRICA (Inferior Dreta)
		// Definiciï¿½ de Viewport, Projecciï¿½ i Cï¿½mara
		ProjectionMatrix = Projeccio_Orto();
		ViewMatrix = Vista_Ortografica(shader_programID, 3, OPV.R, c_fons, col_obj, objecte, mida, pas, front_faces, oculta,
			test_vis, back_line, ilumina, llum_ambient, llumGL, ifixe, ilum2sides,
			eixos, grid, hgrid);
		// Dibuix de l'Objecte o l'Escena
		configura_Escena();     // Aplicar Transformacions Geometriques segons persiana Transformacio i configurar objectes
		dibuixa_Escena(glm::vec3(0));		// Dibuix geometria de l'escena amb comandes GL.

// ALï¿½AT (Superior Esquerra)
		// Definiciï¿½ de Viewport, Projecciï¿½ i Cï¿½mara
		ProjectionMatrix = Projeccio_Orto();
		ViewMatrix = Vista_Ortografica(shader_programID, 1, OPV.R, c_fons, col_obj, objecte, mida, pas, front_faces, oculta,
			test_vis, back_line, ilumina, llum_ambient, llumGL, ifixe, ilum2sides,
			eixos, grid, hgrid);
		// Dibuix de l'Objecte o l'Escena
		  configura_Escena();     // Aplicar Transformacions Geom?triques segons persiana Transformacio i configurar objectes
	 	  dibuixa_Escena(glm::vec3(0));		// Dibuix geometria de l'escena amb comandes GL.

// PERFIL (Superior Dreta)
		// Definiciï¿½ de Viewport, Projecciï¿½ i Cï¿½mara
		ProjectionMatrix = Projeccio_Orto();
		ViewMatrix = Vista_Ortografica(shader_programID, 2, OPV.R, c_fons, col_obj, objecte, mida, pas, front_faces, oculta,
			test_vis, back_line, ilumina, llum_ambient, llumGL, ifixe, ilum2sides,
			eixos, grid, hgrid);
		// Dibuix de l'Objecte o l'Escena
		configura_Escena();     // Aplicar Transformacions Geom?triques segons persiana Transformacio i configurar objectes
		  // glScalef();			// Escalat d'objectes, per adequar-los a les vistes ortogrï¿½fiques (Prï¿½ctica 2)
		dibuixa_Escena(glm::vec3(0));		// Dibuix geometria de l'escena amb comandes GL.

		// Intercanvia l'escena al front de la pantalla
		glfwSwapBuffers(window);
		break;

	case PERSPECT:
// PROJECCIï¿½ PERSPECTIVA
		//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Set Perspective Calculations To Most Accurate
		glDisable(GL_SCISSOR_TEST);		// Desactivaciï¿½ del retall de pantalla

		// Activar shader Visualitzaciï¿½ Escena
		glUseProgram(shader_programID);

		// Definiciï¿½ de Viewport, Projecciï¿½ i Cï¿½mara
		ProjectionMatrix = Projeccio_Perspectiva(shader_programID, 0, 0, w, h, OPV.R);

		// Definiciï¿½ de la cï¿½mera.
		if (camera == CAM_ESFERICA) {
			n[0] = 0;		n[1] = 0;		n[2] = 0;
			ViewMatrix = Vista_Esferica(shader_programID, OPV, Vis_Polar, pan, tr_cpv, tr_cpvF, c_fons, col_obj, objecte, mida, pas,
				front_faces, oculta, test_vis, back_line,
				ilumina, llum_ambient, llumGL, ifixe, ilum2sides,
				eixos, grid, hgrid);
		}
		else if (camera == CAM_NAVEGA) {
			ViewMatrix = Vista_Navega(shader_programID, opvN, false, n, vpv, pan, tr_cpv, tr_cpvF, c_fons, col_obj, objecte, true, pas,
				front_faces, oculta, test_vis, back_line,
				ilumina, llum_ambient, llumGL, ifixe, ilum2sides,
				eixos, grid, hgrid);
		}
		else if (camera == CAM_GEODE) {
			ViewMatrix = Vista_Geode(shader_programID, OPV_G, Vis_Polar, pan, tr_cpv, tr_cpvF, c_fons, col_obj, objecte, mida, pas,
				front_faces, oculta, test_vis, back_line,
				ilumina, llum_ambient, llumGL, ifixe, ilum2sides,
				eixos, grid, hgrid);
		}
		else if (camera == CAM_PERSONALITZADA)
		{
			ViewMatrix = Vista_Personalitzada(shader_programID, Camera::MAIN_CAMERA.horizontal_angle, Camera::MAIN_CAMERA.vertical_angle, Camera::MAIN_CAMERA.position, 
				c_fons, col_obj, objecte, true, pas,
				front_faces, oculta, test_vis, back_line,
				ilumina, llum_ambient, llumGL, ifixe, ilum2sides,
				eixos, grid, hgrid);
		}

		// Dibuix de l'Objecte o l'Escena
		configura_Escena();     // Aplicar Transformacions Geometriques segons persiana Transformacio i configurar objectes.
		dibuixa_Escena(skybox_offset);		// Dibuix geometria de l'escena amb comandes GL.

		// Intercanvia l'escena al front de la pantalla
		glfwSwapBuffers(window);
		break;

	default:
// Cï¿½rrega SHADERS
// Cï¿½rrega Shader Eixos
		//if (!eixos_Id) eixos_Id = deixos();						// Funciï¿½ que defineix els Eixos Coordenades Mï¿½n com un VAO.
		if (!eixos_programID) eixos_programID = shaderEixos.loadFileShaders(".\\shaders\\eixos.VERT", ".\\shaders\\eixos.FRAG");

// Cï¿½rrega Shader de Gouraud
		shader_menu = GOURAUD_SHADER;
		if (!shader_programID) shader_programID = shaderLighting.loadFileShaders(".\\shaders\\gouraud_shdrML.vert", ".\\shaders\\gouraud_shdrML.frag");
		//gouraud_programID = shader_programID;

// Entorn VGI: Creaciï¿½ de la llista que dibuixarï¿½ els eixos Coordenades Mï¿½n. Funciï¿½ on estï¿½ codi per dibuixar eixos	
		if (!eixos_Id) eixos_Id = deixos();						// Funciï¿½ que defineix els Eixos Coordenades Mï¿½n com un VAO.

		// Cï¿½rrega VAO Skybox Cube
		if (skC_VAOID.vaoId == 0) skC_VAOID = loadCubeSkybox_VAO();
		Set_VAOList(CUBE_SKYBOX, skC_VAOID);

	/*
		if (!cubemapTexture) {	// load Skybox textures
								// -------------
								std::vector<std::string> faces = 
									{	".\\textures\\skybox\\right.jpg",
										".\\textures\\skybox\\left.jpg",
										".\\textures\\skybox\\top.jpg",
										".\\textures\\skybox\\bottom.jpg",
										".\\textures\\skybox\\front.jpg",
										".\\textures\\skybox\\back.jpg"
									};
								cubemapTexture = loadCubemap(faces);
							}
*/
// Crida a la funciï¿½ Fons Blanc
		FonsB();


// Intercanvia l'escena al front de la pantalla
		glfwSwapBuffers(window);
		break;
}

//  Actualitzar la barra d'estat de l'aplicaciï¿½ amb els valors R,A,B,PVx,PVy,PVz
	if (statusB) Barra_Estat();
}

// configura_Escena: Funcio que configura els parametres de Model i dibuixa les
//                   primitives OpenGL dins classe Model
void configura_Escena() {

// Aplicar Transformacions Geometriques segons persiana Transformacio i Quaternions
	GTMatrix = instancia(transf, TG, TGF);
}

// dibuixa_Escena: Funcio que crida al dibuix dels diferents elements de l'escana
void dibuixa_Escena(glm::vec3 skybox_offset) {

	//glUseProgram(shader_programID);
//	Dibuix SkyBox Cï¿½bic.
	if (SkyBoxCube) dibuixa_Skybox(skC_programID, cubemapTexture, Vis_Polar, ProjectionMatrix, ViewMatrix, skybox_offset);

//	Dibuix Coordenades Mï¿½n i Reixes.
	dibuixa_Eixos(eixos_programID, eixos, eixos_Id, grid, hgrid, ProjectionMatrix, ViewMatrix);

// Escalat d'objectes, per adequar-los a les vistes ortogrï¿½fiques (Prï¿½ctica 2)
//	GTMatrix = glm::scalef();

//	Dibuix geometria de l'escena amb comandes GL.
	dibuixa_EscenaGL(shader_programID, eixos, eixos_Id, grid, hgrid, objecte, col_obj, sw_material,
		textura, texturesID, textura_map, tFlag_invert_Y,
		npts_T, PC_t, pas_CS, sw_Punts_Control, dibuixa_TriedreFrenet,
		FIT_3DS, FIT_OBJ, // VAO's i nombre de vï¿½rtexs dels objectes 3DS i OBJ
		ViewMatrix, GTMatrix);
}

// Barra_Estat: Actualitza la barra d'estat (Status Bar) de l'aplicaciï¿½ amb els
//      valors R,A,B,PVx,PVy,PVz en Visualitzaciï¿½ Interactiva.
void Barra_Estat()
{
	std::string buffer,sss;
	CEsfe3D OPVAux;
	double PVx, PVy, PVz;

// Status Bar fitxer fractal
	if (nom != "") fprintf(stderr, "Fitxer: %s \n",nom.c_str());

// Cï¿½lcul dels valors per l'opciï¿½ Vista->Navega
	if (projeccio != CAP && projeccio != ORTO) {
		if (camera == CAM_ESFERICA)
		{	// Cï¿½mera Esfï¿½rica
			OPVAux.R = OPV.R; OPVAux.alfa = OPV.alfa; OPVAux.beta = OPV.beta;
		}
		else if (camera == CAM_NAVEGA)
		{	// Cï¿½mera Navega
			OPVAux.R = sqrt(opvN.x * opvN.x + opvN.y * opvN.y + opvN.z * opvN.z);
			OPVAux.alfa = (asin(opvN.z / OPVAux.R) * 180) / PI;
			OPVAux.beta = (atan(opvN.y / opvN.x)) * 180 / PI;
		}
		else {	// Cï¿½mera Geode
			OPVAux.R = OPV_G.R; OPVAux.alfa = OPV_G.alfa; OPVAux.beta = OPV_G.beta;
		}
	}
	else {
		OPVAux.R = OPV.R; OPVAux.alfa = OPV.alfa; OPVAux.beta = OPV.beta;
	}

// Status Bar R Origen Punt de Vista
	if (projeccio == CAP) buffer = "       ";
		else if (projeccio == ORTO) buffer = " ORTO   ";
			else if (camera == CAM_NAVEGA) buffer = " NAV   ";
				else buffer= std::to_string(OPVAux.R);
	// Refrescar posiciï¿½ R Status Bar
	fprintf(stderr, "R=: %s", buffer.c_str());

// Status Bar angle alfa Origen Punt de Vista
	if (projeccio == CAP) buffer = "       ";
		else if (projeccio == ORTO) buffer = "ORTO   ";
			else if (camera == CAM_NAVEGA) buffer = " NAV   ";
				else buffer = std::to_string(OPVAux.alfa);
	// Refrescar posiciï¿½ angleh Status Bar
	fprintf(stderr, " a=: %s", buffer.c_str());

	// Status Bar angle beta Origen Punt de Vista
	if (projeccio == CAP) buffer = "       ";
		else if (projeccio == ORTO) buffer = "ORTO   ";
			else if (camera == CAM_NAVEGA) buffer = " NAV   ";
				else buffer = std::to_string(OPVAux.beta);
	// Refrescar posiciï¿½ anglev Status Bar
	fprintf(stderr, " ï¿½=: %s  ", buffer.c_str());

// Transformaciï¿½ PV de Coord. esfï¿½riques (R,anglev,angleh) --> Coord. cartesianes (PVx,PVy,PVz)
	if (camera == CAM_NAVEGA) { PVx = opvN.x; PVy = opvN.y; PVz = opvN.z; }
	else {	if (Vis_Polar == POLARZ) 
			{	PVx = OPVAux.R * cos(OPVAux.beta * PI / 180) * cos(OPVAux.alfa * PI / 180);
				PVy = OPVAux.R * sin(OPVAux.beta * PI / 180) * cos(OPVAux.alfa * PI / 180);
				PVz = OPVAux.R * sin(OPVAux.alfa * PI / 180);
			}
		else if (Vis_Polar == POLARY) 
				{	PVx = OPVAux.R * sin(OPVAux.beta * PI / 180) * cos(OPVAux.alfa * PI / 180);
					PVy = OPVAux.R * sin(OPVAux.alfa * PI / 180);
					PVz = OPVAux.R * cos(OPVAux.beta * PI / 180) * cos(OPVAux.alfa * PI / 180);
				}
				else {	PVx = OPVAux.R * sin(OPVAux.alfa * PI / 180);
						PVy = OPVAux.R * cos(OPVAux.beta * PI / 180) * cos(OPVAux.alfa * PI / 180);
						PVz = OPVAux.R * sin(OPVAux.beta * PI / 180) * cos(OPVAux.alfa * PI / 180);
					}
		}

// Status Bar PVx
	if (projeccio == CAP) buffer = "       ";
	else if (pan) buffer = std::to_string(tr_cpv.x);
	else buffer = std::to_string(PVx);
	//sss = _T("PVx=") + buffer;
// Refrescar posiciï¿½ PVx Status Bar
	fprintf(stderr, "PVx= %s", buffer.c_str());

// Status Bar PVy
	if (projeccio == CAP) buffer = "       ";
	else if (pan) buffer = std::to_string(tr_cpv.y);
	else buffer = std::to_string(PVy);
	//sss = "PVy=" + buffer;
// Refrescar posiciï¿½ PVy Status Bar
	fprintf(stderr, " PVy= %s", buffer.c_str());

// Status Bar PVz
	if (projeccio == CAP) buffer = "       ";
	else if (pan) buffer = std::to_string(tr_cpv.z);
	else buffer = std::to_string(PVz);
	//sss = "PVz=" + buffer;
// Refrescar posiciï¿½ PVz Status Bar
	fprintf(stderr, " PVz= %s \n", buffer.c_str());

// Status Bar per indicar el modus de canvi de color (FONS o OBJECTE)
	sss = " ";
	if (sw_grid) sss = "GRID ";
		else if (pan) sss = "PAN ";
			else if (camera == CAM_NAVEGA) sss = "NAV ";
				else if (sw_color) sss = "OBJ ";
					else sss = "FONS ";
// Refrescar posiciï¿½ Transformacions en Status Bar
	fprintf(stderr, "%s ", sss.c_str());

// Status Bar per indicar tipus de Transformaciï¿½ (TRAS, ROT, ESC)
	sss = " ";
	if (transf) {	if (rota) sss = "ROT";
					else if (trasl) sss = "TRA";
					else if (escal) sss = "ESC";
				}
	else if ((!sw_grid) && (!pan) && (camera != CAM_NAVEGA))
	{	// Components d'intensitat de fons que varien per teclat
		if ((fonsR) && (fonsG) && (fonsB)) sss = " RGB";
		else if ((fonsR) && (fonsG)) sss = " RG ";
		else if ((fonsR) && (fonsB)) sss = " R   B";
		else if ((fonsG) && (fonsB)) sss = "   GB";
		else if (fonsR) sss = " R  ";
		else if (fonsG) sss = "   G ";
		else if (fonsB) sss = "      B";
	}
// Refrescar posiciï¿½ Transformacions en Status Bar
	fprintf(stderr, "%s ", sss.c_str());

// Status Bar dels parï¿½metres de Transformaciï¿½, Color i posicions de Robot i Cama
	sss = " ";
	if (transf)
	{	if (rota)
		{	buffer = std::to_string(TG.VRota.x);
			sss = " " + buffer + " ";

			buffer = std::to_string(TG.VRota.y);
			sss = sss + buffer + " ";

			buffer = std::to_string(TG.VRota.z);
			sss = sss + buffer;
		}
		else if (trasl)
		{	buffer = std::to_string(TG.VTras.x);
			sss = " " + buffer + " ";

			buffer = std::to_string(TG.VTras.y);
			sss = sss + buffer + " ";

			buffer = std::to_string(TG.VTras.z);
			sss = sss + buffer;
		}
		else if (escal)
		{	buffer = std::to_string(TG.VScal.x);
			sss = " " + buffer + " ";

			buffer = std::to_string(TG.VScal.y);
			sss = sss + buffer + " ";

			buffer = std::to_string(TG.VScal.x);
			sss = sss + buffer;
		}
	}
	else if ((!sw_grid) && (!pan) && (camera != CAM_NAVEGA))
	{	if (!sw_color)
		{	// Color fons
			buffer = std::to_string(c_fons.r);
			sss = " " + buffer + " ";

			buffer = std::to_string(c_fons.g);
			sss = sss + buffer + " ";

			buffer = std::to_string(c_fons.b);
			sss = sss + buffer;
		}
		else
		{	// Color objecte
			buffer = std::to_string(col_obj.r);
			sss = " " + buffer + " ";

			buffer = std::to_string(col_obj.g);
			sss = sss + buffer + " ";

			buffer = std::to_string(col_obj.b);
			sss = sss + buffer;
		}
	}

// Refrescar posiciï¿½ PVz Status Bar
	fprintf(stderr, "%s \n", sss.c_str());

// Status Bar per indicar el pas del Fractal
	if (objecte == O_FRACTAL)
	{	buffer = std::to_string(pas);
		//sss = "Pas=" + buffer;
		fprintf(stderr, "Pas= %s \n", buffer.c_str());
	}
	else {	sss = "          ";
			fprintf(stderr, "%s \n", sss.c_str());
		}
}


/* ------------------------------------------------------------------------- */
/*                           CONTROL DEL TECLAT                              */
/* ------------------------------------------------------------------------- */

// OnKeyDown: Funciï¿½ de tractament de teclat (funciï¿½ que es crida quan es prem una tecla)
//   PARï¿½METRES:
//    - key: Codi del caracter seleccionat
//    - scancode: Nombre de vegades que s'ha apretat la tecla (acceleraciï¿½)
//    - action: Acciï¿½ de la tecla: GLFW_PRESS (si s'ha apretat), GLFW_REPEAT, si s'ha repetit pressiï¿½ i GL_RELEASE, si es deixa d'apretar.
//    - mods: Variable que identifica si la tecla s'ha pulsat directa (mods=0), juntament amb la tecla Shift (mods=1) o la tecla Ctrl (mods=2).
void OnKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods)
{
// TODO: Agregue aquï¿½ su cï¿½digo de controlador de mensajes o llame al valor predeterminado
	const double incr = 0.025f;
	double modul = 0;
	GLdouble vdir[3] = { 0, 0, 0 };

// EntornVGI: Si tecla pulsada és ESCAPE, tancar finestres i aplicació.
	if (mods == 0 && key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) glfwSetWindowShouldClose(window, GL_TRUE);

	else if (mods == 0 && key == GLFW_KEY_PRINT_SCREEN && action == GLFW_PRESS) statusB = !statusB;
	else if ((mods == 1) && (action == GLFW_PRESS)) Teclat_Shift(key, window);	// Shorcuts Shift Key
	else if ((mods == 2) && (action == GLFW_PRESS)) Teclat_Ctrl(key);	// Shortcuts Ctrl Key

	else if (mods == 0 && key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		std::cout << "CAM PERSONALITZADA" << std::endl;
		if (camera == CAM_PERSONALITZADA)
			camera = CAM_ESFERICA;
		else
			camera = CAM_PERSONALITZADA;
		Camera::MAIN_CAMERA.position = glm::vec3(0, 0, 1.8);
	}
	else if (mods == 0 && key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		Camera::MAIN_CAMERA.fly_behind();
	}
	
	else if (mods == 0 && key == GLFW_KEY_F && action == GLFW_PRESS)
	{
		if (!Camera::MAIN_CAMERA.flying)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			Camera::MAIN_CAMERA.fly();
			Menu::instance
				.change_indicator(MenuType::MENU);

			Crosshair::instance.disable();
		}
		else
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			Camera::MAIN_CAMERA.enterTrain();
			Menu::instance
				.remove_indicator();
		}
			
	}
	else if (camera == CAM_PERSONALITZADA && action == GLFW_PRESS && !Camera::MAIN_CAMERA.sit && !Camera::MAIN_CAMERA.flying && !Camera::MAIN_CAMERA.zoom)
	{
		if (key == GLFW_KEY_W) w_pressed = true;
		if (key == GLFW_KEY_S) s_pressed = true;
		if (key == GLFW_KEY_A) a_pressed = true;
		if (key == GLFW_KEY_D) d_pressed = true;

		std::cout << "MOVING" << std::endl;
		//soundEngine->play2D("../EntornVGI/media/Footsteps.mp3");
		std::cout << "NOT MOVING" << std::endl;

		if (key == GLFW_KEY_C) c_pressed = true;
	}
	else if (camera == CAM_PERSONALITZADA && action == GLFW_PRESS && Camera::MAIN_CAMERA.sit && !Camera::MAIN_CAMERA.flying)
	{
		if (key == GLFW_KEY_C) Camera::MAIN_CAMERA.standUp();
	}
	else if (camera == CAM_PERSONALITZADA && action == GLFW_PRESS && Camera::MAIN_CAMERA.zoom)
	{
		if (key == GLFW_KEY_C)
		{
			Camera::MAIN_CAMERA.zoomOut();
			contrasenya.clear();
			Level::CURRENT_LEVEL.panel->clear_display();

			InteractableEntity* euc = Level::CURRENT_LEVEL.my_entity_under_cursor;
			if (euc) //si hay algo bajo el cursor
			{
				if (euc->is_interactable())
					InteractionIndicator::instance.change_indicator(euc->interaction_type());
			}
		}
	}
	else if (camera == CAM_PERSONALITZADA && action == GLFW_RELEASE)
	{
		//soundEngine->removeSoundSource("../EntornVGI/media/Footsteps.mp3");
		if (key == GLFW_KEY_W) w_pressed = false;
		if (key == GLFW_KEY_S) s_pressed = false;
		if (key == GLFW_KEY_A) a_pressed = false;
		if (key == GLFW_KEY_D) d_pressed = false;
		if (key == GLFW_KEY_C) c_pressed = false;
	}
	else if (camera == CAM_NAVEGA) Teclat_Navega(key, action);

	else if ((sw_grid) && ((grid.x) || (grid.y) || (grid.z))) Teclat_Grid(key, action);
	else if (((key == GLFW_KEY_G) && (action == GLFW_PRESS)) && ((grid.x) || (grid.y) || (grid.z))) sw_grid = !sw_grid;
	else if ((key == GLFW_KEY_O) && (action == GLFW_PRESS)) sw_color = true; // Activaciï¿½ color objecte
	else if ((key == GLFW_KEY_F) && (action == GLFW_PRESS)) sw_color = false; // Activaciï¿½ color objecte
	else if ((!pan) && (!transf) && (camera == CAM_NAVEGA))
	{
		if (!sw_color) Teclat_ColorFons(key, action);
		else Teclat_ColorObjecte(key, action);
	}
	else {
		if (transf)
		{
			if (rota) Teclat_TransRota(key, action);
			else if (trasl) Teclat_TransTraslada(key, action);
			else if (escal) Teclat_TransEscala(key, action);
		}
		if (pan) Teclat_Pan(key, action);
		else if (camera == CAM_PLAY) Teclat_Play(key, action);
		else if (!sw_color) Teclat_ColorFons(key, action);
		else Teclat_ColorObjecte(key, action);
	}

// Crida a OnPaint() per redibuixar l'escena
	//OnPaint(window);

/*	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		activate_airship();

	int state = glfwGetKey(window, GLFW_KEY_E);
	if (state == GLFW_PRESS) activate_airship();
*/
}

void OnKeyUp(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

void OnTextDown(GLFWwindow* window, unsigned int codepoint)
{
}

// Teclat_Shift: Shortcuts per Pop Ups Fitxer, Finestra, Vista, Projecciï¿½ i Objecte
void Teclat_Shift(int key, GLFWwindow* window)
{
	const char* nomfitxer;
	char* nomfitx;
	bool testA = false;

	CColor color_Mar;

	switch (key)
	{	
// ----------- POP UP Fitxers
		// Tecla Obrir Fractal
		case GLFW_KEY_F1:
			objecte = O_FRACTAL;
			// Entorn VGI: Obrir diï¿½leg de lectura de fitxer (fitxers (*.MNT)
			nom = ".\\fractals\\escena8p.mnt";
			nomfitxer = nom.c_str();	// Conversiï¿½ tipus string --> char *

			// Conversiï¿½ std::string --> char *
			nomfitx = new char[nom.length() + 1];
			strcpy(nomfitx, nom.c_str());
			// Entorn VGI: Llegir fitxer fractal (nomfitx) i inicialitzar alï¿½ades

			break;

		// Tecla Obrir Fitxer OBJ
		case GLFW_KEY_F2:
			objecte = OBJOBJ;	textura = true;

			// Entorn VGI: Obrir diï¿½leg de lectura de fitxer (fitxers (*.OBJ)
			nom = ".\\OBJFiles\\12140_Skull_v3_L2.obj";
			nomfitxer = nom.c_str();	// Conversiï¿½ tipus string --> char *

			// Conversiï¿½ std::string --> char *
			nomfitx = new char[nom.length() + 1];
			strcpy(nomfitx, nom.c_str());

			if (ObOBJ == NULL) ObOBJ = new COBJModel;
			if (vao_OBJ.vaoId != 0) deleteVAOList(FIT_OBJ); // Eliminar VAO anterior.
			vao_OBJ = ObOBJ->LoadModel(nomfitx, FIT_OBJ);	// Carregar objecte OBJ AMB textura

		//	Pas de parï¿½metres textura al shader
			if (shader_menu != CAP_SHADER) glUniform1i(glGetUniformLocation(shader_programID, "textur"), textura);
			if (shader_menu != CAP_SHADER) glUniform1i(glGetUniformLocation(shader_programID, "flag_invert_y"), tFlag_invert_Y);
			break;

		// Tecla Obrir Fitxer 3DS
		case GLFW_KEY_F3:
			objecte = OBJ3DS;	textura = true;

			// Entorn VGI: Obrir diï¿½leg de lectura de fitxer (fitxers (*.OBJ)
			nom = ".\\3DSFiles\\mortonjpg.3ds";
			nomfitxer = nom.c_str();	// Conversiï¿½ tipus string --> char *

			// Conversiï¿½ std::string --> char *
			nomfitx = new char[nom.length() + 1];
			strcpy(nomfitx, nom.c_str());

/* Funcions lectura fitxer 3DS (Load3DS i OBJ3DS)
//			if (Ob3DS == NULL) Ob3DS = new Obj_3DS;
			Ob3DS->EliminarMemoria();
			Ob3DS->Inicialitzar();
			Ob3DS->Carregar3DS(nomfitx);

// Precompilaciï¿½ de dos objectes nous: OBJECTE3DS: Objecte 3DS sense textures i OBJECTE3DST amb textures,
			if (vao_3DS.vaoId != 0) deleteVAOList(FIT_3DS); // Eliminar VAO anterior.
			vao_3DS = Ob3DS->Dibuixa3DS(false, FIT_3DS);

//	Pas de parï¿½metres textura al shader
			if (shader_menu != CAP_SHADER) glUniform1i(glGetUniformLocation(shader_programID, "textur"), textura);
			if (shader_menu != CAP_SHADER) glUniform1i(glGetUniformLocation(shader_programID, "flag_invert_y"), tFlag_invert_Y);
*/

//  Entorn VGI: Modificar R per centrar Vista amb mida de l'objecte
			mida = sqrt(3.0) * 10.0;
			OPV.R = 0.5 * mida / sin(30.0 * PI / 180.0) + p_near;
			break;

// ----------- POP UP Finestra
		// Tecla Obrir nova finestra
		case GLFW_KEY_W:
			camera = CAM_PLAY;
			break;

// ----------- POP UP Vista
		// Tecla Full Screen?
		case GLFW_KEY_F:
			OnFull_Screen(primary, window);
			break;

		// Tecla Mobil?
		case GLFW_KEY_M:
			if ((projeccio != ORTO) && (projeccio != CAP)) mobil = !mobil;
			// Desactivaciï¿½ de Transformacions Geomï¿½triques via mouse 
			//		si Visualitzaciï¿½ Interactiva activada.	
			if (mobil) {	transX = false;	transY = false; transZ = false;
						}
			break;

		// Tecla Zoom
		case GLFW_KEY_Q:
			if ((projeccio != ORTO) && (projeccio != CAP)) zzoom = !zzoom;
			// Desactivaciï¿½ de Transformacions Geomï¿½triques via mouse 
			//		si Zoom activat.
			if (zzoom) {	transX = false;	transY = false;	transZ = false;
						}
			break;

		// Tecla Satï¿½l.lit?
		case GLFW_KEY_S:
			if ((projeccio != CAP && projeccio != ORTO)) satelit = !satelit;
			if (satelit) mobil = true;
			testA = anima;									// Testejar si hi ha alguna animaciï¿½ activa apart de Satï¿½lit.
	//		if ((!satelit) && (!testA)) KillTimer(WM_TIMER);	// Si es desactiva Satï¿½lit i no hi ha cap animaciï¿½ activa es desactiva el Timer.
			break;

		// Tecla Polars Eix X?
		case GLFW_KEY_X:
			if ((projeccio != CAP) && (camera != CAM_NAVEGA)) Vis_Polar = POLARX;
			break;

		// Tecla Polars Eix Y?
		case GLFW_KEY_Y:
			if ((projeccio != CAP) && (camera != CAM_NAVEGA)) Vis_Polar = POLARY;
			break;

		// Tecla Polars Eix Z?
		case GLFW_KEY_Z:
			if ((projeccio != CAP) && (camera != CAM_NAVEGA)) Vis_Polar = POLARZ;
			break;

		// Tecla Pan?
		case GLFW_KEY_G:
			if ((projeccio != ORTO) && (projeccio != CAP)) pan = !pan;
			// Desactivaciï¿½ de Transformacions Geomï¿½triques via mouse i navega si pan activat
			if (pan) {	mobil = true;		zzoom = true;
						transX = false;		transY = false;	transZ = false;
					}
			break;

		// Tecla Navega?
		case GLFW_KEY_N:
			if (projeccio != ORTO) camera = CAM_NAVEGA;
			// Desactivaciï¿½ de zoom, mobil, Transformacions Geomï¿½triques via mouse i pan 
			//		si navega activat
			if (camera == CAM_NAVEGA)
			{	mobil = false;	zzoom = false;
				transX = false;	transY = false;	transZ = false;
				pan = false;
				tr_cpv.x = 0.0;		tr_cpv.y = 0.0;		tr_cpv.z = 0.0;	// Inicialitzar a 0 desplaï¿½ament de pantalla
				tr_cpvF.x = 0.0;	tr_cpvF.y = 0.0;	tr_cpvF.x = 0.0; // Inicialitzar a 0 desplaï¿½ament de pantalla
			}
			else {	mobil = true;
					zzoom = true;
				}
			break;

		// Tecla Escape (per a Pan i Navega)
		case GLFW_KEY_ESCAPE:
			if (pan) {	fact_pan = 1;
						tr_cpv.x = 0;	tr_cpv.y = 0;	tr_cpv.z = 0;
					}
			else 	if (camera == CAM_NAVEGA) {	n[0] = 0.0;		n[1] = 0.0;		n[2] = 0.0;
									opvN.x = 10.0;	opvN.y = 0.0;		opvN.z = 0.0;
									angleZ = 0.0;
								}
			break;

		// Tecla Eixos?
		case GLFW_KEY_F4:
			eixos = !eixos;
			break;

		// Tecla Grid XY?
		case GLFW_KEY_F5:
			grid.x = !grid.x;	hgrid.x = 0.0;
			if (grid.x) grid.w = false;
			break;

		// Tecla Grid XZ?
		case GLFW_KEY_F6:
			grid.y = !grid.y;	hgrid.y = 0.0;
			if (grid.y) grid.w = false;
			break;

		// Tecla Grid YZ?
		case GLFW_KEY_F7:
			grid.z = !grid.z;	hgrid.z = 0.0;
			if (grid.z) grid.w = false;
			break;

		// Tecla Grid XYZ?
		case GLFW_KEY_F8:
			grid.w = !grid.w;	hgrid.w = 0.0;
			if (grid.w)
				{	grid.x = false;	grid.y = false;		grid.z = false;
				}
			break;

		// Tecla Skybox Cube
		case GLFW_KEY_K:
			SkyBoxCube = !SkyBoxCube;
			if (SkyBoxCube)
			{	Vis_Polar = POLARY;
				// Cï¿½rrega VAO Skybox Cube
				if (skC_VAOID.vaoId == 0) skC_VAOID = loadCubeSkybox_VAO();
				
				if (!cubemapTexture)
					{	// load Skybox textures
						// -------------
						std::vector<std::string> faces =
							{	".\\textures\\skybox\\final\\left.png", //girado
								".\\textures\\skybox\\final\\right.png", //girado
								".\\textures\\skybox\\final\\top.png",
								".\\textures\\skybox\\final\\bottom.png",
								".\\textures\\skybox\\final\\front.png",
								".\\textures\\skybox\\final\\back.png"
							};
						cubemapTexture = loadCubemap(faces);	
					}
			}
			break;

// ----------- POP UP Projecciï¿½
		// Tecla Axonomï¿½trica
		case GLFW_KEY_A:
			projeccio = AXONOM;
			mobil = true;
			zzoom = true;
			break;

		// Tecla Ortogrï¿½fica
		case GLFW_KEY_O:
			projeccio = ORTO;
			mobil = false;			zzoom = false;
			break;

		// Tecla Perspectiva
		case GLFW_KEY_P:
			projeccio = PERSPECT;
			mobil = true;			zzoom = true;
			break;

// ----------- POP UP Objecte
		// Tecla Cub
		case GLFW_KEY_C:
			objecte = CUB;
			//  Modificar R per centrar la Vista a la mida de l'objecte (Perspectiva)
			//	Canviar l'escala per a centrar la vista (Ortogrï¿½fica)
			netejaVAOList();											// Neteja Llista VAO.

// Posar color objecte (col_obj) al vector de colors del VAO.
			SetColor4d(col_obj.r, col_obj.g, col_obj.b, col_obj.a);

			//if (Get_VAOId(GLUT_CUBE) != 0) deleteVAOList(GLUT_CUBE);	// Neteja VAO Cub
			//Set_VAOList(GLUT_CUBE, loadglutSolidCube_VAO(1.0));	// Genera VAO de cub mida 1 i el guarda a la posiciï¿½ GLUT_CUBE.
			Set_VAOList(GLUT_CUBE, loadglutSolidCube_EBO(1.0));		// Genera EBO de cub mida 1 i el guarda a la posiciï¿½ GLUT_CUBE.
			break;

			// Tecla Cub
		case GLFW_KEY_L:
			objecte = CUB_REVERS;
			//  Modificar R per centrar la Vista a la mida de l'objecte (Perspectiva)
			//	Canviar l'escala per a centrar la vista (Ortogrï¿½fica)
			netejaVAOList();											// Neteja Llista VAO.

			// Posar color objecte (col_obj) al vector de colors del VAO.
			SetColor4d(col_obj.r, col_obj.g, col_obj.b, col_obj.a);

			//if (Get_VAOId(GLUT_CUBE) != 0) deleteVAOList(GLUT_CUBE);	// Neteja VAO Cub
			//Set_VAOList(GLUT_CUBE, loadglutSolidCube_VAO(1.0));	// Genera EBO de cub mida 1 i el guarda a la posició GLUT_CUBE.
			Set_VAOList(GLUT_USER7, loadglutSolidCubeRevers_EBO(1.0));		// Genera EBO de cub mida 1 i el guarda a la posiciï¿½ GLUT_CUBE.
			Set_VAOList(GLUT_CUBE, loadglutSolidCube_EBO(1.0));		// Genera EBO de cub mida 1 i el guarda a la posició GLUT_CUBE.
			break;

		// Tecla Cub RGB
		case GLFW_KEY_D:
			objecte = CUB_RGB;
			//  Modificar R per centrar la Vista a la mida de l'objecte (Perspectiva)
			//	Canviar l'escala per a centrar la vista (Ortogrï¿½fica)
			netejaVAOList();						// Neteja Llista VAO.

			//if (Get_VAOId(GLUT_CUBE_RGB) != 0) deleteVAOList(GLUT_CUBE_RGB);
			//Set_VAOList(GLUT_CUBE_RGB, loadglutSolidCubeRGB_VAO(1.0));	// Genera VAO de cub mida 1 i el guarda a la posiciï¿½ GLUT_CUBE_RGB.
			Set_VAOList(GLUT_CUBE_RGB, loadglutSolidCubeRGB_EBO(1.0));	// Genera EBO de cub mida 1 i el guarda a la posiciï¿½ GLUT_CUBE_RGB.
			break;

		// Tecla Esfera
		case GLFW_KEY_E:
			objecte = ESFERA;
			//  Modificar R per centrar la Vista a la mida de l'objecte (Perspectiva)
			//	Canviar l'escala per a centrar la vista (Ortogrï¿½fica)
			netejaVAOList();						// Neteja Llista VAO.

			// Posar color objecte (col_obj) al vector de colors del VAO.
			SetColor4d(col_obj.r, col_obj.g, col_obj.b, col_obj.a);

			//if (Get_VAOId(GLU_SPHERE) != 0) deleteVAOList(GLU_SPHERE);
			//Set_VAOList(GLU_SPHERE, loadgluSphere_VAO(1.0, 30,30)); // // Genera VAO d'esfera radi 1 i el guarda a la posiciï¿½ GLUT_CUBE_RGB.
			Set_VAOList(GLU_SPHERE, loadgluSphere_EBO(1.0, 30, 30));
			break;

		// Tecla Tetera
		case GLFW_KEY_T:
			objecte = TETERA;
			//  Modificar R per centrar la Vista a la mida de l'objecte (Perspectiva)
			//	Canviar l'escala per a centrar la vista (Ortogrï¿½fica)
			netejaVAOList();						// Neteja Llista VAO.

			// Posar color objecte (col_obj) al vector de colors del VAO.
			SetColor4d(col_obj.r, col_obj.g, col_obj.b, col_obj.a);

			//if (Get_VAOId(GLUT_TEAPOT) != 0) deleteVAOList(GLUT_TEAPOT);
			Set_VAOList(GLUT_TEAPOT, loadglutSolidTeapot_VAO()); //Genera VAO tetera mida 1 i el guarda a la posiciï¿½ GLUT_TEAPOT.
			break;

		// Tecla Arc
		case GLFW_KEY_R:
			objecte = ARC;
			//  Modificar R per centrar la Vista a la mida de l'objecte (Perspectiva)
			//	Canviar l'escala per a centrar la vista (Ortogrï¿½fica)

			color_Mar.r = 0.5;	color_Mar.g = 0.4; color_Mar.b = 0.9; color_Mar.a = 1.0;
			// TODO: Agregue aquï¿½ su cï¿½digo de controlador de comandos
			objecte = ARC;

			//  Modificar R per centrar la Vista a la mida de l'objecte (Perspectiva)
			//	Canviar l'escala per a centrar la vista (Ortogrï¿½fica)

			// Cï¿½rrega dels VAO's per a construir objecte ARC
			netejaVAOList();						// Neteja Llista VAO.

			// Posar color objecte (col_obj) al vector de colors del VAO.
			SetColor4d(col_obj.r, col_obj.g, col_obj.b, col_obj.a);

			//if (Get_VAOId(GLUT_CUBE) != 0) deleteVAOList(GLUT_CUBE);
			Set_VAOList(GLUT_CUBE, loadglutSolidCube_EBO(1.0));		// Cï¿½rrega Cub de costat 1 com a EBO a la posiciï¿½ GLUT_CUBE.

			//if (Get_VAOId(GLU_SPHERE) != 0) deleteVAOList(GLU_SPHERE);
			Set_VAOList(GLU_SPHERE, loadgluSphere_EBO(0.5, 20, 20));	// Cï¿½rrega Esfera a la posiciï¿½ GLU_SPHERE.

			//if (Get_VAOId(GLUT_TEAPOT) != 0) deleteVAOList(GLUT_TEAPOT);
			Set_VAOList(GLUT_TEAPOT, loadglutSolidTeapot_VAO());		// Carrega Tetera a la posiciï¿½ GLUT_TEAPOT.

			//if (Get_VAOId(MAR_FRACTAL_VAO) != 0) deleteVAOList(MAR_FRACTAL_VAO);
			Set_VAOList(MAR_FRACTAL_VAO, loadSea_VAO(color_Mar));		// Carrega Mar a la posiciï¿½ MAR_FRACTAL_VAO.


			break;

		// Tecla Tie (Star Wars)
		case GLFW_KEY_I:
			objecte = TIE;		textura = true;

			// Cï¿½rrega dels VAO's per a construir objecte TIE
			netejaVAOList();						// Neteja Llista VAO.

			// Posar color objecte (col_obj) al vector de colors del VAO.
			SetColor4d(col_obj.r, col_obj.g, col_obj.b, col_obj.a);

			//if (Get_VAOId(GLU_CYLINDER) != 0) deleteVAOList(GLU_CYLINDER);
			Set_VAOList(GLUT_CYLINDER, loadgluCylinder_EBO(5.0f, 5.0f, 0.5f, 6, 1));// Cï¿½rrega cilindre com a VAO.

			//if (Get_VAOId(GLU_DISK) != 0)deleteVAOList(GLU_DISK);
			Set_VAOList(GLU_DISK, loadgluDisk_EBO(0.0f, 5.0f, 6, 1));	// Cï¿½rrega disc com a VAO

			//if (Get_VAOId(GLU_SPHERE) != 0)deleteVAOList(GLU_SPHERE);
			Set_VAOList(GLU_SPHERE, loadgluSphere_EBO(10.0f, 80, 80));	// Cï¿½rrega disc com a VAO

			//if (Get_VAOId(GLUT_USER1) != 0)deleteVAOList(GLUT_USER1);
			Set_VAOList(GLUT_USER1, loadgluCylinder_EBO(5.0f, 5.0f, 2.0f, 6, 1)); // Cï¿½rrega cilindre com a VAO

			//if (Get_VAOId(GLUT_CUBE) != 0)deleteVAOList(GLUT_CUBE);
			Set_VAOList(GLUT_CUBE, loadglutSolidCube_EBO(1.0));			// Cï¿½rrega cub com a EBO

			//if (Get_VAOId(GLUT_TORUS) != 0)deleteVAOList(GLUT_TORUS);
			Set_VAOList(GLUT_TORUS, loadglutSolidTorus_EBO(1.0, 5.0, 20, 20));

			//if (Get_VAOId(GLUT_USER2) != 0)deleteVAOList(GLUT_USER2);	
			Set_VAOList(GLUT_USER2, loadgluCylinder_EBO(1.0f, 0.5f, 5.0f, 60, 1)); // Cï¿½rrega cilindre com a VAO

			//if (Get_VAOId(GLUT_USER3) != 0)deleteVAOList(GLUT_USER3);
			Set_VAOList(GLUT_USER3, loadgluCylinder_EBO(0.35f, 0.35f, 5.0f, 80, 1)); // Cï¿½rrega cilindre com a VAO

			//if (Get_VAOId(GLUT_USER4) != 0)deleteVAOList(GLUT_USER4);
			Set_VAOList(GLUT_USER4, loadgluCylinder_EBO(4.0f, 2.0f, 10.25f, 40, 1)); // Cï¿½rrega cilindre com a VAO

			//if (Get_VAOId(GLUT_USER5) != 0) deleteVAOList(GLUT_USER5);
			Set_VAOList(GLUT_USER5, loadgluCylinder_EBO(1.5f, 4.5f, 2.0f, 8, 1)); // Cï¿½rrega cilindre com a VAO

			//if (Get_VAOId(GLUT_USER6) != 0) deleteVAOList(GLUT_USER6);
			Set_VAOList(GLUT_USER6, loadgluDisk_EBO(0.0f, 1.5f, 8, 1)); // Cï¿½rrega disk com a VAO
			break;

		// Tecla Corbes Bezier
		case GLFW_KEY_F9:
			nom = "";
			objecte = C_BEZIER;

			// Entorn VGI: Obrir diï¿½leg de lectura de fitxer (fitxers (*.crv)
			nom = ".\\Corbes\\Corba9-Hidro.crv";
			nomfitxer = nom.c_str();	// Conversiï¿½ tipus string --> char *

			npts_T = llegir_ptsC(nomfitxer);
			break;

		// Tecla Corbes B-Spline
		case GLFW_KEY_F10:
			nom = "";
			objecte = C_BSPLINE;

			// Entorn VGI: Obrir diï¿½leg de lectura de fitxer (fitxers (*.crv)
			nom = ".\\Corbes\\Corba9-Hidro.crv";
			nomfitxer = nom.c_str();	// Conversiï¿½ tipus string --> char *

			npts_T = llegir_ptsC(nomfitxer);
			break;

		// Tecla Corbes Lemniscata
		case GLFW_KEY_F11:
			objecte = C_LEMNISCATA;

			// 	---- Entorn VGI: Modificar R per centrar Vista amb mida de l'objecte

			break;

		// Tecla Punts de Control?
		case GLFW_KEY_F12:
			sw_Punts_Control = !sw_Punts_Control;
			break;

		// Tecla Matriu Primitives
		case GLFW_KEY_H:
			objecte = MATRIUP;
			break;

		// Tecla Matriu Primitives VAO
		case GLFW_KEY_V:
			objecte = MATRIUP_VAO;
			break;

		default:
			break;
		}
}


// Teclat_Ctrl: Shortcuts per Pop Ups Transforma, Iluminaciï¿½, llums, Shaders
void Teclat_Ctrl(int key)
{
	const char* nomfitxer;
	std::string nomVert, nomFrag;	// Nom de fitxer.

	switch (key)
	{
// ----------- POP UP TRANSFORMA
	// Tecla Transforma --> Traslaciï¿½?
	case GLFW_KEY_T:
		trasl = !trasl;
		rota = false;
		if (trasl) escal = true;
		transf = trasl || rota || escal;
		break;

	// Tecla Transforma --> Rotaciï¿½?
	case GLFW_KEY_R:
		rota = !rota;
		trasl = false;
		if (rota) escal = true;
		transf = trasl || rota || escal;
		break;

	// Tecla Transforma --> Escalat?
	case GLFW_KEY_S:
		if ((!rota) && (!trasl)) escal = !escal;
		transf = trasl || rota || escal;
		break;

	// Tecla Escape (per a Transforma --> Origen Traslaciï¿½, Transforma --> Origen Rotaciï¿½ i Transforma --> Origen Escalat)
	case GLFW_KEY_ESCAPE:
		if (trasl)
		{	fact_Tras = 1;
			TG.VTras.x = 0.0;	TG.VTras.y = 0.0;	TG.VTras.z = 0;
		}
		else if (rota)	{	fact_Rota = 90;
							TG.VRota.x = 0;		TG.VRota.y = 0;		TG.VRota.z = 0;
						}
			else if (escal) { TG.VScal.x = 1;	TG.VScal.y = 1;	TG.VScal.z = 1; }
		break;

	// Tecla Transforma --> Mobil Eix X? (opciï¿½ booleana).
	case GLFW_KEY_X:
		if (transf)
		{	transX = !transX;
			if (transX) {
				mobil = false;	zzoom = false;
				pan = false;
			}
			else if ((!transY) && (!transZ)) {
				mobil = true;
				zzoom = true;
			}
		}
		break;

	// Tecla Transforma --> Mobil Eix Y? (opciï¿½ booleana).
	case GLFW_KEY_Y:
		if (transf)
		{	transY = !transY;
			if (transY) {
				mobil = false;	zzoom = false;
				pan = false;
			}
			else if ((!transX) && (!transZ)) {
				mobil = true;
				zzoom = true;
			}
		}
		break;

	// Tecla Transforma --> Mobil Eix Z? (opciï¿½ booleana).
	case GLFW_KEY_Z:
		if (transf)
		{	transZ = !transZ;
			if (transZ) {
				mobil = false;	zzoom = false;
				pan = false;
			}
			else if ((!transX) && (!transY)) {
				mobil = true;
				zzoom = true;
			}
		}
		break;

// ----------- POP UP OCULTACIONS
	// Tecla Ocultacions --> Front faces? (opciï¿½ booleana).
	case GLFW_KEY_D:
		front_faces = !front_faces;
		break;

	// Tecla Ocultacions --> Test Visibilitat? (back face culling)
	case GLFW_KEY_C:
		test_vis = !test_vis;
		break;

	// Tecla Ocultacions --> Z-Buffer? (opciï¿½ booleana).
	case GLFW_KEY_O:
		oculta = !oculta;
		break;

	// Tecla Ocultacions --> Back-lines? (opciï¿½ booleana).
	case GLFW_KEY_B:
		back_line = !back_line;
		break;

// ----------- POP UP ILUMINACIï¿½
	// Tecla Llum Fixe? (opciï¿½ booleana).
	case GLFW_KEY_F:
		ifixe = !ifixe;
		break;

	// Tecla Iluminaciï¿½ --> Punts
	case GLFW_KEY_F1:
		ilumina = PUNTS;
		test_vis = false;		oculta = false;
		break;

	// Tecla Iluminaciï¿½ --> Filferros
	case GLFW_KEY_F2:
		ilumina = FILFERROS;
		test_vis = false;		oculta = false;
		break;

	// Tecla Iluminaciï¿½ --> Plana
	case GLFW_KEY_F3:
		ilumina = PLANA;
		test_vis = false;		oculta = true;
		break;

	// Tecla Iluminaciï¿½ --> Gouraud
	case GLFW_KEY_F4:
		ilumina = GOURAUD;
		test_vis = false;		oculta = true;
		break;

	// Tecla Iluminaciï¿½ --> Reflexiï¿½ Material --> Emissiï¿½?
	case GLFW_KEY_F5:
		sw_material[0] = !sw_material[0];
		//glUniform1i(glGetUniformLocation(shader_programID, "sw_intensity[0]"), sw_material[0]); // Pas mï¿½scara llums al shader
		break;

	// Tecla Iluminaciï¿½ --> Reflexiï¿½ Material -> Ambient?
	case GLFW_KEY_F6:
		sw_material[1] = !sw_material[1];
		//glUniform1i(glGetUniformLocation(shader_programID, "sw_intensity[1]"), sw_material[1]); // Pas mï¿½scara llums al shader
		break;

	// Tecla Iluminaciï¿½ --> Reflexiï¿½ Material -> Difusa?
	case GLFW_KEY_F7:
		sw_material[2] = !sw_material[2];
		//glUniform1i(glGetUniformLocation(shader_programID, "sw_intensity[2]"), sw_material[2]); // Pas mï¿½scara llums al shader
		break;

	// Tecla Iluminaciï¿½ --> Reflexiï¿½ Material -> Especular?
	case GLFW_KEY_F8:
		sw_material[3] = !sw_material[3];
		//glUniform1i(glGetUniformLocation(shader_programID, "sw_intensity[3]"), sw_material[3]); // Pas mï¿½scara llums al shader
		break;

	// Tecla Iluminaciï¿½ --> Textura?.
	case GLFW_KEY_I:
		textura = !textura;
		glUniform1i(glGetUniformLocation(shader_programID, "texture"), textura); //	Pas de textura al shader
		break;

	// Tecla Iluminaciï¿½ --> Fitxer Textura?
	case GLFW_KEY_J:
		t_textura = FITXERIMA;
		// Obrir diï¿½leg de lectura de fitxer
		nom = ".\\textures\\brick.jpg";
		nomfitxer = nom.c_str();	// Conversiï¿½ tipus string --> char *
		texturesID[0] = loadIMA_SOIL(nomfitxer);
		break;


// ----------- POP UP Llums
	// Tecla Llums --> Llum Ambient?.
	case GLFW_KEY_A:
		llum_ambient = !llum_ambient;
		sw_il = true;
		if (shader_menu != CAP_SHADER) glUniform1i(glGetUniformLocation(shader_programID, "sw_intensity[1]"), (llum_ambient && sw_material[1])); // Pas mï¿½scara llums al shader
		break;

	// Tecla Llums --> Llum #0? (+Z)
	case GLFW_KEY_0:
		llumGL[0].encesa = !llumGL[0].encesa;
		sw_il = true;
		if (shader_menu != CAP_SHADER) glUniform1i(glGetUniformLocation(shader_programID, "sw_lights[0]"), llumGL[0].encesa); // Pas mï¿½scara Llum #0 al shader
		break;

	// Tecla Llums --> Llum #1? (+X)
	case GLFW_KEY_1:
		llumGL[1].encesa = !llumGL[1].encesa;
		sw_il = true;
		if (shader_menu != CAP_SHADER) glUniform1i(glGetUniformLocation(shader_programID, "sw_lights[1]"), llumGL[1].encesa);
		break;

	// Tecla Llums --> Llum #2? (+Y)
	case GLFW_KEY_2:
		llumGL[2].encesa = !llumGL[2].encesa;
		sw_il = true;
		if (shader_menu != CAP_SHADER) glUniform1i(glGetUniformLocation(shader_programID, "sw_lights[2]"), llumGL[2].encesa);
		break;

	// Tecla Llums --> Llum #3? (Z=Y=X)
	case GLFW_KEY_3:
		llumGL[3].encesa = !llumGL[3].encesa;
		sw_il = true;

		if (shader_menu != CAP_SHADER) glUniform1i(glGetUniformLocation(shader_programID, "sw_lights[3]"), llumGL[3].encesa);
		break;

	// Tecla Llums --> Llum #4? (-Z)
	case GLFW_KEY_4:
		llumGL[4].encesa = !llumGL[4].encesa;
		sw_il = true;
		if (shader_menu != CAP_SHADER) glUniform1i(glGetUniformLocation(shader_programID, "sw_lights[4]"), llumGL[4].encesa);
		break;

// ----------- POP UP SHADERS
	// Tecla Shaders --> Sense
//	case GLFW_KEY_F9:
//		shader_menu = CAP_SHADER;
//		releaseAllShaders();
//		break;

	// Tecla Shaders --> Gouraud (shader)
	case GLFW_KEY_F10:
		// Cï¿½rrega Shader de Gouraud
		sw_shader = true;				shader_menu = GOURAUD_SHADER;	shader_programID = 0;
		//shaderGouraud.loadFileShaders(".\\shaders\\gouraud_shdrML.vert", ".\\shaders\\gouraud_shdrML.frag");
		fprintf(stderr, "Gouraud_shdrML: \n");
		shader_programID = shaderGouraud.initializeShaders(".\\shaders\\gouraud_shdrML");
		//shader_programID = shaderGouraud.getProgramID();
		shaderGouraud.Use();
		glUseProgram(shader_programID);
		break;

	// Tecla Shaders --> Phong (shader)
	case GLFW_KEY_F11:
		// Cï¿½rrega Shader de Phong
		sw_shader = true;				shader_menu = PHONG_SHADER;	shader_programID = 0;
		//shaderGouraud.loadFileShaders(".\\shaders\\gouraud_shdrML.vert", ".\\shaders\\gouraud_shdrML.frag");
		fprintf(stderr, "Phong_shdrML: \n");
		shader_programID = shaderPhong.initializeShaders(".\\shaders\\phong_shdrML");
		//shader_programID = shaderGouraud.getProgramID();
		//shader_programID = initializeShaders(".\\shaders\\gouraud_shdrML");
		shaderPhong.Use();
		//glUseProgram(shader_programID);
		break;

	// Tecla Shaders --> Fitxers Shaders
	case GLFW_KEY_F12:
		// Cï¿½rrega Shader de Gouraud
		sw_shader = true;				shader_menu = FILE_SHADER;	shader_programID = 0;
		// Cï¿½rrega fitxer VERT
		// Entorn VGI: Obrir diï¿½leg de lectura de fitxer (fitxers (*.VERT)
		//nomVert = openVert.GetPathName();
		// Cï¿½rrega fitxer FRAG
		// Entorn VGI: Obrir diï¿½leg de lectura de fitxer (fitxers (*.FRAG)
		//nomFrag = openFrag.GetPathName();
		fprintf(stderr, "File Shader: \n");
		shader_programID = shaderGouraud.loadFileShaders(".\\shaders\\gouraud_shdrML.vert", ".\\shaders\\gouraud_shdrML.frag");
		//shader_programID = shaderGouraud.getProgramID();
		shaderFiles.Use();
		break;

	default:
		break;
	}
}

// Teclat_ColorObjecte: Teclat pels canvis de color de l'objecte per teclat.
void Teclat_ColorObjecte(int key, int action)
{
	const double incr = 0.025f;

	if (action == GLFW_PRESS)
	{
		// FRACTAL: Canvi resoluciï¿½ del fractal pe tecles '+' i'-'
		if (objecte == O_FRACTAL)
		{
			if (key == GLFW_KEY_KP_SUBTRACT) // Carï¿½cter '-' (ASCII 109)
			{
				pas = pas * 2;
				if (pas > 64) pas = 64;
				sw_il = true;
			}
			else if (key == GLFW_KEY_KP_ADD) // Carï¿½cter '+' (ASCII 107)
			{
				pas = pas / 2;
				if (pas < 1) pas = 1;
				sw_il = true;
			}
		}
		//	else 
		if (key == GLFW_KEY_DOWN) // Carï¿½cter VK_DOWN
		{
			if (fonsR) {
				col_obj.r -= incr;
				if (col_obj.r < 0.0) col_obj.r = 0.0;
			}
			if (fonsG) {
				col_obj.g -= incr;
				if (col_obj.g < 0.0) col_obj.g = 0.0;
			}
			if (fonsB) {
				col_obj.b -= incr;
				if (col_obj.b < 0.0) col_obj.b = 0.0;
			}
		}
		else if (key == GLFW_KEY_UP)
		{
			if (fonsR) {
				col_obj.r += incr;
				if (col_obj.r > 1.0) col_obj.r = 1.0;
			}
			if (fonsG) {
				col_obj.g += incr;
				if (col_obj.g > 1.0) col_obj.g = 1.0;
			}
			if (fonsB) {
				col_obj.b += incr;
				if (col_obj.b > 1.0) col_obj.b = 1.0;
			}
		}
		else if (key == GLFW_KEY_SPACE)
		{
			if ((fonsR) && (fonsG) && (fonsB)) {
				fonsG = false;
				fonsB = false;
			}
			else if ((fonsR) && (fonsG)) {
				fonsG = false;
				fonsB = true;
			}
			else if ((fonsR) && (fonsB)) {
				fonsR = false;
				fonsG = true;
			}
			else if ((fonsG) && (fonsB)) fonsR = true;
			else if (fonsR) {
				fonsR = false;
				fonsG = true;
			}
			else if (fonsG) {
				fonsG = false;
				fonsB = true;
			}
			else if (fonsB) {
				fonsR = true;
				fonsG = true;
				fonsB = false;
			}
		}
		else if (key == GLFW_KEY_O) sw_color = true;
		else if (key == GLFW_KEY_F) sw_color = false;
	}
}


// Teclat_ColorFons: Teclat pels canvis del color de fons.
void Teclat_ColorFons(int key, int action)
{		const double incr = 0.025f;

		if (action == GLFW_PRESS)
		{
			// FRACTAL: Canvi resoluciï¿½ del fractal pe tecles '+' i'-'
			if (objecte == O_FRACTAL)
			{
				if (key == GLFW_KEY_KP_SUBTRACT) // Carï¿½cter '-' - (ASCII:109)
				{
					pas = pas * 2;
					if (pas > 64) pas = 64;
					sw_il = true;
				}
				else if (key == GLFW_KEY_KP_ADD) // Carï¿½cter '+' - (ASCII:107)
				{
					pas = pas / 2;
					if (pas < 1) pas = 1;
					sw_il = true;
				}
			}
			//	else 
			if (key == GLFW_KEY_DOWN) {
				if (fonsR) {
					c_fons.r -= incr;
					if (c_fons.r < 0.0) c_fons.r = 0.0;
				}
				if (fonsG) {
					c_fons.g -= incr;
					if (c_fons.g < 0.0) c_fons.g = 0.0;
				}
				if (fonsB) {
					c_fons.b -= incr;
					if (c_fons.b < 0.0) c_fons.b = 0.0;
				}
			}
			else if (key == GLFW_KEY_UP) {
				if (fonsR) {
					c_fons.r +=  incr;
					if (c_fons.r > 1.0) c_fons.r = 1.0;
				}
				if (fonsG) {
					c_fons.g += incr;
					if (c_fons.g > 1.0) c_fons.g = 1.0;
				}
				if (fonsB) {
					c_fons.b += incr;
					if (c_fons.b > 1.0) c_fons.b = 1.0;
				}
			}
			else if (key == GLFW_KEY_SPACE) {
				if ((fonsR) && (fonsG) && (fonsB)) {
					fonsG = false;
					fonsB = false;
				}
				else if ((fonsR) && (fonsG)) {
					fonsG = false;
					fonsB = true;
				}
				else if ((fonsR) && (fonsB)) {
					fonsR = false;
					fonsG = true;
				}
				else if ((fonsG) && (fonsB)) fonsR = true;
				else if (fonsR) {
					fonsR = false;
					fonsG = true;
				}
				else if (fonsG) {
					fonsG = false;
					fonsB = true;
				}
				else if (fonsB) {
					fonsR = true;
					fonsG = true;
					fonsB = false;
				}
			}
			else if (key == GLFW_KEY_O) sw_color = true;
			else if (key == GLFW_KEY_F) sw_color = false;
		}
}

// Teclat_Navega: Teclat pels moviments de navegaciï¿½.
void Teclat_Navega(int key, int action)
{
	GLdouble vdir[3] = { 0, 0, 0 };
	double modul = 0;

	opvN.z = 1.7f;

	// Entorn VGI: Controls de moviment de navegació
	vdir[0] = n[0] - opvN.x;
	vdir[1] = n[1] - opvN.y;
	vdir[2] = n[2] - opvN.z;
	modul = sqrt(vdir[0] * vdir[0] + vdir[1] * vdir[1] + vdir[2] * vdir[2]);
	vdir[0] = vdir[0] / modul;
	vdir[1] = vdir[1] / modul;
	vdir[2] = vdir[2] / modul;
	
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		// Tecla cursor amunt
		case GLFW_KEY_W:
			opvN.x += fact_pan * vdir[0];
			opvN.y += fact_pan * vdir[1];
			n[0] += fact_pan * vdir[0];
			n[1] += fact_pan * vdir[1];
			break;

		// Tecla cursor avall
		case GLFW_KEY_S:
			opvN.x -= fact_pan * vdir[0];
			opvN.y -= fact_pan * vdir[1];
			n[0] -= fact_pan * vdir[0];
			n[1] -= fact_pan * vdir[1];
			break;

		// Tecla cursor esquerra
		case GLFW_KEY_D:
			angleZ += fact_pan;
			n[0] = n[0] - opvN.x;
			n[1] = n[1] - opvN.y;
			n[0] = n[0] * cos(angleZ * PI / 180) - n[1] * sin(angleZ * PI / 180);
			n[1] = n[0] * sin(angleZ * PI / 180) + n[1] * cos(angleZ * PI / 180);
			n[0] = n[0] + opvN.x;
			n[1] = n[1] + opvN.y;
			break;

		// Tecla cursor dret
		case GLFW_KEY_A:
			angleZ = 360 - fact_pan;
			n[0] = n[0] - opvN.x;
			n[1] = n[1] - opvN.y;
			n[0] = n[0] * cos(angleZ * PI / 180) - n[1] * sin(angleZ * PI / 180);
			n[1] = n[0] * sin(angleZ * PI / 180) + n[1] * cos(angleZ * PI / 180);
			n[0] = n[0] + opvN.x;
			n[1] = n[1] + opvN.y;
			break;

		// Tecla Inicio
		case GLFW_KEY_HOME:
			opvN.z += fact_pan;
			n[2] += fact_pan;
			break;

		// Tecla Fin
		case GLFW_KEY_END:
			opvN.z -= fact_pan;
			n[2] -= fact_pan;
			break;

		// Tecla PgUp
		case GLFW_KEY_PAGE_UP:
			fact_pan /= 2;
			if (fact_pan < 1) fact_pan = 1;
			break;

		// Tecla PgDown
		case GLFW_KEY_PAGE_DOWN:
			fact_pan *= 2;
			if (fact_pan > 2048) fact_pan = 2048;
			break;

		default:
			break;
		}
	}
}

void Teclat_Play(int key, int action)
{
	if (action != GLFW_PRESS)
		return;

	GLdouble vdir[3] = { 0, 0, 0 };
	double modul = 0;

	// Entorn VGI: Controls de moviment de navegaciï¿½
	vdir[0] = n[0] - opvN.x;
	vdir[1] = n[1] - opvN.y;
	vdir[2] = n[2] - opvN.z;
	modul = sqrt(vdir[0] * vdir[0] + vdir[1] * vdir[1] + vdir[2] * vdir[2]);
	vdir[0] = vdir[0] / modul;
	vdir[1] = vdir[1] / modul;
	vdir[2] = vdir[2] / modul;

	switch (key)
	{
	case GLFW_KEY_W:
		opvN.x += fact_pan * vdir[0];
		opvN.y += fact_pan * vdir[1];
		n[0] += fact_pan * vdir[0];
		n[1] += fact_pan * vdir[1];
		// Tecla cursor amunt
	case GLFW_KEY_UP:
		opvN.x += fact_pan * vdir[0];
		opvN.y += fact_pan * vdir[1];
		n[0] += fact_pan * vdir[0];
		n[1] += fact_pan * vdir[1];
		break;

		// Tecla cursor avall
	case GLFW_KEY_DOWN:
		opvN.x -= fact_pan * vdir[0];
		opvN.y -= fact_pan * vdir[1];
		n[0] -= fact_pan * vdir[0];
		n[1] -= fact_pan * vdir[1];
		break;

		// Tecla cursor esquerra
	case GLFW_KEY_LEFT:
		angleZ += fact_pan;
		n[0] = n[0] - opvN.x;
		n[1] = n[1] - opvN.y;
		n[0] = n[0] * cos(angleZ * PI / 180) - n[1] * sin(angleZ * PI / 180);
		n[1] = n[0] * sin(angleZ * PI / 180) + n[1] * cos(angleZ * PI / 180);
		n[0] = n[0] + opvN.x;
		n[1] = n[1] + opvN.y;
		break;

		// Tecla cursor dret
	case GLFW_KEY_RIGHT:
		angleZ = 360 - fact_pan;
		n[0] = n[0] - opvN.x;
		n[1] = n[1] - opvN.y;
		n[0] = n[0] * cos(angleZ * PI / 180) - n[1] * sin(angleZ * PI / 180);
		n[1] = n[0] * sin(angleZ * PI / 180) + n[1] * cos(angleZ * PI / 180);
		n[0] = n[0] + opvN.x;
		n[1] = n[1] + opvN.y;
		break;

		// Tecla Inicio
	case GLFW_KEY_HOME:
		opvN.z += fact_pan;
		n[2] += fact_pan;
		break;

		// Tecla Fin
	case GLFW_KEY_END:
		opvN.z -= fact_pan;
		n[2] -= fact_pan;
		break;

		// Tecla PgUp
	case GLFW_KEY_PAGE_UP:
		fact_pan /= 2;
		if (fact_pan < 1) fact_pan = 1;
		break;

		// Tecla PgDown
	case GLFW_KEY_PAGE_DOWN:
		fact_pan *= 2;
		if (fact_pan > 2048) fact_pan = 2048;
		break;

	default:
		break;
	}
}

// Teclat_Pan: Teclat pels moviments de Pan.
void Teclat_Pan(int key, int action)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			// Tecla cursor amunt
		case VK_UP:
			tr_cpv.y -=  fact_pan;
			if (tr_cpv.y < -100000) tr_cpv.y = 100000;
			break;

		// Tecla cursor avall
		case GLFW_KEY_DOWN:
			tr_cpv.y += fact_pan;
			if (tr_cpv.y > 100000) tr_cpv.y = 100000;
			break;

		// Tecla cursor esquerra
		case GLFW_KEY_LEFT:
			tr_cpv.x +=  fact_pan;
			if (tr_cpv.x > 100000) tr_cpv.x = 100000;
			break;

		// Tecla cursor dret
		case GLFW_KEY_RIGHT:
			tr_cpv.x -=  fact_pan;
			if (tr_cpv.x < -100000) tr_cpv.x = 100000;
			break;

		// Tecla PgUp
		case GLFW_KEY_PAGE_UP:
			fact_pan /= 2;
			if (fact_pan < 0.125) fact_pan = 0.125;
			break;

		// Tecla PgDown
		case GLFW_KEY_PAGE_DOWN:
			fact_pan *= 2;
			if (fact_pan > 2048) fact_pan = 2048;
			break;

		// Tecla Insert: Fixar el desplaï¿½ament de pantalla (pan)
		case GLFW_KEY_INSERT:
			// Acumular desplaï¿½aments de pan (tr_cpv) en variables fixes (tr_cpvF).
			tr_cpvF.x += tr_cpv.x;		tr_cpv.x = 0.0;
			if (tr_cpvF.x > 100000) tr_cpvF.y = 100000;
			tr_cpvF.y += tr_cpv.y;		tr_cpv.y = 0.0;
			if (tr_cpvF.y > 100000) tr_cpvF.y = 100000;
			tr_cpvF.z += tr_cpv.z;		tr_cpv.z = 0.0;
			if (tr_cpvF.z > 100000) tr_cpvF.z = 100000;
			break;

		// Tecla Delete: Inicialitzar el desplaï¿½ament de pantalla (pan)
		case GLFW_KEY_DELETE:
			// Inicialitzar els valors de pan tant de la variable tr_cpv com de la tr_cpvF.
			tr_cpv.x = 0.0;			tr_cpv.y = 0.0;			tr_cpv.z = 0.0;
			tr_cpvF.x = 0.0;		tr_cpvF.y = 0.0;		tr_cpvF.z = 0.0;
			break;

		default:
			break;
		}
	}
}

// Teclat_TransEscala: Teclat pels canvis del valor d'escala per X,Y,Z.
void Teclat_TransEscala(int key, int action)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
// Modificar vector d'Escalatge per teclat (actiu amb Escalat ï¿½nicament)
		// Tecla '+' (augmentar tot l'escalat)
		case GLFW_KEY_KP_ADD:
			TG.VScal.x = TG.VScal.x * 2;
			if (TG.VScal.x > 8192) TG.VScal.x = 8192;
			TG.VScal.y = TG.VScal.y * 2;
			if (TG.VScal.y > 8192) TG.VScal.y = 8192;
			TG.VScal.z = TG.VScal.z * 2;
			if (TG.VScal.z > 8192) TG.VScal.z = 8192;
			break;

		// Tecla '-' (disminuir tot l'escalat)
		case GLFW_KEY_KP_SUBTRACT:
			TG.VScal.x = TG.VScal.x / 2;
			if (TG.VScal.x < 0.25) TG.VScal.x = 0.25;
			TG.VScal.y = TG.VScal.y / 2;
			if (TG.VScal.y < 0.25) TG.VScal.y = 0.25;
			TG.VScal.z = TG.VScal.z / 2;
			if (TG.VScal.z < 0.25) TG.VScal.z = 0.25;
			break;

		// Tecla cursor amunt ('8')
		case GLFW_KEY_UP:
			TG.VScal.x = TG.VScal.x * 2;
			if (TG.VScal.x > 8192) TG.VScal.x = 8192;
			break;

		// Tecla cursor avall ('2')
		case GLFW_KEY_DOWN:
			TG.VScal.x = TG.VScal.x / 2;
			if (TG.VScal.x < 0.25) TG.VScal.x = 0.25;
			break;

		// Tecla cursor esquerra ('4')
		case GLFW_KEY_LEFT:
			TG.VScal.y = TG.VScal.y / 2;
			if (TG.VScal.y < 0.25) TG.VScal.y = 0.25;
			break;

		// Tecla cursor dret ('6')
		case GLFW_KEY_RIGHT:
			TG.VScal.y = TG.VScal.y * 2;
			if (TG.VScal.y > 8192) TG.VScal.y = 8192;
			break;

		// Tecla HOME ('7')
		case GLFW_KEY_HOME:
			TG.VScal.z = TG.VScal.z * 2;
			if (TG.VScal.z > 8192) TG.VScal.z = 8192;
			break;

		// Tecla END ('1')
		case GLFW_KEY_END:
			TG.VScal.z = TG.VScal.z / 2;
			if (TG.VScal.z < 0.25) TG.VScal.z = 0.25;
			break;

		// Tecla INSERT
		case GLFW_KEY_INSERT:
			// Acumular transformacions Geomï¿½triques (variable TG) i de pan en variables fixes (variable TGF)
			TGF.VScal.x *= TG.VScal.x;	TGF.VScal.y *= TG.VScal.y; TGF.VScal.z *= TG.VScal.z;
			if (TGF.VScal.x > 8192)		TGF.VScal.x = 8192;
			if (TGF.VScal.y > 8192)		TGF.VScal.y = 8192;
			if (TGF.VScal.z > 8192)		TGF.VScal.z = 8192;
			TG.VScal.x = 1.0;				TG.VScal.y = 1.0;			TG.VScal.z = 1.0;
			TGF.VRota.x += TG.VRota.x;	TGF.VRota.y += TG.VRota.y; TGF.VRota.z += TG.VRota.z;
			if (TGF.VRota.x >= 360)		TGF.VRota.x -= 360; 		if (TGF.VRota.x < 0) TGF.VRota.x += 360;
			if (TGF.VRota.y >= 360)		TGF.VRota.y -= 360;		if (TGF.VRota.y < 0) TGF.VRota.y += 360;
			if (TGF.VRota.z >= 360)		TGF.VRota.z -= 360;		if (TGF.VRota.z < 0) TGF.VRota.z += 360;
			TG.VRota.x = 0.0;				TG.VRota.y = 0.0;					TG.VRota.z = 0.0;
			TGF.VTras.x += TG.VTras.x;	TGF.VTras.y += TG.VTras.y; TGF.VTras.z += TG.VTras.z;
			if (TGF.VTras.x < -100000)		TGF.VTras.x = 100000;		if (TGF.VTras.x > 10000) TGF.VTras.x = 100000;
			if (TGF.VTras.y < -100000)		TGF.VTras.y = 100000;		if (TGF.VTras.y > 10000) TGF.VTras.y = 100000;
			if (TGF.VTras.z < -100000)		TGF.VTras.z = 100000;		if (TGF.VTras.z > 10000) TGF.VTras.z = 100000;
			TG.VTras.x = 0.0;		TG.VTras.y = 0.0;		TG.VTras.z = 0.0;
			break;

		// Tecla Delete: Esborrar les Transformacions Geomï¿½triques Calculades
		case GLFW_KEY_DELETE:
			// Inicialitzar els valors de transformacions Geomï¿½triques i de pan en variables fixes.
			TGF.VScal.x = 1.0;		TGF.VScal.y = 1.0;;		TGF.VScal.z = 1.0;
			TG.VScal.x = 1.0;		TG.VScal.y = 1.0;		TG.VScal.z = 1.0;
			TGF.VRota.x = 0.0;		TGF.VRota.y = 0.0;		TGF.VRota.z = 0.0;
			TG.VRota.x = 0.0;		TG.VRota.y = 0.0;		TG.VRota.z = 0.0;
			TGF.VTras.x = 0.0;		TGF.VTras.y = 0.0;		TGF.VTras.z = 0.0;
			TG.VTras.x = 0.0;		TG.VTras.y = 0.0;		TG.VTras.z = 0.0;
			break;

		default:
			break;
		}
	}
}

// Teclat_TransRota: Teclat pels canvis del valor del vector de l'angle de rotaciï¿½ per X,Y,Z.
void Teclat_TransRota(int key, int action)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		// Tecla cursor amunt ('8')
		case GLFW_KEY_UP:
			TG.VRota.x += fact_Rota;
			if (TG.VRota.x >= 360) TG.VRota.x -= 360;
			break;

		// Tecla cursor avall ('2')
		case GLFW_KEY_DOWN:
			TG.VRota.x -= fact_Rota;
			if (TG.VRota.x < 1) TG.VRota.x += 360;
			break;

		// Tecla cursor esquerra ('4')
		case GLFW_KEY_LEFT:
			TG.VRota.y -= fact_Rota;
			if (TG.VRota.y < 1) TG.VRota.y += 360;
			break;

		// Tecla cursor dret ('6')
		case GLFW_KEY_RIGHT:
			TG.VRota.y += fact_Rota;
			if (TG.VRota.y >= 360) TG.VRota.y -= 360;
			break;

			// Tecla HOME ('7')
		case GLFW_KEY_HOME:
			TG.VRota.z += fact_Rota;
			if (TG.VRota.z >= 360) TG.VRota.z -= 360;
			break;

			// Tecla END ('1')
		case GLFW_KEY_END:
			TG.VRota.z -= fact_Rota;
			if (TG.VRota.z < 1) TG.VRota.z += 360;
			break;

			// Tecla PgUp ('9')
		case GLFW_KEY_PAGE_UP:
			fact_Rota /= 2;
			if (fact_Rota < 1) fact_Rota = 1;
			break;

			// Tecla PgDown ('3')
		case GLFW_KEY_PAGE_DOWN:
			fact_Rota *= 2;
			if (fact_Rota > 90) fact_Rota = 90;
			break;

			// Modificar vector d'Escalatge per teclat (actiu amb Rotaciï¿½)
				// Tecla '+' (augmentar escalat)
		case GLFW_KEY_KP_ADD:
			TG.VScal.x = TG.VScal.x * 2;
			if (TG.VScal.x > 8192) TG.VScal.x = 8192;
			TG.VScal.y = TG.VScal.y * 2;
			if (TG.VScal.y > 8192) TG.VScal.y = 8192;
			TG.VScal.z = TG.VScal.z * 2;
			if (TG.VScal.z > 8192) TG.VScal.z = 8192;
			break;

			// Tecla '-' (disminuir escalat)
		case GLFW_KEY_KP_SUBTRACT:
			TG.VScal.x = TG.VScal.x / 2;
			if (TG.VScal.x < 0.25) TG.VScal.x = 0.25;
			TG.VScal.y = TG.VScal.y / 2;
			if (TG.VScal.y < 0.25) TG.VScal.y = 0.25;
			TG.VScal.z = TG.VScal.z / 2;
			if (TG.VScal.z < 0.25) TG.VScal.z = 0.25;
			break;

			// Tecla Insert: Acumular transformacions Geomï¿½triques (variable TG) i de pan en variables fixes (variable TGF)
		case GLFW_KEY_INSERT:
			TGF.VScal.x *= TG.VScal.x;	TGF.VScal.y *= TG.VScal.y; TGF.VScal.z *= TG.VScal.z;
			if (TGF.VScal.x > 8192)		TGF.VScal.x = 8192;
			if (TGF.VScal.y > 8192)		TGF.VScal.y = 8192;
			if (TGF.VScal.z > 8192)		TGF.VScal.z = 8192;
			TG.VScal.x = 1.0;				TG.VScal.y = 1.0;			TG.VScal.z = 1.0;
			TGF.VRota.x += TG.VRota.x;	TGF.VRota.y += TG.VRota.y; TGF.VRota.z += TG.VRota.z;
			if (TGF.VRota.x >= 360)		TGF.VRota.x -= 360; 		if (TGF.VRota.x < 0) TGF.VRota.x += 360;
			if (TGF.VRota.y >= 360)		TGF.VRota.y -= 360;		if (TGF.VRota.y < 0) TGF.VRota.y += 360;
			if (TGF.VRota.z >= 360)		TGF.VRota.z -= 360;		if (TGF.VRota.z < 0) TGF.VRota.z += 360;
			TG.VRota.x = 0.0;				TG.VRota.y = 0.0;					TG.VRota.z = 0.0;
			TGF.VTras.x += TG.VTras.x;	TGF.VTras.y += TG.VTras.y; TGF.VTras.z += TG.VTras.z;
			if (TGF.VTras.x < -100000)		TGF.VTras.x = 100000;		if (TGF.VTras.x > 10000) TGF.VTras.x = 100000;
			if (TGF.VTras.y < -100000)		TGF.VTras.y = 100000;		if (TGF.VTras.y > 10000) TGF.VTras.y = 100000;
			if (TGF.VTras.z < -100000)		TGF.VTras.z = 100000;		if (TGF.VTras.z > 10000) TGF.VTras.z = 100000;
			TG.VTras.x = 0.0;		TG.VTras.y = 0.0;		TG.VTras.z = 0.0;
			break;

			// Tecla Delete: Esborrar les Transformacions Geomï¿½triques Calculades
		case GLFW_KEY_DELETE:
			// Inicialitzar els valors de transformacions Geomï¿½triques i de pan en variables fixes.
			TGF.VScal.x = 1.0;	TGF.VScal.y = 1.0;;	TGF.VScal.z = 1.0;
			TG.VScal.x = 1.0;		TG.VScal.y = 1.0;		TG.VScal.z = 1.0;
			TGF.VRota.x = 0.0;	TGF.VRota.y = 0.0;	TGF.VRota.z = 0.0;
			TG.VRota.x = 0.0;		TG.VRota.y = 0.0;		TG.VRota.z = 0.0;
			TGF.VTras.x = 0.0;	TGF.VTras.y = 0.0;	TGF.VTras.z = 0.0;
			TG.VTras.x = 0.0;		TG.VTras.y = 0.0;		TG.VTras.z = 0.0;
			break;

			// Tecla Espaiador
		case GLFW_KEY_SPACE:
			rota = !rota;
			trasl = !trasl;
			break;

		default:
			break;
		}
	}
}

// Teclat_TransTraslada: Teclat pels canvis del valor de traslaciï¿½ per X,Y,Z.
void Teclat_TransTraslada(int key, int action)
{
	GLdouble vdir[3] = { 0, 0, 0 };
	double modul = 0;

	if (action == GLFW_PRESS)
	{
		switch (key)
		{
			// Tecla cursor amunt ('8') - (ASCII:104)
		case GLFW_KEY_UP:
			TG.VTras.x -= fact_Tras;
			if (TG.VTras.x < -100000) TG.VTras.x = 100000;
			break;

			// Tecla cursor avall ('2') - (ASCII:98)
		case GLFW_KEY_DOWN:
			TG.VTras.x += fact_Tras;
			if (TG.VTras.x > 10000) TG.VTras.x = 100000;
			break;

			// Tecla cursor esquerra ('4') - (ASCII:100)
		case GLFW_KEY_LEFT:
			TG.VTras.y -= fact_Tras;
			if (TG.VTras.y < -100000) TG.VTras.y = -100000;
			break;

			// Tecla cursor dret ('6') - (ASCII:102)
		case GLFW_KEY_RIGHT:
			TG.VTras.y += fact_Tras;
			if (TG.VTras.y > 100000) TG.VTras.y = 100000;
			break;

			// Tecla HOME ('7') - (ASCII:103)
		case GLFW_KEY_HOME:
			TG.VTras.z += fact_Tras;
			if (TG.VTras.z > 100000) TG.VTras.z = 100000;
			break;

			// Tecla END ('1') - (ASCII:10#)
		case GLFW_KEY_END:
			TG.VTras.z -= fact_Tras;
			if (TG.VTras.z < -100000) TG.VTras.z = -100000;
			break;

			// Tecla PgUp ('9') - (ASCII:105)
		case GLFW_KEY_PAGE_UP:
			fact_Tras /= 2;
			if (fact_Tras < 1) fact_Tras = 1;
			break;

			// Tecla PgDown ('3') - (ASCII:99)
		case GLFW_KEY_PAGE_DOWN:
			fact_Tras *= 2;
			if (fact_Tras > 100000) fact_Tras = 100000;
			break;

			// Modificar vector d'Escalatge per teclat (actiu amb Traslaciï¿½)
				// Tecla '+' (augmentar escalat)
		case GLFW_KEY_KP_ADD:
			TG.VScal.x = TG.VScal.x * 2;
			if (TG.VScal.x > 8192) TG.VScal.x = 8192;
			TG.VScal.y = TG.VScal.y * 2;
			if (TG.VScal.y > 8192) TG.VScal.y = 8192;
			TG.VScal.z = TG.VScal.z * 2;
			if (TG.VScal.z > 8192) TG.VScal.z = 8192;
			break;

			// Tecla '-' (disminuir escalat) . (ASCII:109)
		case GLFW_KEY_KP_SUBTRACT:
			TG.VScal.x = TG.VScal.x / 2;
			if (TG.VScal.x < 0.25) TG.VScal.x = 0.25;
			TG.VScal.y = TG.VScal.y / 2;
			if (TG.VScal.y < 0.25) TG.VScal.y = 0.25;
			TG.VScal.z = TG.VScal.z / 2;
			if (TG.VScal.z < 0.25) TG.VScal.z = 0.25;
			break;

			// Tecla INSERT
		case GLFW_KEY_INSERT:
			// Acumular transformacions Geomï¿½triques (variable TG) i de pan en variables fixes (variable TGF)
			TGF.VScal.x *= TG.VScal.x;	TGF.VScal.y *= TG.VScal.y; TGF.VScal.z *= TG.VScal.z;
			if (TGF.VScal.x > 8192)		TGF.VScal.x = 8192;
			if (TGF.VScal.y > 8192)		TGF.VScal.y = 8192;
			if (TGF.VScal.z > 8192)		TGF.VScal.z = 8192;
			TG.VScal.x = 1.0;				TG.VScal.y = 1.0;			TG.VScal.z = 1.0;
			TGF.VRota.x += TG.VRota.x;	TGF.VRota.y += TG.VRota.y; TGF.VRota.z += TG.VRota.z;
			if (TGF.VRota.x >= 360)		TGF.VRota.x -= 360; 		if (TGF.VRota.x < 0) TGF.VRota.x += 360;
			if (TGF.VRota.y >= 360)		TGF.VRota.y -= 360;		if (TGF.VRota.y < 0) TGF.VRota.y += 360;
			if (TGF.VRota.z >= 360)		TGF.VRota.z -= 360;		if (TGF.VRota.z < 0) TGF.VRota.z += 360;
			TG.VRota.x = 0.0;				TG.VRota.y = 0.0;					TG.VRota.z = 0.0;
			TGF.VTras.x += TG.VTras.x;	TGF.VTras.y += TG.VTras.y; TGF.VTras.z += TG.VTras.z;
			if (TGF.VTras.x < -100000)		TGF.VTras.x = 100000;		if (TGF.VTras.x > 10000) TGF.VTras.x = 100000;
			if (TGF.VTras.y < -100000)		TGF.VTras.y = 100000;		if (TGF.VTras.y > 10000) TGF.VTras.y = 100000;
			if (TGF.VTras.z < -100000)		TGF.VTras.z = 100000;		if (TGF.VTras.z > 10000) TGF.VTras.z = 100000;
			TG.VTras.x = 0.0;		TG.VTras.y = 0.0;		TG.VTras.z = 0.0;
			break;

			// Tecla Delete: Esborrar les Transformacions Geomï¿½triques Calculades
		case GLFW_KEY_DELETE:
			// Inicialitzar els valors de transformacions Geomï¿½triques i de pan en variables fixes.
			TGF.VScal.x = 1.0;		TGF.VScal.y = 1.0;;		TGF.VScal.z = 1.0;
			TG.VScal.x = 1.0;		TG.VScal.y = 1.0;		TG.VScal.z = 1.0;
			TGF.VRota.x = 0.0;		TGF.VRota.y = 0.0;		TGF.VRota.z = 0.0;
			TG.VRota.x = 0.0;		TG.VRota.y = 0.0;		TG.VRota.z = 0.0;
			TGF.VTras.x = 0.0;		TGF.VTras.y = 0.0;		TGF.VTras.z = 0.0;
			TG.VTras.x = 0.0;		TG.VTras.y = 0.0;		TG.VTras.z = 0.0;
			break;

			// Tecla Espaiador
		case GLFW_KEY_SPACE:
			rota = !rota;
			trasl = !trasl;
			break;

		default:
			break;
		}
	}
}

// Teclat_Grid: Teclat pels desplaï¿½aments dels gridXY, gridXZ i gridYZ.
void Teclat_Grid(int key, int action)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		// Key Up cursor ('8') - (ASCII:104)
		case GLFW_KEY_UP:
			hgrid.x -= PAS_GRID;
			break;

		// Key Down cursor ('2') - (ASCII:98)
		case GLFW_KEY_DOWN:
			hgrid.x += PAS_GRID;
			break;

		// Key Left cursor ('4') - (ASCII:100)
		case GLFW_KEY_LEFT:
			hgrid.y -= PAS_GRID;
			break;

		// Key Right cursor ('6') - (ASCII:102)
		case GLFW_KEY_RIGHT:
			hgrid.y += PAS_GRID;
			break;

			// Key HOME ('7') - (ASCII:103)
		case GLFW_KEY_HOME:
			hgrid.z += PAS_GRID;
			break;

			// Key END ('1') - (ASCII:97)
		case GLFW_KEY_END:
			hgrid.z -= PAS_GRID;
			break;

			// Key grid ('G') - (ASCII:'G')
		case GLFW_KEY_G:
			sw_grid = !sw_grid;
			break;

			/*
			// Key grid ('g')
			case 'g':
			sw_grid = !sw_grid;
			break;
			*/

		default:
			break;
		}
	}
}


/* ------------------------------------------------------------------------- */
/*                           CONTROL DEL RATOLI                              */
/* ------------------------------------------------------------------------- */

// OnMouseButton: Funciï¿½ que es crida quan s'apreta algun botï¿½ (esquerra o dreta) del mouse.
//      PARAMETRES: - window: Finestra activa
//					- button: Botï¿½ seleccionat (GLFW_MOUSE_BUTTON_LEFT o GLFW_MOUSE_BUTTON_RIGHT)
//					- action: Acciï¿½ de la tecla: GLFW_PRESS (si s'ha apretat), GLFW_REPEAT, si s'ha repetit pressiï¿½ i GL_RELEASE, si es deixa d'apretar.
void OnMouseButton(GLFWwindow* window, int button, int action, int mods)
{

// Get the cursor position when the mouse key has been pressed or released.
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

// TODO: Agregue aquï¿½ su cï¿½digo de controlador de mensajes o llame al valor predeterminado

	if (Camera::MAIN_CAMERA.flying && action == GLFW_PRESS && !Camera::MAIN_CAMERA.endcam)
	{
		if (w / xpos < 2.2 && w / xpos > 1.8)
		{
			if (h / ypos < 2.1 && h / ypos > 1.8)
			{
				cout << "START BUTTON" << endl;
				OnKeyDown(window, GLFW_KEY_F, 1, GLFW_PRESS, 0);
				Crosshair::instance.enable();
			}
			if (h / ypos < 1.58 && h / ypos > 1.4)
			{
				OnKeyDown(window, GLFW_KEY_ESCAPE, 1, GLFW_PRESS, 0);
			}
		}
	}

	if (Camera::MAIN_CAMERA.zoom && action == GLFW_PRESS)
	{
		//cout << "x " << w / xpos << " y " << h / ypos << endl;

		int r = -1, c = -1;
		
		// columna:
		if (w / xpos < 3 && w / xpos > 2.5) c = 0;
		if (w / xpos < 2.35 && w / xpos > 2) c = 1;
		if (w / xpos < 1.93 && w / xpos > 1.72) c = 2;
		if (w / xpos < 1.63 && w / xpos > 1.47) c = 3;

		// fila
		if (h / ypos < 2.9 && h / ypos > 2.1) r = 0;
		if (h / ypos < 1.9 && h / ypos > 1.56) r = 1;
		if (h / ypos < 1.42 && h / ypos > 1.2) r = 2;

		if (r != -1 && c != -1) // c cancelar, o ok
		{
			char panell_numeric[3][4] = {
				{'1','2', '3', 'c'},
				{'4', '5', '6', 'k' },
				{'7', '8', '9', '0'}
			};

			char tecla = panell_numeric[r][c];
			if (tecla == 'k')
			{
				if (contrasenya == "573")
				{
					Level::CURRENT_LEVEL.my_vago->obrir_porta();
				}
				else
				{
					contrasenya.clear();
					Level::CURRENT_LEVEL.panel->clear_display();
				}
					
				cout << "solucio" << endl;
			}
			else if (tecla == 'c')
			{
				contrasenya.clear();
				Level::CURRENT_LEVEL.panel->clear_display();
				cout << "borrar" << endl;
			}
			else
			{
				contrasenya += tecla;
				if (contrasenya.length() > 3)
					contrasenya.erase(0, contrasenya.length() - 3);
				Level::CURRENT_LEVEL.panel->push_digit(tecla - '0');
			}
			cout << "Tecla: " << tecla << endl;
		}
	}

// OnLButtonDown
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) //pulsar click
		{
		// Entorn VGI: Detectem en quina posiciï¿½ s'ha apretat el botï¿½ esquerra del
		//				mouse i ho guardem a la variable m_PosEAvall i activem flag m_ButoEAvall
			m_ButoEAvall = true;
			//m_PosEAvall = point;
			m_PosEAvall.x = xpos;	m_PosEAvall.y = ypos;
			m_EsfeEAvall = OPV;

			InteractableEntity* euc = Level::CURRENT_LEVEL.my_entity_under_cursor; 
			if (euc) //si hay algo bajo el cursor
			{
				if (euc->is_interactable())
					euc->interact(); //ejecutamos interact
			}	
		}
// OnLButtonUp: Funciï¿½ que es crida quan deixem Fd'apretar el botï¿½ esquerra del mouse.
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
			{	// Entorn VGI: Desactivem flag m_ButoEAvall quan deixem d'apretar botï¿½ esquerra del mouse.
				m_ButoEAvall = false;

				// OPCIï¿½ VISTA-->SATï¿½LIT: Cï¿½lcul increment desplaï¿½ament del Punt de Vista
				if ((satelit) && (projeccio != ORTO))
				{	//m_EsfeIncEAvall.R = m_EsfeEAvall.R - OPV.R;
					m_EsfeIncEAvall.alfa = 0.01f * (OPV.alfa - m_EsfeEAvall.alfa); //if (abs(m_EsfeIncEAvall.alfa)<0.01) { if ((m_EsfeIncEAvall.alfa)>0.0) m_EsfeIncEAvall.alfa = 0.01 else m_EsfeIncEAvall.alfa=0.01}
					m_EsfeIncEAvall.beta = 0.01f * (OPV.beta - m_EsfeEAvall.beta);
					if (abs(m_EsfeIncEAvall.beta) < 0.01) 
						{	if ((m_EsfeIncEAvall.beta) > 0.0) m_EsfeIncEAvall.beta = 0.01;
								else m_EsfeIncEAvall.beta = 0.01;
						}
				//if ((m_EsfeIncEAvall.R == 0.0) && (m_EsfeIncEAvall.alfa == 0.0) && (m_EsfeIncEAvall.beta == 0.0)) KillTimer(WM_TIMER);
				//else SetTimer(WM_TIMER, 10, NULL);
				}
			}
// OnRButtonDown
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{	// Entorn VGI: Detectem en quina posiciï¿½ s'ha apretat el botï¿½ esquerra del
		//				mouse i ho guardem a la variable m_PosEAvall i activem flag m_ButoEAvall
		m_ButoDAvall = true;
		//m_PosDAvall = point;
		m_PosDAvall.x = xpos;	m_PosDAvall.y = ypos;
	}
	// OnLButtonUp: Funciï¿½ que es crida quan deixem d'apretar el botï¿½ esquerra del mouse.
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
	{	// Entorn VGI: Desactivem flag m_ButoEAvall quan deixem d'apretar botï¿½ esquerra del mouse.
		m_ButoDAvall = false;
	}


}

// OnMouseMove: Funciï¿½ que es crida quan es mou el mouse. La utilitzem per la 
//				  Visualitzaciï¿½ Interactiva amb les tecles del mouse apretades per 
//				  modificar els parï¿½metres de P.V. (R,angleh,anglev) segons els 
//				  moviments del mouse.
//      PARAMETRES: - window: Finestra activa
//					- xpos: Posiciï¿½ X del cursor del mouse (coord. pantalla) quan el botï¿½ s'ha apretat.
//					- ypos: Posiciï¿½ Y del cursor del mouse(coord.pantalla) quan el botï¿½ s'ha apretat.
void OnMouseMove(GLFWwindow* window, double xpos, double ypos)
{
// TODO: Agregue aquï¿½ su cï¿½digo de controlador de mensajes o llame al valor predeterminado
	double modul = 0;
	GLdouble vdir[3] = { 0, 0, 0 };
	CSize gir, girn, girT, zoomincr;

	if (Camera::MAIN_CAMERA.flying && !Camera::MAIN_CAMERA.endcam)
	{
		if (w / xpos < 2.2 && w / xpos > 1.8 && h / ypos < 2.1 && h / ypos > 1.8)
		{
			Menu::instance.change_indicator(MenuType::START);
		}
		else if (w / xpos < 2.2 && w / xpos > 1.8 && h / ypos < 1.58 && h / ypos > 1.4)
		{
			Menu::instance.change_indicator(MenuType::EXIT);
		}
		else {
			Menu::instance.change_indicator(MenuType::MENU);
		}
	}
	if (camera == CAM_PERSONALITZADA && !Camera::MAIN_CAMERA.flying && !Camera::MAIN_CAMERA.zoom)
	{
		Camera::MAIN_CAMERA.horizontal_angle += Camera::MAIN_CAMERA.mouse_speed * float(w / 2 - xpos);
		Camera::MAIN_CAMERA.vertical_angle += Camera::MAIN_CAMERA.mouse_speed * float(h / 2 - ypos);

		Camera::MAIN_CAMERA.vertical_angle = glm::clamp<float>(Camera::MAIN_CAMERA.vertical_angle, -PI / 2 + 0.01, PI / 2 - 0.01);

		glfwSetCursorPos(window, w / 2, h / 2);
	}

	// TODO: Add your message handler code here and/or call default
	if (m_ButoEAvall && mobil && projeccio != CAP)
	{
		// Entorn VGI: Determinaciï¿½ dels angles (en graus) segons l'increment
		//				horitzontal i vertical de la posiciï¿½ del mouse.
		//CSize gir = m_PosEAvall - point;
		gir.cx = m_PosEAvall.x - xpos;		gir.cy = m_PosEAvall.y - ypos;
		//m_PosEAvall = point;
		m_PosEAvall.x = xpos;				m_PosEAvall.y = ypos;
		OPV.beta = OPV.beta - gir.cx / 2;
		OPV.alfa = OPV.alfa + gir.cy / 2;

		// Entorn VGI: Control per evitar el creixement desmesurat dels angles.
		if (OPV.alfa >= 360)	OPV.alfa = OPV.alfa - 360;
		if (OPV.alfa < 0)		OPV.alfa = OPV.alfa + 360;
		if (OPV.beta >= 360)	OPV.beta = OPV.beta - 360;
		if (OPV.beta < 0)		OPV.beta = OPV.beta + 360;
		// Crida a OnPaint() per redibuixar l'escena
		//OnPaint(window);
	}
	else if (m_ButoEAvall && (camera == CAM_NAVEGA) && (projeccio != CAP && projeccio != ORTO)) // Opciï¿½ Navegaciï¿½
	{
		// Entorn VGI: Canviar orientaciï¿½ en opciï¿½ de Navegaciï¿½
		//CSize girn = m_PosEAvall - point;
		girn.cx = m_PosEAvall.x - xpos;		girn.cy = m_PosEAvall.y - ypos;
		angleZ = girn.cx / 2.0;
		// Entorn VGI: Control per evitar el creixement desmesurat dels angles.
		if (angleZ >= 360) angleZ = angleZ - 360;
		if (angleZ < 0)	angleZ = angleZ + 360;

		n[0] = n[0] - opvN.x;
		n[1] = n[1] - opvN.y;
		n[0] = n[0] * cos(angleZ * PI / 180) - n[1] * sin(angleZ * PI / 180);
		n[1] = n[0] * sin(angleZ * PI / 180) + n[1] * cos(angleZ * PI / 180);
		n[0] = n[0] + opvN.x;
		n[1] = n[1] + opvN.y;

		//m_PosEAvall = point;
		m_PosEAvall.x = xpos;		m_PosEAvall.y = ypos;
		// Crida a OnPaint() per redibuixar l'escena
		//OnPaint(window);
	}

	// Entorn VGI: Transformaciï¿½ Geomï¿½trica interactiva pels eixos X,Y boto esquerra del mouse.
	else {
		bool transE = transX || transY;
		if (m_ButoEAvall && transE && transf)
		{
			// Calcular increment
			//CSize girT = m_PosEAvall - point;
			girT.cx = m_PosEAvall.x - xpos;		girT.cy = m_PosEAvall.y - ypos;
			if (transX)
			{
				long int incrT = girT.cx;
				if (trasl)
				{
					TG.VTras.x += incrT * fact_Tras;
					if (TG.VTras.x < -100000) TG.VTras.x = 100000;
					if (TG.VTras.x > 100000) TG.VTras.x = 100000;
				}
				else if (rota)
				{
					TG.VRota.x += incrT * fact_Rota;
					while (TG.VRota.x >= 360) TG.VRota.x -= 360;
					while (TG.VRota.x < 0) TG.VRota.x += 360;
				}
				else if (escal)
				{
					if (incrT < 0) incrT = -1 / incrT;
					TG.VScal.x = TG.VScal.x * incrT;
					if (TG.VScal.x < 0.25) TG.VScal.x = 0.25;
					if (TG.VScal.x > 8192) TG.VScal.x = 8192;
				}
			}
			if (transY)
			{
				long int incrT = girT.cy;
				if (trasl)
				{
					TG.VTras.y += incrT * fact_Tras;
					if (TG.VTras.y < -100000) TG.VTras.y = 100000;
					if (TG.VTras.y > 100000) TG.VTras.y = 100000;
				}
				else if (rota)
				{
					TG.VRota.y += incrT * fact_Rota;
					while (TG.VRota.y >= 360) TG.VRota.y -= 360;
					while (TG.VRota.y < 0) TG.VRota.y += 360;
				}
				else if (escal)
				{
					if (incrT <= 0) {
						if (incrT >= -2) incrT = -2;
						incrT = 1 / Log2(-incrT);
					}
					else incrT = Log2(incrT);
					TG.VScal.y = TG.VScal.y * incrT;
					if (TG.VScal.y < 0.25) TG.VScal.y = 0.25;
					if (TG.VScal.y > 8192) TG.VScal.y = 8192;
				}
			}
			//m_PosEAvall = point;
			m_PosEAvall.x = xpos;	m_PosEAvall.y = ypos;
			// Crida a OnPaint() per redibuixar l'escena
			//InvalidateRect(NULL, false);
			//OnPaint(windows);
		}
	}

	// Entorn VGI: Determinaciï¿½ del desplaï¿½ament del pan segons l'increment
	//				vertical de la posiciï¿½ del mouse (tecla dreta apretada).
	if (m_ButoDAvall && pan && (projeccio != CAP && projeccio != ORTO))
	{
		//CSize zoomincr = m_PosDAvall - point;
		zoomincr.cx = m_PosDAvall.x - xpos;		zoomincr.cy = m_PosDAvall.y - ypos;
		long int incrx = zoomincr.cx;
		long int incry = zoomincr.cy;

		// Desplaï¿½ament pan vertical
		tr_cpv.y -= incry * fact_pan;
		if (tr_cpv.y > 100000) tr_cpv.y = 100000;
		else if (tr_cpv.y < -100000) tr_cpv.y = -100000;

		// Desplaï¿½ament pan horitzontal
		tr_cpv.x += incrx * fact_pan;
		if (tr_cpv.x > 100000) tr_cpv.x = 100000;
		else if (tr_cpv.x < -100000) tr_cpv.x = -100000;

		//m_PosDAvall = point;
		m_PosDAvall.x = xpos;	m_PosDAvall.y = ypos;
		// Crida a OnPaint() per redibuixar l'escena
		//OnPaint(window);
	}
	// Determinaciï¿½ del parï¿½metre R segons l'increment
	//   vertical de la posiciï¿½ del mouse (tecla dreta apretada)
		//else if (m_ButoDAvall && zzoom && (projeccio!=CAP && projeccio!=ORTO))
	else if (m_ButoDAvall && zzoom && (projeccio != CAP))
	{
		//CSize zoomincr = m_PosDAvall - point;
		zoomincr.cx = m_PosDAvall.x - xpos;		zoomincr.cy = m_PosDAvall.y - ypos;
		long int incr = zoomincr.cy / 1.0;

		//		zoom=zoom+incr;
		OPV.R = OPV.R + incr;
		if (OPV.R < p_near) OPV.R = p_near;
		if (OPV.R > p_far) OPV.R = p_far;
		//m_PosDAvall = point;
		m_PosDAvall.x = xpos;				m_PosDAvall.y = ypos;
		// Crida a OnPaint() per redibuixar l'escena
		//OnPaint(window);
	}
	else if (m_ButoDAvall &&  (camera == CAM_NAVEGA) && (projeccio != CAP && projeccio != ORTO))
	{	// Avanï¿½ar en opciï¿½ de Navegaciï¿½
		if ((m_PosDAvall.x != xpos) && (m_PosDAvall.y != ypos))
		{
			//CSize zoomincr = m_PosDAvall - point;
			zoomincr.cx = m_PosDAvall.x - xpos;		zoomincr.cy = m_PosDAvall.y - ypos;
			double incr = zoomincr.cy / 2;
			//			long int incr=zoomincr.cy/2.0;  // Causa assertion en "afx.inl" lin 169
			vdir[0] = n[0] - opvN.x;
			vdir[1] = n[1] - opvN.y;
			vdir[2] = n[2] - opvN.z;
			modul = sqrt(vdir[0] * vdir[0] + vdir[1] * vdir[1] + vdir[2] * vdir[2]);
			vdir[0] = vdir[0] / modul;
			vdir[1] = vdir[1] / modul;
			vdir[2] = vdir[2] / modul;
			opvN.x += incr * vdir[0];
			opvN.y += incr * vdir[1];
			n[0] += incr * vdir[0];
			n[1] += incr * vdir[1];
			//m_PosDAvall = point;
			m_PosDAvall.x = xpos;				m_PosDAvall.y = ypos;
			// Crida a OnPaint() per redibuixar l'escena
			//OnPaint(window);
		}
	}

	// Entorn VGI: Transformaciï¿½ Geomï¿½trica interactiva per l'eix Z amb boto dret del mouse.
	else if (m_ButoDAvall && transZ && transf)
	{
		// Calcular increment
		//CSize girT = m_PosDAvall - point;
		girT.cx = m_PosDAvall.x - xpos;		girT.cy = m_PosDAvall.y - ypos;
		long int incrT = girT.cy;
		if (trasl)
		{
			TG.VTras.z += incrT * fact_Tras;
			if (TG.VTras.z < -100000) TG.VTras.z = 100000;
			if (TG.VTras.z > 100000) TG.VTras.z = 100000;
		}
		else if (rota)
		{
			incrT = girT.cx;
			TG.VRota.z += incrT * fact_Rota;
			while (TG.VRota.z >= 360) TG.VRota.z -= 360;
			while (TG.VRota.z < 0) TG.VRota.z += 360;
		}
		else if (escal)
		{
			if (incrT <= 0) {
				if (incrT >= -2) incrT = -2;
				incrT = 1 / Log2(-incrT);
			}
			else incrT = Log2(incrT);
			TG.VScal.z = TG.VScal.z * incrT;
			if (TG.VScal.z < 0.25) TG.VScal.z = 0.25;
			if (TG.VScal.z > 8192) TG.VScal.z = 8192;
		}

		//m_PosDAvall = point;
		m_PosDAvall.x = xpos;	m_PosDAvall.y = ypos;
		// Crida a OnPaint() per redibuixar l'escena
		//OnPaint(window);
	}
}

// OnMouseWheel: Funciï¿½ que es crida quan es mou el rodet del mouse. La utilitzem per la 
//				  Visualitzaciï¿½ Interactiva per modificar el parï¿½metre R de P.V. (R,angleh,anglev) 
//				  segons el moviment del rodet del mouse.
//      PARAMETRES: - nFlags: Flags que controlen si el botï¿½ es apretat o no.
//					- zDelta: Unitats de desplaï¿½ament del rodet del mouse.
//					- pt: Estructura (x,y) que dï¿½na la posiciï¿½ del mouse 
//							 (coord. pantalla) quan el botï¿½ s'ha apretat.
//void OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
void OnMouseWheel(GLFWwindow* window, double xoffset, double yoffset)
{
	// TODO: Agregue aquï¿½ su cï¿½digo de controlador de mensajes o llame al valor predeterminado
	double modul = 0;
	GLdouble vdir[3] = { 0, 0, 0 };

	// Funciï¿½ de zoom quan estï¿½ activada la funciï¿½ pan o les T. Geomï¿½triques
	if ((zzoom) || (transX) || (transY) || (transZ))
	{
		//OPV.R = OPV.R + zDelta / 4;
		OPV.R = OPV.R + yoffset / 4;
		if (OPV.R < 1) OPV.R = 1;
		// Crida a OnPaint() per redibuixar l'escena
		//OnPaint(window);
	}
	else if (camera == CAM_NAVEGA)
	{
		vdir[0] = n[0] - opvN.x;
		vdir[1] = n[1] - opvN.y;
		vdir[2] = n[2] - opvN.z;
		modul = sqrt(vdir[0] * vdir[0] + vdir[1] * vdir[1] + vdir[2] * vdir[2]);
		vdir[0] = vdir[0] / modul;
		vdir[1] = vdir[1] / modul;
		vdir[2] = vdir[2] / modul;
		opvN.x += (yoffset / 4) * vdir[0];		//opvN.x += (zDelta / 4) * vdir[0];
		opvN.y += (yoffset / 4) * vdir[1];		//opvN.y += (zDelta / 4) * vdir[1];
		n[0] += (yoffset / 4) * vdir[0];		//n[0] += (zDelta / 4) * vdir[0];
		n[1] += (yoffset / 4) * vdir[1];			//n[1] += (zDelta / 4) * vdir[1];
		// Crida a OnPaint() per redibuixar l'escena
		//OnPaint(window);
	}
}


/* ------------------------------------------------------------------------- */
/*					     TIMER (ANIMACIï¿½)									 */
/* ------------------------------------------------------------------------- */
void OnTimer()
{
	// TODO: Agregue aquï¿½ su cï¿½digo de controlador de mensajes o llame al valor predeterminado
	if (anima) {
		// Codi de tractament de l'animaciï¿½ quan transcorren els ms. del crono.

		// Crida a OnPaint() per redibuixar l'escena
		//InvalidateRect(NULL, false);
	}
	else if (satelit) {	// OPCIï¿½ SATï¿½LIT: Increment OPV segons moviments mouse.
		//OPV.R = OPV.R + m_EsfeIncEAvall.R;
		OPV.alfa = OPV.alfa + m_EsfeIncEAvall.alfa;
		while (OPV.alfa > 360) OPV.alfa = OPV.alfa - 360;	while (OPV.alfa < 0) OPV.alfa = OPV.alfa + 360;
		OPV.beta = OPV.beta + m_EsfeIncEAvall.beta;
		while (OPV.beta > 360) OPV.beta = OPV.beta - 360;	while (OPV.beta < 0) OPV.beta = OPV.beta + 360;

		// Crida a OnPaint() per redibuixar l'escena
		//OnPaint();
	}
}

// ---------------- Entorn VGI: Funcions locals a main.cpp

// Log2: Cï¿½lcul del log base 2 de num
int Log2(int num)
{
	int tlog;

	if (num >= 8192) tlog = 13;
	else if (num >= 4096) tlog = 12;
	else if (num >= 2048) tlog = 11;
	else if (num >= 1024) tlog = 10;
	else if (num >= 512) tlog = 9;
	else if (num >= 256) tlog = 8;
	else if (num >= 128) tlog = 7;
	else if (num >= 64) tlog = 6;
	else if (num >= 32) tlog = 5;
	else if (num >= 16) tlog = 4;
	else if (num >= 8) tlog = 3;
	else if (num >= 4) tlog = 2;
	else if (num >= 2) tlog = 1;
	else tlog = 0;

	return tlog;
}


// -------------------- FUNCIONS CORBES SPLINE i BEZIER

// llegir_ptsC: Llegir punts de control de corba (spline o Bezier) d'un fitxer .crv. 
//				Retorna el nombre de punts llegits en el fitxer.
//int llegir_pts(CString nomf)
int llegir_ptsC(const char* nomf)
{
	int i, j;
	FILE* fd;

	// Inicialitzar vector punts de control de la corba spline
	for (i = 0; i < MAX_PATCH_CORBA; i = i++)
	{
		PC_t[i].x = 0.0;
		PC_t[i].y = 0.0;
		PC_t[i].z = 0.0;
	}

	//	ifstream f("altinicials.dat",ios::in);
	//    f>>i; f>>j;
	if ((fd = fopen(nomf, "rt")) == NULL)
	{
		//LPCWSTR texte1 = reinterpret_cast<LPCWSTR> ("ERROR:");
		//LPCWSTR texte2 = reinterpret_cast<LPCWSTR> ("File .crv was not opened");
		//MessageBox(texte1, texte2, MB_OK);
		fprintf(stderr, "ERROR: File .crv was not opened");
		return false;
	}
	fscanf(fd, "%d \n", &i);
	if (i == 0) return false;
	else {
		for (j = 0; j < i; j = j++)
		{	//fscanf(fd, "%f", &corbaSpline[j].x);
			//fscanf(fd, "%f", &corbaSpline[j].y);
			//fscanf(fd, "%f \n", &corbaSpline[j].z);
			fscanf(fd, "%lf %lf %lf \n", &PC_t[j].x, &PC_t[j].y, &PC_t[j].z);

		}
	}
	fclose(fd);

	return i;
}


// Entorn VGI. OnFull_Screen: Funciï¿½ per a pantalla completa
void OnFull_Screen(GLFWmonitor* monitor, GLFWwindow *window)
{   
	//int winPosX, winPosY;
	//winPosX = 0;	winPosY = 0;

	fullscreen = !fullscreen;

	if (fullscreen) {	// backup window position and window size
						//glfwGetWindowPos(window, &winPosX, &winPosY);
						//glfwGetWindowSize(window, &width_old, &height_old);

						// Get resolution of monitor
						const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

						w = mode->width;	h = mode->height;
						// Switch to full screen
						glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
					}
	else {	// Restore last window size and position
			glfwSetWindowMonitor(window, nullptr, 216, 239, 640, 480, mode->refreshRate);
		}
	}

// -------------------- TRACTAMENT ERRORS
// error_callback: Displaia error que es pugui produir
void error_callback(int code, const char* description)
{
    //const char* descripcio;
    //int codi = glfwGetError(&descripcio);

 //   display_error_message(code, description);
	fprintf(stderr, "Codi Error: %i", code);
	fprintf(stderr, "Descripcio: %s\n",description);
}


GLenum glCheckError_(const char* file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		fprintf(stderr, "ERROR %s | File: %s | Line ( %3i ) \n", error.c_str(), file, line);
		//fprintf(stderr, "ERROR %s | ", error.c_str());
		//fprintf(stderr, "File: %s | ", file);
		//fprintf(stderr, "Line ( %3i ) \n", line);
	}
	return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

void APIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam)
{
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // ignore these non-significant error codes

	fprintf(stderr, "---------------\n");
	fprintf(stderr, "Debug message ( %3i %s \n", id, message);

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             fprintf(stderr, "Source: API \n"); break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   fprintf(stderr, "Source: Window System \n"); break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: fprintf(stderr, "Source: Shader Compiler \n"); break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     fprintf(stderr, "Source: Third Party \n"); break;
	case GL_DEBUG_SOURCE_APPLICATION:     fprintf(stderr, "Source: Application \n"); break;
	case GL_DEBUG_SOURCE_OTHER:           fprintf(stderr, "Source: Other \n"); break;
	} //std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               fprintf(stderr, "Type: Error\n"); break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: fprintf(stderr, "Type: Deprecated Behaviour\n"); break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  fprintf(stderr, "Type: Undefined Behaviour\n"); break;
	case GL_DEBUG_TYPE_PORTABILITY:         fprintf(stderr, "Type: Portability\n"); break;
	case GL_DEBUG_TYPE_PERFORMANCE:         fprintf(stderr, "Type: Performance\n"); break;
	case GL_DEBUG_TYPE_MARKER:              fprintf(stderr, "Type: Marker\n"); break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          fprintf(stderr, "Type: Push Group\n"); break;
	case GL_DEBUG_TYPE_POP_GROUP:           fprintf(stderr, "Type: Pop Group\n"); break;
	case GL_DEBUG_TYPE_OTHER:               fprintf(stderr, "Type: Other\n"); break;
	} //std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         fprintf(stderr, "Severity: high\n"); break;
	case GL_DEBUG_SEVERITY_MEDIUM:       fprintf(stderr, "Severity: medium\n"); break;
	case GL_DEBUG_SEVERITY_LOW:          fprintf(stderr, "Severity: low\n"); break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: fprintf(stderr, "Severity: notification\n"); break;
	} //std::cout << std::endl;
	//std::cout << std::endl;
	fprintf(stderr, "\n");


	//exit(0);
}

int main(void)
{


	irrklang::ISoundEngine* soundEngine = irrklang::createIrrKlangDevice();;

	if (!soundEngine)
	{
		cout << "Could not startup irrKlang engine" << endl;
	}
	if(soundEngine) {
		// To play a sound, we only to call play2D(). The second parameter
		// tells the engine to play it looped.
		// play some sound stream, looped
		irrklang::ISound* snd = soundEngine->play2D("../EntornVGI/media/movingTrain.mp3", true);
		//soundEngine->setSoundVolume(irrklang::ik_f32(0.02)); //cambiar volumen
	}

	///-----includes_end-----

	int i;
	///-----initialization_start-----

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -10, 0));

	///-----initialization_end-----

	//keep track of the shapes, we release memory at exit.
	//make sure to re-use collision shapes among rigid bodies whenever possible!
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	///create a few basic rigid bodies

	//the ground is a cube of side 100 at position y = -56.
	//the sphere will hit it at y = -6, with center at -5
	{
		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

		collisionShapes.push_back(groundShape);

		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, -56, 0));

		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass, localInertia);

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		dynamicsWorld->addRigidBody(body);
	}

	{
		//create a dynamic rigidbody

		//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
		btCollisionShape* colShape = new btSphereShape(btScalar(1.));
		collisionShapes.push_back(colShape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar mass(1.f);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
			colShape->calculateLocalInertia(mass, localInertia);

		startTransform.setOrigin(btVector3(2, 10, 0));

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		dynamicsWorld->addRigidBody(body);
	}

	/// Do some simulation

	///-----stepsimulation_start-----
	for (i = 0; i < 150; i++)
	{
		dynamicsWorld->stepSimulation(1.f / 60.f, 10);

		//print positions of all objects
		for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform trans;
			if (body && body->getMotionState())
			{
				body->getMotionState()->getWorldTransform(trans);
			}
			else
			{
				trans = obj->getWorldTransform();
			}
			printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
		}
	}

	///-----stepsimulation_end-----

	//cleanup in the reverse order of creation/initialization

	///-----cleanup_start-----

	//remove the rigidbodies from the dynamics world and delete them
	for (i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	for (int j = 0; j < collisionShapes.size(); j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}

	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;

	//next line is optional: it will be cleared by the destructor when the array goes out of scope
	collisionShapes.clear();

	


	


	BulletWorld::WORLD = new BulletWorld;







//    GLFWwindow* window;
// Entorn VGI. Timer: Variables
	float time = elapsedTime;
	float now;
	float delta;


// glfw: initialize and configure
// ------------------------------
	if (!glfwInit())
	{	fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

// Retrieving main monitor
    primary = glfwGetPrimaryMonitor();

// To get current video mode of a monitor
    mode = glfwGetVideoMode(primary);

// Retrieving monitors
//    int countM;
//   GLFWmonitor** monitors = glfwGetMonitors(&countM);

// Retrieving video modes of the monitor
    int countVM;
    const GLFWvidmode* modes = glfwGetVideoModes(primary, &countVM);

// ------------- Entorn VGI: Configure OpenGL context
//	glfwWindowHint(GLFW_SAMPLES, 4);
//	if (GLEW_VERSION_4_3) {	
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // GL4.3

		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Si funcions deprecades sï¿½n eliminades (no ARB_COMPATIBILITY)
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_FALSE);  // Si funcions deprecades NO sï¿½n eliminades (Si ARB_COMPATIBILITY)

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// Creaciï¿½ contexte CORE
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);	// Creaciï¿½ contexte ARB_COMPATIBILITY
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE); // comment this line in a release build! 
//		}
/*
	else if (GLEW_VERSION_3_3) {	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	
									glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // GL3.3
									glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
									glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
								}
//		else  {	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
//				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0); // GL2.0
//				}
*/	

	const unsigned char* version = (unsigned char*)glGetString(GL_VERSION);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

// Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Entorn VGI - Visualitzacio Grafica Interactiva, Escola d'Enginyeria (UAB)", NULL, NULL);
    if (!window)
    {	fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
        return -1;
    }

// Make the window's context current
    glfwMakeContextCurrent(window);

// Llegir resoluciï¿½ actual de pantalla
	glfwGetWindowSize(window, &width_old, &height_old);
	

// Initialize GLEW
	if (GLEW_VERSION_3_3) glewExperimental = GL_TRUE; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		glGetError();	// Esborrar codi error generat per bug a llibreria GLEW
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}


// ------------ - Entorn VGI : Enable OpenGL debug context if context allows for DEBUG CONTEXT (GL4.3)
	if (GLEW_VERSION_4_3)
	{	GLint flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{	glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // makes sure errors are displayed synchronously
			glDebugMessageCallback(glDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}
	}

// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

// Initialize Application control varibles
	InitGL();

//	OnPaint();
// Swap front and back buffers
//    glfwSwapBuffers(window);

// ------------- Entorn VGI: Callbacks
// Set GLFW event callbacks. I removed glfwSetWindowSizeCallback for conciseness
	glfwSetWindowSizeCallback(window, OnSize);										// - Windows Size in screen Coordinates
	glfwSetFramebufferSizeCallback(window, OnSize);									// - Windows Size in Pixel Coordinates
	glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)OnMouseButton);			// - Directly redirect GLFW mouse button events
	glfwSetCursorPosCallback(window, (GLFWcursorposfun)OnMouseMove);				// - Directly redirect GLFW mouse position events
	glfwSetScrollCallback(window, (GLFWscrollfun)OnMouseWheel);						// - Directly redirect GLFW mouse wheel events
	glfwSetKeyCallback(window, (GLFWkeyfun)OnKeyDown);								// - Directly redirect GLFW key events
	//glfwSetCharCallback(window, OnTextDown);										// - Directly redirect GLFW char events
	glfwSetErrorCallback(error_callback);											// Error callback
	glfwSetWindowRefreshCallback(window, (GLFWwindowrefreshfun)OnPaint);			// - Callback to refresh the screen

// Entorn VGI. Timer: Lectura temps
	float previous = glfwGetTime();

	Camera::MAIN_CAMERA.setupColliders();

	std::vector<Vertex> cube_vertices = {
		Vertex({0.5f,  0.5f,  0.5f,}, {0.0,  0.0,  1.0}, {0.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({-0.5f,  0.5f,  0.5f}, {0.0,  0.0,  1.0}, {1.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({-0.5f, -0.5f,  0.5f}, {0.0,  0.0,  1.0}, {1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({0.5f, -0.5f,  0.5f}, {0.0,  0.0,  1.0}, {0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({0.5f,  0.5f,  0.5f,}, {1.0,  0.0,  0.0}, {1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({0.5f, -0.5f,  0.5f}, {1.0,  0.0,  0.0}, {0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({0.5f, -0.5f, -0.5f}, {1.0,  0.0,  0.0}, {0.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({0.5f,  0.5f, -0.5f}, {1.0,  0.0,  0.0}, {1.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({0.5f,  0.5f,  0.5f,}, {0.0,  1.0,  0.0}, {1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({0.5f,  0.5f, -0.5f}, {0.0,  1.0,  0.0}, {1.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({-0.5f,  0.5f, -0.5f}, {0.0,  1.0,  0.0}, {0.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({-0.5f,  0.5f,  0.5f}, {0.0,  1.0,  0.0}, {0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({-0.5f,  0.5f,  0.5f,}, {-1.0,  0.0,  0.0}, {0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({-0.5f,  0.5f, -0.5f}, {-1.0,  0.0,  0.0}, {0.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({-0.5f, -0.5f, -0.5f}, {-1.0,  0.0,  0.0}, {1.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({-0.5f, -0.5f,  0.5f}, {-1.0,  0.0,  0.0}, {1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({-0.5f, -0.5f, -0.5f,}, {0.0, -1.0,  0.0}, {1.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({0.5f, -0.5f, -0.5f}, {0.0, -1.0,  0.0}, {0.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({0.5f, -0.5f,  0.5f}, {0.0, -1.0,  0.0}, {0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({-0.5f, -0.5f,  0.5f}, {0.0, -1.0,  0.0}, {1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({0.5f, -0.5f, -0.5f,}, {0.0,  0.0, -1.0}, {1.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({-0.5f, -0.5f, -0.5f}, {0.0,  0.0, -1.0}, {0.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({-0.5f,  0.5f, -0.5f}, {0.0,  0.0, -1.0}, {0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({0.5f,  0.5f, -0.5}, {0.0,  0.0, -1.0}, {1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
	};

	std::vector<Vertex> cube_vertices_brown = {
		Vertex({0.5f,  0.5f,  0.5f,}, {0.0,  0.0,  1.0}, {0.0, 0.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({-0.5f,  0.5f,  0.5f}, {0.0,  0.0,  1.0}, {1.0, 0.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({-0.5f, -0.5f,  0.5f}, {0.0,  0.0,  1.0}, {1.0, 1.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({0.5f, -0.5f,  0.5f}, {0.0,  0.0,  1.0}, {0.0, 1.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({0.5f,  0.5f,  0.5f,}, {1.0,  0.0,  0.0}, {1.0, 1.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({0.5f, -0.5f,  0.5f}, {1.0,  0.0,  0.0}, {0.0, 1.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({0.5f, -0.5f, -0.5f}, {1.0,  0.0,  0.0}, {0.0, 0.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({0.5f,  0.5f, -0.5f}, {1.0,  0.0,  0.0}, {1.0, 0.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({0.5f,  0.5f,  0.5f,}, {0.0,  1.0,  0.0}, {1.0, 1.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({0.5f,  0.5f, -0.5f}, {0.0,  1.0,  0.0}, {1.0, 0.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({-0.5f,  0.5f, -0.5f}, {0.0,  1.0,  0.0}, {0.0, 0.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({-0.5f,  0.5f,  0.5f}, {0.0,  1.0,  0.0}, {0.0, 1.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({-0.5f,  0.5f,  0.5f,}, {-1.0,  0.0,  0.0}, {0.0, 1.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({-0.5f,  0.5f, -0.5f}, {-1.0,  0.0,  0.0}, {0.0, 0.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({-0.5f, -0.5f, -0.5f}, {-1.0,  0.0,  0.0}, {1.0, 0.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({-0.5f, -0.5f,  0.5f}, {-1.0,  0.0,  0.0}, {1.0, 1.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({-0.5f, -0.5f, -0.5f,}, {0.0, -1.0,  0.0}, {1.0, 0.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({0.5f, -0.5f, -0.5f}, {0.0, -1.0,  0.0}, {0.0, 0.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({0.5f, -0.5f,  0.5f}, {0.0, -1.0,  0.0}, {0.0, 1.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({-0.5f, -0.5f,  0.5f}, {0.0, -1.0,  0.0}, {1.0, 1.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({0.5f, -0.5f, -0.5f,}, {0.0,  0.0, -1.0}, {1.0, 0.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({-0.5f, -0.5f, -0.5f}, {0.0,  0.0, -1.0}, {0.0, 0.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({-0.5f,  0.5f, -0.5f}, {0.0,  0.0, -1.0}, {0.0, 1.0}, {0.8, 0.4, 0.0, 1.0}),
		Vertex({0.5f,  0.5f, -0.5}, {0.0,  0.0, -1.0}, {1.0, 1.0}, {0.8, 0.4, 0.0, 1.0}),
	};

	std::vector<Vertex> cube_vertices_soft_brown = {
		Vertex({0.5f,  0.5f,  0.5f,}, {0.0,  0.0,  1.0}, {0.0, 0.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({-0.5f,  0.5f,  0.5f}, {0.0,  0.0,  1.0}, {1.0, 0.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({-0.5f, -0.5f,  0.5f}, {0.0,  0.0,  1.0}, {1.0, 1.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({0.5f, -0.5f,  0.5f}, {0.0,  0.0,  1.0}, {0.0, 1.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({0.5f,  0.5f,  0.5f,}, {1.0,  0.0,  0.0}, {1.0, 1.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({0.5f, -0.5f,  0.5f}, {1.0,  0.0,  0.0}, {0.0, 1.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({0.5f, -0.5f, -0.5f}, {1.0,  0.0,  0.0}, {0.0, 0.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({0.5f,  0.5f, -0.5f}, {1.0,  0.0,  0.0}, {1.0, 0.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({0.5f,  0.5f,  0.5f,}, {0.0,  1.0,  0.0}, {1.0, 1.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({0.5f,  0.5f, -0.5f}, {0.0,  1.0,  0.0}, {1.0, 0.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({-0.5f,  0.5f, -0.5f}, {0.0,  1.0,  0.0}, {0.0, 0.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({-0.5f,  0.5f,  0.5f}, {0.0,  1.0,  0.0}, {0.0, 1.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({-0.5f,  0.5f,  0.5f,}, {-1.0,  0.0,  0.0}, {0.0, 1.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({-0.5f,  0.5f, -0.5f}, {-1.0,  0.0,  0.0}, {0.0, 0.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({-0.5f, -0.5f, -0.5f}, {-1.0,  0.0,  0.0}, {1.0, 0.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({-0.5f, -0.5f,  0.5f}, {-1.0,  0.0,  0.0}, {1.0, 1.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({-0.5f, -0.5f, -0.5f,}, {0.0, -1.0,  0.0}, {1.0, 0.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({0.5f, -0.5f, -0.5f}, {0.0, -1.0,  0.0}, {0.0, 0.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({0.5f, -0.5f,  0.5f}, {0.0, -1.0,  0.0}, {0.0, 1.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({-0.5f, -0.5f,  0.5f}, {0.0, -1.0,  0.0}, {1.0, 1.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({0.5f, -0.5f, -0.5f,}, {0.0,  0.0, -1.0}, {1.0, 0.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({-0.5f, -0.5f, -0.5f}, {0.0,  0.0, -1.0}, {0.0, 0.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({-0.5f,  0.5f, -0.5f}, {0.0,  0.0, -1.0}, {0.0, 1.0}, {0.8, 0.3, 0.4, 1.0}),
		Vertex({0.5f,  0.5f, -0.5}, {0.0,  0.0, -1.0}, {1.0, 1.0}, {0.8, 0.3, 0.4, 1.0}),
	};

	std::vector<unsigned int> indices = {
		0, 1, 2, 2, 3, 0,			// v0-v1-v2-v3 (front)
		4, 5, 6, 6, 7, 4,			// v0-v3-v4-v5 (right)
		8, 9, 10, 10, 11, 8,		// v0-v5-v6-v1 (top)
		12, 13, 14, 14, 15, 12,		// v1-v6-v7-v2 (left)
		16, 17, 18, 18, 19, 16,		// v7-v4-v3-v2 (bottom)
		20, 21, 22, 22, 23, 20		// v4-v7-v6-v5 (back)
	};

	std::vector<Texture> textures;

	Mesh::BASIC_CUBE_MESH = new Mesh(cube_vertices, indices, textures);
	Mesh::BASIC_CUBE_MESH_BROWN = new Mesh(cube_vertices_brown, indices, textures);
	Mesh::BASIC_CUBE_MESH_SOFT_BROWN = new Mesh(cube_vertices_soft_brown, indices, textures);


	std::vector<Vertex> plane_vertices = {
		Vertex({0.5f,  0.5f,  0.0f}, {0.0,  0.0,  1.0}, {0.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({-0.5f,  0.5f,  0.0f}, {0.0,  0.0,  1.0}, {1.0, 0.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({-0.5f, -0.5f,  0.0f}, {0.0,  0.0,  1.0}, {1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
		Vertex({0.5f, -0.5f,  0.0f}, {0.0,  0.0,  1.0}, {0.0, 1.0}, {1.0, 1.0, 1.0, 1.0}),
	};
	
	std::vector<unsigned int> plane_indices = {
		0, 1, 2, 2, 3, 0,			// v0-v1-v2-v3 (front)
	};

	// crosshair
	Texture texture = LoadTexture("./textures", "circle.png", "texture_diffuse");

	Transform crosshair_transform = Transform::blank();
	crosshair_transform.scale(0.025);

	// menu
	Texture texture_menu = LoadTexture("./textures/menu", "Menu DEFAULT.png", "texture_diffuse");
	Texture texture_exit = LoadTexture("./textures/menu", "Menu Exit Rojo.png", "texture_diffuse");
	Texture texture_start = LoadTexture("./textures/menu", "Menu Start Pressed.png", "texture_diffuse");

	Transform menu_transform = Transform();
	menu_transform.scale(1);
	Transform exit_transform = Transform();
	menu_transform.scale(1);
	Transform start_transform = Transform();
	menu_transform.scale(1);

	Transform menu_indicator_transform = Transform::blank();
	menu_indicator_transform.scale(1.8);
	menu_indicator_transform.translate({ 0, 0, 0 });
	Menu::instance = Menu(menu_indicator_transform);
	Menu::instance
		.set_menu_default(new UIElement(menu_transform, texture_menu))
		.set_menu_exit(new UIElement(exit_transform, texture_exit))
		.set_menu_start(new UIElement(start_transform, texture_start))
		.change_indicator(MenuType::MENU);

	// interacteable
	Texture texture_sit_down = LoadTexture("./textures/ui_assets", "seure_img.png", "texture_diffuse");
	Texture texture_obrir_tancar = LoadTexture("./textures/ui_assets", "obrir_tancar_img.png", "texture_diffuse");
	Texture texture_maleta = LoadTexture("./textures/ui_assets", "maleta_img.png", "texture_diffuse");
	Texture texture_close_up = LoadTexture("./textures/ui_assets", "aproparse_img.png", "texture_diffuse");
	Texture texture_lever = LoadTexture("./textures/ui_assets", "lever_img.png", "texture_diffuse");

	Transform transform_sit = Transform();
	transform_sit.scale(0.15);
	Transform transform_open_close = Transform();
	transform_open_close.scale(0.15);
	Transform transform_maleta = Transform();
	transform_maleta.scale(0.2);
	Transform transform_close_up = Transform();
	transform_close_up.scale(0.15);
	Transform transform_lever = Transform();
	transform_lever.scale(0.18);

	Transform indicator_transform = Transform::blank();
	indicator_transform.scale(1);
	indicator_transform.translate({ 0, -0.2, 0 });
	InteractionIndicator::instance = InteractionIndicator(indicator_transform);
	InteractionIndicator::instance
		.set_sit_indicator(new UIElement(transform_sit, texture_sit_down))
		.set_maleta(new UIElement(transform_maleta, texture_maleta))
		.set_open_close_indicator(new UIElement(transform_open_close, texture_obrir_tancar))
		.set_close_up_indicator(new UIElement(transform_close_up, texture_close_up))
		.set_lever(new UIElement(transform_lever, texture_lever));

	Crosshair::instance = Crosshair(crosshair_transform, texture);

	UI::instance.elements.push_back(&Crosshair::instance);
	UI::instance.elements.push_back(&InteractionIndicator::instance);
	UI::instance.elements.push_back(&Menu::instance);


	//Mesh::CROSSHAIR = new Mesh(plane_vertices, plane_indices, plane_textures);

	string path = "./textures/maya/maya.obj"; //ruta del objeto
	Model::BACKPACK = new Model(path); //crear nuevo modelo

	std::cout << "shader ID:" << shaderGouraud.getProgramID() << std::endl;
	
	Level::buildFirstLevel(shaderGouraud.getProgramID());
	Level::exterior_train_offset(shaderGouraud.getProgramID(), exterior_offset_inicial);
	Level::slender_offset(shaderGouraud.getProgramID(), slenderman_offset);

	Level::CURRENT_LEVEL.llumAmbient = &llum_ambient;
	Level::CURRENT_LEVEL.iFixe = &ifixe;

	irrklang::ISound* backgroundSound = Audio::AUDIO_FUNCTIONS.play2D("./media/movingTrain.mp3", true, true);
	if (!backgroundSound)
	{
		std::cout << "Could not play sound" << std::endl;
	}
	else
	{
		if (backgroundSound->getIsPaused()) {
			backgroundSound->setVolume(0.25f);
			backgroundSound->setIsPaused(false);
		}
	}

// Loop until the user closes the window

	irrklang::ISound* steps = soundEngine->play2D("../EntornVGI/media/Footsteps.mp3", true, true, true);
	if (!steps)
		cout << "Error al crear el so" << endl;

	bool start = true;
	float trasX = 0;
    while (!glfwWindowShouldClose(window))
    {
// Poll for and process events */
//        glfwPollEvents();

// Entorn VGI. Timer: common part, do this only once
		now = glfwGetTime();
		delta = now - previous;
		previous = now;

		float v = -30;

		if (Level::CURRENT_LEVEL.slenderman->my_transform.position().x < 10)
		{
			Level::CURRENT_LEVEL.slenderman->my_transform.translate(vec3(0.5,0, 0));
		}

		//railes
		
		Level::CURRENT_LEVEL.via->update(delta);
		Level::CURRENT_LEVEL.via_secundaria->update(delta);
		Level::CURRENT_LEVEL.terreny->update(delta);
		Level::CURRENT_LEVEL.tren_passant->update(delta);

// // Entorn VGI. Timer: for each timer do this
		time -= delta;
		if ((time <= 0.0) && (satelit || anima)) OnTimer();



		glm::vec3 direction = glm::normalize(glm::vec3(
			cos(Camera::MAIN_CAMERA.horizontal_angle),
			sin(Camera::MAIN_CAMERA.horizontal_angle),
			0
		));

		glm::vec3 left = glm::normalize(glm::vec3(
			cos(Camera::MAIN_CAMERA.horizontal_angle + PI / 2),
			sin(Camera::MAIN_CAMERA.horizontal_angle + PI / 2),
			0
		));

		vec3 old_position = Camera::MAIN_CAMERA.position;

		if (w_pressed || s_pressed || d_pressed || a_pressed)
		{
			steps->setIsPaused(false);
		}
		else
		{
			steps->setIsPaused(true);
		}

		btVector3 velocity(0, 0, 0);
		
		if (w_pressed)
		{
			velocity.setX(velocity.x() + direction.x * Camera::MAIN_CAMERA.move_speed);
			velocity.setY(velocity.y() + direction.y * Camera::MAIN_CAMERA.move_speed);
		}
		if (s_pressed)
		{
			velocity.setX(velocity.x() - direction.x * Camera::MAIN_CAMERA.move_speed);
			velocity.setY(velocity.y() - direction.y * Camera::MAIN_CAMERA.move_speed);
		}

		if (a_pressed)
		{
			velocity.setX(velocity.x() + left.x * Camera::MAIN_CAMERA.move_speed);
			velocity.setY(velocity.y() + left.y * Camera::MAIN_CAMERA.move_speed);
		}
		if (d_pressed)
		{
			velocity.setX(velocity.x() - left.x * Camera::MAIN_CAMERA.move_speed);
			velocity.setY(velocity.y() - left.y * Camera::MAIN_CAMERA.move_speed);
		}
		
		if (c_pressed)
		{
			if (Camera::MAIN_CAMERA.position.z > 1) Camera::MAIN_CAMERA.position.z -= 2 * delta;
		}
		else if (Camera::MAIN_CAMERA.position.z < 1.8 && !Camera::MAIN_CAMERA.sit)
		{
			Camera::MAIN_CAMERA.position.z += 2 * delta;
		}

		if (Camera::MAIN_CAMERA.flying && !Camera::MAIN_CAMERA.endcam)
		{
			Camera::MAIN_CAMERA.horizontal_angle += Camera::MAIN_CAMERA.angular_speed;
			Camera::MAIN_CAMERA.fly_arround(glm::vec3(0, 0, 0));
		}

		Camera::MAIN_CAMERA.my_rigid_body->activate();
		Camera::MAIN_CAMERA.my_rigid_body->setGravity({0, 0, 0});
		Camera::MAIN_CAMERA.my_rigid_body->setLinearVelocity(velocity);

		Camera::MAIN_CAMERA.syncColliders();
		BulletWorld::WORLD->simulate(delta * 10);
		
		btTransform trans;
		Camera::MAIN_CAMERA.my_rigid_body->getMotionState()->getWorldTransform(trans);

		if (!Camera::MAIN_CAMERA.sit && !Camera::MAIN_CAMERA.zoom)
		{
			Camera::MAIN_CAMERA.position.x = trans.getOrigin().getX();
			Camera::MAIN_CAMERA.position.y = trans.getOrigin().getY();
			//Camera::MAIN_CAMERA.position.z = trans.getOrigin().getZ();
		}

		if (Camera::MAIN_CAMERA.zoom || Camera::MAIN_CAMERA.flying && !Camera::MAIN_CAMERA.endcam)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else 
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
		
		skybox_offset.x -= delta * 450;
		if (skybox_offset.x <= -2200)
			skybox_offset.x = 2200;
		
		//skybox_offset.x = 0;


// Crida a OnPaint() per redibuixar l'escena
		OnPaint(window);

// Intercanvia l'escena al front de la pantalla
	//	glfwSwapBuffers(window);

// Poll for and process events
		glfwPollEvents();
		if (start)
		{
			start = false;
			// INICIAR TOT
			OnKeyDown(window, GLFW_KEY_P, 1, GLFW_PRESS, 1);
			OnKeyDown(window, GLFW_KEY_L, 1, GLFW_PRESS, 1);
			OnKeyDown(window, GLFW_KEY_K, 1, GLFW_PRESS, 1);
			OnKeyDown(window, GLFW_KEY_Z, 1, GLFW_PRESS, 1);
			OnKeyDown(window, GLFW_KEY_F3, 1, GLFW_PRESS, 2);
			OnKeyDown(window, GLFW_KEY_P, 1, GLFW_PRESS, 0);
			OnKeyDown(window, GLFW_KEY_F, 1, GLFW_PRESS, 0);
			OnKeyDown(window, GLFW_KEY_F, 1, GLFW_PRESS, 1);

		}
    }

// Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glfwDestroyWindow(window);

// Terminating GLFW: Destroy the windows, monitors and cursor objects
    glfwTerminate();

	if (shaderGouraud.getProgramID()!=-1) shaderGouraud.DeleteProgram();
	if (shaderPhong.getProgramID() != -1) shaderPhong.DeleteProgram();
	if (shaderFiles.getProgramID() != -1) shaderFiles.DeleteProgram();
	if (shaderSkyBox.getProgramID() != -1) shaderSkyBox.DeleteProgram();


	delete Mesh::BASIC_CUBE_MESH;

	// After we are finished, we have to delete the irrKlang Device created earlier
	// with createIrrKlangDevice(). Use ::drop() to do that. In irrKlang, you should
	// delete all objects you created with a method or function that starts with 'create'.
	// (an exception is the play2D()- or play3D()-method, see the documentation or the
	// next example for an explanation)
	// The object is deleted simply by calling ->drop().

	if (backgroundSound) {
		backgroundSound->drop();
	}
	
	//audio.~audio();

    return 0;
}