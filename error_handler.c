/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 03:00:16 by brjorgen          #+#    #+#             */
/*   Updated: 2019/12/10 01:52:04 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*g_error_codes[__ERROR_CODE_NUMBER] = {
	[command_not_found] = ": Command not found.\n",
	[could_not_execute] = ": Fatal: execution failed.\n",
	[no_such_var] = ": No such variable in ENV.\n",
	[no_such_dir_file] = ": No such file or directory.\n",
	[no_args_passed] = ": No arguments passed.\n",
	[undefined_path] = ": Undefined PATH variable.\n",
	[missing_env] = ": Missing environement.\n"
};

void	error_handler(char *process_name, int error_code)
{
	ft_putstr_fd(process_name, 1);
	ft_putstr_fd(g_error_codes[error_code], 1);
}
