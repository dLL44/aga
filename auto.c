#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void successTone() {
    // Success: A short, high-pitched tone
    Beep(1000, 200);  // Frequency: 1000 Hz, Duration: 200 ms
    Beep(1200, 150);  // Frequency: 1200 Hz, Duration: 150 ms
}

void errorTone() {
    // Error: A lower-pitched, longer tone
    Beep(500, 500);   // Frequency: 500 Hz, Duration: 500 ms
}

void saveSettings(INT delay, BOOL rClick, BOOL hold) {
	FILE *file = fopen("settings.conf", "w");
	if (file == NULL) {
		printf("Err saving\n");
		errorTone();
		return;
	}
	fprintf(file, "DELAY=%d\n", delay);
	fprintf(file, "RCLICK=%d\n", rClick);
	fprintf(file, "HOLD=%d\n", hold);
	fclose(file);
	printf("settings saved\n");
	successTone();
	printf("delay is %d ms\n", delay);
	printf("right click is %s\n", rClick ? "on" : "off");
	printf("hold is %s\n", hold ? "on" : "off");
}

void loadSettings(INT *delay, BOOL *rClick, BOOL *hold) {
	FILE *file = fopen("settings.conf", "r");
	if (file == NULL) {
		printf("settings.conf doesnt exist, using default values\n");
		errorTone();
		return;
	}
	fscanf(file, "DELAY=%d\n", delay);
	fscanf(file, "RCLICK=%d\n", rClick);
	fscanf(file, "HOLD=%d\n", hold);
	fclose(file);
	printf("loaded settings.\n");
	successTone();
	printf("delay is %d ms\n", *delay);
	printf("right click is %s\n", *rClick ? "on" : "off");
	printf("hold is %s\n", *hold ? "on" : "off");
}

int main() {
	BOOL click = FALSE;
	BOOL rClick = FALSE;
	BOOL hold = FALSE;
	BOOL cmdMode = FALSE;
	INT DELAY = 100;

	printf("anga, another generic autoclicker.\n--- hotkeys ---\n F7        start\n F8        end\n F9        exit the autoclicker\n F10       command mode \n---------------\ncredits:\n made FULLY by dLL44.\n---------------\nlogs\n---------------\n");
	loadSettings(&DELAY, &rClick, &hold);
	while (TRUE) {
		if (GetAsyncKeyState(VK_F7) & 0x8000 && cmdMode == FALSE) {
			click = TRUE;
			printf("started!\n");
			successTone();
			Sleep(300);
		}

		if (GetAsyncKeyState(VK_F8) & 0x8000 && cmdMode == FALSE) {
			click = FALSE;
			printf("ended!\n");
			successTone();
			Sleep(300);
		}

		if (GetAsyncKeyState(VK_F9) & 0x8000 && cmdMode == FALSE) {
			click = FALSE;
			printf("exiting...\n");
			Sleep(1000);
			break;
		}

		if (GetAsyncKeyState(VK_F10) & 0x8000) {
			click = FALSE;
			cmdMode = TRUE;
			CHAR cmd[10];
			while (cmdMode) {
				printf("command mode>");
				scanf("%s", cmd);
				if (strcmp(cmd, "delay") == 0) {
					INT delayToSet;
					printf("set delay, current is %i\n", DELAY);
					scanf("%i", &delayToSet);
					DELAY = delayToSet;
					printf("set to %i\n", DELAY);
					successTone();
				} else if (strcmp(cmd, "start") == 0) {
					click = TRUE;
					printf("started!\n");
					successTone();
					Sleep(300);
				} else if (strcmp(cmd, "end") == 0) {
					click = FALSE;
					printf("ended!\n");
					successTone();
					Sleep(300);
				} else if (strcmp(cmd, "help") == 0) {
					printf("\nHelp\n");
					printf(" delay       set delay, int value only\n");
					printf(" start       start the autoclicker\n");
					printf(" end         stop the autoclicker\n");
					printf(" help        display help page\n");
					printf(" exit        exit command mode\n");
					printf(" toggle      toggle right and left click\n");
					printf(" hold        hold down instead of clicking\n");
					printf(" save        save current settings\n");
					printf(" load        if autoload doesn't work; load settings\n");
				} else if (strcmp(cmd, "exit") == 0) {
					cmdMode = FALSE;
					printf("exited cmdmode\n");
				} else if (strcmp(cmd, "toggleclick") == 0) {
					rClick = !rClick;
					printf("mouse button toggled to %s click\n", rClick ? "right" : "left");
					successTone();
				} else if (strcmp(cmd, "hold") == 0) {
					hold = !hold;
					printf("holding down val is now %s\n", hold ? "on" : "off");
					successTone();
				} else if (strcmp(cmd, "save") == 0) {
					saveSettings(DELAY, rClick, hold);
				} else if (strcmp(cmd, "load") == 0) {
					loadSettings(&DELAY, &rClick, &hold);
				}
			}
		}

		if (click) {
			if (hold) {
				if (rClick) {
					mouse_event(MOUSEEVENTF_RIGHTDOWN, 0,0,0,0);
				} else {
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
				}
				Sleep(DELAY);
			} else {
				if (rClick) {
					mouse_event(MOUSEEVENTF_RIGHTDOWN, 0,0,0,0);
					mouse_event(MOUSEEVENTF_RIGHTUP, 0,0,0,0);
				} else {
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0,0,0,0);
					mouse_event(MOUSEEVENTF_LEFTUP, 0,0,0,0);
				}
				Sleep(DELAY);
			}
		}

		Sleep(10);
	}

	return 0;
}
