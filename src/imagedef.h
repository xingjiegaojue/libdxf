/*!
 * \file imagedef.h
 *
 * \author Copyright (C) 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Header file for a DXF imagedef object (\c IMAGEDEF).
 *
 * \version The \c IMAGEDEF object was introduced in DXF R14.
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


#ifndef LIBDXF_SRC_IMAGEDEF_H
#define LIBDXF_SRC_IMAGEDEF_H


#include "global.h"


/*!
 * \brief DXF definition of an AutoCAD imagedef object (\c IMAGEDEF).
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13 (backward compatibility).
 * \version According to DXF R14.
 */
typedef struct
dxf_imagedef
{
        /* Members common for all DXF group objects. */
        int id_code;
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file.\n
                 * Group code = 5. */
        char *dictionary_owner_soft;
                /*!< Soft-pointer ID/handle to owner dictionary (optional).\n
                 * Group code = 330. */
        char *dictionary_owner_hard;
                /*!< Hard owner ID/handle to owner dictionary (optional).\n
                 * Group code = 360. */
        /* Specific members for a DXF imagedef. */
        char *file_name;
                /*!< File name of image.\n
                 * Group code = 1. */
        double x0;
                /*!< Image size in pixels. DXF: U value; APP: 2D point
                 * (U and V values).\n
                 * Group code = 10. */
        double y0;
                /*!< DXF: V value of image size in pixels.\n
                 * Group code = 20. */
        double x1;
                /*!< Default size of one pixel in AutoCAD units.\n
                 * DXF: U value; APP: 2D point (U and V values).\n
                 * Group code = 11. */
        double y1;
                /*!< DXF: V value of pixel size.\n
                 * Group code = 12. */
        int32_t class_version;
                /*!< Class version.\n
                 * 0 = R14 version.\n
                 * Group code = 90. */

        int image_is_loaded_flag;
                /*!< Image-is-loaded flag.\n
                 * <ol>
                 * <li value = "0"> Unloaded.</li>
                 * <li value = "1"> Loaded.</li>
                 * </ol>
                 * Group code = 280.
                 */
        int resolution_units;
                /*!< Resolution units.\n
                 * <ol>
                 * <li value = "0"> No units.</li>
                 * <li value = "2"> Centimeters.</li>
                 * <li value = "5"> Inch.</li>
                 * </ol>
                 * Group code = 281. */
        char *acad_image_dict_soft;
                /*!< Soft-pointer ID/handle to the ACAD_IMAGE_DICT
                 * dictionary.\n
                 * Group code = 330. */
        char *imagedef_reactor_soft[DXF_MAX_PARAM];
                /*!< Soft-pointer ID/handle to IMAGEDEF_REACTOR object
                 * (multiple entries; one for each instance).\n
                 * Group code = 330. */
        struct DxfImagedef *next;
                /*!< Pointer to the next DxfImagedef.\n
                 * \c NULL in the last DxfImagedef. */
} DxfImagedef;


DxfImagedef *
dxf_imagedef_new ();
int
dxf_imagedef_free
(
        DxfImagedef *imagedef
);


#endif /* LIBDXF_SRC_IMAGEDEF_H */


/* EOF */
