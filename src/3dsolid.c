/*!
 * \file 3dsolid.c
 *
 * \author Copyright (C) 2012, 2013, 2014, 2015, 2016 by Bert Timmerman
 * <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF 3D solid entity (\c 3DSOLID).
 *
 * \version The \c 3DSOLID entity was introduced in DXF R13.
 *
 * \warning dxf_3dsolid_new(), dxf_3dsolid_init(), dxf_3dsolid_read()
 * and dxf_3dsolid_free() are backward compatible with versions
 * R10 .. R12 to allow for reading DXF data generated with other CAD
 * software. \n
 * When writing DXF data to file with versions before DXF R13 a warning
 * message is given.
 *
 * \version According to DXF R10 (backward compatibility).
 * \version According to DXF R11 (backward compatibility).
 * \version According to DXF R12 (backward compatibility).
 * \version According to DXF R13.
 * \version According to DXF R14.
 *
 * <hr>
 * <h1><b>Copyright Notices.</b></h1>\n
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.\n
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.\n
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to:\n
 * the Free Software Foundation, Inc.,\n
 * 51 Franklin Street,\n
 * Fifth Floor,\n
 * Boston,\n
 * MA 02110-1301 USA.\n
 *
 * Drawing eXchange Format (DXF) is a defacto industry standard for the
 * exchange of drawing files between various Computer Aided Drafting
 * programs.\n
 * DXF is an industry standard designed by Autodesk(TM).\n
 * For more details see http://www.autodesk.com.
 * <hr>
 */


#include "3dsolid.h"


/*!
 * \brief Allocate memory for a DXF \c 3DSOLID.
 *
 * Fill the memory contents with zeros.
 */
