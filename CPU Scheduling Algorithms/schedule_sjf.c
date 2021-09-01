/** <sjf.c>
*Submitted by: Seyedeh Asal Zarepakziabari
*Student #: 201920840
*
*This code implements the scheduling algorthm for sjf. first we create a list like before and add the tasks to it in the add()
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

//create a method to pick the next task to be processed based on their burst time
Task *pickNext()
{

	//reference variable
	int n = 10000;

	//create an instance of Task struct
	Task *selected_task = &tasks_list[0];

	//traverse the list
	for (int count = 0; count < i; count++)
	{

		//check if the task's burst time is less than our reference variable and if it is not done
		if (tasks_list[count].burst < n && tasks_list[count].done == 0)
		{

			//store the chosen task in the tsk variable above
			selected_task = &tasks_list[count];

			//set the reference number to the task chosen to compare the next ones with this
			n = selected_task->burst;
		}
	}
	return selected_task;
}

void schedule()
{

	//initialize numbers used to calculate overall turnaround, waiting and response time
	float turnaround_time = 0;
	float response_time = 0;
	float waiting_time = 0;
	int burst = 0;

	int count = 0;
	while (count < i)
	{
		

		//call pickNext() and store the returned task in a variable
		Task *task = pickNext();

		num = num + 1;

		//run the chosen task and set the done flag to 1 indicating that task has been done
		run(task, task->burst);
		task->done = 1;

		//calculate turnaround, reaponse and waiting time with the algorthims rules
		burst = burst + task->burst;
		turnaround_time = turnaround_time + burst; 
		response_time = response_time + burst;

		count++;
	}
	waiting_time = turnaround_time - burst;

	printf("Average turnaround time: %f time units \n", turnaround_time / num);
    printf("Average wait time: %f time units\n", waiting_time / num);
    printf("Average response time: %f time units \n", response_time / num);
}