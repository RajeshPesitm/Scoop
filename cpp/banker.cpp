#include <stdio.h>
int allocation[5][5], Max[5][5], Need[5][5], available[5] = { 0, 0, 0, 0, 0 },Maxres[5];
int Numproc,NumresType,i,j;
int request[5];
int Safteycheck();
int main()
{
    setbuf(stdout,NULL);
	printf("\nEnter the number of processes: ");
    scanf("%d", &Numproc);
    printf("\nEnter the number of resource type: ");
    scanf("%d", &NumresType);
    //read number of resources of each type
    for(i=0;i<NumresType;i++)
    {
        printf("\nenter the total number of resources of type %d ", i);
        scanf("%d",&Maxres[i]);
    }
    //read Max matrix
   printf("\nEnter %d * %d matrix: Max", Numproc, NumresType);
   for (i = 0; i < Numproc; i++)
   {
	   for(j = 0; j < NumresType; j++)
	   {
		   scanf("%d", &Max[i][j]);
	   }
   }
   //read Allocation matrix
   printf("\nEnter %d * %d matrix: Allocation", Numproc, NumresType);
   for (i = 0; i < Numproc; i++)
   {
	   for(j = 0; j < NumresType; j++)
	   {
		   scanf("%d", &allocation[i][j]);
	   }
   }
   //Compute Available resources

	for (j = 0; j < NumresType; j++) {
		for (i = 0; i < Numproc; i++) {
			available[j] = available[j] + allocation[i][j];
		}
		available[j] = Maxres[j]-available[j];
	}

  //compute need matrix
  for (i = 0; i < Numproc; i++)
     {
  	   for(j = 0; j < NumresType; j++)
  	   {
  		   Need[i][j] = Max[i][j]-allocation[i][j];
  	   }
     }

	while(1){
			if(Safteycheck())		//call safety algorithm
					printf("\n The system is in safe state");
				else
					{printf("\n this request can't be granted"); break;}
			//read request from process j
			printf("\n enter the requesting process");
			scanf("%d",&j);
			printf("\n enter the request");
			for(i = 0;i<NumresType; i++)
				scanf("%d",&request[i]);
			//Resource request algorithm
			for(i = 0;i<NumresType; i++){
				available[i] = available[i] - request[i];	//available = available - request
				Need[j][i] = Need[j][i] - request[i];		//need = need - request
				allocation[j][i] = allocation[j][i] + request[i];	//allocation = allocation + request
			}
	}
}

int Safteycheck()
{
	int CheckAvailable[5],finish[5],flag;
	//Step 1: CheckAvailable = Available
	//		  finish[i] = false for i = 0,1,.....Numproc
	for (i = 0; i < NumresType; i++) {
		CheckAvailable[i] = available[i];
	}

	for (i = 0; i < Numproc; i++) {
		finish[i] = 0;
	}
	//step 2: Find an index i such that
	//		  finish[i] = false
	//		  need[i][j] <= checkAvailable[j] for j = 0,1,......Numproc
	for (i = 0; i < Numproc; i++) { //this is the loop to find such an index i
		flag = 1;
		for (j = 0; j < NumresType; j++)
			if (Need[i][j] > CheckAvailable[j]) {
				flag = 0;
				break;
			}
		if (finish[i] == 0 && flag == 1) {//step 3:
			for (j = 0; j < NumresType; j++) {
				CheckAvailable[j] = CheckAvailable[j] + allocation[i][j];// checkAvailable = checkAvailable + Allocation
			}
			finish[i] = 1;	//finish[i] = true
			i = -1;// Goto step 2	//start again, i = -1 because i++ executes at the end of loop
		}
	}
	for (i = 0; i < Numproc; i++) { //step 4: finish[i] == false for atleast one process then system is not in safe state
		if (finish[i] == 0)
			return 0;
	}
	return 1;
}

