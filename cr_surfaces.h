#ifndef _CR_SURFACES_H_
#define _CR_SURFACES_H_

#include <cairo.h>
cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1280, 1000);
cairo_surface_t *cdu = cairo_image_surface_create_from_png("./images/cdu_base.png");
cairo_surface_t *warn_light_on = cairo_image_surface_create_from_png("./images/btn_lit/warn.png");
cairo_surface_t *warn_light_off = cairo_image_surface_create_from_png("./images/btn_unlit/warn.png");
cairo_surface_t *key_pad_on = cairo_image_surface_create_from_png("./images/btn_lit/key_pad.png");
cairo_surface_t *key_pad_off = cairo_image_surface_create_from_png("./images/btn_unlit/key_pad.png");
cairo_surface_t *bat_on = cairo_image_surface_create_from_png("./images/btn_lit/bat.png");
cairo_surface_t *bat_off = cairo_image_surface_create_from_png("./images/btn_unlit/bat.png");
cairo_surface_t *alert_on = cairo_image_surface_create_from_png("./images/btn_lit/alert.png");
cairo_surface_t *alert_off = cairo_image_surface_create_from_png("./images/btn_unlit/alert.png");
cairo_surface_t *insert_on = cairo_image_surface_create_from_png("./images/btn_lit/insert.png");
cairo_surface_t *insert_off = cairo_image_surface_create_from_png("./images/btn_unlit/insert.png");
cairo_surface_t *remote_on = cairo_image_surface_create_from_png("./images/btn_lit/remote.png");
cairo_surface_t *remote_off = cairo_image_surface_create_from_png("./images/btn_unlit/remote.png");
cairo_surface_t *hold_on = cairo_image_surface_create_from_png("./images/btn_lit/hold.png");
cairo_surface_t *hold_off = cairo_image_surface_create_from_png("./images/btn_unlit/hold.png");
cairo_surface_t *wyptchg_on = cairo_image_surface_create_from_png("./images/btn_lit/wypt_chg.png");
cairo_surface_t *wyptchg_off = cairo_image_surface_create_from_png("./images/btn_unlit/wypt_chg.png");
cairo_surface_t *wpt_num_digits = cairo_image_surface_create_from_png("./images/wpt_num.png");
cairo_surface_t *wpt_bkg = cairo_image_surface_create_from_png("./images/wpt_window.png");
cairo_surface_t *data_selector_knob = cairo_image_surface_create_from_png("./images/knobs/dataselect.png");
cairo_surface_t *auto_man_knob = cairo_image_surface_create_from_png("./images/knobs/auto-man-test.png");
cairo_surface_t *clear_off = cairo_image_surface_create_from_png("./images/btn_unlit/clear.png");
cairo_surface_t *clear_on = cairo_image_surface_create_from_png("./images/btn_lit/clear.png");
cairo_surface_t *dimmer = cairo_image_surface_create_from_png("./images/knobs/dimmer.png");
#endif