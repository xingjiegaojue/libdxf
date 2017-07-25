/*!
 * \file arc.c
 *
 * \author Copyright (C) 2008, 2010, 2012, 2013, 2014, 2015, 2016, 2017
 * by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Functions for a DXF arc entity (\c ARC).
 *
 * \version According to DXF R10.
 * \version According to DXF R11.
 * \version According to DXF R12.
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


#include "arc.h"


/*!
 * \brief Allocate memory for a DXF \c ARC entity.
 *
 * Fill the memory contents with zeros.
 *
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfArc *
dxf_arc_new ()
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfArc *arc = NULL;
        size_t size;

        size = sizeof (DxfArc);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((arc = malloc (size)) == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                arc = NULL;
        }
        else
        {
                memset (arc, 0, size);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c ARC
 * entity.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfArc *
dxf_arc_init
(
        DxfArc *arc
                /*!< a pointer to the DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                arc = dxf_arc_new ();
        }
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        dxf_arc_set_id_code (arc, 0);
        dxf_arc_set_linetype (arc, strdup (DXF_DEFAULT_LINETYPE));
        dxf_arc_set_layer (arc, strdup (DXF_DEFAULT_LAYER));
        dxf_arc_set_elevation (arc, 0.0);
        dxf_arc_set_thickness (arc, 0.0);
        dxf_arc_set_linetype_scale (arc, DXF_DEFAULT_LINETYPE_SCALE);
        dxf_arc_set_visibility (arc, DXF_DEFAULT_VISIBILITY);
        dxf_arc_set_color (arc, DXF_COLOR_BYLAYER);
        dxf_arc_set_paperspace (arc, DXF_MODELSPACE);
        dxf_arc_set_graphics_data_size (arc, 0);
        dxf_arc_set_shadow_mode (arc, 0);
        dxf_arc_set_binary_graphics_data (arc, (DxfBinaryGraphicsData *) dxf_binary_graphics_data_new ());
        dxf_binary_graphics_data_init ((DxfBinaryGraphicsData *) dxf_arc_get_binary_graphics_data (arc));
        dxf_arc_set_dictionary_owner_soft (arc, strdup (""));
        dxf_arc_set_material (arc, strdup (""));
        dxf_arc_set_dictionary_owner_hard (arc, strdup (""));
        dxf_arc_set_lineweight (arc, 0);
        dxf_arc_set_plot_style_name (arc, strdup (""));
        dxf_arc_set_color_value (arc, 0);
        dxf_arc_set_color_name (arc, strdup (""));
        dxf_arc_set_transparency (arc, 0);
        dxf_arc_set_p0 (arc, dxf_point_new ());
        dxf_point_init ((DxfPoint *) dxf_arc_get_p0 (arc));
        dxf_arc_set_x0 (arc, 0.0);
        dxf_arc_set_y0 (arc, 0.0);
        dxf_arc_set_z0 (arc, 0.0);
        dxf_arc_set_radius (arc, 0.0);
        dxf_arc_set_start_angle (arc, 0.0);
        dxf_arc_set_end_angle (arc, 0.0);
        dxf_arc_set_extr_x0 (arc, 0.0);
        dxf_arc_set_extr_y0 (arc, 0.0);
        dxf_arc_set_extr_z0 (arc, 1.0);
        dxf_arc_set_next (arc, NULL);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Read data from a DXF file into a DXF \c ARC entity.
 *
 * The last line read from file contained the string "ARC". \n
 * Now follows some data for the \c ARC, to be terminated with a "  0"
 * string announcing the following entity, or the end of the \c ENTITY
 * section marker \c ENDSEC. \n
 * While parsing the DXF file store data in \c arc. \n
 *
 * \return a pointer to \c arc.
 */
