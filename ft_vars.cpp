#include "ft_vars.h"
#include "cairo_vars.h"
const char * fontdir;
const char * font_filename1;
const char * font_filename2;

void init_font()
{
    font_filename1 = "./Fonts/DSEG7Classic-Italic.ttf";
    font_filename2 = "./Fonts/NotoSansCJK-Bold.ttc"; 

    status = FT_Init_FreeType(&value);
    if (status != 0) 
    {
        fprintf (stderr, "Error %d opening library.\n", status);
        exit (EXIT_FAILURE);
    }
    status = FT_New_Face (value, font_filename1, 0, &ft_seven_seg);

    if (status != 0) 
    {
        fprintf (stderr, "Error %d opening %s.\n", status, font_filename1);
        exit (EXIT_FAILURE);
    }

    status = FT_Init_FreeType(&value);
    if (status != 0) 
    {
        fprintf (stderr, "Error %d opening library.\n", status);
        exit (EXIT_FAILURE);
    }
    status = FT_New_Face (value, font_filename2, 0, &ft_sans);

    if (status != 0) 
    {
        fprintf (stderr, "Error %d opening %s.\n", status, font_filename2);
        exit (EXIT_FAILURE);
    }

    seven_seg = cairo_ft_font_face_create_for_ft_face(ft_seven_seg, 0);
    sans = cairo_ft_font_face_create_for_ft_face(ft_sans, 0);
}