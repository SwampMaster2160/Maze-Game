#include <stdio.h>

#include "main.h"

const LPCSTR ERROR_MESSAGES[MGERROR_COUNT - 1] =
{
	"Unable to register window class.",
	"Unable to create window.",
	"Unable to retrieve the device context of the window.",
	"Unable to create timer.",
	"Unable to retrieve a pixel format.",
	"Unable to set the pixel format.",
	"Unable to create OpenGL rendering context.",
	"Unable to make the OpenGL rendering context the current context.",
	"Unable to allocate memory for textures.",
	"Unable to get the textures bitmap resource.",
	"Unable to load the textures bitmap resource.",
	"Bad image format for textures bitmap resource.",
	"Unable to release the textures bitmap resource.",
	"Error while polling messages.",
};

/// @brief Will display an error message an an error dialog if it is not `MGERROR_NONE`.
/// @param error The error to display, `MGERROR_NONE` if no error.
/// @return A return code for the program, `1` if there is an error, `0` if `error` is `MGERROR_NONE`.
int DisplayError(MGERROR error)
{
	char title[6 + 11 + 1];
	if (error == MGERROR_NONE) return 0;
	sprintf(title, "Error %d", error);
	MessageBoxA(NULL, ERROR_MESSAGES[error - 1], title, MB_ICONERROR);
	return 1;
}