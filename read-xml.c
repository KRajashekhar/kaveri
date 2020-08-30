#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

char configReceive[8][80] = { " " };

//xml parsing
void ParsingXMLFile(char *filename) {
    char         *docname;
    xmlDocPtr    doc;
    xmlNodePtr   cur;
    xmlChar      *uri;
    char config[8][80] = { "Messag ID","Message Type", "Sender","Destination","CreationDateTime","Signature","ReferenceId","Payload"};
    int count = 0;
    int count1 = 0;

    docname = filename;
    doc = xmlParseFile(docname);
    cur = xmlDocGetRootElement(doc);
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"bmd"))) {
            uri = xmlGetProp(cur, (xmlChar *)config[count++]);
            strcpy(configReceive[count1++], (char *)uri);
            xmlFree(uri);
        }
        cur = cur->next;
    }

    count = 0;
    count1 = 0;
    xmlFreeDoc(doc);
}
