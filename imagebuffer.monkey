Strict

'this forces the app to enable certain bits of glfw
Import mojo
Import mojo.graphicsdevice
Import "native/imagebuffer.glfw.cpp"

Extern
	Class FBONative
		Private
		Method _Init:Void()
		Method _Free:Void()
		Method _Attach:Void(surface:Surface)
		Method _Dettach:Void()
		Method _Start:Void()
		Method _Finish:Void()
		Method _Clear:Void(r:float, g:float, b:float, a:float)
	End
Public

Class FBO Extends FBONative
	Method New()
		_Init()
	End
	
	Method New(image:Image)
		_Init()
		If image SetImage(image)
	End
	
	Method Free:Void()
		_Free()
	End
	
	Method SetImage:Void(image:Image)
		If image = Null
			_Dettach()
		Else
			_Attach(image.GetSurface())
		EndIf
	End
		
	Method Start:Void()
		_Start()
	End
	
	Method Finish:Void()
		_Finish()
	End
	
	Method Clear:Void(r:int, g:int, b:int, a:int = 255)
		_Clear(r, g, b, a)
	End
End