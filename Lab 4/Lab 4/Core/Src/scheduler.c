/*
 * scheduler.c
 */

#include "scheduler.h"
#include "main.h"
int TIME_CYCLE;

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;

//Delete task
uint8_t SCH_Delete_Task(uint32_t taskID) {
	if (current_index_task == 0 || taskID < 0 || taskID >= SCH_MAX_TASKS)
		return -1;

	for (int i = taskID; i < SCH_MAX_TASKS - 1; i++) {
//		Move task from index i + 1 to i
		SCH_tasks_G[i].pTask = SCH_tasks_G[i + 1].pTask;
		SCH_tasks_G[i].Delay = SCH_tasks_G[i + 1].Delay;
		SCH_tasks_G[i].Period = SCH_tasks_G[i + 1].Period;
		SCH_tasks_G[i].RunMe = SCH_tasks_G[i + 1].RunMe;
	}
//	Reset SCH_tasks_G[SCH_MAX_TASKS-1]
	SCH_tasks_G[SCH_MAX_TASKS - 1].pTask = 0x0000;
	SCH_tasks_G[SCH_MAX_TASKS - 1].Delay = 0;
	SCH_tasks_G[SCH_MAX_TASKS - 1].Period = 0;
	SCH_tasks_G[SCH_MAX_TASKS - 1].RunMe = 0;

	current_index_task--;
	return taskID;
}

//Initialize SCH_task
void SCH_Init(void) {
	while (current_index_task > 0)
		SCH_Delete_Task(0);
}

//Add task to the end of SCH_task_G with period as software timer counter
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t Delay, uint32_t Period) {
	if (current_index_task < SCH_MAX_TASKS) {
//		initialize new task
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = Delay / TIME_CYCLE;
		SCH_tasks_G[current_index_task].Period = Period / TIME_CYCLE;
		SCH_tasks_G[current_index_task].RunMe = 0;
//		add task to the end
		SCH_tasks_G[current_index_task].TaskID = current_index_task++;

		return SCH_tasks_G[current_index_task].TaskID;
	}
	return -1;
}

/*
 * Update timer for each tasks
 * works as runTimer()
 */
void SCH_Update(void) {
	for (int i = 0; i < current_index_task; i++) {
		if (SCH_tasks_G[i].Delay > 0)
//			decrease 1 tick
			SCH_tasks_G[i].Delay--;
		else {
//			First time trigger with time = Delay
//			For more loop, time => Period
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe++;
		}
	}
}
/*
 * Check runMe each task
 * someway like check flag of software timer
 */
void SCH_Dispatch_Tasks(void) {
	for (int i = 0; i < current_index_task; i++) {
		if (SCH_tasks_G[i].RunMe > 0) {
//			Reset runme flag
			SCH_tasks_G[i].RunMe--;
//			Run task
			(*SCH_tasks_G[i].pTask)();
//			Periodic tasks will automatically run again
//			If this is a "one shot" task, remove it from array
			if (SCH_tasks_G[i].Period == 0)
				SCH_Delete_Task(i--);
		}
	}
}

