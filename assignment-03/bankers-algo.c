#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Brian Barr
 * Professor Freedman
 * comp 322
 *
 * */

/* Declare dynamic arrays and global variables*/
int m, // # of resources
	n; // # of processes

int *resource_vector, // m element arrays
	*available_vector;

int **max_claims, // nxm element arrays (multidimensional)
	**allocations,
	**need;

/***********************************************************/

void PrintMatrices()
{
	printf("\t Max Claims\t \t Current \t \t Potential \n");
	// print resources
	// 3 is for the number of matrices
	printf("\t");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("r[%d] ", j);
		}
		printf("\t \t");
	}
	printf("\n");
	printf("-------------------------------------------------------------------------\n");

	for (int i = 0; i < n; i++)
	{
		// print the process id
		printf("p[%d]: ", i);
		printf("\t");
		for (int j = 0; j < m; j++)
		{
			printf(" %d   ", max_claims[i][j]);
		}
		printf("\t \t");
		for (int j = 0; j < m; j++)
		{
			printf(" %d   ", allocations[i][j]);
		}
		printf("\t \t");
		for (int j = 0; j < m; j++)
		{
			printf(" %d   ", need[i][j]);
		}
		printf("\n");
	}

	printf("\n\n");
	/* declare local variables */
	/* for loop: print each resource index */
	/* for each process: */
	/* for each resource: */
	/* print maximum number of units each process may request, is allocated, and needs from each resource */
	return;
}

int **Allocate2DArray(int n, int m)
{
	int **temp = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
	{
		temp[i] = (int *)malloc(m * sizeof(int));
	}

	return temp;
}

void PrintResourcesVector()
{
	/* declare local variables */
	/* for loop: print each resource index */
	printf("\tunits\tavailable \n");
	printf("----------------------------\n");
	for (int i = 0; i < m; i++)
	{
		printf("r%d\t%d\t%d \n", i, resource_vector[i], available_vector[i]);
	}

	/* for loop: print number of total units and available units of each resource index */
	return;
}

void CalculateAvailable()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			available_vector[j] -= allocations[i][j];
		}
	}
}

int ResourcesAreAvailable(int row)
{
	for (int j = 0; j < m; j++)
	{
		if (need[row][j] > available_vector[j])
		{
			/* code */
			return 0;
		}
	}

	return 1;
}
/***************************************************************/

void PrintMainPrompt()
{
	printf("  Bankers Algorithm\n");
	printf("----------------------\n");
	printf("1) Enter Parameters\n");
	printf("2) Determine Safe Sequence \n");
	printf("3) Exit Program\n");
	printf("4) Quick populate (random values)\n");
}

/****************************************************************/
void EnterParams()
{
	/* declare local variables */
	/* prompt for number of processes and number of resources */
	printf("enter number of processes: ");
	scanf("%d", &n);
	printf("enter the number of resources: ");
	scanf("%d", &m);

	/* allocate memory for vectors and arrays: resource, available, max_claim, allocated, need */
	resource_vector = (int *)malloc(sizeof(int) * m);
	available_vector = (int *)malloc(sizeof(int) * m);

	max_claims = Allocate2DArray(n, m);
	allocations = Allocate2DArray(n, m);
	need = Allocate2DArray(n, m);

	/* for each resource, prompt for number of units, set resource and available vectors indices*/
	printf("enter number of resources for r0 to r%d: ", (m - 1));
	for (int i = 0; i < m; i++)
	{
		scanf("%d", (resource_vector + i));
	}

	// instantiate the available vector with the values within resource vector
	//  this will help when calculating available later
	for (int i = 0; i < m; i++)
	{
		available_vector[i] = resource_vector[i];
	}

	/* for each process, for each resource, prompt for maximum number of units requested by process, update max_claim and need arrays */
	for (int i = 0; i < n; i++)
	{
		printf("enter the maximum number of units process p%d will request for each resource (r0 to r%d) ", i, (m - 1));
		for (int j = 0; j < m; j++)
		{
			scanf("%d", &max_claims[i][j]);
		}
	}
	/* for each process, for each resource, prompt for number of resource units allocated to process */
	for (int i = 0; i < n; i++)
	{
		printf("enter the number of units of each resource (r0 to r%d) allocated to process p%d: ", m, i);
		for (int j = 0; j < m; j++)
		{
			scanf("%d", &allocations[i][j]);
		}
	}

	CalculateAvailable();

	// calcuate the potential matrix
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			need[i][j] = max_claims[i][j] - allocations[i][j];
		}
	}

	/* print resource vector, available vector, max_claim array, allocated array, need array */
	PrintResourcesVector();
	PrintMatrices();
	return;
}

