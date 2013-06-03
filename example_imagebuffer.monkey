Strict

Import mojo
Import opengl
Import skn3.imagebuffer

Function Main:Int()
	New MyApp
	Return 0
End

Class MyApp Extends App
	Field fbo:FBO
	Field image:Image
	Field angle:Float
	Field lastX:Float
	Field lastY:Float
	Field r:Int
	Field g:Int
	Field b:Int
	
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
		
		'paint the default image canvas
		ClearImage()
		
		Return 0
	End
	
	Method OnUpdate:Int()
		' --- update the game ---
		If KeyHit(KEY_ESCAPE) Error("")
		
		'update the fbo
		If KeyHit(KEY_SPACE)
			'clear
			ClearImage()
		EndIf
		
		'paint
		Local paint:= False
		If MouseHit(MOUSE_LEFT)
			lastX = MouseX()
			lastY = MouseY()
			paint = True
		EndIf
		
		If paint or (MouseDown(MOUSE_LEFT) And (MouseX() <> lastX or MouseY() <> lastY))
			'prevent drawing from top corner
			'update color
			r = Rnd(0, 255)
			g = Rnd(0, 255)
			b = Rnd(0, 255)
			
			'update image
			fbo.Start()
			SetColor(r, g, b)
			If paint
				'single point
				DrawRect(lastX - 3, lastY - 3, 6, 6)
			Else
				'line
				DrawLineWidthTest(lastX, lastY, MouseX(), MouseY(), 6, 0.8)
			EndIf
			fbo.Finish()
			
			'update mouse position
			lastX = MouseX()
			lastY = MouseY()
		EndIf
		
		angle += 1
		Return 0
	End
	
	Method OnRender:Int()
		' --- render the game ---
		Cls(180, 180, 180)
				
		If image
			'draw iamge in background
			DrawImage(image, DeviceWidth() / 2, DeviceHeight() / 2)
						
			Local imageSize:Float = 80.0
			Local imageScale:Float
			
			If DeviceWidth() > DeviceHeight()
				'landscape
				imageScale = imageSize / DeviceWidth()
			Else
				'portrait
				imageScale = imageSize / DeviceHeight()
			EndIf
			
			'draw copies on screen
			Local offset:Float = imageSize
			Local total:Int = (DeviceHeight() -imageSize - imageSize) / imageSize
			For Local copies:= 0 Until total
				PushMatrix()
				Translate(DeviceWidth() -imageSize, offset)
				offset += imageSize
			
				'draw drop shadow
				PushMatrix()
				Translate(5, 5)
				Rotate(angle)
				SetAlpha(0.3)
				SetColor(0, 0, 0)
				Scale(imageScale, imageScale)
				Translate(-DeviceWidth() / 2, -DeviceHeight() / 2)
				DrawRect(0, 0, DeviceWidth(), DeviceHeight())
				PopMatrix()
				
				'draw image
				PushMatrix()
				Rotate(angle)
				SetAlpha(1.0)
				SetColor(255, 255, 255)
				DrawImage(image, 0, 0, 0, imageScale, imageScale)
				PopMatrix()
				
				PopMatrix()
			Next
		EndIf
		
		'draw overlay text
		SetColor(255, 255, 255)
		DrawText("Click To Draw", 5, 5)
		DrawText("Press Space To Clear", 5, 25)
		
		Return 0
	End
	
	Method ClearImage:Void()
		' --- hlper to clear teh canvas ---
		'do first render on image
		fbo.Start()
		Cls(255, 0, 0)
		SetColor(255, 255, 255)
		DrawRect(5, 5, DeviceWidth() -10, DeviceHeight() -10)
		fbo.Finish()		
	End
End

Function DrawLineWidthTest:Void(X1:Float, Y1:Float, X2:Float, Y2:Float, Width:Float = 2, DrawStep:Float = 1)
	Local OX:Float = 0 - (Width / 2)
	Local OY:Float = 0 - (Width / 2)
	Local DX:Float = (Width / 2)
	Local DY:Float = (Width / 2)
	
	Local tY:Float = OY
	While tY < DY
		Local tX:Float = OX
		While tX < DX
			DrawLine(X1+tX,Y1+tY,X2+tX,Y2+tY)
			tX += DrawStep
		Wend
		tY += DrawStep
	Wend
End