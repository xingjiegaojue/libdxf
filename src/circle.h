/*!
 * \file circle.h
 *
 * \author Copyright (C) 2008 ... 2016 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF circle entity (\c CIRCLE).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
 * \version According to DXF R13.
 * \version According to DXF R14.
 *
 * <hr>
 * <h1><b>Copyright Notices.</b></h1>\n
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.\n\n
 * This program is distributed in the hope that it will be useful, but
 * <b>WITHOUT ANY WARRANTY</b>; without even the implied warranty of
 * <b>MERCHANTABILITY</b> or <b>FITNESS FOR A PARTICULAR PURPOSE</b>.\n
 * See the GNU General Public License for more details.\n\n
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to:\n
 * Free Software Foundation, Inc.,\n
 * 59 Temple Place,\n
 * Suite 330,\n
 * Boston,\n
 * MA 02111 USA.\n
 * \n
 * Drawing eXchange Format (DXF) is a defacto industry standard for the
 * exchange of drawing files between various Computer Aided Drafting
 * programs.\n
 * DXF is an industry standard designed by Autodesk(TM).\n
 * For more details see http://www.autodesk.com.
 * <hr>
 */


#ifndef LIBDXF_SRC_CIRCLE_H
#define LIBDXF_SRC_CIRCLE_H


#include "global.h"
#include "point.h"
#include "binary_graphics_data.h"

/*!
 * \brief DXF definition of a circle entity (\c CIRCLE).
 */
typedef struct
dxf_circle_struct
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *linetype;
                /*!< The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Group code = 6. */
        char *layer;
                /*!< Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given.\n
                 * Group code = 8. */
        double elevation;
                /*!< Elevation of the entity in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default).\n
                 * Group code = 38.\n
                 * \deprecated As of version R11. */
        double thickness;
                /*!< Thickness of the entity in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file.\n
                 * Group code = 39. */
        double linetype_scale;
                /*!< Linetype scale (optional).\n
                 * Group code = 48.\n
                 * \since Introduced in version R13. */
        int16_t visibility;
                /*!< Object visibility (optional):\n
                 * <ol>
                 * <li value = "0"> Visible</li>
                 * <li value = "1"> Invisible</li>
                 * </ol>
                 * Group code = 60.\n
                 * \since Introduced in version R13. */
        int color;
                /*!< Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity.\n
                 * Group code = 62. */
        int paperspace;
                /*!< Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0).\n
                 * Group code = 67.\n
                 * \since Introduced in version R13. */
        int graphics_data_size;
                /*!< Number of bytes in the proxy entity graphics
                 * represented in the sub-sequent 310 groups, which are
                 * binary chunk records (optional).\n
                 * Group code = 92.\n
                 * \since Introduced in version R2000.\n
                 * \warning On some 64 bit workstations output is
                 * generated with group code "160", thus omitting group
                 * code "92". */
        int16_t shadow_mode;
                /*!< Shadow mode:\n
                 * <ol>
                 * <li value = "0"> Casts and receives shadows.</li>
                 * <li value = "1"> Casts shadows.</li>
                 * <li value = "2"> Receives shadows.</li>
                 * <li value = "3"> Ignores shadows.</li>
                 * </ol>\n
                 * Group code = 284.\n
                 * \since Introduced in version R2009. */
        DxfBinaryGraphicsData *binary_graphics_data;
                /*!< Proxy entity graphics data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional).\n
                 * Group code = 310.\n
                 * \since Introduced in version R2000. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330.\n
                 * \since Introduced in version R14. */
        char *material;
                /*!< Hard-pointer ID/handle to material object (present if
                 * not BYLAYER).\n
                 * Group code = 347.\n
                 * \since Introduced in version R2008. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360.\n
                 * \since Introduced in version R14. */
        int16_t lineweight;
                /*!< Lineweight enum value.\n
                 * Stored and moved around as a 16-bit integer.\n
                 * Group code = 370.\n
                 * \since Introduced in version R2002. */
        char *plot_style_name;
                /*!< Hard pointer ID / handle of PlotStyleName object.\n
                 * Group code = 390.\n
                 * \since Introduced in version R2009. */
        long color_value;
                /*!< A 24-bit color value that should be dealt with in
                 * terms of bytes with values of 0 to 255.\n
                 * The lowest byte is the blue value, the middle byte is
                 * the green value, and the third byte is the red value.\n
                 * The top byte is always 0.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 420.\n
                 * \since Introduced in version R2004. */
        char *color_name;
                /*!< Color name.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 430.\n
                 * \since Introduced in version R2004. */
        long transparency;
                /*!< Transparency value.\n
                 * The group code cannot be used by custom entities for
                 * their own data because the group code is reserved for
                 * AcDbEntity, class-level color data and AcDbEntity,
                 * class-level transparency data.\n
                 * Group code = 440.\n
                 * \since Introduced in version R2004. */
        /* Specific members for a DXF circle. */
        DxfPoint *p0;
                /*!< Base point.\n
                 * Group codes = 10, 20 and 30.*/
        double radius;
                /*!< Radius.\n
                 * Group code = 40. */
        double extr_x0;
                /*!< X-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 210. */
        double extr_y0;
                /*!< Y-value of the extrusion vector.\n
                 * Defaults to 0.0 if omitted in the DXF file.\n
                 * Group code = 220. */
        double extr_z0;
                /*!< Z-value of the extrusion vector.\n
                 * Defaults to 1.0 if omitted in the DXF file.\n
                 * Group code = 230. */
        struct DxfCircle *next;
                /*!< Pointer to the next DxfCircle.\n
                 * \c NULL in the last DxfCircle. */
} DxfCircle;