int EveryoneIsScheduled(int *v)
{
	for (int i = 0; i < n; i++)
	{
		if (v[i] == 0)
		{
			//printf("safely sequenced returned 0 \n");
			return 0;
		}
	}
	//printf("safely sequenced returned 1 \n");
	return 1;
}

/********************************************************************/
void DetermineSafeSequence()
{

	/* declare local variables, including vector to indicate if process is safely sequenced and "num_sequenced" count*/
	int *safely_sequenced = (int *)malloc(sizeof(int) * n);
	int num_sequenced = 0;

	// this is somewhat hacky but its a means to prevent an infinte loop 
	int deadlock_safety = 0;  
	int deadlock_safety_max = 10; 

	// initialize each element as false
	for (int i = 0; i < n; i++)
	{
		safely_sequenced[i] = 0;
	}
	// printf("result of !EveryoneIsScheduled: %d\n",!EveryoneIsScheduled(safelySequenced));
	/* while not all processed are sequenced */
	while (!EveryoneIsScheduled(safely_sequenced))
	{
		// the deadlock_saftey is meant to prevent infinite looping 
		if (deadlock_safety > deadlock_safety_max)
		{
			printf("deadlock detected. cannot be safely sequenced: \n\n"); 
			break;
		}
		
		/* for each process */
		for (int i = 0; i < n; i++)
		{
			/* if process has not been safely sequenced yet ? */
			if (safely_sequenced[i] == 0)
			{

				// comparing our ith row of the potential matrix
				//  to the available vector

				// print the damn thing, then worry about the logic
				printf("checking < ");
				/* for each resource */
				for (int j = 0; j < m; j++)
				{
					/* check for safe sequencing by comparing process' need vector to available vector */
					printf("%d ", need[i][j]);
				}
				printf("> <= < ");
				for (int j = 0; j < m; j++)
				{
					printf("%d ", available_vector[j]);
				}
				printf(">");
				// if what's needed is more than what's available
				// go to the next iteration in the loop
				if (!ResourcesAreAvailable(i))
				{
					printf(" :p[%d] not sequenced \n", i);
					continue;
				}

				/* if each resource is available */
				/* print message that process had been safely sequenced */
				printf(" :p[%d] successfully sequenced \n", i);
				/* update number of available units of resource */
				/* for each resource */
				for (int j = 0; j < n; j++)
				{
					// update the available vector
					available_vector[j] += allocations[i][j];
					/*free all resources allocated to process */
					allocations[i][j] = 0;
				}

				/* increment number of sequenced processes */
				safely_sequenced[i] = 1;
				num_sequenced++;
			}
		}
		deadlock_safety++;
		printf("\n"); // marks new line:: Checking: < 6 0 0 > <= < 7 5 5 > :pi safely sequenced
	} // end safely sequenced while loop
	if (num_sequenced == n)
	{
	printf("everyone was served hurray! \n");
	}
	
}

void QuickPopulate()
{
	n = 5;
	m = 3;
	time_t t;
	srand((unsigned)time(&t));

	resource_vector = (int *)malloc(sizeof(int) * m);
	available_vector = (int *)malloc(sizeof(int) * m);
	max_claims = Allocate2DArray(n, m);
	allocations = Allocate2DArray(n, m);
	need = Allocate2DArray(n, m);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			max_claims[i][j] = (rand() % 7) + 1;
			while (allocations[i][j] == 0 || allocations[i][j] > max_claims[i][j])
			{
				/* code */
				allocations[i][j] = (rand() % 3) + 1;
			}

			need[i][j] = max_claims[i][j] - allocations[i][j];
		}
	}

	// populate the resource vector with some values
	for (int i = 0; i < m; i++)
	{
		available_vector[i] = resource_vector[i] = (rand() % 15) + 5;
	}

	// calculate what is available
	CalculateAvailable();

	PrintResourcesVector();
	PrintMatrices();
}

/********************************************************************/
void TerminateProgram()
{
	/* check if vectors/array are not NULL--if so, free each vector/array */
	printf("goodbye!\n");
	exit(EXIT_SUCCESS);
	return;
}

/***************************************************************/
int main()
{

	/* Declare local variables */
	int selector;
	/* Until the user quits, print the menu, prompt for the menu choice, call the appropriate procedure */
	while (1)
	{
		/* code */
		PrintMainPrompt();
		printf("enter selection: \n");
		scanf("%d", &selector);

		switch (selector)
		{
		case 1:
			/* code */
			EnterParams();
			break;
		case 2:
			DetermineSafeSequence();
			break;
		case 3:
			TerminateProgram();
			break;
		case 4:
			QuickPopulate();
		default:
			printf("input not understood \n\n");
			break;
		}
	}

	return 1;
}
