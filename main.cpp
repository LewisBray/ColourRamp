#include <GL/glut.h>
#include <iostream>

#include "InputCheck.h"

using namespace std;

static double frame_buffer[16][9][3]; //Holds R, G, B colour values for 16x9 grid of pixels

void convert_to_ints(int &argc, char** argv, long colours[]);
void process_keys(unsigned char key, int x, int y);
void display_pixels(void);

class Display
{
    public:
            Display();
            void set_frame_buffer(long colour_tl, long colour_tr, long colour_bl, long colour_br);
    private:
            void set_corner_colours(long colour_tl, long colour_tr, long colour_bl, long colour_br);
            void RGB565toRGB(long colour, double colourRGB[]);
};

int main(int argc, char **argv)
{
    long colours[4]; //User specified colours array, 0 = tl, 1 = tr, 2 = bl, 3 = br
    for(int i = 0; i < 4; i++){colours[i] = 0;}


    /*User input checking and set-up*/
    if(!check_arg_count(argc)){return 0;} //Makes sure there are a valid number of user inputs

    if(!check_display_name(argv[1])){return 0;} //Makes sure the display name is specified/valid (i.e. not a number)

    if(!check_if_numbers(argc, argv)){return 0;} //Makes sure arguments 3 to 6 are numbers in the specified form

    convert_to_ints(argc, argv, colours); //Converts user inputs into integers and places into the colours array

    if(!check_if_colours_valid(colours)){return 0;} //Makes sure user inputted colours are in the range [0, 2^16 - 1]

    Display ramp; //Creates instance of Display class and initialises all frame_buffer values to 0.

    ramp.set_frame_buffer(colours[0], colours[1], colours[2], colours[3]); //Sets all values in frame_buffer ready for display


    /*Initiates GLUT and creates a window*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(320,320);
    glutCreateWindow("ramp");
    glutFullScreen();


    glutDisplayFunc(display_pixels); //Outputs pixel grid

    glutKeyboardFunc(process_keys); //Closes window when user presses 'ESC'

	glutMainLoop();

	return 0;
}

void convert_to_ints(int &argc, char** argv, long colours[])
{
    for(int i = 2; i < argc; i++) //Converts available user inputs into integers and assigns to colours array
    {
        if(argv[i][0] == '0' && argv[i][1] == 'x'){colours[i - 2] = strtol(argv[i], NULL, 0);}
        else{colours[i - 2] = strtol(argv[i], NULL, 10);}
    }

    switch(argc) //Assigns colours to bl and br if not specified
    {
    case 4: colours[2] = colours[0];
            colours[3] = colours[1];
            break;
    case 5: colours[3] = colours[1];
            break;
    }
}

void process_keys(unsigned char key, int x, int y)
{
    if(key == 27){exit(0);}
}

void display_pixels(void)
{
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Clears the colour to black before drawing
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION); //Sets coordinates, x: tl (0) -> tr (16) and y: tl (0) -> bl (9)
        glLoadIdentity();
        glOrtho(0, 16, 9, 0, 0, 1);

        for(int y = 0; y < 9; y++) //Prints pixels row-wise from tl to br, colouring with the frame_buffer values
        {
            for(int x = 0; x < 16; x++)
            {
                glColor3f(frame_buffer[x][y][0], frame_buffer[x][y][1], frame_buffer[x][y][2]);
                glBegin(GL_QUADS);
                glVertex2f(x, y);
                glVertex2f(x, y + 1);
                glVertex2f(x + 1, y + 1);
                glVertex2f(x + 1, y);
                glEnd();
            }
        }

        glPopMatrix();

        glutSwapBuffers();
}

/*Display class method definitions*/
Display::Display()
{
    memset(frame_buffer, 0, sizeof(frame_buffer));
}

void Display::set_frame_buffer(long colour_tl, long colour_tr, long colour_bl, long colour_br)
{
    set_corner_colours(colour_tl, colour_tr, colour_bl, colour_br);

    double corner_grad[2][3]; //gradient ((end colour value - start colour value)/(#spaces between))
                            //0 <=> left-hand side, 1 <=> right-hand side
    for(int x = 0; x < 3; x++)
    {
        corner_grad[0][x] = (frame_buffer[0][8][x] - frame_buffer[0][0][x])/8;
        corner_grad[1][x] = (frame_buffer[15][8][x] - frame_buffer[15][0][x])/8;
    }

    for(int y = 1; y < 8; y++) //Sets the frame_buffer values for the LHS and RHS by incrementing the diffRatio.
    {
        for(int z = 0; z < 3; z++)
        {
            frame_buffer[0][y][z] = frame_buffer[0][0][z] + y*corner_grad[0][z];
            frame_buffer[15][y][z] = frame_buffer[15][0][z] + y*corner_grad[1][z];
        }
    }

    for(int y = 0; y < 9; y++) //Goes row by row, calculates the gradient between each side and fills in the values
    {                          //between by incrementing the grad
        double grad[3];

        for(int z = 0; z < 3; z++){grad[z] = (frame_buffer[15][y][z] - frame_buffer[0][y][z])/15;}

        for(int x = 1; x < 15; x++)
        {
            for(int z = 0; z < 3; z++){frame_buffer[x][y][z] = frame_buffer[0][y][z] + x*grad[z];}
        }
    }
}

void Display::set_corner_colours(long colour_tl, long colour_tr, long colour_bl, long colour_br)
{
    RGB565toRGB(colour_tl, frame_buffer[0][0]); //Extracts top left colour's RGB values, stores it in tl of frame_buffer
    RGB565toRGB(colour_tr, frame_buffer[15][0]); //Extracts top right colour's RGB values, stores it in tr of frame_buffer
    RGB565toRGB(colour_bl, frame_buffer[0][8]); //etc...
    RGB565toRGB(colour_br, frame_buffer[15][8]);
}

void Display::RGB565toRGB(long colour, double colourRGB[])
{
    double r = (colour >> 11) & 31; //Red colour value, shifts colour 11 bits to the right, takes first 5 bits of memory
    double g = (colour >> 5) & 63; //etc...
    double b = colour & 31;

    colourRGB[0] = r/31; //0 <=> red values, 1 <=> green values, 2 <=> blue values
    colourRGB[1] = g/63;
    colourRGB[2] = b/31;
}
