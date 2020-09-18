#include "munit.h"
#include "esb.h"
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<stdio.h>
#include "../bmd/xmljson.c"
#include "../bmd/bmd.h"
#include"../bmd/transport.c"
/**
 * If the name of a test function is "test_abc" then you should
 * define the setup and teardown functions by the names:
 * test_abc_setup and test_abc_tear_down respectively.
 */
static void *
test_parse_bmd_xml_setup(const MunitParameter params[], void *user_data)
{
    /**
     * Return the data that will be used for test1. Here we
     * are just return a string. It can be a struct or anything.
     * The memory that you allocate here for the test data
     * has to be cleaned up in corresponding tear down function,
     * which in this case is test1_tear_down.
     */
     DIR *d;
     struct dirent *dir;
     d=opendir("./Testing");
     char **s;
     s=malloc(100*sizeof(char *));
     int i=0;
     if(d)
     {
     	while((dir=readdir(d))!=NULL)
     	{
     		char *file=strdup(dir->d_name);
     		if(file[0]=='.')
     		{
     			continue;
     		}
     		char cwd[100];
     		getcwd(cwd,sizeof(cwd));
     		char path[100];
     		sprintf(path,"%s/Testing/%s",cwd,file);
     		s[i]=strdup(path);
     		free(file);
     		i++;
     	}
     	closedir(d);
     }
     return s;
    }
    static void test_parse_bmd_xml_tear_down(void *fixture)
    {
    
    	//receives the pointer to data if that data was created in test1_setup function
    	free(fixture);
    }
    
    
static MunitResult
test_parse_bmd_xml(const MunitParameter params[], void *fixture)
{
    char **str = (char **)fixture;
    /**
     * Perform the checking of logic here as needed.
     * Typically, you will invoke the function under testing
     * here by passing it suitable data from fixture. Then,
     * use assertions to verify the expected results.
     * In this example, we are just checking the value of a
     * string which we were expecting to be available in the
     * fixture itself. This test will fail when you change the
     * string. You will need to recompile and re-run the tests
     * to see the effect of any changes in data in this example.
     */
     int i=0;
     while(str[i]!=NULL)
     {
     	bmd *bmd;
     	bmd=parse_bmd_xml(str[i]);
     	munit_assert_true(bmd!=NULL);
     	
     	free(bmd);
     	i++;
     }
    //munit_assert_string_equal(str, "/path/to/bmd.xml");

    // Invoke the ESB function (or any other function to test)
    int status = process_esb_request(str);
    
    // Assert the expected results
    munit_assert_true(status == 0);
    return MUNIT_OK;
}

/* Define the setup and the test for test2 */
static void *
test2_parse_bmd_xml_setup(const MunitParameter params[], void *user_data)
{
    char cwd[100];
    getcwd(cwd,sizeof(cwd));
    char path[100];
    sprintf(path,"%s/Testing/%s",cwd,"bmd.xml");
    
    return strdup(path);
 }


static void
test2_parse_bmd_xml_tear_down(void *fixture)
{
    free(fixture);
}

