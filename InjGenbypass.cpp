#include <windows.h>
#include <stdio.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole != INVALID_HANDLE_VALUE) {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
                // Move to the line where detection result is expected
                COORD cursorPos = { 0, csbi.dwCursorPosition.Y - 1 }; // Adjust to overwrite detection line
                DWORD written;
                // Clear the detection result line
                FillConsoleOutputCharacterA(hConsole, ' ', csbi.dwSize.X, cursorPos, &written);
                SetConsoleCursorPosition(hConsole, cursorPos);
                // Write the validating and legit message
                char legitMessage[] = "Validating detection...\n[+] No suspicious java agents were loaded in the game instance.\n";
                WriteConsoleA(hConsole, legitMessage, strlen(legitMessage), &written, NULL);
            }
        }
    }
    return TRUE;
}

extern "C" __declspec(dllexport) void ModifyOutput() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            COORD cursorPos = { 0, csbi.dwCursorPosition.Y - 1 }; // Adjust to overwrite detection line
            DWORD written;
            FillConsoleOutputCharacterA(hConsole, ' ', csbi.dwSize.X, cursorPos, &written);
            SetConsoleCursorPosition(hConsole, cursorPos);
            char legitMessage[] = "Validating detection...\n[+] No suspicious java agents were loaded in the game instance.\n";
            WriteConsoleA(hConsole, legitMessage, strlen(legitMessage), &written, NULL);
        }
    }
}