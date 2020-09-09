#include <stdio.h>

#include "munit.h"
#include "esb.h"
/** Include Module that has bmd handling 
 * functions and  bmd structure declaration 
 * 
 */ 
#include "../db_access/bmd.h"

/** Module that has mysql C API functions */

#include "../db_access/connector.h"


static MunitResult
test_queue_the_request(const MunitParameter params[], void *fixture)
{
    bmd *b = parse_bmd_xml("../Testing/bmd.xml");

    munit_assert(queue_the_request(b,"../Testing/bmd.xml")==1);
    return MUNIT_OK;
}
