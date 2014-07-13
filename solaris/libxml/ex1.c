#include <stdio.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>


int main (int argc , char **argv)
{
	xmlDocPtr     pdoc = NULL;
	xmlNodePtr    proot = NULL, curNode = NULL;
	char *psfilename;

	if (argc < 1)
	{
		printf ("usage: %s xml_file\n", argv[0]);
		exit (1);
	}

	psfilename = argv[1];
	// open xml file
	//xmlKeepBlanksDefault(0);
	pdoc = xmlReadFile (psfilename, "UTF-8", XML_PARSE_RECOVER);

	if (pdoc == NULL)
	{
		printf ("failed to open file: %s \n", psfilename);
		exit (1);
	}

	// get root content
	proot = xmlDocGetRootElement (pdoc);

	if (proot == NULL)
	{
		printf("error: no root node in xml file!! \n", psfilename);
		exit (1);
	}


	if (xmlStrcmp (proot->name, BAD_CAST "root") != 0)
	{
		printf ("file is error!!\n" );
		exit (1);
	}

	if (xmlHasProp (proot, BAD_CAST "version"))
	{
		xmlChar *szAttr = xmlGetProp (proot, BAD_CAST "version");
		printf ("version: %s \nroot:%s\n" , szAttr, proot->name);
	}
	else
	{
		printf (" no message in xml file.\n");
	}

	curNode = proot->xmlChildrenNode;

	char n=0;
	while (curNode != NULL)
	{
		if (curNode->name != BAD_CAST "text")
		{
			printf ("child-node%d , %s\n", n++,curNode->name);
		}
		curNode = curNode->next;
	}

	xmlFreeDoc (pdoc);
	xmlCleanupParser ();
	return 0;
}
