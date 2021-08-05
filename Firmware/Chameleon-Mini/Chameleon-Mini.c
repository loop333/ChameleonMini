#include "Chameleon-Mini.h"
#include "Uart.h"
#include "uartcmd.h"

int main(void) {
    SystemInit();
    SettingsLoad();
    LEDInit();
    MemoryInit();
    DetectionInit();
    CodecInitCommon();
    ConfigurationInit();
    TerminalInit();
    RandomInit();
    ButtonInit();
    AntennaLevelInit();
    LogInit();
    SystemInterruptInit();
    uart_init();
    uartcmd_init();

    while (1) {
        if (SystemTick100ms()) {
            LEDTick(); // this has to be the first function called here, since it is time-critical - the functions below may have non-negligible runtimes!

            RandomTick();
            TerminalTick();
            ButtonTick();
            LogTick();
            ApplicationTick();
            CommandLineTick();
            AntennaLevelTick();
            uartcmd_tick();

            LEDHook(LED_POWERED, LED_ON);
        }

        uart_task();
        uartcmd_task();
        TerminalTask();
        LogTask();
        ApplicationTask();
        CodecTask();
    }
}

