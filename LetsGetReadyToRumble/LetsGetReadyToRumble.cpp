#include "pch.h"
#include <stdio.h>
#include <windows.h>
#include <Xinput.h>

// Controller ID. We only expect a single Xbox controller to be connected,
// so this number will always be zero.
#define CONTROLLER_0 0

// Define magic numbers that will be easily identifiable in packet captures.
#define LEFT_MOTOR_SPEED 0xF00D
#define RIGHT_MOTOR_SPEED 0xBEEF

int main()
{
    XINPUT_STATE xInputState;
    XINPUT_VIBRATION vibration;

    printf("Let's get ready to rumble!\n");

    // Check if controller is connected.
    // Program expects a single Xbox controller connected.
    DWORD result = XInputGetState(CONTROLLER_0, &xInputState);

    if (result == ERROR_SUCCESS)
    {
        printf("Connected\n");
    }
    else
    {
        printf("Failed to find connected controller. Error: %x\n", result);
        goto Exit;
    }

    // Set vibration level.
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
    vibration.wLeftMotorSpeed = LEFT_MOTOR_SPEED; // use any value between 0-65535 here
    vibration.wRightMotorSpeed = RIGHT_MOTOR_SPEED; // use any value between 0-65535 here

    result = XInputSetState(CONTROLLER_0, &vibration);
    if (result != ERROR_SUCCESS)
    {
        printf("Failed to set controller state. Result: %x\n", result);
        goto Exit;
    }

    printf("Vibrating controller... press enter to stop vibration.\n");
    getchar();

    printf("Stopping vibration.\n");
    ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
    vibration.wLeftMotorSpeed = 0;
    vibration.wRightMotorSpeed = 0;

    result = XInputSetState(CONTROLLER_0, &vibration);
    if (result != ERROR_SUCCESS)
    {
        printf("Failed to set controller state. Result: %x\n", result);
        goto Exit;
    }

Exit:
    return 0;
}