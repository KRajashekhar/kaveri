#include <stdio.h>

#include "munit.h"
#include "esb.h"
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

    munit_assert(queue_the_request(b,"../Testing/bmd.xml")==1);
    return MUNIT_OK;
}

static MunitResult
 test_process_esb_request(const MunitParameter params[], void *fixture)
 {
 	bmd *b=(bmd *)fixture;
 	
 	munit_assert(process_esb_request("../Testing/bmd.xml")==1);
 	return MUNIT_OK;
 	
 }
 
 MunitTest esb_tests[] ={
 	{
 	//processing the esb request
 	test_process_esb_request,
 	NULL,
 	NULL,
 	MUNIT_TEST_OPTION_NONE,
 	NULL
 	},
 	
 	{
 	//queue_the_request,
 	test_queue_the_request,
 	NULL,
 	NULL,
 	MUNIT_TEST_OPTION_NONE,
 	NULL
 	},
 	
 	{NULL,NULL,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL}
 	};
 	
 	//arranging the cases into respective suites,
 	
 	static const MunitSuite suite{
 	//es_tests,
 	esb_tests,
 	NULL
 	1,
 	MUNIT_TEST_OPTION_NONE
 	};
 	
 	//checking the tests
 	int main(int argc, const char* argv[]){
 	return munit_suite_main(&suite,NULL,argc,NULL);
 	}
