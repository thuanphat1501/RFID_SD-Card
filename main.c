#include "main.h"
#include "stm32f10x.h"
#include "fatfs.h"
#include "gpio.h"
#include "uart.h"
#include "spi.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>
#include "delay.h"
#include "mfrc522.h"
#include "servo.h"

/* Definitions for FATFS and file */
FATFS fs;
FIL fil;
FRESULT fres;
DWORD fre_clust;
uint32_t total, freespace;
char buffer[100];

uint8_t CardID[5];
char szBuff[100];

/* Node for linked list */
typedef struct Node {
    uint8_t cardID[5];
    struct Node* next;
} Node;

Node* head = NULL;
/* Function to add a new ID to the linked list */
void addID(uint8_t* newID) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        _Error_Handler(__FILE__, __LINE__);
    }
    memcpy(newNode->cardID, newID, 5);
    newNode->next = head;
    head = newNode;
}
/* Function to check if an ID is already in the linked list */
int isIDExists(uint8_t* id) {
    Node* current = head;
    while (current != NULL) {
        if (memcmp(current->cardID, id, 5) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}
/* Function to load existing IDs from the CSV file into the linked list */
void loadExistingIDs(void) {
    if (f_open(&fil, "rfid_data.csv", FA_READ) == FR_OK) {
        while (f_gets(buffer, sizeof(buffer), &fil)) {
            uint8_t id[5];
            if (sscanf(buffer, "ID: 0x%02X%02X%02X%02X%02X", &id[0], &id[1], &id[2], &id[3], &id[4]) == 5) {
                addID(id);
            }
        }
        f_close(&fil);
    }
}
int main(void)
{
    /* Initialize configurations */
    GPIO_Config();
    SPI_Config();
    UART_Config();
    TM_MFRC522_Init();
    MX_FATFS_Init();
    Delay_Init();
    TIM2_Config();

    /* Mount SD Card */
    if (f_mount(&fs, "", 0) != FR_OK)
        _Error_Handler(__FILE__, __LINE__);

    /* Load existing IDs from the file */
    loadExistingIDs();
		
		MoveServoTo180Degrees();
		Delay(5000);
    /* Ensure servo is at initial position */
    MoveServoBackTo0Degrees();
		
    /* Main loop */
    while (1)
    {
        if (TM_MFRC522_Check(CardID) == MI_OK)
        {
            if (isIDExists(CardID)) {
                UART_Transmit("ID is found\n");
                MoveServoTo90Degrees();
                Delay(500); // Hold for 0.5 seconds
                MoveServoBackTo0Degrees();
            } else {
                UART_Transmit("ID is NOT found\n");
            }
        }
    }

    return 0;
}

void _Error_Handler(char *file, int line) {
    while (1) {
    }
}
