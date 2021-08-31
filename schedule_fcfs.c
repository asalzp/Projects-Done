/** <fcfs.c>
*Submitted by: Seyedeh Asal Zarepakziabari
*Student #: 201920840
*
*This code implements the scheduling algorthm for fcfs. first we create a list and add the tasks to it in the add()
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
int num = 0;

//counter variable
int i = 0;

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
    float waiting_time = 0;
    float response_time = 0;
    int burst = 0;

    int count = 0;

    while (count < i)
    {
        
        num = num + 1;

        //run the task using the run function from CPU.h
        run(&tasks_list[count], tasks_list[count].burst);

        //calculate the turnaround, response and waiting time using the algorithm rules
        burst = burst + tasks_list[count].burst;   
        turnaround_time = turnaround_time + burst; 

        response_time = response_time + burst;

        count++;
    }
    
    waiting_time = turnaround_time - burst;

    printf("Average turnaround time: %f time units \n", turnaround_time / num);
    printf("Average wait time: %f time units\n", waiting_time / num);
    printf("Average response time: %f time units \n", response_time / num);
}
