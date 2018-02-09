/* 
 * Copyright (C) 2008 Red Hat, Inc.
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
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * Author: Matthias Clasen <mclasen@redhat.com>
 */

#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <gio/gio.h>


typedef struct 
{
	gchar *path;
	GFileType type;
	guint match_case : 1;
	guint executable : 1;
	guint non_empty  : 1;
	guint on_disc    : 1;
	gchar *mimetype;
	GList *matches;
} TreeMatchlet;

typedef struct
{
	gchar *contenttype;
	gint priority;
	GList *matches;
} TreeMatch;

static GList *tree_matches = NULL;

static void
tree_matchlet_free (TreeMatchlet *matchlet)
{
	g_list_foreach (matchlet->matches, (GFunc)tree_matchlet_free, NULL);
	g_list_free (matchlet->matches);
	g_free (matchlet->path);
	g_free (matchlet->mimetype);
	g_slice_free (TreeMatchlet, matchlet);
}

static void
tree_match_free (TreeMatch *match)
{
	g_list_foreach (match->matches, (GFunc)tree_matchlet_free, NULL);
	g_list_free (match->matches);
	g_free (match->contenttype);
	g_slice_free (TreeMatch, match);
}

static void 
tree_magic_shutdown (void)
{
	g_list_foreach (tree_matches, (GFunc)tree_match_free, NULL);
	g_list_free (tree_matches);
	tree_matches = NULL;
}

static TreeMatch *
parse_header (gchar *line)
{
	gint len;
	gchar *s;
	TreeMatch *match;

	len = strlen (line);

	if (line[0] != '[' || line[len - 1] != ']')
		return NULL;
	
	line[len - 1] = 0;
	s = strchr (line, ':');
	
	match = g_slice_new0 (TreeMatch);
	match->priority = atoi (line + 1);
	match->contenttype = g_strdup (s + 1);

	return match;
}

static TreeMatchlet *
parse_match_line (gchar *line, 
		  gint  *depth)
{
	gchar *s, *p;
	TreeMatchlet *matchlet;
	gchar **parts;
	gint i;

	matchlet = g_slice_new0 (TreeMatchlet);

	if (line[0] == '>') {
		*depth = 0;
		s = line;
	}
	else {
		*depth = atoi (line);
		s = strchr (line, '>');
	}
	s += 2; 
	p = strchr (s, '"');
	*p = 0;
	
	matchlet->path = g_strdup (s);
	s = p + 1;
	parts = g_strsplit (s, ",", 0);
	if (strcmp (parts[0], "=file") == 0)
		matchlet->type = G_FILE_TYPE_REGULAR;
	else if (strcmp (parts[0], "=directory") == 0)
		matchlet->type = G_FILE_TYPE_DIRECTORY;
	else if (strcmp (parts[0], "=link") == 0)
		matchlet->type = G_FILE_TYPE_SYMBOLIC_LINK;
	else
		matchlet->type = G_FILE_TYPE_UNKNOWN;
	for (i = 1; parts[i]; i++) {
		if (strcmp (parts[i], "executable") == 0)
			matchlet->executable = 1;
		else if (strcmp (parts[i], "match-case") == 0)
			matchlet->match_case = 1;
		else if (strcmp (parts[i], "non-empty") == 0)
			matchlet->non_empty = 1;
		else if (strcmp (parts[i], "on-disc") == 0)
			matchlet->on_disc = 1;
		else 
			matchlet->mimetype = g_strdup (parts[i]);
	}

	g_strfreev (parts);

	return matchlet;
}

static gint
cmp_match (gconstpointer a, gconstpointer b)
{
	const TreeMatch *aa = (const TreeMatch *)a;
	const TreeMatch *bb = (const TreeMatch *)b;

	return bb->priority - aa->priority;
}

static void
insert_match (TreeMatch *match)
{
	tree_matches = g_list_insert_sorted (tree_matches, match, cmp_match);
}

static void
insert_matchlet (TreeMatch    *match, 
		 TreeMatchlet *matchlet, 
		 gint          depth)
{
	g_return_if_fail (match != NULL);

	if (depth == 0) 
		match->matches = g_list_append (match->matches, matchlet);
	else {
		GList *last;
		TreeMatchlet *m;

		last = g_list_last (match->matches);
		if (!last) {
			tree_matchlet_free (matchlet);
			g_warning ("can't insert matchlet at depth %d", depth);
			return;
		}

		m = (TreeMatchlet *) last->data;
		depth--;
		while (depth > 0) {
			last = g_list_last (m->matches);
			if (!last) {
				tree_matchlet_free (matchlet);
				g_warning ("can't insert matchlet at depth %d", depth);
				return;
			}
			
			m = (TreeMatchlet *) last->data;
			depth--;
		}
		m->matches = g_list_append (m->matches, matchlet);
	}
}

