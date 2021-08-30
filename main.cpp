#include "acfutils/geom.h"
#include "cairo-ft.h"
#include "freetype/fttypes.h"
#include <cairo.h>
#include <acfutils/mt_cairo_render.h>
#include <acfutils/math.h>
#include <cmath>
#include <ft2build.h>
#include <locale>
#include <stdio.h>
#include <iostream>
#include <string>
#include "structs.h"
#include <vector>
#include "cr_surfaces.h"
#include FT_FREETYPE_H

#if IBM
	#include <windows.h>
#endif
#if LIN
	#include <GL/gl.h>
#elif __GNUC__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif


//cairo 


cairo_t *cr;
cairo_t *cr2;
cairo_font_face_t *seven_seg;
cairo_font_face_t *sans;
//freetype
static FT_Library value;
static FT_Face ft_seven_seg;
static FT_Face ft_sans;
FT_Error status;
const char * fontdir;
const char * seven_seg_fnt= "./Fonts/DSEG7Classic-Italic-1.ttf";
const char * sans_fnt= "./Fonts/NotoSansCJK-Bold.ttc";
int x, y;

void init_font()
{
    status = FT_Init_FreeType(&value);
    if (status != 0) 
    {
        fprintf (stderr, "Error %d opening library.\n", status);
        exit (EXIT_FAILURE);
    }
    status = FT_New_Face (value, seven_seg_fnt, 0, &ft_seven_seg);

    if (status != 0) 
    {
        fprintf (stderr, "Error %d opening %s.\n", status, seven_seg_fnt);
        exit (EXIT_FAILURE);
    }

    status = FT_Init_FreeType(&value);
    if (status != 0) 
    {
        fprintf (stderr, "Error %d opening library.\n", status);
        exit (EXIT_FAILURE);
    }
    status = FT_New_Face (value, sans_fnt, 0, &ft_sans);

    if (status != 0) 
    {
        fprintf (stderr, "Error %d opening %s.\n", status, sans_fnt);
        exit (EXIT_FAILURE);
    }

    seven_seg = cairo_ft_font_face_create_for_ft_face(ft_seven_seg, 0);
    sans = cairo_ft_font_face_create_for_ft_face(ft_sans, 0);
}

void n_s_light(bool on, bool north, bool test)
{
    cairo_set_font_face(cr, sans);
    cairo_set_font_size(cr, 60.0);
    
    cairo_set_source_rgb(cr, text_color.red, text_color.green, text_color.blue);

    if(on && north && !test)
    {
        cairo_move_to(cr, 526, 103);
        cairo_show_text(cr, "N");
        
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
        cairo_move_to(cr, 529, 157);
        cairo_show_text(cr, "S");
    }
    else if (on && !north && !test) 
    {
        cairo_move_to(cr, 529, 157);
        cairo_show_text(cr, "S");

        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
        cairo_move_to(cr, 526, 103);
        cairo_show_text(cr, "N");
    }

    else if (on && test) 
    {
        cairo_move_to(cr, 526, 103);
        cairo_show_text(cr, "N");
        cairo_move_to(cr, 529, 157);
        cairo_show_text(cr, "S");
    }

    else if(!on)
    {
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
        cairo_move_to(cr, 526, 103);
        cairo_show_text(cr, "N"); 
        cairo_move_to(cr, 529, 157);
        cairo_show_text(cr, "S");                 
    }
 
}

void e_w_light(bool on, bool east, bool test)
{
    cairo_set_font_face(cr, sans);
    cairo_set_font_size(cr, 60.0);    
    cairo_set_source_rgb(cr, text_color.red, text_color.green, text_color.blue);



    if(on && east && !test)
    {
        cairo_move_to(cr, 1118, 103);
        cairo_show_text(cr, "E");
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
        cairo_move_to(cr, 1111, 157);
        cairo_show_text(cr, "W");        
    }
    if(on && !east && !test)
    {
        cairo_move_to(cr, 1111, 157);
        cairo_show_text(cr, "W");
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
        cairo_move_to(cr, 1118, 103);
        cairo_show_text(cr, "E");        
    }
    if(on && test)
    {
        cairo_set_source_rgb(cr, text_color.red, text_color.green, text_color.blue);
        cairo_move_to(cr, 1118, 103);
        cairo_show_text(cr, "E");
        cairo_move_to(cr, 1111, 157);
        cairo_show_text(cr, "W");
    }
    else if(!on)
    {
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
        cairo_move_to(cr, 1118, 103);
        cairo_show_text(cr, "E");
        cairo_move_to(cr, 1111, 157);
        cairo_show_text(cr, "W");            
    }  
}

