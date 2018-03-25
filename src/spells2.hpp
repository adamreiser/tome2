#pragma once

#include "h-basic.h"
#include "monster_race_flag_set.hpp"
#include "object_filter.hpp"
#include "object_type_fwd.hpp"

void curse_artifact(object_type * o_ptr);
void grow_things(s16b type, int rad);
void grow_grass(int rad);
void grow_trees(int rad);
bool_ hp_player(int num);
bool_ heal_insanity(int val);
void warding_glyph();
void explosive_rune();
bool_ do_dec_stat(int stat, int mode);
bool_ do_res_stat(int stat, bool_ full);
bool_ do_inc_stat(int stat);
void identify_hooks(object_type *o_ptr);
bool_ identify_pack();
void identify_pack_fully();
bool_ remove_curse();
bool_ remove_all_curse();
bool_ restore_level();
bool_ lose_all_info();
bool_ detect_traps(int rad);
bool_ detect_doors(int rad);
bool_ detect_stairs(int rad);
bool_ detect_treasure(int rad);
bool detect_objects_gold(int rad);
bool detect_objects_normal(int rad);
bool_ detect_monsters_normal(int rad);
bool_ detect_monsters_invis(int rad);
void detect_monsters_orcs(int rad);
bool_ detect_all(int rad);
void stair_creation();
bool_ wall_stone(int y, int x);
bool_ enchant(object_type *o_ptr, int n, int eflag);
bool_ enchant_spell(int num_hit, int num_dam, int num_ac, int num_pval);
bool_ ident_spell();
bool_ ident_all();
bool_ identify_fully();
bool_ recharge(int num);
void aggravate_monsters(int who);
void genocide();
void mass_genocide();
void change_wild_mode();
bool_ banish_evil(int dist);
bool_ dispel_evil(int dam);
bool_ dispel_good(int dam);
void dispel_undead(int dam);
bool_ dispel_monsters(int dam);
void destroy_area(int y1, int x1, int r);
void earthquake(int cy, int cx, int r);
void lite_room(int y1, int x1);
void unlite_room(int y1, int x1);
void lite_area(int dam, int rad);
void unlite_area(int dam, int rad);
bool_ fire_cloud(int typ, int dir, int dam, int rad, int time);
bool_ fire_wave(int typ, int dir, int dam, int rad, int time, s32b eff);
bool_ fire_wall(int typ, int dir, int dam, int time);
bool_ fire_ball(int typ, int dir, int dam, int rad);
bool_ fire_bolt(int typ, int dir, int dam);
bool_ fire_beam(int typ, int dir, int dam);
void call_chaos();
bool_ fire_bolt_or_beam(int prob, int typ, int dir, int dam);
bool_ lite_line(int dir);
bool_ drain_life(int dir, int dam);
bool_ wall_to_mud(int dir);
bool_ wizard_lock(int dir);
bool_ slow_monster(int dir);
bool_ sleep_monster(int dir);
bool_ confuse_monster(int dir, int plev);
bool_ fear_monster(int dir, int plev);
bool_ poly_monster(int dir);
bool_ teleport_monster(int dir);
bool_ trap_creation();
bool_ destroy_doors_touch();
bool_ destroy_traps_touch();
bool_ sleep_monsters_touch();
bool_ alchemy();
void activate_ty_curse();
void activate_dg_curse();
void summon_cyber();
bool_ confuse_monsters(int dam);
bool_ charm_monsters(int dam);
bool_ charm_animals(int dam);
bool_ stun_monsters(int dam);
bool_ banish_monsters(int dist);
bool_ turn_monsters(int dam);
bool_ charm_monster(int dir, int plev);
bool_ control_one_undead(int dir, int plev);
bool_ charm_animal(int dir, int plev);
bool_ mindblast_monsters(int dam);
void alter_reality();
void report_magics();
void teleport_swap(int dir);
void swap_position(int lty, int ltx);
object_filter_t const &item_tester_hook_recharge();
bool_ project_hack(int typ, int dam);
void project_meteor(int radius, int typ, int dam, u32b flg);
object_filter_t const &item_tester_hook_artifactable();
bool_ passwall(int dir, bool_ safe);
bool_ project_hook(int typ, int dir, int dam, int flg);
bool_ reset_recall(bool_ no_trepas_max_depth);
void geomancy_random_wall(int y, int x);
void geomancy_random_floor(int y, int x, bool_ kill_wall);
void geomancy_dig(int oy, int ox, int dir, int length);
void channel_the_elements(int y, int x, int level);
void random_resistance(object_type *o_ptr, int specific);
