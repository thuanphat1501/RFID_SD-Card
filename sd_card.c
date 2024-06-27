#include "sd_card.h"


void readFile(char* filename){
	// M? file
    fres = f_open(&fil, "test.txt", FA_READ);
    if (fres == FR_OK) {
        char buffer[128];

        // Ð?c file
        UINT br;
        fres = f_read(&fil, buffer, sizeof(buffer)-1, &br);
        if (fres == FR_OK && br > 0) {
            buffer[br] = '\0'; // Ð?m b?o chu?i du?c k?t thúc b?ng NULL
            // Truy?n qua UART
            UART_Transmit(buffer);
        }

        // Ðóng file
        f_close(&fil);
    }

    // Unmount SD card
    f_mount(NULL, "", 0);
}