static void
read_tree_magic_from_directory (const gchar *prefix)
{
	gchar *filename;
	gchar *text;
	gsize len;
	gint i;
	TreeMatch *match;
	TreeMatchlet *matchlet;
	gint depth;

	filename = g_build_filename (prefix, "mime", "treemagic", NULL);
	match = NULL;

	if (g_file_get_contents (filename, &text, &len, NULL)) {
		if (strcmp (text, "MIME-TreeMagic") == 0) {
			gchar **lines;

			lines = g_strsplit (text + strlen ("MIME-TreeMagic") + 2, "\n", 0);
			for (i = 0; lines[i] && lines[i][0]; i++) {
				if (lines[i][0] == '[') {
					match = parse_header (lines[i]);
					insert_match (match);
				}
				else {
					matchlet = parse_match_line (lines[i], &depth);
					insert_matchlet (match, matchlet, depth);
				}
			}
			g_strfreev (lines);
		}
		else 
			g_warning ("%s: header not found, skipping\n", filename);

		g_free (text);
	}
	
	g_free (filename);
}

typedef struct 
{
	gchar *path;
	gint depth;
	gboolean ignore_case;
	gchar **components;
	gchar **case_components;
	GFileEnumerator **enumerators;
	GFile **children;
} Enumerator;

static gboolean
component_match (Enumerator  *e, 
		 gint         depth, 
		 const gchar *name)
{
	gchar *case_folded, *key;
	gboolean found;

	if (strcmp (name, e->components[depth]) == 0)
		return TRUE;

	if (!e->ignore_case)
		return FALSE;

	case_folded = g_utf8_casefold (name, -1);
	key = g_utf8_collate_key (case_folded, -1);

	found = strcmp (key, e->case_components[depth]) == 0;

	g_free (case_folded);
	g_free (key);

	return found;
}

static GFile *
next_match_recurse (Enumerator *e, 
		    gint        depth)
{
	GFile *file;
	GFileInfo *info;
	const gchar *name;

	while (TRUE) {
		if (e->enumerators[depth] == NULL) {
			if (depth > 0) {
				file = next_match_recurse (e, depth - 1);
				if (file)  {
					e->children[depth] = file;
					e->enumerators[depth] = g_file_enumerate_children (file,
									G_FILE_ATTRIBUTE_STANDARD_NAME,
									G_FILE_QUERY_INFO_NONE,
									NULL,
									NULL);
				}
			}
			if (e->enumerators[depth] == NULL)
				return NULL;
		}

		while ((info = g_file_enumerator_next_file (e->enumerators[depth], NULL, NULL))) {
			name = g_file_info_get_name (info);
			if (component_match (e, depth, name)) {
				file = g_file_get_child (e->children[depth], name);
				g_object_unref (info);
				return file;
			}
			g_object_unref (info);
		}

		g_object_unref (e->enumerators[depth]);
		e->enumerators[depth] = NULL;
		g_object_unref (e->children[depth]);
		e->children[depth] = NULL;
	}
}

static GFile *
enumerator_next (Enumerator *e)
{
	return next_match_recurse (e, e->depth - 1);
}

static Enumerator *
enumerator_new (GFile      *root,
		const char *path, 
		gboolean    ignore_case)
{
	Enumerator *e;
	gint i;
	gchar *case_folded;

	e = g_new0 (Enumerator, 1);
	e->path = g_strdup (path);
	e->ignore_case = ignore_case;

	e->components = g_strsplit (e->path, G_DIR_SEPARATOR_S, -1);
	e->depth = g_strv_length (e->components);
	if (e->ignore_case) {
		e->case_components = g_new0 (char *, e->depth + 1);
		for (i = 0; e->components[i]; i++) {
			case_folded = g_utf8_casefold (e->components[i], -1);
			e->case_components[i] = g_utf8_collate_key (case_folded, -1);
			g_free (case_folded);
		}	
	}

	e->children = g_new0 (GFile *, e->depth);
	e->children[0] = g_object_ref (root);
	e->enumerators = g_new0 (GFileEnumerator *, e->depth);
	e->enumerators[0] = g_file_enumerate_children (root,
						       G_FILE_ATTRIBUTE_STANDARD_NAME,
						       G_FILE_QUERY_INFO_NONE,
						       NULL,
						       NULL);

	return e;
}