DxfArc *
dxf_arc_read
(
        DxfFile *fp,
                /*!< DXF file pointer to an input file (or device). */
        DxfArc *arc
                /*!< a pointer to the DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;

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
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                arc = dxf_arc_new ();
                arc = dxf_arc_init (arc);
        }
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        fclose (fp->fp);
                        /* Clean up. */
                        free (temp_string);
                        return (NULL);
                }
                if (strcmp (temp_string, "5") == 0)
                {
                        /* Now follows a string containing a sequential
                         * id number. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%x\n", &arc->id_code);
                }
                else if (strcmp (temp_string, "6") == 0)
                {
                        /* Now follows a string containing a linetype
                         * name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", arc->linetype);
                }
                else if (strcmp (temp_string, "8") == 0)
                {
                        /* Now follows a string containing a layer name. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", arc->layer);
                }
                else if (strcmp (temp_string, "10") == 0)
                {
                        /* Now follows a string containing the
                         * X-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->p0->x0);
                }
                else if (strcmp (temp_string, "20") == 0)
                {
                        /* Now follows a string containing the
                         * Y-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->p0->y0);
                }
                else if (strcmp (temp_string, "30") == 0)
                {
                        /* Now follows a string containing the
                         * Z-coordinate of the center point. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->p0->z0);
                }
                else if ((fp->acad_version_number <= AutoCAD_11)
                        && (strcmp (temp_string, "38") == 0))
                {
                        /* Now follows a string containing the
                         * elevation. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->elevation);
                }
                else if (strcmp (temp_string, "39") == 0)
                {
                        /* Now follows a string containing the
                         * thickness. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->thickness);
                }
                else if (strcmp (temp_string, "40") == 0)
                {
                        /* Now follows a string containing the
                         * radius. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->radius);
                }
                else if (strcmp (temp_string, "48") == 0)
                {
                        /* Now follows a string containing the linetype
                         * scale. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->linetype_scale);
                }
                else if (strcmp (temp_string, "50") == 0)
                {
                        /* Now follows a string containing the
                         * start angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->start_angle);
                }
                else if (strcmp (temp_string, "51") == 0)
                {
                        /* Now follows a string containing the
                         * end angle. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->end_angle);
                }
                else if (strcmp (temp_string, "60") == 0)
                {
                        /* Now follows a string containing the
                         * visibility value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%hd\n", &arc->visibility);
                }
                else if (strcmp (temp_string, "62") == 0)
                {
                        /* Now follows a string containing the
                         * color value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &arc->color);
                }
                else if (strcmp (temp_string, "67") == 0)
                {
                        /* Now follows a string containing the
                         * paperspace value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &arc->paperspace);
                }
                else if ((fp->acad_version_number >= AutoCAD_13)
                        && (strcmp (temp_string, "100") == 0))
                {
                        /* Now follows a string containing the
                         * subclass marker value. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        if ((strcmp (temp_string, "AcDbEntity") != 0)
                        && ((strcmp (temp_string, "AcDbCircle") != 0)))
                        {
                                fprintf (stderr,
                                  (_("Warning in %s () found a bad subclass marker in: %s in line: %d.\n")),
                                  __FUNCTION__, fp->filename, fp->line_number);
                        }
                }
                else if (strcmp (temp_string, "210") == 0)
                {
                        /* Now follows a string containing the
                         * X-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->extr_x0);
                }
                else if (strcmp (temp_string, "220") == 0)
                {
                        /* Now follows a string containing the
                         * Y-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->extr_y0);
                }
                else if (strcmp (temp_string, "230") == 0)
                {
                        /* Now follows a string containing the
                         * Z-value of the extrusion vector. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%lf\n", &arc->extr_z0);
                }
                else if (strcmp (temp_string, "330") == 0)
                {
                        /* Now follows a string containing Soft-pointer
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", arc->dictionary_owner_soft);
                }
                else if (strcmp (temp_string, "360") == 0)
                {
                        /* Now follows a string containing Hard owner
                         * ID/handle to owner dictionary. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", arc->dictionary_owner_hard);
                }
                else if (strcmp (temp_string, "999") == 0)
                {
                        /* Now follows a string containing a comment. */
                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }
        /* Handle omitted members and/or illegal values. */
        if (strcmp (arc->linetype, "") == 0)
        {
                arc->linetype = strdup (DXF_DEFAULT_LINETYPE);
        }
        if (strcmp (arc->layer, "") == 0)
        {
                arc->layer = strdup (DXF_DEFAULT_LAYER);
        }
        /* Clean up. */
        free (temp_string);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Write DXF output for a DXF \c ARC entity.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_arc_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfArc *arc
                /*!< a pointer to the DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("ARC");

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
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_arc_get_start_angle (arc) == dxf_arc_get_end_angle (arc))
        {
                fprintf (stderr,
                  (_("Error in %s () start angle and end angle are identical for the %s entity with id-code: %x.\n")),
                    __FUNCTION__, dxf_entity_name, dxf_arc_get_id_code (arc));
                fprintf (stderr,
                  (_("\tskipping %s entity.\n")), dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_arc_get_start_angle (arc)> 360.0)
        {
                fprintf (stderr, "Error in dxf_arc_write () start angle is greater than 360 degrees for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_arc_get_id_code (arc));
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_arc_get_start_angle (arc) < 0.0)
        {
                fprintf (stderr, "Error in dxf_arc_write () start angle is lesser than 0 degrees for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_arc_get_id_code (arc));
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_arc_get_end_angle (arc) > 360.0)
        {
                fprintf (stderr, "Error in dxf_arc_write () end angle is greater than 360 degrees for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_arc_get_id_code (arc));
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_arc_get_end_angle (arc) < 0.0)
        {
                fprintf (stderr, "Error in dxf_arc_write () end angle is lesser than 0 degrees for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_arc_get_id_code (arc));
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (dxf_arc_get_radius (arc) == 0.0)
        {
                fprintf (stderr, "Error in dxf_arc_write () radius value equals 0.0 for the %s entity with id-code: %x.\n",
                        dxf_entity_name, dxf_arc_get_id_code (arc));
                fprintf (stderr, "\tskipping %s entity.\n",
                        dxf_entity_name);
                /* Clean up. */
                free (dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (strcmp (dxf_arc_get_linetype (arc), "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty linetype string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_arc_get_id_code (arc));
                fprintf (stderr,
                  (_("\t%s entity is reset to default linetype")),
                  dxf_entity_name);
                dxf_arc_set_linetype (arc, strdup (DXF_DEFAULT_LINETYPE));
        }
        if (strcmp (dxf_arc_get_layer (arc), "") == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty layer string for the %s entity with id-code: %x\n")),
                  __FUNCTION__, dxf_entity_name, dxf_arc_get_id_code (arc));
                fprintf (stderr,
                  (_("\t%s entity is relocated to layer 0")),
                  dxf_entity_name);
                dxf_arc_set_layer (arc, DXF_DEFAULT_LAYER);
        }
        /* Start writing output. */
        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        if (dxf_arc_get_id_code (arc) != -1)
        {
                fprintf (fp->fp, "  5\n%x\n", dxf_arc_get_id_code (arc));
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
        if ((strcmp (dxf_arc_get_dictionary_owner_soft (arc), "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_REACTORS\n");
                fprintf (fp->fp, "330\n%s\n", dxf_arc_get_dictionary_owner_soft (arc));
                fprintf (fp->fp, "102\n}\n");
        }
        if ((strcmp (dxf_arc_get_dictionary_owner_hard (arc), "") != 0)
          && (fp->acad_version_number >= AutoCAD_14))
        {
                fprintf (fp->fp, "102\n{ACAD_XDICTIONARY\n");
                fprintf (fp->fp, "360\n%s\n", dxf_arc_get_dictionary_owner_hard (arc));
                fprintf (fp->fp, "102\n}\n");
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbEntity\n");
        }
        if (dxf_arc_get_paperspace (arc) == DXF_PAPERSPACE)
        {
                fprintf (fp->fp, " 67\n%d\n", DXF_PAPERSPACE);
        }
        fprintf (fp->fp, "  8\n%s\n", dxf_arc_get_layer (arc));
        if (strcmp (dxf_arc_get_linetype (arc), DXF_DEFAULT_LINETYPE) != 0)
        {
                fprintf (fp->fp, "  6\n%s\n", dxf_arc_get_linetype (arc));
        }
        if ((fp->acad_version_number <= AutoCAD_11)
          && DXF_FLATLAND
          && (dxf_arc_get_elevation (arc) != 0.0))
        {
                fprintf (fp->fp, " 38\n%f\n", dxf_arc_get_elevation (arc));
        }
        if (dxf_arc_get_color (arc) != DXF_COLOR_BYLAYER)
        {
                fprintf (fp->fp, " 62\n%d\n", dxf_arc_get_color (arc));
        }
        if (dxf_arc_get_linetype_scale (arc) != 1.0)
        {
                fprintf (fp->fp, " 48\n%f\n", dxf_arc_get_linetype_scale (arc));
        }
        if (dxf_arc_get_visibility (arc) != 0)
        {
                fprintf (fp->fp, " 60\n%d\n", dxf_arc_get_visibility (arc));
        }
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbCircle\n");
        }
        if (dxf_arc_get_thickness (arc) != 0.0)
        {
                fprintf (fp->fp, " 39\n%f\n", dxf_arc_get_thickness (arc));
        }
        fprintf (fp->fp, " 10\n%f\n", dxf_arc_get_x0 (arc));
        fprintf (fp->fp, " 20\n%f\n", dxf_arc_get_y0 (arc));
        fprintf (fp->fp, " 30\n%f\n", dxf_arc_get_z0 (arc));
        fprintf (fp->fp, " 40\n%f\n", dxf_arc_get_radius (arc));
        if (fp->acad_version_number >= AutoCAD_13)
        {
                fprintf (fp->fp, "100\nAcDbArc\n");
        }
        fprintf (fp->fp, " 50\n%f\n", dxf_arc_get_start_angle (arc));
        fprintf (fp->fp, " 51\n%f\n", dxf_arc_get_end_angle (arc));
        if ((fp->acad_version_number >= AutoCAD_12)
                && (dxf_arc_get_extr_x0 (arc) != 0.0)
                && (dxf_arc_get_extr_y0 (arc) != 0.0)
                && (dxf_arc_get_extr_z0 (arc) != 1.0))
        {
                fprintf (fp->fp, "210\n%f\n", dxf_arc_get_extr_x0 (arc));
                fprintf (fp->fp, "220\n%f\n", dxf_arc_get_extr_y0 (arc));
                fprintf (fp->fp, "230\n%f\n", dxf_arc_get_extr_z0 (arc));
        }
        /* Clean up. */
        free (dxf_entity_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a DXF \c ARC entity and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_arc_free
(
        DxfArc *arc
                /*!< a pointer to the memory occupied by the DXF \c ARC
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (arc->next != NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () pointer to next was not NULL.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        free (arc->linetype);
        free (arc->layer);
        free (arc->dictionary_owner_soft);
        free (arc->material);
        free (arc->dictionary_owner_hard);
        free (arc->plot_style_name);
        free (arc->color_name);
        dxf_point_free (arc->p0);
        free (arc);
        arc = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}


/*!
 * \brief Free the allocated memory for a chain of DXF \c ARC
 * entities and all their data fields.
 */
void
dxf_arc_free_chain
(
        DxfArc *arcs
                /*!< a pointer to the chain of DXF \c ARC entities. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        if (arcs == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
        }
        while (arcs != NULL)
        {
                struct DxfArc *iter = arcs->next;
                dxf_arc_free (arcs);
                arcs = (DxfArc *) iter;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
}


/*!
 * \brief Get the ID code from a DXF \c ARC entity.
 *
 * \return ID code.
 */
int
dxf_arc_get_id_code
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->id_code < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->id_code);
}


/*!
 * \brief Set the ID code for a DXF \c ARC entity.
 */
DxfArc *
dxf_arc_set_id_code
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
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
        if (arc == NULL)
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
        arc->id_code = id_code;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the linetype from a DXF \c ARC entity.
 *
 * \return linetype when sucessful, \c NULL when an error occurred.
 */
char *
dxf_arc_get_linetype
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->linetype ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (arc->linetype));
}


/*!
 * \brief Set the linetype for a DXF \c ARC entity.
 */
DxfArc *
dxf_arc_set_linetype
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        char *linetype
                /*!< a string containing the linetype for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->linetype = strdup (linetype);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the layer from a DXF \c ARC entity.
 *
 * \return layer when sucessful, \c NULL when an error occurred.
 */
char *
dxf_arc_get_layer
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->layer ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (arc->layer));
}


