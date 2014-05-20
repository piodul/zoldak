set(SOURCES
	linux_evdev.c
	macosx_hidmanager.c
	macosx_hidutilities.c
	manymouse.c
	windows_wminput.c
	x11_xinput2.c
)

add_library(ManyMouse ${SOURCES})