DxfCircle *dxf_circle_new ();
DxfCircle *dxf_circle_init
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_read
(
        DxfFile *fp,
        DxfCircle *circle
);
int dxf_circle_write
(
        DxfFile *fp,
        DxfCircle *circle
);
int dxf_circle_free
(
        DxfCircle *circle
);
void
dxf_circle_free_chain
(
        DxfCircle *circles
);
int
dxf_circle_get_id_code
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_id_code
(
        DxfCircle *circle,
        int id_code
);
char *
dxf_circle_get_linetype
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_linetype
(
        DxfCircle *circle,
        char *linetype
);
char *
dxf_circle_get_layer
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_layer
(
        DxfCircle *circle,
        char *layer
);
double
dxf_circle_get_elevation
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_elevation
(
        DxfCircle *circle,
        double elevation
);
double
dxf_circle_get_thickness
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_thickness
(
        DxfCircle *circle,
        double thickness
);
double
dxf_circle_get_linetype_scale
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_linetype_scale
(
        DxfCircle *circle,
        double linetype_scale
);
int16_t
dxf_circle_get_visibility
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_visibility
(
        DxfCircle *circle,
        int16_t visibility
);
int
dxf_circle_get_color
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_color
(
        DxfCircle *circle,
        int color
);
int
dxf_circle_get_paperspace
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_paperspace
(
        DxfCircle *circle,
        int paperspace
);
int
dxf_circle_get_graphics_data_size
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_graphics_data_size
(
        DxfCircle *circle,
        int graphics_data_size
);
int16_t
dxf_circle_get_shadow_mode
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_shadow_mode
(
        DxfCircle *circle,
        int16_t shadow_mode
);
DxfBinaryGraphicsData *
dxf_circle_get_binary_graphics_data
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_binary_graphics_data
(
        DxfCircle *circle,
        DxfBinaryGraphicsData *data
);
char *
dxf_circle_get_dictionary_owner_soft
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_dictionary_owner_soft
(
        DxfCircle *circle,
        char *dictionary_owner_soft
);
char *
dxf_circle_get_material
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_material
(
        DxfCircle *circle,
        char *material
);
char *
dxf_circle_get_dictionary_owner_hard
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_dictionary_owner_hard
(
        DxfCircle *circle,
        char *dictionary_owner_hard
);
int16_t
dxf_circle_get_lineweight
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_lineweight
(
        DxfCircle *circle,
        int16_t lineweight
);
char *
dxf_circle_get_plot_style_name
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_plot_style_name
(
        DxfCircle *circle,
        char *plot_style_name
);
long
dxf_circle_get_color_value
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_color_value
(
        DxfCircle *circle,
        long color_value
);
char *
dxf_circle_get_color_name
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_color_name
(
        DxfCircle *circle,
        char *color_name
);
long
dxf_circle_get_transparency
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_transparency
(
        DxfCircle *circle,
        long transparency
);
DxfPoint *
dxf_circle_get_p0
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_p0
(
        DxfCircle *circle,
        DxfPoint *point
);
double
dxf_circle_get_x0
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_x0
(
        DxfCircle *circle,
        double x0
);
double
dxf_circle_get_y0
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_y0
(
        DxfCircle *circle,
        double y0
);
double
dxf_circle_get_z0
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_z0
(
        DxfCircle *circle,
        double z0
);
double
dxf_circle_get_radius
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_radius
(
        DxfCircle *circle,
        double radius
);
DxfPoint *
dxf_circle_get_extrusion_vector_as_point
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_extrusion_vector
(
        DxfCircle *circle,
        double extr_x0,
        double extr_y0,
        double extr_z0
);
DxfCircle *
dxf_circle_set_extr_x0
(
        DxfCircle *circle,
        double extr_x0
);
DxfCircle *
dxf_circle_set_extr_y0
(
        DxfCircle *circle,
        double extr_y0
);
DxfCircle *
dxf_circle_set_extr_z0
(
        DxfCircle *circle,
        double extr_z0
);
DxfCircle *
dxf_circle_get_next
(
        DxfCircle *circle
);
DxfCircle *
dxf_circle_set_next
(
        DxfCircle *circle,
        DxfCircle *next
);


#endif /* LIBDXF_SRC_CIRCLE_H */


/* EOF */
