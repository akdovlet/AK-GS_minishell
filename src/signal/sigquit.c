/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigquit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:04:17 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/26 11:08:24 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_minishell.h"

// Ctrl-\ (SIGQUIT) :
// *Ctrl-* envoie un signal SIGQUIT au processus.
// Par défaut, cela provoque l’arrêt du processus et génère un fichier de vidage de cœur (core dump).
// Vous pouvez utiliser *Ctrl-* pour forcer l’arrêt d’un processus récalcitrant.