Dxf3dsolid *
dxf_3dsolid_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        Dxf3dsolid *solid = NULL;
        size_t size;

        size = sizeof (Dxf3dsolid);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((solid = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        else
        {
                memset (solid, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Allocate memory and initialize data fields in a \c 3DSOLID
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
Dxf3dsolid *
dxf_3dsolid_init
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                solid = dxf_3dsolid_new ();
        }
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_3dsolid_set_id_code (solid, 0);
        dxf_3dsolid_set_linetype (solid, strdup (DXF_DEFAULT_LINETYPE));
        dxf_3dsolid_set_layer (solid, strdup (DXF_DEFAULT_LAYER));
        dxf_3dsolid_set_elevation (solid, 0.0);
        dxf_3dsolid_set_thickness (solid, 0.0);
        dxf_3dsolid_set_linetype_scale (solid, DXF_DEFAULT_LINETYPE_SCALE);
        dxf_3dsolid_set_visibility (solid, DXF_DEFAULT_VISIBILITY);
        dxf_3dsolid_set_color (solid, DXF_COLOR_BYLAYER);
        dxf_3dsolid_set_paperspace (solid, DXF_MODELSPACE);
        dxf_3dsolid_set_graphics_data_size (solid, 0);
        dxf_3dsolid_set_shadow_mode (solid, 0);
        dxf_3dsolid_set_binary_graphics_data (solid, (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ());
        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) dxf_3dsolid_get_binary_graphics_data (solid));
        dxf_3dsolid_set_dictionary_owner_soft (solid, strdup (""));
        dxf_3dsolid_set_material (solid, strdup (""));
        dxf_3dsolid_set_dictionary_owner_hard (solid, strdup (""));
        dxf_3dsolid_set_lineweight (solid, 0);
        dxf_3dsolid_set_plot_style_name (solid, strdup (""));
        dxf_3dsolid_set_color_value (solid, 0);
        dxf_3dsolid_set_color_name (solid, strdup (""));
        dxf_3dsolid_set_transparency (solid, 0);
        dxf_3dsolid_set_proprietary_data (solid, (DxfProprietaryData *) dxf_proprietary_data_init (solid->proprietary_data));
        dxf_3dsolid_set_additional_proprietary_data (solid, (DxfProprietaryData *) dxf_proprietary_data_init (solid->additional_proprietary_data));
        dxf_3dsolid_set_modeler_format_version_number (solid, 1);
        dxf_3dsolid_set_history (solid, strdup (""));
        dxf_3dsolid_set_next (solid, NULL);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Read data from a DXF file into a DXF \c 3DSOLID entity.
 *
 * The last line read from file contained the string "3DSOLID". \n
 * Now follows some data for the \c 3DSOLID, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c solid. \n
 *
 * \return \c a pointer to \c solid.
 */
Dxf3dsolid *
dxf_3dsolid_read
(
        DxfFile *fp,
                /*!< a DXF file pointer to an input file (or device). */
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (temp_string);
                return (NULL);
        }
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                solid = dxf_3dsolid_new ();
                solid = dxf_3dsolid_init (solid);
        }
        i = 1;
        solid->proprietary_data->order = 0;
        solid->additional_proprietary_data->order = 0;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        /* Clean up. */
                        free (temp_string);
                        fclose (fp->fp);
                        return (NULL);
                }
                else if (strcmp (temp_string, "  1") == 0)
                {
                        /* Now follows a string containing proprietary
                         * data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->proprietary_data->line);
                        solid->proprietary_data->order = i;
                        i++;
                        dxf_proprietary_data_init ((DxfProprietaryData *) solid->proprietary_data->next);
                        solid->proprietary_data = (DxfProprietaryData *) solid->proprietary_data->next;
                }
                else if (strcmp (temp_string, "  3") == 0)
                {
                        /* Now follows a string containing additional
                         * proprietary data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->additional_proprietary_data->line);
                        solid->additional_proprietary_data->order = i;
                        i++;
                        dxf_proprietary_data_init ((DxfProprietaryData *) solid->additional_proprietary_data->next);
                        solid->additional_proprietary_data = (DxfProprietaryData *) solid->additional_proprietary_data->next;
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &solid->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->layer);
                }
                else if (strcmp (temp_string, "38") == 0)
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->thickness);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &solid->linetype_scale);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &solid->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &solid->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &solid->paperspace);
                }
                else if (strcmp (temp_string, "70") == 0)
                {
                        /* Now follows a string containing the modeler
                         * format version number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &solid->modeler_format_version_number);
                }
                else if (strcmp (temp_string, "92") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &solid->graphics_data_size);
                }
                else if (strcmp (temp_string, "100") == 0)
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "AcDbModelerGeometry") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "100") == 0)
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if (strcmp (temp_string, "AcDb3dSolid") != 0)
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "160") == 0)
                {
                        /* Now follows a string containing the
                         * graphics data size value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &solid->graphics_data_size);
                }
                else if (strcmp (temp_string, "284") == 0)
                {
                        /* Now follows a string containing the shadow
                         * mode value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &solid->shadow_mode);
                }
                else if (strcmp (temp_string, "310") == 0)
                {
                        /* Now follows a string containing binary
                         * graphics data. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->binary_graphics_data->data_line);
                        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) solid->binary_graphics_data->next);
                        solid->binary_graphics_data = (DxfBinaryGraphicsData *) solid->binary_graphics_data->next;
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "347") == 0)
                {
                        /* Now follows a string containing a
                         * hard-pointer ID/handle to material object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->material);
                }
                else if (strcmp (temp_string, "350") == 0)
                {
                        /* Now follows a string containing a handle to a
                         * history object. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->history);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "370") == 0)
                {
                        /* Now follows a string containing the lineweight
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &solid->lineweight);
                }
                else if (strcmp (temp_string, "390") == 0)
                {
                        /* Now follows a string containing a plot style
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->plot_style_name);
                }
                else if (strcmp (temp_string, "420") == 0)
                {
                        /* Now follows a string containing a color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &solid->color_value);
                }
                else if (strcmp (temp_string, "430") == 0)
                {
                        /* Now follows a string containing a color
                         * name value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", solid->color_name);
                }
                else if (strcmp (temp_string, "440") == 0)
                {
                        /* Now follows a string containing a transparency
                         * value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%ld\n", &solid->transparency);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, (_("DXF comment: %s\n")), temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (solid->linetype, "") == 0)
        {
                solid->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (solid->layer, "") == 0)
        {
                solid->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Write DXF output to a file for a DXF \c 3DSOLID entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_3dsolid_write
(
        DxfFile *fp,
                /*!< a DXF file pointer to an output file (or device). */
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("3DSOLID");
        DxfProprietaryData *iter = NULL;
        DxfProprietaryData *additional_iter = NULL;
        int i;

        /* Do some basic checks. */
        if (fp == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL file pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (fp->acad_version_number < AutoCAD_13)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this %s entity with id-code: %x.\n")),
                  __FUNCTION__, dxf_entity_name, dxf_3dsolid_get_id_code (solid));
        }
        if (strcmp (dxf_3dsolid_get_linetype (solid), "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_3dsolid_get_id_code (solid));
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_3dsolid_set_linetype (solid, strdup (DXF_DEFAULT_LINETYPE));
        }
        if (strcmp (dxf_3dsolid_get_layer (solid), "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_3dsolid_get_id_code (solid));
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_3dsolid_set_layer (solid, (strdup (DXF_DEFAULT_LAYER)));
        }
        /* Start writing output. */
        i = 1;
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_3dsolid_get_id_code (solid) != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_3dsolid_get_id_code (solid));
        }
        /*!
         * \todo for version R14.\n
         * Implementing the start of application-defined group
         * "{application_name", with Group code 102.\n
         * For example: "{ACAD_REACTORS" indicates the start of the
         * AutoCAD persistent reactors group.\n\n
         * application-defined codes: Group codes and values within the
         * 102 groups are application defined (optional).\n\n
         * End of group, "}" (optional), with Group code 102.
         */
        if ((strcmp (dxf_3dsolid_get_dictionary_owner_soft (solid), "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_3dsolid_get_dictionary_owner_soft (solid));
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_3dsolid_get_dictionary_owner_hard (solid), "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_3dsolid_get_dictionary_owner_hard (solid));
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_3dsolid_get_paperspace (solid) == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_3dsolid_get_layer (solid));
        if (strcmp (dxf_3dsolid_get_linetype (solid), DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_3dsolid_get_linetype (solid));
        }
        if ((fp->acad_version_number >= AutoCAD_2008)
          && (strcmp (dxf_3dsolid_get_material (solid), "") != 0))
        {
                fprintf (fp->fp, "347\n%s\n", dxf_3dsolid_get_material (solid));
        }
        if (dxf_3dsolid_get_color (solid) != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_3dsolid_get_color (solid));
        }
        if (fp->acad_version_number >= AutoCAD_2002)
        {
                fprintf (fp->fp, "370\n%d\n", dxf_3dsolid_get_lineweight (solid));
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (dxf_3dsolid_get_elevation (solid) != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", dxf_3dsolid_get_elevation (solid));
        }
        if (dxf_3dsolid_get_thickness (solid) != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_3dsolid_get_thickness (solid));
        }
        if (dxf_3dsolid_get_linetype_scale (solid) != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_3dsolid_get_linetype_scale (solid));
        }
        if (dxf_3dsolid_get_visibility (solid) != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_3dsolid_get_visibility (solid));
        }
        if (fp->acad_version_number >= AutoCAD_2000)
        {
#ifdef BUILD_64
                fprintf (fp->fp, "160\n%d\n", dxf_3dsolid_get_graphics_data_size (solid));
#else
                fprintf (fp->fp, " 92\n%d\n", dxf_3dsolid_get_graphics_data_size (solid));
#endif
                DxfBinaryGraphicsData *bgd_iter = (DxfBinaryGraphicsData *) dxf_3dsolid_get_binary_graphics_data (solid);
                while (dxf_binary_graphics_data_get_data_line (bgd_iter) != NULL)
                {
                        fprintf (fp->fp, "310\n%s\n", dxf_binary_graphics_data_get_data_line (bgd_iter));
                        bgd_iter = (DxfBinaryGraphicsData *) dxf_binary_graphics_data_get_next (bgd_iter);
                }
        }
        if (fp->acad_version_number >= AutoCAD_2004)
        {
                fprintf (fp->fp, "420\n%ld\n", dxf_3dsolid_get_color_value (solid));
                fprintf (fp->fp, "430\n%s\n", dxf_3dsolid_get_color_name (solid));
                fprintf (fp->fp, "440\n%ld\n", dxf_3dsolid_get_transparency (solid));
        }
        if (fp->acad_version_number >= AutoCAD_2009)
        {
                fprintf (fp->fp, "390\n%s\n", dxf_3dsolid_get_plot_style_name (solid));
                fprintf (fp->fp, "284\n%d\n", dxf_3dsolid_get_shadow_mode (solid));
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbModelerGeometry\n");
        }
        if (fp->acad_version_number >= AutoCAD_2008)
        {
                fprintf (fp->fp, "100\nAcDb3dSolid\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, " 70\n%d\n", dxf_3dsolid_get_modeler_format_version_number (solid));
        }
        iter = (DxfProprietaryData *) dxf_3dsolid_get_proprietary_data (solid);
        additional_iter = (DxfProprietaryData *) dxf_3dsolid_get_additional_proprietary_data (solid);
        while ((iter != NULL) || (additional_iter != NULL))
        {
                if (iter->order == i)
                {
                        fprintf (fp->fp, "  1\n%s\n", dxf_proprietary_data_get_line (iter));
                        iter = (DxfProprietaryData *) dxf_proprietary_data_get_next (iter);
                        i++;
                }
                if (additional_iter->order == i)
                {
                        fprintf (fp->fp, "  3\n%s\n", dxf_proprietary_data_get_line (additional_iter));
                        additional_iter = (DxfProprietaryData *) dxf_proprietary_data_get_next (additional_iter);
                        i++;
                }
        }
        if (fp->acad_version_number >= AutoCAD_2008)
        {
                fprintf (fp->fp, "350\n%s\n", dxf_3dsolid_get_history (solid));
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c 3DSOLID and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_3dsolid_free
(
        Dxf3dsolid *solid
                /*!< a pointer to the memory occupied by the DXF
                 * \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_3dsolid_get_linetype (solid));
        free (dxf_3dsolid_get_layer (solid));
        dxf_binary_graphics_data_free_chain (dxf_3dsolid_get_binary_graphics_data (solid));
        free (dxf_3dsolid_get_dictionary_owner_soft (solid));
        free (dxf_3dsolid_get_material (solid));
        free (dxf_3dsolid_get_dictionary_owner_hard (solid));
        free (dxf_3dsolid_get_plot_style_name (solid));
        free (dxf_3dsolid_get_color_name (solid));
        dxf_proprietary_data_free_chain (dxf_3dsolid_get_proprietary_data (solid));
        dxf_proprietary_data_free_chain (dxf_3dsolid_get_additional_proprietary_data (solid));
        free (dxf_3dsolid_get_history (solid));
        free (solid);
        solid = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c 3DSOLID
 * entities and all their data fields.
 */
void
dxf_3dsolid_free_chain
(
        Dxf3dsolid *solids
                /*!< a pointer to the chain of DXF \c 3DSOLID entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (solids == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (solids != NULL)
        {
                struct Dxf3dsolid *iter = solids->next;
                dxf_3dsolid_free (solids);
                solids = (Dxf3dsolid *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c 3DSOLID entity.
 *
 * \return ID code.
 */
int
dxf_3dsolid_get_id_code
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c 3DSOLID entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_id_code
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        int id_code
                /*!< Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the linetype from a DXF \c 3DSOLID entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_3dsolid_get_linetype
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c 3DSOLID entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_linetype
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the layer from a DXF \c 3DSOLID entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_3dsolid_get_layer
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->layer));
}


/*!
 * \brief Set the layer for a DXF \c 3DSOLID entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_layer
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (layer == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the elevation from a DXF \c 3DSOLID entity.
 *
 * \return elevation.
 */
double
dxf_3dsolid_get_elevation
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->elevation);
}


/*!
 * \brief Set the elevation for a DXF \c 3DSOLID entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_elevation
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the thickness from a DXF \c 3DSOLID entity.
 *
 * \return thickness.
 */
double
dxf_3dsolid_get_thickness
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->thickness);
}


