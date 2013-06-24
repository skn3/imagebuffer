Strict

'version 7
' - updated to work with Monkey 71b+
' - fbos now working on opengl 2.0 :D
'version 6
' - can now set matrix uniform
'version 5
' - shaders are now usable
' - examples updated to be contained in class applets
' - set uniforms fully working (no matrix yet)
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
		Method _Free:Bool()
		Public
		Method SetSource:Bool(source:String) = "_SetSource"
		Method HasError:Bool() = "_HasError"
		Method GetError:String() = "_GetError"
		Method IsValid:Bool() = "_IsValid"
		Method HasSource:Bool() = "_HasSource"	
	End
	
	Class ShaderProgramNative
		Private
		Method _Init:Bool()
		Method _Free:Bool()
		Method _Attach:Bool(shader:ShaderNative)
		Method _Detach:Bool(shader:ShaderNative)
		Method _GetUniformLocation:Int(name:String)
		Method _SetUniformInt:Bool(location:Int, values:Int[], count:Int, size:Int)
		Method _SetUniformFloat:Bool(location:Int, values:Float[], count:Int, size:Int, columns:Int, rows:Int, transpose:bool = False)
		Method _GetUniformInt:Bool(location:Int, values:Int[])
		Method _GetUniformFloat:Bool(location:Int, values:Float[])
		Public
		Method HasError:Bool() = "_HasError"
		Method GetError:String() = "_GetError"
		Method Link:Bool() = "_Link"
		Method Start:Bool() = "_Start"
		Method Finish:Bool() = "_Finish"
	End

	Class FBONative
		Private
		Method _Init:bool()
		Method _Free:Bool()
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
		
		Method Free:Void()
			' --- destructor ---
			_Free()
		End
		
		Method Clear:Bool()
			' --- clear this shader ---
			SetSource("")
			Return True
		End
	End
	
	'shaderprogram
	Class ShaderProgram Extends ShaderProgramNative
		Private
		Field shaders:= New List<Shader>
		Field tempIntVec:Int[4]
		Field tempFloatVec:Float[4]
		Public
		
		Method New()
			' --- constructor ---
			If _Init() = False Error("Error Creating Shader Program")
		End
		
		Method Free:Void()
			' --- destructor ---
			Clear()
			_Free()
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
				_Detach(delNode.Value())
				delNode.Remove()
			Wend
			
			Return True
		End
		
		'set uniform api
		Method SetUniform:Bool(location:Int, value:Int)
			' --- set a uniform ---
			'this sets a single int
			'use temp vec array
			tempIntVec[0] = value
			
			'call the correct native method
			Return _SetUniformInt(location, tempIntVec, 1, 1)
		End
		
		Method SetUniform:Bool(location:Int, x:Int, y:Int)
			' --- set a uniform ---
			'this sets a vec2
			'use temp vec array
			tempIntVec[0] = x
			tempIntVec[1] = y
			
			'call the correct native method
			Return _SetUniformInt(location, tempIntVec, 1, 2)
		End
		
		Method SetUniform:Bool(location:Int, x:Int, y:Int, z:Int)
			' --- set a uniform ---
			'this sets a vec3
			'use temp vec array
			tempIntVec[0] = x
			tempIntVec[1] = y
			tempIntVec[2] = z
			
			'call the correct native method
			Return _SetUniformInt(location, tempIntVec, 1, 3)
		End
		
		Method SetUniform:Bool(location:Int, x:Int, y:Int, z:Int, w:Int)
			' --- set a uniform ---
			'this sets a vec4
			'use temp vec array
			tempIntVec[0] = x
			tempIntVec[1] = y
			tempIntVec[2] = z
			tempIntVec[3] = w
			
			'call the correct native method
			Return _SetUniformInt(location, tempIntVec, 1, 4)
		End
		
		Method SetUniform:Bool(location:Int, values:Int[], count:Int)
			' --- set a uniform ---
			'this sets an array of ints
			
			'get count
			If count < 1 count = values.Length
			
			'check there enough array elements
			If count > values.Length
				#IF CONFIG = "debug"
					Print "SetUniform(int array) not enough elements in array"
				#End
				Return False
			EndIf
			
			'call the correct native method
			Return _SetUniformInt(location, values, count, 1)
		End
		
		Method SetUniform:Bool(location:Int, values:Int[], size:Int, count:Int)
			' --- set a uniform ---
			'this sets an array of vec2, vec3 or vec4
			'check correct size is given
			If size < 2 or size > 4
				#IF CONFIG = "debug"
					Print "SetUniform(int vec" + size + ") invalid vec size"
				#End
				Return False
			EndIf
			
			'get count
			If count < 1 count = Floor(values.Length / size)
			
			'check tehre enough array elements
			If count * size > values.Length
				#IF CONFIG = "debug"
					Print "SetUniform(int vec"+size+") not enough elements in array"
				#End
				Return False
			EndIf
			
			'call the correct native method
			Return _SetUniformInt(location, values, count, size)
		End
		
		Method SetUniform:Bool(location:Int, value:Float)
			' --- set a uniform ---
			'this sets a single float
			'use temp vec array
			tempFloatVec[0] = value
			
			'call the correct native method
			Return _SetUniformFloat(location, tempFloatVec, 1, 1, 0, 0, False)
		End
		
		Method SetUniform:Bool(location:Int, x:Float, y:Float)
			' --- set a uniform ---
			'this sets a vec2
			'use temp vec array
			tempFloatVec[0] = x
			tempFloatVec[1] = y
			
			'call the correct native method
			Return _SetUniformFloat(location, tempFloatVec, 1, 2, 0, 0, False)
		End
		
		Method SetUniform:Bool(location:Int, x:Float, y:Float, z:Float)
			' --- set a uniform ---
			'this sets a vec3
			'use temp vec array
			tempFloatVec[0] = x
			tempFloatVec[1] = y
			tempFloatVec[2] = z
			
			'call the correct native method
			Return _SetUniformFloat(location, tempFloatVec, 1, 3, 0, 0, False)
		End
		
		Method SetUniform:Bool(location:Int, x:Float, y:Float, z:Float, w:Float)
			' --- set a uniform ---
			'this sets a vec4
			'use temp vec array
			tempFloatVec[0] = x
			tempFloatVec[1] = y
			tempFloatVec[2] = z
			tempFloatVec[3] = w
			
			'call the correct native method
			Return _SetUniformFloat(location, tempFloatVec, 1, 4, 0, 0, False)
		End
		
		Method SetUniform:Bool(location:Int, values:Float[], count:Int)
			' --- set a uniform ---
			'this sets an array of floats
			
			'get count
			If count < 1 count = values.Length
			
			'check there enough array elements
			If count > values.Length
				#IF CONFIG = "debug"
					Print "SetUniform(float array) not enough elements in array"
				#End
				Return False
			EndIf
			
			'call the correct native method
			Return _SetUniformFloat(location, values, count, 1, 0, 0, False)
		End
		
		Method SetUniform:Bool(location:Int, values:Float[], size:Int, count:Int)
			' --- set a uniform ---
			'this sets an array of vec2, vec3 or vec4
			'check correct size is given
			If size < 2 or size > 4
				#IF CONFIG = "debug"
					Print "SetUniform(float vec" + size + ") invalid vec size"
				#End
				Return False
			EndIf
			
			'get count
			If count < 1 count = Floor(values.Length / size)
			
			'check tehre enough array elements
			If count * size > values.Length
				#IF CONFIG = "debug"
					Print "SetUniform(float vec" + size + ") not enough elements in array"
				#End
				Return False
			EndIf
			
			'call the correct native method
			Return _SetUniformFloat(location, values, count, size, 0, 0, False)
		End
		
		Method SetUniform:Bool(location:Int, values:Float[], columns:Int, rows:Int, count:Int, transpose:Bool = False)
			' --- set a uniform ---
			'this sets an single/array of matrices
			'transpose dictates if the data is provided in column major or row major format (false = column major)
			
			'check correct size is given
			If columns < 2 or rows < 2 or columns > 4 or rows > 4
				#IF CONFIG = "debug"
					Print "SetUniform(matrix " + columns + "x" + rows + ") invalid matrix dimensions"
				#End
				Return False
			EndIf
			
			'get count
			If count < 1 count = Floor(values.Length / (columns * rows))
			
			'check tehre enough array elements
			If count * (columns * rows) > values.Length
				#IF CONFIG = "debug"
					Print "SetUniform(matrix " + columns + "x" + rows + ") not enough elements in array"
				#End
				Return False
			EndIf
			
			'call the correct native method
			Return _SetUniformFloat(location, values, count, 0, columns, rows, transpose)
		End
		
		'get uniform api
		Method GetUniformLocation:Int(name:String)
			' -- basic call to get uniform location ---
			Return _GetUniformLocation(name)
		End
		
		Method GetUniformLocation:Int(name:String, index:Int)
			' -- array call to get uniform location ---
			Return _GetUniformLocation(name + "[" + index + "]")
		End
		
		Method GetUniformLocation:Int(name:String, column:Int, row:Int, columns:Int, rows:Int)
			' -- matrix call to get uniform location ---
			Return _GetUniformLocation(name + "[" + ( (column * rows) + row + "]"))
		End
		
		Method GetUniform:Int(location:Int, defaultValue:Int)
			' --- get a uniform ---
			If _GetUniformInt(location, tempIntVec) = False
				'there was an error so return the default value
				Return defaultValue
			EndIf
			
			'return the retrieved value
			Return tempIntVec[0]
		End
		
		Method GetUniform:Bool(location:Int, values:Int[], size:Int)
			' --- get a uniform ---
			'this gets a vec2, vec3 or vec4
			'check correct size is given
			If size < 2 or size > 4
				#IF CONFIG = "debug"
					Print "GetUniform(int vec" + size + ") invalid vec size"
				#End
				Return False
			EndIf
			
			'check tehre enough array elements
			If size > values.Length
				#IF CONFIG = "debug"
					Print "GetUniform(int vec" + size + ") not enough elements in array"
				#End
				Return False
			EndIf
			
			'call the correct native method
			Return _GetUniformInt(location, values)
		End
		
		Method GetUniform:Float(location:Int, defaultValue:Float)
			' --- get a uniform ---
			If _GetUniformFloat(location, tempFloatVec) = False
				'there was an error so return the default value
				Return defaultValue
			EndIf
			
			'return the retrieved value
			Return tempFloatVec[0]
		End
		
		Method GetUniform:Bool(location:Int, values:Float[], size:Int)
			' --- get a uniform ---
			'this gets a vec2, vec3 or vec4
			'check correct size is given
			If size < 2 or size > 4
				#IF CONFIG = "debug"
					Print "GetUniform(float vec" + size + ") invalid vec size"
				#End
				Return False
			EndIf
			
			'check tehre enough array elements
			If size > values.Length
				#IF CONFIG = "debug"
					Print "GetUniform(float vec" + size + ") not enough elements in array"
				#End
				Return False
			EndIf
			
			'call the correct native method
			Return _GetUniformFloat(location, values)
		End
	End
		
	'fbo
	Class FBO Extends FBONative
		Method New()
			' --- constructor ---
			'init the fbo
			If _Init() = False Error("Error Creating FBO")
		End
		
		'Method Free:Void()
			' --- destructor ---
		'	_Free()
		'End
		
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
#end


