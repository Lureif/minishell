/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:23:06 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/14 03:18:26 by brjorgen         ###   ########.fr       */
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
# include <sys/param.h>
# include "./libft/libft.h"
# include "./get_next_line.h"
# define CLEAR_SCREEN "\e[1;1H\e[2J"
# define TOKEN_MAX 255

typedef struct	s_sh_utils
{
	char		***envp;
	bool		changed_env;
	char		**command;
	char		**line;
	char		*prev_working_dir;
	char		*cur_working_dir;
}				t_sh_utils;

enum			e_error_codes
{
	command_not_found,
	could_not_execute,
	no_such_var,
	no_such_dir_file,
	no_args_passed,
	undefined_path,
	missing_env,
	__ERROR_CODE_NUMBER
};

enum			e_builtin_names
{
	echo,
	help,
	clear,
	BUILTIN_NUMBER
};

enum			e_env_builtin_names
{
	cd,
	fct_env,
	fct_setenv,
	fct_unsetenv,
	fct_exit,
	ENV_BUILTIN_NUMBER
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

/*
**	____________ Process launch functions.
*/

bool			ft_process_launch(char ***args, char ***envp);
bool			ft_child_process(char *bin_path, char **args, char **envp);
bool			ft_path_function(char **path_to_exec, char ***args
								, char ***envp);
bool			ft_path_check_stat(char **path_to_exec, char ***args);
bool			ft_fork_actions(char ***args, char ***envp, char *path_to_exec);
bool			parse_arg(char *args);
void			ft_path_cleanup(char **path_to_exec, char ***split_bin_paths);
void			error_handler(char *process_name, int error_code);
void			ft_cleanup(t_sh_utils *sh_utils);
void			ft_print_prompt(void);
char			**ft_str_tab_cpy(char **tab);

/*
**	Builtin functions
*/

bool			ft_exec_builtins(t_sh_utils *sh_utils);
bool			ft_cd(t_sh_utils *sh_utils);
void			ft_cd_update_prev_dir(t_sh_utils *sh_utils);
void			ft_cd_print_dir_switch(t_sh_utils *sh_utils, bool went_back);
bool			ft_echo(char **str);
bool			ft_help(char **param);
bool			ft_clear(char **param);

/*
** ___________________ ENV builtin funcitons
*/

void			ft_add_var(char **tab, char *key, char *val);
bool			ft_env(t_sh_utils *sh_utils);
bool			ft_setenv(t_sh_utils *sh_utils);
bool			ft_unsetenv(t_sh_utils *sh_utils);
char			**ft_str_tab_del_element(char **tab, char *element);
bool			ft_check_input_add_var(t_sh_utils *sh_utils);
bool			ft_exit(t_sh_utils *sh_utils);

/*
** ___________________ Expantions
*/

bool			ft_parse_input(char **input_tab, char **envp);
char			*dollar_expantion(char *to_expand, char **envp);
char			*tilde_expantion(char *to_expand, char **envp);

void			print_tab(char **tab);
#endif
