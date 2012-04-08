-- Library quest in Minas Anor

-- Partially based on Fireproofing quest

library_quest = {}

-- Book creation helpers
library_quest.bookable_spells =
{
	MANATHRUST, DELCURSES,
	GLOBELIGHT, FIREGOLEM, FIREFLASH, FIREWALL,
	GEYSER, VAPOR, ENTPOTION,
	NOXIOUSCLOUD, POISONBLOOD,
	STONESKIN, DIG,
	RECHARGE, DISPERSEMAGIC,
	BLINK, DISARM, TELEPORT,
	SENSEMONSTERS, SENSEHIDDEN, REVEALWAYS, IDENTIFY, VISION,
	MAGELOCK, SLOWMONSTER, ESSENCESPEED,
	CHARM, CONFUSE, ARMOROFFEAR, STUN,
	GROWTREE, HEALING, RECOVERY,
	ERU_SEE, ERU_LISTEN,
	MANWE_BLESS, MANWE_SHIELD,
	YAVANNA_CHARM_ANIMAL, YAVANNA_GROW_GRASS, YAVANNA_TREE_ROOTS,
	TULKAS_AIM, TULKAS_SPIN,
	MELKOR_CURSE, MELKOR_CORPSE_EXPLOSION, DRAIN,
	AULE_FIREBRAND, AULE_CHILD,
	VARDA_LIGHT_VALINOR, VARDA_EVENSTAR,
	ULMO_BELEGAER, ULMO_WRATH,
	MANDOS_TEARS_LUTHIEN, MANDOS_TALE_DOOM
}

-- Print a spell (taken from s_aux)
function library_quest.print_spell(color, y, spl)
	local x, index, sch, size, s

	x = 0
	size = 0
	book = 255
	obj = nil

	-- Hack if the book is 255 it is a random book
	if book == 255 then
		school_book[book] = {spl}
	end

	-- Parse all spells
	for index, s in school_book[book] do
		local lvl, na = get_level_school(s, 50, -50)
		local xx, sch_str

		sch_str = spell_school_name(s)

		if s == spl then
			if na then
				c_prt(color, format("%-20s%-16s   %3s %4s %3d%s %s", spell(s).name, sch_str, na, get_mana(s), spell_chance(s), "%", __spell_info[s]()), y, x)
			else
				c_prt(color, format("%-20s%-16s   %3d %4s %3d%s %s", spell(s).name, sch_str, lvl, get_mana(s), spell_chance(s), "%", __spell_info[s]()), y, x)
			end
			y = y + 1
			size = size + 1
		end
	end
	return y
end
