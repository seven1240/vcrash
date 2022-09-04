module mod

struct FreeswitchFunctionTable {
	switch_api_version int
	load               voidptr
	shutdown           voidptr
	runtime            voidptr
	flags              int
}

const (
	module_interface = FreeswitchFunctionTable{5, start, stop, C.NULL, 0}
)

struct Globals {
	a int
	b int
}

__global (
	a           = int(1)
	seven       = int(7)
	mod_globals Globals
)

pub fn start()
{
	println("start")
}

pub fn stop()
{
	println("stop")
}
