//C00242944
//Niamh Andrews
//Helped by Michael Rainsford Ryan

#include <Game.h>

static bool flip;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube Vertex and Fragment Shaders")
{

}

Game::~Game() {}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[4];
} Vertex;

Vertex vertex[8];
GLubyte triangles[36];

/* Variable to hold the VBO identifier and shader data */
GLuint	index, //Index to draw
vsid, //Vertex Shader ID
fsid, //Fragment Shader ID
progID, //Program ID
vbo = 1, // Vertex Buffer ID
positionID, //Position ID
colorID; // Color ID


void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;



	glEnable(GL_CULL_FACE);



	glewInit();

	// Vertices counter-clockwise winding
	vertex[0].coordinate[0] = -1.0f;
	vertex[0].coordinate[1] = -1.0f;
	vertex[0].coordinate[2] = 1.0f;

	vertex[1].coordinate[0] = 1.0f;
	vertex[1].coordinate[1] = -1.0f;
	vertex[1].coordinate[2] = 1.0f;

	vertex[2].coordinate[0] = 1.0f;
	vertex[2].coordinate[1] = 1.0f;
	vertex[2].coordinate[2] = 1.0f;

	vertex[3].coordinate[0] = -1.0f;
	vertex[3].coordinate[1] = 1.0f;
	vertex[3].coordinate[2] = 1.0f;

	vertex[4].coordinate[0] = -1.0f;
	vertex[4].coordinate[1] = -1.0f;
	vertex[4].coordinate[2] = -1.0f;

	vertex[5].coordinate[0] = 1.0f;
	vertex[5].coordinate[1] = -1.0f;
	vertex[5].coordinate[2] = -1.0f;

	vertex[6].coordinate[0] = 1.0f;
	vertex[6].coordinate[1] = 1.0f;
	vertex[6].coordinate[2] = -1.0f;

	vertex[7].coordinate[0] = -1.0f;
	vertex[7].coordinate[1] = 1.0f;
	vertex[7].coordinate[2] = -1.0f;





	vertex[0].color[0] = 0.5f;
	vertex[0].color[1] = 0.0f;
	vertex[0].color[2] = 0.5f;
	vertex[0].color[3] = 1.0f;

	vertex[1].color[0] = 0.5f;
	vertex[1].color[1] = 0.0f;
	vertex[1].color[2] = 0.5f;
	vertex[1].color[3] = 1.0f;

	vertex[2].color[0] = 0.5f;
	vertex[2].color[1] = 0.0f;
	vertex[2].color[2] = 0.5f;
	vertex[2].color[3] = 1.0f;

	vertex[0].color[0] = 0.9f;
	vertex[0].color[1] = 0.3f;
	vertex[0].color[2] = 0.0f;
	vertex[0].color[3] = 1.0f;

	vertex[1].color[0] = 0.7f;
	vertex[1].color[1] = 0.0f;
	vertex[1].color[2] = 0.5f;
	vertex[1].color[3] = 1.0f;

	vertex[2].color[0] = 0.0f;
	vertex[2].color[1] = 0.6f;
	vertex[2].color[2] = 0.6f;
	vertex[2].color[3] = 1.0f;

	vertex[3].color[0] = 0.4f;
	vertex[3].color[1] = 0.9f;
	vertex[3].color[2] = 0.0f;
	vertex[3].color[3] = 1.0f;

	vertex[4].color[0] = 0.6f;
	vertex[4].color[1] = 0.6f;
	vertex[4].color[2] = 0.0f;
	vertex[4].color[3] = 1.0f;

	vertex[5].color[0] = 0.4f;
	vertex[5].color[1] = 0.0f;
	vertex[5].color[2] = 0.7f;
	vertex[5].color[3] = 1.0f;

	vertex[6].color[0] = 0.0f;
	vertex[6].color[1] = 0.0f;
	vertex[6].color[2] = 0.9f;
	vertex[6].color[3] = 1.0f;

	vertex[7].color[0] = 0.7f;
	vertex[7].color[1] = 0.3f;
	vertex[7].color[2] = 0.4f;
	vertex[7].color[3] = 1.0f;






	/*Index of Poly / Triangle to Draw */
	triangles[0] = 0;   triangles[1] = 1;	triangles[2] = 2;
	triangles[3] = 2;   triangles[4] = 3;	triangles[5] = 0;
	triangles[6] = 3;	triangles[7] = 7;	triangles[8] = 4;
	triangles[9] = 4;   triangles[10] = 0;	triangles[11] = 3;
	triangles[12] = 4;   triangles[13] = 7;	triangles[14] = 6;
	triangles[15] = 6;	triangles[16] = 5;	triangles[17] = 4;
	triangles[18] = 6;   triangles[19] = 2;	triangles[20] = 1;
	triangles[21] = 1;	triangles[22] = 5;	triangles[23] = 6;
	triangles[24] = 6;	triangles[25] = 7;	triangles[26] = 3;
	triangles[27] = 3;	triangles[28] = 2;	triangles[29] = 6;
	triangles[30] = 0;	triangles[31] = 4;	triangles[32] = 5;
	triangles[33] = 5;	triangles[34] = 1;	triangles[35] = 0;

	for (int i = 0; i < 8; i++)
	{
		Vector3 vector{ vertex[i].coordinate[0],vertex[i].coordinate[1],vertex[i].coordinate[2] };

		vector = Matrix3::Scale3D(50.0f/*, 50.0f*/) * vector;

		vertex[i].coordinate[0] = vector.x;
		vertex[i].coordinate[1] = vector.y;
		vertex[i].coordinate[2] = vector.z;
	}

	/* Create a new VBO using VBO id */
	glGenBuffers(1, &vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Vertex Shader which would normally be loaded from an external file */
	const char* vs_src = "#version 400\n\r"
		"in vec4 sv_position;"
		"in vec4 sv_color;"
		"out vec4 color;"
		"void main() {"
		"	color = sv_color;"
		"	gl_Position = sv_position;"
		"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar * *)& vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader which would normally be loaded from an external file */
	const char* fs_src = "#version 400\n\r"
		"in vec4 color;"
		"out vec4 fColor;"
		"void main() {"
		"	fColor = color + vec4(0.7f, 0.0f, 0.0f, 0.3f);"
		"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar * *)& fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	// Find variables in the shader
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f / 60.0f)
	{
		clock.restart();


		//Rotate Right
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
		{
			for (int i = 0; i < 8; i++)
			{
				Vector3 vector{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
				vector = Matrix3::RotationY(0.8) * vector;
				vertex[i].coordinate[0] = vector.x;
				vertex[i].coordinate[1] = vector.y;
				vertex[i].coordinate[2] = vector.z;
			}
		}
		//Rotate Left
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
		{
			for (int i = 0; i < 8; i++)
			{
				Vector3 vector{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
				vector = Matrix3::RotationY(-0.8) * vector;
				vertex[i].coordinate[0] = vector.x;
				vertex[i].coordinate[1] = vector.y;
				vertex[i].coordinate[2] = vector.z;
			}
		}
		//Rotate Up
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
		{
			for (int i = 0; i < 8; i++)
			{
				Vector3 vector{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
				vector = Matrix3::RotationX(0.8) * vector;
				vertex[i].coordinate[0] = vector.x;
				vertex[i].coordinate[1] = vector.y;
				vertex[i].coordinate[2] = vector.z;
			}
		}
		//Rotate Down
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
		{
			for (int i = 0; i < 8; i++)
			{
				Vector3 vector{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
				vector = Matrix3::RotationX(-0.8) * vector;
				vertex[i].coordinate[0] = vector.x;
				vertex[i].coordinate[1] = vector.y;
				vertex[i].coordinate[2] = vector.z;
			}
		}



		//Increase Scale
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)))
		{
			for (int i = 0; i < 8; i++)
			{
				Vector3 vector{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };

				vector = Matrix3::Scale3D(110.0f) * vector;
				vertex[i].coordinate[0] = vector.x;
				vertex[i].coordinate[1] = vector.y;
				vertex[i].coordinate[2] = vector.z;
			}
		}
		//Decrease Scale
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)))
		{
			for (int i = 0; i < 8; i++)
			{
				Vector3 vector{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };

				vector = Matrix3::Scale3D(90.0f) * vector;
				vertex[i].coordinate[0] = vector.x;
				vertex[i].coordinate[1] = vector.y;
				vertex[i].coordinate[2] = vector.z;
			}
		}



		//Translate +
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Period)))
		{
			for (int i = 0; i < 8; i++)
			{
				Vector3 vector{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };

				float tempZ = vector.z;
				vector.z = 1;
				vector = Matrix3::Translate(0.05f, 0.05f) * vector;
				vector.z = tempZ;
				vertex[i].coordinate[0] = vector.x;
				vertex[i].coordinate[1] = vector.y;
			}
		}
		//Translate -
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)))
		{
			for (int i = 0; i < 8; i++)
			{
				Vector3 vector{ vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };

				float tempZ = vector.z;
				vector.z = 1;
				vector = Matrix3::Translate(-0.05f, -0.05f) * vector;
				vector.z = tempZ;
				vertex[i].coordinate[0] = vector.x;
				vertex[i].coordinate[1] = vector.y;
			}
		}






	}



#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif

}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/

		// Set pointers for each parameter
		// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)NULL + 3);

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, &vbo);
}
