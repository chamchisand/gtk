/* GTK - The GIMP Toolkit
 *
 * Copyright © 2017 Benjamin Otte <otte@gnome.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __GSK_SL_FUNCTION_PRIVATE_H__
#define __GSK_SL_FUNCTION_PRIVATE_H__

#include <glib.h>

#include "gsksltypesprivate.h"

G_BEGIN_DECLS

GskSlFunction *         gsk_sl_function_new_constructor         (GskSlType              *type);
GskSlFunction *         gsk_sl_function_new_native              (const GskSlNativeFunction *native);
GskSlFunction *         gsk_sl_function_new_parse               (GskSlScope             *scope,
                                                                 GskSlPreprocessor      *stream,
                                                                 GskSlType              *return_type,
                                                                 const char             *name);

GskSlFunction *         gsk_sl_function_ref                     (GskSlFunction          *function);
void                    gsk_sl_function_unref                   (GskSlFunction          *function);

void                    gsk_sl_function_print                   (const GskSlFunction    *function,
                                                                 GskSlPrinter           *printer);

const char *            gsk_sl_function_get_name                (const GskSlFunction    *function);
GskSlType *             gsk_sl_function_get_return_type         (const GskSlFunction    *function);
gsize                   gsk_sl_function_get_n_arguments         (const GskSlFunction    *function);
GskSlType *             gsk_sl_function_get_argument_type       (const GskSlFunction    *function,
                                                                 gsize                   i);
GskSlValue *            gsk_sl_function_get_constant            (const GskSlFunction    *function,
                                                                 GskSlValue            **values,
                                                                 gsize                   n_values);
guint32                 gsk_sl_function_write_spv               (const GskSlFunction    *function,
                                                                 GskSpvWriter           *writer,
                                                                 GskSpvWriterFunc        initializer,
                                                                 gpointer                initializer_data);
guint32                 gsk_sl_function_write_call_spv          (GskSlFunction          *function,
                                                                 GskSpvWriter           *writer,
                                                                 guint32                *arguments);

struct _GskSlFunctionMatcher
{
  GList *best_matches;
  GList *matches;
};

void                    gsk_sl_function_matcher_init            (GskSlFunctionMatcher   *matcher,
                                                                 GList                  *list);
void                    gsk_sl_function_matcher_finish          (GskSlFunctionMatcher   *matcher);

gboolean                gsk_sl_function_matcher_has_matches     (GskSlFunctionMatcher   *matcher);
GskSlFunction *         gsk_sl_function_matcher_get_match       (GskSlFunctionMatcher   *matcher);

void                    gsk_sl_function_matcher_match_n_arguments (GskSlFunctionMatcher *matcher,
                                                                 gsize                   n_arguments);
void                    gsk_sl_function_matcher_match_argument  (GskSlFunctionMatcher   *matcher,
                                                                 gsize                   n,
                                                                 const GskSlType        *argument_type);
void                    gsk_sl_function_matcher_match_function  (GskSlFunctionMatcher   *matcher,
                                                                 const GskSlFunction    *function);

G_END_DECLS

#endif /* __GSK_SL_FUNCTION_PRIVATE_H__ */