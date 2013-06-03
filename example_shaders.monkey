Strict

#TEXT_FILES="*.vert|*.frag"

Import mojo
Import opengl
Import skn3.imagebuffer

Function Main:Int()
	New MyApp
	Return 0
End

Class MyApp Extends App
	Field image:Image
	Field shaderProgram:ShaderProgram
	Field shaderVert:Shader
	Field shaderFragment:Shader
	Field shaderTotal:Int = 2
	Field shaderIndex:Int = 0
	
	Method OnCreate:Int()
		' --- setup the game ---
		SetUpdateRate(60)
		
		'do basic shaders check
		If CheckGraphicsCapability(GRAPHICS_CAPABILITY_SHADERS) = False Error("Not supported sorry!")
		
		'load an image
		image = LoadImage("image.png", 1, Image.MidHandle)
		
		'create a shaders
		shaderProgram = New ShaderProgram()
		shaderVert = New Shader(VERTEX_SHADER)
		shaderFragment = New Shader(FRAGMENT_SHADER)
				
		'setup first shader source
		NextShader()
		
		Return 0
	End
	
	Method OnUpdate:Int()
		' --- update the game ---
		If KeyHit(KEY_ESCAPE) Error("")
		
		If MouseHit(MOUSE_LEFT) NextShader()
		
		Return 0
	End
	
	Method OnRender:Int()
		' --- render the game ---
		Cls(180, 180, 180)
		
		'experiment
		shaderProgram.Start()
		DrawImage(image, MouseX(), MouseY())
		shaderProgram.Finish()
		
		Return 0
	End
	
	Method NextShader:Void()
		' --- helper to switch to next shader ---
		shaderIndex += 1
		If shaderIndex > shaderTotal shaderIndex = 1
		
		'clear previous attachments
		shaderProgram.Clear()
		shaderVert.Clear()
		shaderFragment.Clear()
		
		'set shader files to load
		Local fileVert:String
		Local fileFrag:String
		Select shaderIndex
			Case 1
				fileFrag = "shader1.frag"
				
			Case 2
				fileVert = "shader2.vert"
				fileFrag = "shader2.frag"
		End
		
		'load vert shader
		If fileVert.Length = 0
			'no vert shader
		Else
			'has vert shader
			If shaderVert.SetSource(LoadString(fileVert)) = False
				Print "Set Shader '" + fileVert + "' Source: Failed - " + shaderVert.GetError()
			Else
				Print "Set Shader '" + fileVert + "' Source: Success!"
			EndIf
		EndIf
		
		'load frag shader
		If fileFrag.Length = 0
			'no frag shader
		Else
			'has frag shader
			If shaderFragment.SetSource(LoadString(fileFrag)) = False
				Print "Set Shader '" + fileFrag + "' Source: Failed: " + shaderFragment.GetError()
			Else
				Print "Set Shader '" + fileFrag + "' Source: Success!"
			EndIf
		EndIf
		
		'attach shaders to program
		If shaderVert.HasSource()
			If shaderProgram.Attach(shaderVert) = False
				Print "Attach Shader '" + fileVert + "': Failed"
			Else
				Print "Attach Shader '" + fileVert + "': Success!"
			EndIf
		EndIf
		
		If shaderFragment.HasSource()
			If shaderProgram.Attach(shaderFragment) = False
				Print "Attach Shader '" + fileFrag + "': Failed"
			Else
				Print "Attach Shader '" + fileFrag + "': Success!"
			EndIf
		EndIf
		
		'link the program
		If shaderProgram.Link() = False
			Print "Link Shader Program: Failed"
		Else
			Print "Link Shader Program: Success!"
		EndIf
		
		'test setting a uniform value
		If shaderProgram.Start() = False
			Print "Start Shader Program: Failed"
		Else
			Print "Start Shader Program: Success!"
			
			Local id:= "testing123"
			Local value:= 123
			Local location:= shaderProgram.GetUniformLocation(id)
			If location = -1 Print "cant find uniform '" + id + "'"
			
			If shaderProgram.SetUniform(location, value) = False
				Print "Set Shader Program Uniform '" + id + "' to '" + value + "': Failed"
			Else
				Print "Set Shader Program Uniform '" + id + "' to '" + value + "': Success!"
			EndIf
			
			If shaderProgram.Finish() = False
				Print "Finish Shader Program: Failed"
			Else
				Print "Finish Shader Program: Success!"
			EndIf
		EndIf
	End
End