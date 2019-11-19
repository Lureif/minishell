/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_augment_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brjorgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 01:47:05 by brjorgen          #+#    #+#             */
/*   Updated: 2019/11/19 01:47:16 by brjorgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				ft_augment_size(char **original_container, size_t *size)
{
	char			*tmp_container;
	size_t			size_to_augment;

	size_to_augment = *size * 2;
	if (!(tmp_container = (char *)malloc(sizeof(char) * (size_to_augment))))
	{
		ft_memdel((void **)original_container);
		return ;
	}
	ft_memcpy(tmp_container, *original_container, *size);
	ft_memdel((void **)original_container);
	*original_container = tmp_container;
	*size = size_to_augment;
}
