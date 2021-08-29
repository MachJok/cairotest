#include "displ_funct.h"
#include "structs.h"
#include "cairo_vars.h"
#include <stdio.h>
#include <cmath>
#include <string>
#include "ft_vars.h"

void n_s_light(bool on, bool north)
{
    cairo_set_font_face(cr, sans);
    cairo_set_font_size(cr, 60.0);
    
    cairo_set_source_rgb(cr, on_color.red, on_color.green, on_color.blue);

    if(on && north)
    {
        cairo_move_to(cr, 526, 103);
        cairo_show_text(cr, "N");
        
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
        cairo_move_to(cr, 529, 157);
        cairo_show_text(cr, "S");
    }
    else if (on && !north) 
    {
        cairo_move_to(cr, 529, 157);
        cairo_show_text(cr, "S");

        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
        cairo_move_to(cr, 526, 103);
        cairo_show_text(cr, "N");
    }
    else
    {
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
        cairo_move_to(cr, 526, 103);
        cairo_show_text(cr, "N"); 
        cairo_move_to(cr, 529, 157);
        cairo_show_text(cr, "S");                 
    }
 
}

void e_w_light(bool on, bool east)
{
    cairo_set_font_face(cr, sans);
    cairo_set_font_size(cr, 60.0);    
    cairo_set_source_rgb(cr, on_color.red, on_color.green, on_color.blue);

    if(on && east)
    {
        cairo_move_to(cr, 1118, 103);
        cairo_show_text(cr, "E");
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
        cairo_move_to(cr, 1111, 157);
        cairo_show_text(cr, "W");        
    }
    if(on && !east)
    {
        cairo_move_to(cr, 1111, 157);
        cairo_show_text(cr, "W");
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
        cairo_move_to(cr, 1118, 103);
        cairo_show_text(cr, "E");        
    }
    else
    {
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
        cairo_move_to(cr, 1118, 103);
        cairo_show_text(cr, "E");
        cairo_move_to(cr, 1111, 157);
        cairo_show_text(cr, "W");            
    }  
}


void left_display(double nums[5], int size, bool disp_on, bool deg, bool decimal, bool north, bool south)
{   

    //display mask for blank segments
    cairo_move_to(cr, 124, 157);
    cairo_set_font_face(cr, seven_seg);
    cairo_set_font_size(cr, 97.0);
    cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
    cairo_show_text(cr, "88888");

    if(!decimal)
    {
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue); //set to "off" color
        cairo_move_to(cr, 441, 158);
        cairo_show_text(cr, "."); 
    }
    if(!deg)
    {
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue); //set to off color
        cairo_move_to(cr, 290, 71);
        cairo_show_text(cr, ".");
    }

    if(disp_on)
    {        
        if(deg)
        {
            cairo_set_source_rgb(cr, on_color.red, on_color.green, on_color.blue); //set to "on" color
            cairo_move_to(cr, 290, 71);
            cairo_show_text(cr, ".");
        }


        if(decimal)
        {
            cairo_set_source_rgb(cr, on_color.red, on_color.green, on_color.blue); //set to "on" color
            cairo_move_to(cr, 441, 158);
            cairo_show_text(cr, ".");
        }


        cairo_set_source_rgb(cr, on_color.red, on_color.green, on_color.blue); //set to "on" color
        cairo_move_to(cr, 124, 157); //move to start of display line 

        char buffer[1];

        for (int i = 0; i < 5; ++i)
        {
            if(std::isnan(nums[i]))
            {
                snprintf(buffer, size, "!");
                cairo_show_text(cr, buffer);            
            }
            else if(!std::isnan(nums[i]))
            {
                snprintf(buffer, size, "%.0f", nums[i]);
                cairo_show_text(cr, buffer);
            }
        }  
    }
    if(north)
    {
        n_s_light(true, true);
    }
    else if (south) 
    {
        n_s_light(true, false);
    }
    else if(!north && !south)
    {
        n_s_light(false, false);
    }      
}

void right_display(double nums[6], int size, bool disp_on, bool deg, bool decimal, bool east, bool west)
{
    cairo_set_font_face(cr, seven_seg);
    cairo_set_font_size(cr, 97.0);
    cairo_move_to(cr, 638, 157);
    cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
    cairo_show_text(cr, "888888");
    
    if(!decimal)
    {
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue); //set to "off" color
        cairo_move_to(cr, 1035, 157);
        cairo_show_text(cr, ".");           
    }
    if(!deg)
    {
        cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue); //set to off color
        cairo_move_to(cr, 883, 71);
        cairo_show_text(cr, ".");
    }

    if(disp_on)
    {    
        if(deg)
        {
            cairo_set_source_rgb(cr, on_color.red, on_color.green, on_color.blue); //set to "on" color
            cairo_move_to(cr, 883, 71);
            cairo_show_text(cr, ".");
        }


        if(decimal)
        {
            cairo_set_source_rgb(cr, on_color.red, on_color.green, on_color.blue); //set to "on" color
            cairo_move_to(cr, 1035, 157);
            cairo_show_text(cr, ".");        
        }    

        cairo_move_to(cr, 638, 157);
        cairo_set_source_rgb(cr, on_color.red, on_color.green, on_color.blue); //set to "on" color    
        char buffer[1];

        for (int i = 0; i < 6; ++i)
        {
            if(std::isnan(nums[i]))
            {
                snprintf(buffer, size, "!");
                cairo_show_text(cr, buffer);            
            }
            else if(!std::isnan(nums[i]))
            {
                snprintf(buffer, size, "%.0f", nums[i]);
                cairo_show_text(cr, buffer);
            }

        }

    }
    if(east)
    {
        e_w_light(true, true);
    }
    else if (west) 
    {
        e_w_light(true, false);
    }
    else if(!east && !west)
    {
        e_w_light(false, false);
    }
}

void from_pt(int frm)
{
    cairo_set_font_face(cr, seven_seg);
    cairo_set_font_size(cr, 92.0);
    cairo_move_to(cr, 491, 487);
    cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
    cairo_show_text(cr, "8");

    cairo_move_to(cr, 491, 487);
    cairo_set_source_rgb(cr, on_color.red, on_color.green, on_color.blue);
    std::string tmp = std::to_string(frm);
    const char * from = tmp.c_str();
    cairo_show_text(cr, from);    
}

void to_pt(int to_i)
{
    cairo_set_font_face(cr, seven_seg);
    cairo_set_font_size(cr, 92.0);
    cairo_move_to(cr, 566, 487);
    cairo_set_source_rgb(cr, off_color.red, off_color.green, off_color.blue);
    cairo_show_text(cr, "8");

    std::string tmp = std::to_string(to_i);
    const char * to = tmp.c_str();
  
    cairo_set_source_rgb(cr, on_color.red, on_color.green, on_color.blue);
    cairo_move_to(cr, 566, 487);
    cairo_show_text(cr, to);       

}