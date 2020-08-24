#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int
main(int argc, char *argv[])
{
    int pipefd[2];
    pid_t cpid;
    char buf;
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <string>\n", argv[0]);
        exit(1);
    }
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(1);
    }
    if (cpid == 0) {    /* Потомок читает из канала */
        close(pipefd[1]);          /* Закрывает неиспользуемый конец для записи */
        while (read(pipefd[0], &buf, 1) > 0)
            write(1, &buf, 1);
        write(1, "\n", 1);
        close(pipefd[0]);
        _exit(0);
    } else {            /* Родитель пишет значение argv[1] в канал */
        close(pipefd[0]);          /* Закрывает неиспользуемый конец для чтения */
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);          /* Читатель видит EOF */
        wait(NULL);                /* Ожидание потомка */
        exit(0);
    }
}