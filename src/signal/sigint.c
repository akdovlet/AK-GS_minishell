/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:03:48 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/26 11:07:51 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_minishell.h"

// Ctrl-C (SIGINT) :
// Lorsque vous appuyez sur Ctrl-C, le terminal envoie un signal SIGINT au processus en cours d’exécution.
// Par défaut, la plupart des processus réagissent à SIGINT en s’arrêtant proprement (par exemple, en quittant le programme).
// Cependant, le comportement exact dépend du code du processus.