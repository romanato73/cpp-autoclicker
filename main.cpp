/*
 * Autoclicker script
 * @author Roman Országh
 */

#include <iostream>
#include <ctype.h>
#include <windows.h>

using namespace std;

int isClicked(char key);
void clickWithDelay(int delay, char stopKey, int *status);

int main() {
    int delay = 0;
    char startKey = 'S';
    char stopKey = 'S';
    int status = 0;

    cout << "Click delay (ms): ";
    cin >> delay;
    while (delay < 1 || cin.fail()) {
        cout << "Delay must be a number and more than 0.\nEnter new value (ms): ";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> delay;
    }
    cout << "\n\tPress S to start/stop clicking." << endl;
    cout << "\tPress ESC to end the program." << endl;
    cout << "\nListening..." << endl;

    do {
        if (isClicked(startKey)) {
            status = 1;
            cout << "Clicking every " << delay << "ms" << endl;
            Sleep(1000);
            while (status) {
                clickWithDelay(delay, stopKey, &status);
            }
            cout << "Event stopped." << endl;
            Sleep(1000);
        }
    } while(!isClicked(VK_ESCAPE));

    return 0;
}

int isClicked(char key) {
    if (GetKeyState(key) & 0x8000)
        return 1;
    return 0;
}

void clickWithDelay(int delay, char stopKey, int *status) {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
    for (int i = 0; i < delay; i++) {
        if (isClicked(stopKey)) {
            *status = 0;
            break;
        }
        if (isClicked(VK_ESCAPE)) {
            exit(1);
        }
        Sleep(1);
    }
}