/*!
 * \brief Set the layer for a DXF \c ARC entity.
 */
DxfArc *
dxf_arc_set_layer
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        char *layer
                /*!< a string containing the layer for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->layer = strdup (layer);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the elevation from a DXF \c ARC entity.
 *
 * \return elevation.
 */
double
dxf_arc_get_elevation
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->elevation);
}


/*!
 * \brief Set the elevation for a DXF \c ARC entity.
 */
DxfArc *
dxf_arc_set_elevation
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double elevation
                /*!< the elevation to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->elevation = elevation;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the thickness from a DXF \c ARC entity.
 *
 * \return thickness.
 */
double
dxf_arc_get_thickness
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->thickness < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->thickness);
}


/*!
 * \brief Set the thickness for a DXF \c ARC entity.
 */
DxfArc *
dxf_arc_set_thickness
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double thickness
                /*!< the thickness to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->thickness = thickness;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the linetype scale from a DXF \c ARC entity.
 *
 * \return linetype scale.
 */
double
dxf_arc_get_linetype_scale
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->linetype_scale < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->linetype_scale);
}


/*!
 * \brief Set the linetype scale for a DXF \c ARC entity.
 */
DxfArc *
dxf_arc_set_linetype_scale
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double linetype_scale
                /*!< the linetype scale to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->linetype_scale = linetype_scale;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the visibility from a DXF \c ARC entity.
 *
 * \return visibility.
 */
