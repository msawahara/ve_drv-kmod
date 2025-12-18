#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#define ARGS_NUM 4



int main(int argc, char *argv[]) {
    char **new_argv = argv;
    const char *target = "/opt/nec/ve/veos/libexec/ve_check_config";
    if (argc != ARGS_NUM) {
        fprintf(stderr, "ve_check_config_wrapper: invalid args\n");
        return EINVAL;
    }
    new_argv[0] = (char *)target;
    execv(target, new_argv);

    fprintf(stderr, "ve_check_config_wrapper: execv failed: %s\n", strerror(errno));
    _exit(1);
}
