#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#ifdef __APPLE__
#define SONAME "./mod.dylib"
#else
#define SONAME "./mod.so"
#endif

static void *thread_run(void *ptr)
{
	void *lib = NULL;
	void (*start)();
	void (*stop)();
	char *error;

	lib = dlopen(SONAME, RTLD_NOW | RTLD_GLOBAL);
	// lib = dlopen(SONAME, RTLD_NOW | RTLD_LOCAL);
	if (!lib) {
		fprintf(stderr, "cannot load " SONAME);
		exit(1);
	}
	// https://man7.org/linux/man-pages/man3/dlopen.3.html
	// test = (void (*)())dlsym(lib, "test");
	*(void **)(&start) = dlsym(lib, "mod__start");
	error = dlerror();
	if (error != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}
	*(void **)(&stop) = dlsym(lib, "mod__stop");
	error = dlerror();
	if (error != NULL) {
		fprintf(stderr, "%s\n", error);
		exit(EXIT_FAILURE);
	}

	start();
	stop();
	dlclose(lib);
	printf("thread done\n");
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t thread;
	int ret = 0;

	printf("Hello\n");
	ret = pthread_create(&thread, NULL, thread_run, NULL);
	if (ret == 0) {
		printf("Closing\n");
		pthread_join(thread, NULL);
	}
	printf("Closed\n");
	int sanity = 3;
	while (sanity-- > 0) {
		printf("Tick ... %d\n", sanity);
		sleep(1);
	}
	printf("Done\n");
	return 0;
}