int16_t
dxf_arc_get_visibility
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->visibility < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->visibility > 1)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->visibility);
}


/*!
 * \brief Set the visibility for a DXF \c ARC entity.
 */
DxfArc *
dxf_arc_set_visibility
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        int16_t visibility
                /*!< the visibility to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->visibility = visibility;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the color from a DXF \c ARC entity.
 *
 * \return color.
 */
int
dxf_arc_get_color
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->color);
}


/*!
 * \brief Set the color for a DXF \c ARC entity.
 */
DxfArc *
dxf_arc_set_color
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        int color
                /*!< the color to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (color < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was passed.\n")),
                  __FUNCTION__);
        }
        arc->color = color;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the paperspace flag value from a DXF \c ARC entity.
 *
 * \return paperspace flag value.
 */
int
dxf_arc_get_paperspace
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->paperspace < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (arc->paperspace > 1)
        {
                fprintf (stderr,
                  (_("Warning in %s () an out of range value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->paperspace);
}


/*!
 * \brief Set the paperspace flag for a DXF \c ARC entity.
 */
DxfArc *
dxf_arc_set_paperspace
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        int paperspace
                /*!< the paperspace flag value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->paperspace = paperspace;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c graphics_data_size value from a DXF \c ARC entity.
 *
 * \return \c graphics_data_size value when successful, or
 * \c EXIT_FAILURE when an error occurred.
 */
int
dxf_arc_get_graphics_data_size
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->graphics_data_size < 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a negative value was found.\n")),
                  __FUNCTION__);
        }
        if (arc->graphics_data_size == 0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a zero value was found.\n")),
                  __FUNCTION__);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->graphics_data_size);
}


