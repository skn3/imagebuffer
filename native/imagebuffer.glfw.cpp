// --- forward references ---
extern gxtkGraphics* bb_graphics_renderDevice;
extern gxtkGraphics* bb_graphics_device;
extern int bb_graphics_BeginRender();
extern int bb_graphics_SetScissor(Float t_x,Float t_y,Float t_width,Float t_height);



// --- gl stuff ---
typedef char GLchar;

void(__stdcall*glGenFramebuffers)(GLsizei n, GLuint* framebuffers);
void(__stdcall*glBindFramebuffer)(GLenum target, GLuint framebuffer);
void(__stdcall*glFramebufferTexture)(GLenum target, GLenum attachment, GLuint texture, GLint level);
GLenum(__stdcall*glCheckFramebufferStatus)(GLenum target);
void(__stdcall*glDeleteFramebuffers)(GLsizei n, const GLuint* framebuffers);
void(__stdcall*glGenRenderbuffers)(GLsizei n, GLuint* renderbuffers);
void(__stdcall*glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
void(__stdcall*glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
void(__stdcall*glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
void(__stdcall*glDeleteRenderbuffers)(GLsizei n, const GLuint* renderbuffers);
GLuint(__stdcall*glCreateShader)(GLenum type);
void(__stdcall*glShaderSource)(GLuint shader, GLsizei count, const GLchar** string, const GLint* length);
void(__stdcall*glCompileShader)(GLuint shader);
void(__stdcall*glGetProgramiv)(GLuint program, GLenum pname, GLint* params);
void(__stdcall*glGetShaderiv)(GLuint shader, GLenum pname, GLint* params);
void(__stdcall*glGetShaderInfoLog)(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog);
GLuint(__stdcall*glCreateProgram)(void);
void(__stdcall*glAttachShader)(GLuint program, GLuint shader);
void(__stdcall*glDetachShader)(GLuint program, GLuint shader);
void(__stdcall*glLinkProgram)(GLuint program);
void(__stdcall*glUseProgram)(GLuint program);
void(__stdcall*glGetShaderSource)(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source);



#define GL_FRAMEBUFFER 0x8D40
#define GL_RENDERBUFFER 0x8D41
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_DEPTH_ATTACHMENT 0x8D00
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_DEPTH_COMPONENT16 0x81A5
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_COMPILE_STATUS 0x8B81
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_ATTACHED_SHADERS 0x8B85
#define GL_SHADER_SOURCE_LENGTH 0x8B88



// --- globals / constants ---
#define GRAPHICS_CAPABILITY_IMAGE_BUFFERS 1
#define GRAPHICS_CAPABILITY_SHADERS 2

static bool capabilitySupportedImageBuffers = false;
static bool capabilitySupportedShaders = false;

static bool capabilityLoadedImageBuffers = false;
static bool capabilityLoadedShaders = false;



// --- functions ---
static int CheckGraphicsCapability(int capability) {
	// --- return if the device supports certain abilities ---
	switch(capability) {
		case GRAPHICS_CAPABILITY_IMAGE_BUFFERS:
			return glfwExtensionSupported("GL_ARB_framebuffer_object");
			break;
			
		case GRAPHICS_CAPABILITY_SHADERS:
			return glfwExtensionSupported("GL_ARB_shading_language_100") && glfwExtensionSupported("GL_ARB_vertex_shader") && glfwExtensionSupported("GL_ARB_fragment_shader");
			break;
	}
	
	//default no
	return 0;
}

static void LoadGraphicsCapability(int capability) {
	// --- this will load a capability ---
	//these will only ever be loaded once, obviously.
	
	//do speciffic loading
	switch(capability) {
		case GRAPHICS_CAPABILITY_IMAGE_BUFFERS:
			if (capabilityLoadedImageBuffers == false) {
				capabilityLoadedImageBuffers = true;
				
				if (CheckGraphicsCapability(GRAPHICS_CAPABILITY_IMAGE_BUFFERS)) {
					//supported
					capabilitySupportedImageBuffers = true;
					
					//load extensions
					(void*&)glGenFramebuffers=(void*)glfwGetProcAddress("glGenFramebuffers");
					(void*&)glBindFramebuffer=(void*)glfwGetProcAddress("glBindFramebuffer");
					(void*&)glFramebufferTexture=(void*)wglGetProcAddress("glFramebufferTexture");
					(void*&)glCheckFramebufferStatus=(void*)wglGetProcAddress("glCheckFramebufferStatus");
					(void*&)glDeleteFramebuffers=(void*)wglGetProcAddress("glDeleteFramebuffers");
					(void*&)glGenRenderbuffers=(void*)wglGetProcAddress("glGenRenderbuffers");
					(void*&)glRenderbufferStorage=(void*)wglGetProcAddress("glRenderbufferStorage");
					(void*&)glFramebufferRenderbuffer=(void*)wglGetProcAddress("glFramebufferRenderbuffer");
					(void*&)glBindRenderbuffer=(void*)wglGetProcAddress("glBindRenderbuffer");
					(void*&)glDeleteRenderbuffers=(void*)wglGetProcAddress("glDeleteRenderbuffers");
		
				} else {
					//not supported
					capabilitySupportedImageBuffers = false;
				}
			}
			break;
			
		case GRAPHICS_CAPABILITY_SHADERS:
			if (capabilityLoadedShaders == false) {
				capabilityLoadedShaders = true;
				
				if (CheckGraphicsCapability(GRAPHICS_CAPABILITY_SHADERS)) {
					//supported
					capabilitySupportedShaders = true;
					
					//load extensions
					(void*&)glCreateShader=(void*)wglGetProcAddress("glCreateShader");
					(void*&)glShaderSource=(void*)wglGetProcAddress("glShaderSource");
					(void*&)glCompileShader=(void*)wglGetProcAddress("glCompileShader");
					(void*&)glGetProgramiv=(void*)wglGetProcAddress("glGetProgramiv");
					(void*&)glGetShaderiv=(void*)wglGetProcAddress("glGetShaderiv");
					(void*&)glGetShaderInfoLog=(void*)wglGetProcAddress("glGetShaderInfoLog");
					(void*&)glCreateProgram=(void*)wglGetProcAddress("glCreateProgram");
					(void*&)glAttachShader=(void*)wglGetProcAddress("glAttachShader");
					(void*&)glDetachShader=(void*)wglGetProcAddress("glDetachShader");
					(void*&)glLinkProgram=(void*)wglGetProcAddress("glLinkProgram");
					(void*&)glUseProgram=(void*)wglGetProcAddress("glUseProgram");
					(void*&)glGetShaderSource=(void*)wglGetProcAddress("glGetShaderSource");
					
				} else {
					//not supported
					capabilitySupportedShaders = false;
				}
			}
			break;
	}
	
	//do shared loading (required for gl functions used by multiple capabilities)
	//none yet
}



// --- Shader header ---
class ShaderNative : public Object {
	public:
	ShaderNative();
	
	GLuint shader;
	String compileError;
	bool valid;
	
	bool _Init(int type);
	bool _SetSource(String source);
	String _GetError();
	bool _IsValid();
	bool _HasSource();
};



// --- ShaderProgram header ---
class ShaderProgramNative : public Object {
	public:
	ShaderProgramNative();
	
	static bool startLocked;
	
	GLuint program;
	bool used;
	
	bool _Init();
	bool _Attach(ShaderNative *shader);
	bool _Detach(ShaderNative *shader);
	bool _Link();
	bool _Start();
	bool _Finish();
};



// --- FBO header ---
class FBONative : public Object {
	public:
	FBONative();
	
	static bool startLocked;
	static bool onRenderActive;
	
	GLuint fbo;
	GLuint depthBuffer;
	GLuint texture;
	int width;
	int height;
	bool bound;
	bool attached;
	int deviceWidth;
	int deviceHeight;
	
	bool _Init();
	bool _Free();
	bool _Attach(gxtkSurface *surface);
	bool _Detach();
	bool _Start();
	bool _Finish();
	bool _Clear(float r,float g, float b,float a);
};



// --- Shader class ---
//constructor/destructor
ShaderNative::ShaderNative() {
	shader = 0;
	compileError = String();
	valid = false;
}

bool ShaderNative::_Init(int type) {
	// --- init the shader ---
	//make sure capabilities are loaded
	LoadGraphicsCapability(GRAPHICS_CAPABILITY_SHADERS);
	
	//are we supported?
	if (capabilitySupportedShaders) {
		//convert monkey shader type
		GLenum shaderType;
		switch(type) {
			case 1://VERTEX_SHADER
				shaderType = GL_VERTEX_SHADER;
				break;
			case 2://FRAGMENT_SHADER
				shaderType = GL_FRAGMENT_SHADER;
				break;
			default:
				//fail
				return false;
				break;
		}
		
		//create the shader
		shader = glCreateShader(shaderType);
		if (shader == 0) { return false; }
		
		//success
		return true;
	}
	
	//fail
	return false;
}

bool ShaderNative::_SetSource(String source) {
	// --- set the shaders source ---
	valid = false;
	
	if (capabilitySupportedShaders) {
		//convert monkey string into char
		const GLchar *theSource = source.ToCString<GLchar>();
		
		//set the shaders source
		glShaderSource(shader,1,&theSource,NULL);
		
		//compile the source
		glCompileShader(shader);
		
		//free the source
		delete theSource;
		
		//check if the shader compiled
		GLint compiled;
		glGetProgramiv(shader, GL_COMPILE_STATUS, &compiled);
		if (compiled == 0) {
			//failed
			//get the compile error
			GLint blen = 0;	
			GLsizei slen = 0;

			glGetShaderiv(shader, GL_INFO_LOG_LENGTH , &blen);       
			if (blen > 1) {
				//has error
 				GLchar* compilerLog = (GLchar*)malloc(blen);
 				glGetShaderInfoLog(shader, blen, &slen, compilerLog);
				compileError = String(compilerLog);
 				delete compilerLog;
			} else {
				//no error
				compileError = String();
			}
			
			//fail
			return false;
		}
		
		//success
		valid = true;
		return true;
	}
	
	//fail
	return false;
}

String ShaderNative::_GetError() {
	// --- return the last compile error ---
	return compileError;
}

bool ShaderNative::_IsValid() {
	// --- return true if the shader is valid ---
	return capabilitySupportedShaders && valid;
}

bool ShaderNative::_HasSource() {
	// --- return true if the shader has source ---
	if (capabilitySupportedShaders && valid) {
		GLint size = 0;
		glGetShaderiv(shader,GL_SHADER_SOURCE_LENGTH,&size);
		
		//take into account null terminated string (should probably fix this?)
		return size<=1?false:true;
	}
	
	//fail
	return false;
}



// --- ShaderProgram class ---
bool ShaderProgramNative::startLocked = false;

//constructor/destructor
ShaderProgramNative::ShaderProgramNative() {
	used = false;
}

bool ShaderProgramNative::_Init() {
	// --- init the shaderprogram ---
	//make sure capabilities are loaded
	LoadGraphicsCapability(GRAPHICS_CAPABILITY_SHADERS);
	
	//are we supported?
	if (capabilitySupportedShaders) {
		//create the program
		program = glCreateProgram();
		if (program == 0) {
			//fail
			return false;
		}
		
		//success
		return true;
	}
	
	//fail
	return false;
}

bool ShaderProgramNative::_Attach(ShaderNative *shader) {
	// --- attach a ahder to the program ---
	//are we supported?
	if (capabilitySupportedShaders) {
		//attach
		glAttachShader(program,shader->shader);
		
		//check for error
		if (glGetError() != GL_NO_ERROR) { return false; }
		
		//success
		return true;
	}
	
	//fail
	return false;
}

bool ShaderProgramNative::_Detach(ShaderNative *shader) {
	// --- detach a ahder from the program ---
	//are we supported?
	if (capabilitySupportedShaders) {
		//attach
		glDetachShader(program,shader->shader);
		
		//check for error
		if (glGetError() != GL_NO_ERROR) { return false; }
		
		//success
		return true;
	}
	
	//fail
	return false;
}

bool ShaderProgramNative::_Link() {
	// --- link shaders into program ---
	//are we supported?
	if (capabilitySupportedShaders) {
		//attach
		glLinkProgram(program);
		
		//check for error
		if (glGetError() != GL_NO_ERROR) { return false; }
		
		//success
		return true;
	}
	
	//fail
	return false;	
}

bool ShaderProgramNative::_Start() {
	// --- use program ---
	//are we supported?
	if (capabilitySupportedShaders && startLocked == false && used == false) {
		//make monkey flush itself
		bb_graphics_renderDevice->Flush();
		
		//use program
		glUseProgram(program);
		
		//check for error
		if (glGetError() != GL_NO_ERROR) { return false; }
		
		//flag using
		used = true;
		startLocked = true;
		
		//success
		return true;
	}
	
	//fail
	return false;	
}

bool ShaderProgramNative::_Finish() {
	// --- stop using this program ---
	if (used) {
		//make monkey flush itself
		bb_graphics_renderDevice->Flush();
		
		//unuse program
		glUseProgram(0);
	
		used = false;
		startLocked = false;
			
		//check for error
		if (glGetError() != GL_NO_ERROR) { return false; }
			
		//success
		return true;
	}
	
	//fail
	return false;
}



// --- FBO class ---
bool FBONative::startLocked = false;
bool FBONative::onRenderActive = false;

//constructor/destructor
FBONative::FBONative() {
	bound = false;
	attached = false;
}

bool FBONative::_Init() {
	// --- create the fbo ---
	//make sure capabilities are loaded
	LoadGraphicsCapability(GRAPHICS_CAPABILITY_IMAGE_BUFFERS);
	
	//are we supported?
	if (capabilitySupportedImageBuffers) {
		//create fbo
		glGenFramebuffers(1,&fbo);
		
		//success
		return true;
	}
	
	//fail
	return false;
}

//api
bool FBONative::_Free() {
	// --- free teh fbo ---
	if (capabilitySupportedImageBuffers) {
		_Detach();
		_Finish();
		
		//delete teh fbo
		glDeleteFramebuffers(1,&fbo);
		fbo = 0;
		
		//success
		return true;
	}
	
	//fail
	return false;
}

bool FBONative::_Attach(gxtkSurface *surface) {
	// --- attach texture to the fbo ---
	//we do this separately so we can reuse the depth buffer in later binds
	if (capabilitySupportedImageBuffers && bound == false) {
		//generate a depth buffer
		glGenRenderbuffers(1, &depthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16,surface->width,surface->height);
			
		//store some values
		attached = true;
		texture = surface->texture;
		width = surface->width;
		height = surface->height;
		
		//success
		return true;
	}
	
	//fail
	return false;
}

bool FBONative::_Detach() {
	// --- dettach texture from fbo ---
	if (attached) {
		//dettach
		attached = false;
		
		//reset values
		texture = 0;
		width = 0;
		height = 0;
		
		//dettach texture and depth buffer
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,0, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER, 0);
		
		//destroy the depth buffer
		glDeleteRenderbuffers(1,&depthBuffer);
		depthBuffer = 0;
		
		//success
		return true;
	}
	
	//fail
	return false;
}

bool FBONative::_Start() {
	// --- bind the fbo ---
	if (startLocked == false && capabilitySupportedImageBuffers && attached && bound == false) {
		bound = true;
		
		//check if mojo is current rendering
		if (bb_graphics_renderDevice == 0) {
			//we are rendering to the fbo outside of OnRender()
			onRenderActive = false;
			
			//trick monkey into thinking it is rendering
			gc_assign(bb_graphics_renderDevice,bb_graphics_device);
		} else {
			//mojo is rendering
			//when we finish the fbo we will need to reset the mojo rendering
			onRenderActive = true;
			
			//make monkey flush itself
			bb_graphics_renderDevice->Flush();
		}
		
		//bind the fbo
		glBindFramebuffer(GL_FRAMEBUFFER,fbo);
		
		//set depth buffer
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER, depthBuffer);
		
		//attach texture
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,texture, 0);
				
		//check for success
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			_Finish();
			return false;
		}
		
		//setup viewport
		glViewport(0,0,width,height);
	
		//setup matrix for image
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glScalef (1.0f, -1.0f, 1.0f); // switch y axis so it matches screen rendering
		glOrtho(0,width,height,0,-1,1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		//extra stuff
		//taken from monkey BeginRender()
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2,GL_FLOAT,20,&bb_graphics_renderDevice->vertices[0]);	
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2,GL_FLOAT,20,&bb_graphics_renderDevice->vertices[2]);
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4,GL_UNSIGNED_BYTE,20,&bb_graphics_renderDevice->vertices[4]);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE,GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_TEXTURE_2D);
		bb_graphics_renderDevice->primCount=0;
		
		//rember device size so we can restore it later
		deviceWidth = bb_graphics_device->width;
		deviceHeight = bb_graphics_device->height;
		
		//fake the final beginrender
		bb_graphics_renderDevice->width = width;
		bb_graphics_renderDevice->height = height;
		bb_graphics_BeginRender();
		
		//flag graphics started
		startLocked = true;
		
		//success
		return true;
	}
	
	//fail
	return false;
}

