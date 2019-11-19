/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:23:06 by brjorgen          #+#    #+#             */
/*   Updated: 2019/11/19 06:02:07 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "./libft/libft.h"
# include "./get_next_line.h"
# define SH_PROMPT "[Unimaginative prompt] : "
# define TOKEN_MAX 255
# define BUILTIN_NUMBER 4
# define ENV_BUILTIN_NUMBER 4
# define ERROR_CODE_NUMBER 1
# define UNUSED __attribute__((unused))
# define STRINGIFY(x) #x

typedef struct	s_sh_utils
{
	char		***envp;
	char		**command;
	char		**line;    
}				t_sh_utils;

enum	e_error_codes
{
	command_not_found,
	no_such_var,
};

/*
**	Just for fun functions
*/

void			ft_print_welcome_banner(void);

/*
**	Environement related functions
*/

int				ret_env_var_index(char **env, char *var, int initial_pos);
bool			trim_env_var(char **env_var_name);

/*
**	Tab functions
*/
void			ft_augment_size(char **original_container, size_t *size);
void			free_tab(void **tab);
int				tab_size(const void **tab);

/*
**	Shell utils
*/

bool			ft_process_launch(char *bin_paths, char ***args, char ***envp);
void			ft_cleanup(char **line, char ***tab);
void			ft_print_prompt(void);

/*
**	Builtin functions
*/

bool			ft_exec_builtins(t_sh_utils *sh_utils);
bool			ft_cd(char **dir);
bool			ft_echo(char **str);
bool			ft_help(__attribute__((unused)) char **param);
bool			ft_clear(__attribute__((unused)) char **param);

/*
** ___________________ ENV builtin funcitons
*/

bool			ft_env(t_sh_utils *sh_utils);
bool			ft_setenv(t_sh_utils *sh_utils);
bool			ft_unsetenv(t_sh_utils *sh_utils);
bool			ft_exit(t_sh_utils *sh_utils);
#endif
