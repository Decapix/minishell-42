/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apesic <apesicstudent.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:34:49 by apesic            #+#    #+#             */
/*   Updated: 2025/05/17 10:34:51 by apesic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>

t_list *ft_lstnew(char *str)
{
    t_list *node;

    node = malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->str = str;
    node->next = NULL;
    return (node);
}

void ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list *last;

    if (!lst || !new)
        return;
    if (*lst == NULL)
    {
        *lst = new;
        return;
    }
    last = *lst;
    while (last->next)
        last = last->next;
    last->next = new;
}

void ft_lstclear(t_list **lst)
{
    t_list *tmp;

    if (!lst)
        return;
    while (*lst)
    {
        tmp = (*lst)->next;
        free((*lst)->str);
        free(*lst);
        *lst = tmp;
    }
}

// Recherche dans mini_env la valeur de la variable name, retourne NULL si non trouvée.
static char *env_get(t_env *mini_env, char *name)
{
    t_env *cur = mini_env;
    size_t len = ft_strlen(name);
    while (cur)
    {
        if (ft_strncmp(cur->var_name, name, len) == 0 && cur->var_name[len] == '\0')
            return cur->var;
        cur = cur->next_var;
    }
    return NULL;
}

// Crée un t_shell contenant une seule commande `export VAR=val` et l’appelle
static int call_export(t_env *mini_env, char *var, char *val)
{
    // Construire la chaîne "VAR=val"
    char *arg = malloc(ft_strlen(var) + 1 + ft_strlen(val) + 1);
    if (!arg) return 1;
    sprintf(arg, "%s=%s", var, val);

    // Construire la liste des tokens ["export", "VAR=val"]
    t_list *lst = ft_lstnew(ft_strdup("export"));
    ft_lstadd_back(&lst, ft_lstnew(arg));

    // Préparer la structure shell
    t_shell cmd = { .command = lst, .is_buildin = true };

    int ret = ft_export(mini_env, &cmd);

    // libération
    ft_lstclear(&lst);
    return ret;
}

int ft_cd(t_env *mini_env, t_shell *command)
{
    char *target;
    char cwd[PATH_MAX];
    char *home;
    t_list *args = command->command;

    // 1. Récupération de l'argument
    //    args->str == "cd", donc on passe au suivant
    if (args && args->next && args->next->str)
        target = args->next->str;
    else
    {
        home = env_get(mini_env, "HOME");
        if (!home)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return 1;
        }
        target = home;
    }

    // 1b. Cas spécial '-'
    if (ft_strncmp(target, "-", ft_strlen(target)) == 0)
    {
        char *old = env_get(mini_env, "OLDPWD");
        if (!old)
        {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return 1;
        }
        target = old;
        // On affiche la nouvelle cible comme bash le fait
        printf("%s\n", target);
    }

    // 2. Vérifier que target existe et est un répertoire
    struct stat sb;
    if (stat(target, &sb) != 0)
    {
        perror("cd");
        return 1;
    }
    if (!S_ISDIR(sb.st_mode))
    {
        fprintf(stderr, "cd: not a directory: %s\n", target);
        return 1;
    }

    // 3. Sauvegarder le pwd courant pour OLDPWD
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("getcwd");
        return 1;
    }

    // 4. Chdir
    if (chdir(target) != 0)
    {
        perror("cd");
        return 1;
    }

    // 5. Mettre à jour OLDPWD puis PWD
    if (call_export(mini_env, "OLDPWD", cwd) != 0)
        return 1;

    // récup nouveau pwd
    if (!getcwd(cwd, sizeof(cwd)))
    {
        perror("getcwd");
        return 1;
    }
    if (call_export(mini_env, "PWD", cwd) != 0)
        return 1;

    return 0;
}