void left_display(cdu_t *cdu)
{   

    //display mask for blank segments
    cairo_set_font_face(cr, seven_seg);
    cairo_set_font_size(cr, 97.0);
    
    if(!cdu->displays.left_decimal)
    {
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue); //set to "off" color
        cairo_move_to(cr, 441, 158);
        cairo_show_text(cr, "."); 
    }
    
    if(!cdu->displays.left_degrees)
    {
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue); //set to off color
        cairo_move_to(cr, 290, 71);
        cairo_show_text(cr, ".");
    }
    if(!cdu->displays.left_deg2)
    {
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue); //set to off color
        cairo_move_to(cr, 526, 71);
        cairo_show_text(cr, ".");
    } 
    if(!cdu->displays.left_2dec_deg)
    {
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue); //set to "off" color
        cairo_move_to(cr, 362, 158);
        cairo_show_text(cr, ".");
    }
   

    if(cdu->displays.left_display_on)
    {        


        if(cdu->displays.left_degrees)
        {
            cairo_set_source_rgb(cr, on_color.red, on_color.green, on_color.blue); //set to off color
            cairo_move_to(cr, 290, 71);
            cairo_show_text(cr, ".");
        }

        if(cdu->displays.left_deg2)
        {
            cairo_set_source_rgb(cr, text_color.red, text_color.green, text_color.blue); //set to "off" color
            cairo_move_to(cr, 526, 71);
            cairo_show_text(cr, "."); 
        }

        if(cdu->displays.left_2dec_deg)
        {
            cairo_set_source_rgb(cr, text_color.red, text_color.green, text_color.blue); //set to "on" color
            cairo_move_to(cr, 362, 158);
            cairo_show_text(cr, ".");             
        }
        if(cdu->displays.left_decimal)
        {
            cairo_set_source_rgb(cr, text_color.red, text_color.green, text_color.blue); //set to "off" color
            cairo_move_to(cr, 441, 158);
            cairo_show_text(cr, ".");
        }        


        cairo_set_source_rgb(cr, text_color.red, text_color.green, text_color.blue); //set to "on" color
        cairo_move_to(cr, 124, 157); //move to start of display line 

        char buffer[1];

        for (int i = 0; i < 5; ++i)
        {
            sprintf(buffer, "%c", cdu->displays.left_digits[i]);
            cairo_show_text(cr, buffer);
        }  
    }

    n_s_light(cdu->displays.ns_on, cdu->displays.north_on, cdu->test_pressed);
     
}

void right_display(cdu_t *cdu)
{
    cairo_set_font_face(cr, seven_seg);
    cairo_set_font_size(cr, 97.0);
    
    if(!cdu->displays.right_decimal)
    {
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue); //set to "off" color
        cairo_move_to(cr, 1035, 157);
        cairo_show_text(cr, ".");           
    }
    if(!cdu->displays.right_degrees)
    {
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue); //set to off color
        cairo_move_to(cr, 883, 71);
        cairo_show_text(cr, ".");
    }

    if(!cdu->displays.right_dec_deg)
    {
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue); //set to off color
        cairo_move_to(cr, 1118, 71);
        cairo_show_text(cr, ".");
    }     

    if(cdu->displays.right_display_on)
    {    
        if(cdu->displays.right_degrees)
        {
            cairo_set_source_rgb(cr, text_color.red, text_color.green, text_color.blue); //set to "on" color
            cairo_move_to(cr, 883, 71);
            cairo_show_text(cr, ".");
        }


        if(cdu->displays.right_decimal)
        {
            cairo_set_source_rgb(cr, text_color.red, text_color.green, text_color.blue); //set to "on" color
            cairo_move_to(cr, 1035, 157);
            cairo_show_text(cr, ".");        
        }    
        
        if(cdu->displays.right_dec_deg)
        {
            cairo_set_source_rgb(cr, text_color.red, text_color.green, text_color.blue); //set to "off" color
            cairo_move_to(cr, 1118, 71);
            cairo_show_text(cr, "."); 
        }

        cairo_move_to(cr, 638, 157);
        cairo_set_source_rgb(cr, text_color.red, text_color.green, text_color.blue); //set to "on" color    
        char buffer[1];

        for (int i = 0; i < 6; ++i)
        {
            sprintf(buffer, "%c", cdu->displays.right_digits[i]);
            cairo_show_text(cr, buffer);
        }  
    }
    
    e_w_light(cdu->displays.ew_on, cdu->displays.east_on, cdu->test_pressed);
}

