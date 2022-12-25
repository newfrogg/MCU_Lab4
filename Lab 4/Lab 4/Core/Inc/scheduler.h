
#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

#define SCH_MAX_TASKS 40

extern int TIME_CYCLE;
typedef struct {
	void (*pTask)(void);
//	Time for first operation
	uint32_t Delay;
//	Time for the next operations
	uint32_t Period;
//	Number of time to perform the operation
	uint8_t RunMe;
//	Location of task
	uint32_t TaskID;
}sTasks;

void SCH_Init(void);
uint32_t SCH_Add_Task (void (*pFunction) () , uint32_t Delay, uint32_t Period);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);


#endif /* INC_SCHEDULER_H_ */
