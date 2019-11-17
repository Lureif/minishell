/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 02:29:33 by brjorgen          #+#    #+#             */
/*   Updated: 2019/11/16 03:53:53 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : ret_env_var_index
**	ARGS  	   : -> env : environement 2d array (envp)
**	      	     -> var : the wanted environement variable
**	      	     -> initial_pos : 1st position in 2d array (set to 0)
**	DESCRIPTION:
**	returns the index at which the VAR is contained int the env 2d array.
*/

int	ret_env_var_index(char **env, char *var, int initial_pos)
{
	if (!*env || !var)
		return  (-1);
	if (ft_strncmp(env[initial_pos], var, ft_strlen(var)) == 0)
		return (initial_pos);
	else
		return (ret_env_var_index(env, var, ++initial_pos));
	return (0);
}

/*
**	HEADER	   : minishell.h
**	PROJ  	   : minishell
**	NAME  	   : ret_env_var
**	ARGS  	   : ->env_var_name : the address of the pertinent line in
**				      envp
**		     ->var_len : length of the argument variable
**	DESCRIPTION:
**	Moves the pointer at the address of env_var_name 
**	to var_len (length of env variable name) + 1 (for the '=').
*/

bool	trim_env_var(char **env_var_name)
{
	unsigned int var_len;

	if (!env_var_name || *env_var_name)
		return (false);
	var_len = ft_strlen(*env_var_name);
	*env_var_name += (var_len + 1);
	return (true);
}
