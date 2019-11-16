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
#include <assert.h>

int		ret_env_var_index(char **env, char *var, int initial_pos)
{
	if (!*env || !var)
		return  (-1);
    if (ft_strncmp(env[initial_pos], var, ft_strlen(var)) == 0)
		return (initial_pos);
	else
		return (ret_env_var_index(env, var, ++initial_pos));
	return (0);
}

void	ret_env_var(char **env_var_name, int var_len)
{
	*env_var_name += (var_len + 1);
}
