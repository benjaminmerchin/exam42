#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

#define PIPE 1
#define END 2
#define SEP 3

typedef struct s_a {
	int type;
	int type_backup;
	int pipe_fd[2];
	int pipe_fd_backup;
	char **av;
	char **env;
} t_a;

void ft_putstr_fd(char *str, int fd) {
	int i = 0;
	while (str && str[i]) {
		write(fd, &str[i], 1);
		i++;
	}
}

int error(char *s1, char *s2) {
	ft_putstr_fd("error: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(s2, 2);
	ft_putstr_fd("\n", 2);
	return 1;
}

int cd(t_a *a) {
	int i = 0;
	while (a->av[i]) {
		i++;
	}
	if (i != 2) {
		return error("cd: bad arguments", NULL);
	}
	if (chdir(a->av[i]) < 0)
		return error("cd: cannot change directory to ", a->av[1]);
	return 0;
}

int execution(t_a *a) {
	pid_t pid;

	if (a->type == PIPE)
		if (pipe(a->pipe_fd) < 0)
			return error("fatal", NULL);
	pid = fork();
	if (pid < 0)
		return error("fatal", NULL);
	if (pid == 0) {
		if (a->type_backup == PIPE)
			if (dup2(a->pipe_fd_backup, 0) < 0)
				return error("fatal", NULL);
		if (a->type == PIPE)
			if (dup2(a->pipe_fd[1], 1) < 0)
				return error("fatal", NULL);
		if (execve(a->av[0], a->av, a->env) < 0) {
			error("cannot execute ", a->av[0]); // error("cannot execute ", a->av[0]);
			exit(1);
		}
	}
	else {
		waitpid(pid, 0, 0);
		if (a->type_backup == PIPE)
			close(a->pipe_fd_backup);
		if (a->type_backup == PIPE && a->type != PIPE)
			close(a->pipe_fd[0]);
		if (a->type == PIPE)
			close(a->pipe_fd[1]);
	}
	return 0;
}

int parsing(t_a *a, char **av) { //  char **av
	int i = 0;

	a->av = av; // a->av = av;
	a->type_backup = a->type;
	a->pipe_fd_backup = a->pipe_fd[0]; //doute ici
	while (a->av[i]) {
		if (strcmp(a->av[i], "|") == 0) {
			a->type = PIPE;
			a->av[i] = NULL;
			return i;
		}
		if (strcmp(a->av[i], ";") == 0) {
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
	int ret = 0;
	t_a a;
	int moving;
	int i = 1;

	a.env = env;
	a.type = END;
	a.pipe_fd[0] = 0;
	a.pipe_fd[1] = 1;
	while (i < ac && av[i]) { // i < ac
		moving = parsing(&a, &av[i]); //av[i]
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