#include "OpegGLImplement.h"

OpenGlImplement::OpenGlImplement(){
}

void OpenGlImplement::setSDLWindow(SDL_Window *window){
	this->window = window;
}

void OpenGlImplement::InitGL()
{
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)SDL_GL_GetProcAddress("glAttachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)SDL_GL_GetProcAddress("glLinkProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC)SDL_GL_GetProcAddress("glUseProgram");
	glCreateShader = (PFNGLCREATESHADERPROC)SDL_GL_GetProcAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)SDL_GL_GetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)SDL_GL_GetProcAddress("glCompileShader");
	glBindBuffer = (PFNGLBINDBUFFERPROC)SDL_GL_GetProcAddress("glBindBuffer");
	glGenBuffers = (PFNGLGENBUFFERSPROC)SDL_GL_GetProcAddress("glGenBuffers");
	glBufferData = (PFNGLBUFFERDATAPROC)SDL_GL_GetProcAddress("glBufferData");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)SDL_GL_GetProcAddress("glDeleteProgram");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)SDL_GL_GetProcAddress("glDisableVertexAttribArray");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)SDL_GL_GetProcAddress("glEnableVertexAttribArray");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)SDL_GL_GetProcAddress("glGetAttribLocation");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)SDL_GL_GetProcAddress("glGetUniformLocation");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)SDL_GL_GetProcAddress("glGetProgramiv");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)SDL_GL_GetProcAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)SDL_GL_GetProcAddress("glGetShaderInfoLog");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)SDL_GL_GetProcAddress("glGetProgramInfoLog");
	glIsShader = (PFNGLISSHADERPROC)SDL_GL_GetProcAddress("glIsShader");
	glIsProgram = (PFNGLISPROGRAMPROC)SDL_GL_GetProcAddress("glIsProgram");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)SDL_GL_GetProcAddress("glVertexAttribPointer");
	glActiveTexture = (PFNGLACTIVETEXTUREPROC)SDL_GL_GetProcAddress("glActiveTexture");
	glUniform1i = (PFNGLUNIFORM1IPROC)SDL_GL_GetProcAddress("glUniform1i");
}

void OpenGlImplement::InitShaders()
{
	/////CHECK VERSION OF OPENGL/////
	//char message [200];
	//strcpy (message, (char *)glGetString(GL_VERSION));
	//strcat (message, "\n\nEs necesario tener la versinn 3.2 para que funcione adecuadamente.\nSi no es tu caso, actualiza tus Driver de video.\nPrecione ENTER para continuar. ");
	//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"OpenGL Version: ",	(const char *)message,NULL);
	
	//Success flag
	bool success = true;

	//Generate program
	shaderProgram = glCreateProgram();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Read shaders
	std::string vertShaderStr = readFile("vertex.glsl");
	std::string fragShaderStr = readFile("fragment.glsl");
	const GLchar *vertexShaderSource = vertShaderStr.c_str();
	const GLchar *fragmentShaderSource = fragShaderStr.c_str();
		
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE)
		printf("Unable to compile vertex shader %d!\n", vertexShader);
	glAttachShader(shaderProgram, vertexShader);


	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	GLint fShaderCompiled = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
	if (fShaderCompiled != GL_TRUE)
		printf("Unable to compile fragment shader %d!\n", fragmentShader);
	glAttachShader(shaderProgram, fragmentShader);


	glLinkProgram(shaderProgram);
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &programSuccess);
		
	if (programSuccess != GL_TRUE)
		printf("Error linking program %d!\n", shaderProgram);
		
	//Get vertex attribute location
	vertexPositionAttribute = glGetAttribLocation(shaderProgram, "aVertexPosition");
	vertexTextureCoordAttribute = glGetAttribLocation(shaderProgram, "aTextureCoord");
	samplerUniform = glGetUniformLocation(shaderProgram, "uSampler");
	
	//Initialize clear color
	glClearColor(0.6f, 0.6f, 0.6f, 1.f);
	glViewport(0, 0, WIDTH_SCREEN, HEIGHT_SCREEN);

	//glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_ALWAYS);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