/*!
 * \brief Set the \c graphics_data_size value for a DXF \c ARC entity.
 *
 * \return a pointer to \c arc when successful, or \c NULL when an
 * error occurred.
 */
DxfArc *
dxf_arc_set_graphics_data_size
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        int graphics_data_size
                /*!< the \c graphics_data_size value to be set for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
                  (_("Warning in %s () a zero value was passed.\n")),
                  __FUNCTION__);
        }
        arc->graphics_data_size = graphics_data_size;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c shadow_mode from a DXF \c ARC entity.
 *
 * \return \c shadow_mode when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_arc_get_shadow_mode
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->shadow_mode < 0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->shadow_mode > 3)
        {
                fprintf (stderr,
                  (_("Error in %s () an out of range value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->shadow_mode);
}


/*!
 * \brief Set the \c shadow_mode for a DXF \c ARC entity.
 *
 * \return a pointer to \c arc when successful, or \c NULL when an
 * error occurred.
 */
DxfArc *
dxf_arc_set_shadow_mode
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        int16_t shadow_mode
                /*!< the shadow mode to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->shadow_mode = shadow_mode;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the pointer to the \c binary_graphics_data from a DXF
 * \c ARC entity.
 *
 * \return pointer to the \c binary_graphics_data.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfBinaryGraphicsData *
dxf_arc_get_binary_graphics_data
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->binary_graphics_data ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfBinaryGraphicsData *) arc->binary_graphics_data);
}


/*!
 * \brief Set the pointer to the \c binary_graphics_data for a DXF
 * \c ARC entity.
 */
DxfArc *
dxf_arc_set_binary_graphics_data
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        DxfBinaryGraphicsData *data
                /*!< a string containing the pointer to the
                 * \c binary_graphics_data for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->binary_graphics_data = (DxfBinaryGraphicsData *) data;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the soft pointer to the dictionary owner from a DXF 
 * \c ARC entity.
 *
 * \return soft pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_arc_get_dictionary_owner_soft
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->dictionary_owner_soft ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (arc->dictionary_owner_soft));
}


/*!
 * \brief Set the pointer to the dictionary_owner_soft for a DXF
 * \c ARC entity.
 */
