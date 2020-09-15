#include<stdio.h>
#include<stdlib.h>


#include "db_access.h"


int main() {
    //insert_into_esb_request("A9ECAEF2-107A-4452-9553-043B6D25386E","6393F82F-4687-433D-AA23-1966330381FE","CreditReport","INV-PROFILE-889712","A9ECAEF2-107A-4452-9553-043B6D25386E","2020-08-02T05:18:00+0000", "bmd.xml","available","It is available" );
   int route_id = select_active_route("756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA","6393F82F-4687-433D-AA23-1966330381FE","CreditReport");
   printf("%d\n",route_id);
   int success = select_transport_config(route_id);
   printf("%d\n",success);
   success = select_transform_config(route_id);
   printf("%d\n",success);
    return 0;
} 
