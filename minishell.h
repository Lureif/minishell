#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "./libft/libft.h"
#include "./get_next_line.h"
#define SH_PROMPT "[Unimaginative prompt] : "
#define STRINGIFY(x) #x
#define TOKEN_MAX 255

typedef struct		s_env
{
	char *PATH;
}					t_env;

typedef	enum		s_builtin_enum
{
	ft_cd,
	ft_echo,
	ft_help,
	__BUILTIN_NUMBER
}			t_builtin_enum;

/*
**	Environement related functions
*/

int	ret_env_var_index(char **env, char *var, int initial_pos);
void	ret_env_var(char **env_var_name, int var_len);

/*
**	Memory management functions
*/
void	ft_free_d_tab(void **d_tab);

/*
**	Builtin functions
*/

bool	ft_cd(char *dir);
bool	ft_echo(char *str);
bool	ft_help(void);

/*
**	Main functions
*/
void	ft_print_prompt(void);
