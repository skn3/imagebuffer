Strict

'version 4
' - started to add some shader support
'version 3
' - added device capability checks
' - removed some wasted method calls from extended FBO
' - added unsupported device stub
' - locked it so only 1 fbo can be started at a time
' - updated example
' - made it so depth buffer gets discarded
'version 2
' - fixed some flags not being reset
'version 1
' - first commit

' --- imports ---
#if TARGET = "glfw"
#SKN3_GRAPHICS_IMPLEMENTED=True
Import mojo
Import mojo.graphicsdevice
Import "native/imagebuffer.${TARGET}.${LANG}"

'externals
Extern
	Class ShaderNative
		Private
		Method _Init:bool(type:Int)
		Method _SetSource:Bool(source:String)
		Public
		Method GetError:String() = "_GetError"
		Method IsValid:Bool() = "_IsValid"
		Method HasSource:Bool() = "_HasSource"
	End
	
	Class ShaderProgramNative
		Private
		Method _Init:Bool()
		Method _Attach:Bool(shader:ShaderNative)
		Method _Detach:Bool(shader:ShaderNative)
		Public
		Method Link:Bool() = "_Link"
		Method Start:Bool() = "_Start"
		Method Finish:Bool() = "_Finish"
	End

	Class FBONative
		Private
		Method _Init:bool()
		Method _Attach:bool(surface:Surface)
		Method _Detach:bool()
		Method _Start:bool()
		Method _Finish:bool()
		Method _Clear:bool(r:float, g:float, b:float, a:float = 255.0)
		Public
		Method Free:bool() = "_Free"
	End
	
	Function CheckGraphicsCapability:int(capability:Int)
Public
#end
#SKN3_GRAPHICS_IMPLEMENTED=false

' --- constants ---
'capabilities
Const GRAPHICS_CAPABILITY_IMAGE_BUFFERS:= 1
Const GRAPHICS_CAPABILITY_SHADERS:= 2

Const VERTEX_SHADER:= 1
Const FRAGMENT_SHADER:= 2

' --- module code ---
#If SKN3_GRAPHICS_IMPLEMENTED="1"
	'supported device
	' --- classes ---	
	'shader
	Class Shader Extends ShaderNative
		Method New()
			Error("Error Creating Shader. Must specify type!")
		End
		
		Method New(type:Int)
			' --- constructor ---
			'init the fbo
			If _Init(type) = False Error("Error Creating Shader")
		End
		
		Method SetSource:Bool(source:String)
			' --- change source of shader ---
			Return _SetSource(source)
		End
		
		Method Clear:Bool()
			' --- clear this shader ---
			_SetSource("")
			Return True
		End
	End
	
	'shaderprogram
	Class ShaderProgram Extends ShaderProgramNative
		Field shaders:= New List<Shader>
		
		Method New()
			' --- constructor ---
			If _Init() = False Error("Error Creating Shader Program")
		End
		
		Method Attach:Bool(shader:Shader)
			' --- attach a shader ---
			shaders.AddLast(shader)
			If _Attach(shader)
				Return True
			End
			
			Return False
		End
		
		Method Detach:Bool(shader:Shader)
			' --- detach a shader ---
			shaders.RemoveEach(shader)
			If _Detach(shader)
				Return True
			End
			
			Return False
		End
		
		Method Clear:Bool()
			' --- clear attached shaders ---
			Local node:= shaders.FirstNode()
			
			Local delNode:list.Node<Shader>
			
			While node
				delNode = node
				node = node.NextNode()
				Detach(delNode.Value())
			Wend
			
			Return True
		End
	End
	
	'fbo
	Class FBO Extends FBONative
		Method New()
			' --- constructor ---
			'init the fbo
			If _Init() = False Error("Error Creating FBO")
		End
		
		Method SetImage:Void(image:Image)
			' --- attach or dettach the image to the fbo ---
			If image = Null
				_Detach()
			Else
				If _Attach(image.GetSurface()) = False Error("FBO.SetImage() Failed")
			EndIf
		End
		
		Method Start:Void()
			' --- start buffer ---
			If _Start() = False Error("FBO.Start() Failed")
		End
		
		Method Finish:Void()
			' --- start buffer ---
			If _Finish() = False Error("FBO.Finish() Failed")
		End
		
		Method Clear:Void(r:float, g:float, b:float, a:float = 255.0)
			' --- start buffer ---
			If _Clear(r, g, b, a) = False Error("FBO.Clear() Failed")
		End
	End
#else
	'unsupported device
	Class FBO
		Method New()
			Error("Image Buffer Not Supported")
		End
		
		Method Free:Void()
		End
		
		Method SetImage:Void(image:Image)
			Error("FBO.SetImage() Failed")
		End
		
		Method Start:Void()
			Error("FBO.Start() Failed")
		End
		
		Method Finish:Void()
			Error("FBO.Finish() Failed")
		End
		
		Method Clear:Void(r:float, g:float, b:float, a:float = 255.0)
			Error("FBO.Clear() Failed")
		End
	End
	
	' --- functions ---
	Function CheckGraphicsCapability:Bool(capability:Int)
		' --- always return false as not supported device ---
		Return False
	End
#end