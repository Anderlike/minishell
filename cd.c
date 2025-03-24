/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fragarc2 <fragarc2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:46:18 by fragarc2          #+#    #+#             */
/*   Updated: 2025/03/24 13:44:46 by fragarc2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"


static void ft_putenv(t_env *env, char *var)
{
	int i;

	i = 0;
    while (env->env[i])
    {
        if (ft_strncmp(env->env[i], var, ft_strlen(var)) == 0)
        {
                env->env[i] = var;
            return ;
        }

    }
}

static void handle_cd_error(char *path)
{
    char    *error;
    char    *tmp;

    tmp = ft_strjoin("minishell: cd: ", path);
    error = ft_strjoin(tmp, "\n");
    free(tmp);
    write(1, error, ft_strlen(error));
    free(error);
}

static char *get_cd_path(char *path)
{
    char    *home;
    char    *old_pwd;

    if (!path || !*path)
    {
        home = getenv("HOME");
        return (home);
    }
    if (ft_strcmp(path, "-") == 0)
    {
        old_pwd = getenv("OLDPWD");
        return (old_pwd);
    }
    return (path);
}
static void update_pwd(t_env *pwd, char *old_pwd)
{
    char    new_pwd[MAX_PATH];
    char    *tmp;

    if (getcwd(new_pwd, MAX_PATH))
    {
        tmp = ft_strjoin("OLDPWD=", old_pwd);
        ft_putenv(pwd, tmp);
        free(tmp);
        tmp = ft_strjoin("PWD=", new_pwd);
        ft_putenv(pwd, tmp);
        free(tmp);
    }
    else
        perror("getcwd");
}

void    ft_cd(t_env *mini, char **args)
{
    char    old_pwd[MAX_PATH];
    char    *path;

    if (!getcwd(old_pwd, MAX_PATH))
        return (perror("getcwd"));
    path = get_cd_path(args[1]);
    if (!path)
        return ;
    if (chdir(path) != 0)
        handle_cd_error(path);
    else
        update_pwd(mini, old_pwd);
}
