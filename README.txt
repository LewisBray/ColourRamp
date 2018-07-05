This program receives four colour values from the user which define the corner
colours of a 16x9 grid of pixels.  A linear colour ramp is created between the
corner colours and displayed to the screen.

The program is invoked by a command line of the form:

	C:>ramp.exe display tl tr [bl] [br]

where,	display - the name of the display device (in this program it just checks
	  							that a display name was specified)
						 tl - the top-left colour value
						 tr - the top-right colour value
						 bl	- the bottom-left colour value (defaults to tl)
						 br	- the bottom-right colour value (defaults to tr)

All colours are specified in RGB565 format in hex or decimal.

If we have four points in the xy-plane (0, 0), (15, 0), (0, 8) and (15, 8) with
associated z-axis values z_1, z_2, z_3 and z_4 respectively, then the linear
ramp function that is defined by these values is given by

		f(x, y) = a + bx + cy + dxy,

where, a = z_1
			 b = (z_2 - z_1) / 15
			 c = (z_3 - z_1) / 8
			 d = (z_4 - z_3 - z_2 + z_1) / 120

which I'm not going to derive in a readme (may make a LaTeX doc for this).  The
z values in our case are RGB565 values and so operations like +, *, etc... are
sensitive to the underlying RGB values and so in order to keep the structure of
the above formula we create a class for manipulating RGB565 values.

This is now implemented in modern OpenGL.  Unfortunately my laptop doesn't
support some of the modern OpenGL features (most notably layout locations) but
it's using shaders which I believe is mostly the point.  The abstractions of the
OpenGL constructs into classes are not particularly general but it does hide a
lot of the OpenGL code and breaks it down to the general algorithm whilst
providing resource management (deleting buffers in constructors, etc...).  In a
project like a game engine these classes would need to be more flexible.  This
project uses GLFW and GLEW to implement OpenGL.

Going forward I need to make it display in full screen and close when the user
presses 'Esc'.
