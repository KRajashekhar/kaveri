#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int rear=-1;
int front=-1;
int count=0;

struct task_t{
	int id;
	char *sender;
	char *destination;
	char *message_type;
	int processing_attempts;
	char *status;
	
	};
 struct task_t t1[60];
 void enqueue(struct task_t t)
 {
 	if(front==-1)
 	{
 		front=0;
 	}
 	printf("Insert elements in queue \n");
 	//assigned 0
 	rear = rear++; 
	t1[rear].id=t.id;
	t1[rear].sender=t.sender;
	t1[rear].destination=t.destination;
	t1[rear].message_type=t.message_type;
	t1[rear].processing_attempts=1;
	t1[rear].status="Available";
	count++;
 }
 
 void dequeue()
 {
 	if(front ==-1 || front>rear)
 	{
 		printf("Currently no elemnets in queue\n");
 		front=-1;
 		rear=-1;
 	}
 	else 
 	{
 		printf("deleted id is %d\n",t1[front].id);
 		front=front+1;
 		count=count-1;
 	}
 }
 
 void display()
 {
 	int i;
 	if(front==-1)
 	{
 		printf("Currently no elemments\n");
 	}
 	else 
 	{
 		for(i=front;i<front+count;i++)
 		{
 			printf("id=%d \n",t1[i].id);
 			printf("sender =%s \n",t1[i].sender);
 			printf("destination =%s\n",t1[i].destination);
 			printf("message_type=%s\n", t1[i].message_type);
 			printf("processing_attempts =%d\n",t1[i].processing_attempts);
 			printf("status=%s\n",t1[i].status);
 		}
 	}
 }
 int request_process()
 {
 	int i=front;
 	if(front==-1)
 	{
 		printf("Currently no elements in queue");
 	}
 	else
 	{
 		while(i<=rear)
 		{
 			if(!(strcmp(t1[i].status,"Available")))
 			{
 				if(t1[i].processing_attempts<99)
 				{
 					t1[i].status="Taken";
 					t1[i].processing_attempts++;
 					
 				}
 				
 				else
 				{
 					t1[i].status="failed";
 				}
 			}
 			i++;
 		}
 	}
 }
 
 
 int main()
 {
 	struct task_t temp;
 	temp.id=1;
 	temp.sender="Vin";
 	temp.destination="raja";
 	temp.message_type="test";
 	
 	
 	enqueue(temp);
 	
 	temp.id=2;
 	temp.sender="raja2";
 	temp.destination="vin2";
 	temp.message_type="test2";
 	

 	enqueue(temp);
 	
 	 	
 	request_process();
 	dequeue();
 	display();
 	return 0;
 }
 	