DxfArc *
dxf_arc_set_dictionary_owner_soft
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        char *dictionary_owner_soft
                /*!< a string containing the pointer to the
                 * dictionary_owner_soft for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->dictionary_owner_soft = strdup (dictionary_owner_soft);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the pointer to the \c material from a DXF \c ARC entity.
 *
 * \return a pointer to \c material when successful, or \c NULL when an
 * error occurred.
 *
 * \warning No checks are performed on the returned pointer.
 */
char *
dxf_arc_get_material
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->material ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (arc->material));
}


/*!
 * \brief Set the pointer to the \c material for a DXF \c ARC entity.
 *
 * \return a pointer to \c arc when successful, or \c NULL when an
 * error occurred.
 */
DxfArc *
dxf_arc_set_material
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        char *material
                /*!< a string containing the pointer to the \c
                 * material for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->material = strdup (material);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the hard pointer to the dictionary owner from a DXF 
 * \c ARC entity.
 *
 * \return hard pointer to the dictionary owner.
 *
 * \warning No checks are performed on the returned pointer (string).
 */
char *
dxf_arc_get_dictionary_owner_hard
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->dictionary_owner_hard ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (arc->dictionary_owner_hard));
}


/*!
 * \brief Set the pointer to the dictionary_owner_hard for a DXF
 * \c ARC entity.
 */
DxfArc *
dxf_arc_set_dictionary_owner_hard
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        char *dictionary_owner_hard
                /*!< a string containing the pointer to the
                 * dictionary_owner_hard for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->dictionary_owner_hard = strdup (dictionary_owner_hard);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c lineweight from a DXF \c ARC entity.
 *
 * \return \c lineweight when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
int16_t
dxf_arc_get_lineweight
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->lineweight);
}


/*!
 * \brief Set the \c lineweight for a DXF \c ARC entity.
 *
 * \return a pointer to \c arc when successful, or \c NULL when an
 * error occurred.
 */
DxfArc *
dxf_arc_set_lineweight
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        int16_t lineweight
                /*!< the \c lineweight to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->lineweight = lineweight;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c plot_style_name from a DXF \c ARC entity.
 *
 * \return a pointer to \c plot_style_name when sucessful, or \c NULL
 * when an error occurred.
 */
char *
dxf_arc_get_plot_style_name
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->plot_style_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (arc->plot_style_name));
}


/*!
 * \brief Set the \c plot_style_name for a DXF \c ARC entity.
 *
 * \return a pointer to \c arc when successful, or \c NULL when an
 * error occurred.
 */
DxfArc *
dxf_arc_set_plot_style_name
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        char *plot_style_name
                /*!< a string containing the \c plot_style_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->plot_style_name = strdup (plot_style_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c color_value from a DXF \c ARC entity.
 *
 * \return \c color_value when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_arc_get_color_value
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->color_value);
}


/*!
 * \brief Set the \c color_value for a DXF \c ARC entity.
 *
 * \return a pointer to \c arc when successful, or \c NULL when an
 * error occurred.
 */
DxfArc *
dxf_arc_set_color_value
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        long color_value
                /*!< the \c color_value to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->color_value = color_value;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c color_name from a DXF \c ARC entity.
 *
 * \return \c color_name when sucessful, or \c NULL when an error
 * occurred.
 */
char *
dxf_arc_get_color_name
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->color_name ==  NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (strdup (arc->color_name));
}


/*!
 * \brief Set the \c color_name for a DXF \c ARC entity.
 *
 * \return a pointer to \c arc when successful, or \c NULL when an
 * error occurred.
 */
DxfArc *
dxf_arc_set_color_name
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        char *color_name
                /*!< a string containing the \c color_name for the
                 * entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->color_name = strdup (color_name);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the \c transparency from a DXF \c ARC entity.
 *
 * \return \c transparency when successful, or \c EXIT_FAILURE when an
 * error occurred.
 */
long
dxf_arc_get_transparency
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->transparency);
}


/*!
 * \brief Set the \c transparency for a DXF \c ARC entity.
 *
 * \return a pointer to \c arc when successful, or \c NULL when an
 * error occurred.
 */
