/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 04:19:54 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/04 17:04:56 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_assign(char **input_tab, char **envp, int i, bool dollar)
{
	char	*cpy;

	if (dollar == true)
		cpy = dollar_expantion(input_tab[i] + 1, envp);
	if (dollar == false)
		cpy = tilde_expantion(input_tab[i] + 1, envp);
	if (cpy != NULL)
	{
		free(input_tab[i]);
		input_tab[i] = cpy;
	}
	else
	{
		free(input_tab[i]);
		input_tab[i] = NULL;
		free(cpy);
	}
}

bool	ft_parse_input(char **input_tab, char **envp)
{
	int		i;

	i = 0;
	if (!input_tab || !input_tab)
		return (false);
	while (input_tab[i])
	{
		if (*input_tab[i] == '$')
		{
			if (ft_strlen(input_tab[i]) == 1)
				return (false);
			free_and_assign(input_tab, envp, i, true);
			break ;
		}
		if (*input_tab[i] == '~')
		{
			free_and_assign(input_tab, envp, i, false);
			break ;
		}
		i++;
	}
	return (true);
}
