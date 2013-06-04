// --- forward references ---
extern gxtkGraphics* bb_graphics_renderDevice;
extern gxtkGraphics* bb_graphics_device;
extern int bb_graphics_BeginRender();



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
void(__stdcall*glGetShaderiv)(GLuint shader, GLenum pname, GLint* params);
void(__stdcall*glGetShaderInfoLog)(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog);
void(__stdcall*glAttachShader)(GLuint program, GLuint shader);
void(__stdcall*glDetachShader)(GLuint program, GLuint shader);
void(__stdcall*glDeleteShader)(GLuint shader);
GLuint(__stdcall*glCreateProgram)(void);
void(__stdcall*glDeleteProgram)(GLuint program);
void(__stdcall*glGetProgramiv)(GLuint program, GLenum pname, GLint* params);
void(__stdcall*glLinkProgram)(GLuint program);
void(__stdcall*glUseProgram)(GLuint program);
void(__stdcall*glGetShaderSource)(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source);
int(__stdcall*glGetUniformLocation)(GLuint program, const GLchar* name);
void(__stdcall*glGetUniformfv)(GLuint program, GLint location, GLfloat* params);
void(__stdcall*glGetUniformiv)(GLuint program, GLint location, GLint* params);
void(__stdcall*glUniform1f)(GLint location, GLfloat x);
void(__stdcall*glUniform1fv)(GLint location, GLsizei count, const GLfloat* v);
void(__stdcall*glUniform1i)(GLint location, GLint x);
void(__stdcall*glUniform1iv)(GLint location, GLsizei count, const GLint* v);
void(__stdcall*glUniform2f)(GLint location, GLfloat x, GLfloat y);
void(__stdcall*glUniform2fv)(GLint location, GLsizei count, const GLfloat* v);
void(__stdcall*glUniform2i)(GLint location, GLint x, GLint y);
void(__stdcall*glUniform2iv)(GLint location, GLsizei count, const GLint* v);
void(__stdcall*glUniform3f)(GLint location, GLfloat x, GLfloat y, GLfloat z);
void(__stdcall*glUniform3fv)(GLint location, GLsizei count, const GLfloat* v);
void(__stdcall*glUniform3i)(GLint location, GLint x, GLint y, GLint z);
void(__stdcall*glUniform3iv)(GLint location, GLsizei count, const GLint* v);
void(__stdcall*glUniform4f)(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void(__stdcall*glUniform4fv)(GLint location, GLsizei count, const GLfloat* v);
void(__stdcall*glUniform4i)(GLint location, GLint x, GLint y, GLint z, GLint w);
void(__stdcall*glUniform4iv)(GLint location, GLsizei count, const GLint* v);
void(__stdcall*glUniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void(__stdcall*glUniformMatrix2x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void(__stdcall*glUniformMatrix2x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void(__stdcall*glUniformMatrix3x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void(__stdcall*glUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void(__stdcall*glUniformMatrix3x4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void(__stdcall*glUniformMatrix4x2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void(__stdcall*glUniformMatrix4x3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void(__stdcall*glUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
void(__stdcall*glGetProgramInfoLog)(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);



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
#define GL_LINK_STATUS 0x8B82
#define GL_ACTIVE_UNIFORMS 0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH 0x8B87
#define GL_ACTIVE_ATTRIBUTES 0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH 0x8B8A



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
					(void*&)glGetShaderiv=(void*)wglGetProcAddress("glGetShaderiv");
					(void*&)glGetShaderInfoLog=(void*)wglGetProcAddress("glGetShaderInfoLog");
					(void*&)glAttachShader=(void*)wglGetProcAddress("glAttachShader");
					(void*&)glDetachShader=(void*)wglGetProcAddress("glDetachShader");
					(void*&)glDeleteShader=(void*)wglGetProcAddress("glDeleteShader");
					(void*&)glCreateProgram=(void*)wglGetProcAddress("glCreateProgram");
					(void*&)glDeleteProgram=(void*)wglGetProcAddress("glDeleteProgram");
					(void*&)glGetProgramiv=(void*)wglGetProcAddress("glGetProgramiv");
					(void*&)glLinkProgram=(void*)wglGetProcAddress("glLinkProgram");
					(void*&)glUseProgram=(void*)wglGetProcAddress("glUseProgram");
					(void*&)glGetShaderSource=(void*)wglGetProcAddress("glGetShaderSource");
					(void*&)glGetUniformfv=(void*)wglGetProcAddress("glGetUniformfv");
					(void*&)glGetUniformiv=(void*)wglGetProcAddress("glGetUniformiv");
					(void*&)glGetUniformLocation=(void*)wglGetProcAddress("glGetUniformLocation");
					(void*&)glUniform1f=(void*)wglGetProcAddress("glUniform1f");
					(void*&)glUniform1fv=(void*)wglGetProcAddress("glUniform1fv");
					(void*&)glUniform1i=(void*)wglGetProcAddress("glUniform1i");
					(void*&)glUniform1iv=(void*)wglGetProcAddress("glUniform1iv");
					(void*&)glUniform2f=(void*)wglGetProcAddress("glUniform2f");
					(void*&)glUniform2fv=(void*)wglGetProcAddress("glUniform2fv");
					(void*&)glUniform2i=(void*)wglGetProcAddress("glUniform2i");
					(void*&)glUniform2iv=(void*)wglGetProcAddress("glUniform2iv");
					(void*&)glUniform3f=(void*)wglGetProcAddress("glUniform3f");
					(void*&)glUniform3fv=(void*)wglGetProcAddress("glUniform3fv");
					(void*&)glUniform3i=(void*)wglGetProcAddress("glUniform3i");
					(void*&)glUniform3iv=(void*)wglGetProcAddress("glUniform3iv");
					(void*&)glUniform4f=(void*)wglGetProcAddress("glUniform4f");
					(void*&)glUniform4fv=(void*)wglGetProcAddress("glUniform4fv");
					(void*&)glUniform4i=(void*)wglGetProcAddress("glUniform4i");
					(void*&)glUniform4iv=(void*)wglGetProcAddress("glUniform4iv");
					(void*&)glUniformMatrix2fv=(void*)wglGetProcAddress("glUniformMatrix2fv");
					(void*&)glUniformMatrix2x3fv=(void*)wglGetProcAddress("glUniformMatrix2x3fv");
					(void*&)glUniformMatrix2x4fv=(void*)wglGetProcAddress("glUniformMatrix2x4fv");
					(void*&)glUniformMatrix3x2fv=(void*)wglGetProcAddress("glUniformMatrix3x2fv");
					(void*&)glUniformMatrix3fv=(void*)wglGetProcAddress("glUniformMatrix3fv");
					(void*&)glUniformMatrix3x4fv=(void*)wglGetProcAddress("glUniformMatrix3x4fv");
					(void*&)glUniformMatrix4x2fv=(void*)wglGetProcAddress("glUniformMatrix4x2fv");
					(void*&)glUniformMatrix4x3fv=(void*)wglGetProcAddress("glUniformMatrix4x3fv");
					(void*&)glUniformMatrix4fv=(void*)wglGetProcAddress("glUniformMatrix4fv");
					(void*&)glGetProgramInfoLog=(void*)wglGetProcAddress("glGetProgramInfoLog");
					
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
	GLenum error;
	String customError;
	bool valid;
	
	bool _Init(int type);
	bool _Free();
	bool _SetSource(String source);
	bool _HasError();
	String _GetError();
	bool _IsValid();
	bool _HasSource();
};



// --- ShaderProgram header ---
class ShaderProgramNative : public Object {
	public:
	ShaderProgramNative();
	
	static GLuint activeProgram;
	static bool startLocked;
	static bool onRenderActive;
	
	GLuint program;
	GLenum error;
	String customError;
	bool used;
	
	bool _Init();
	bool _Free();
	bool _Attach(ShaderNative *shader);
	bool _Detach(ShaderNative *shader);
	bool _Link();
	bool _Start();
	bool _Finish();
	bool _HasError();
	String _GetError();
	int _GetUniformLocation(String name);
	bool _SetUniformInt(int location,Array<int > values,GLsizei count,int size);
	bool _SetUniformFloat(int location,Array<Float > values,GLsizei count,int size,int columns,int rows,GLboolean transpose);
	bool _GetUniformInt(int location,Array<int > values);
	bool _GetUniformFloat(int location,Array<float > values);
	
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
				customError = "Invalid Shader Type";
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

bool ShaderNative::_Free() {
	// --- free the shader ---
	if (capabilitySupportedShaders && valid) {
		//if this shader is still attached it will only be flagged for deletion
		valid = false;
		glDeleteShader(shader);
		shader = 0;
		
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
		
		//free the source
		delete theSource;
		
		//check for error
		error = glGetError();
		if (error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION) {
			return false;
		}
		
		//compile the source
		glCompileShader(shader);
		
		//check if the shader compiled
		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			//failed
			GLint infoLogLength;
	        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
			
	        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
	        glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
			customError = String(strInfoLog);
			delete strInfoLog;
			
			//fail
			return false;
		}
		
		//check for error
		error = glGetError();
		if (error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION) {
			return false;
		}
		
		//success
		valid = true;
		return true;
	}
	
	//fail
	return false;
}

bool ShaderNative::_HasError() {
	// --- get last error code ---
	return error != GL_NO_ERROR || customError.Length() > 0;
}

String ShaderNative::_GetError() {
	// --- return last error as string ---
	if (_HasError()) {
		//reset stored errors
		int theError = (int)error;
		error = GL_NO_ERROR;
		String theCustomError = String(customError);
		customError = "";
		
		//use custo merror
		if (theCustomError.Length() > 0) {
			return theCustomError;
		} else {
			switch(theError) {
				case GL_INVALID_VALUE:
					return String("GL_INVALID_VALUE");
					break;
				case GL_INVALID_OPERATION:
					return String("GL_INVALID_OPERATION");
					break;
			}
		}
	}
	
	return String();
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
GLuint ShaderProgramNative::activeProgram = 0;
bool ShaderProgramNative::startLocked = false;
bool ShaderProgramNative::onRenderActive = false;

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

bool ShaderProgramNative::_Free() {
	// --- free the shader program ---
	if (capabilitySupportedShaders) {
		//if program is in use it will be flagged for deletion
		//we want to avoid this so force end here
		if (used) {
			_Finish();
		}
		
		//delete program
		glDeleteProgram(program);
		program = 0;
		
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
		error = glGetError();
		if (error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION) {
			return false;
		}
		
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
		error = glGetError();
		if (error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION) {
			return false;
		}
		
		//success
		return true;
	}
	
	//fail
	return false;
}

bool ShaderProgramNative::_HasError() {
	// --- get last error code ---
	return error != GL_NO_ERROR || customError.Length() > 0;
}

String ShaderProgramNative::_GetError() {
	// --- return last error as string ---
	if (_HasError()) {
		//reset stored errors
		int theError = (int)error;
		error = GL_NO_ERROR;
		String theCustomError = String(customError);
		customError = "";
		
		//use custo merror
		if (theCustomError.Length() > 0) {
			return theCustomError;
		} else {
			switch(theError) {
				case GL_INVALID_VALUE:
					return String("GL_INVALID_VALUE");
					break;
				case GL_INVALID_OPERATION:
					return String("GL_INVALID_OPERATION");
					break;
			}
		}
	}
	
	return String();
}

bool ShaderProgramNative::_Link() {
	// --- link shaders into program ---
	//are we supported?
	if (capabilitySupportedShaders) {
		//link
		glLinkProgram(program);
		
		//check for error linking
		GLint status;
    	glGetProgramiv (program, GL_LINK_STATUS, &status);
    	if (status == GL_FALSE) {
        	GLint infoLogLength;
        	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
        
       		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
       		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
			customError = String(strInfoLog);
       		delete[] strInfoLog;
			
			return false;
    	}
		
		//check for error
		error = glGetError();
		if (error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION) {
			return false;
		}
		
		//success
		return true;
	}
	
	//fail
	return false;	
}

bool ShaderProgramNative::_Start() {
	// --- use program ---
	//check to see if this program is already in use
	if (activeProgram == program) {
		//dont need to do anything as it is already active
		return true;
	}
	
	//are we supported?
	if (capabilitySupportedShaders && startLocked == false && used == false) {
		//check if mojo is current rendering
		if (bb_graphics_renderDevice == 0) {
			//we are rendering to the fbo outside of OnRender()
			onRenderActive = false;
			
		} else {
			//not rendering
			onRenderActive = true;
			
			//make monkey flush itself
			bb_graphics_renderDevice->Flush();
		}
				
		//use program
		glUseProgram(program);
		
		//check for error
		error = glGetError();
		if (error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION) {
			return false;
		}
		
		//flag using
		activeProgram = program;
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
		//check if we are in onrender
		if (onRenderActive) {
			//make monkey flush itself
			bb_graphics_renderDevice->Flush();
		/*} else {
			//finish it please!

			error = glGetError();
			if (error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION) {
				return false;
			}*/
		}
		
		//unuse program
		glUseProgram(0);
	
		//unflag using
		activeProgram = 0;
		used = false;
		startLocked = false;
			
		//check for error
		error = glGetError();
		if (error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION) {
			return false;
		}
			
		//success
		return true;
	}
	
	//fail
	return false;
}

GLint ShaderProgramNative::_GetUniformLocation(String name) {
	// --- get location of a uniform ---
	//this location int wont change again until the program is relinked so can be reused
	GLchar *theName = name.ToCString<GLchar>();
	GLint location = glGetUniformLocation(program,theName);
	delete theName;
	
	//check for error
	error = glGetError();
	if (error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION) {
		//fail
		return -1;
	}
	
	//success
	return location;
}

bool ShaderProgramNative::_SetUniformInt(int location,Array<int > values,GLsizei count,int size) {
	// --- set int uniform ---
	//make sure the program is active
	if (used == false) {
		customError = "Cant modify uniform when shader program isn't active";
		return false;
	}
	
	if (location == -1) {
		return false;
	}
	
	//we are setting a value, vector or array
	//check size
	switch(size) {
		case 1:
			//we are setting a single value, vector or array
			if (count == 1) {
				//single int
				//call apropriate gl function
				glUniform1i(location,values[0]);
				
			} else {
				//array of ints
				//call apropriate gl function
				glUniform1iv(location,count,&values[0]);
			}
			break;
		case 2:
			if (count == 1) {
				//single int vec2
				//call apropriate gl function
				glUniform2i(location,values[0],values[1]);
			} else {
				//array of int vec2
				//call apropriate gl function
				glUniform2iv(location,count,&values[0]);
			}
			break;
		case 3:
			if (count == 1) {
				//single int vec3
				//call apropriate gl function
				glUniform3i(location,values[0],values[1],values[2]);
			} else {
				//array of int vec3
				//call apropriate gl function
				glUniform3iv(location,count,&values[0]);
			}
			break;
		case 4:
			if (count == 1) {
				//single int vec4
				//call apropriate gl function
				glUniform4i(location,values[0],values[1],values[2],values[3]);
			} else {
				//array of int vec4
				//call apropriate gl function
				glUniform4iv(location,count,&values[0]);
			}
			break;
		default:
			//failed
			return false;
			break;
	}
	
	//check for error
	error = glGetError();
	if (error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION) {
		return false;
	}
	
	//sucess :D
	return true;
}

bool ShaderProgramNative::_SetUniformFloat(int location,Array<Float > values,GLsizei count,int size, int columns,int rows,GLboolean transpose = GL_FALSE) {
	// --- set int uniform ---
	//make sure the program is active
	if (used == false) {
		customError = "Cant modify uniform when shader program isn't active";
		return false;
	}
	
	if (location == -1) {
		return false;
	}
	
	//check for setting matrix
	if (columns > 1 && rows > 1) {
		//we are setting a mtrix
		switch(columns) {
			case 2:
				switch(rows) {
					case 2:
						glUniformMatrix2fv(location,count,transpose,&values[0]);
						break;
					case 3:
						glUniformMatrix2x3fv(location,count,transpose,&values[0]);
						break;
					case 4:
						glUniformMatrix2x4fv(location,count,transpose,&values[0]);
						break;
					default:
						return false;
						break;
				}
				break;
			case 3:
				switch(rows) {
					case 2:
						glUniformMatrix3x2fv(location,count,transpose,&values[0]);
						break;
					case 3:
						glUniformMatrix3fv(location,count,transpose,&values[0]);
						break;
					case 4:
						glUniformMatrix3x4fv(location,count,transpose,&values[0]);
						break;
					default:
						return false;
						break;
				}
				break;
			case 4:
				switch(rows) {
					case 2:
						glUniformMatrix4x2fv(location,count,transpose,&values[0]);
						break;
					case 3:
						glUniformMatrix4x3fv(location,count,transpose,&values[0]);
						break;
					case 4:
						glUniformMatrix4fv(location,count,transpose,&values[0]);
						break;
					default:
						return false;
						break;
				}
				break;
			default:
				return false;
				break;
		}
	} else {
		//check size
		switch(size) {
			case 1:
				if (count == 1) {
					//single float
					//call apropriate gl function
					glUniform1f(location,values[0]);
					
				} else {
					//array of floats
					//call apropriate gl function
					glUniform1fv(location,count,&values[0]);
				}
				break;
			case 2:
				if (count == 1) {
					//single float vec2
					//call apropriate gl function
					glUniform2f(location,values[0],values[1]);
				} else {
					//array of float vec2
					//call apropriate gl function
					glUniform2fv(location,count,&values[0]);
				}
				break;
			case 3:
				if (count == 1) {
					//single float vec3
					//call apropriate gl function
					glUniform3f(location,values[0],values[1],values[2]);
				} else {
					//array of float vec3
					//call apropriate gl function
					glUniform3fv(location,count,&values[0]);
				}
				break;
			case 4:
				if (count == 1) {
					//single float vec4
					//call apropriate gl function
					glUniform4f(location,values[0],values[1],values[2],values[3]);
				} else {
					//array of float vec4
					//call apropriate gl function
					glUniform4fv(location,count,&values[0]);
				}
				break;
			default:
				//failed
				return false;
				break;
		}
	}
	
	//check for error
	error = glGetError();
	if (error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION) {
		return false;
	}
	
	//sucess :D
	return true;
}

bool ShaderProgramNative:: _GetUniformInt(int location,Array<int > values) {
	// --- get a uniform as float ---
	//check location
	if (location == -1) {
		return false;
	}
	
	//do it
	glGetUniformiv(program,location,&values[0]);
	
	//check for error
	error = glGetError();
	if (error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION) {
		return false;
	}
	
	//success
	return true;
}

bool ShaderProgramNative:: _GetUniformFloat(int location,Array<float > values) {
	// --- get a uniform as float ---
	//check location
	if (location == -1) {
		return false;
	}
	
	//do it
	glGetUniformfv(program,location,&values[0]);
	
	//check for error
	error = glGetError();
	if (error == GL_INVALID_VALUE || error == GL_INVALID_OPERATION) {
		return false;
	}
	
	//success
	return true;
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