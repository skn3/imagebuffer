Strict

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
	Class FBONative
		Private
		Method _Init:bool()
		Method Free:bool() = "_Free"
		Method _Attach:bool(surface:Surface)
		Method _Dettach:bool()
		Method _Start:bool()
		Method _Finish:bool()
		Method _Clear:bool(r:float, g:float, b:float, a:float = 255.0)
	End
	
	Function CheckGraphicsAbility:Bool(ability:Int)
Public
#end
#SKN3_GRAPHICS_IMPLEMENTED=false

' --- constants ---
'capabilities
Const GRAPHICS_CAPABILITY_IMAGE_BUFFER:= 1
Const GRAPHICS_CAPABILITY_SHADERS:= 2

' --- module code ---
#If SKN3_GRAPHICS_IMPLEMENTED="1"
	'supported device
	' --- classes ---
	'fbo
	Class FBO Extends FBONative
		Global supported:Int = -1
		
		Method New()
			GetMatrix()
			' --- constructor ---
			'cache the device capability
			If supported = -1 supported = CheckGraphicsAbility(GRAPHICS_CAPABILITY_IMAGE_BUFFER)
			
			'check device capability
			If supported = 0 Error("Image Buffer Not Supported")
			
			'init the fbo
			If _Init() = False Error("Error Creating FBO")
		End
		
		Method SetImage:Void(image:Image)
			' --- attach or dettach the image to the fbo ---
			If image = Null
				_Dettach()
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
	Function CheckGraphicsAbility:Bool(ability:Int)
		' --- always return false as not supported device ---
		Return False
	End
#end