void from_display(cdu_t *cdu) //add flashing function
{
    cairo_set_font_face(cr, seven_seg);
    cairo_set_font_size(cr, 92.0);

    if(cdu->displays.nav_from_on)
    {
        cairo_move_to(cr, 491, 487);
        cairo_set_source_rgb(cr, text_color.red, text_color.green, text_color.blue);
        std::string tmp = std::to_string(cdu->displays.nav_from);
        const char * from = tmp.c_str();
        cairo_show_text(cr, from);
    }
}

void to_display(cdu_t *cdu) //add flashing function
{
    cairo_set_font_face(cr, seven_seg);
    cairo_set_font_size(cr, 92.0);

    if(cdu->displays.nav_to_on)
    {
        std::string tmp = std::to_string(cdu->displays.nav_to);
        const char * to = tmp.c_str();
    
        cairo_set_source_rgb(cr, text_color.red, text_color.green, text_color.blue);
        cairo_move_to(cr, 566, 487);
        cairo_show_text(cr, to);
    }

}

void warn_lit(cdu_t *cdu)
{
    x = 1055;
    y = 229;    
    if(cdu->warn_on)
    {
        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, warn_light_on, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }
    if(!cdu->warn_on)
    {
        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, warn_light_off, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }    
}

void numpad_lit(cdu_t *cdu)
{
    x = 737;
    y = 400;    
    if(cdu->keypad_on)
    {
        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, key_pad_on, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }
    if(!cdu->keypad_on)
    {
        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, key_pad_off, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }    
}

void bat_lit(cdu_t *cdu)
{
    x = 898;
    y = 229;
    if(cdu->bat_on)
    {
        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, bat_on, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }
    if(!cdu->bat_on)
    {
        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, bat_off, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }    
}

void alert_lit(cdu_t *cdu)
{
    x = 741;
    y = 229;
    if(cdu->alert_on)
    {

        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, alert_on, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }
    if(!cdu->alert_on)
    {
        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, alert_off, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }    
}

void insert_lit(cdu_t *cdu)
{
    x = 485;
    y = 229;
    if(cdu->insert_on)
    {

        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, insert_on, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }
    if(!cdu->insert_on)
    {
        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, insert_off, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }    
}

void remote_lit(cdu_t *cdu)
{
    x = 281;
    y = 229;
    if(cdu->remote_on)
    {

        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, remote_on, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }
    if(!cdu->remote_on)
    {
        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, remote_off, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }    
}

void hold_lit(cdu_t *cdu)
{
    x = 124;
    y = 229;

    if(cdu->hold_on)
    {

        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, hold_on, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }
    if(!cdu->hold_on)
    {
        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, hold_off, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }    
}

void wyptchg_lit(cdu_t *cdu)
{
    x = 560;
    y = 552;
    if(cdu->wypt_chg_on)
    {
        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, wyptchg_on, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }
    if(!cdu->wypt_chg_on)
    {
        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, wyptchg_off, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }    
}

void clear_lit(cdu_t *cdu)
{
    int x = 930;
    int y = 845;

    if(cdu->clear_on)
    {
        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, clear_on, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }
    if(!cdu->clear_on)
    {
        cairo_save(cr);
        cairo_translate(cr, x, y);
        cairo_set_source_surface(cr, clear_off, 0, 0);
        cairo_paint(cr);
        cairo_restore(cr);
    }    
}