static MunitResult
test2_parse_bmd_xml(const MunitParameter params[], void *fixture)
{
    char *str = (char *)fixture;
    bmd *bmd;
    bmd=parse_bmd_xml(str);
    munit_assert_string_equal(bmd->envelop.message_id,"A9ECAEF2-107A-4452-9553-043B6D25386E");
    munit_assert_string_equal(bmd->envelop.sender_id,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
    munit_assert_string_equal(bmd->envelop.destination_id,"6393F82F-4687-433D-AA23-1966330381FE");
    munit_assert_string_equal(bmd->envelop.message_type,"CreditReport");
    munit_assert_string_equal(bmd->envelop.signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
    munit_assert_string_equal(bmd->envelop.reference_id,"INV-PROFILE-889712");
    munit_assert_string_equal(bmd->envelop.received_on,"2020-08-12T05:18:00+0000");
    return MUNIT_OK;
    munit_assert_string_equal(str, "TEST-2");
    return MUNIT_OK;
}

//test setup for paylaod.json file

static void * test_filesize_setup(const MunitParameter params[],void *user_data)
{
	char file[] ="Paylaod.json";
	int *p=malloc(sizeof(int *));
	*p=get_filesize(file);
	return p;
}

//teardown

static void test_filesize_tear_down(void *fixture)
{
	free(fixture);
}

static MunitResult
test_filesize(const MunitParameter params[],void *fixture)
{
	int *filesize=(int *)fixture;
	munit_assert_int(*filesize,<,5000000);
	return MUNIT_OK;
}

//test setup function for json content 

static void *Json_filecontents_setup(const MunitParameter params[], void *user_data)
{
	char *file_created=xmltojson("001-01-1234");
	char *json_data=get_filecontents(file_created);
	return strdup(json_data);
}


//teardown
static void Json_filecontents_tear_down(void *fixture)
{
	free(fixture);
}

static MunitResult test_Json_filecontents (const MunitParameter params[],void *fixture)
{
	char *json_data=(char *)fixture;
	char *test_data=get_filecontents("Paylaod.json");
	
	munit_assert_string_equal(json_data,test_data);
	
	return MUNIT_OK;
}

//test function for HTTP transport service
static MunitResult test_HTTP_transport_service(const MunitParameter params[],void *fixture)
{
	int status=Apply_transport_service("https://ifsc.razorpay.com/HDFC0CAGSBK", "HTTP");
	munit_assert_int(status,==,1);
	return MUNIT_OK;
}
//test fucntion for email transport servicde

static MunitResult test_email_transport_service(const MunitParameter params[], void *fixture)
{
	int status=Apply_transport_service("testmailv1@gmail.com","email");
	munit_assert_int(status,==,1);
	return MUNIT_OK;
}

//test function for no transport service

static MunitResult test_no_transport_service(const MunitParameter params[],void *fixture)
{
	int status=Apply_tranport_service("URL","service");
	munit_assert_int(status,==,0);
	return MUNIT_OK;
}

//test function for http json transform

static MunitResult test_HTTP_Json_transform(const MunitParameter params[],void *fixture)
{
	char type[]="Json_transform";
	int route_id=10;
	char *transport_key;
	char *transport_value="HTTP";
	char *SENDER;
	int transport_status=check_transform(type,route_id,transport_key,transport_value,SENDER);
	munit_assert_int(transport_status,==,1);
	return MUNIT_OK;
}

//test function for email json transform

static MunitResult test_email_Json_transform(const MunitParameter params[], void *fixture)
{
	char type[]="Json_transform";
	int route_id=2;
	char *transport_key;
	char *transport_value="email";
	char *SENDER;
	int  transform_status=check_transform(type,route_id,transport_key,transport_value,SENDER);
	munit_assert_int(transform_status,==,1);
	return MUNIT_OK;
}
static MunitResult test_no_transform(const MunitParameter params[], void * fixture)
{
	char type[]="";
	int route_id=1;
	char* transport_key;
	char *transport_value="";
	char* SENDER;
	int transform_status=check_transform(type,route_id,transport_key,transport_value,SENDER);
	munit_assert_int(transform_status,==,0);
	return MUNIT_OK;
}
//test function for send http request

static MunitResult test_HTTP_request(const MunitParameter params[],void * fixture)
{
	char *URL="https://ifsc.razorpay.com/HDFC0CAGSBK";
	int HTTP_status=send_http_request(URL);
	munit_assert_int(HTTP_status,==,1);
	return MUNIT_OK;
}

//test function for send emaol

static MunitResult test_send_email(const MunitParameter params[], void *fixture)
{
	int mail_status=send_mail("testmailv1@gmail.com","Payload.Json");
	munit_assert_int(mail_status,==,0);
	return MUNIT_OK;
}

//test function for active route
static MunitResult test_select_active_route(const MunitParameter params[], void *fixture)
{
	int x =select_active_route("756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA","6393F82F-4687-433D-AA23-1966330381FE","CreditReport");
	munit_assert_int(x,==,1);
	return MUNIT_OK;
}

//test function for transport config present for route_id

static MunitResult test_select_transport_config(const MunitParameter params[],void *fixture)
{
	int x=select_transport_config(1)
	munit_assert_int(x,==,1);
	return MUNIT_OK;
}

//test fucntion for transport config not present for a route_id

static MunitResult test_select_transport_config_invalid(const MunitParameter params[],void *fixture)
{
	int x=select_transport_config(0);
	munit_assert_int(x,==,-1);
	return MUNIT_OK;
	
}

//test function for transform config for route_id

static MunitResult test_select_transform_config(const MunitParameter params[], void *fixture)
{	
	int x=select_transform_config(2);
	munit_assert_int(x,==,1);
	return MUNIT_OK;
}

//test function for transform config for no route_id
static MunitResult test_select_transform_config_invalid(MunitParameter params[], void *fixture)
{
	int x=select_transform_config(999);
	munit_assert_int(x,==,-1);
	return MUNIT_OK;
}

// test function for an id with status = available

static MunitResult test_check_new_request(const MunitParameter params[], void * fixture)
{
	int x=check_new_request(1234);
	munit_assert_int(x,==,1);
	return MUNIT_OK;
}

// test function for an id with status not available

static MunitResult test_check_new_request_invalid(const MunitParameter params[], void * fixture)
{
	int x=check_new_request(1);
	munit_assert_int(x,==,-1);
	return MUNIT_OK;
}

// test function for getting route_id
static MunitResult test_get_route_id(const MunitParameter params[], void *fixture)
{
	int x =get_route_id("756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA","6393F82F-4687-433D-AA23-1966330381FE","CreditReport");
	munit_assert_int(x,==,1);
	return MUNIT_OK;
}

//test function to get transform key

static MunitResult test_get_transform_key(const MunitParameter params[], void * fixture)
{
	char transform_key[50];
	get_transform_key(1,transform_key);
	munit_assert_string_equal(transform_key,"Json_transform");
	return MUNIT_OK;
}

//test 1 for above function
static MunitResult test_get_transport_key_T1(const MunitParameter params[], void *fixture)
{
	char Payload_value[]="IDIB000V086";
	int route_id=1;
	char transport_key[50];
	char url[]="https://ifsc.razorpay.com/IDIB000V086";
	add_payload(Payload_value,route_id,transport_key);
	
	munit_assert_string_equal(transport_key,url);
	return MUNIT_OK;
}

//test 2

static MunitResult test_get_transport_key_T2(const MunitParameter params[], void *fixture)
{
	char transport_key[70];
	char type[]="Json_transform";
	int route_id=2;
	char *transport_value="email";
	char *SENDER;
	
	int check=check_transform(type,route_id,transport_key,transport_value,SENDER);
	munit_assert_string_equal(transport_key,"testmailv1@gmail.com");
	return MUNIT_OK;
}
//test 3
static MunitResult test_get_transport_key_T3(const MunitParameter params[], void *fixture)
{
	char transport_key[70];
	int route_id=2;
	get_emailId(route_id,transport_key);
	
	munit_assert_string_equal(transport_key,"testmailv1@gmail.com");
	return MUNIT_OK;
}

//test 1 for get_transform_value
static MunitResult test_get_transport_value_T1(const MunitParameter params[], void *fixture)
{
	char transport_value[50];
	get_transport_value(1,transport_value);
	munit_assert_string_equal(transport_value,"HTTP");
	return MUNIT_OK;
}

//test 2 
static MunitResult test_get_transport_value_T2(const MunitParameter params[], void *fixture)
{
	char transport_value[50];
	get_transport_value(2,transport_value);
	
	munit_assert_string_equal(transport_value,"email");
	return MUNIT_OK;
}


	/* Put all unit tests here. */
MunitTest esb_tests[] = {
    {
    	"/test_bmd_parse_xml",
    	test_parse_bmd_xml,
    	test_parse_bmd_xml_setup,
    	test_parse_bmd_xml_tear_down,
    	MUNIT_TEST_OPTION_NONE,
    	NULL
    },
    
    {
     	"/test2_bmd_parse_xml",
     	test2_parse_bmd_xml,
     	test2_parse_bmd_xml_setup,
     	test2_parse_bmd_xml_tear_down,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/test_json_filesize",
     	test_filesize,
     	test_filesize_setup,
     	test_filesize_tear_down,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/filecontents_test",
     	test_Json_filecontents,
     	Json_filecontents_setup,
     	Json_filecontents_tear_down,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/http transport_test",
     	test_HTTP_transport_service,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/email_transport_test",
     	test_email_transport_service,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/no_transport_test",
     	test_no_transport_service,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/HTTP_Json_transform_test",
     	test_HTTP_Json_transform,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/email_Json_transform_test",
     	test_email_Json_transform,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/no_transform_test",
     	test_no_transform,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/http request_test",
     	test_HTTP_request,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/send_email_test",
     	test_send_email,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     
     	"/select_active_route_test",
     	test_select_active_route,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/select_transport_config",
     	test_select_transport_config,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/select_transport_config_invalid_test",
     	test_select_transport_config_invalid,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/select_tranform_config",
     	test_select_transform_config,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/select_transform_config_invalid",
     	test_select_transform_config_invalid,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/test_check_new_request",
	test_check_new_request,
	NULL,
	NULL,
	MUNIT_TEST_OPTION_NONE,
	NULL
     },
     
     {
     	"/test_check_new_request_invalid",
     	test_check_new_request_invalid,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/test_get_route_id",
     	test_get_route_id,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/test_get_transform_key",
     	test_get_transform_key,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/get transport_key t1",
     	test_get_transport_key_T1,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/get_transport_key_t2",
     	test_get_transport_key_T2,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/get_transport_key_t3",
     	test_get_transport_key_T3,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/tst_get_transport_value_t1",
     	test_get_transport_value_T1,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {
     	"/test_get_transport_value_t2",
     	test_get_transport_value_T2,
     	NULL,
     	NULL,
     	MUNIT_TEST_OPTION_NONE,
     	NULL
     },
     
     {NULL,NULL,NULL,NULL,MUNIT_TEST_OPTION_NONE,NULL}};
     
     
     	
     	
/* Arrange the test cases into a test suite. */
static const MunitSuite suite = {
  "/test_suite_esb", /* name */
  esb_tests, /* tests */
  NULL, /* suites */
  1, /* iterations */
  MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */
int main (int argc, const char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
     
     
