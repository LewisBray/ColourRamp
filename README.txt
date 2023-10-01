This program receives four colour values from the user which define the corner
colours of a 16x9 grid of pixels.  A linear colour ramp is created between the
corner colours and displayed to the screen.

The program is invoked by a command line of the form:

	C:>ramp.exe tl tr [bl] [br]

where, tl - the top-left colour value
       tr - the top-right colour value
       bl - the bottom-left colour value (defaults to tl)
       br - the bottom-right colour value (defaults to tr)

All colours are specified in RGB565 format in hex or decimal.

If we have four points in the xy-plane (0, 0), (15, 0), (0, 8) and (15, 8) with
associated z-axis values z_1, z_2, z_3 and z_4 respectively, then the linear
ramp function that is defined by these values is given by

    f(x, y) = a + bx + cy + dxy,

where, a = z_1
       b = (z_2 - z_1) / 15
       c = (z_3 - z_1) / 8
       d = (z_4 - z_3 - z_2 + z_1) / 120

which I'm not going to derive in a readme (may make a LaTeX doc for this).