void OpenGlImplement::InitBuffers(GLuint* vertexBufferObject, GLuint* indexBufferObject, GLuint* textureBufferObject, GLfloat* vexterPositions, GLuint vertexDataLen, GLuint* indexData, GLuint indexDataLen, GLfloat* textureData, GLuint textureDataLen){
	//Create VBO
	glGenBuffers(1, vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, *vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertexDataLen, vexterPositions, GL_STATIC_DRAW);

	//Create IBO
	glGenBuffers(1, indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataLen, indexData, GL_STATIC_DRAW);

	//Create Texture
	glGenBuffers(1, textureBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, *textureBufferObject);
	glBufferData(GL_ARRAY_BUFFER, textureDataLen, textureData, GL_STATIC_DRAW);

}

void OpenGlImplement::QuitShaders()
{
	//Deallocate program
	glDeleteProgram(shaderProgram);
	//Destroy window	
	SDL_DestroyWindow(window);
	window = NULL;
	//Quit SDL subsystems
	SDL_Quit();
}

void OpenGlImplement::DrawStart()
{
	glMatrixMode(GL_PROJECTION);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.999999, 30.0);
	glTranslatef(-1.0f, 1.0f, -2.00f);
}

GLfloat OpenGlImplement::ConvertCOORDf(GLfloat x){
	return ((GLfloat)x * 2.0f) / (GLfloat)WIDTH_SCREEN;
}

GLfloat OpenGlImplement::ConvertCOORDInvf(GLfloat x){
	return ((GLfloat)x / 2.0f) * (GLfloat)WIDTH_SCREEN;
}

/* The main drawing function. */
void  OpenGlImplement::Draw(GLuint* vertexBufferObject, GLuint* indexBufferObject, GLuint* textureBufferObject, GLuint textureObject, GLfloat translate_x, GLfloat translate_y, GLfloat translate_z, GLfloat rotate_x, GLfloat rotate_y, GLfloat rotate_z, GLfloat scale_x, GLfloat scale_y, GLfloat scale_z, GLuint size)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(ConvertCOORDf(translate_x), -ConvertCOORDf(translate_y), translate_z);
	glRotatef(rotate_x, 1.f, 0.f, 0.f);
	glRotatef(rotate_y, 0.f, 1.f, 0.f);
	glRotatef(rotate_z, 0.f, 0.f, 1.f);

	glScalef(scale_x, scale_y, scale_z);
	//Bind program
	glUseProgram(shaderProgram);
	//Enable vertex position
	glEnableVertexAttribArray(vertexPositionAttribute);
	glEnableVertexAttribArray(vertexTextureCoordAttribute);

	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, *vertexBufferObject);
	glVertexAttribPointer(vertexPositionAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	//Set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, *textureBufferObject);
	glVertexAttribPointer(vertexTextureCoordAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureObject);
	//glUniform1i(samplerUniform, 0);
	
	glDrawElements(GL_TRIANGLE_STRIP, size, GL_UNSIGNED_INT, NULL);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//Disable vertex position
	glDisableVertexAttribArray(vertexTextureCoordAttribute);
	glDisableVertexAttribArray(vertexPositionAttribute);

	
	//Unbind program
	glUseProgram(NULL);
	
}

void OpenGlImplement::DrawEnd()
{
	SDL_GL_SwapWindow(window);
}

OpenGlImplement::~OpenGlImplement(){
	glDeleteProgram(shaderProgram);
	SDL_DestroyWindow(window);
	window = NULL;
}

std::string OpenGlImplement::readFile(const char *filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

GLuint OpenGlImplement::LoadTexture(SDL_Surface * surface, GLuint x, GLuint y, GLuint w, GLuint h)
{
	GLuint texture;
	SDL_Surface *image;
	SDL_Rect area;

	image = SDL_CreateRGBSurface(SDL_SWSURFACE, surface->w, surface->h, 32, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);

	area.x = 0;
	area.y = 0;
	area.w = surface->w;
	area.h = surface->h;
	SDL_BlitSurface(surface, &area, image, &area);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
	SDL_FreeSurface(image);

	return texture;
}