static void
enumerator_free (Enumerator *e)
{
	gint i;

	for (i = 0; i < e->depth; i++) { 
		if (e->enumerators[i]) 
			g_object_unref (e->enumerators[i]);
		if (e->children[i])
			g_object_unref (e->children[i]);
	}

	g_free (e->enumerators);
	g_free (e->children);
	g_strfreev (e->components);
	if (e->case_components)
		g_strfreev (e->case_components);
	g_free (e->path);
	g_free (e);
}

static gboolean
matchlet_match (TreeMatchlet *matchlet,
		GFile        *root)
{
	GFile *file;
	GFileInfo *info;
	gboolean result;
	const gchar *attrs;
	Enumerator *e;
	GList *l;

	e = enumerator_new (root, matchlet->path, !matchlet->match_case);
	
	do {
 		file = enumerator_next (e);
		if (!file) {
			enumerator_free (e);	
			return FALSE;
		}

		if (matchlet->mimetype)
			attrs = G_FILE_ATTRIBUTE_STANDARD_TYPE ","
				G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE ","
				G_FILE_ATTRIBUTE_STANDARD_CONTENT_TYPE;
		else
			attrs = G_FILE_ATTRIBUTE_STANDARD_TYPE ","
				G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE;
		info = g_file_query_info (file, 
					  attrs,
					  G_FILE_QUERY_INFO_NONE,
					  NULL,
					  NULL);
		if (info) {
			result = TRUE;

			if (matchlet->type != G_FILE_TYPE_UNKNOWN &&
			    g_file_info_get_file_type (info) != matchlet->type) 
				result = FALSE;

			if (matchlet->executable &&
			    !g_file_info_get_attribute_boolean (info, G_FILE_ATTRIBUTE_ACCESS_CAN_EXECUTE))
				result = FALSE;
		}	
		else 
			result = FALSE;

		if (result && matchlet->non_empty) {
			GFileEnumerator *child_enum;
			GFileInfo *child_info;

			child_enum = g_file_enumerate_children (file, 
								G_FILE_ATTRIBUTE_STANDARD_NAME,
								G_FILE_QUERY_INFO_NONE,
								NULL,
								NULL);
	
			if (child_enum) {
				child_info = g_file_enumerator_next_file (child_enum, NULL, NULL);
				if (child_info)
					g_object_unref (child_info);
				else 
					result = FALSE;	
				g_object_unref (child_enum);
			}
			else 
				result = FALSE;
		}
	
		if (result && matchlet->mimetype) {
			if (strcmp (matchlet->mimetype, g_file_info_get_content_type (info)) != 0) 
				result = FALSE;
		}
	
		g_object_unref (info);
		g_object_unref (file);
	
	}
	while (!result);	

	enumerator_free (e);
	
	if (!matchlet->matches) 
		return TRUE;

	for (l = matchlet->matches; l; l = l->next) {
		TreeMatchlet *submatchlet;

		submatchlet = l->data;
		if (matchlet_match (submatchlet, root))
			return TRUE;
	}

	return FALSE;
}

static void
match_match (TreeMatch   *match,
	     GFile       *root,
	     GPtrArray   *types)
{
	GList *l;
	
	for (l = match->matches; l; l = l->next) {
		TreeMatchlet *matchlet = l->data;
		if (matchlet_match (matchlet, root)) {
			g_ptr_array_add (types, g_strdup (match->contenttype));
			break;
		}
	}
}

static void
tree_magic_init (void)
{
	static gboolean initialized = FALSE;
	const gchar *dir;
	const gchar * const * dirs;
	int i;

	if (!initialized) {
		initialized = TRUE;

		dir = g_get_user_data_dir ();

		read_tree_magic_from_directory (dir);

		dirs = g_get_system_data_dirs ();
		for (i = 0; dirs[i]; i++)
			read_tree_magic_from_directory (dirs[i]);
	}
}

static GPtrArray *
sniff_content_type (GFile *root)
{
	GPtrArray *types;
	GList *l;

	/* TODO: monitor and reload */
	tree_magic_init ();

	types = g_ptr_array_new ();

	for (l = tree_matches; l; l = l->next) {
		TreeMatch *match = l->data;
		match_match (match, root, types);
	}

	return types;
}

