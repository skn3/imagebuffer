Import mojo
Import opengl
Import skn3.imagebuffer

Function Main:Int()
	New MyApp
End

Class MyApp Extends App
	Field image:Image
	Field angle:Float
	
	Method OnCreate:Int()
		' --- setup the game ---
		SetUpdateRate(60)
		
		If image = Null
			'create monkey image (this will generate teh underlying texture)
			image = CreateImage(80, 80, 1, Image.MidHandle)
			
			'create a new fbo (passing in the image will also attach it)
			Local fbo:= New FBO()
			fbo.SetImage(image)
			fbo.Start()
			
			Local tempImage:= LoadImage("baseimage.png")
			DrawImage(tempImage, 0, 0)
			
			fbo.Finish()
		EndIf
		
		Return 0
	End
	
	Method OnUpdate:Int()
		' --- update the game ---
		If KeyHit(KEY_ESCAPE) Error("")
		
		angle += 1
		Return 0
	End
	
	Method OnRender:Int()
		' --- render the game ---
		Cls(0, 0, 0)
		SetColor(255, 255, 255)
				
		If image
			'draw some images in a nice pattern
			Translate(DeviceWidth() / 2, DeviceHeight() / 2)
			Rotate(angle)
			DrawImage(image, 0, 0)
			DrawImage(image, -40, 0)
			DrawImage(image, 40, 0)
			DrawImage(image, 0, -40)
			DrawImage(image, 0, 40)
		EndIf
		
		Return 0
	End
End