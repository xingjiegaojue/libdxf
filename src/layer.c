/*!
 * \file layer.c
 *
 * \author Copyright (C) 2008 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief DXF layer entity.
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


#include "layer.h"


/*!
 * \brief Allocate memory for a DXF \c LAYER.
 *
 * Fill the memory contents with zeros.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfLayer *
dxf_layer_new ()
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_layer_new () function.\n",
                __FILE__, __LINE__);
#endif
        DxfLayer *dxf_layer = NULL;
        size_t size;

        size = sizeof (DxfLayer);
        /* avoid malloc of 0 bytes */
        if (size == 0) size = 1;
        if ((dxf_layer = malloc (size)) == NULL)
        {
                fprintf (stderr, "ERROR in dxf_layer_new () could not allocate memory for a DxfLayer struct.\n");
                dxf_layer = NULL;
        }
        else
        {
                memset (dxf_layer, 0, size);
        }
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_arc_new () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_layer);
}


/*!
 * \brief Allocate memory and initialize data fields in a DXF \c LAYER
 * table.
 * 
 * \return \c NULL when no memory was allocated, a pointer to the
 * allocated memory when succesful.
 */
DxfLayer *
dxf_layer_init
(
        DxfLayer *dxf_layer
                /*!< DXF LAYER table. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_layer_init () function.\n",
                __FILE__, __LINE__);
#endif
        dxf_layer = dxf_layer_new ();
        if (dxf_layer == NULL)
        {
              fprintf (stderr, "ERROR in dxf_layer_init () could not allocate memory for a DxfLayer struct.\n");
              return (NULL);
        }
        dxf_layer->layer_name = strdup ("");
        dxf_layer->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_layer->color = DXF_COLOR_BYLAYER;
        dxf_layer->flag = 0;
        dxf_layer->plotting_flag = 0;
        dxf_layer->material = strdup ("");
        dxf_layer->lineweight = 0;
        dxf_layer->plot_style_name = strdup ("");
        dxf_layer->next = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_arc_init () function.\n",
                __FILE__, __LINE__);
#endif
        return (dxf_layer);
}


/*!
 * \brief Free the allocated memory for a DXF \c LAYER and all it's
 * data fields.
 *
 * \return \c EXIT_SUCCESS when done, or \c EXIT_FAILURE when an error
 * occurred.
 */
int
dxf_layer_free
(
        DxfLayer *dxf_layer
                /*!< Pointer to the memory occupied by the DXF \c LAYER
                 * table. */
)
{
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Entering dxf_layer_free () function.\n",
                __FILE__, __LINE__);
#endif
        if (dxf_layer->next != NULL)
        {
              fprintf (stderr, "ERROR in dxf_layer_free () pointer to next DxfLayer was not NULL.\n");
              return (EXIT_FAILURE);
        }
        free (dxf_layer->layer_name);
        free (dxf_layer->linetype);
        free (dxf_layer->material);
        free (dxf_layer->plot_style_name);
        free (dxf_layer);
        dxf_layer = NULL;
#if DEBUG
        fprintf (stderr, "[File: %s: line: %d] Leaving dxf_layer_free () function.\n",
                __FILE__, __LINE__);
#endif
        return (EXIT_SUCCESS);
}


/* EOF */
