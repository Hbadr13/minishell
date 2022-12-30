/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouabba <ebouabba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 00:13:00 by ebouabba          #+#    #+#             */
/*   Updated: 2022/10/26 18:04:41 by ebouabba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	init_variable_global(int status)
{
	char	*pwd1;

	if (status)
	{
		g_global.exit_status = 0;
		rl_catch_signals = 0;
	}
	else
	{
		g_global.skip = 0;
		g_global.if_fork = 0;
		g_global.prinf_old_pwd = 0;
		pwd1 = getcwd(NULL, 0);
		if (pwd1)
		{
			free(g_global.pwd);
			g_global.pwd = pwd1;
		}
	}
	return (0);
}

char	*prompt(char *pwd)
{
	char	*str;
	char	*path;

	path = pwd;
	if (ft_strcmp("/", path) == 0)
	{
		if (g_global.exit_status == 0)
			path = my_ft_strjoin("\x1B[32m➜ \x1B[33m", path, 0, 0);
		else
			path = my_ft_strjoin("\x1B[31m➜ \x1B[33m", path, 0, 0);
		path = my_ft_strjoin(path, " \x1B[0m", 1, 0);
		return (path);
	}
	str = path;
	path = strrchr(path, '/') + 1;
	if (g_global.exit_status == 0)
		path = my_ft_strjoin("\x1B[32m➜ \x1B[33m", path, 0, 0);
	else
		path = my_ft_strjoin("\x1B[31m➜ \x1B[33m", path, 0, 0);
	path = my_ft_strjoin(path, " \x1B[0m", 1, 0);
	return (path);
}

char	*ft_readline(void)
{
	char	*line;
	char *prmt;

	signal(SIGINT, fanc_aplic);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = get_c;
	prmt = prompt(g_global.pwd);
	line = readline(prmt);
	if (!line)
	{
		ft_putendl_fd("exit", 2);
		exit(g_global.exit_status);
	}
	if (!line[0] || g_global.skip == 1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	main(int ac, char **av, char **envp)
{
	t_env	**envs;
	t_mini	**big_stack;
	char	*line;

	(void)av;
	if (ac != 1)
		exit(1);
	envs = ft_env(envp);
	g_global.pwd = my_ft_strdup("");
	init_variable_global(1);
	while (1)
	{
		init_variable_global(0);
		g_global.envs = envs;
		line = ft_readline();
		if (!line)
			continue ;
		add_history(line);
		big_stack = parsing(line);
		if (!big_stack)
			continue ;
		execution(big_stack, envs);
	}
}
