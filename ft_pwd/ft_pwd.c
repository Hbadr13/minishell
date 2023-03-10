/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbadr <hbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 06:52:17 by hbadr             #+#    #+#             */
/*   Updated: 2022/10/22 07:56:45 by hbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

void	ft_pwd(void)
{
	ft_putendl_fd(g_global.pwd, 1);
	g_global.exit_status = 0;
}
