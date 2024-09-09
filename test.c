#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#include <stdlib.h>
#include <stdio.h>

void printWindowProp(Display *display, Window *window) {
	XWindowAttributes xwa;
	XGetWindowAttributes(display, window, &xwa);

	char *windowName;
	char *className;
	int pid;
	{
		XTextProperty textData;
		Atom atom = XInternAtom(display, "WM_NAME", True);
		int status = XGetTextProperty(display, window, &textData, atom);
		windowName = (char*)textData.value;
	}
	{
		XTextProperty textData;
		Atom atom = XInternAtom(display, "WM_CLASS", True);
		int status = XGetTextProperty(display, window, &textData, atom);
		className = (char*)textData.value;
	}
	{
		XTextProperty textData;
		Atom atom = XInternAtom(display, "_NET_WM_PID", True);
		int status = XGetTextProperty(display, window, &textData, atom);
		if (textData.nitems) {
			pid = (unsigned char*)textData.value;
			pid = textData.value[1] * 256;
			pid += textData.value[0];
		}
	}

	{
		XWMHints* hints = XGetWMHints(display, window);
		if (hints) {
			// printf("%ld\n", hints->flags);
			// printf("%d\n", hints->initial_state);
		}
	}

	if (windowName) {
		if (className) {
			if (xwa.override_redirect == 0 && xwa.width > 200 && xwa.height > 200) {
				printf("==================\n");
				printf("Pid: %5i %s[%s]\n", pid, className, windowName);
				printf("X: %d, Y:%d\n", xwa.x, xwa.y);
				printf("Width: %d, Height: %d\n", xwa.width, xwa.height);
				printf("%d\n", xwa.override_redirect);
			}
		}
	}
}

void getWindows(Display *display, Window rootWin, int depth) {
	Window parent;
	Window *children;
	Window *child;
	unsigned int numberOfChildren;

	Status status = XQueryTree(display, rootWin, &rootWin, &parent, &children, &numberOfChildren);
	if (!status) {
		return;
	}

	if (!numberOfChildren) {
		return;
	}

	int i;
	for (i = 0; i < numberOfChildren; i++) {
		child = children[i];
		printWindowProp(display, child);
		getWindows(display, child, depth + 1);
	}
}

int main() {
	Display *display = XOpenDisplay(NULL);
	if (display == NULL) {
		printf("Failed to connect to X server\n");
		exit(-1);
	}

	int screenNum = DefaultScreen(display);
	printf("Screen: %i\n", screenNum);
	printf("Dim: %i %i\n", DisplayWidth(display, screenNum), DisplayHeight(display, screenNum));

	Window rootWin = DefaultRootWindow(display);
	int depth;
	getWindows(display, rootWin, 0);
	return 0;
}
