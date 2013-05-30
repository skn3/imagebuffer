imagebuffer
===========

Monkey ImageBuffer Module

This module requires one modification to monkey.

Add: 

```monkey
Method GetSurface:Surface()
	Return surface
End
```

to the _Class Image_ in _modules/mojo/graphics.monkey_