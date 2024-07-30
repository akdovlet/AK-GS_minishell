/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:03:48 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/29 12:17:46 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_minishell.h"

// Ctrl-C (SIGINT) :
// Lorsque vous appuyez sur Ctrl-C, le terminal envoie un signal SIGINT au processus en cours d’exécution.
// Par défaut, la plupart des processus réagissent à SIGINT en s’arrêtant proprement (par exemple, en quittant le programme).
// Cependant, le comportement exact dépend du code du processus.

// dans le cas de readline juste clear la ligne et la renvoyer avec le code d'erreur 130
// dans un heredoc, juste clear la ligne et la renvoyer avec le code d'erreur 130

// bash-5.1$ cat <<EOF
// > bonjour
// > je mappelle gautier
// > 
// bash: warning: here-document at line 10 delimited by end-of-file (wanted `EOF')
// bonjour
// je mappelle gautier
// ctrl-d

// ctrl-c pas de message d'erreur

void	sigint_handler(int signum)
{
    if (signum == SIGINT || signum == SIGQUIT)
    {
        if (signum == SIGQUIT)
            signal(SIGQUIT, SIG_ING);
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        g_exit_status = 130;
    }
}