/*!
 * \brief Set the thickness for a DXF \c 3DSOLID entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_thickness
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the linetype scale from a DXF \c 3DSOLID entity.
 *
 * \return linetype scale.
 */
double
dxf_3dsolid_get_linetype_scale
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->linetype_scale);
}


/*!
 * \brief Set the linetype scale for a DXF \c 3DSOLID entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_linetype_scale
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the visibility from a DXF \c 3DSOLID entity.
 *
 * \return visibility.
 */
int16_t
dxf_3dsolid_get_visibility
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->visibility);
}


/*!
 * \brief Set the visibility for a DXF \c 3DSOLID entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_visibility
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the color from a DXF \c 3DSOLID entity.
 *
 * \return color.
 */
int
dxf_3dsolid_get_color
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->color);
}


/*!
 * \brief Set the color for a DXF \c 3DSOLID entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_color
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negativevalue was passed.\n")),
                  __FUNCTION__);
        }
        solid->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c 3DSOLID entity.
 *
 * \return paperspace flag value.
 */
int
dxf_3dsolid_get_paperspace
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (solid->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->paperspace);
}


/*!
 * \brief Set the paperspace flag for a DXF \c 3DSOLID entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_paperspace
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        int paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (paperspace > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c 3DSOLID entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_3dsolid_get_graphics_data_size
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (solid->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c 3DSOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dsolid *
dxf_3dsolid_set_graphics_data_size
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a zero value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c 3DSOLID entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_3dsolid_get_shadow_mode
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c 3DSOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dsolid *
dxf_3dsolid_set_shadow_mode
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the pointer to the binary graphics data from a DXF 
 * \c 3DSOLID entity.
 *
 * \return pointer to the binary graphics data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_3dsolid_get_binary_graphics_data
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) solid->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the binary_graphics_data for a DXF
 * \c 3DSOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dsolid *
dxf_3dsolid_set_binary_graphics_data
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c 3DSOLID entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_3dsolid_get_dictionary_owner_soft
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c 3DSOLID entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_dictionary_owner_soft
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_soft == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c 3DSOLID
 * entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_3dsolid_get_material
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c 3DSOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dsolid *
dxf_3dsolid_set_material
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (material == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c 3DSOLID entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_3dsolid_get_dictionary_owner_hard
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the \c dictionary_owner_hard for a DXF
 * \c 3DSOLID entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_dictionary_owner_hard
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the \c
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (dictionary_owner_hard == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c lineweight from a DXF \c 3DSOLID entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_3dsolid_get_lineweight
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c 3DSOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dsolid *
dxf_3dsolid_set_lineweight
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c 3DSOLID entity.
 *
 * \return \c plot_style_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_3dsolid_get_plot_style_name
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c 3DSOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dsolid *
dxf_3dsolid_set_plot_style_name
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (plot_style_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c color_value from a DXF \c 3DSOLID entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_3dsolid_get_color_value
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c 3DSOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dsolid *
dxf_3dsolid_set_color_value
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c color_name from a DXF \c 3DSOLID entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_3dsolid_get_color_name
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c 3DSOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dsolid *
dxf_3dsolid_set_color_name
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color_name == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the \c transparency from a DXF \c 3DSOLID entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_3dsolid_get_transparency
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c 3DSOLID entity.
 *
 * \return a pointer to \c solid when successful, or \c NULL when an
 * error occurred.
 */
