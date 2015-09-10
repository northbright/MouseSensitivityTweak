// MouseSensitivityTweak.cpp : Defines the entry point for the console application.
//

#include <Windows.h>
#include <tchar.h>

#define MIN_SPEED        1
#define MAX_SPEED        20
#define DEF_SPEED        10

BOOL IsSpeedValid(int nSpeed) {
    return ((nSpeed >= MIN_SPEED) && (nSpeed <= MAX_SPEED)) ? TRUE : FALSE;
}

int GetMouseSpeed() {
    int nSpeed = 0;
    BOOL fResult = SystemParametersInfo(SPI_GETMOUSESPEED,  // Get mouse information
                                        0,                  // Not used
                                        &nSpeed,            // Holds mouse speed
                                        0);

    if (!fResult || !IsSpeedValid(nSpeed)) {
        return -1;
    }
    return nSpeed;
}

BOOL SetMouseSpeed(int nSpeed) {
    if (!IsSpeedValid(nSpeed)) {
        return FALSE;
    }

    int nOldSpeed = GetMouseSpeed();
    if (nOldSpeed == nSpeed) {
        return TRUE;
    }

    BOOL fResult = SystemParametersInfo(SPI_SETMOUSESPEED,  // Get mouse information
                                        0,                  // Not used
                                        PVOID(nSpeed),      // Holds mouse speed
                                        SPIF_SENDCHANGE);   // Broadcasts the WM_SETTINGCHANGE message

    return fResult;
}

// Usage MouseSensitivityTweak <speed>
// Ex:
// MouseSensitivityTweak 16
int _tmain(int argc, _TCHAR* argv[])
{
    int nSpeed = DEF_SPEED;

    if (argc != 2) {
        return 0;
    }

    nSpeed = _wtoi(argv[1]);
    return SetMouseSpeed(nSpeed);
}