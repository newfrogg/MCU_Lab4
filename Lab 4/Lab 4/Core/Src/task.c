/*
 * task.c
 */
#include "task.h"

void ledToggle_0_5s(void){
	HAL_GPIO_TogglePin(L1_GPIO_Port, L1_Pin);
}
void ledToggle_1_s(void){
	HAL_GPIO_TogglePin(L2_GPIO_Port, L2_Pin);
}
void ledToggle_1_5s(void){
	HAL_GPIO_TogglePin(L3_GPIO_Port, L3_Pin);
}
void ledToggle_2s(void){
	HAL_GPIO_TogglePin(L4_GPIO_Port, L4_Pin);
}
void ledToggle_2_5s(void){
	HAL_GPIO_TogglePin(L5_GPIO_Port, L5_Pin);
}

void ledToggle_oneshot(void){
	HAL_GPIO_TogglePin(LB1_GPIO_Port, LB1_Pin);
}

void ledToggle_longpressed(void){
	if (isButtonPressed(0))
		HAL_GPIO_TogglePin(LC1_GPIO_Port, LC1_Pin);
}
