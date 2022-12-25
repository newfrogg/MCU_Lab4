/*
 * button.c
 *
 *  Created on: Dec 25, 2022
 *      Author: Beelzebufo
 */
#include "button.h"
//Initialize array for button signal processing
int KeyReg0[NUM_OF_BUTTONS] = {
NORMAL_STATE };
int KeyReg1[NUM_OF_BUTTONS] = {
NORMAL_STATE };
int KeyReg2[NUM_OF_BUTTONS] = {
NORMAL_STATE };
int KeyReg3[NUM_OF_BUTTONS] = {
NORMAL_STATE };
//Initialize press button/ long press button flag
int button_flag[NUM_OF_BUTTONS] = { 0 };
int buttonlong_flag[NUM_OF_BUTTONS] = { 0 };
//Initialize period variable for 2 events triggered of buttons
int TimeOutForKeyPressed[NUM_OF_BUTTONS] = { 0 };

int isButtonPressed(int index) {
	if (button_flag[index] == 1) {
		button_flag[index] = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int index) {
	button_flag[index] = 1;
}

void getKeyInput() {
	for (int i = 0; i < NUM_OF_BUTTONS; i++) {
//		Bouncing processing
		KeyReg0[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg2[i];
//		Read signal from button
		if (i == 0)
			KeyReg2[i] = HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin);
//		Signal processing
		if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])) {
			if (KeyReg3[i] != KeyReg2[i]) {
				KeyReg3[i] = KeyReg2[i];
				if (KeyReg2[i] == PRESSED_STATE) {
//					Set timer flag to 1
					subKeyProcess(i);
					if (buttonlong_flag[i] == 0) {
//						Set period for long key press event 2s
						TimeOutForKeyPressed[i] = 2000 / TIME_CYCLE;
					} else {
//						Set period for normal key  event 1s
						TimeOutForKeyPressed[i] = 1000 / TIME_CYCLE;
					}
				}
			} else {
				TimeOutForKeyPressed[i]--;
//				TimeOutForKeyPress > 3 then button flag = 1 else 0
				if (TimeOutForKeyPressed[i] == 0) {
					KeyReg3[i] = NORMAL_STATE;
					buttonlong_flag[i] = 1;
				}
			}
		} else {
			buttonlong_flag[i] = 0;
		}

	}
}

