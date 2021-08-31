/** <rr.c>
*Submitted by: Seyedeh Asal Zarepakziabari
*Student #: 201920840
*
*This code implements the scheduling algorthm for rr. first we create a list like before and add the tasks to it in the add()
function; then we use the schedule function to implement the algorithm and calculate the turnaround, response and 
waiting time.
**/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

//define a way find the minimum number between two numbers
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

//create a list of tasks
Task tasks_list[100];

//variable to hold the numbers of tasks
int i = 0;

//counter variable
int num = 0;

void add(char *name, int priority, int burst)
{

	//add the name, burst time and priority to the tasks list's respective slots
	tasks_list[i].burst = burst;
	tasks_list[i].name = name;
	tasks_list[i].priority = priority;
	i++;
}

void schedule()
{

	//initialize numbers used to calculate overall turnaround, waiting and response time
	float turnaround_time = 0;
	float response_time = 0;
	float waiting_time = 0;
	int burst = 0;

	//counter
	int finish = 0;

	//while the function isn't done yet
	while (finish <= 0)
	{

		//traverse the list
		for (int count = 0; count < i; count++)
		{
			//if the task has been processing for more than 10 time units set the finish flag to 1 and stop scheduling
			if (tasks_list[count].done * 10 >= tasks_list[count].burst)
			{

				finish = 1;
				continue;
			}

			//if not, run the task for the minimum of 10 time units or the time units left for the process to be done executing
			finish = 0;

			run(&tasks_list[count], MIN(10, tasks_list[count].burst - (tasks_list[count].done * 10)));

			//mark the task as done
			tasks_list[count].done++;

			num = num + 1;

			//calculate the turnaround, wait and response time with the algorithm rules
			burst = burst + MIN(10, tasks_list[count].burst - (tasks_list[count].done * 10));
			turnaround_time = turnaround_time + burst;

			response_time = response_time + burst;
		}
	}
	waiting_time = turnaround_time - burst;

	printf("Average turnaround time: %f time units \n", turnaround_time / num);
	printf("Average wait time: %f time units\n", waiting_time / num);
	printf("Average response time: %f time units \n", response_time / num);
	;
}

