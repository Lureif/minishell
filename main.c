#include "minishell.h"
#include "get_next_line.h"

void	ft_print_prompt(void)
{
	ft_putstr_fd(SH_PROMPT, 1);
}

void	free_tab(void **tab)
{
	unsigned int y;

	y = 0;
	while (tab[y])
	{
		free(tab[y]);
		y++;
	}
	free(tab);
}

bool	ft_cd(char *dir)
{	
	if(chdir(dir) != 0)
	{
		return (false);
	}
}

void	ft_cleanup_shell(char *path, char *input_line, char **split_input_line)
{
	printf("1\n");
	if (path)
		free(path);
	printf("2\n");
	if (input_line)
		free(input_line);
	printf("3\n");
	if (split_input_line)
		free_tab((void **)split_input_line);
}

bool	ft_process_launch(char *path, char **args)
{
	int	status;
	pid_t	child_pid;
	pid_t	wait_pid;
	
	child_pid = fork();
	if (child_pid < 0)
	{
		perror("\nminishell");
	}
	else if (child_pid == 0)
	{
		if (execve(path, args, NULL) == -1)
		{
			perror("\nminishell");
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait_pid = waitpid(child_pid, &status, WUNTRACED);
	}
	return (true);
}

int	main(int ac, char **av)
{
	char	**split_input_line;
	char	*input_line;
	char	*path;

	while (420)
	{
		ft_print_prompt();
		get_next_line(1, &input_line);
		split_input_line = ft_strsplit(input_line, ' ');
		if (split_input_line && !ft_strcmp(split_input_line[0], "cd"))
			ft_cd(split_input_line[1]);
		if (split_input_line && split_input_line[0])
		{
			path = ft_strjoin("/usr/bin/", split_input_line[0]);
			if (!(ft_process_launch(path, split_input_line)))
			{
				ft_cleanup_shell(path, input_line, split_input_line);
				exit(EXIT_FAILURE);
			}
		}
//		ft_cleanup_shell(path, input_line, split_input_line);
	}
	return (0);
}
