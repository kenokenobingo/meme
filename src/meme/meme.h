/*
 *  meme.h
 *
 *  K E N O <win@kenokeno.bingo>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MM_MEME_H
#define MM_MEME_H

#include <alpm_list.h>

#define PACMAN_CALLER_PREFIX "MEME"

/* database.c */
int meme_database(alpm_list_t *targets);
/* deptest.c */
int meme_deptest(alpm_list_t *targets);
/* files.c */
int meme_files(alpm_list_t *files);
/* query.c */
int meme_query(alpm_list_t *targets);
/* remove.c */
int meme_remove(alpm_list_t *targets);
/* sync.c */
int memen_sync(alpm_list_t *targets);
int sync_prepare_execute(void);
/* upgrade.c */
int meme_upgrade(alpm_list_t *targets);

#endif /* MM_MEME_H */

/* vim: set noet: */