DxfArc *
dxf_arc_set_transparency
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        long transparency
                /*!< the \c transparency to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->transparency = transparency;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the center point \c p0 of a DXF \c ARC entity.
 *
 * \return the center point \c p0.
 */
DxfPoint *
dxf_arc_get_p0
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->p0);
}


/*!
 * \brief Set the center point \c p0 of a DXF \c ARC entity.
 *
 * \return a pointer to a DXF \c ARC entity.
 */
DxfArc *
dxf_arc_set_p0
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        DxfPoint *p0
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->p0 = p0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the X-value of the center point \c x0 of a DXF \c ARC
 * entity.
 *
 * \return the X-value of the center point \c x0.
 */
double
dxf_arc_get_x0
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->p0->x0);
}


/*!
 * \brief Set the X-value of the center point \c x0 of a DXF \c ARC
 * entity.
 *
 * \return a pointer to \c arc when successful, or \c NULL when an
 * error occurred.
 */
DxfArc *
dxf_arc_set_x0
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double x0
                /*!< the X-value of the center point \c x0 of a DXF
                 * \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->p0->x0 = x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the Y-value of the center point \c y0 of a DXF \c ARC
 * entity.
 *
 * \return the Y-value of the center point \c y0.
 */
double
dxf_arc_get_y0
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->p0->y0);
}


/*!
 * \brief Set the Y-value of the center point \c y0 of a DXF \c ARC
 * entity.
 *
 * \return a pointer to \c arc when successful, or \c NULL when an
 * error occurred.
 */
DxfArc *
dxf_arc_set_y0
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double y0
                /*!< the Y-value of the center point \c y0 of a DXF
                 * \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->p0->y0 = y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the Z-value of the center point \c z0 of a DXF \c ARC
 * entity.
 *
 * \return the Z-value of the center point \c z0.
 */
double
dxf_arc_get_z0
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->p0->z0);
}


/*!
 * \brief Set the Z-value of the center point \c z0 of a DXF \c ARC
 * entity.
 *
 * \return a pointer to \c arc when successful, or \c NULL when an
 * error occurred.
 */
DxfArc *
dxf_arc_set_z0
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double z0
                /*!< the Z-value of the center point \c z0 of a DXF
                 * \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->p0 == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->p0->z0 = z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the radius from a DXF \c ARC entity.
 *
 * \return radius.
 */
double
dxf_arc_get_radius
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->radius < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->radius == 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a value of zero was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->radius);
}


/*!
 * \brief Set the radius for a DXF \c ARC entity.
 */
DxfArc *
dxf_arc_set_radius
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double radius
                /*!< the radius to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (radius < 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a negative value was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (radius == 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a value of zero was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->radius = radius;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the start angle from a DXF \c ARC entity.
 *
 * \return start angle.
 */
double
dxf_arc_get_start_angle
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->start_angle);
}


/*!
 * \brief Set the start angle for a DXF \c ARC entity.
 */
DxfArc *
dxf_arc_set_start_angle
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double start_angle
                /*!< the start angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->start_angle = start_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the end angle from a DXF \c ARC entity.
 *
 * \return end angle.
 */
double
dxf_arc_get_end_angle
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->end_angle);
}


/*!
 * \brief Set the end angle for a DXF \c ARC entity.
 */
DxfArc *
dxf_arc_set_end_angle
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double end_angle
                /*!< the end angle to be set for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->end_angle = end_angle;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Calculate the length of a DXF \c ARC entity.
 *
 * \return the length.
 */
