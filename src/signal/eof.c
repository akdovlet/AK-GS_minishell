/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eof.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gschwand <gschwand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 11:04:12 by gschwand          #+#    #+#             */
/*   Updated: 2024/07/26 11:08:11 by gschwand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_minishell.h"

// Ctrl-D (EOF) :
// Ctrl-D signifie End-Of-File (fin de fichier).
// Si vous appuyez sur Ctrl-D lors de la saisie, cela indique au processus que l’entrée est terminée.
// Si le processus lit l’entrée (par exemple, via scanf() ou fgets()), Ctrl-D provoque la fin de la saisie.
// Si le processus ne lit pas l’entrée, Ctrl-D peut être ignoré.