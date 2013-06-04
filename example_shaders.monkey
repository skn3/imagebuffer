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
	Field shaderExamples:= New List<ShaderExample>
	Field currentExampleNode:list.Node<ShaderExample>
	Field currentExample:ShaderExample
	
	Method OnCreate:Int()
		' --- setup the game ---
		SetUpdateRate(60)
		
		'do basic shaders check
		If CheckGraphicsCapability(GRAPHICS_CAPABILITY_SHADERS) = False Error("Not supported sorry!")
		
		'create examples
		shaderExamples.AddLast(New ShaderExample1)
		shaderExamples.AddLast(New ShaderExample2)
		
		'setup first shader source
		NextShader()
		
		Return 0
	End
	
	Method OnUpdate:Int()
		' --- update the game ---
		If KeyHit(KEY_ESCAPE) Error("")
		If MouseHit(MOUSE_LEFT) NextShader()
		
		'update example
		If currentExample currentExample.OnUpdate()
		
		Return 0
	End
	
	Method OnRender:Int()
		' --- render the game ---
		Cls(180, 180, 180)
		
		'render example
		If currentExample currentExample.OnRender()
		
		Return 0
	End
	
	Method NextShader:Void()
		' --- helper to switch to next shader ---
		'finish old example
		If currentExample currentExample.OnFinish()
		
		'get the next shader example
		If currentExampleNode currentExampleNode = currentExampleNode.NextNode()
		If currentExampleNode = Null currentExampleNode = shaderExamples.FirstNode()
		currentExample = currentExampleNode.Value()
		
		'start new example
		currentExample.OnStart()
	End
End

Class ShaderExample Abstract
	Method OnStart:Void() Abstract
	Method OnFinish:Void() Abstract
	Method OnUpdate:Void() Abstract
	Method OnRender:Void() Abstract
End

Class ShaderExample1 Extends ShaderExample
	Field program:ShaderProgram
	Field fragShader:Shader
	Field angleLocation:Int
	Field angle:Float
	
	Method OnStart:Void()
		' --- setup example ---
		program = New ShaderProgram()
		fragShader = New Shader(FRAGMENT_SHADER)
		
		'frag shader
		If fragShader.SetSource(LoadString("example1.frag")) = False
			Print "shader compile error: ~n" + fragShader.GetError()
		EndIf
		program.Attach(fragShader)
		
		'link
		If program.Link() = False
			Print "shader program link error: ~n" + program.GetError()
		EndIf
		
		'get uniform locations
		angleLocation = program.GetUniformLocation("angle")
	End
	
	Method OnFinish:Void()
		' --- free example ---
		fragShader.Free()
		program.Free()
	End
	
	Method OnUpdate:Void()
		' --- update example ---
		angle += 0.01
	End
	
	Method OnRender:Void()
		' --- render example ---
		program.Start()
		
		'modify the shader based on mouse position
		program.SetUniform(angleLocation, angle)
		
		DrawRect(MouseX() -100, MouseY() -100, 200, 200)
		program.Finish()
	End
End

Class ShaderExample2 Extends ShaderExample
	Field image:Image
	Field program:ShaderProgram
	Field vertShader:Shader
	Field fragShader:Shader
	Field timeLocation:Int
	
	Method OnStart:Void()
		' --- setup example ---
		image = LoadImage("smiles.png", 1, Image.MidHandle)
		program = New ShaderProgram()
		vertShader = New Shader(VERTEX_SHADER)
		fragShader = New Shader(FRAGMENT_SHADER)

		'vert shader
		If vertShader.SetSource(LoadString("example2.vert")) = False
			Print "shader compile error: ~n" + vertShader.GetError()
		EndIf
		program.Attach(fragShader)
				
		'frag shader
		If fragShader.SetSource(LoadString("example2.frag")) = False
			Print "shader compile error: ~n" + fragShader.GetError()
		EndIf
		program.Attach(fragShader)
		
		'link
		If program.Link() = False
			Print "shader program link error: ~n" + program.GetError()
		EndIf
		
		'get uniform locations
		timeLocation = program.GetUniformLocation("time")
	End
	
	Method OnFinish:Void()
		' --- free example ---
		vertShader.Free()
		fragShader.Free()
		program.Free()
	End
	
	Method OnUpdate:Void()
		' --- update example ---
		
	End
	
	Method OnRender:Void()
		' --- render example ---
		program.Start()
		'update time
		program.SetUniform(timeLocation, Float(Millisecs())/1000.0)
		
		'draw image
		DrawImage(image, MouseX(), MouseY())
		program.Finish()
		
		Local time:= program.GetUniform(program.GetUniformLocation("time"), 0.0)
		DrawText(time, 5, 5)
	End
End