Dxf3dsolid *
dxf_3dsolid_set_transparency
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the pointer to the \c proprietary_data from a DXF 
 * \c 3DSOLID entity.
 *
 * \return pointer to the \c proprietary_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfProprietaryData *
dxf_3dsolid_get_proprietary_data
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->proprietary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfProprietaryData *) solid->proprietary_data);
}


/*!
 * \brief Set the \c proprietary_data for a DXF \c 3DSOLID entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_proprietary_data
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        DxfProprietaryData *proprietary_data
                /*!< the \c proprietary_data to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (proprietary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->proprietary_data = proprietary_data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the pointer to the \c additional_proprietary_data from a
 * DXF \c 3DSOLID entity.
 *
 * \return pointer to the \c additional_proprietary_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfProprietaryData *
dxf_3dsolid_get_additional_proprietary_data
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->additional_proprietary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfProprietaryData *) solid->additional_proprietary_data);
}


/*!
 * \brief Set the \c additional_proprietary_data for a DXF \c 3DSOLID
 * entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_additional_proprietary_data
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        DxfProprietaryData *additional_proprietary_data
                /*!< the \c additional_proprietary_data to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (additional_proprietary_data == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->additional_proprietary_data = additional_proprietary_data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the modeler format version number from a DXF \c 3DSOLID
 * entity.
 *
 * \return the modeler format version number.
 */
