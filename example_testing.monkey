Strict

Import mojo
Import opengl
Import skn3.imagebuffer

Function Main:Int()
	New MyApp
	Return 0
End

Class MyApp Extends App
	Field image:Image
	Field fbo:FBO
	Field done:Bool
	
	Method OnCreate:Int()
		' --- setup the game ---
		SetUpdateRate(60)
		
		'do basic fbo check
		If CheckGraphicsCapability(GRAPHICS_CAPABILITY_IMAGE_BUFFERS) = False Error("Not supported sorry!")
		
		'create monkey image (this will generate teh underlying texture)
		image = CreateImage(DeviceWidth(), DeviceHeight(), 1, Image.MidHandle)
		
		'create fbo and attach the image to it
		fbo = New FBO()
		fbo.SetImage(image)
		
		Return 0
	End
	
	Method OnUpdate:Int()
		' --- update the game ---
		If KeyHit(KEY_ESCAPE) Error("")
		
		Return 0
	End
	
	Method OnRender:Int()
		' --- render the game ---
		If done = False
			done = True
			fbo.Start()
			DrawCircle(20, 20, 100)
			fbo.Finish()
		EndIf
		
		Cls(180, 180, 180)
		
		If image DrawImage(image, DeviceWidth() / 2, DeviceHeight() / 2)
		
		Return 0
	End
End