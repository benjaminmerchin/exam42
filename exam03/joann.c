#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//STRUCT

typedef enum 	e_type
{
	SEP,
	PIPE,
	END
}				t_type;

typedef struct	s_cmd
{
	char	**av;
	char	**env;
	t_type	type;
	int		pipe_fd[2];
	t_type	prev_cmd_type;
	int		prev_cmd_pipe;
}				t_cmd;

//UTILS

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void ft_putstr(int fd, char *str, int len)
{
	write(fd, str, len);
}
	
int err_int(int fd, char *s1, char *s2, int ret)
{
	write(fd, "error: ", 7);
	if (s1)
		ft_putstr(fd, s1, ft_strlen(s1));
	if (s2)
		ft_putstr(fd, s2, ft_strlen(s2));
	write(fd, "\n", 1);
	return (ret);
}

// CD

int built_in_cd(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->av[i])
		i++;
	if (i != 2)
		return (err_int(2, "cd: bad arguments", NULL, 1));
	if (chdir(cmd->av[1]) == -1)
		return (err_int(2, "cd: cannot change directory path to ", cmd->av[1], 1));
	return (0);
}

// EXEC

int execute_cmd(t_cmd *cmd)
{
	pid_t pid;

	if (cmd->type == PIPE)
	{
		if (pipe(cmd->pipe_fd) == -1)
			return (err_int(2, "fatal", NULL, 1));
	}

	pid = fork();
	if (pid < 0)
		return (err_int(2, "fatal", NULL, 1));
	if (pid == 0) // child
	{
		if (cmd->prev_cmd_type == PIPE)
			if (dup2(cmd->prev_cmd_pipe, 0) < 0)
				return (err_int(2, "fatal", NULL, 1));
		if (cmd->type == PIPE)
		{
			if (dup2(cmd->pipe_fd[1], 1) < 0)
				return (err_int(2, "fatal", NULL, 1));
		}
		if (execve(cmd->av[0], cmd->av, cmd->env) < 0)
		{
			err_int(2, "cannot execute ", cmd->av[0], 1);
			exit(1);
		}
	}
	else
	{
		waitpid(pid, 0, 0);
		if (cmd->prev_cmd_type == PIPE)
			close(cmd->prev_cmd_pipe);
		if (cmd->type == PIPE)
			close(cmd->pipe_fd[1]);
		if (cmd->prev_cmd_type == PIPE && cmd->type != PIPE)
			close(cmd->pipe_fd[0]);
	}
	return (0);
}

//PARSING

int cmd_end(t_cmd *cmd, char **av)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (strcmp(av[i], "|") == 0)
		{
			cmd->type = PIPE;
			av[i] = NULL;
			return (i);
		}
		if (strcmp(av[i], ";") == 0)
		{
			cmd->type = SEP;
			av[i] = NULL;
			return (i);
		}
		i++;
	}
	cmd->type = END;
	return (i);
}


int parse_cmd(t_cmd *cmd, char **av)
{
	int len;

	cmd->av = av;
	cmd->prev_cmd_type = cmd->type;
	cmd->prev_cmd_pipe = cmd->pipe_fd[0];
	len = cmd_end(cmd, av);
	return (len);
}


//MAIN


int main(int ac, char **av, char **env)
{
	int		res;
	int		i;
	int 	avance; 
	t_cmd	cmd;

	res = 0;
	
	cmd.env = env;
	cmd.type = END;
	cmd.pipe_fd[0] = 0;
	cmd.pipe_fd[1] = 1;
	
	i = 1;
	while (i < ac && av[i])
	{
		avance = parse_cmd(&cmd, &(av[i]));
		if (avance != 0)
		{
			if (strcmp(av[i], "cd") == 0)
				res = built_in_cd(&cmd);
			else
				res = execute_cmd(&cmd);
		}
		i += avance + 1;
	}
	return (res);
}