void wpt_sel(cdu_t *cdu)
{
    int num = cdu->wpt_num;
    y = 360;
    int offset[10] = {0, 60, 113, 168, 223, 279, 334, 387, 443, 498};
    x = 253 - offset[num];
    cairo_save(cr);
    cairo_translate(cr, x, y);
    cairo_set_source_surface(cr, wpt_num_digits, 0, 0);
    cairo_paint(cr);
    cairo_restore(cr);    
}

void wpt_sel_bkg()
{
    x = 227;
    y = 369;
    cairo_save(cr);
    cairo_translate(cr, x, y);
    cairo_set_source_surface(cr, wpt_bkg, 0, 0);
    cairo_paint(cr);
    cairo_restore(cr);
}

void data_selector(cdu_t *cdu)
{
    float width_2 = 116;
    float height_2 = 117.5;
    int x = 247;
    int y = 730;
    float radians = DEG2RAD(cdu->data_sel);
    cairo_save(cr);

    cairo_translate(cr, x, y);
    cairo_rotate(cr, radians);
    cairo_translate(cr, -width_2, -height_2);

    cairo_set_source_surface(cr, data_selector_knob, 0,0);
    cairo_paint(cr);
    cairo_restore(cr);  

}

void text_dimmer(cdu_t *cdu)
{
    
    float max = 1;
    float min = 0.5;

    float dim_val = (((90 - cdu->brightness_knob_ang) / 90) * (max - min)) + min;
    
    text_color.red = on_color.red * dim_val;
    text_color.green = on_color.green * dim_val;
    text_color.blue = on_color.blue * dim_val;

}

void brightness_knob(cdu_t *cdu)
{
    float width_2 = 54;
    float height_2 = 54;
    int x = 247;
    int y = 730;
    float radians = -DEG2RAD(cdu->brightness_knob_ang);
    cairo_save(cr);

    cairo_translate(cr, x, y);
    cairo_rotate(cr, radians);
    cairo_translate(cr, -width_2, -height_2);

    cairo_set_source_surface(cr, dimmer, 0,0);
    cairo_paint(cr);
    cairo_restore(cr);
    text_dimmer(cdu);
}

void auto_man(cdu_t *cdu)
{
    float width_2 = 56;
    float height_2 = 58;
    int x = 477;
    int y = 913;
    float radians = DEG2RAD(cdu->sequence);
    cairo_save(cr);

    cairo_translate(cr, x, y);
    cairo_rotate(cr, radians);
    cairo_translate(cr, -width_2, -height_2);
    cairo_set_source_surface(cr, auto_man_knob, 0,0);
    cairo_paint(cr);
    cairo_restore(cr);

}

