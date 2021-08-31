/** <priority_rr.c>
*Submitted by: Seyedeh Asal Zarepakziabari
*Student #: 201920840
*
*This code implements the scheduling algorthm for priority_rr. first we create a list like before and add the tasks to it in the add()
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


//define a way find the minimum and maximum number between two numbers
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))



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



int pick_priority()
{
	//reference variable
	int top = -1;

	//traverse the list
	for (int count = 0; count < i; count++)
	{
		//if a task has beend processing for more thatn 10 time units then continue
		if (tasks_list[count].done * 10 >= tasks_list[count].burst)
		{

			continue;
		}

		//if not, set the reference variable to the maximum number between the variable and the priority of the task
		top = MAX(top, tasks_list[count].priority);
	}

	return top;
}

void schedule()
{

	//initialize numbers used to calculate overall turnaround, waiting and response time
	float turnaround_time = 0;
	float response_time = 0;
	float waiting_time = 0;
	int burst = 0;

	//call the pick_priority() function to initialize the returned top in the priority variable
	int priority = pick_priority();

	//while function is running
	while (priority > 0)
	{

		//traverse the list
		for (int count = 0; count < i; count++)
		{
			//if the chosen task's priority is equal to the initialized one
			if (tasks_list[count].priority == priority)
			{

				//run the task for the minimum of 10 time units or the time units left for the process to be done executing
				run(&tasks_list[count], MIN(10, tasks_list[count].burst - (tasks_list[count].done * 10)));

				//markthe task as done
				tasks_list[count].done++;
				num = num + 1;

				//calculate the turnaround, wait and response time with the algorithm rules
				burst = burst + MIN(10, tasks_list[count].burst - (tasks_list[count].done * 10));
				turnaround_time = turnaround_time + burst; //5 (5+10+5)20  50      (5 + 5+10 + 5+10+15)

				response_time = response_time + burst;
			}
		}

		//set priority to the function call again
		priority = pick_priority();
	}
	waiting_time = turnaround_time - burst;

	printf("Average turnaround time: %f time units \n", turnaround_time / num);
    printf("Average wait time: %f time units\n", waiting_time / num);
    printf("Average response time: %f time units \n", response_time / num);;

}