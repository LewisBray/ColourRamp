Colour ramp program:

This program receives four colour values from the user which define the 
corner colours of a 16x9 grid of pixels.  A linear colour ramp iscreated 
between the corner colours and displayed to the screen.

The program is invoked by a command line of the form:

	C:>ramp.exe display tl tr [bl] [br]

where,
display - the name of the display device (in this program it just checks 
	  that a display name was specified)
tl - the top-left colour value
tr - the top-right colour value
bl - the bottom-left colour value (defaults to tl if not specified)
br - the bottom-right colour value (defaults to tr if not specified)
(all colours are specified in RGB565 format in hex or decimal).

After receiving the command line from the user (and after some 
error handling) the program splits the user specified colours into their 
corresponding (R, G, B) colour values and stores these in a 16x9x3 frame 
buffer (16x9 as the display is a 16x9 grid of coloured pixels and the x3 
to hold the colour values).  Once the corner values of the display are 
set, a linear ramp is made from the top left to the bottom left and from 
the top right to the bottom right and stored in the frame buffer, it then 
goes row-wise and creates a linear ramp from the left-hand side to the 
right-hand side to fill out the rest of the frame buffer.  Once all values 
are set GLUT (using freeglut 3.0.0 for MinGW) is initialised and a 16x9 
grid is created and coloured appropriately with values from the frame 
buffer.  The program is closed by pressing ‘Esc’.

The linear map from colour_1 to colour_2 is achieved by breaking them down 
into their corresponding (R_1, G_1, B_1) and (R_2, G_2, B_3) colour values 
and linearly mapping each component to its corresponding component in the 
other colour, e.g. R_1 + p(R_2 – R_1), for 0 <= p <= 1 maps the red value 
for colour_1 to the red value for colour_2.  A gradient is defined which 
(using the red values example) is simply

(R_2 – R_1)/(no. of spaces between colour_1 and colour_2) 

so that we can iterate along the frame buffer to assign all values.
