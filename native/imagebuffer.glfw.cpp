// --- forward references ---
extern gxtkGraphics* bb_graphics_renderDevice;
extern gxtkGraphics* bb_graphics_device;
extern int bb_graphics_BeginRender();
extern int bb_graphics_SetScissor(Float t_x,Float t_y,Float t_width,Float t_height);

// --- gl stuff ---
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

#define GL_FRAMEBUFFER 0x8D40
#define GL_RENDERBUFFER 0x8D41
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_DEPTH_ATTACHMENT 0x8D00
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_DEPTH_COMPONENT16 0x81A5

// --- functions ---
static bool CheckGraphicsAbility(int ability) {
	// --- return if the device supports certain abilities ---
	switch(ability) {
		case 1://GRAPHICS_CAPABILITY_IMAGE_BUFFER
			return glfwExtensionSupported("GL_ARB_framebuffer_object");
			break;
			
		case 2://GRAPHICS_CAPABILITY_SHADERS
			return true;
			break;
	}
	
	//default no
	return false;
}

// --- Shader ---
class Shader : public Object {
	
};

// --- FBO header ---
class FBONative : public Object {
	public:
	FBONative();
	
	static bool loaded;
	static bool supported;
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
	bool _Dettach();
	bool _Start();
	bool _Finish();
	bool _Clear(float r,float g, float b,float a);
};

// --- FBO class ---
bool FBONative::loaded = false;
bool FBONative::supported = false;
bool FBONative::startLocked = false;
bool FBONative::onRenderActive = false;

FBONative::FBONative() {
	bound = false;
	attached = false;
}

bool FBONative::_Init() {
	// --- create the fbo ---
	//do we need to load ?
	if (loaded != true) {
		loaded = true;
		
		//glGenFramebuffers
		//GL_EXT_framebuffer_object
		//GL_ARB_framebuffer_object
		if (glfwExtensionSupported("GL_ARB_framebuffer_object")) {
			//supported
			supported = true;
			
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
			supported = false;
		}
	}
	
	//are we supported?
	if (supported) {
		//create fbo
		glGenFramebuffers(1,&fbo);
		
		//success
		return true;
	}
	
	//fail
	return false;
}

bool FBONative::_Free() {
	// --- free teh fbo ---
	if (supported) {
		_Dettach();
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
	if (supported && bound == false) {
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

bool FBONative::_Dettach() {
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
	if (startLocked == false && supported && attached && bound == false) {
		bound = true;
		
		//check if mojo is current rendering
		if (bb_graphics_renderDevice == 0) {
			//we are rendering to the fbo outside of the OnRender()
			onRenderActive = false;
		} else {
			//mojo is rendering
			//when we finish the fbo we will need to reset the mojo rendering
			onRenderActive = true;
			
			//make monkey flush itself
			bb_graphics_renderDevice->Flush();
		}
		
		//trick monkey into thinking it is rendering
		gc_assign(bb_graphics_renderDevice,bb_graphics_device);
		
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
		//_Dettach();
		
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