void screen_format(cdu_t *cdu)
{
    switch (cdu->data_sel) 
    {
        case TKGS:
            cdu->displays.left_degrees = false;
            cdu->displays.right_degrees = false;
            cdu->displays.left_decimal = true;
            cdu->displays.right_decimal = false;
            cdu->displays.left_deg2 = true;
            cdu->displays.right_dec_deg = false;
            cdu->displays.nav_from_on = true;
            cdu->displays.nav_to_on = true;
            break;

        case HDG:
            cdu->displays.left_degrees = false;
            cdu->displays.right_degrees = false;
            cdu->displays.left_decimal = true;
            cdu->displays.right_decimal = false;
            cdu->displays.left_deg2 = true;
            cdu->displays.right_dec_deg = false;
            cdu->displays.nav_from_on = true;
            cdu->displays.nav_to_on = true;
            break;
        case XTK:
            cdu->displays.left_2dec_deg = true;
            cdu->displays.left_deg2 = false;
            cdu->displays.left_decimal = false;
            cdu->displays.left_degrees = false;
            cdu->displays.ns_on = false;

            cdu->displays.right_degrees = false;
            cdu->displays.right_dec_deg = true;
            cdu->displays.right_decimal = false;
            cdu->displays.ew_on = false;

            cdu->displays.nav_from_on = true;
            cdu->displays.nav_to_on = true;            
            break;

        case POS:
            cdu->displays.left_degrees = true;
            cdu->displays.left_decimal = true;
            cdu->displays.ns_on = true;
            cdu->displays.left_2dec_deg = false;
            cdu->displays.left_deg2 = false;

            cdu->displays.right_degrees = true;
            cdu->displays.right_decimal = true;
            cdu->displays.ew_on = true;
            cdu->displays.right_dec_deg = false;

            cdu->displays.nav_from_on = true;
            cdu->displays.nav_to_on = true;            
            break;

        case WAYPT:
            cdu->displays.left_degrees = true;
            cdu->displays.left_decimal = true;
            cdu->displays.ns_on = true;
            cdu->displays.left_2dec_deg = false;
            cdu->displays.left_deg2 = false;

            cdu->displays.right_degrees = true;
            cdu->displays.right_decimal = true;
            cdu->displays.ew_on = true;
            cdu->displays.right_dec_deg = false;

            cdu->displays.nav_from_on = true;
            cdu->displays.nav_to_on = true;            
            break;

        case DIS:
            cdu->displays.left_deg2 = false;
            cdu->displays.left_2dec_deg = false;
            cdu->displays.left_decimal = false;
            cdu->displays.left_degrees = false;
            cdu->displays.ns_on = false;

            cdu->displays.right_decimal = true;
            cdu->displays.right_dec_deg = false;
            cdu->displays.right_degrees = false;
            cdu->displays.ew_on = false;

            cdu->displays.nav_from_on = true;
            cdu->displays.nav_to_on = true;            
            break;

        case WIND:
            cdu->displays.left_decimal = false;
            cdu->displays.left_2dec_deg = false;
            cdu->displays.left_degrees = false;

            if(cdu->hold_pressed)
            {
                cdu->displays.left_deg2 = false;
                cdu->displays.ns_on = true;
                cdu->displays.ew_on = true;
            }
            else if(!cdu->hold_pressed)
            {
                cdu->displays.left_deg2 = true;                
                cdu->displays.ns_on = false;
                cdu->displays.ew_on = false;
            }

            cdu->displays.right_dec_deg = false;
            cdu->displays.right_decimal = false;
            cdu->displays.right_degrees = false;

            cdu->displays.nav_from_on = true;
            cdu->displays.nav_to_on = true;            
            break;
        
        case STS:
            cdu->displays.left_deg2 = true;
            cdu->displays.left_decimal = false;
            cdu->displays.left_2dec_deg = false;
            cdu->displays.left_degrees = false;
            cdu->displays.ns_on = false;

            cdu->displays.right_decimal = false;
            cdu->displays.right_dec_deg = false;
            cdu->displays.right_degrees = false;
            cdu->displays.ew_on = false;

            cdu->displays.nav_from_on = true;
            cdu->displays.nav_to_on = true;            
            break;
    }
}

void load_digits(cdu_t* cdu, char display_str[14])
{
    for (int i = 0; i < 14; ++i)
    {
        if (i < 5)
        {
            cdu->displays.left_digits[i] = display_str[i];
        }

        if (i > 4 && i < 11)
        {
            cdu->displays.right_digits[i-5] = display_str[i];
        }

        if (i == 11 && display_str[i] == 'N')
        {
            cdu->displays.north_on = true;
        }
        if (i == 11 && display_str[i] == 'S')
        {
            cdu->displays.north_on = false;
        }
        if (i == 12 && display_str[i] == 'E')
        {
            cdu->displays.east_on = true;
        }
        if (i == 12 && display_str[i] == 'W')
        {
            cdu->displays.east_on = false;
        }        
    }
}

