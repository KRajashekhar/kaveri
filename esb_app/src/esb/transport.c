#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Apply transport service */
int Apply_transport_service(char URL[], char transport_service[]) {
    int status = 1;
    if (!strcmp(transport_service, "HTTP")) {
        printf("\nHTTP service applied\n");
        send_http_request(URL);
        return status;
    } else if (!strcmp(transport_service, "email")) {
        char filename[100];
        printf("Enter file to read:\t");
        scanf("%s", & filename);
        printf("\nemail service applied\n");
        int mail_status = send_mail(URL, filename);
        if (mail_status == 0) {
            printf("Mail sent\n");
            return status;
        } else {
            printf("Failed to send the Mail\n");
            status = 0;
        }
    } else {
        status = 0;
        printf("\nNo service found\n");
    }
    return status;

}