double
dxf_arc_get_length
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->radius == 0.0)
        {
                fprintf (stderr,
                  (_("Error in %s () a radius of 0.0 was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (arc->radius < 0.0)
        {
                fprintf (stderr,
                  (_("Warning in %s () a radius smaller than 0.0 was found.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->radius * ((arc->end_angle - arc->start_angle) / 360.0));
}


/*!
 * \brief Get the extrusion vector as a DXF \c POINT entity from a DXF
 * \c ARC entity.
 *
 * \return a DXF \c POINT containing the extrusion coordinates.
 *
 * \warning No other members are copied into the DXF \c POINT.
 */
DxfPoint *
dxf_arc_get_extrusion_vector_as_point
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        DxfPoint *point = NULL;

        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        point = dxf_point_init (point);
        if (point == NULL)
        {
              fprintf (stderr,
                  (_("Error in %s () could not allocate memory.\n")),
                __FUNCTION__);
              return (NULL);
        }
        point->x0 = arc->extr_x0;
        point->y0 = arc->extr_y0;
        point->z0 = arc->extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (point);
}


/*!
 * \brief Get the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c ARC entity.
 *
 * \return the X-value of the extrusion vector \c extr_x0.
 */
double
dxf_arc_get_extr_x0
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->extr_x0);
}


/*!
 * \brief Set the X-value of the extrusion vector \c extr_x0 of a DXF
 * \c ARC entity.
 *
 * \return a pointer to \c arc when successful, or \c NULL when an
 * error occurred.
 */
DxfArc *
dxf_arc_set_extr_x0
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double extr_x0
                /*!< the X-value of the extrusion vector \c extr_x0 of a
                 * DXF \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->extr_x0 = extr_x0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c ARC entity.
 *
 * \return the Y-value of the extrusion vector \c extr_y0.
 */
double
dxf_arc_get_extr_y0
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->extr_y0);
}


/*!
 * \brief Set the Y-value of the extrusion vector \c extr_y0 of a DXF
 * \c ARC entity.
 *
 * \return a pointer to \c arc when successful, or \c NULL when an
 * error occurred.
 */
DxfArc *
dxf_arc_set_extr_y0
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double extr_y0
                /*!< the Y-value of the extrusion vector \c extr_y0 of a
                 * DXF \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->extr_y0 = extr_y0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c ARC entity.
 *
 * \return the Z-value of the extrusion vector \c extr_z0.
 */
double
dxf_arc_get_extr_z0
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif

        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc->extr_z0);
}


/*!
 * \brief Set the Z-value of the extrusion vector \c extr_z0 of a DXF
 * \c ARC entity.
 *
 * \return a pointer to \c arc when successful, or \c NULL when an
 * error occurred.
 */
DxfArc *
dxf_arc_set_extr_z0
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double extr_z0
                /*!< the Z-value of the extrusion vector \c extr_z0 of a
                 * DXF \c ARC entity. */
)
{
#ifdef DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Set the extrusion vector from a DXF \c POINT for a DXF \c ARC
 * entity.
 */
DxfArc *
dxf_arc_set_extrusion_vector_from_point
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        DxfPoint *point
                /*!< a pointer to a DXF \c POINT entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (point == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->extr_x0 = (double) point->x0;
        arc->extr_y0 = (double) point->y0;
        arc->extr_z0 = (double) point->z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Set the extrusion vector for a DXF \c ARC entity.
 */
DxfArc *
dxf_arc_set_extrusion_vector
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        double extr_x0,
                /*!<  X-value of the extrusion direction. */
        double extr_y0,
                /*!<  Y-value of the extrusion direction. */
        double extr_z0
                /*!<  Z-value of the extrusion direction. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        arc->extr_x0 = extr_x0;
        arc->extr_y0 = extr_y0;
        arc->extr_z0 = extr_z0;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the pointer to the next \c ARC entity from a DXF
 * \c ARC entity.
 *
 * \return pointer to the next \c ARC entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfArc *
dxf_arc_get_next
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->next == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return (NULL);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfArc *) arc->next);
}


/*!
 * \brief Set the pointer to the next \c ARC for a DXF \c ARC
 * entity.
 */
DxfArc *
dxf_arc_set_next
(
        DxfArc *arc,
                /*!< a pointer to a DXF \c ARC entity. */
        DxfArc *next
                /*!< a pointer to the next \c ARC for the entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
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
        arc->next = (struct DxfArc *) next;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (arc);
}


/*!
 * \brief Get the pointer to the last \c ARC entity from a linked list
 * of DXF \c ARC entities.
 *
 * \return pointer to the last \c ARC entity.
 *
 * \warning No checks are performed on the returned pointer.
 */
DxfArc *
dxf_arc_get_last
(
        DxfArc *arc
                /*!< a pointer to a DXF \c ARC entity. */
)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        /* Do some basic checks. */
        if (arc == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (NULL);
        }
        if (arc->next == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was found.\n")),
                  __FUNCTION__);
                return ((DxfArc *) arc);
        }
        DxfArc *iter = (DxfArc *) arc->next;
        while (iter->next != NULL)
        {
                iter = (DxfArc *) iter->next;
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return ((DxfArc *) iter);
}


/* EOF*/
