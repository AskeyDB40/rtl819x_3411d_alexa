#include <libxml/tree.h>
#include <stdio.h>
#include <string.h>

int
main (int    argc,
      char **argv)
{
	xmlDocPtr doc;
	xmlNodePtr node;

	doc = xmlReadFile ("freedesktop.org.xml", NULL, 0);
	if (doc == NULL) {
		fprintf (stderr, "Reading \"freedesktop.org.xml\" failed. Aborting.\n");
		return 1;
	}

	if ((node = xmlDocGetRootElement (doc)) == NULL) {
		fprintf (stderr, "\"freedesktop.org.xml\" has no root node. Aborting.\n");
		return 1;
	}

	for (node = node->children; node != NULL; node = node->next) {
		if (!strcmp ((char *) node->name, "mime-type")) {
			xmlNodePtr p;
			xmlChar *prop;

			for (p = node->children; p != NULL; p = p->next) {
				if (!strcmp ((char *) p->name, "sub-class-of")) {
					break;
				}
			}

			if (p != NULL) {
				/* got sub-class-of node */
				continue;
			}

			prop = xmlGetProp (node, (xmlChar *) "type");
			printf ("%s\n", prop);
			xmlFree (prop);
		}
	}

	xmlFreeDoc (doc);
	return 0;
}
