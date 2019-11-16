#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "./libft/libft.h"
#include "./get_next_line.h"
#define SH_PROMPT "[Unimaginative prompt] : "
#define TOKEN_MAX 255

typedef struct		s_env
{
	char *PATH;
}					t_env;

int		ret_env_var_index(char **env, char *var, int initial_pos);
void	ret_env_var(char **env_var_name, int var_len);
void	ft_free_d_tab(void **d_tab);
void	ft_print_prompt(void);