static gboolean
handle_one_line (const char *line)
{
	GFile *file;
	GPtrArray *array;
	gboolean retval = TRUE;
	gboolean supposed_to_fail = FALSE;
	char **items, **mimetypes;
	char *filename;
	guint i;

	if (strncmp (line, "x ", 2) == 0) {
		supposed_to_fail = TRUE;
		items = g_strsplit (line + 2, " ", 2);
	} else {
		items = g_strsplit (line, " ", 2);
	}

	filename = items[0];
	mimetypes = g_strsplit (items[1], " ", -1);

	file = g_file_new_for_commandline_arg (filename);

	array = sniff_content_type (file);
	if (array->len == 0) {
		if (supposed_to_fail == FALSE) {
			g_warning ("Tree %s didn't match %s (found nothing)",
				   filename, items[1]);
			retval = FALSE;
		} else {
			g_message ("Tree %s failed to match %s (expected)",
				   filename, items[1]);
			retval = TRUE;
		}
		goto bail;
	}

	for (i = 0; i < array->len; i++) {
		char *found;
		gboolean matched;
		guint j;

		matched = FALSE;
		found = (char *) array->pdata[i];
		for (j = 0; mimetypes[j] != NULL; j++) {
			if (strcmp (mimetypes[j], found) == 0) {
				matched = TRUE;
				break;
			}
		}
		if (matched == FALSE && supposed_to_fail == FALSE) {
			g_warning ("Tree %s didn't match %s (found %s)",
				   filename, items[1], found);
			retval = FALSE;
			goto bail;
		} else if (matched == FALSE) {
			g_message ("Tree %s failed to match %s (expected)",
				   filename, items[1]);
		} else {
			g_message ("Tree %s looks good (found %s)",
				   filename, found);
		}
	}

bail:
	g_strfreev (items);
	g_ptr_array_free (array, TRUE);
	g_strfreev (mimetypes);

	return retval;
}

static const char *
type_to_path (GFileType type)
{
	switch (type) {
	case G_FILE_TYPE_REGULAR:
		return "Regular";
	case G_FILE_TYPE_DIRECTORY:
		return "Directory";
	case G_FILE_TYPE_SYMBOLIC_LINK:
		return "Symbolic link";
	default:
		return "Unknown";
	}
}

static void
print_matchlet (TreeMatchlet *matchlet, guint depth)
{
	GList *l;
	guint i;

	for (i = depth + 1; i != 0; i--)
		g_print ("\t");
	g_print ("%s (type=%s)\n", matchlet->path, type_to_path (matchlet->type));
	for (l = matchlet->matches ; l != NULL; l = l->next)
		print_matchlet (l->data, depth + 1);
}

int main (int argc, char **argv)
{
	GError *error = NULL;
	char *content, **lines;
	guint i;

	g_type_init ();

	if (argc != 2) {
		g_print ("Usage: %s [file]\n", argv[0]);
		g_print ("Where file contains, on each line, a directory path,\n"
			 "followed by one or more content types\n");
		g_print ("Lines starting with '#' are ignored\n");
		g_print ("Examples:\n");
		g_print ("\t#Supposed to work\n");
		g_print ("\ttests/image-dcf x-content/image-dcf\n");
		g_print ("\t# Supposed to fail\n");
		g_print ("\tx tests/ x-content/image-dcf\n");
		return 1;
	}

	if (strcmp (argv[1], "-d") == 0) {
		GList *l;

		tree_magic_init ();
		for (l = tree_matches ; l != NULL; l = l->next) {
			GList *k;
			TreeMatch *match = (TreeMatch *) l->data;
			g_print ("Type: %s\n", match->contenttype);
			for (k = match->matches ; k != NULL; k = k->next) {
				TreeMatchlet *matchlet = (TreeMatchlet *) k->data;
				print_matchlet (matchlet, 0);
			}
		}
		return 0;
	}

	if (g_file_get_contents (argv[1], &content, NULL, &error) == FALSE) {
		g_warning ("Failed to load %s: %s", argv[1], error->message);
		return 1;
	}
	lines = g_strsplit (content, "\n", -1);
	g_free (content);

	for (i = 0; lines[i] != NULL; i++) {
		if (*lines[i] == '\0' || *lines[i] == '#')
			continue;
		if (handle_one_line (lines[i]) == FALSE)
			return 1;
	}

	tree_magic_shutdown ();

	return 0;
}

