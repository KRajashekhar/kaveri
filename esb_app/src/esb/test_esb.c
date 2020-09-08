#include "munit.h"
#include "esb.h"
#include<string.h>
#include<dirent.h>
#include<stdlib.h>
#include<stdio.h>
#include "parser.h"

/**
 * If the name of a test function is "test_abc" then you should
 * define the setup and teardown functions by the names:
 * test_abc_setup and test_abc_tear_down respectively.
 */
 
 /* gcc test_esb.c munit.c bmd_parser.c database.c esb.c  `mysql_config --cflags --libs` `xml2-config --cflags --libs` -o test_esb
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
    d = opendir("./Testing");
    char **s;
    s = malloc(100 * sizeof(char *));
    int i = 0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            char *file = strdup(dir->d_name);
            if(file[0]=='.')
              continue;
            char cwd[100];
            getcwd(cwd, sizeof(cwd));
            char path[100];
            sprintf(path, "%s/Testing/%s", cwd, file);
             
            s[i] = strdup(path);

            free(file);
            i++;
        }
        closedir(d);
    }

    return s;
}

static void
test_parse_bmd_xml_tear_down(void *fixture)
{
    /* Receives the pointer to the data if that that was created in
    test1_setup function. */
    free(fixture);
}

static MunitResult
test_parse_bmd_xml(const MunitParameter params[],void *fixture)
{
	char **str =(char **)fixture;
	int i=0;
	while(str[i]!=NULL)
	{
	bmd *bmd;
	bmd=parse_bmd_xml(str[i]);
	munit_assert_true(bmd!=NULL);
	free(bmd);
	i++;
	}
	return MUNIT_OK;
}

static void *
test_filesize_setup(const MunitParameter params[], void *user_data)
{
	char file[]"Payload.json";
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
test_filesize(cont MunitParameter params[], void *fixture)
 {
   int *filesize=(int *)fixture;
   munit_assert_int(filesize,<,500000);
   return MUNIT_OK;
 }
 
 static void *
 test2_parse_bmd_xml_setup(const MunitParameter params[], void *user_data)
 {
	 char cwd[100];
	 getcwd(cwd,sizeof(cwd));
	 char path[100];
	 sprintf(path,"%s/Testing%s",cwd,"bmd.xml");
	 return strdup(path);
 }
 
 static void
 test2_parse_bmd_xml_tear_down(void * fixture)
 {
 	free(fixture);
 }
 
 static MunitResult
 
 test2_parse_bmd_xml(const MunitParamter params[], void *fixture)
 {
 	char *str=(char *)fixture;
 	bmd *bmd;
 	bmd=parse_bmd_xml(str);
 	munit_asser_string_equal(bmd->bmd_envelop->MessageId,"A9ECAEF2-107A-4452-9553-043B6D25386E");
 	munit_asser_string_equal(bmd->bmd_envelpo->Sender,"756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA");
 	munit_assert_string_equal(bmd->bmd_envelop->Destination,"6393F82F-4687-433D-AA23-1966330381FE");
 	munit_assert_string_equal(bmd->bmd_envelop->MessageType,"CreditReport");
 	munit_assert_string_equal(bmd->bmd->envelop->Signature,"63f5f61f7a79301f715433f8f3689390d1f5da4f855169023300491c00b8113c");
 	munit_assert_string_equal(bmd->bmd_envelop->RefernceID,"INV-PROFILE-889712");
 	munit_assert_string_equal(bmd->bmd_envelop->CreationDateTime,"2020-08-12T05:18:00+0000");
 	return MUNIT_OK;
 }

/* Put all unit tests here. */
MunitTest esb_tests[] = {
    {
        "/test_parse_bmd_xml",   /* name */
        test1,  /* test function */
        test1_setup,    /* setup function for the test */
        test1_tear_down,    /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
        "/test_bmd_parse_xml",   /* name */
        test2,  /* test function */
        test2_setup,    /* setup function for the test */
        test2_tear_down,    /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    {
    "/test_json_filesize",
    test_filesize,
    test_filesize_setup,
    test_filesize_tear_down,
    MUNIT_TEST_OPTION_NONE,
    NULL
    },
    /* Mark the end of the array with an entry where the test
   * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

/* Arrange the test cases into a test suite. */
static const MunitSuite suite = {
  "/my-tests", /* name */
  esb_tests, /* tests */
  NULL, /* suites */
  1, /* iterations */
  MUNIT_SUITE_OPTION_NONE /* options */
};

/* Run the the test suite */
int main (int argc, const char* argv[]) {
  return munit_suite_main(&suite, NULL, argc, argv);
}