void test_mode_set(cdu_t *cdu)
{

    char test_vals[14];

    for(int i = 0; i < 14; ++i)
    {
        if(i != 13)
        {
            test_vals[i] = '8';
        }
        if (i == 14)
        {
            test_vals[i] = '\0';
        }
    }

    load_digits(cdu, test_vals);

    cdu->displays.left_degrees = true;
    cdu->displays.right_degrees = true;
    cdu->displays.left_decimal = true;
    cdu->displays.right_decimal = true;
    cdu->displays.left_deg2 = true;
    cdu->displays.right_dec_deg = true;
    cdu->displays.left_2dec_deg = true;

    cdu->displays.nav_from_on = true;
    cdu->displays.nav_to_on = true;
    cdu->displays.nav_from = 8;
    cdu->displays.nav_to = 8;

    cdu->hold_on = true;
    cdu->remote_on = true;
    cdu->insert_on = true;
    cdu->alert_on = true;
    cdu->bat_on = true;
    cdu->warn_on = true;
    cdu->wypt_chg_on = true;
    cdu->clear_on = true;
    cdu->keypad_on = true;


    left_display(cdu);
    right_display(cdu);
    from_display(cdu);
    to_display(cdu);
    hold_lit(cdu);
    remote_lit(cdu);
    insert_lit(cdu);
    alert_lit(cdu);
    bat_lit(cdu);
    warn_lit(cdu);
    wyptchg_lit(cdu);
    clear_lit(cdu);
    numpad_lit(cdu);   

}

void display_logic(cdu_t *cdu, char disp_vals[14])
{
    if(cdu->test_pressed)
    {
        test_mode_set(cdu);
    }
    else if (!cdu->test_pressed)
    {
        screen_format(cdu);
        load_digits(cdu, disp_vals);
        hold_lit(cdu);
        remote_lit(cdu);
        insert_lit(cdu);
        alert_lit(cdu);
        bat_lit(cdu);
        warn_lit(cdu);
        wyptchg_lit(cdu);
        clear_lit(cdu);
        numpad_lit(cdu);        
    }
}


int main ()
{
    //write the data to the CDU display
    cdu_data.data_sel = STS;
    cdu_data.displays.left_display_on = true;
    cdu_data.displays.right_display_on = true;
    cdu_data.test_pressed = false;
    cdu_data.wpt_num = 0;
    cdu_data.brightness_knob_ang = 0;

    cdu_data.displays.nav_from = 1;
    cdu_data.displays.nav_to = 2;
    cdu_data.hold_pressed = false;

    char display_vals[14] = {'!', '!', '3', '5', '9', '0', '!', '!', '!', '5', '5', 'S', 'W', '\0'};


    //load_digits(&cdu_data, display_vals);

    cr = cairo_create(surface);
    init_font();
    cairo_set_source_rgba(cr, 0,0,0,1);
    cairo_paint(cr);
    wpt_sel_bkg();
    wpt_sel(&cdu_data);


    cairo_set_source_surface(cr, cdu, 0, 0);
    cairo_paint(cr);
    //test_mode_set(&cdu_data);


    //knobs
    data_selector(&cdu_data);
    screen_format(&cdu_data);
    brightness_knob(&cdu_data);
    display_logic(&cdu_data, display_vals);
    auto_man(&cdu_data);

    //buttons


    //displays
    left_display(&cdu_data);
    right_display(&cdu_data);
    from_display(&cdu_data);
    to_display(&cdu_data);


    cairo_surface_write_to_png(surface, "img.png");

    cairo_destroy(cr);

    cairo_surface_destroy(surface );
    cairo_surface_destroy(cdu);
    cairo_surface_destroy(warn_light_on);
    cairo_surface_destroy(warn_light_off);
    cairo_surface_destroy(key_pad_on);
    cairo_surface_destroy(key_pad_off);
    cairo_surface_destroy(bat_on );
    cairo_surface_destroy(bat_off);
    cairo_surface_destroy(alert_on );
    cairo_surface_destroy(alert_off);
    cairo_surface_destroy(insert_on);
    cairo_surface_destroy(insert_off );
    cairo_surface_destroy(remote_on);
    cairo_surface_destroy(remote_off );
    cairo_surface_destroy(hold_on);
    cairo_surface_destroy(hold_off);
    cairo_surface_destroy(wyptchg_on );
    cairo_surface_destroy(wyptchg_off);
    cairo_surface_destroy(wpt_num_digits);
    cairo_surface_destroy(wpt_bkg);
    cairo_surface_destroy(data_selector_knob);

}