bool FBONative::_Finish() {
	// --- bind the fbo ---
	if (bound == true) {
		bound = false;
		
		//check to see if we are rendering to fbo
		if (startLocked == true) {
			startLocked = false;
			
			//need to output changes to the fbo
			bb_graphics_renderDevice->Flush();
			
			//restore device size
			bb_graphics_device->width = deviceWidth;
			bb_graphics_device->height = deviceHeight;
			
			//check if we were previously in onrender
			if (onRenderActive) {
				//reset monkey render state
				bb_graphics_renderDevice->BeginRender();
			} else {
				//not rendering anymore so stop fooling monkey
				bb_graphics_renderDevice=0;
			}
		}
	
		//dettach first
		//_Detach();
		
		//now unbind the fbo
		glBindFramebuffer(GL_FRAMEBUFFER,0);
		
		//success
		return true;
	}
	
	//fail
	return false;
}

bool FBONative::_Clear(float r,float g, float b,float a = 255.0) {
	// --- this is a helper for completely clearing the image (alpha and all) ---
	if (bound == true) {
		bb_graphics_renderDevice->primCount=0;

		glClearColor( r/255.0f,g/255.0f,b/255.0f,a/255.0f );
		glClear( GL_COLOR_BUFFER_BIT );
		
		//success
		return true;
	}
	
	//fail
	return false;
}