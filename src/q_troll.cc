#include "q_troll.h"

#include "cave.hpp"
#include "hooks.h"
#include "monster2.hpp"
#include "object2.hpp"
#include "util.hpp"

#include <cassert>

#define cquest (quest[QUEST_TROLL])

GENERATE_MONSTER_LOOKUP_FN(get_tom, "Tom the Stone Troll")
GENERATE_MONSTER_LOOKUP_FN(get_stone_troll, "Stone troll")
GENERATE_MONSTER_LOOKUP_FN(get_forest_troll, "Forest troll")

static bool_ quest_troll_gen_hook(void *, void *, void *)
{
	int x, y;
	int xstart = 2;
	int ystart = 2;

	if (p_ptr->inside_quest != QUEST_TROLL) return FALSE;

	/* Start with perm walls */
	for (y = 0; y < cur_hgt; y++)
	{
		for (x = 0; x < cur_wid; x++)
		{
			cave_set_feat(y, x, FEAT_PERM_SOLID);
		}
	}
	dun_level = quest[p_ptr->inside_quest].level;

	/* Set the correct monster hook */
	set_mon_num_hook();

	/* Prepare allocation table */
	get_mon_num_prep();

	init_flags = INIT_CREATE_DUNGEON;
	process_dungeon_file("trolls.map", &ystart, &xstart, cur_hgt, cur_wid, TRUE, TRUE);

	for (x = 3; x < xstart; x++)
		for (y = 3; y < ystart; y++)
		{
			if (cave[y][x].feat == FEAT_MARKER)
			{
				m_allow_special[get_tom()] = TRUE;
				int m_idx = place_monster_one(y, x, get_tom(), 0, FALSE, MSTATUS_ENEMY);
				m_allow_special[get_tom()] = FALSE;

				if (m_idx)
				{
					int o_idx;

					/* Get local object */
					object_type forge, *q_ptr = &forge;

					m_list[m_idx].mflag |= MFLAG_QUEST;

					a_allow_special[ART_GLAMDRING] = TRUE;

					/* Mega-Hack -- Prepare to make "Glamdring" */
					object_prep(q_ptr, lookup_kind(TV_SWORD, SV_BROAD_SWORD));

					/* Mega-Hack -- Mark this item as "Glamdring" */
					q_ptr->name1 = ART_GLAMDRING;

					/* Mega-Hack -- Actually create "Glamdring" */
					apply_magic(q_ptr, -1, TRUE, TRUE, TRUE);

					a_allow_special[ART_GLAMDRING] = FALSE;

					/* Get new object */
					o_idx = o_pop();

					if (o_idx)
					{
						/* Get the item */
						object_type *o_ptr = &o_list[o_idx];

						/* Structure copy */
						object_copy(o_ptr, q_ptr);

						/* Build a stack */
						o_ptr->next_o_idx = m_list[m_idx].hold_o_idx;

						o_ptr->held_m_idx = m_idx;
						o_ptr->ix = 0;
						o_ptr->iy = 0;

						m_list[m_idx].hold_o_idx = o_idx;
					}
					else
					{
						a_info[q_ptr->name1].cur_num = 0;
					}
				}
			}
		}

	/* Reinitialize the ambush ... hehehe */
	cquest.data[0] = FALSE;
	return TRUE;
}

static bool_ quest_troll_finish_hook(void *, void *in_, void *)
{
	struct hook_quest_finish_in *in = static_cast<struct hook_quest_finish_in *>(in_);
	s32b q_idx = in->q_idx;

	if (q_idx != QUEST_TROLL) return FALSE;

	c_put_str(TERM_YELLOW, "I heard about your noble deeds.", 8, 0);
	c_put_str(TERM_YELLOW, "Keep what you found... may it serve you well.", 9, 0);

	/* Continue the plot */
	*(quest[q_idx].plot) = QUEST_NAZGUL;
	quest[*(quest[q_idx].plot)].init(*(quest[q_idx].plot));

	del_hook_new(HOOK_QUEST_FINISH, quest_troll_finish_hook);
	process_hooks_restart = TRUE;

	return TRUE;
}

static bool_ quest_troll_death_hook(void *, void *in_, void *)
{
	struct hook_monster_death_in *in = static_cast<struct hook_monster_death_in *>(in_);
	s32b m_idx = in->m_idx;
	s32b r_idx = m_list[m_idx].r_idx;
	int x, y, xstart = 2, ystart = 2;

	if (p_ptr->inside_quest != QUEST_TROLL) return FALSE;

	if (r_idx == get_tom())
	{
		cave_set_feat(3, 3, FEAT_LESS);
		cave[3][3].special = 0;

		cmsg_print(TERM_YELLOW, "Without Tom, the trolls won't be able to do much.");
		cquest.status = QUEST_STATUS_COMPLETED;
		del_hook_new(HOOK_MONSTER_DEATH, quest_troll_death_hook);
		process_hooks_restart = TRUE;
		return (FALSE);
	}

	init_flags = INIT_GET_SIZE;
	process_dungeon_file("trolls.map", &ystart, &xstart, cur_hgt, cur_wid, TRUE, TRUE);

	if (cquest.data[0]) return FALSE;

	cquest.data[0] = TRUE;

	msg_print("Oops, seems like an ambush...");

	for (x = 3; x < xstart; x++)
		for (y = 3; y < ystart; y++)
		{
			cave_type *c_ptr = &cave[y][x];

			/* Ahah ! */
			if (c_ptr->info & CAVE_SPEC)
			{
				cave_set_feat(y, x, FEAT_GRASS);
				c_ptr->info &= ~CAVE_SPEC;

				int r_idx = (rand_int(2) == 0) ? get_forest_troll() : get_stone_troll();
				place_monster_one(y, x, r_idx, 0, FALSE, MSTATUS_ENEMY);
			}
		}

	return FALSE;
}

bool_ quest_troll_init_hook(int q_idx)
{
	if ((cquest.status >= QUEST_STATUS_TAKEN) && (cquest.status < QUEST_STATUS_FINISHED))
	{
		add_hook_new(HOOK_MONSTER_DEATH, quest_troll_death_hook,  "troll_death",  NULL);
		add_hook_new(HOOK_GEN_QUEST,     quest_troll_gen_hook,    "troll_gen",    NULL);
		add_hook_new(HOOK_QUEST_FINISH,  quest_troll_finish_hook, "troll_finish", NULL);
	}
	return (FALSE);
}
