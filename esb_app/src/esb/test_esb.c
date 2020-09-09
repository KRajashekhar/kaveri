#include <stdio.h>

#include "munit.h"
//#include "esb.h"
/** Include Module that has bmd handling 
 * functions and  bmd structure declaration 
 * 
 */ 
#include "../bmd/bmd.h"

/*
<<<<<<< HEAD


//#include "../db_access/connector.h"
=======



>>>>>>> bc12a8df81135c2ea1698ed5a3b299689e074c50

*/

static MunitResult
test_queue_the_request(const MunitParameter params[], void *fixture)
{
    bmd b = parse_bmd_xml("../Testing/bmd.xml");

    //munit_assert(test_queue_the_request(b,"../Testing/bmd.xml")==1);
    return MUNIT_OK;
}
