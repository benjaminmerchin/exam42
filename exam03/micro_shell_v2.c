#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define PIPE 1
#define END 2
#define SEP 3

typedef struct s_a {
	char **av;
	char **env;
	int type;
	int pipe_fd[2];
	int type_backup;
	int pipe_backup;
} t_a;

void putstr_ft(char *str, int fd) {
	int i = 0;

	while (str && str[i]) {
		write(2, &str[i], 1);
		i++;
	}
}

int error_int(char *s1, char *s2) {
	putstr_ft("error: ", 2);
	putstr_ft(s1, 2);
	putstr_ft(s2, 2);
	putstr_ft("\n", 2);
	return 1;
}

int execution(t_a *a) {
	pid_t pid;

	if (a->type == PIPE)
		if (pipe(a->pipe_fd) < 0)
			return error_int("fatal", NULL);
	pid = fork();
	if (pid < 0)
		return error_int("fatal", NULL);
	if (pid == 0) { //child
		if (a->type_backup == PIPE && dup2(a->pipe_backup, 0) < 0)
			return error_int("fatal", NULL);
		if (a->type == PIPE && dup2(a->pipe_fd[1], 1) < 0)
			return error_int("fatal", NULL);
		if (execve(a->av[0], a->av, a->env) < 0) {
			return error_int("cannot execute ", NULL);
			exit(1);
		}
	}
	else { //parent
		waitpid(pid, 0, 0);
		if (a->type_backup == PIPE)
			close(a->pipe_backup);
		if (a->type_backup && !a->type)
			close(a->pipe_fd[0]);
		if (a->type)
			close(a->pipe_fd[1]);
	}
	return 0;
}

int cd(t_a *a) {
	int i = 0;

	while (a->av[i])
		i++;
	if (i != 2)
		return error_int("cd: bad arguments", NULL);
	if (chdir(a->av[1]) < 0)
		return error_int("cd: cannot change directory to ", a->av[1]);
	return 0;
}

int parsing(t_a *a, char **av) {
	int i = 0;

	a->av = av;
	a->type_backup = a->type;
	a->pipe_backup = a->pipe_fd[0];
	while (av[i]) {
		if (strcmp(av[i], "|") == 0) {
			a->type = PIPE;
			a->av[i] = NULL;
			return i;
		}
		if (strcmp(av[i], ";") == 0) {
			a->type = SEP;
			a->av[i] = NULL;
			return i;
		}
		i++;
	}
	a->type = END;
	return i;
}

int main(int ac, char **av, char **env) {
	int i = 1;
	int ret = 0;
	t_a a;
	int moving;

	a.env = env;
	a.type = END;
	a.pipe_fd[0] = 0;
	a.pipe_fd[1] = 1;
	while (i < ac && av[i]) {
		moving = parsing(&a, &av[i]);
		if (moving != 0) {
			if (strcmp(av[i], "cd") == 0)
				ret = cd(&a);
			else
				ret = execution(&a);
		}
		i += moving + 1;
	}
	return ret;
}