int
dxf_3dsolid_get_modeler_format_version_number
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (solid->modeler_format_version_number < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (solid->modeler_format_version_number > DXF_MODELER_FORMAT_CURRENT_VERSION)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid->modeler_format_version_number);
}


/*!
 * \brief Set the modeler format version number for a DXF \c 3DSOLID
 * entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_modeler_format_version_number
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        int modeler_format_version_number
                /*!< the modeler format version number to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (modeler_format_version_number < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (modeler_format_version_number > DXF_MODELER_FORMAT_CURRENT_VERSION)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->modeler_format_version_number = modeler_format_version_number;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the pointer to the history from a DXF \c 3DSOLID entity.
 *
 * \return soft pointer to the history.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_3dsolid_get_history
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->history ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (solid->history));
}


/*!
 * \brief Set the pointer to the history for a DXF \c 3DSOLID entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_history
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3DSOLID entity. */
        char *history
                /*!< a string containing the pointer to the history for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (history == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->history = strdup (history);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the pointer to the next \c 3DSOLID entity from a DXF 
 * \c 3DSOLID entity.
 *
 * \return pointer to the next \c 3DSOLID entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
Dxf3dsolid *
dxf_3dsolid_get_next
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((Dxf3dsolid *) solid->next);
}


/*!
 * \brief Set the pointer to the next \c 3DSOLID for a DXF \c 3DSOLID
 * entity.
 */
Dxf3dsolid *
dxf_3dsolid_set_next
(
        Dxf3dsolid *solid,
                /*!< a pointer to a DXF \c 3SOLID entity. */
        Dxf3dsolid *next
                /*!< a pointer to the next \c 3DSOLID for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        solid->next = (struct Dxf3dsolid *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (solid);
}


/*!
 * \brief Get the pointer to the last \c 3DSOLID entity from a linked
 * list of DXF \c 3DSOLID entity.
 *
 * \return pointer to the last \c 3DSOLID entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
Dxf3dsolid *
dxf_3dsolid_get_last
(
        Dxf3dsolid *solid
                /*!< a pointer to a DXF \c 3DSOLID entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (solid == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (solid->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((Dxf3dsolid *) solid);
        }
        Dxf3dsolid *iter = (Dxf3dsolid *) solid->next;
        while (iter->next != NULL)
        {
                iter = (Dxf3dsolid *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((Dxf3dsolid *) iter);
}


/* EOF */
