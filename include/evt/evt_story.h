// Story progress and story flags: names for the saved global work bytes (GSW, swByteGet/swByteSet)
// and the saved global flags (GSWF, swGet/swSet/swClear) that record what has happened in the game.
//
// Scripts use them through the EVT operand macros, C code passes them straight to the sw* functions:
//     IF_INT_EQUAL(GSWF(GSWF_GOR01_ULTRA_HAMMER_CHEST_OPENED), 0)    swGet(GSWF_GOR01_ULTRA_HAMMER_CHEST_OPENED)
//     SWITCH(GSW(GSW_STORY_PROGRESS)) CASE_LESS(STORY_STG1_00_PETAL_MEADOWS)
// Names carry the area and map code (docs/GLOSSARY.md) when a value belongs to one map. A few blocks
// are indexed by the code (base + offset); their base names end in _BASE. How each name was found,
// and the low-confidence ones, are listed in docs/NAME_PROVENANCE.md. Area-local values (LSW/LSWF)
// are reused by every map and are not named here.
#pragma once

// Story progress: the value of GSW(GSW_STORY_PROGRESS). Each value is a row of the event table in
// src/event.c (event id, English event name and map in the comment); the story only moves forward,
// so scripts compare it with CASE_LESS / IF_INT_GREATER_OR_EQUAL to pick what a map shows.
typedef enum StoryProgress {
    STORY_STG0_00_PROLOGUE = 0,                   // "Prologue" (aaa_00)
    STORY_STG0_01_PLAZA = 1,                      // "Plaza" (aaa_00)
    STORY_STG0_02_MARIOS_HOUSE = 2,               // "Mario's House" (aaa_00)
    STORY_STG0_03_TO_ROGUEPORT = 3,               // "To Rogueport" (sys_01); "Rogueport (Arrival)" (gor_00)
    STORY_STG0_04_GOOMBELLA_ASSAULTED = 4,        // "Goombella Assaulted" (gor_00)
    STORY_STG0_05_1000_X_NAUTS_BEFORE = 5,        // "1000 X-Nauts (Before)" (gor_00)
    STORY_STG0_06_1000_X_NAUTS_AFTER = 6,         // "1000 X-Nauts (After)" (gor_00)
    STORY_STG0_07_GOOMBELLA_JOINS = 7,            // "Goombella Joins" (gor_01)
    STORY_STG0_08_STOLEN_COINS = 8,               // "Stolen Coins" (gor_02)
    STORY_STG0_09_PROF_FRANKLY = 9,               // "Prof. Frankly" (gor_02)
    STORY_STG0_10_REMOVING_THE_FENCE = 10,        // "Removing the Fence" (gor_02)
    STORY_STG0_10_01_FRANKLYS_TUTORIAL = 11,      // "Frankly's Tutorial" (gor_02)
    STORY_STG0_11_3_GOOMBA_GOONS = 12,            // "3 Goomba Goons" (tik_01)
    STORY_STG0_12_PUNI_ENCOUNTER = 13,            // "Puni Encounter" (tik_04)
    STORY_STG0_12_01_PAPER_STAIR_SWITCH = 14,     // "Paper Stair Switch" (tik_04)
    STORY_STG0_12_02_PAPER_MAGE_1 = 15,           // "Paper Mage 1" (tik_19)
    STORY_STG0_13_FIRST_FLIGHT = 16,              // "First Flight" (tik_04); "Thousand-Year Door" (tik_05)
    STORY_STG0_14_FRONT_OF_THE_PEDESTAL = 17,     // "Front of the Pedestal" (tik_05)
    STORY_STG0_15_THE_PEDESTAL = 18,              // "The Pedestal" (tik_05)
    STORY_STG0_16_FRANKLYS_HOUSE = 19,            // "Frankly's House" (gor_02)
    STORY_STG0_17_BADGE_TUTORIAL = 20,            // "Badge Tutorial" (gor_02)
    STORY_STG0_19_BLOOPER_BATTLE = 21,            // "Blooper Battle" (tik_02)
    STORY_STG0_END_TO_STAGE_1 = 22,               // "To Stage 1" (tik_02)
    STORY_STG1_00_PETAL_MEADOWS = 23,             // "Petal Meadows" (sys_01)
    STORY_STG1_00_01_THE_SHADOW_OF_HOOKTAIL = 24, // "The Shadow of Hooktail" (hei_00)
    STORY_STG1_01_THE_FLIP_BRIDGE = 25,           // "The Flip-Bridge" (hei_01)
    STORY_STG1_01A_PETALBURG_1ST_TIME = 26,       // "Petalburg (1st Time)" (nok_00)
    STORY_STG1_02_TALKING_WITH_KROOP = 27,        // "Talking with Kroop" (nok_01)
    STORY_STG1_03_PETALBURG_GATEKEEPER = 28,      // "Petalburg Gatekeeper" (nok_01)
    STORY_STG1_04_BALD_CLEFT = 29,                // "Bald Cleft" (hei_03)
    STORY_STG1_05_BRISTLE = 30,                   // "Bristle" (hei_05)
    STORY_STG1_06_QUIZ = 31,                      // "Quiz" (hei_07)
    STORY_STG1_06_01_GOLD_FUZZY = 32,             // "Gold Fuzzy" (hei_10)
    STORY_STG1_07_KOOPS_JOINS = 33,               // "Koops Joins" (hei_01)
    STORY_STG1_08_OPENING_THE_PATH = 34,          // "Opening the Path" (hei_00)
    STORY_STG1_09_HOOKTAIL_CASTLE = 35,           // "Hooktail Castle" (gon_01)
    STORY_STG1_09_01_KEY = 36,                    // "Key" (gon_01)
    STORY_STG1_09_02_LOCK = 37,                   // "Lock" (gon_01)
    STORY_STG1_10_FATHERS_LETTER = 38,            // "Father's Letter" (gon_03)
    STORY_STG1_11_1000_DRY_BONES = 39,            // "1000 Dry Bones" (gon_03)
    STORY_STG1_12_PAPER_STAIRS = 40,              // "Paper Stairs" (gon_04)
    STORY_STG1_12_01_KEY = 41,                    // "Key" (gon_04)
    STORY_STG1_12_02_LOCK = 42,                   // "Lock" (gon_04)
    STORY_STG1_13_A_SUSPICIOUS_ROOM = 43,         // "A Suspicious Room" (gon_07)
    STORY_STG1_13_01_50_SECONDS_TO_ESCAPE = 44,   // "50 Seconds to Escape" (gon_06)
    STORY_STG1_13_01_01_PAPER_MAGE_2 = 45,        // "Paper Mage 2" (gon_06)
    STORY_STG1_13_02_KEY_2 = 46,                  // "Key 2" (gon_03)
    STORY_STG1_13_03_LOCK_2 = 47,                 // "Lock 2" (gon_05)
    STORY_STG1_14_PAPER_BRIDGE_RIGHT = 48,        // "Paper Bridge (Right)" (gon_04)
    STORY_STG1_14_01_PAPER_BRIDGE_LEFT = 49,      // "Paper Bridge (Left)" (gon_04)
    STORY_STG1_15_MS_MOWZ = 50,                   // "Ms. Mowz (w/Goombella)" (gon_12); "Ms. Mowz (w/Koops)" (gon_12)
    STORY_STG1_15_01_KEY_3 = 51,                  // "Key 3" (gon_12)
    STORY_STG1_15_02_LOCK_3 = 52,                 // "Lock 3" (gon_08)
    STORY_STG1_15_03_KEY_4 = 53,                  // "Key 4" (gon_05)
    STORY_STG1_15_04_LOCK_4 = 54,                 // "Lock 4" (gon_05)
    STORY_STG1_16_HOOKTAIL = 55,                  // "Hooktail" (gon_11); "Hooktail Defeated" (gon_11)
    STORY_STG1_17_FATHER_AND_SON_REUNITED = 56,   // "Father & Son Reunited" (gon_11)
    STORY_STG1_18_PEACH_CAUGHT = 57,              // "Peach: Caught" (aji_10)
    STORY_STG1_18_01_PEACH_AN_OPEN_DOOR = 58,     // "Peach: An Open Door" (aji_16)
    STORY_STG1_19_PEACH_TEC = 59,                 // "Peach: TEC" (aji_17)
    // "Bowser: Bowser Castle" (kpa_00); "Bowser: Entrance" (kpa_01)
    STORY_STG1_19_01_BOWSER_CASTLE = 60,
    // "Bowser: Castle INT." (kpa_01); "Bowser: Kammy Enters" (kpa_01); "Bowser: Departure" (kpa_00)
    STORY_STG1_19_02_BOWSER_CASTLE_INTERIOR = 61,
    STORY_STG1_20_KOOPS_LEAVES = 62,              // "Koops Leaves" (nok_01)
    STORY_STG1_21_A_MAIL_FROM_PEACH = 63,         // "A Mail from Peach" (hei_01)
    STORY_STG1_30_ZESS_T = 64,                    // "Zess T." (gor_01); "Thousand-Year Door" (tik_05)
    STORY_STG1_31_FRANKLYS_HOUSE = 65,            // "Frankly's House Stg.1" (gor_02)
    STORY_STG1_32_PUNI_ENCOUNTER_2 = 66,          // "Puni Encounter 2" (tik_04)
    STORY_STG1_33_A_PUNI_PLEA_FOR_HELP = 67,      // "A Puni Plea for Help" (tik_03)
    STORY_STG1_34_PUNIS_SECRET_PASSAGE = 68,      // "Puni's Secret Passage" (tik_03)
    STORY_STG1_35_PUNI_JOINS = 69,                // "Puni Joins" (tik_03)
    STORY_STG1_END_TO_STAGE_2 = 70,               // "To Stage 2" (tik_03)
    STORY_STG2_00_BOGGLY_WOODS = 71,              // "Boggly Woods" (sys_01)
    STORY_STG2_01_A_SIREN_ARGUMENT = 72,          // "A Siren Argument" (win_00)
    STORY_STG2_02_TO_THE_GREAT_TREE = 73,         // "To The Great Tree" (win_01)
    STORY_STG2_03_THE_GREAT_TREE = 74,            // "The Great Tree" (mri_00)
    STORY_STG2_03_01_SEALED_ENTRANCE = 75,        // "Sealed Entrance" (mri_00)
    STORY_STG2_03_02_SEALED_ENTRANCE_2 = 76,      // "Sealed Entrance 2" (mri_00)
    STORY_STG2_03_03_FLURRIE_INTRO = 77,          // "Flurrie Intro" (win_03)
    STORY_STG2_03_04_SHES_LOST_HER_PRECIOUS = 78, // "She's Lost Her Precious" (win_03)
    STORY_STG2_03_05_TO_FLURRIES_PLACE = 79,      // "To Flurrie's Place" (win_01)
    STORY_STG2_04_PLANE_PANEL = 80,               // "Extending Plane Panel" (win_02); "The Trail" (win_03)
    STORY_STG2_05_A_SHY_FLURRIE = 81,             // "A Shy Flurrie" (win_04)
    STORY_STG2_05_01_FLURRIE_LIVING_ROOM = 82,    // "Flurrie: Living Room" (win_04)
    STORY_STG2_05_02_FLURRIE_REQUEST = 83,        // "Flurrie: Request" (win_04)
    STORY_STG2_06_THE_SKETCH = 84,                // "The Sketch" (win_00)
    STORY_STG2_07_MARIO_VS_SHADOW_SIRENS = 85,    // "Mario vs. Shadow Sirens" (win_00)
    STORY_STG2_08_SHADOW_SIRENS_LOSE = 86,        // "Shadow Sirens Lose" (win_00)
    STORY_STG2_09_FLURRIE_JOINS = 87,             // "Flurrie Joins" (win_04)
    STORY_STG2_10_SECRET_ENTRANCE_REVEALED = 88,  // "Secret Entrance Revealed!" (mri_00)
    STORY_STG2_11_X_NAUT_BATTLE = 89,             // "X-Naut Battle" (mri_01)
    STORY_STG2_12_RIVAL_ARRIVAL = 90,             // "Rival Arrival" (mri_01)
    STORY_STG2_12_01_A_DARK_FIGURE = 91,          // "A Dark Figure" (mri_04)
    STORY_STG2_12_02_PUNI_ELDER_IMPRISONED = 92,  // "Puni Elder Imprisoned" (mri_03)
    STORY_STG2_13_MS_MOWZ = 93,                   // "Ms. Mowz" (mri_04)
    STORY_STG2_14_PUNI_ELDER_FREED = 94,          // "Puni Elder Freed" (mri_03)
    STORY_STG2_15_11_PUNIES = 95,                 // "11 Punies" (mri_01)
    // "The Puni Elder's Powers" (mri_01); "Puni Switch" (mri_02)
    STORY_STG2_16_PUNI_ELDER_POWERS = 96,
    // "Bubbles" (mri_05); "By Plane?" (mri_19); "Jabbi Encounter" (mri_06)
    STORY_STG2_17_BUBBLES = 97,
    // "Jabble" (mri_07); "Punies vs. Jabbies" (mri_08); "Blue Key Obtained" (mri_09)
    STORY_STG2_18_JABBLE = 98,
    STORY_STG2_19_INSIDE_THE_BLUE_CELL = 99,        // "Inside the Blue Cell" (mri_03)
    STORY_STG2_19_01_PUNIO_AND_PETUNI_BEFORE = 100, // "Punio & Petuni(Before)" (mri_03)
    STORY_STG2_20_PUNIO_AND_PETUNI = 101,           // "Punio & Petuni" (mri_03)
    // "Bubbles 2" (mri_05); "Punies vs. Jabbies 2" (mri_11); "Trapped" (mri_17)
    STORY_STG2_21_PUNIES_VS_JABBIES_2 = 102,
    STORY_STG2_21_01_MYSTERY_PILLAR = 103,        // "Mystery Pillar" (mri_17)
    STORY_STG2_21_02_MATCHING_THE_PATTERNS = 104, // "Matching the Patterns" (mri_09)
    STORY_STG2_21_03_SUPER_BOOTS = 105,           // "Super Boots" (mri_10)
    STORY_STG2_21_04_ESCAPE = 106,                // "Escape" (mri_17)
    STORY_STG2_21_06_WATER_SWITCH = 107,          // "Water Switch" (mri_16); "The 101 Puni Switch" (mri_13)
    STORY_STG2_22_LORD_CRUMP_APPEARS = 108,       // "Lord Crump Appears" (mri_14)
    STORY_STG2_23_TIME_BOMB_ACTIVATED = 109,      // "Time Bomb Activated" (mri_14)
    STORY_STG2_23_01_X_NAUT_BATTLE = 110,         // "X-Naut Battle" (mri_15)
    STORY_STG2_24_BOSS_BATTLE = 111,              // "Boss Battle" (mri_01)
    STORY_STG2_25_AFTER_THE_BOSS_BATTLE = 112,    // "After the Boss Battle" (mri_01)
    // "Peach: Crump & X-Nauts" (aji_10); "Peach: An Open Door 2" (aji_16)
    STORY_STG2_25_01_PEACH_CRUMP_AND_X_NAUTS = 113,
    STORY_STG2_25_02_PEACH_SHALL_WE_DANCE = 114, // "Peach: Shall We Dance?" (aji_17)
    STORY_STG2_25_03_BOWSER_MEADOWS = 115,       // "Bowser: Meadows" (hei_00)
    STORY_STG2_25_04_BOWSER_ACTION_STAGE = 116,  // "Bowser: Action Stage" (kpa_02)
    STORY_STG2_25_05_BOWSER_PETALBURG = 117,     // "Bowser: Petalburg" (nok_00)
    STORY_STG2_26_PRAISE_FROM_THE_PUNI = 118,    // "Praise from the Puni" (mri_00)
    STORY_STG2_27_A_MAIL_FROM_PEACH = 119,       // "A Mail from Peach" (win_01)
    STORY_STG2_40_THOUSAND_YEAR_DOOR = 120,      // "Thousand-Year Door" (tik_05)
    STORY_STG2_41_FRANKLYS_HOUSE = 121,          // "Frankly's House Stg.2" (gor_02)
    // "Finding Don Pianta" (gor_02); "Backdoor" (gor_03); "Mafia Boss" (gor_03)
    STORY_STG2_44_FINDING_DON_PIANTA = 122,
    STORY_STG2_45_DAUGHTER_LOCATED = 123,         // "Daughter Located" (gor_00)
    STORY_STG2_46_BLIMP_TICKET = 124,             // "Blimp Ticket" (gor_03)
    STORY_STG2_47_AFTER_GETTING_THE_TICKET = 125, // "After Getting the Ticket" (gor_03)
    STORY_STG2_END_TO_GLITZVILLE = 126,           // "To Glitzville" (gor_04)
    STORY_STG3_00_WELCOME_TO_GLITZVILLE = 127,    // "Welcome to Glitzville" (tou_20)
    STORY_STG3_01_ARENA_INTRO = 128,              // "Arena Intro (1F)" (tou_03); "Arena Intro (2F)" (tou_03)
    STORY_STG3_02_THE_GUARD_BACKS_OFF = 129,      // "The Guard Backs Off" (tou_02)
    STORY_STG3_03_GRUBBA = 130,                   // "Grubba" (tou_05)
    STORY_STG3_04_GONZALES_IS_BORN = 131,         // "Gonzales is Born" (tou_05)
    STORY_STG3_05_MATCH = 132,                    // "Match" (tou_10)
    STORY_STG3_06_1ST_MATCH = 133,                // "1st Match" (tou_03)
    // "Minors - 9th Pl." (tou_10); "Minors - 8th Pl." (tou_10); "Minors - 7th Pl." (tou_10); "Minors - 6th Pl." (tou_10)
    STORY_STG3_07_MINORS_9TH_TO_6TH = 134,
    STORY_STG3_10_MINORS_5TH_PL_EGG = 135, // "Minors - 5th Pl. (Egg)" (tou_01)
    STORY_STG3_11_RUNAWAY_EGG = 136,       // "Runaway Egg" (tou_01)
    // "The Mini-Yoshi Egg" (tou_01); "Minors - 4th Pl." (tou_10); "Minors - 3rd Pl." (tou_10); "Minors - 2nd Place" (tou_10); "Minors - 1st Pl. (Iron)" (tou_10); "Minors - 1st Pl. (Iron 2)" (tou_10)
    STORY_STG3_12_MINI_YOSHI_EGG = 137,
    // "Majors - 10th Place" (tou_08); "Majors - 9th Place" (tou_08)
    STORY_STG3_20_MAJORS_10TH = 138,
    STORY_STG3_20_00_MAJORS_8TH_PLACE = 139,   // "Majors - 8th Place" (tou_08)
    STORY_STG3_20_01_SUPER_HAMMER = 140,       // "Super Hammer" (tou_01)
    STORY_STG3_20_02_BACK_TO_THE_MINORS = 141, // "Back to the Minors" (tou_04)
    STORY_STG3_20_03_THE_YELLOW_BLOCK = 142,   // "The Yellow Block" (tou_10)
    // "Confiscated" (tou_10); "Majors - 7th Pl.(Raid/Cake)" (tou_08); "Majors - 6th Pl.(Bowser)" (tou_08); "Majors - 5th Pl." (tou_08)
    STORY_STG3_20_04_CONFISCATED = 143,
    STORY_STG3_20_05_MAJORS_4TH_PL = 144,            // "Majors - 4th Pl." (tou_08)
    STORY_STG3_20_06_RAWK_HAWKS_WARNING = 145,       // "Rawk Hawk's Warning" (tou_04)
    STORY_STG3_20_07_STORAGE_KEY = 146,              // "Storage Key" (tou_01)
    STORY_STG3_20_07_00_STORAGE_ROOM_UNLOCKED = 147, // "Storage Room Unlocked" (tou_04)
    STORY_STG3_20_08_MS_MOWZ = 148,                  // "Ms. Mowz" (tou_06)
    STORY_STG3_20_09_BLOWING_CONTAINERS = 149,       // "Blowing Containers" (tou_06)
    STORY_STG3_20_10_HIDDEN_STAIRWAY = 150,          // "Hidden Stairway" (tou_06)
    STORY_STG3_20_11_HOLE_IN_THE_FLOOR = 151,        // "Hole in the Floor" (tou_06)
    // "Jolene's Secret" (tou_05); "Majors - 3rd Pl.(Poison)" (tou_08); "Majors - 2nd Pl." (tou_08)
    STORY_STG3_20_12_JOLENES_SECRET = 152,
    STORY_STG3_20_13_MAJORS_1ST_PL = 153,         // "Majors - 1st Pl." (tou_08)
    STORY_STG3_20_14_LOBBY_POSTER = 154,          // "Lobby Poster" (tou_02)
    STORY_STG3_20_15_UNLOCKING_THE_DOOR = 155,    // "Unlocking the Door" (tou_06)
    STORY_STG3_20_16_FLATTENED = 156,             // "Flattened" (tou_12)
    STORY_STG3_21_1ST_MATCH_WITH_RAWK_HAWK = 157, // "1st Match with Rawk Hawk" (tou_08)
    STORY_STG3_30_NEW_CHAMPION = 158,             // "A New Champion" (tou_08); "Champion's Room" (tou_07)
    STORY_STG3_30_01_AIR_DUCT_ENTRANCE = 159,     // "Air Duct Entrance" (tou_07)
    STORY_STG3_30_02_AIR_DUCT_1ST_TIME = 160,     // "Air Duct (1st Time)" (tou_13)
    STORY_STG3_30_03_EAVESDROPPING = 161,         // "Eavesdropping" (tou_13)
    STORY_STG3_30_04_AIR_DUCT_EXIT = 162,         // "Air Duct Exit" (tou_13)
    STORY_STG3_31_GRUBBAS_PLANS = 163,            // "Grubba's Plans" (tou_05)
    STORY_STG3_32_BOSS_BATTLE = 164,              // "Boss Battle" (tou_03)
    STORY_STG3_33_PEACH_THE_SECRET_WEAPON = 165,  // "Peach: The Secret Weapon" (aji_10)
    STORY_STG3_33_01_PEACH_TECS_REQUEST = 166,    // "Peach: TEC's Request" (aji_17)
    STORY_STG3_33_02_PEACH_INCOGNITO = 167,       // "Peach: Incognito" (aji_09)
    STORY_STG3_33_03_PEACH_GRODUS = 168,          // "Peach: Grodus" (aji_10)
    STORY_STG3_33_04_PEACH_BACK_TO_TEC = 169,     // "Peach: Back to TEC" (aji_17)
    STORY_STG3_33_05_BOWSER_THE_GREAT_TREE = 170, // "Bowser: The Great Tree" (mri_01)
    // "Bowser: Treasure?" (mri_01); "Bowser: Puni Elder" (mri_01)
    STORY_STG3_33_06_BOWSER_PUNI_ELDER = 171,
    STORY_STG3_34_RETURN_TO_ROGUEPORT = 172,           // "Return to Rogueport" (tou_02)
    STORY_STG3_35_A_MAIL_FROM_PEACH = 173,             // "A Mail from Peach" (gor_03)
    STORY_STG3_50_THOUSAND_YEAR_DOOR = 174,            // "Thousand-Year Door" (tik_05)
    STORY_STG3_51_FRANKLYS_HOUSE = 175,                // "Frankly's House Stg.3" (gor_02)
    STORY_STG3_52_DARKLY = 176,                        // "Darkly" (gor_02)
    STORY_STG3_END_TO_STAGE_4 = 177,                   // "To Stage 4" (tik_07)
    STORY_STG4_00_WELCOME_TO_STAGE_4 = 178,            // "Welcome to Stage 4" (sys_01)
    STORY_STG4_01_00_GATEKEEPER_CONVERSATION = 179,    // "Gatekeeper Conversation" (usu_01)
    STORY_STG4_01_THE_MAYORS_A_PIG = 180,              // "The Mayor's a Pig!" (usu_00)
    STORY_STG4_02_DINGE = 181,                         // "Dinge" (usu_01)
    STORY_STG4_02_02_THE_GATEKEEPERS_A_PIG = 182,      // "The Gatekeeper's a Pig!" (usu_01)
    STORY_STG4_02_03_OPENING_THE_GATE = 183,           // "Opening the Gate" (usu_01)
    STORY_STG4_03_SHOP_KEY = 184,                      // "Shop Key" (gra_02)
    STORY_STG4_04_STORAGE_ROOM_UNLOCKED = 185,         // "Storage Room Unlocked" (usu_01)
    STORY_STG4_04_01_PAPER_MAGE_TUBE_MOD = 187,        // "Paper Mage (Tube Mod)" (usu_01)
    STORY_STG4_05_STRAW_TEPEE = 188,                   // "Straw Tepee" (gra_02)
    STORY_STG4_06_TREE_TRUNK = 189,                    // "Tree Trunk" (gra_04)
    STORY_STG4_06_01_BLOW_THE_FLOOR = 190,             // "Blow the Floor" (gra_05)
    STORY_STG4_06_02_THROUGH_THE_HOLE = 191,           // "Through the Hole" (gra_05)
    STORY_STG4_07_TRICK_ROCK = 192,                    // "Trick Rock" (gra_05)
    STORY_STG4_08_STEEPLE_DEMO_EXT = 193,              // "Steeple Demo (EXT.)" (gra_06)
    STORY_STG4_09_STEEPLE_DEMO_INT = 194,              // "Steeple Demo (INT.)" (jin_00)
    STORY_STG4_09_01_PUSH_THE_STATUE = 195,            // "Push the Statue" (jin_00)
    STORY_STG4_09_02_BOO_BOX = 196,                    // "Boo Box" (jin_07)
    STORY_STG4_09_03_1000_BOOS = 197,                  // "1000 Boos" (jin_00)
    STORY_STG4_09_04_KEY = 198,                        // "Key" (jin_00)
    STORY_STG4_09_05_LOCK = 199,                       // "Lock" (jin_00)
    STORY_STG4_10_DOOPLISS_BATTLE = 200,               // "Doopliss Battle" (jin_04)
    STORY_STG4_10_02_TRADING_PLACES = 201,             // "Trading Places" (jin_04)
    STORY_STG4_11_SUPERBOMBBOMB_LOST = 202,            // "Superbombbomb Lost" (usu_00)
    STORY_STG4_11_02_WAITING_DOOPLISS = 203,           // "Waiting Doopliss" (gra_00)
    STORY_STG4_12_VIVIAN = 204,                        // "Vivian" (usu_00)
    STORY_STG4_12_01_SUPERBOMBBOMB_FOUND = 205,        // "Superbombbomb Found" (usu_00)
    STORY_STG4_13_VIVIAN_JOINS = 206,                  // "Vivian Joins" (usu_00)
    STORY_STG4_13_02_WAITING_DOOPLISS_2 = 207,         // "Waiting Doopliss 2" (gra_00)
    STORY_STG4_13_03_BREAKING_THE_FLOOR = 208,         // "Breaking the Floor" (jin_11)
    STORY_STG4_13_04_THE_LETTER_P = 209,               // "The Letter p" (jin_08)
    STORY_STG4_14_NAME_GUESSING = 210,                 // "Name Guessing" (gra_00)
    STORY_STG4_15_DOOPLISS_BATTLE_2 = 211,             // "Doopliss Battle 2" (jin_04)
    STORY_STG4_15_02_BACK_TO_NORMAL = 212,             // "Back to Normal" (jin_04)
    STORY_STG4_15_03_THE_RUBY_STAR = 213,              // "The Ruby Star" (jin_04)
    STORY_STG4_15_04_SHADOW_SIRENS_AND_DOOPLISS = 214, // "Shadow Sirens & Doopliss" (usu_00)
    // "Peach: X-Naut PhD Report" (aji_10); "Peach: TEC's Quiz" (aji_17)
    STORY_STG4_15_05_PEACH_X_NAUT_PHD_REPORT = 215,
    STORY_STG4_15_06_BOWSER_BLIMP = 216,          // "Bowser: Blimp Area" (gor_04); "Bowser: Flying" (tou_00)
    STORY_STG4_15_07_BOWSER_ACTION_STAGE = 217,   // "Bowser: Action Stage" (kpa_03)
    STORY_STG4_15_08_BOWSER_ROGUEPORT_DOCK = 218, // "Bowser: Rogueport Dock" (gor_00)
    STORY_STG4_16_LEAVING_TWILIGHT_TOWN = 219,    // "Leaving Twilight Town" (usu_00)
    STORY_STG4_17_A_MAIL_FROM_PEACH = 220,        // "A Mail from Peach" (tik_07)
    STORY_STG4_30_THOUSAND_YEAR_DOOR = 221,       // "Thousand-Year Door" (tik_05)
    STORY_STG4_31_FRANKLYS_HOUSE = 222,           // "Frankly's House Stg.4" (gor_02)
    STORY_STG4_32_CHATTING_WITH_FLAVIO = 223,     // "Chatting with Flavio" (gor_01)
    STORY_STG4_33_MEET_BOBBERY = 224,             // "Meet Bobbery" (gor_00)
    STORY_STG4_34_BOBBERY_DECLINES = 225,         // "Bobbery Declines" (gor_02)
    STORY_STG4_35_ADVICE_FROM_PODLEY = 226,       // "Advice from Podley" (gor_01)
    STORY_STG4_36_BOBBERYS_DECISION = 227,        // "Bobbery's Decision" (gor_02)
    STORY_STG4_37_TO_THE_PORT = 228,              // "To the Port" (gor_02)
    STORY_STG4_END_OFF_TO_THE_KEYS = 229,         // "Off to the Keys" (gor_00)
    STORY_STG5_00_LOGBOOK = 230,                  // "Logbook" (sys_01)
    STORY_STG5_10_HAUNTED = 231,                  // "Haunted" (muj_20)
    STORY_STG5_11_DESERTED_ISLAND = 232,          // "Deserted Island" (muj_00)
    // "Flavio & Pa-Patch" (muj_01); "Flavio's Favor" (muj_01)
    STORY_STG5_12_FLAVIO_AND_PA_PATCH = 233,
    STORY_STG5_13_BOBBERY_AND_THE_BRIDGE = 234, // "Bobbery & the Bridge" (muj_04)
    // "Runaway Sailors" (muj_03); "Flavio's Rescue Plan" (muj_01); "Saving Bobbery" (muj_05)
    STORY_STG5_15_RUNAWAY_SAILORS = 235,
    STORY_STG5_16_FLAVIOS_WINE = 236,       // "Flavio's Wine" (muj_01)
    STORY_STG5_17_WINE_OBTAINED = 237,      // "Wine Obtained" (muj_01)
    STORY_STG5_18_BOBBERY_RESCUE_2 = 238,   // "Bobbery Rescue 2" (muj_05)
    STORY_STG5_18_01_BOBBERY_JOINS = 239,   // "Bobbery Joins" (muj_05)
    STORY_STG5_18_02_FLAVIOS_FAVOR_2 = 240, // "Flavio's Favor 2" (muj_01)
    STORY_STG5_18_03_MARCOS_JEWEL = 241,    // "Marco's Jewel" (muj_05)
    // "Gems and Jingles" (muj_05); "The Skull Rock" (muj_05); "Skull Rock Blast" (muj_05)
    STORY_STG5_19_SKULL_ROCK = 242,
    STORY_STG5_19_01_ENTERING_THE_GROTTO = 243, // "Entering the Grotto" (dou_00)
    // "The Call of Cortez" (dou_01); "Spikes (Floor)" (dou_02)
    STORY_STG5_19_02_CALL_OF_CORTEZ = 244,
    STORY_STG5_20_THE_BLUE_BLOCK = 245, // "The Blue Block" (dou_05)
    // "Grotto Key" (dou_04); "Spikes (Wall)" (dou_10); "Ship Hole" (dou_09); "Paper Mage 4" (dou_07)
    STORY_STG5_21_GROTTO_KEY = 246,
    STORY_STG5_21_01_BOAT_MOD_OBTAINED = 247, // "Boat Mod Obtained" (dou_07)
    STORY_STG5_22_FLOODGATE = 248,            // "Floodgate Handle" (dou_02); "Floodgate" (dou_03)
    STORY_STG5_29_WAVE_DODGING = 249,         // "Wave-dodging" (dou_10)
    // "Shipwrecked Sailors" (dou_11); "Switch Test" (dou_11); "Thankful Sailors" (dou_11)
    STORY_STG5_30_SHIPWRECKED_SAILORS = 250,
    STORY_STG5_31_FOUR_EYES = 251,               // "Four-Eyes" (muj_10)
    STORY_STG5_32_CORTEZS_WARNING = 252,         // "Cortez's Warning" (muj_11)
    STORY_STG5_33_CORTEZ_AND_THE_TREASURE = 253, // "Cortez and the Treasure" (muj_12)
    STORY_STG5_34_KICKED_OFF = 254,              // "Kicked Off" (muj_10)
    STORY_STG5_35_ESCAPE_ROUTE = 255,            // "Escape Route" (dou_11)
    STORY_STG5_36_HOLE_IN_THE_WALL = 256,        // "Hole in the Wall" (dou_11)
    STORY_STG5_40_TRUE_IDENTITY = 257,           // "True Identity" (muj_00)
    // "Return to the Grotto" (muj_00); "Flavio Makes a Deal" (muj_12)
    STORY_STG5_41_RETURN_TO_THE_GROTTO = 258,
    STORY_STG5_41_01_ALL_ABOARD = 259,        // "All Aboard" (muj_10)
    STORY_STG5_42_PIRATES_VS_X_NAUTS = 260,   // "Pirates vs. X-Nauts" (muj_00)
    STORY_STG5_43_X_NAUTS_RETREAT = 261,      // "X-Nauts Retreat" (muj_00)
    STORY_STG5_44_PEACH_TECS_REQUEST_2 = 262, // "Peach: TEC's Request 2" (aji_10)
    STORY_STG5_45_PEACH_POTION_PUZZLE = 263,  // "Peach: Potion Puzzle" (aji_06)
    STORY_STG5_46_PEACH_DISK_SEARCH = 264,    // "Peach: Disk Search" (aji_11)
    STORY_STG5_47_PEACH_TEC_TALK = 265,       // "Peach: TEC Talk" (aji_17)
    STORY_STG5_48_BOWSER_TWILIGHT_TOWN = 266, // "Bowser: Twilight Town" (usu_00)
    // "Bowser: Twilight Town 2" (usu_00); "Bowser: Bowser vs. X-Nauts" (usu_00)
    STORY_STG5_49_BOWSER_TWILIGHT_TOWN_2 = 267,
    STORY_STG5_58_FAIR_WINDS = 268,           // "Fair Winds!" (muj_00)
    STORY_STG5_59_ROGUEPORT_DOCK = 269,       // "Rogueport Dock" (gor_00)
    STORY_STG5_59_01_A_MAIL_FROM_PEACH = 270, // "A Mail from Peach" (gor_00)
    // "Return to Keelhaul" (gor_00); "Thousand-Year Door" (tik_05)
    STORY_STG5_60_RETURN_TO_KEELHAUL = 271,
    STORY_STG5_61_FRANKLYS_HOUSE = 272,           // "Frankly's House Stg.5" (gor_02)
    STORY_STG5_62_AN_ILL_DON_PIANTA = 273,        // "An Ill Don Pianta" (gor_03)
    STORY_STG5_63_KEELHAUL_ANYTIME = 274,         // "Keelhaul Anytime" (muj_00)
    STORY_STG5_64_LOST_WEDDING_RING = 275,        // "Lost Wedding Ring" (muj_02)
    STORY_STG5_64_01_WEDDING_RING_DELIVERY = 276, // "Wedding Ring Delivery" (muj_02)
    STORY_STG5_64_02_F_AND_F_SAIL_OFF = 277,      // "F & F Sail Off" (muj_00)
    STORY_STG5_64_03_F_AND_F_ARRIVE = 278,        // "F & F Arrive" (gor_00)
    STORY_STG5_65_TRAIN_TICKET = 279,             // "Train Ticket" (gor_03)
    STORY_STG5_66_BELDAM_FINDS_OUT = 280,         // "Beldam Finds Out" (gor_03)
    STORY_STG5_END_THE_TRAIN_LEAVES = 281,        // "The Train Leaves" (gor_04)
    STORY_STG6_00_START = 282,                    // "Start" (sys_01)
    STORY_STG6_01_THE_CONDUCTOR = 283,            // "The Conductor" (rsh_04_a)
    STORY_STG6_02_A_CASE_OF_LOST_STEW = 284,      // "A Case of Lost Stew" (rsh_03_a)
    STORY_STG6_03_STAINED_CARPET = 285,           // "Stained Carpet" (rsh_03_a)
    STORY_STG6_04_GRILLING_HEFF_T = 286,          // "Grilling Heff T." (rsh_02_a)
    STORY_STG6_05_GALLEY_KETTLE_DISCOVERED = 287, // "Galley Kettle Discovered" (rsh_02_a)
    STORY_STG6_06_PENNINGTONS_ASSISTANT = 288,    // "Pennington's Assistant" (rsh_04_a)
    STORY_STG6_07_SYLVIA = 289,                   // "Sylvia" (rsh_04_b)
    STORY_STG6_08_BUB = 290,                      // "Bub" (rsh_04_b)
    STORY_STG6_09_BUBS_REQUEST = 291,             // "Bub's Request" (rsh_04_b)
    STORY_STG6_10_THE_CONDUCTOR_ZIP_TOAD = 292,   // "The Conductor/Zip Toad" (rsh_04_b)
    STORY_STG6_11_OBTAIN_AUTOGRAPH = 293,         // "Obtain Autograph" (rsh_00_b)
    STORY_STG6_12_GIVE_AUTOGRAPH = 294,           // "Give Autograph" (rsh_04_b)
    STORY_STG6_13_TALK_TO_THE_CONDUCTOR = 295,    // "Talk to the Conductor" (rsh_04_c)
    STORY_STG6_14_GHOST_T = 296,                  // "Ghost T." (rsh_02_c)
    STORY_STG6_15_GHOST_REQUEST = 297,            // "Ghost Request" (rsh_02_c)
    STORY_STG6_16_THE_BAGGAGE_CAR = 298,          // "The Baggage Car" (rsh_04_c)
    STORY_STG6_17_GHOST_DIARY = 299,              // "Ghost Diary" (rsh_05_a)
    STORY_STG6_18_BLANKET_EXCHANGE = 300,         // "Blanket Exchange" (rsh_02_c)
    STORY_STG6_19_GIVE_BLANKET = 301,             // "Give Blanket" (rsh_04_c)
    STORY_STG6_20_END_OF_DAY_1 = 302,             // "End of Day 1" (rsh_02_c)
    STORY_STG6_21_DAY_2 = 303,                    // "Day 2" (rsh_02_a)
    STORY_STG6_22_DOCUMENT = 304,                 // "Document" (rsh_04_a)
    STORY_STG6_23_VITAL_PAPER = 305,              // "Vital Paper" (rsh_01_a)
    STORY_STG6_24_A_VITAL_CLUE = 306,             // "A Vital Clue" (rsh_04_a)
    STORY_STG6_24_02_ANOTHER_CLUE = 307,          // "Another Clue" (rsh_02_a)
    STORY_STG6_25_ZIP_TOAD_APPEARS = 308,         // "Zip Toad Appears" (rsh_02_a)
    STORY_STG6_26_ZIP_TOAD_CAUGHT = 309,          // "Zip Toad Caught" (rsh_02_a)
    STORY_STG6_27_RIVERSIDE_STATION = 310,        // "Riverside Station" (hom_00)
    STORY_STG6_28_STATION_KEY_OBTAINED = 311,     // "Station Key Obtained" (hom_00)
    STORY_STG6_29_STATION_DOOR_UNLOCKED = 312,    // "Station Door Unlocked" (hom_00)
    STORY_STG6_30_ORIGAMI_STAIRS = 313,           // "Origami Stairs" (eki_01)
    STORY_STG6_31_KEY = 314,                      // "Key" (eki_02)
    STORY_STG6_32_UNLOCKING_THE_DOOR = 315,       // "Unlocking the Door" (eki_01)
    STORY_STG6_33_BLOW_THE_POSTER = 316,          // "Blow the Poster" (eki_03)
    STORY_STG6_34_3_BLUE_BLOCKS = 317,            // "3 Blue Blocks" (eki_06)
    STORY_STG6_35_ORIGAMI_STAIRS = 318,           // "Origami Stairs" (eki_06)
    STORY_STG6_36_SPRING_JUMP = 319,              // "Spring Jump" (eki_05)
    STORY_STG6_37_ELEVATOR_KEY = 320,             // "Elevator Key" (eki_05)
    STORY_STG6_38_RIDE_THE_ELEVATOR = 321,        // "Ride the Elevator" (eki_00)
    STORY_STG6_39_SMORG_1ST_ENCOUNTER = 322,      // "Smorg (1st Encounter)" (eki_00)
    STORY_STG6_40_SWATTING_SMORGS = 323,          // "Swatting Smorgs" (eki_00)
    STORY_STG6_41_ORIGAMI_STAIRS = 324,           // "Origami Stairs" (eki_00)
    STORY_STG6_42_DRAWBRIDGE_DOWN = 325,          // "Drawbridge Down" (eki_00)
    STORY_STG6_43_CONDUCTOR_APPEARS = 326,        // "Conductor Appears" (hom_00)
    STORY_STG6_44_END_OF_DAY_2 = 327,             // "End of Day 2" (rsh_02_c)
    STORY_STG6_45_DAY_3_STARTS = 328,             // "Day 3 Starts" (rsh_02_a)
    STORY_STG6_46_ENGINEER = 329,                 // "Engineer" (rsh_00_a)
    STORY_STG6_47_00_BAGGAGE_CAR_SMORGS = 330,    // "Baggage Car Smorgs" (rsh_05_a)
    STORY_STG6_47_ESCAPING_THE_SMORGS = 331,      // "Escaping the Smorgs" (rsh_05_a)
    STORY_STG6_48_SMORG_MIASMA = 332,             // "Smorg Miasma" (rsh_06_a)
    // no event-table row: set in rsh_01 after the Smorg battle as the train pulls into Poshley Heights
    STORY_STG6_48_01_ARRIVING_AT_POSHLEY = 333,
    STORY_STG6_49_POSHLEY_HEIGHTS = 334,         // "Poshley Heights" (rsh_01_a)
    STORY_STG6_50_THE_SANCTUM_MANAGER = 335,     // "The Sanctum Manager" (pik_01)
    STORY_STG6_51_3_SURPRISE_GUESTS = 336,       // "3 Surprise Guests" (pik_02)
    STORY_STG6_52_THE_HIDDEN_PIPE = 337,         // "The Hidden Pipe" (pik_02)
    STORY_STG6_53_THE_REAL_GARNET_STAR = 338,    // "The Real Garnet Star" (pik_03)
    STORY_STG6_54_WELCOME_BACK = 339,            // "Welcome Back" (pik_02)
    STORY_STG6_55_PEACH_GRODUS_AND_X_NAUT = 340, // "Peach: Grodus & X-Naut" (aji_10)
    STORY_STG6_55_01_PEACH_TEC_DELETED = 341,    // "Peach: TEC Deleted" (aji_17)
    STORY_STG6_55_02_BOWSER_ROGUEPORT = 342,     // "Bowser: Rogueport" (gor_01)
    STORY_STG6_55_03_BOWSER_ACTION_STAGE = 343,  // "Bowser: Action Stage" (kpa_05)
    STORY_STG6_55_04_BOWSER_RAWK_HAWK = 344,     // "Bowser: Rawk Hawk" (kpa_07)
    STORY_STG6_56_ROGUEPORT_STATION = 345,       // "Rogueport Station" (gor_04)
    STORY_STG6_57_A_MAIL_FROM_PEACH = 346,       // "A Mail from Peach" (gor_04)
    STORY_STG6_70_THOUSAND_YEAR_DOOR = 347,      // "Thousand-Year Door" (tik_05)
    STORY_STG6_71_FRANKLYS_HOUSE = 348,          // "Frankly's House Stg.6" (gor_02)
    // no event-table row and never set; only tested (bom_00/bom_01 "< 349" = before STG6_72)
    STORY_STG6_71_01 = 349,
    // "3 Minutes Later" (gor_02); "A Way to the Moon" (gor_02)
    STORY_STG6_72_THREE_MINUTES_LATER = 350,
    // "Ultra Hammer" (gor_01); "Stone Block Smash" (tik_07); "To Fahr Outpost" (tik_07)
    STORY_STG6_END_ULTRA_HAMMER = 351,
    STORY_STG7_00_START = 352,                  // "Start" (sys_01)
    STORY_STG7_01_FAHR_OUTPOST_1ST_VISIT = 353, // "Fahr Outpost (1st Visit)" (bom_01)
    STORY_STG7_02_MAYOR_BOB = 354,              // "Mayor Bob" (bom_02)
    // "Goldbob" (pik_00); "Where's White?(Petalburg)" (nok_00); "Where's White?(Keelhaul)" (muj_01); "Where's White?(Glitzville)" (tou_01); "Where's White?(Great Tree)" (mri_01); "Where's White?(Twilight)" (usu_00); "Gen. White Awakens" (bom_02)
    STORY_STG7_03_WHERES_WHITE = 355,
    STORY_STG7_04_BACK_ONLINE = 356,              // "Back Online" (bom_02)
    STORY_STG7_05_THE_CANNON = 357,               // "The Cannon" (bom_01)
    STORY_STG7_06_TO_THE_MOON = 358,              // "To the Moon" (moo_00)
    STORY_STG7_07_A_PIPE_APPEARS = 359,           // "A Pipe Appears" (moo_02)
    STORY_STG7_07_01_INSIDE_THE_BUILDING = 360,   // "Inside the Building" (aji_19)
    STORY_STG7_08_ELITE_X_NAUTS = 361,            // "Elite X-Nauts" (aji_00)
    STORY_STG7_09_ELEVATOR_KEY_A_LIT_FLOOR = 362, // "Elevator Key A(Lit Floor)" (aji_02)
    STORY_STG7_10_ELEVATOR_ACTIVATED = 363,       // "Elevator Activated" (aji_01)
    STORY_STG7_11_PASSWORD_FOR_TODAY = 364,       // "Password for Today" (aji_09)
    STORY_STG7_12_PASSWORD_ENTRY = 365,           // "Password Entry" (aji_01)
    STORY_STG7_13_QUIZ_CLEARED = 366,             // "Quiz Cleared" (aji_04)
    STORY_STG7_14_ELEVATOR_KEY_B = 367,           // "Elevator Key B" (aji_04)
    // "Elevator Activated 2" (aji_01); "Room Key A" (aji_05); "Room Key B" (aji_12); "Room Key C" (aji_10)
    STORY_STG7_15_ROOM_KEYS = 368,
    STORY_STG7_16_FACTORY_DOOR = 369,              // "Factory Door" (aji_18)
    STORY_STG7_17_CONVEYOR_BELT = 370,             // "Conveyor Belt" (aji_13)
    STORY_STG7_18_OFF_SCREEN_STAIRS = 371,         // "Off-screen Stairs" (aji_13)
    STORY_STG7_19_THE_DOOR_TO_LORD_CRUMP = 372,    // "The Door to Lord Crump" (aji_13)
    STORY_STG7_20_LORD_CRUMP_DEFEATED = 373,       // "Lord Crump Defeated" (aji_14)
    STORY_STG7_25_00_BOWSER_POSHLEY_HEIGHTS = 374, // "Bowser: Poshley Heights" (pik_01)
    // "Bowser: Poshley Sanctum" (pik_01); "Bowser: Crystal Star" (pik_02)
    STORY_STG7_25_00_1_BOWSER_POSHLEY_SANCTUM = 375,
    STORY_STG7_25_THE_LAST_MAIL = 376,          // "The Last Mail" (aji_18)
    STORY_STG7_26_THE_HIDEOUT_EXPLODES = 377,   // "The Hideout Explodes" (aji_07)
    STORY_STG7_50_A_WAITING_PROF_FRANKLY = 378, // "A Waiting Prof. Frankly " (tik_00)
    STORY_STG7_51_THOUSAND_YEAR_DOOR = 379,     // "Thousand-Year Door" (tik_05)
    STORY_STG7_52_THE_PEDESTAL = 380,           // "The Pedestal" (tik_05)
    STORY_STG7_END_TO_THE_LAST_DUNGEON = 381,   // "To the Last Dungeon" (tik_05)
    STORY_STG8_00_START = 382,                  // "Start" (sys_01)
    STORY_STG8_01_1000_DRY_BONES = 383,         // "1000 Dry Bones" (las_05)
    STORY_STG8_01_01_KEY = 384,                 // "Key" (las_05)
    STORY_STG8_01_02_LOCK = 385,                // "Lock" (las_05)
    STORY_STG8_02_FOLLOW_THE_LIT_TORCHES = 386, // "Follow the Lit Torches" (las_08)
    STORY_STG8_03_THE_PALACE_GARDEN = 387,      // "The Palace Garden" (las_09)
    STORY_STG8_04_GLOOMTAIL = 388,              // "Gloomtail" (las_26)
    STORY_STG8_05_STAR_KEY_SLOT = 389,          // "Star Key Slot" (las_10)
    STORY_STG8_06_MOVING_PLANETS = 390,         // "Moving Planets" (las_10)
    STORY_STG8_07_BELDAM_CONFRONTATION = 391,   // "Beldam Confrontation" (las_09)
    STORY_STG8_08_THE_NEW_PATH = 392,           // "The New Path" (las_19)
    STORY_STG8_09_KEY = 393,                    // "Key" (las_22)
    STORY_STG8_10_LOCK = 394,                   // "Lock" (las_22)
    STORY_STG8_11_STAR_PUZZLE = 395,            // "Star Puzzle" (las_20)
    STORY_STG8_12_LARGE_STONE_BLOCK = 396,      // "Large Stone Block" (las_24)
    STORY_STG8_13_KEY = 397,                    // "Key" (las_24)
    STORY_STG8_14_LOCK = 398,                   // "Lock" (las_25)
    STORY_STG8_14_01_QUEENS_CHAMBER = 399,      // "Queen's Chamber" (las_28)
    STORY_STG8_15_GRODUS = 400,                 // "Grodus" (las_28); "Bowser" (las_28)
    // "The Return of the Queen" (las_29); "End of the World 1" (gor_01); "The Shadow Queen" (las_29); "End of the World 2" (usu_00); "Shadow Peach" (las_29); "The Crystal Stars" (las_29); "Words of Support 1" (gor_01); "Words of Support 2" (usu_00); "Words of Support 3" (las_29)
    STORY_STG8_16_SHADOW_QUEEN = 401,
    STORY_STG8_END_AFTER_THE_BATTLE = 402, // "After the Battle" (las_29)
    // "Epilogue" (gor_11); "Rogueport Dock" (gor_00); "Sail Away" (muj_21); "Mario's House" (aaa_00); "Professor Frankly" (gor_02); "Goombella" (hei_00); "Koops" (nok_01); "Mini-Yoshi" (tou_08); "Vivian" (usu_00); "Bobbery" (muj_20); "Ms. Mowz" (gor_01); "X-Nauts" (pik_04); "Moon" (tik_00); "Goombella 2" (gor_00); "Mario's House 2" (aaa_00)
    STORY_STG9_00_EPILOGUE = 403,
    STORY_STG9_01_END_CREDITS = 404,         // "End Credits" (end_00)
    STORY_STG9_02_RETURN_TO_ROGUEPORT = 405, // "Return to Rogueport" (gor_00)
    STORY_STG9_END_ROGUEPORT = 406,          // "Rogueport" (gor_00)
} StoryProgress;

// Saved global work bytes: swByteGet/swByteSet index, GSW(...) in scripts.
typedef enum GswId {
    // Main story sequence number; values are the event-table ids in src/event.c (the StoryProgress enum above; the event table is in src/event.c)
    GSW_STORY_PROGRESS = 0,
    // Number of times Mario has slept at a Toad inn (capped at 100); the 50th stay plays the inn photographer (Lakitu cameraman) scene evt_50
    GSW_INN_STAY_COUNT = 1,
    // Low byte of the coins the thief stole on arrival in Rogueport (half of Mario's coins); refunded by thief_talk
    GSW_GOR_STOLEN_COINS_LO = 2,
    GSW_GOR_STOLEN_COINS_HI = 3, // High byte of the stolen-coin amount (pairs with GSW 2)
    // How the save was made, read when loading: 0 = normal Save Block (restore position), 1 = during a Peach intermission (resume in aji_10), 2 = during a Bowser intermission (resume in kpa_00), other values for special saves
    GSW_SAVE_RESUME_KIND = 4,
    // 8-byte play-time stamp (GSW 5-12) of the RDM Issue 2 mail; Pungent's shop in mri_07 offers double shop points for 900000 ticks after it (with GSWF 250)
    GSW_MRI07_DOUBLE_POINTS_TIME = 5,
    // 8-byte play-time stamp (GSW 14-21) of the RDM Issue 4 mail; the Twilight Shop (usu_01) offers double shop points for 900000 ticks after it (with GSWF 251)
    GSW_USU01_DOUBLE_POINTS_TIME = 14,
    // 8-byte play-time stamp (GSW 23-30) of the RDM Issue 6 mail; the Excess Express Sales Stall (rsh_03) offers double shop points for 900000 ticks after it (with GSWF 252)
    GSW_RSH03_DOUBLE_POINTS_TIME = 23,
    // Low byte of the record number of consecutive Power Bounce stomps (record = GSW 32 + 256*GSW 35, max 9999); shown on the Pit of 100 Trials sign
    GSW_POWER_BOUNCE_RECORD_LO = 32,
    // Deepest Pit of 100 Trials floor reached (floor number, 1-100); shown on the sign in tik_06
    GSW_JON_DEEPEST_FLOOR = 33,
    // Star Piece count shown on the Pit of 100 Trials sign; read only, nothing in the code ever writes it
    GSW_JON_STAR_PIECES_FOUND = 34,
    // High byte of the record consecutive Power Bounce count (pairs with GSW 32)
    GSW_POWER_BOUNCE_RECORD_HI = 35,
    // 8-byte play-time stamp (GSW 100-107) taken when Frankly starts the chapter 6 research and asks Mario to come back a few minutes later
    GSW_GOR02_FRANKLY_STG6_TIME = 100,
    // 8-byte play-time stamp (GSW 108-115) taken when the contact lens is ordered at the Toad Bros. Bazaar; it arrives after 90000 ticks
    GSW_GOR01_LENS_ORDER_TIME = 108,
    // Number of investments given to Lumpy for his oil venture (3 = ready to leave); drives his payout
    GSW_GOR00_LUMPY_INVESTMENTS = 116,
    // How many backstage tip talks the parlor bunny Boo has given (compared with the four record flags GSWF 1240-1243)
    GSW_GOR03_PARLOR_SECRET_TALKS = 117,
    // Base of the badge shop bargain picks: GSW 118+i holds an index into badge_bottakuru_table for slot i (range 118..)
    GSW_BADGESHOP_BARGAIN_SLOTS = 118,
    // Times the can in hei_13 was hit this visit; the 10th hit drops a Horsetail; reset on map load
    GSW_HEI13_CAN_HITS = 301,
    // Fighter id (FIGHTER_* in include/map/tou_ranking.h) of the reserved/current Glitz Pit opponent (19 Goomba Bros, 10 Iron Clefts, 0 Rawk Hawk)
    GSW_TOU_OPPONENT_ID = 501,
    GSW_TOU_MATCH_RULE = 502, // Battle-condition (promoter request) id for the reserved match
    // First parameter of the reserved match condition (passed to evt_npc_set_battle_rule)
    GSW_TOU_MATCH_RULE_PARAM1 = 503,
    GSW_TOU_MATCH_RULE_PARAM2 = 504, // Second parameter of the reserved match condition
    // Times Mario lost to the Iron Clefts (capped at 100); >=2 triggers the early Yoshi-egg scene in tou_10
    GSW_TOU_IRON_CLEFTS_LOSSES = 505,
    // Mario's ranking before the last match; compared afterwards for rank rose/fell/defended messages and league moves
    GSW_TOU_RANK_BEFORE_MATCH = 506,
    // Fighter id of the opponent in the last finished match (ranking code re-sorts Mario next to it); valid while GSWF 2532 is set
    GSW_TOU_LAST_OPPONENT_ID = 507,
    // 8-byte play-time stamp (GSW 508-515) of when Mario got the Yoshi egg; elapsed minutes pick the Yoshi colour in tou_10
    GSW_TOU_EGG_TIME = 508,
    // Base of the saved ranking points: 2 bytes per fighter at GSW 519+2*FIGHTER_* (23 fighters, 519-564)
    GSW_TOU_FIGHTER_POINTS_BASE = 519,
    // Number of visible fighters ranked above Mario (0 = champion); battle_seq checks <11 for major-league rules
    GSW_TOU_PLAYER_RANK = 580,
    // Number of ordinary Punies following Mario in the Great Tree beyond the fixed ones (9 after the first rescue, 98 when the whole tribe follows); added to the Puni count totals
    GSW_MRI_PUNI_FOLLOWERS = 651,
    // Bitfield over 13 bytes (GSW 652-664, range 652..664): bit n set = Puni n (0-102) is held captive; puniswTrapGetindex/Setindex read and write it
    GSW_MRI_PUNI_TRAPPED_BITS = 652,
    // Great Tree map number (+1) where the Puni group was last set up (Punigp->floor); 1 skips the follower placement
    GSW_MRI_PUNI_CUR_MAP = 665,
    // Great Tree map number (+1) the Puni group was in on the previous map; mri_01 uses (cur 2, prev 1) to start puni_mario_wait
    GSW_MRI_PUNI_PREV_MAP = 666,
    // Last shown Puni counter value (Punies with Mario), restored when the Puni system is not running
    GSW_MRI_PUNI_COUNTER_HERE = 667,
    // Last shown Puni counter total, restored when the Puni system is not running
    GSW_MRI_PUNI_COUNTER_TOTAL = 668,
    // Times Mario has hit Whacka on Keelhaul Key for a Whacka Bump; after 8 Whacka is gone (koburon_dead plays the farewell at 7)
    GSW_MUJ00_WHACKA_BUMPS = 721,
    // First of three Excess Express random-passenger state words (GSW 821-823), zeroed by evt_rsh_rnd_npc_init and updated by _get_rnd_npc_data
    GSW_RSH_RANDOM_NPC_STATE_A = 821,
    GSW_RSH_RANDOM_NPC_STATE_B = 822, // Second Excess Express random-passenger state word
    GSW_RSH_RANDOM_NPC_STATE_C = 823, // Third Excess Express random-passenger state word
    // Leg of the Excess Express ride in progress, set on departure: 0 Rogueport to Riverside, 1 Riverside to Poshley, 2 Poshley to Riverside, 3 Riverside to Rogueport
    GSW_TRAIN_LEG = 870,
    // Times Mario tried the locked door / elevator in aji_01 (X-Naut Fortress); stops at 3; the 3rd try adds a partner comment (stg7_aji_45_03)
    GSW_AJI01_LOCKED_DOOR_TRIES = 1071,
    // Correct doors chosen in a row in the Palace of Shadow endless corridor (las_08); a wrong door resets it, 7 advances the story to 386
    GSW_LAS08_CORRIDOR_STREAK = 1121,
    GSW_LAS10_KEYS_USED = 1122, // Palace Keys put into the big locked door in las_10; 8 opens it
    // Progress of defeating the las_17 enemies in the required order (0-4); 4 makes the switch/chest appear, less than 4 is reset on entry
    GSW_LAS17_ENEMY_ORDER = 1123,
    // Shadow Queen HP recorded when she changes form during the final battle (written only, never read)
    GSW_SHADOW_QUEEN_HP = 1124,
    // Lives counter for Bowser's side-scrolling stages (kpa); 1 on a fresh start, kpa_dead raises it up to 99; passed to kpa_status_init (kwp->lives)
    GSW_KPA_LIVES = 1221,
    // Time limit for Bowser's side-scrolling stage (180 on start/replay); low time (<=30) switches the music
    GSW_KPA_TIME_LEFT = 1222,
    // Bowser's power-up level in the side-scrolling stages, carried between kpa maps
    GSW_KPA_BOWSER_POWER = 1223,
    // Current Pit of 100 Trials floor (0-99, floor number minus 1); also scales Charlieton's prices ((floor+11)/10)
    GSW_JON_FLOOR = 1321,
    // Id of the Trouble Center request currently accepted (0 = none); each trouble script checks its own number
    GSW_TROUBLE_ACTIVE = 1420,
    // 8-byte play-time stamp (GSW 1421-1428) saved when trouble #7 (find Koopook, hiding in gon_08) is solved
    GSW_GON08_TROUBLE07_TIME = 1421,
    // 8-byte play-time stamp (GSW 1429-1436) saved when trouble #12 (rescue the Toad's father lying beaten in tik_06, back from the Pit of 100 Trials) is solved
    GSW_TIK06_TROUBLE12_TIME = 1429,
    // 8-byte play-time stamp (GSW 1437-1444) saved when trouble #13 (Jolene, clean the storeroom) is finished
    GSW_TOU_JOLENE_TROUBLE_TIME = 1437,
    // 8-byte play-time stamp (GSW 1445-1452) saved when trouble #15 (Bub-ulber's food requests in Petalburg) is solved
    GSW_NOK00_TROUBLE15_TIME = 1445,
    // 8-byte play-time stamp (GSW 1453-1460) saved when trouble #20 (the old woman who wants to meet her former love Podley) is solved
    GSW_USU01_TROUBLE20_TIME = 1453,
    // 8-byte play-time stamp (GSW 1461-1468) saved when trouble #26 (the Bob-omb in Fahr Outpost who lost his voice) is solved
    GSW_BOM02_TROUBLE26_TIME = 1461,
    // First of six per-trouble scratch counters (GSW 1469-1474), zeroed on accepting a trouble; trouble #9 counts Courage Shells here
    GSW_TROUBLE_WORK_FIRST = 1469,
    // Last per-trouble scratch counter (loop bound in irai_flag_clear)
    GSW_TROUBLE_WORK_LAST = 1474,
} GswId;

// Saved global flags: swGet/swSet/swClear index, GSWF(...) in scripts.
typedef enum GswfId {
    // First shop interaction done; the shop-points explanation (first_shopping_evt) has been given
    GSWF_SHOP_FIRST_VISIT = 0,
    // The 300-shop-point prize was earned while Mario's pockets were full; the shop holds it and pays it out on the next talk
    GSWF_SHOP_MAX_POINTS_PRIZE_HELD = 1,
    // The gor_01 badge shop clerk gave the first-talk greeting (first_shopping_evt, badgeshop_30) (Japanese demo only)
    GSWF_GOR01_BADGE_SHOP_FIRST_TALK = 2,
    // Talked to Wonky (the item buyer in the Rogueport sewers) once; later talks skip his introduction
    GSWF_TIK00_WONKY_FIRST_TALK = 3,
    // Talked to Grifty the minstrel once (short greeting afterwards)
    GSWF_GOR02_GRIFTY_FIRST_TALK = 4,
    GSWF_TIK00_MERLUVLEE_MET = 5, // Merluvlee's first-meeting introduction has been heard
    // Mario already went through Merluvlee's greeting and yes/no this visit (skip to the fortune menu); cleared when tik_00 loads
    GSWF_TIK00_MERLUVLEE_SESSION = 6,
    // Frankly's first e-mail and the RDM registration mail were delivered (on reaching nok_01 at story 27)
    GSWF_MAIL_FRANKLY_SENT = 7,
    GSWF_MAIL_KOOPLEY_SENT = 8,    // Koopley's mail was delivered (gor_03, story 125)
    GSWF_MAIL_KOOPIE_KOO_SENT = 9, // Koopie Koo's mail was delivered (gor_02, story 175)
    GSWF_MAIL_PETUNI_SENT = 10,    // Petuni's mail was delivered (gor_01, story 228)
    GSWF_MAIL_BOO_SENT = 11,       // The Creepy Steeple Boo's mail was delivered (gor_04, story 280)
    GSWF_MAIL_PA_PATCH_SENT = 12,  // Pa-Patch's mail was delivered (on the Excess Express)
    GSWF_MAIL_KING_K_SENT = 13,    // King K's mail was delivered (hom_00, story 325)
    GSWF_MAIL_ZIP_TOAD_SENT = 14,  // The real Zip Toad's mail was delivered (gor_02, story 348)
    GSWF_MAIL_RAWK_HAWK_SENT = 15, // Rawk Hawk's mail was delivered (bom_01, story 354)
    // Ghost T.'s mail and the RDM final issue were delivered (tik_00, story 378)
    GSWF_MAIL_GHOST_T_SENT = 16,
    GSWF_MAIL_RDM_ISSUE1_SENT = 17, // The RDM premiere issue was delivered (win_01, story 87)
    // RDM Issue 2 was delivered (tou_01, story 137); starts Pungent's double-point sale
    GSWF_MAIL_RDM_ISSUE2_SENT = 18,
    GSWF_MAIL_RDM_ISSUE3_SENT = 19, // RDM Issue 3 was delivered (usu_01, story 187)
    // RDM Issue 4 was delivered (gor_01, story 270); starts the Twilight Shop double-point sale
    GSWF_MAIL_RDM_ISSUE4_SENT = 20,
    GSWF_MAIL_RDM_ISSUE5_SENT = 21, // RDM Issue 5 was delivered (rsh_03_a, story 303)
    // RDM Issue 6 was delivered (pik_00, story 354); starts the Sales Stall double-point sale
    GSWF_MAIL_RDM_ISSUE6_SENT = 22,
    GSWF_MAIL_TUTORIAL_SEEN = 37, // The first-mail explanation (mail_first_hit) has been shown
    // Mario has opened a letter in the Mailbox SP; until then every new mail repeats the mail explanation
    GSWF_MAIL_OPENED_ONCE = 38,
    // Set by muj_00 when arriving on Cortez's ship, cleared by gor_00; never tested anywhere
    GSWF_SHIP_TRAVEL_ACTIVE = 39,
    // Base of the chapter title-card flags: GSWF 40+n is set once title card n (evt_telop_entry) has been shown
    GSWF_TELOP_SHOWN_BASE = 40,
    // Zess T. has cooked a dish once; win_log adds the Recipes page when set
    GSWF_RECIPE_LOG_UNLOCKED = 64,
    // Recipe-known flags: GSWF (item id - 114), i.e. 65 + (item - 0xB3); set by cooking_flag, read by win_log
    GSWF_RECIPE_BASE = 65,
    // Base of the Badge Log flags: GSWF 128+n is set when badge BADGE_MIN+n is first obtained (pouchGetItem); read by the Badge Log
    GSWF_BADGE_FOUND_BASE = 128,
    // The first Save Block explanation (save_first_hit) has been shown
    GSWF_SAVE_BLOCK_TUTORIAL_SEEN = 233,
    // The first Heart Block explanation has been shown (mobj_recovery_blk, outside kiosk mode)
    GSWF_HEART_BLOCK_TUTORIAL_SEEN = 234,
    // The first-item explanation (item_first_hit) has been shown, from a pickup or a shop purchase; also checked when the audience throws an item
    GSWF_ITEM_TUTORIAL_SEEN = 235,
    // Mario hit a Save Block after Goombella joined (GSW0>=7); suppresses her save-block reminder
    GSWF_SAVE_BLOCK_USED_AFTER_GOOMBELLA = 236,
    // Merluvlee gave her long greeting this visit (later talks use the short one); cleared when tik_00 loads
    GSWF_TIK00_MERLUVLEE_GREETED = 237,
    // The chapter 1 clear badges (story >= 55) were added to the badge shop's special stock
    GSWF_BADGESHOP_STG1_STOCK_ADDED = 238,
    // The chapter 2 clear badges (story >= 112) were added to the badge shop's special stock
    GSWF_BADGESHOP_STG2_STOCK_ADDED = 239,
    // The chapter 3 clear badges (story >= 164) were added to the badge shop's special stock
    GSWF_BADGESHOP_STG3_STOCK_ADDED = 240,
    // The chapter 4 clear badges (story >= 212) were added to the badge shop's special stock
    GSWF_BADGESHOP_STG4_STOCK_ADDED = 241,
    // The chapter 5 clear badges (story >= 253) were added to the badge shop's special stock
    GSWF_BADGESHOP_STG5_STOCK_ADDED = 242,
    // The chapter 6 clear badges (story >= 338) were added to the badge shop's special stock
    GSWF_BADGESHOP_STG6_STOCK_ADDED = 243,
    // Chapter 7 clear (story >= 373) stock step done; no badges are added for it
    GSWF_BADGESHOP_STG7_STOCK_ADDED = 244,
    // Story >= 401 stock step done; no badges are added for it
    GSWF_BADGESHOP_STG8_STOCK_ADDED = 245,
    // Owning the Special Card added its badges to the bunny Boo's exchange stock (badge_bteresa_table_card_special)
    GSWF_PARLOR_SPECIAL_CARD_PRIZES_ADDED = 246,
    // Owning the Silver Card added its badges to the bunny Boo's exchange stock
    GSWF_PARLOR_SILVER_CARD_PRIZES_ADDED = 247,
    // Owning the Gold Card added its badges to the bunny Boo's exchange stock
    GSWF_PARLOR_GOLD_CARD_PRIZES_ADDED = 248,
    // Owning the Platinum Card added its badges to the bunny Boo's exchange stock
    GSWF_PARLOR_PLATINUM_CARD_PRIZES_ADDED = 249,
    // Pungent's shop (mri_07) double-shop-point sale announced by RDM Issue 2; active while less than 900000 ticks since GSW 5
    GSWF_MRI07_DOUBLE_POINTS_SALE = 250,
    // Twilight Shop (usu_01) double-shop-point sale announced by RDM Issue 4; active while less than 900000 ticks since GSW 14
    GSWF_USU01_DOUBLE_POINTS_SALE = 251,
    // Excess Express Sales Stall (rsh_03) double-shop-point sale announced by RDM Issue 6; active while less than 900000 ticks since GSW 23
    GSWF_RSH03_DOUBLE_POINTS_SALE = 252,
    // Journal map: route dots of type 1 count as visited (set on entering win_04); the US dot table has no type-1 dots
    GSWF_LOG_MAP_WIN_ROUTE_SHOWN = 253,
    // Journal map: the Rogueport-underground dots (type 2: gor/tik) show before the story reaches them; set on entering tik_01
    GSWF_LOG_MAP_TIK_ROUTE_SHOWN = 254,
    // Journal map: the Petal Meadows to Hooktail Castle dots (type 3: hei/gon) show early; set on entering gon_00
    GSWF_LOG_MAP_GON_ROUTE_SHOWN = 255,
    // Journal map: the Twilight Trail dots (type 4: usu/gra) show early; set on entering gra_00
    GSWF_LOG_MAP_GRA_ROUTE_SHOWN = 256,
    // Temporary lottery state while Mario buys a new number after a void ticket
    GSWF_GOR03_LOTTERY_REDRAW = 257,
    GSWF_GOR_LUIGI_FIRST_TALK = 1175, // First talk with Luigi at the Rogueport inn done
    // Agreed to help Frankie and Francesca (cleared again if Mario refused)
    GSWF_GOR00_FRANKIE_FRANCESCA_HELPED = 1176,
    // Flavio has said the ship is ready after Bobbery joined
    GSWF_GOR00_FLAVIO_READY_TO_SAIL = 1177,
    // Set when sailing back from Keelhaul Key; gor_00 plays the docking scene once and clears it
    GSWF_GOR00_SHIP_ARRIVAL_PENDING = 1178,
    // Goombella-being-harassed scene in the plaza done (also set by the stg0_05 skip)
    GSWF_GOR00_GOOMBELLA_ASSAULTED_SEEN = 1179,
    // Arrived by ship: gor_00 places Mario on the dock and clears it
    GSWF_GOR00_SHIP_ARRIVAL_AT_DOCK = 1180,
    // Frankie/Francesca follow-up scene at GSW0=123 has played
    GSWF_GOR00_FRANKIE_FRANCESCA_AFTER_SEEN = 1181,
    GSWF_GOR00_LUMPY_FIRST_TALK = 1182,  // First talk with Lumpy before he leaves for the oil field
    GSWF_GOR00_LUMPY_RETURN_TALK = 1183, // First talk with Lumpy after he struck oil
    GSWF_GOR02_MERLON_FIRST_TALK = 1185, // Merlon's full introduction heard
    // A partner has been upgraded by Merlon at least once; the party menu shows ranks only after this
    GSWF_MERLON_FIRST_UPGRADE_DONE = 1186,
    // Zess T. (internal name Nancy) has blocked the west gate (also set by the stg1_30 skip)
    GSWF_GOR01_ZESS_BLOCKS_GATE = 1187,
    // Contact lens given to Zess T.; she leaves the west gate (also set by the stg1_30 skip)
    GSWF_GOR01_LENS_DELIVERED = 1188,
    // Contact lens ordered at the Toad Bros. Bazaar (first ordering path)
    GSWF_GOR01_LENS_ORDERED = 1189,
    // Contact lens ordered (second dialogue path; summed with 1189)
    GSWF_GOR01_LENS_ORDERED_ALT = 1190,
    GSWF_GOR01_LENS_ARRIVED = 1191,      // The ordered contact lens has arrived at the shop
    GSWF_GOR01_FLAVIO_FIRST_TALK = 1192, // First talk with Flavio at Podley's Place
    // Podley started telling Admiral Bobbery's sad tale
    GSWF_GOR01_PODLEY_BOBBERY_TALE_OFFERED = 1193,
    GSWF_GOR01_PODLEY_BOBBERY_TALE_DONE = 1194, // Heard Bobbery's tale and chose to make him sail
    // Ultra Hammer treasure chest opened (also set by the stg6_end skip)
    GSWF_GOR01_ULTRA_HAMMER_CHEST_OPENED = 1195,
    // Ultra Hammer chest has dropped down after its trigger
    GSWF_GOR01_ULTRA_HAMMER_CHEST_FALLEN = 1196,
    GSWF_GOR01_ZESS_INTRO_DONE = 1197,  // Zess T. introduced herself in Rogueport
    GSWF_GOR01_THIEF_CONFRONTED = 1198, // Confronted the coin thief (coins refunded)
    GSWF_GOR01_THIEF_LEFT_HOUSE = 1199, // Left the thief's house after the confrontation
    // Goombella's reminder to save, after she joins, has played
    GSWF_GOR01_GOOMBELLA_SAVE_TALK_DONE = 1200,
    // Trouble #16 reward (Attack FX B) left on the ground because Mario's badges were full
    GSWF_GOR01_TROUBLE16_BADGE_LEFT = 1201,
    // Trouble #18 reward (Honey Shroom) left on the ground because the inventory was full
    GSWF_GOR01_TROUBLE18_ITEM_LEFT = 1202,
    // Merlon has a star-chart portent to tell (set by the dearu event before any upgrade)
    GSWF_GOR02_MERLON_PORTENT_PENDING = 1203,
    GSWF_GOR02_MERLON_PORTENT_TOLD = 1204,   // Merlon told the star-chart portent
    GSWF_GOR01_CHARLIETON_FIRST_TALK = 1205, // First talk with Charlieton in Rogueport
    GSWF_GOR01_CHARLIETON_BOUGHT = 1206,     // Bought from Charlieton this visit (reset on NPC init)
    // Frankly's first door scene in gor_02 played (also set by the stg0_11 skip)
    GSWF_GOR02_FRANKLY_INTRO_SEEN = 1207,
    GSWF_GUS_TAUNT_SHOWN = 1208,             // Gus's mid-battle taunt shown once
    GSWF_GOR02_ROBBO_BOSS_FIRST_TALK = 1209, // First talk with the Robbo boss
    // Robbo boss told Mario about Don Pianta and the protection money
    GSWF_GOR02_ROBBO_BOSS_PIANTA_TALK = 1210,
    GSWF_GOR02_ROBBO_BOSS_PARLOR_HINT = 1211, // Robbo boss pointed Mario to Don Pianta's parlor
    GSWF_GOR02_GUS_FIRST_TALK = 1212,         // First talk with Gus at the west gate
    // Beat Gus; the west gate is open (also drives Frankly's Gus tattle reminder)
    GSWF_GOR02_GUS_DEFEATED = 1213,
    GSWF_GOR_BOBBERY_HOUSE_KNOWN = 1214, // Told where Admiral Bobbery lives (by Podley or Frankly)
    GSWF_GOR02_BOBBERY_DENIED = 1215,    // Bobbery first denied being Bobbery
    // Bobbery's house door unlocked (also set by the stg4_35 skip)
    GSWF_GOR02_BOBBERY_DOOR_OPEN = 1216,
    // Scene after leaving Bobbery's house at GSW0=225 done (also set by the stg4_35 skip)
    GSWF_GOR02_BOBBERY_DECLINE_SCENE_DONE = 1217,
    // Frankly suggested finding Darkly about the Twilight Town pipe
    GSWF_GOR02_FRANKLY_DARKLY_HINT = 1218,
    // House key returned (trouble #1); the padlock on that house is gone
    GSWF_GOR02_HOUSE_KEY_RETURNED = 1219,
    // Frankly is researching after chapter 6; the next door exit clears it
    GSWF_GOR02_FRANKLY_STG6_RESEARCH = 1220,
    // Flurrie blew away the wall covering in gor_02, revealing the passage
    GSWF_GOR02_WALL_COVER_BLOWN = 1221,
    GSWF_GOR02_TROUBLE_BACKDOOR_TALK = 1222, // Talked to the Trouble Center back-door guard
    // One-shot: set by gor_03_down_evt when Mario drops into the Rogueport underground; tik_07_down_evt plays the landing and clears it
    GSWF_GOR03_DROP_TO_UNDERGROUND = 1223,
    GSWF_GOR03_WALL_BOMBED = 1224,           // Bombable wall in gor_03 blown open
    GSWF_GOR03_PIANTA_CHANGER_INTRO = 1225,  // Pianta Changer machine introduction heard
    GSWF_GOR03_PARLOR_FIRST_GREETING = 1226, // Parlor bunny Boo's first greeting heard
    // A new member card was just registered; cleared when the game-room door opens
    GSWF_GOR03_PARLOR_CARD_SHOWN_THIS_VISIT = 1227,
    GSWF_GOR03_PRIZE_EXCHANGE_EXPLAINED = 1228, // Prize exchange rules explained
    // Quit a Pianta Parlor minigame; gor_03 restores the pipe, music and pianta medals then clears it
    GSWF_YUU_MINIGAME_QUIT = 1229,
    // Pianta syndicate back door opened (also set by the stg2_44 skip)
    GSWF_GOR03_SYNDICATE_BACKDOOR_OPEN = 1230,
    // Set only by the story-skip setups stg5_62/stg5_65/stg5_66 (An Ill Don Pianta, Train Ticket, Beldam Finds Out); never read
    GSWF_GOR03_DON_PIANTA_STG5_SCENE = 1231,
    GSWF_YUU_PLANE_GAME_UNLOCKED = 1232,       // Plane Game unlocked with the Special Card
    GSWF_YUU_BOAT_GAME_UNLOCKED = 1233,        // Boat Game unlocked with the Platinum Card
    GSWF_YUU_TUBE_GAME_UNLOCKED = 1234,        // Tube Game unlocked with the Gold Card
    GSWF_YUU_PAPER_GAME_UNLOCKED = 1235,       // Paper Game unlocked with the Silver Card
    GSWF_GOR03_DON_PIANTA_TICKET_GIVEN = 1236, // Don Pianta handed over the blimp ticket
    GSWF_GOR03_LOTTERY_EXPLAINED = 1237,       // Happy Lucky Lottery explained
    // First-time lottery result message variant shown (kuji_bomb_055 callback, case A)
    GSWF_GOR03_LOTTERY_FIRST_RESULT_A = 1238,
    // First-time lottery result message variant shown (kuji_bomb_055 callback, case B)
    GSWF_GOR03_LOTTERY_FIRST_RESULT_B = 1239,
    // Set a new top score in the Plane Game (yuu_00, ranking type 0)
    GSWF_YUU_PLANE_GAME_RECORD = 1240,
    // Set a new top score in the Boat Game (yuu_01, ranking type 3)
    GSWF_YUU_BOAT_GAME_RECORD = 1241,
    // Set a new top score in the Tube Game (yuu_02, ranking type 2)
    GSWF_YUU_TUBE_GAME_RECORD = 1242,
    // Set a new best (lowest) result in the Paper Game (yuu_03, ranking type 1)
    GSWF_YUU_PAPER_GAME_RECORD = 1243,
    // Rode the blimp back from Glitzville to Rogueport station; set twice, never tested
    GSWF_TOU00_BLIMP_RETURNED = 1244,
    // Frankly read the first Thousand-Year Door epigraphy; switches the tik_04 enemy formations
    GSWF_GOR02_FIRST_EPIGRAPHY_DONE = 1246,
    GSWF_GOR00_ITEMBOX_00 = 1247,         // gor_00 treasure chest mobj_box00 opened
    GSWF_GOR02_ITEMBOX_01 = 1248,         // gor_02 treasure chest mobj_box01 opened
    GSWF_GOR02_FRANKLY_FINAL_TALK = 1249, // Frankly's near-the-end research talk heard
    // Merlon greeted Mario this visit; cleared when the door opens
    GSWF_GOR02_MERLON_GREETED_THIS_VISIT = 1250,
    // Talked to Dazzle (Star Piece collector) once; later talks skip his introduction
    GSWF_TIK00_DAZZLE_FIRST_TALK = 1325,
    // Mario just used the sewer teleporter to the X-Naut Fortress; aji_07 plays the arrival and clears it
    GSWF_TIK00_TELEPORT_TO_AJI = 1326,
    // The tik_00 teleporter-room door has been passed from inside (after chapter 7); before that it does not open
    GSWF_TIK00_STG7_DOOR_OPENED = 1327,
    // Partner's comment after first returning by the teleporter to tik_00 (tik_00_tensou_0) has been given
    GSWF_TIK00_TELEPORT_RETURN_COMMENT = 1328,
    // Partner's comment on leaving the tik_00 teleporter room (tik_00_tensou_1) has been given
    GSWF_TIK00_TELEPORT_ROOM_COMMENT = 1329,
    GSWF_TIK00_PILLAR_BOMBED = 1330, // The cracked pillar in tik_00 was blown up with Bobbery
    GSWF_TIK01_WALL1_BOMBED = 1331,  // The first cracked wall in tik_01 (bom_kabe_1) was blown up
    // The cracked wall between tik_01 and tik_02 (bom_kabe_2/3) was blown up; shared by both maps
    GSWF_TIK01_WALL2_BOMBED = 1332,
    // The hidden switch in tik_03 (that the Puni elder mentioned) has the secret passage open; the switch toggles it
    GSWF_TIK03_SECRET_DOOR_OPEN = 1334,
    // The blue switch in tik_04 was pressed, swapping the fake platform for the real one (dai_6)
    GSWF_TIK04_SWITCH_PRESSED = 1335,
    GSWF_TIK04_CLOUD_BLOWN = 1336, // Flurrie blew away the wall paper/cloud (win_1) in tik_04
    // The Black Key (for the Plane Mode chest in tik_19) was picked up in tik_04
    GSWF_TIK04_BLACK_KEY_TAKEN = 1337,
    // The big yellow block (MOBJ_Lv1BigBigBlock) in tik_04 was broken
    GSWF_TIK04_BIG_BLOCK_BROKEN = 1338,
    // Mario made his first Plane Mode flight in tik_04 and landed on the far platform (stops the flight-check script)
    GSWF_TIK04_FIRST_FLIGHT_DONE = 1339,
    // The big blue block (MOBJ_Lv2BigBlock) in tik_07 was broken
    GSWF_TIK07_BIG_BLOCK_BROKEN = 1340,
    // Reached the Twilight Town pipe area (tik_08); Frankly and Darkly stop hinting
    GSWF_TIK08_TWILIGHT_PIPE_REACHED = 1341,
    GSWF_TIK11_CHET_RIPPO_MET = 1342, // Chet Rippo's first-meeting introduction has been heard
    // The first big yellow block (block00) in tik_15 was broken
    GSWF_TIK15_BIG_BLOCK_A_BROKEN = 1343,
    // The second big yellow block (block01) in tik_15 was broken
    GSWF_TIK15_BIG_BLOCK_B_BROKEN = 1344,
    // The tornado switch in tik_16 opened the pipe to the Great Tree (mri_00), which also shows the pipe there
    GSWF_TIK16_PIPE_MRI_OPEN = 1345,
    // The tornado switch in tik_16 opened the pipe to Petalburg (nok_01)
    GSWF_TIK16_PIPE_NOK_OPEN = 1346,
    GSWF_TIK16_BIG_BLOCK_BROKEN = 1347, // The big yellow block in tik_16 was broken
    // The tornado switch in tik_17 opened the pipe to Poshley Heights (pik_01)
    GSWF_TIK17_PIPE_PIK_OPEN = 1348,
    // The tornado switch in tik_17 opened the pipe to Keelhaul Key (muj_02)
    GSWF_TIK17_PIPE_MUJ_OPEN = 1349,
    // The big blue block (MOBJ_Lv2BigBigBlock) in tik_17 was broken
    GSWF_TIK17_BIG_BLOCK_BROKEN = 1350,
    GSWF_TIK18_CLOUD_BLOWN = 1351, // Flurrie blew away the wall paper/cloud (s_win_1) in tik_18
    // The black chest in tik_19 was opened with the Black Key; Mario got the Plane Mode curse (story set to 15)
    GSWF_TIK19_BLACK_CHEST_OPENED = 1352,
    // The locked black chest in tik_19 has spoken to Mario once (asks for its key)
    GSWF_TIK19_BLACK_CHEST_TALKED = 1353,
    GSWF_TIK00_SOFT_STOMP_CHEST_OPENED = 1354,     // Chest in tik_00 (Soft Stomp badge) opened
    GSWF_TIK01_DEFEND_PLUS_P_CHEST_OPENED = 1355,  // Chest in tik_01 (Defend Plus P badge) opened
    GSWF_TIK03_DAMAGE_DODGE_TAKEN = 1356,          // Damage Dodge badge on the floor of tik_03 picked up
    GSWF_TIK04_HAPPY_HEART_P_CHEST_OPENED = 1357,  // Chest in tik_04 (Happy Heart P badge) opened
    GSWF_TIK04_PRETTY_LUCKY_BLOCK_HIT = 1358,      // Hidden block in tik_04 (Pretty Lucky badge) hit
    GSWF_TIK07_FLOWER_SAVER_P_CHEST_OPENED = 1359, // Chest in tik_07 (Flower Saver P badge) opened
    GSWF_TIK10_CHEST_OPENED = 1360,                // Chest in tik_10 opened (gives a Mushroom)
    GSWF_TIK14_CHEST_OPENED = 1361,                // Chest in tik_14 opened (gives a Mushroom)
    GSWF_TIK15_MUSHROOM_BLOCK_HIT = 1362,          // Item block in tik_15 (Mushroom) hit
    GSWF_TIK15_FIRE_FLOWER_BLOCK_HIT = 1363,       // Item block in tik_15 (Fire Flower) hit
    GSWF_TIK17_FP_PLUS_CHEST_OPENED = 1364,        // Chest in tik_17 (FP Plus badge) opened
    GSWF_TIK18_SLOW_SHROOM_BLOCK_HIT = 1365,       // Item block in tik_18 (Slow Shroom) hit
    GSWF_TIK18_GRADUAL_SYRUP_BLOCK_HIT = 1366,     // Item block in tik_18 (Gradual Syrup) hit
    GSWF_TIK20_DEFEND_PLUS_TAKEN = 1367,           // Defend Plus badge in tik_20 picked up
    GSWF_TIK21_SPIKE_SHIELD_CHEST_OPENED = 1368,   // Chest in tik_21 (Spike Shield badge) opened
    // The tik_01 music has faded in once (later entries start it without the fade)
    GSWF_TIK01_BGM_STARTED = 1369,
    // The partner's Plane Mode explanation in tik_04 (mac_0_094_01) has been given; later tries get the short tip
    GSWF_TIK04_PLANE_TIP_GIVEN = 1370,
    // Chet Rippo gave his greeting this visit (later talks go straight to the menu); cleared when tik_11 loads
    GSWF_TIK11_CHET_RIPPO_GREETED = 1371,
    // The Dull Bones in gon_03 just shoved Mario back out to gon_01; gon_01 plays the pushed-out entry and clears it
    GSWF_GON03_PUSHED_OUT = 1476,
    // Mario has been shoved out of gon_03 by the Dull Bones at least once
    GSWF_GON03_PUSHED_OUT_ONCE = 1477,
    // Mario has been shoved out of gon_03 a second time; the partner then wonders who controls them (stg1_gon_13/14)
    GSWF_GON03_PUSHED_OUT_TWICE = 1478,
    // The partner's complaint while the Dull Bones push (stg1_gon_11/12) has been given
    GSWF_GON03_PUSHING_COMMENT = 1479,
    // At the skeleton in gon_03 Mario told Koops to read his father's letter (set only, never read)
    GSWF_GON03_KOOPS_READ_LETTER = 1481,
    // State of the flipping staircase in gon_04, toggled by the red switch
    GSWF_GON04_STAIRS_FLIPPED = 1482,
    // Blue switch mobj_hashi0 in gon_04 pressed (lowers a bridge)
    GSWF_GON04_BRIDGE_SWITCH_A = 1483,
    // Blue switch mobj_hashi1 in gon_04 pressed (lowers the other bridge)
    GSWF_GON04_BRIDGE_SWITCH_B = 1484,
    GSWF_GON04_BIG_BLOCK_A_BROKEN = 1485, // The big yellow block mobj_blk00 in gon_04 was broken
    GSWF_GON04_BIG_BLOCK_B_BROKEN = 1486, // The big blue block mobj_blk01 in gon_04 was broken
    GSWF_GON04_BIG_BLOCK_C_BROKEN = 1487, // The big blue block mobj_blk02 in gon_04 was broken
    GSWF_GON04_DOOR_UNLOCKED = 1488,      // Locked door in gon_04 opened with a Castle Key
    GSWF_GON05_DOOR_A_UNLOCKED = 1489,    // Lower locked door in gon_05 opened with a Castle Key
    GSWF_GON05_DOOR_B_UNLOCKED = 1490,    // Upper locked door in gon_05 opened with a Castle Key
    GSWF_GON06_CELL_SWITCH = 1491,        // Red switch in gon_06 pressed, raising the barred gate
    // The locked black chest in gon_06 has spoken to Mario once (asks for its key)
    GSWF_GON06_BLACK_CHEST_TALKED = 1492,
    // The black chest in gon_06 was opened with the Black Key (Paper Mode curse); forced on from story 45
    GSWF_GON06_BLACK_CHEST_OPENED = 1493,
    // Chest in gon_07 opened (Black Key for the gon_06 chest); forced on from story 43
    GSWF_GON07_BLACK_KEY_CHEST_OPENED = 1494,
    GSWF_GON07_WALL_BOMBED = 1495,   // The cracked wall in gon_07 was blown open
    GSWF_GON08_DOOR_UNLOCKED = 1496, // Locked door in gon_08 opened with a Castle Key
    // Skips Hooktail's entrance scene in gon_11; only set by the event-table jump stg1_16_init01
    GSWF_GON11_HOOKTAIL_INTRO_SKIP = 1498,
    // Floating blue switch in gon_13 pressed; makes the chest (mobj_box04) appear
    GSWF_GON13_SWITCH_PRESSED = 1499,
    // After beating Hooktail Koops was not the active partner, so he was swapped in for the scene; nok_01 farewell uses it
    GSWF_GON11_KOOPS_SWAPPED_IN = 1500,
    GSWF_GON01_HP_PLUS_TAKEN = 1501,          // HP Plus badge in gon_01 picked up
    GSWF_GON02_POWER_BOUNCE_BLOCK_HIT = 1502, // Badge block in gon_02 (Power Bounce) hit
    GSWF_GON05_LAST_STAND_P_TAKEN = 1503,     // Last Stand P badge in gon_05 picked up
    GSWF_GON06_ATTACK_FX_R_TAKEN = 1504,      // Attack FX R badge in gon_06 picked up
    GSWF_GON08_LIFE_SHROOM_TAKEN = 1505,      // Life Shroom in gon_08 picked up
    // Chest mobj_box00 in gon_12 opened (Castle Key); forced on from story 51
    GSWF_GON12_CASTLE_KEY_CHEST_OPENED = 1507,
    GSWF_GON12_MUSHROOM_CHEST_OPENED = 1508,    // Chest mobj_box01 in gon_12 opened (Mushroom)
    GSWF_GON12_HONEY_SYRUP_CHEST_OPENED = 1509, // Chest mobj_box02 in gon_12 opened (Honey Syrup)
    GSWF_GON13_UP_ARROW_CHEST_OPENED = 1510,    // Chest mobj_box04 in gon_13 opened (Up Arrow)
    // Mario first met Ms. Mowz in gon_12 with Koops as partner; the ending uses an alternate picture (image 9 -> 53)
    GSWF_GON12_MOWZ_MET_WITH_KOOPS = 1511,
    // Mario has entered Petalburg (nok_00) at least once: set on the first nok_00 load; only its own guard reads it
    GSWF_NOK00_VISITED = 1624,
    // Koopie Koo's first introduction (stg1_nok_64) has been heard
    GSWF_NOK01_KOOPIE_KOO_MET = 1625,
    // Koopie Koo told Mario about her feelings for Koops (stg1_nok_65/66)
    GSWF_NOK01_KOOPIE_KOO_CONFIDED = 1626,
    // Koopie Koo has talked to Mario with Koops as his partner (stg1_nok_67/68, nok_01); moves her idle placement
    GSWF_NOK01_KOOPIE_KOO_TALKED_TO_KOOPS = 1627,
    GSWF_NOK01_MEGA_RUSH_P_TAKEN = 1628, // Mega Rush P badge in nok_01 picked up
    // Turtley Leaf reward for trouble #8 (Kroop in nok_01) picked up, or left on the ground when Mario's pockets were full
    GSWF_NOK01_TURTLEY_LEAF_TAKEN = 1629,
    // Mario got the Sun Stone (from the Fuzzy in hei_12); also unlocks Koops joining in hei_01
    GSWF_HEI_SUN_STONE_TAKEN = 1774,
    GSWF_HEI_MOON_STONE_TAKEN = 1775,      // Mario got the Moon Stone (from the Fuzzy in hei_08)
    GSWF_HEI00_SUN_STONE_PLACED = 1776,    // The Sun Stone was set into its pedestal in hei_00
    GSWF_HEI00_MOON_STONE_PLACED = 1777,   // The Moon Stone was set into its pedestal in hei_00
    GSWF_HEI00_TREE_MUSHROOM_TAKEN = 1778, // Mushroom shaken out of a tree in hei_00 picked up
    GSWF_HEI00_MUSHROOM_BLOCK_HIT = 1780,  // Item block in hei_00 (Mushroom) hit
    // Koops caught up with Mario in hei_01 and asked to come along (stg1_hei_06); later he waits at the side
    GSWF_HEI01_KOOPS_ASKED_TO_JOIN = 1781,
    GSWF_HEI01_KOOPIE_KOO_FAREWELL = 1782,      // Koopie Koo's send-off scene in hei_01 has played
    GSWF_HEI01_BUSH_PIPE_REVEALED = 1783,       // The pipe hidden in the bush in hei_01 was revealed
    GSWF_HEI01_BUSH_MYSTERY_TAKEN = 1784,       // Mystery item from a bush in hei_01 picked up
    GSWF_HEI01_FIRE_FLOWER_BLOCK_HIT = 1785,    // Item block in hei_01 (Fire Flower) hit
    GSWF_HEI02_TREE_COIN_TAKEN = 1786,          // Coin shaken out of a tree in hei_02 picked up
    GSWF_HEI02_POW_BLOCK_ITEM_BLOCK_HIT = 1787, // Item block in hei_02 (POW Block) hit
    // The first of the two enemies hiding behind the pillars in hei_03 was beaten (both flags are set when either battle is won); hei_05 hashira_evt also reads it
    GSWF_HEI03_PILLAR_ENEMY_A_DEFEATED = 1788,
    // The second pillar enemy in hei_03 was beaten (set together with GSWF 1788)
    GSWF_HEI03_PILLAR_ENEMY_B_DEFEATED = 1789,
    GSWF_HEI04_BUSH_COIN_TAKEN = 1790, // Coin from a bush in hei_04 picked up
    GSWF_HEI04_TREE_COIN_TAKEN = 1791, // Coin shaken out of a tree in hei_04 picked up
    // The first of the two enemies hiding behind the pillars in hei_05 was beaten (set together with GSWF 1793)
    GSWF_HEI05_PILLAR_ENEMY_A_DEFEATED = 1792,
    GSWF_HEI05_PILLAR_ENEMY_B_DEFEATED = 1793, // The second pillar enemy in hei_05 was beaten
    GSWF_HEI06_BUSH_COIN_TAKEN = 1794,         // Coin from a bush in hei_06 picked up
    GSWF_HEI06_FIRE_FLOWER_BLOCK_HIT = 1795,   // Item block in hei_06 (Fire Flower) hit
    GSWF_HEI10_MULTIBOUNCE_BLOCK_HIT = 1796,   // Badge block in hei_10 (Multibounce) hit
    GSWF_HEI13_CLOSE_CALL_BLOCK_HIT = 1797,    // Badge block in hei_13 (Close Call) hit
    GSWF_HEI13_HAPPY_HEART_TAKEN = 1798,       // Happy Heart badge in hei_13 picked up
    GSWF_HEI13_COIN_BRICK_EMPTIED = 1799,      // The multi-coin brick (10m) in hei_13 was emptied
    GSWF_HEI01_BUSH_COIN_B_TAKEN = 1800,       // Coin from bush 7 in hei_01 picked up
    GSWF_HEI04_BUSH_POW_BLOCK_TAKEN = 1801,    // POW Block from a bush in hei_04 picked up
    GSWF_HEI01_BUSH_COIN_A_TAKEN = 1802,       // Coin from bush 2 in hei_01 picked up
    // Blue switch spawned for Koops's shell-hold lesson; cleared each time the lesson starts
    GSWF_HEI_KOOPS_LECTURE_SWITCH = 1803,
    // Timed double switch in hei_00 (raises the pipe until story 34)
    GSWF_HEI00_TIMER_SWITCH = 1804,
    // Goombella's hei_01 tip about asking her for advice has been given
    GSWF_HEI01_GOOMBELLA_TIP_GIVEN = 1805,
    GSWF_HEI06_INN_COUPON_TAKEN = 1806, // Inn Coupon in hei_06 picked up
    // The crying shopkeeper in Twilight Town told Mario her husband became a pig and opened her storeroom to him
    GSWF_USU01_SHOPKEEPER_ASKED_HELP = 1925,
    // The storeroom lock in usu_01 was opened with the Shop Key
    GSWF_USU01_STOREROOM_UNLOCKED = 1926,
    // The mother who asked for food in usu_01 turned into a pig in front of her children (before story 200)
    GSWF_USU01_MOTHER_TURNED_PIG = 1927,
    // Partner reacted to the two gossiping crows in Twilight Town's west street (stg4_usu_149/150); later crow talks skip the reaction
    GSWF_USU01_CROWS_PARTNER_REACTION = 1928,
    // Talked to Mayor Kroop once while Doopliss has Mario's name (GSW0 200-209); later talks use the short line stg4_usu_25
    GSWF_USU00_MAYOR_NAMELESS_FIRST_TALK = 1929,
    // Mayor Kroop spoke to the nameless Mario when he walked close (proximity scene, GSW0 203-209, stg4_usu_23); plays once
    GSWF_USU00_MAYOR_APPROACHED_NAMELESS = 1930,
    // Twilight Town black chest opened and its paper curse (Tube Mode) received (GSW0 -> 187); also forced on in usu_01 init once GSW0>=187
    GSWF_USU01_BLACK_CHEST_OPENED = 1931,
    // Heard the Twilight Town black chest's first speech asking for its key (stg4_usu_majin3_01..07); later checks go straight to the key test
    GSWF_USU01_BLACK_CHEST_FIRST_TALK = 1932,
    // Coin hidden in a bush in Twilight Town east (usu_00 kusa 06) collected
    GSWF_USU00_BUSH_COIN_TAKEN = 1933,
    GSWF_USU01_DEFEND_PLUS_CHEST_OPENED = 1934, // Twilight Town west chest (Defend Plus) opened
    // Life Shroom pickup in Twilight Town west (usu_01) collected
    GSWF_USU01_LIFE_SHROOM_TAKEN = 1935,
    // Boo's Sheet pickup in Twilight Town west (usu_01) collected
    GSWF_USU01_BOOS_SHEET_TAKEN = 1936,
    // Jammin' Jelly pickup in Twilight Town west (usu_01) collected
    GSWF_USU01_JAMMIN_JELLY_TAKEN = 1937,
    // Meteor Meal reward from trouble #20 (the Twilight Town aunt) collected, either straight to the bag or after it was set down because the bag was full
    GSWF_USU01_TROUBLE20_METEOR_MEAL_TAKEN = 1938,
    // Inn Coupon pickup in Twilight Town west (usu_01) collected
    GSWF_USU01_INN_COUPON_TAKEN = 1939,
    // Vivian's first remark on entering Twilight Trail gra_01 after she joined (GSW0>=206, stg4_gra_16_01) done
    GSWF_GRA01_VIVIAN_FIRST_TRAIL_TALK = 2075,
    // Chain on the gate in front of Creepy Steeple (gra_06) broken and the gate opened
    GSWF_GRA06_STEEPLE_GATE_OPENED = 2078,
    // Set just before a drop-down map change (gra_06 well -> jin_09, jin_00 pedestal -> jin_06, jin_11 hole -> jin_07); the destination room plays the falling-in entrance and clears it
    GSWF_STG4_DROP_IN_ENTRANCE = 2079,
    // Breakable floor panel in Twilight Trail gra_05 broken (only placed while GSW0<191)
    GSWF_GRA05_BREAKING_FLOOR_BROKEN = 2080,
    // Doopliss has stolen Mario's body and name (set at GSW0 201 in jin_04, cleared when Vivian joins at 206); battle table switches the gra_01 enemies to their shadow-Mario formations
    GSWF_STG4_MARIO_IS_SHADOW = 2081,
    GSWF_GRA01_COIN_BLOCK_HIT = 2082,     // Coin ? block in Twilight Trail gra_01 (blk00) hit
    GSWF_GRA03_COIN_BLOCK_EMPTIED = 2083, // Ten-coin block in Twilight Trail gra_03 (blk00) emptied
    // ? block holding an Earth Quake in Twilight Trail gra_03 hit
    GSWF_GRA03_EARTH_QUAKE_BLOCK_HIT = 2084,
    // Hidden ten-coin block in Twilight Trail gra_05 emptied
    GSWF_GRA05_HIDDEN_COIN_BLOCK_EMPTIED = 2085,
    // ? block holding the Hammer Throw badge in Twilight Trail gra_04 hit
    GSWF_GRA04_HAMMER_THROW_BLOCK_HIT = 2086,
    // Hidden ? block holding a Super Shroom in Twilight Trail gra_01 hit
    GSWF_GRA01_HIDDEN_SUPER_SHROOM_BLOCK_HIT = 2087,
    // Ten-coin block in Twilight Trail gra_01 (blk06) emptied
    GSWF_GRA01_TEN_COIN_BLOCK_EMPTIED = 2088,
    GSWF_GRA00_COIN_BLOCK_EMPTIED = 2089, // Ten-coin block in Twilight Trail gra_00 (blk02) emptied
    // Hidden ? block holding a coin in Twilight Trail gra_06 hit
    GSWF_GRA06_HIDDEN_COIN_BLOCK_HIT = 2090,
    // Black Key for the Twilight Town chest picked up in Twilight Trail gra_00
    GSWF_GRA00_BLACK_KEY_TAKEN = 2091,
    // Atomic Boo beaten in Creepy Steeple; Frankly reminds Mario to tattle it
    GSWF_JIN00_ATOMIC_BOO_DEFEATED = 2226,
    // The Boos lifted Mario out of Creepy Steeple; gra_06 plays the thrown-out landing on the next load and clears it
    GSWF_JIN00_BOOS_CARRIED_MARIO_OUT = 2227,
    // Locked north door in the Creepy Steeple main hall (jin_00, first Steeple Key) unlocked
    GSWF_JIN00_NORTH_DOOR_UNLOCKED = 2228,
    // Flurrie blew away the peeling wall in Creepy Steeple jin_06
    GSWF_JIN06_PEELING_WALL_BLOWN = 2229,
    GSWF_JIN08_STEEPLE_KEY_TAKEN = 2230, // Steeple Key taken from the box in Creepy Steeple jin_08
    // Locked door between Creepy Steeple jin_08 and jin_07 (second Steeple Key) unlocked
    GSWF_JIN08_DOOR_UNLOCKED = 2231,
    // The Creepy Steeple parrot (jin_08) has let slip Doopliss's name: set by its first talk with Vivian out
    // (oumu_juyo_talk, stg4_jin_43; later talks give stg4_jin_44). usu_01 also reads it: once it is set the
    // sniffling/shouting from the Twilight Town shop (usu01_gusun) is no longer heard
    GSWF_JIN08_PARROT_REVEALED_DOOPLISS_NAME = 2232,
    // Breakable floor in Creepy Steeple jin_11 broken (event STG4_13_03 Breaking the Floor; only placed while GSW0<208)
    GSWF_JIN11_FLOOR_BROKEN = 2233,
    // Mario and partner's confused look-around on the looping staircase (jin_01/jin_02) played once
    GSWF_JIN_ENDLESS_STAIRS_REACTION_SEEN = 2234,
    GSWF_JIN05_COOKBOOK_CHEST_OPENED = 2235, // Creepy Steeple jin_05 chest (Cookbook) opened
    // Creepy Steeple jin_05 second chest (Ice Smash) opened
    GSWF_JIN05_ICE_SMASH_CHEST_OPENED = 2237,
    // Creepy Steeple jin_06 chest (Flower Saver) opened
    GSWF_JIN06_FLOWER_SAVER_CHEST_OPENED = 2238,
    GSWF_JIN08_POWER_PLUS_CHEST_OPENED = 2239,  // Creepy Steeple jin_08 chest (Power Plus) opened
    GSWF_JIN08_MR_SOFTENER_CHEST_OPENED = 2240, // Creepy Steeple jin_08 chest (Mr. Softener) opened
    // ? block holding the Tornado Jump badge in Creepy Steeple jin_10 hit
    GSWF_JIN10_TORNADO_JUMP_BLOCK_HIT = 2241,
    // Lucky Start dropped by the Atomic Boo after its battle collected (the script also sets it right after the drop)
    GSWF_JIN00_ATOMIC_BOO_LUCKY_START_TAKEN = 2242,
    // Arena intro done; tou_02 runs the "guard backs off" scene on arrival and clears it
    GSWF_TOU_ARENA_INTRO_TO_LOBBY = 2374,
    // Grubba's first-visit tour: set in his office (tou_05); tou_04 runs his escort to the champion's room (tou_07),
    // which he shows off; back in the office tou_05 clears it and runs the next scene (evt_sensyu2)
    GSWF_TOU_GRUBBA_ESCORT_PENDING = 2375,
    GSWF_TOU_JOLENE_ESCORT_1_PENDING = 2376, // Jolene escort #1 from her office to tou_04 pending
    // Jolene escort to the major-league locker room pending (after promotion)
    GSWF_TOU_JOLENE_ESCORT_MAJORS_PENDING = 2377,
    // Jolene escort to the champion's room pending (after winning the belt)
    GSWF_TOU_JOLENE_ESCORT_CHAMP_PENDING = 2378,
    // Security is escorting Mario to the minor-league locker room in tou_04
    GSWF_TOU04_GUARD_ESCORT_MINORS = 2379,
    // Security is escorting Mario to the major-league locker room in tou_04
    GSWF_TOU04_GUARD_ESCORT_MAJORS = 2380,
    // Security is escorting Mario to the title-match waiting room (tou_11)
    GSWF_TOU04_GUARD_ESCORT_TITLE_ROOM = 2381,
    GSWF_TOU04_GUARD_ESCORT_CHAMP_ROOM = 2382, // Security is escorting Mario to the champion's room
    // Title match with Rawk Hawk reserved; Mario is held in tou_11 until he escapes via the toilet
    GSWF_TOU_TITLE_MATCH_RESERVED = 2383,
    GSWF_TOU04_ARRIVED_FROM_TOILET_A = 2384, // Came out of the tou_09 toilet pipe into tou_04
    GSWF_TOU04_ARRIVED_FROM_TOILET_B = 2385, // Came out of the tou_08 toilet pipe into tou_04
    GSWF_TOU11_LOCKED_IN_SEEN = 2386,        // Locked in the room scene in tou_11 played
    GSWF_TOU11_POSTER_BLOWN = 2387,          // Flurrie blew the poster off the tou_11 wall
    GSWF_TOU_MATCH_RESERVED = 2388,          // A match is reserved and Mario must wait for Security
    // Just came back from a match; the locker-room init runs the post-match scene and clears it
    GSWF_TOU_MATCH_RESULT_PENDING = 2389,
    // Set when leaving the minor-league locker room; never tested anywhere
    GSWF_TOU10_ROOM_EXITED = 2390,
    GSWF_TOU_EGG_STORY_SKIP = 2391, // Debug-start flag (stg3_12 skip): tou_10 raises GSW0 to 137
    // Post-first-match (Goomba Bros) scene in tou_10 played
    GSWF_TOU10_FIRST_MATCH_AFTER_SEEN = 2392,
    // Promotion to the major league in progress; tou_08 continues the scene
    GSWF_TOU_PROMOTION_PENDING = 2393,
    // The tou_08 guard let Mario through (talk_gardman with LF(1) set; also set by the stg3_20 rank-1 skip); never tested
    GSWF_TOU08_GUARD_LET_THROUGH = 2394,
    GSWF_TOU_GOOMBA_BROS_OPENING_SEEN = 2395, // Goomba Bros match opening played
    GSWF_TOU_GOOMBA_BROS_WIN_SEEN = 2396,     // Goomba Bros victory scene played (first fight money)
    GSWF_TOU_IRON_CLEFTS_OPENING_SEEN = 2397, // Iron Clefts match opening played
    GSWF_TOU_IRON_CLEFTS_WIN_SEEN = 2398,     // Iron Clefts victory scene played
    // Title-match opening against Rawk Hawk played (NPCs ask why Mario is not in the ring until then)
    GSWF_TOU_CHAMP_OPENING_SEEN = 2399,
    GSWF_TOU_CHAMP_WIN_SEEN = 2400, // Title-match victory scene played
    // Air-duct grate in Grubba's office fell (Mario dropped in)
    GSWF_TOU05_DUCT_GRATE_FALLEN = 2401,
    GSWF_TOU02_LOBBY_CROWD_SEEN = 2402,       // Lobby fan-crowd scene after the first match played
    GSWF_TOU02_LOBBY_CROWD_CHAMP_SEEN = 2403, // Lobby fan-crowd scene as champion played
    GSWF_TOU_KING_K_MATCH_SCENE = 2405,       // King K pre-match scene (opponent 18, evt_michel_1) played
    // Rank-18 locker-room scene (evt_michel_2) played (also set by the stg3_07 skip)
    GSWF_TOU_RANK18_SCENE = 2406,
    GSWF_TOU_RANK17_SCENE = 2407, // Rank-17 scene (evt_michel_3) played
    GSWF_TOU_RANK16_SCENE = 2408, // Rank-16 scene (evt_michel_4) played
    GSWF_TOU_RANK15_SCENE = 2409, // Rank-15 scene (evt_michel_5) played
    GSWF_TOU_RANK14_SCENE = 2410, // Rank-14 scene (evt_michel_6) played
    GSWF_TOU_RANK13_SCENE = 2411, // Rank-13 scene (evt_michel_7) played
    // Reached rank 12: King K leaves; ranking hides FIGHTER_KP_KOOPAS
    GSWF_TOU_RANK12_KING_K_GONE = 2412,
    // Reached rank 11: evt_michel_8 played and Sir Swoop enters the ranking
    GSWF_TOU_RANK11_SWOOPS_JOINS = 2413,
    // Rank-10 scene played; set only by the story-skip setup stg3_20_init_10, never read
    GSWF_TOU_RANK10_SCENE = 2414,
    // Rank-9 scene played; set only by the story-skip setup stg3_20_init_9, never read
    GSWF_TOU_RANK9_SCENE = 2415,
    GSWF_TOU_MAIL1_RECEIVED = 2416,   // Rank 8-10: first anonymous e-mail scene played
    GSWF_TOU_MAIL2_RECEIVED = 2417,   // Rank 7: second e-mail (and random-battle raid) played
    GSWF_TOU_CAKE_EVENT_DONE = 2418,  // Rank 6: fan-cake scene played
    GSWF_TOU_BOWSER_RAID_DONE = 2419, // Rank 5: Bowser raid aftermath played
    GSWF_TOU_MAIL3_RECEIVED = 2420,   // Rank 4: third e-mail played
    // Rank 3: fourth e-mail; the Bandit fighter leaves and The Destructors (Spinia) enter the ranking
    GSWF_TOU_MAIL4_RECEIVED = 2421,
    // Rank-2 scene played; set only by the story-skip setup stg3_20_init_2, never read
    GSWF_TOU_RANK2_SCENE = 2422,
    GSWF_TOU_RANK1_SCENE = 2423, // Rank-1 scene played
    // Champion scene played; set only by the story-skip setup stg3_30_init, never read
    GSWF_TOU_CHAMPION_SCENE = 2424,
    // tou_06 storage-room yellow block "a" smashed (set by the block mobj; the stg3_20_12 skip sets all eight)
    GSWF_TOU06_BLOCK_A_BROKEN = 2425,
    // tou_06 storage-room yellow block "b" smashed (set by the block mobj; the stg3_20_12 skip sets all eight)
    GSWF_TOU06_BLOCK_B_BROKEN = 2426,
    // tou_06 storage-room yellow block "c" smashed (set by the block mobj; the stg3_20_12 skip sets all eight)
    GSWF_TOU06_BLOCK_C_BROKEN = 2427,
    // tou_06 storage-room yellow block "d" smashed (set by the block mobj; the stg3_20_12 skip sets all eight)
    GSWF_TOU06_BLOCK_D_BROKEN = 2428,
    // tou_06 storage-room yellow block "e" smashed (set by the block mobj; the stg3_20_12 skip sets all eight)
    GSWF_TOU06_BLOCK_E_BROKEN = 2429,
    // tou_06 storage-room yellow block "f" smashed (set by the block mobj; the stg3_20_12 skip sets all eight)
    GSWF_TOU06_BLOCK_F_BROKEN = 2430,
    // tou_06 storage-room yellow block "g" smashed (set by the block mobj; the stg3_20_12 skip sets all eight)
    GSWF_TOU06_BLOCK_G_BROKEN = 2431,
    // tou_06 storage-room yellow block "h" smashed (set by the block mobj; the stg3_20_12 skip sets all eight)
    GSWF_TOU06_BLOCK_H_BROKEN = 2432,
    GSWF_TOU06_BLOCK_I_BROKEN = 2433, // tou_06 yellow block "i" smashed
    GSWF_TOU06_BLOCK_J_BROKEN = 2434, // tou_06 yellow block "j" smashed
    // Flurrie blew the stickers off the second container in tou_06
    GSWF_TOU06_CONTAINER_BLOWN = 2435,
    // Storage-room padlock in tou_04 opened with the storage key
    GSWF_TOU04_STORAGE_LOCK_OPEN = 2436,
    GSWF_TOU06_LOCK_OPEN = 2437, // Padlock in tou_06 opened with the second storage key
    // Blue switch that raises the hidden stairway in tou_06 pressed
    GSWF_TOU06_STAIR_SWITCH_HIT = 2438,
    GSWF_TOU06_BIG_BLOCK_BROKEN = 2439, // Large yellow block "aa" in tou_06 smashed
    // Large yellow block in the minor-league locker room smashed (Super Hammer)
    GSWF_TOU10_BIG_BLOCK_BROKEN = 2440,
    GSWF_TOU12_BIG_BLOCK_BROKEN = 2441, // Large yellow block in tou_12 smashed
    GSWF_TOU_LAST_MATCH_WON = 2442,     // Last Glitz Pit match was won (cleared on a loss)
    // Last match result bit 4 (condition met): next opponent is the fighter above instead of below
    GSWF_TOU_LAST_RULE_MET = 2443,
    // Heard the Bandit fighter's "research" talk about Grubba
    GSWF_TOU04_BANDIT_RESEARCH_TALK = 2444,
    GSWF_TOU04_STORAGE_JOLENE_SCOLD = 2445, // Jolene caught Mario in the storage area
    // First Yoshi-egg check in tou_10 done (scene shown if Mario lost to the Iron Clefts twice)
    GSWF_TOU10_EGG_HINT_CHECKED = 2446,
    // A fan cake is waiting in the locker room (Rawk Hawk eats it if refused)
    GSWF_TOU_CAKE_WAITING = 2447,
    GSWF_TOU_POISON_CAKE_EVENT = 2448, // Rank-3 poisoned-cake scene started
    // Poisoned cake placed in the locker room; cleared when eaten; never tested anywhere
    GSWF_TOU_POISON_CAKE_ON_TABLE = 2449,
    GSWF_TOU_PARTNER_POISONED = 2450,        // A partner ate the poisoned cake and is paralysed
    GSWF_TOU_PARTNER_POISON_CURED = 2451,    // Partners recovered from the poisoned cake
    GSWF_TOU08_SKIP_TO_143 = 2452,           // Debug-start flag (stg3_20 rank 7): tou_08 sets GSW0=143
    GSWF_TOU08_SKIP_TO_144 = 2453,           // Debug-start flag (stg3_20 rank 4): tou_08 sets GSW0=144
    GSWF_TOU08_SKIP_TO_153 = 2454,           // Debug-start flag (stg3_20 rank 1): tou_08 sets GSW0=153
    GSWF_TOU03_CHAMPION_CROWNED_SEEN = 2455, // Belt-presentation scene in the ring played
    GSWF_TOU02_POSTER_1_SEEN = 2456,         // Lobby poster 1 (evt_poster_1) checked in tou_02
    GSWF_TOU02_POSTER_2_SEEN = 2457,         // Lobby poster 2 (evt_poster_2) checked in tou_02
    GSWF_TOU02_POSTER_3_SEEN = 2458,         // Lobby poster 3 (evt_poster_3) checked in tou_02
    GSWF_TOU02_POSTER_4_SEEN = 2459,         // Lobby poster 4 (evt_poster_4) checked in tou_02
    GSWF_TOU02_POSTER_5_SEEN = 2460,         // Lobby poster 5 (evt_poster_5) checked in tou_02
    GSWF_TOU02_POSTER_6_SEEN = 2461,         // Lobby poster 6 (evt_poster_6) checked in tou_02
    GSWF_TOU02_POSTER_7_SEEN = 2462,         // Lobby poster 7 (evt_poster_7) checked in tou_02
    GSWF_TOU02_POSTER_8_SEEN = 2463,         // Lobby poster 8 (evt_poster_8) checked in tou_02
    GSWF_TOU02_POSTER_9_SEEN = 2464,         // Lobby poster 9 (evt_poster_9) checked in tou_02
    // Base of 23 per-fighter flags (2465+FIGHTER_*, 2465-2487): fighter is ranked below Mario; saved/loaded by rankingExit/rankingInit; event.c skips set 2484 downward (swSet(0x9B4 - i))
    GSWF_TOU_FIGHTER_BELOW_BASE = 2465,
    // Left Glitzville by gondola as champion; NPCs switch to post-chapter lines
    GSWF_TOU_LEFT_AS_CHAMPION = 2496,
    // Post-chapter: lobby guards stepped aside for the ex-champ
    GSWF_TOU02_GUARDS_STEP_ASIDE = 2497,
    // Post-chapter: a guard asked whether Mario is going to fight again
    GSWF_TOU04_REMATCH_GUARD_TALK = 2498,
    GSWF_TOU04_REMATCH_JOLENE_CALL = 2499, // Post-chapter: guard told Mario Jolene is waiting
    GSWF_TOU_REENTERED_LEAGUE = 2500,      // Post-chapter: Mario re-registered as a minor-league fighter
    // Post-chapter: duct exit grate in tou_13 knocked out again
    GSWF_TOU13_DUCT_EXIT_OPEN_REVISIT = 2501,
    // Post-chapter: duct entrance in the champion room knocked out again
    GSWF_TOU07_DUCT_ENTRY_OPEN_REVISIT = 2502,
    // Post-chapter: Mario became champion again (Rawk Hawk rematch won)
    GSWF_TOU_REMATCH_CHAMPION = 2503,
    GSWF_TOU_REMATCH_PROMOTED = 2504, // Post-chapter: promoted to the major league again
    // Post-chapter: dropped back to the minors (cleared on returning to rank 10)
    GSWF_TOU_REMATCH_MAJORS_LEFT = 2505,
    GSWF_TOU01_COIN_BRICK = 2507, // tou_01 hidden coin brick hblk01 exhausted
    // Star Piece taken from Grubba's desk drawer (the flag that guards it; GSWF 5625 is set with it)
    GSWF_TOU05_DRAWER_STAR_PIECE_TAKEN = 2508,
    GSWF_TOU_GOOMBA_BROS_FIRST_STRIKE_SEEN = 2509, // Goomba Bros pre-bell attack scene played
    GSWF_TOU_IRON_CLEFTS_INTRO_SEEN = 2510,        // Iron Clefts battle intro taunt shown
    GSWF_TOU_IRON_CLEFTS_WEAKNESS_SEEN = 2511,     // Iron Clefts "weak point" reaction shown
    GSWF_TOU_IRON_CLEFTS_BEATEN = 2512,            // Beat the Iron Clefts once (rematch battle text changes)
    GSWF_TOU_RAWK_HAWK_INTRO_SEEN = 2513,          // Rawk Hawk battle entry taunt shown
    GSWF_TOU_RAWK_HAWK_PHASE1_SEEN = 2514,         // Rawk Hawk first mid-battle line shown
    GSWF_TOU_RAWK_HAWK_PHASE2_SEEN = 2515,         // Rawk Hawk second mid-battle line shown
    GSWF_TOU_RAWK_HAWK_PHASE3_SEEN = 2516,         // Rawk Hawk third mid-battle line shown
    GSWF_TOU04_GUARD1_STEPPED_ASIDE = 2517,        // Guard 1 in tou_04 stepped aside when Mario came in through s_bero_7 at STORY_STG3_20_04_CONFISCATED; the tou_10 fighters then switch from their _15 to their _14 lines
    GSWF_TOU12_FLATTENED_FIGHTER_TALK = 2518,      // Talked to the flattened fighter in tou_12
    GSWF_TOU01_ITEMBOX_00 = 2519,                  // tou_01 treasure chest opened
    GSWF_TOU04_LAST_STAND = 2520,                  // Last Stand badge in tou_04 picked up
    GSWF_TOU06_HP_PLUS_P = 2521,                   // HP Plus P badge in tou_06 picked up
    GSWF_TOU01_HIDDEN_SWITCH = 2522,               // Hidden tornado switch in tou_01 hit (opens the stairway)
    GSWF_TOU06_CHARGE_P = 2523,                    // Charge P badge in tou_06 picked up
    GSWF_TOU08_ICE_STORM = 2524,                   // Ice Storm in the major-league locker room picked up
    GSWF_TOU_DOOR_BUSY = 2526,                     // Mutex while a tou_01/tou_02 door animation runs
    GSWF_TOU01_TROUBLE24_ITEM_LEFT = 2528,         // Trouble #24 reward (Hot Sauce) left on the ground
    // Ranking points have been saved to GSW 519-564 (else initial points are used)
    GSWF_TOU_RANKING_SAVED = 2529,
    GSWF_TOU_SWOOPS_ADDED = 2530, // Sir Swoop added to the ranking (below Mario) once
    GSWF_TOU_SPINIA_ADDED = 2531, // The Destructors added to the ranking (below Mario) once
    // GSW 507 holds a valid last-opponent id for re-sorting the ranking
    GSWF_TOU_LAST_OPPONENT_VALID = 2532,
    GSWF_TOU01_INN_COUPON = 2533, // Inn Coupon in tou_01 picked up
    // Flurrie's necklace dropped by the Shadow Sirens after their Boggly Woods defeat collected; win_00 then sets up the post-fight NPC (GSW0<=112)
    GSWF_WIN00_NECKLACE_TAKEN = 2675,
    GSWF_WIN00_HONEY_SYRUP_TAKEN = 2676, // Honey Syrup pickup in Boggly Woods win_00 collected
    // ? block holding the Quake Hammer badge in Boggly Woods win_02 hit
    GSWF_WIN02_QUAKE_HAMMER_BLOCK_HIT = 2677,
    // Blue switch in Boggly Woods win_02 pressed; the platform (S_hikou) stays extended
    GSWF_WIN02_BLUE_SWITCH_PRESSED = 2678,
    GSWF_WIN03_VOLT_SHROOM_TAKEN = 2679, // Volt Shroom pickup in Boggly Woods win_03 collected
    // Selects the alternate battle groups for the win_02 Pale Piranha and Piranha Plant encounters; never set anywhere in this tree
    GSWF_WIN02_ALT_BATTLES = 2680,
    // Flurrie asked Mario to get her necklace back (GSW0 -> 83); the win_03 Piranha encounter uses its alternate formation from then on
    GSWF_WIN04_FLURRIE_REQUEST_HEARD = 2681,
    // Flurrie joined the party (GSW0 -> 87); win_00 Dark Puff/Pale Piranha encounters switch to their alternate formations
    GSWF_WIN04_FLURRIE_JOINED = 2682,
    // Hidden badge block holding P-Down, D-Up P in Boggly Woods win_02 hit
    GSWF_WIN02_HIDDEN_PDOWN_DUP_P_BLOCK_HIT = 2683,
    // Boggly Woods win_05 chest (Super Appeal P) opened
    GSWF_WIN05_SUPER_APPEAL_P_CHEST_OPENED = 2684,
    // Sleepy Sheep shaken out of a tree in Boggly Woods win_00 collected
    GSWF_WIN00_TREE_SLEEPY_SHEEP_TAKEN = 2685,
    GSWF_WIN01_TREE_COIN_TAKEN = 2686,  // Coin shaken out of a tree in Boggly Woods win_01 collected
    GSWF_WIN01_INN_COUPON_TAKEN = 2687, // Inn Coupon pickup in Boggly Woods win_01 collected
    GSWF_MRI00_FP_PLUS_TAKEN = 2825,    // FP Plus pickup outside the Great Tree (mri_00) collected
    // Punio started following Mario through the Great Tree entrance (set leaving mri_00 by the north-east exit at GSW0 88); mri_00 then shows the dancers
    GSWF_MRI00_PUNIO_FOLLOWING = 2826,
    // Answered Petuni's post-chapter quiz and got a Mystic Egg; cleared whenever Mario leaves the tree by the pipe, so it can be won once per visit
    GSWF_MRI01_PETUNI_QUIZ_EGG_GIVEN = 2827,
    // Coin hidden in the planter in Great Tree mri_01 collected
    GSWF_MRI01_PLANTER_COIN_TAKEN = 2828,
    // Puni Elder explained her powers after being freed (STG2_16, GSW0 95); before that the elder talk is a one-liner
    GSWF_MRI01_ELDER_POWERS_EXPLAINED = 2829,
    // Puni orb currently placed on the pedestal in Great Tree mri_02 (cleared when it is picked up again); drives the weight switch for the pipe
    GSWF_MRI02_ORB_ON_PEDESTAL = 2830,
    // Power Punch hidden in the planter in Great Tree mri_02 collected
    GSWF_MRI02_PLANTER_POWER_PUNCH_TAKEN = 2831,
    // Red Key used on the lock of the red cell (the Puni Elder's cell) in Great Tree mri_03
    GSWF_MRI03_RED_CELL_UNLOCKED = 2832,
    // Red cell door in mri_03 opened after unlocking (Puni Elder freed, STG2_14)
    GSWF_MRI03_RED_CELL_DOOR_OPEN = 2833,
    // Blue Key used on the lock of the blue cell (Petuni's cell) in Great Tree mri_03
    GSWF_MRI03_BLUE_CELL_UNLOCKED = 2834,
    // Blue cell door in mri_03 opened after unlocking (Petuni freed)
    GSWF_MRI03_BLUE_CELL_DOOR_OPEN = 2835,
    // Punio left the Puni group to wait in front of Petuni's cell (set at the STG2_20 reunion, cleared when she is freed); mri_puni skips him in follower checks
    GSWF_MRI03_PUNIO_WAITING_AT_CELL = 2836,
    GSWF_MRI04_ULTRA_SHROOM_CHEST_OPENED = 2837, // Great Tree mri_04 chest (Ultra Shroom) opened
    // Coin hidden in the planter in Great Tree mri_04 collected
    GSWF_MRI04_PLANTER_COIN_TAKEN = 2838,
    GSWF_MRI04_RED_KEY_TAKEN = 2839, // Red Key dropped by the X-Naut in Great Tree mri_04 collected
    // The little Jabbi in mri_04 gave Mario a Mushroom after the chapter; cleared whenever Mario leaves the tree by the pipe
    GSWF_MRI04_JABBI_MUSHROOM_GIVEN = 2840,
    // Lamp door between Great Tree mri_05 (west) and mri_01 (east) switched open; toggles with its switch
    GSWF_MRI05_WEST_DOOR_UNLOCKED = 2841,
    // Puni orb currently on the first (left) pedestal in Great Tree mri_05
    GSWF_MRI05_ORB_A_ON_PEDESTAL = 2842,
    // Puni orb currently on the second (right) pedestal in Great Tree mri_05
    GSWF_MRI05_ORB_B_ON_PEDESTAL = 2843,
    // Thunder Rage hidden in the planter in Great Tree mri_05 collected
    GSWF_MRI05_PLANTER_THUNDER_RAGE_TAKEN = 2844,
    // ? block holding Damage Dodge P in Great Tree mri_06 hit
    GSWF_MRI06_DAMAGE_DODGE_P_BLOCK_HIT = 2845,
    GSWF_MRI06_FAKE_WALL_BLOWN = 2846, // Flurrie blew away the fake wall in Great Tree mri_06
    // Punio called the Punies to fight the Jabbies in Great Tree mri_08 (STG2_18)
    GSWF_MRI08_JABBI_FIGHT_STARTED = 2847,
    // The Punies lost the Jabbi fight in mri_08; Mario is sent back to mri_06, where Punio comments and clears it
    GSWF_MRI08_JABBI_FIGHT_LOST = 2848,
    GSWF_MRI08_JABBI_FIGHT_WON = 2849, // The Punies beat the Jabbies in mri_08
    // Rolling wall panels in Great Tree mri_09 turned to the open layout; mri_puni loads the alternate Puni map data
    GSWF_MRI09_WALL_PANELS_ROLLED = 2850,
    // Breakable floor in Great Tree mri_09 broken; Punies use the lower floor height afterwards (the demo build tests it inverted)
    GSWF_MRI09_FLOOR_BROKEN = 2851,
    GSWF_MRI09_BLUE_KEY_CHEST_OPENED = 2852, // Great Tree mri_09 chest holding the Blue Key opened
    GSWF_MRI09_CHARGE_TAKEN = 2853,          // Charge badge pickup in Great Tree mri_09 collected
    // Super Boots chest in Great Tree mri_10 opened (GSW0 -> 105)
    GSWF_MRI10_SUPER_BOOTS_CHEST_OPENED = 2854,
    // Punio called the Punies to the second Jabbi fight in Great Tree mri_11
    GSWF_MRI11_JABBI_FIGHT2_STARTED = 2855,
    // The Punies lost the second Jabbi fight in mri_11; Punio comments in mri_06 and clears it
    GSWF_MRI11_JABBI_FIGHT2_LOST = 2856,
    GSWF_MRI11_JABBI_FIGHT2_WON = 2857, // The Punies won the second Jabbi fight in mri_11
    // Breakable floor in Great Tree mri_12 broken; Punies use the lower floor height afterwards
    GSWF_MRI12_FLOOR_BROKEN = 2858,
    GSWF_MRI12_ORB_ON_PEDESTAL = 2859, // Puni orb currently on the pedestal in Great Tree mri_12
    // Coin hidden in the planter in Great Tree mri_12 collected
    GSWF_MRI12_PLANTER_COIN_TAKEN = 2860,
    // Puni orb currently on the pedestal in Great Tree mri_13 (the floor it lowers depends on it)
    GSWF_MRI13_ORB_ON_PEDESTAL = 2861,
    // Mushroom hidden in the planter in Great Tree mri_13 collected
    GSWF_MRI13_PLANTER_MUSHROOM_TAKEN = 2862,
    GSWF_MRI14_ORB_ON_PEDESTAL = 2863, // Puni orb currently on the pedestal in Great Tree mri_14
    // Lord Crump set the time bomb in mri_14 (GSW0 -> 108); the next mri_14 load places Mario at the west door and clears it
    GSWF_MRI14_TIME_BOMB_SCENE_PENDING = 2864,
    // Lamp door between Great Tree mri_15 (west) and mri_06 switched open; toggles with its switch
    GSWF_MRI15_WEST_DOOR_UNLOCKED = 2865,
    // Lord Crump left mri_15 (the X-Naut battle there is over, or Mario left by the pipe first)
    GSWF_MRI15_CRUMP_GONE = 2866,
    // Blue switch in Great Tree mri_16 pressed and the water level changed (STG2_21_06 Water Switch); Puni map data changes
    GSWF_MRI16_WATER_SWITCH_PRESSED = 2867,
    // Light-blue ride switch for the bar mechanism in Great Tree mri_16 pressed
    GSWF_MRI16_BAR_SWITCH_PRESSED = 2868,
    GSWF_MRI16_DIZZY_DIAL_TAKEN = 2869, // Dizzy Dial pickup in Great Tree mri_16 collected
    // Puni orb currently on the pedestal in Great Tree mri_17 (the trap room)
    GSWF_MRI17_ORB_ON_PEDESTAL = 2870,
    // Breakable floor in Great Tree mri_17 broken; Punies use the lower floor height afterwards
    GSWF_MRI17_FLOOR_BROKEN = 2871,
    // First entry to mri_17 from mri_12 played the strange statue scene
    GSWF_MRI17_STRANGE_STATUE_SEEN = 2872,
    // Coin hidden in the planter in Great Tree mri_18 collected
    GSWF_MRI18_PLANTER_COIN_TAKEN = 2873,
    // Flurrie's gust in Great Tree mri_19 uncovered the airplane panel (success jingle)
    GSWF_MRI19_GUST_REVEALED_PANEL = 2874,
    // Power Punch hidden in the planter in Great Tree mri_20 collected
    GSWF_MRI20_PLANTER_POWER_PUNCH_TAKEN = 2875,
    // Punio joined the Puni group as follower #1 after meeting the rival (STG2_12_01); counted by mri_puni
    GSWF_MRI_PUNIO_IN_PUNI_GROUP = 2876,
    // Petuni joined the Puni group as follower #2 after leaving her cell; counted by mri_puni
    GSWF_MRI_PETUNI_IN_PUNI_GROUP = 2877,
    // The little Jabbi from mri_07 (chibitoge, Puni follower slot 3, PUNI_FLAG_NPC_JABBI) joined the Puni group (STG2_18); the Puni clerk only comments on it
    GSWF_MRI_JABBI_IN_PUNI_GROUP = 2878,
    // The rival Puni and his followers joined the Puni group as follower #4 (STG2_15 11 Punies); counted by mri_puni
    GSWF_MRI_RIVAL_IN_PUNI_GROUP = 2879,
    // Start the time bomb's 5-minute countdown on the next Great Tree map load (set at STG2_23_01, consumed by mri_countdown)
    GSWF_MRI_BOMB_COUNTDOWN_PENDING = 2880,
    // Punio showed Mario the sealed Great Tree entrance (GSW0 -> 75); never tested
    GSWF_MRI00_TREE_SEAL_SCENE_DONE = 2881,
    // During Bowser's Great Tree interlude (GSW0 170) the planter in mri_01 was checked and the Puni ran off (kpa_stg3_006_2)
    GSWF_MRI01_BOWSER_PLANTER_SCENE_DONE = 2883,
    // Mario left the Great Tree by the pipe after the chapter 2 boss (GSW0>=112); Punies, Petuni and the Jabbis take their post-chapter spots
    GSWF_MRI_LEFT_TREE_AFTER_STG2 = 2884,
    GSWF_MRI16_SHRINK_STOMP_CHEST_OPENED = 2885, // Great Tree mri_16 chest (Shrink Stomp) opened
    GSWF_DOU02_GATE_HANDLE_TAKEN = 2975,         // Gate Handle pickup in Pirate's Grotto dou_02 collected
    GSWF_DOU04_GROTTO_KEY_TAKEN = 2977,          // Grotto Key in Pirate's Grotto dou_04 collected (STG5_21)
    // Blue switch for the big door in Pirate's Grotto dou_05 pressed
    GSWF_DOU05_BIG_DOOR_SWITCH_PRESSED = 2978,
    // Locked door in Pirate's Grotto dou_05 opened with the Grotto Key
    GSWF_DOU05_DOOR_UNLOCKED = 2979,
    // Pirate's Grotto black chest (dou_07) opened and its paper curse received (Boat Mode, STG5_21 Paper Mage 4)
    GSWF_DOU07_BLACK_CHEST_OPENED = 2980,
    // Cracked wall at the west exit of Pirate's Grotto dou_09 blown open
    GSWF_DOU09_BOMB_WALL_BLOWN = 2981,
    // Saw the stranded Bob-omb sailors shouting across the water in Pirate's Grotto dou_11 (stg5_dou_13)
    GSWF_DOU11_STRANDED_SAILORS_SEEN = 2982,
    // First of the two blue switches that raise the floating platform in dou_11 pressed
    GSWF_DOU11_ISLAND_SWITCH_A_PRESSED = 2983,
    // Second of the two blue switches that raise the floating platform in dou_11 pressed
    GSWF_DOU11_ISLAND_SWITCH_B_PRESSED = 2984,
    // P-Down, D-Up badge pickup in Pirate's Grotto dou_07 collected
    GSWF_DOU07_PDOWN_DUP_TAKEN = 2985,
    // Pirate's Grotto dou_05 chest opened (Defend Plus P in the US release, Damage Dodge P in the others)
    GSWF_DOU05_CHEST_OPENED = 2986,
    // Black Key dropped by the Ember in Pirate's Grotto dou_07 collected
    GSWF_DOU07_BLACK_KEY_TAKEN = 2987,
    // The Ember guarding the black chest in dou_07 has appeared; it reappears on reload until beaten
    GSWF_DOU07_EMBER_APPEARED = 2988,
    // The Ember in dou_07 was defeated; the Black Key then sits where it fell
    GSWF_DOU07_EMBER_DEFEATED = 2989,
    GSWF_DOU00_RUIN_POWDER_TAKEN = 2990, // Ruin Powder pickup in Pirate's Grotto dou_00 collected
    // Couple's Cake reward from trouble #21 (the Goomba in Pirate's Grotto dou_04) collected
    GSWF_DOU04_TROUBLE21_COUPLES_CAKE_TAKEN = 2991,
    // Both platform switches pressed and the stranded sailors crossed over to Mario in dou_11 (they thank him; ship collision on)
    GSWF_DOU11_SAILORS_CROSSED = 2992,
    // Hidden ? block holding a coin in Pirate's Grotto dou_05 hit
    GSWF_DOU05_HIDDEN_COIN_BLOCK_HIT = 2993,
    // Hidden ten-coin block in Pirate's Grotto dou_09 emptied
    GSWF_DOU09_HIDDEN_COIN_BLOCK_EMPTIED = 2994,
    // Told Cortez to sail to Keelhaul Key; muj_00 plays the arrival and clears it
    GSWF_GOR00_SAIL_TO_KEELHAUL = 3125,
    // Makes the muj_01 crew-split scene (GSW0 232) jump straight to the show-of-hands vote; only set by the debug story jump stg5_12_init01
    GSWF_MUJ01_SKIP_TO_SHOW_OF_HANDS = 3126,
    // First talk with Flavio on Keelhaul Key at GSW0 234 (stg5_muj_31); later talks give stg5_muj_32
    GSWF_MUJ01_FLAVIO_FIRST_TALK_234 = 3127,
    // Talked the timid sailor into helping with the rescue in muj_01 (STG5_15 Flavio's Rescue Plan)
    GSWF_MUJ01_TIMID_SAILOR_PERSUADED = 3129,
    // The runaway sailor scene in Keelhaul Key muj_03 played (GSW0>=234)
    GSWF_MUJ03_RUNAWAY_SAILOR_SEEN = 3131,
    GSWF_MUJ03_COIN_BLOCK_HIT = 3133, // Coin ? block in Keelhaul Key muj_03 (mobj01) hit
    // Hidden ten-coin block in Keelhaul Key muj_03 (mobj02) emptied
    GSWF_MUJ03_HIDDEN_COIN_BLOCK_EMPTIED = 3134,
    // First-arrival scene at the Keelhaul Key cliff (muj_05) with Bobbery's shout played (stg5_muj_33)
    GSWF_MUJ05_FIRST_VISIT_SCENE = 3136,
    GSWF_MUJ05_EMBERS_DEFEATED = 3137, // Embers holding Bobbery in muj_05 defeated
    // First talk with Bobbery at GSW0 238 (stg5_muj_47); the next talk starts his scene
    GSWF_MUJ05_BOBBERY_FIRST_TALK_238 = 3138,
    GSWF_MUJ05_SKULL_GEM_PLACED = 3139, // Skull Gem set into the Skull Rock in muj_05 (eyes flash)
    // Examined the Skull Rock after GSW0 240 and heard the partner's comment
    GSWF_MUJ05_SKULL_ROCK_EXAMINED = 3140,
    // Talked to the humming Flavio at the Skull Rock (GSW0 241); stops his hum
    GSWF_MUJ05_FLAVIO_HUMMING_STOPPED = 3141,
    // Flavio gave his Skull Rock riddle hint (stg5_muj_93_03)
    GSWF_MUJ05_FLAVIO_SKULL_ROCK_HINT = 3142,
    GSWF_MUJ05_WEDDING_RING_TAKEN = 3143, // Wedding Ring pickup in Keelhaul Key muj_05 collected
    GSWF_MUJ03_BRICK_BROKEN = 3145,       // Brick block bblk00 in Keelhaul Key muj_03 broken
    // ? block holding the Head Rattle badge in Keelhaul Key muj_02 hit
    GSWF_MUJ02_HEAD_RATTLE_BLOCK_HIT = 3146,
    // ? block holding a Thunder Rage in Keelhaul Key muj_03 hit
    GSWF_MUJ03_THUNDER_RAGE_BLOCK_HIT = 3147,
    GSWF_MUJ04_ICE_POWER_TAKEN = 3148, // Ice Power badge pickup in Keelhaul Key muj_04 collected
    // The Skull Rock in muj_05 opened its mouth to the Grotto (STG5_19)
    GSWF_MUJ05_SKULL_ROCK_OPENED = 3149,
    // ? block holding a Courage Shell in Keelhaul Key muj_02 hit
    GSWF_MUJ02_COURAGE_SHELL_BLOCK_HIT = 3150,
    // First talk with (or defeat of) the beach creature hiding in the sand in Keelhaul Key muj_00 (NPC "koburon"); later talks cycle through GSW 721
    GSWF_MUJ00_KOBURON_FIRST_TALK = 3151,
    // Keel Mango shaken from the muj_02 tree this visit (cleared on every load); the US release forces it on while GSW0<261
    GSWF_MUJ02_KEEL_MANGO_TAKEN = 3152,
    // Hidden ? block holding a Jammin' Jelly in Keelhaul Key muj_03 hit
    GSWF_MUJ03_HIDDEN_JAMMIN_JELLY_BLOCK_HIT = 3153,
    // Coin hidden in a bush in Keelhaul Key muj_02 (kusa 2) collected
    GSWF_MUJ02_BUSH_COIN_TAKEN = 3154,
    // Mini Mr. Mini hidden in a bush in Keelhaul Key muj_03 (kusa 5) collected
    GSWF_MUJ03_BUSH_MINI_MR_MINI_TAKEN = 3155,
    // Coin hidden in a bush in Keelhaul Key muj_03 (kusa 7) collected
    GSWF_MUJ03_BUSH_COIN_TAKEN = 3156,
    // Spite Pouch hidden in a bush in Keelhaul Key muj_05 (kusa 1) collected
    GSWF_MUJ05_BUSH_SPITE_POUCH_TAKEN = 3157,
    GSWF_MUJ04_INN_COUPON_TAKEN = 3158, // Inn Coupon pickup in Keelhaul Key muj_04 collected
    // Gave the Gold Ring back to the madam in Poshley Heights (30-coin reward); her later lines change
    GSWF_PIK00_GOLD_RING_RETURNED = 3275,
    GSWF_PIK00_HP_DRAIN_P_CHEST_OPENED = 3276, // Poshley Heights pik_00 chest (HP Drain P) opened
    GSWF_PIK03_L_EMBLEM_TAKEN = 3277,          // L Emblem pickup in Poshley Heights pik_03 collected
    // Got the Choco Cake reward from the Poshley Heights souvenir-shop owner for Trouble #27 (handed over, or dropped on the floor when the bag is full)
    GSWF_PIK01_TROUBLE27_CAKE_REWARD = 3278,
    GSWF_PIK04_INN_COUPON = 3279, // Picked up the Inn Coupon in Poshley Heights (pik_04)
    // Excess Express autograph hunt (story 291-293): Bub first told Mario he still has no autograph (stg6_rsh_95)
    GSWF_RSH04_BUB_NO_AUTOGRAPH_FIRST = 3425,
    // Talked to Pennington during the autograph hunt (story 291-293, stg6_rsh_103); set only, never tested
    GSWF_RSH04_PENNINGTON_AUTOGRAPH_TALK = 3426,
    // First talk with the passenger "toron" (talk_toron) before story 287 (stg6_rsh_09; repeat line stg6_rsh_10)
    GSWF_RSH01_TORON_FIRST_TALK = 3427,
    // Pennington's dining-car scene after the missing-lunch incident (stg6_rsh_44/45); changes the chef, waitress and businessman lines
    GSWF_RSH03_PENNINGTON_LUNCH_CASE_TALK = 3428,
    // Toodles first asked Mario for help (on the Excess Express or later in Poshley Heights)
    GSWF_RSH_TOODLES_ASKED_HELP = 3429,
    // Mario agreed to help Toodles (answered yes to stg6_rsh_83_yn / stg6_pik_04_05)
    GSWF_RSH_TOODLES_HELP_ACCEPTED = 3430,
    // The Excess Express waitress first asked Mario for help (stg6_rsh_74)
    GSWF_RSH03_WAITRESS_ASKED_HELP = 3431,
    // Mario agreed to help the waitress (yes to stg6_rsh_77_yn)
    GSWF_RSH03_WAITRESS_HELP_ACCEPTED = 3432,
    // Tried the rattling west door of the rsh_04 car once; later tries skip the camera pan before stg6_rsh_236_02
    GSWF_RSH04_WEST_DOOR_MSG_SEEN = 3433,
    // Story 295: first talk with the gourmet passenger (stg6_rsh_117); entering cabin 4 afterwards sets GSWF 3435
    GSWF_RSH02_GOURMET_CABIN_TALK = 3434,
    // Opened cabin 4 (heya_4) after the gourmet's story-295 talk; his line changes to stg6_rsh_117_01
    GSWF_RSH02_CABIN4_ENTERED_AFTER_GOURMET = 3435,
    // Asked the conductor during the autograph hunt (stg6_rsh_105); with GSWF 3452 advances the story to 292
    GSWF_RSH04_CONDUCTOR_AUTOGRAPH_TALK = 3436,
    // Asked Toron during the autograph hunt (stg6_rsh_106); with GSWF 3436 the partner gives the stg6_rsh_107_* hint
    GSWF_RSH01_TORON_AUTOGRAPH_TALK = 3437,
    // First talk with the conductor at story 294 (stg6_rsh_111, then the stg6_rsh_114_yn bedtime question that moves the story to 295)
    GSWF_RSH04_CONDUCTOR_NIGHT_FIRST_TALK = 3438,
    // Story 297: the ghost's voice (stg6_rsh_123) heard once when leaving a cabin in rsh_02_c
    GSWF_RSH02_GHOST_VOICE_HEARD = 3439,
    // Talked to Pennington at story 297-300 (stg6_rsh_124); the businessman then says stg6_rsh_125
    GSWF_RSH04_PENNINGTON_TALK_297 = 3440,
    // First talk with Toodles at story 310-325 (stg6_rsh_204 before the repeat line stg6_rsh_205)
    GSWF_RSH01_TOODLES_POSTSTORY_TALK = 3441,
    // Story 329-331: the sleeping dining-car shop clerk was woken (stg6_rsh_236_01); evt_shop blocks the rsh_03 shop until set
    GSWF_RSH03_SHOP_CLERK_WOKEN = 3442,
    // The conductor's automatic line stg6_rsh_129 has played
    GSWF_RSH04_CONDUCTOR_AUTO_TALK_DONE = 3443,
    // Next Excess Express room load uses a scripted entrance instead of the door entry (set before day-change and cutscene map swaps, cleared by the receiving room's init)
    GSWF_RSH_SCRIPTED_ENTRY_PENDING = 3444,
    // The ghost has faded in inside cabin 4 (after Mario hides there with Vivian's ability for ~4 s); reset at the end of each day
    GSWF_RSH02_GHOST_APPEARED = 3445,
    // Mario is inside cabin 5 (heya_5) of rsh_04; set on door open, cleared on close
    GSWF_RSH04_INSIDE_CABIN5 = 3446,
    // Mario is inside cabin 3 (heya_3) of rsh_04; set on door open, cleared on close
    GSWF_RSH04_INSIDE_CABIN3 = 3447,
    // Conversation with the cabin-4 ghost in progress (pauses its fade loop)
    GSWF_RSH02_GHOST_TALK_ACTIVE = 3448,
    // The ghost's fade loop is waiting for the talk (GSWF 3448) to end
    GSWF_RSH02_GHOST_FADE_PAUSED = 3449,
    // The waitress was freed from Smorg's grip during the Smorg attack (evt_moamoa_escape0)
    GSWF_RSH05_SMORG_RELEASED_WAITRESS = 3450,
    // The conductor was freed from Smorg's grip during the Smorg attack (evt_moamoa_escape1)
    GSWF_RSH05_SMORG_RELEASED_CONDUCTOR = 3451,
    // Talked to Bub again without the autograph (stg6_rsh_95_01); with GSWF 3436 advances the story to 292
    GSWF_RSH04_BUB_NO_AUTOGRAPH_AGAIN = 3452,
    // Later rides: the a-variant of the passenger cars was loaded last; rsh_05 and rsh_08 pick the matching entrance (one of 3453-3455 set)
    GSWF_RSH_REVISIT_VARIANT_A = 3453,
    // Later rides: the b-variant of the passenger cars was loaded last (see GSWF 3453)
    GSWF_RSH_REVISIT_VARIANT_B = 3454,
    // Later rides: the c-variant of the passenger cars was loaded last (see GSWF 3453)
    GSWF_RSH_REVISIT_VARIANT_C = 3455,
    // A later ride (story >= 345) has just left Rogueport or Poshley Heights; rsh_02 re-rolls the random passengers and clears it
    GSWF_RSH_NEW_RIDE_PENDING = 3456,
    // Gave the first answer to the question of later-ride passenger 4_8 (stg6_rsh_c_42_sel)
    GSWF_RSH_PASSENGER_4_8_ANSWERED = 3457,
    // Answered the question of later-ride passenger 5_3 (stg6_rsh_c_47_sel)
    GSWF_RSH_PASSENGER_5_3_ANSWERED = 3458,
    // Mario is inside cabin 4 (heya_4) of rsh_02; the ghost waits for this
    GSWF_RSH02_INSIDE_CABIN4 = 3459,
    // The train has pulled in at Poshley Station (arrival chime stg6_rsh_c_04 in rsh_02); the cars play the Poshley music; cleared on departure
    GSWF_TRAIN_ARRIVED_POSHLEY = 3460,
    // The train has pulled in at Rogueport Station (gor_04 arrival); the cars play the Rogueport music; cleared on departure
    GSWF_TRAIN_ARRIVED_ROGUEPORT = 3461,
    // Took the Dried Shroom from shelf tana_5 in the middle passenger car (forced on from story 345)
    GSWF_RSH02_SHELF_DRIED_SHROOM = 3462,
    // The Riverside Station worker first explained the raised drawbridge (stg6_hom_04/05)
    GSWF_HOM00_BRIDGE_EXPLAINED = 3574,
    // Unlocked the Riverside Station entrance door with the first station key (lock mobj)
    GSWF_HOM00_STATION_DOOR_UNLOCKED = 3575,
    // Bridge switch pressed: map swaps to hom_00 to show the bridge lowering, then eki_00 restores the room (story 325) and clears it
    GSWF_EKI00_BRIDGE_LOWER_SCENE = 3576,
    // Set with GSWF 3582 when the train leaves Riverside Station (hom_00); never tested
    GSWF_HOM00_TRAIN_DEPARTED = 3577,
    // The train is on its way back to Rogueport (set on leaving Poshley Heights, cleared on leaving Rogueport); picks the return-leg scenes and GSW 870 = 3 at Riverside
    GSWF_TRAIN_RETURN_TRIP = 3578,
    // The train is stopped at Riverside Station (set on arrival in hom_00, cleared on departure)
    GSWF_TRAIN_AT_RIVERSIDE = 3579,
    // The train is stopped at Poshley Station (set on arrival in pik_00, cleared on departure)
    GSWF_TRAIN_AT_POSHLEY = 3580,
    // The train is stopped at Rogueport Station (set on arrival in gor_04, cleared on departure)
    GSWF_TRAIN_AT_ROGUEPORT = 3581,
    // Set whenever the train leaves a station (gor_04, hom_00, pik_00); never tested
    GSWF_TRAIN_DEPARTED = 3582,
    GSWF_TRAIN_MOVING = 3583, // Train is moving (scenery, wheel and clank loops run)
    // Pressed the blue switch that lowers the Riverside drawbridge (switch mobj)
    GSWF_EKI00_BRIDGE_SWITCH_PRESSED = 3725,
    // Unlocked the eki_01 door with the second station key (lock mobj; story 315)
    GSWF_EKI01_DOOR_UNLOCKED = 3726,
    // Pressed the blue switch that unfolds the eki_01 staircase (switch mobj)
    GSWF_EKI01_STAIRS_SWITCH_PRESSED = 3727,
    // Opened the treasure chest with the Ultra Boots in eki_05
    GSWF_EKI05_ULTRA_BOOTS_CHEST_OPENED = 3728,
    // Flurrie blew poster 1 off the eki_03 wall; range 3729-3743 = posters 1-15, posters 5-15 all gone opens the hidden passage (story 316)
    GSWF_EKI03_POSTER_1_BLOWN = 3729,
    GSWF_EKI03_POSTER_2_BLOWN = 3730, // Flurrie blew poster 2 off the eki_03 wall (range 3729-3743)
    GSWF_EKI03_POSTER_3_BLOWN = 3731, // Flurrie blew poster 3 off the eki_03 wall (range 3729-3743)
    GSWF_EKI03_POSTER_4_BLOWN = 3732, // Flurrie blew poster 4 off the eki_03 wall (range 3729-3743)
    // Flurrie blew poster 5 off the eki_03 wall; one of the eleven checked by evt_chk
    GSWF_EKI03_POSTER_5_BLOWN = 3733,
    // Flurrie blew poster 6 off the eki_03 wall (checked by evt_chk)
    GSWF_EKI03_POSTER_6_BLOWN = 3734,
    // Flurrie blew poster 7 off the eki_03 wall (checked by evt_chk)
    GSWF_EKI03_POSTER_7_BLOWN = 3735,
    // Flurrie blew poster 8 off the eki_03 wall (checked by evt_chk)
    GSWF_EKI03_POSTER_8_BLOWN = 3736,
    // Flurrie blew poster 9 off the eki_03 wall (checked by evt_chk)
    GSWF_EKI03_POSTER_9_BLOWN = 3737,
    // Flurrie blew poster 10 off the eki_03 wall (checked by evt_chk)
    GSWF_EKI03_POSTER_10_BLOWN = 3738,
    // Flurrie blew poster 11 off the eki_03 wall (checked by evt_chk)
    GSWF_EKI03_POSTER_11_BLOWN = 3739,
    // Flurrie blew poster 12 off the eki_03 wall (checked by evt_chk)
    GSWF_EKI03_POSTER_12_BLOWN = 3740,
    // Flurrie blew poster 13 off the eki_03 wall (checked by evt_chk)
    GSWF_EKI03_POSTER_13_BLOWN = 3741,
    // Flurrie blew poster 14 off the eki_03 wall (checked by evt_chk)
    GSWF_EKI03_POSTER_14_BLOWN = 3742,
    // Flurrie blew poster 15 off the eki_03 wall (checked by evt_chk)
    GSWF_EKI03_POSTER_15_BLOWN = 3743,
    GSWF_EKI04_DRIED_SHROOM = 3744, // Picked up the Dried Shroom in eki_04
    GSWF_EKI00_CLOSE_CALL_P = 3745, // Picked up the Close Call P badge in eki_00
    GSWF_EKI03_HP_PLUS = 3746,      // Picked up the HP Plus badge in eki_03
    GSWF_EKI04_P_UP_D_DOWN = 3747,  // Picked up the P-Up, D-Down badge in eki_04
    // Flurrie blew paper 1 away in eki_01; range 3748-3753 = papers 1-6
    GSWF_EKI01_PAPER_1_BLOWN = 3748,
    GSWF_EKI01_PAPER_2_BLOWN = 3749,          // Flurrie blew paper 2 away in eki_01 (range 3748-3753)
    GSWF_EKI01_PAPER_3_BLOWN = 3750,          // Flurrie blew paper 3 away in eki_01 (range 3748-3753)
    GSWF_EKI01_PAPER_4_BLOWN = 3751,          // Flurrie blew paper 4 away in eki_01 (range 3748-3753)
    GSWF_EKI01_PAPER_5_BLOWN = 3752,          // Flurrie blew paper 5 away in eki_01 (range 3748-3753)
    GSWF_EKI01_PAPER_6_BLOWN = 3753,          // Flurrie blew paper 6 away in eki_01 (range 3748-3753)
    GSWF_EKI03_THUNDER_RAGE_BLOCK_HIT = 3754, // Hit the brick block with the Thunder Rage in eki_03
    // Goldbob signed the approval to fire the Fahr Outpost cannon (stg7_pik_19); with GSWF 3876 moves the story to 355
    GSWF_PIK00_GOLDBOB_CANNON_APPROVAL = 3874,
    // Woke General White in the Fahr Outpost bed and he agreed to help; with GSWF 3874 moves the story to 355
    GSWF_BOM02_GENERAL_WHITE_WOKEN = 3876,
    // General White hint heard in Petalburg (nok) during the chapter 7 search
    GSWF_STG7_WHITE_PETALBURG_HINT = 3877,
    // General White hint heard on Keelhaul Key (needs the Petalburg hint GSWF 3877); set only, never tested
    GSWF_STG7_WHITE_KEELHAUL_HINT = 3878,
    GSWF_STG7_WHITE_GLITZVILLE_HINT = 3879, // Glitzville bar owner told Mario about General White
    // Twilight Town villager said General White went back to Fahr Outpost (needs GSWF 3889); White then appears in Fahr
    GSWF_STG7_WHITE_TWILIGHT_HINT = 3880,
    // First chapter-7 talk with Goldbob about the cannon (stg7_pik_01-03)
    GSWF_PIK00_GOLDBOB_CANNON_FIRST_TALK = 3881,
    GSWF_BOM_FAHR_REACHED = 3884, // Reached Fahr Outpost; Frankly stops the Ultra Hammer hint
    // Entered Fahr Outpost town before the chapter-7 arrival (story < 349); the partner's arrival line changes
    GSWF_BOM01_VISITED_BEFORE_STG7 = 3885,
    // First talk with Mayor Dour about General White (stg7_bom_20/21)
    GSWF_BOM02_MAYOR_FIRST_TALK = 3886,
    GSWF_BOM04_HP_PLUS_P = 3887, // Got the HP Plus P badge from the block in bom_04
    // Saw General White wander into the house in Fahr Outpost after the Twilight Town hint (stg7_bom_39-41)
    GSWF_BOM02_WHITE_SEEN_IN_TOWN = 3888,
    // Boggly Woods Puni gave the General White hint (stg2_mri_re_000_1; needs GSWF 3879)
    GSWF_STG7_WHITE_BOGGLY_HINT = 3889,
    // Got the Snow Bunny reward for Trouble #30 in Fahr Outpost
    GSWF_BOM02_TROUBLE30_SNOW_BUNNY_REWARD = 3890,
    // Hit the hidden block with the Double Dip P badge in bom_00
    GSWF_BOM00_DOUBLE_DIP_P_BLOCK_HIT = 3891,
    GSWF_BOM02_INN_COUPON = 3892,    // Picked up the Inn Coupon in Fahr Outpost (bom_02)
    GSWF_MOO00_ROCK_A_BOMBED = 4025, // Bobbery blew up moon rock S_iwa_01 in moo_00
    GSWF_MOO00_ROCK_B_BOMBED = 4026, // Bobbery blew up moon rock S_iwa_08 in moo_00
    GSWF_MOO01_ROCK_A_BOMBED = 4027, // Bobbery blew up moon rock S_iwa_01 in moo_01
    GSWF_MOO01_ROCK_B_BOMBED = 4028, // Bobbery blew up moon rock S_iwa_08 in moo_01
    GSWF_MOO02_ROCK_A_BOMBED = 4029, // Bobbery blew up moon rock S_iwa_01 in moo_02
    GSWF_MOO02_ROCK_B_BOMBED = 4030, // Bobbery blew up moon rock S_iwa_07 in moo_02
    GSWF_MOO05_ROCK_BOMBED = 4031,   // Bobbery blew up moon rock S_iwa_07 in moo_05
    GSWF_MOO06_ROCK_A_BOMBED = 4032, // Bobbery blew up moon rock S_iwa_01 in moo_06
    GSWF_MOO06_ROCK_B_BOMBED = 4033, // Bobbery blew up moon rock S_iwa_09 in moo_06
    GSWF_MOO07_ROCK_BOMBED = 4034,   // Bobbery blew up moon rock S_iwa_07 in moo_07
    GSWF_MOO00_STOPWATCH = 4035,     // Picked up the Stopwatch on the moon (moo_00)
    GSWF_MOO01_VOLT_SHROOM = 4036,   // Picked up the Volt Shroom on the moon (moo_01)
    GSWF_MOO02_POWER_PUNCH = 4037,   // Picked up the Power Punch on the moon (moo_02)
    GSWF_MOO06_RUIN_POWDER = 4038,   // Picked up the Ruin Powder on the moon (moo_06)
    GSWF_MOO07_COURAGE_SHELL = 4039, // Picked up the Courage Shell on the moon (moo_07)
    // Teleported from the X-Naut Fortress or the moon to the Rogueport Underground; tik_00 plays the arrival and clears it
    GSWF_TIK00_TELEPORTER_ARRIVAL = 4175,
    // Opened the chest with the Elevator Key on the electric floor in aji_02 (item box mobj)
    GSWF_AJI02_ELEVATOR_KEY_CHEST_OPENED = 4176,
    // Opened the chest with the card key on the electric floor in aji_05 (item box mobj)
    GSWF_AJI05_CARD_KEY_CHEST_OPENED = 4178,
    // Opened the chest with the card key on the electric floor in aji_12 (item box mobj)
    GSWF_AJI12_CARD_KEY_CHEST_OPENED = 4179,
    GSWF_AJI11_CARD_KEY_TAKEN = 4180, // Picked up the card key in aji_11
    GSWF_AJI13_CARD_KEY_TAKEN = 4181, // Picked up the card key in aji_13 (the factory)
    // Got the card key from the aji_05 chest; the electric floor switches off
    GSWF_AJI05_CARD_KEY_TAKEN = 4182,
    // Got the card key from the aji_12 chest; the electric floor switches off
    GSWF_AJI12_CARD_KEY_TAKEN = 4183,
    // Pressed the aji_13 blue switch that raises the staircase (switch mobj)
    GSWF_AJI13_STAIRS_SWITCH_PRESSED = 4184,
    // Pressed the aji_13 blue switch that starts the conveyor belts (switch mobj; story 370)
    GSWF_AJI13_CONVEYOR_SWITCH_PRESSED = 4185,
    // Story 375 in aji_17: Mario and partners were healed and the closing scene started once
    GSWF_AJI17_POST_BOSS_SCENE_STARTED = 4186,
    // Crane room: button 1 pressed in the right order (cleared on a wrong order); range 4188-4190
    GSWF_AJI03_CRANE_BUTTON_1 = 4188,
    // Crane room: button 2 pressed in the right order (range 4188-4190)
    GSWF_AJI03_CRANE_BUTTON_2 = 4189,
    // Crane room: button 3 pressed in the right order (range 4188-4190)
    GSWF_AJI03_CRANE_BUTTON_3 = 4190,
    // Inserted card key 1 into its slot on the aji_18 door; all three slots open the door (story 369)
    GSWF_AJI18_CARD_KEY_SLOT_1 = 4191,
    GSWF_AJI18_CARD_KEY_SLOT_2 = 4192, // Inserted card key 2 into its slot on the aji_18 door
    GSWF_AJI18_CARD_KEY_SLOT_3 = 4193, // Inserted card key 3 into its slot on the aji_18 door
    GSWF_AJI07_COG_TAKEN = 4194,       // Picked up the Cog in the teleporter room aji_07
    GSWF_AJI10_VISITED = 4195,         // Set on every aji_10 load, so its east-door lock check never fires
    GSWF_AJI03_COG_INSERTED = 4196,    // Put the Cog into the crane machine in aji_03
    // All three crane buttons pressed in order: the crane game is running
    GSWF_AJI03_CRANE_ACTIVATED = 4197,
    // Won the first crane-game badge prize (Feeling Fine) in aji_03
    GSWF_AJI03_CRANE_PRIZE_A = 4198,
    // Peach entered the shower room during intermission 1; aji_16 then plays her remark (story 57)
    GSWF_AJI15_PEACH1_SHOWER_ROOM_ENTERED = 4199,
    // Peach's remark after the shower in intermission 1 (peach_aji_39) has played
    GSWF_AJI16_PEACH1_AFTER_SHOWER_REMARK = 4200,
    // Intermission 1: a door opened by itself as Peach walked past (peach_aji_41)
    GSWF_AJI01_PEACH1_DOOR_OPENED = 4201,
    // Peach's intermission-2 scene in aji_16 (story 112) has played; later visits use peach_evt_stg2_1
    GSWF_AJI16_PEACH2_SCENE_DONE = 4202,
    // Intermission 3: Peach took the X-Naut uniform (peach_aji_134/135)
    GSWF_AJI09_PEACH3_UNIFORM_TAKEN = 4203,
    // Intermission 3: Peach is currently wearing the X-Naut disguise
    GSWF_AJI09_PEACH3_DISGUISED = 4204,
    // Intermission 3: Peach changed in changing booth 1 (0 = booth 2); she must change back in the same booth
    GSWF_AJI09_PEACH3_CHANGED_IN_BOOTH1 = 4205,
    // Intermission 3 (story 168): Peach's remark after changing back (peach_aji_155)
    GSWF_AJI09_PEACH3_CHANGE_BACK_REMARK = 4206,
    // Intermission 5: Peach's remark on entering aji_11 (peach_aji_244)
    GSWF_AJI11_PEACH5_ROOM_REMARK = 4207,
    // Intermission 5: Peach took the Data Disk from the shelf
    GSWF_AJI11_PEACH5_DATA_DISK_TAKEN = 4208,
    // Intermission 5: Peach put the disk in the computer and read the data (peach_aji_248)
    GSWF_AJI11_PEACH5_DISK_READ = 4209,
    // Intermission 5 (story 262): Peach found the correct potion in the lab; the aji_06 door opens
    GSWF_AJI06_PEACH5_RIGHT_POTION = 4210,
    GSWF_AJI02_SUPER_SHROOM_BLOCK_HIT = 4211, // Got the Super Shroom from the block in aji_02
    GSWF_AJI05_SLEEPY_SHEEP_BLOCK_HIT = 4212, // Got the Sleepy Sheep from the block in aji_05
    GSWF_AJI09_REPEL_CAPE_TAKEN = 4213,       // Picked up the Repel Cape in aji_09 (Japanese demo only)
    GSWF_AJI12_HP_DRAIN_BLOCK_HIT = 4214,     // Got the HP Drain from the block in aji_12
    GSWF_AJI13_ULTRA_SHROOM = 4215,           // Picked up the Ultra Shroom in aji_13
    // Won the second crane-game badge prize (Feeling Fine P) in aji_03
    GSWF_AJI03_CRANE_PRIZE_B = 4216,
    // Dropping into changing booth 2 from the ceiling turned Mario into 8-bit Mario (BGM_EVT_DOT_MARIO1); aji's _epilog clears it and the mode on leaving
    GSWF_AJI09_PIXEL_MARIO_ACTIVE = 4217,
    // First use of the crane control panel (stg7_aji_00_01)
    GSWF_AJI03_CRANE_PANEL_FIRST_USE = 4218,
    // First talk at the TEC terminal in aji_17 (stg7_aji_tec_00)
    GSWF_AJI17_TEC_TERMINAL_FIRST_TALK = 4219,
    // Peach has taken the shower once (peach_aji_37); later showers use peach_aji_35_1
    GSWF_AJI15_PEACH_SHOWER_TAKEN = 4220,
    // Palace of Shadow (story 385): took the wrong door in las_08; las_07 plays the wrong-door sound and clears it
    GSWF_LAS_WRONG_DOOR_TAKEN = 4325,
    // Bobbery blew up the first chain-chomp statue in las_09
    GSWF_LAS09_CHOMP_STATUE_1_BOMBED = 4326,
    // Bobbery blew up the second chain-chomp statue in las_09
    GSWF_LAS09_CHOMP_STATUE_2_BOMBED = 4327,
    // Pressed blue switch 1 in las_09, flipping pedestal 1 into a plane panel
    GSWF_LAS09_SWITCH_1_PRESSED = 4328,
    // Pressed blue switch 2 in las_09, flipping pedestal 2 into a plane panel
    GSWF_LAS09_SWITCH_2_PRESSED = 4329,
    // First entry into the Riddle Tower hub (las_10): the partner's line stg8_las_32 played
    GSWF_LAS10_RIDDLE_TOWER_ENTERED = 4330,
    // Placed a Palace Key in lock 1 of the Riddle Tower; range 4331-4338 = locks 1-8 (count in GSW 1122)
    GSWF_LAS10_TOWER_LOCK_1 = 4331,
    // Placed a Palace Key in lock 2 of the Riddle Tower (range 4331-4338)
    GSWF_LAS10_TOWER_LOCK_2 = 4332,
    // Placed a Palace Key in lock 3 of the Riddle Tower (range 4331-4338)
    GSWF_LAS10_TOWER_LOCK_3 = 4333,
    // Placed a Palace Key in lock 4 of the Riddle Tower (range 4331-4338)
    GSWF_LAS10_TOWER_LOCK_4 = 4334,
    // Placed a Palace Key in lock 5 of the Riddle Tower (range 4331-4338)
    GSWF_LAS10_TOWER_LOCK_5 = 4335,
    // Placed a Palace Key in lock 6 of the Riddle Tower (range 4331-4338)
    GSWF_LAS10_TOWER_LOCK_6 = 4336,
    // Placed a Palace Key in lock 7 of the Riddle Tower (range 4331-4338)
    GSWF_LAS10_TOWER_LOCK_7 = 4337,
    // Placed a Palace Key in lock 8 of the Riddle Tower (range 4331-4338)
    GSWF_LAS10_TOWER_LOCK_8 = 4338,
    // Riddle Tower big block at (150,50,0): stone block in las_11 and metal block in las_15 share this flag
    GSWF_LAS_TOWER_BIG_BLOCK_A = 4339,
    // Riddle Tower big block at (-150,0,75): stone in las_11, metal in las_15 (shared flag)
    GSWF_LAS_TOWER_BIG_BLOCK_B = 4340,
    // Hit the floating blue switch in las_11, revealing the Palace Key chest
    GSWF_LAS11_FLOAT_SWITCH_PRESSED = 4341,
    // Hit the floating blue switch in las_12, revealing the Palace Key chest
    GSWF_LAS12_FLOAT_SWITCH_PRESSED = 4342,
    // Hit both floating red switches in las_13 together, revealing the Palace Key chest
    GSWF_LAS13_RED_SWITCHES_SOLVED = 4343,
    // Flurrie blew away the A_kura cover in las_14 (las cloud gust), revealing the Palace Key chest
    GSWF_LAS14_FLURRIE_GUST_SOLVED = 4344,
    // Riddle Tower big block at (150,0,75): metal in las_11, stone in las_15 (shared flag)
    GSWF_LAS_TOWER_BIG_BLOCK_C = 4345,
    // Riddle Tower big block at (-150,50,0): metal in las_11, stone in las_15 (shared flag)
    GSWF_LAS_TOWER_BIG_BLOCK_D = 4346,
    // Hit the floating blue switch in las_15, revealing the Palace Key chest
    GSWF_LAS15_FLOAT_SWITCH_PRESSED = 4347,
    // Riddle-tower room las_16: Bobbery blew open the cracked wall (also set by the stg8_06 skip)
    GSWF_LAS16_WALL_BOMBED = 4348,
    // Riddle Tower: set only by the stg8_06 skip with the other tower puzzle flags; no map reads or sets it
    GSWF_LAS16_PUZZLE_2_SOLVED = 4349,
    // Riddle-tower room las_17: the four enemies were beaten in the hinted order (GSW 1123 counter reached 4), making the blue switch appear (also set by the stg8_06 skip)
    GSWF_LAS17_ENEMIES_BEATEN_IN_ORDER = 4350,
    // Riddle-tower room las_17: blue floating switch pressed; reveals the Palace Key chest (also set by the stg8_06 skip)
    GSWF_LAS17_SWITCH_PRESSED = 4351,
    // Riddle-tower room las_18: the hidden blue switch (revealed by Vivian) pressed; reveals the Palace Key chest (also set by the stg8_06 skip)
    GSWF_LAS18_SWITCH_PRESSED = 4352,
    // las_19 toggle switch 1 state after the light returns (GSW0>=390); raises/lowers floating block 19blk1 in las_21
    GSWF_LAS19_SWITCH1_ON = 4353,
    // las_19 toggle switch 2 state after the light returns (GSW0>=390); raises/lowers the second floating block in las_21
    GSWF_LAS19_SWITCH2_ON = 4354,
    // las_22 west door unlocked with Palace Key 0x2F (also set by the stg8_11 skip)
    GSWF_LAS22_DOOR_UNLOCKED = 4355,
    // las_24: Flurrie blew away the cover hiding the big block (also set by the stg8_13 skip)
    GSWF_LAS24_BLOCK_UNCOVERED = 4356,
    // las_24: big hammer block MOBJ_Lv2BigBigBlock smashed (also set by the stg8_13 skip)
    GSWF_LAS24_BIG_BLOCK_BROKEN = 4357,
    // las_24: breakable floor brkflr smashed (also set by the stg8_13 skip)
    GSWF_LAS24_FLOOR_BROKEN = 4358,
    // las_25 east door unlocked with Palace Key 0x30 (also set by the stg8_15 skip)
    GSWF_LAS25_DOOR_UNLOCKED = 4359,
    // las_26: Bobbery blew open the cracked wall (A_ana_before1); never set by a story skip
    GSWF_LAS26_WALL_BOMBED = 4360,
    // las_26: Star Key chest that appears after Gloomtail is beaten opened (also set by the stg8_05 skip)
    GSWF_LAS26_STAR_KEY_CHEST_OPENED = 4361,
    // Riddle-tower room las_11: chest with Palace Key 0x26 opened (also set by the stg8_06 skip, which sets all eight)
    GSWF_LAS11_KEY_CHEST_OPENED = 4362,
    // Riddle-tower room las_12: chest with Palace Key 0x27 opened (also set by the stg8_06 skip, which sets all eight)
    GSWF_LAS12_KEY_CHEST_OPENED = 4363,
    // Riddle-tower room las_13: chest with Palace Key 0x28 opened (also set by the stg8_06 skip, which sets all eight)
    GSWF_LAS13_KEY_CHEST_OPENED = 4364,
    // Riddle-tower room las_14: chest with Palace Key 0x29 opened (also set by the stg8_06 skip, which sets all eight)
    GSWF_LAS14_KEY_CHEST_OPENED = 4365,
    // Riddle-tower room las_15: chest with Palace Key 0x2A opened (also set by the stg8_06 skip, which sets all eight)
    GSWF_LAS15_KEY_CHEST_OPENED = 4366,
    // Riddle-tower room las_16: chest with Palace Key 0x2B opened (also set by the stg8_06 skip, which sets all eight)
    GSWF_LAS16_KEY_CHEST_OPENED = 4367,
    // Riddle-tower room las_17: chest with Palace Key 0x2C opened (also set by the stg8_06 skip, which sets all eight)
    GSWF_LAS17_KEY_CHEST_OPENED = 4368,
    // Riddle-tower room las_18: chest with Palace Key 0x2D opened (also set by the stg8_06 skip, which sets all eight)
    GSWF_LAS18_KEY_CHEST_OPENED = 4369,
    // las_24: chest with Palace Key 0x30 opened (also set by the stg8_14 skip)
    GSWF_LAS24_KEY_CHEST_OPENED = 4370,
    GSWF_LAS02_SHOOTING_STAR_BLOCK_HIT = 4371, // las_02 ? block mobj00 (Shooting Star) hit
    GSWF_LAS06_ULTRA_SHROOM_BLOCK_HIT = 4372,  // las_06 ? block mobj00 (Ultra Shroom) hit
    GSWF_LAS07_COIN_BLOCK_HIT = 4373,          // las_07 ? block mobj00 (coin) hit
    GSWF_LAS07_JAMMIN_JELLY_BLOCK_HIT = 4374,  // las_07 ? block mobj01 (Jammin' Jelly) hit
    // las_03 badge block mobj_badge_gat (All or Nothing badge) hit
    GSWF_LAS03_ALL_OR_NOTHING_BLOCK_HIT = 4375,
    // las_07 badge block mobj_badge_gat (P-Up, D-Down P badge) hit
    GSWF_LAS07_P_UP_D_DOWN_P_BLOCK_HIT = 4376,
    GSWF_LAS22_ITEMBOX_00 = 4377,            // las_22 treasure chest mobj_box00 (Shooting Star) opened
    GSWF_LAS22_LIFE_SHROOM_BLOCK_HIT = 4378, // las_22 ? block mobj_hatena_gat (Life Shroom) hit
    GSWF_LAS25_LIFE_SHROOM_ITEM02 = 4379,    // las_25 Life Shroom field item item02 picked up
    // Set on entering las_09 after Gloomtail is beaten (GSW0>=388); las_26 then drops Gloomtail's collapsed body and its collision (also set by the stg8_05 skip)
    GSWF_LAS26_GLOOMTAIL_BODY_CLEARED = 4380,
    // Riddle-tower room las_12: Mario slipped past the wall to the left side (kabenuke check); success jingle plays once
    GSWF_LAS12_WALL_PASSED = 4381,
    // Riddle-tower room las_18: Vivian's shadow fully revealed the hidden switch; success jingle plays once
    GSWF_LAS18_HIDDEN_SWITCH_REVEALED = 4382,
    GSWF_LAS01_STOPWATCH_ITEM_01 = 4383,      // las_01 Stopwatch field item item_01 picked up
    GSWF_LAS04_BOOS_SHEET_BRICK = 4384,       // las_04 brick mobj_01 (Boo's Sheet) hit
    GSWF_LAS26_ULTRA_SHROOM_BLOCK_HIT = 4385, // las_26 ? block mobj_01 (Ultra Shroom) hit
    GSWF_LAS26_JAMMIN_JELLY_BLOCK_HIT = 4386, // las_26 ? block mobj_02 (Jammin' Jelly) hit
    GSWF_LAS19_THUNDER_RAGE_BLOCK_HIT = 4387, // las_19 ? block mobj_item00 (Thunder Rage) hit
    GSWF_LAS20_REPEL_CAPE_BLOCK_HIT = 4388,   // las_20 ? block mobj_item00 (Repel Cape) hit
    GSWF_LAS20_LIFE_SHROOM_BLOCK_HIT = 4389,  // las_20 ? block mobj_item01 (Life Shroom) hit
    GSWF_LAS24_COIN_BLOCK_HIT = 4390,         // las_24 ? block mobj_hatena_gat (coin) hit
    // las_24 hidden brick mobj_kakusi (Point Swap) hit
    GSWF_LAS24_POINT_SWAP_HIDDEN_BLOCK_HIT = 4391,
    GSWF_LAS25_SHOOTING_STAR_ITEM03 = 4392, // las_25 Shooting Star field item item03 picked up
    GSWF_LAS30_ITEMBOX_01 = 4393,           // las_30 treasure chest mobj_box01 (Ultra Shroom) opened
    GSWF_LAS30_ITEMBOX_02 = 4394,           // las_30 treasure chest mobj_box02 (Jammin' Jelly) opened
    GSWF_TATTLE_BASE = 4474,                // Base of the Tattle Log flags: GSWF 4474+UNIT_* (set by monosiri_on)
    GSWF_TATTLE_GUS = 4481,                 // Gus tattled (4474+UNIT_GUS)
    GSWF_TATTLE_ATOMIC_BOO = 4550,          // Atomic Boo tattled (4474+UNIT_ATOMIC_BOO)
    GSWF_TATTLE_BONETAIL = 4645,            // Bonetail tattled (4474+UNIT_BONETAIL)
    // Bowser interlude (kpa_01): first talk with the two Hammer Bros. done; afterwards they just turn to face him
    GSWF_KPA01_HAMMER_BROS_TALKED = 4775,
    // Pit of 100 Trials: reward chest on floor 10 opened (picked by GSW 1321 + 1)
    GSWF_JON_FLOOR10_CHEST_OPENED = 5075,
    // Pit of 100 Trials: reward chest on floor 20 opened (picked by GSW 1321 + 1)
    GSWF_JON_FLOOR20_CHEST_OPENED = 5076,
    // Pit of 100 Trials: reward chest on floor 30 opened (picked by GSW 1321 + 1)
    GSWF_JON_FLOOR30_CHEST_OPENED = 5077,
    // Pit of 100 Trials: reward chest on floor 40 opened (picked by GSW 1321 + 1)
    GSWF_JON_FLOOR40_CHEST_OPENED = 5078,
    // Pit of 100 Trials: reward chest on floor 50 opened (picked by GSW 1321 + 1)
    GSWF_JON_FLOOR50_CHEST_OPENED = 5079,
    // Pit of 100 Trials: reward chest on floor 60 opened (picked by GSW 1321 + 1)
    GSWF_JON_FLOOR60_CHEST_OPENED = 5080,
    // Pit of 100 Trials: reward chest on floor 70 opened (picked by GSW 1321 + 1)
    GSWF_JON_FLOOR70_CHEST_OPENED = 5081,
    // Pit of 100 Trials: reward chest on floor 80 opened (picked by GSW 1321 + 1)
    GSWF_JON_FLOOR80_CHEST_OPENED = 5082,
    // Pit of 100 Trials: reward chest on floor 90 opened (picked by GSW 1321 + 1)
    GSWF_JON_FLOOR90_CHEST_OPENED = 5083,
    // Pit of 100 Trials: reward chest on floor 100 (appears after Bonetail) opened
    GSWF_JON_FLOOR100_CHEST_OPENED = 5084,
    GSWF_JON_BONETAIL_DEFEATED = 5085, // Bonetail beaten in the Pit of 100 Trials
    // Trouble Center rules explained; also the base of the "trouble N solved" flags (5374+N)
    GSWF_TROUBLE_LECTURE_HEARD = 5374,
    GSWF_TROUBLE_SOLVED_BASE = 5374, // trouble N (1-30) solved is GSWF_TROUBLE_SOLVED_BASE + N
    GSWF_TROUBLE_01_SOLVED = 5375,   // Trouble #1 solved: Robbo house key
    GSWF_TROUBLE_02_SOLVED = 5376,   // Trouble #2 solved: Goomfrey package delivery
    GSWF_TROUBLE_03_SOLVED = 5377,   // Trouble #3 solved: Fire Flower price check
    GSWF_TROUBLE_04_SOLVED = 5378,   // Trouble #4 solved: Larson the Bandit
    GSWF_TROUBLE_05_SOLVED = 5379,   // Trouble #5 solved: forgetful mouse (Sleepy Sheep)
    GSWF_TROUBLE_06_SOLVED = 5380,   // Trouble #6 solved: hungry pirate Bob-omb
    GSWF_TROUBLE_07_SOLVED = 5381,   // Trouble #7 solved (solved in another area; listed by gor_irai)
    GSWF_TROUBLE_08_SOLVED = 5382,   // Trouble #8 solved (solved in another area; listed by gor_irai)
    GSWF_TROUBLE_09_SOLVED = 5383,   // Trouble #9 solved: Courage Shells for the Bazaar
    // Trouble #10 solved (solved in another area; listed by gor_irai)
    GSWF_TROUBLE_10_SOLVED = 5384,
    GSWF_TROUBLE_11_SOLVED = 5385, // Trouble #11 solved: parlor bunny secret
    // Trouble #12 solved (solved in another area; listed by gor_irai)
    GSWF_TROUBLE_12_SOLVED = 5386,
    GSWF_TROUBLE_13_SOLVED = 5387, // Trouble #13 solved: Jolene storeroom cleanup
    // Trouble #14 solved (solved in another area; listed by gor_irai)
    GSWF_TROUBLE_14_SOLVED = 5388,
    // Trouble #15 solved (solved in another area; listed by gor_irai)
    GSWF_TROUBLE_15_SOLVED = 5389,
    // Trouble #16 solved: Ms. Mowz badge hunt (badge shop / gor_01 spawn her after it; also set by the stg9_02 skip)
    GSWF_TROUBLE_16_SOLVED = 5390,
    // Trouble #17 solved (solved in another area; listed by gor_irai)
    GSWF_TROUBLE_17_SOLVED = 5391,
    GSWF_TROUBLE_18_SOLVED = 5392, // Trouble #18 solved: Zess T. cookbook
    GSWF_TROUBLE_19_SOLVED = 5393, // Trouble #19 solved: Frankie's wedding ring
    GSWF_TROUBLE_20_SOLVED = 5394, // Trouble #20 solved (Podley)
    // Trouble #21 solved (solved in another area; listed by gor_irai)
    GSWF_TROUBLE_21_SOLVED = 5395,
    // Trouble #22 solved (solved in another area; listed by gor_irai)
    GSWF_TROUBLE_22_SOLVED = 5396,
    // Trouble #23 solved (solved in another area; listed by gor_irai)
    GSWF_TROUBLE_23_SOLVED = 5397,
    GSWF_TROUBLE_24_SOLVED = 5398, // Trouble #24 solved: Glitzville chair-fan briefcase code
    GSWF_TROUBLE_25_SOLVED = 5399, // Trouble #25 solved: General White search
    // Trouble #26 solved (solved in another area; listed by gor_irai)
    GSWF_TROUBLE_26_SOLVED = 5400,
    // Trouble #27 solved (solved in another area; listed by gor_irai)
    GSWF_TROUBLE_27_SOLVED = 5401,
    // Trouble #28 solved (solved in another area; listed by gor_irai)
    GSWF_TROUBLE_28_SOLVED = 5402,
    // Trouble #29 solved (solved in another area; listed by gor_irai)
    GSWF_TROUBLE_29_SOLVED = 5403,
    // Trouble #30 solved (solved in another area; listed by gor_irai)
    GSWF_TROUBLE_30_SOLVED = 5404,
    // Per-trouble scratch flag 0: "trouble giver talked to" for the active trouble (cleared on accepting a new one; range 5405-5421)
    GSWF_TROUBLE_WORK_BASE = 5405,
    // Per-trouble scratch flag 1: second step of the active trouble (key found, package handed over, ...)
    GSWF_TROUBLE_WORK_1 = 5406,
    GSWF_TROUBLE_WORK_2 = 5407, // Per-trouble scratch flag 2: third step of the active trouble
    GSWF_TROUBLE_WORK_3 = 5408, // Per-trouble scratch flag 3: fourth step of the active trouble
    GSWF_TROUBLE_WORK_4 = 5409, // Per-trouble scratch flag 4; trouble #25: the Poshley Heights hint was heard (pik_00, irai_25_03)
    // Per-trouble scratch flag 5 (range 5405-5421, cleared on accepting a trouble); trouble #25 sets it once General White has been woken in Fahr Outpost
    GSWF_TROUBLE_WORK_5 = 5410,
    // Per-trouble scratch flag 6 (range 5405-5421); trouble #25 sets it when the package is handed to General White
    GSWF_TROUBLE_WORK_6 = 5411,
    GSWF_TROUBLE_WORK_LAST = 5421,    // Last per-trouble scratch flag (loop bound)
    GSWF_GOR02_SHINE_SPRITE_1 = 5525, // Shine Sprite block pblk1 in gor_02 collected
    GSWF_GOR02_SHINE_SPRITE_2 = 5526, // Shine Sprite block pblk2 in gor_02 collected
    GSWF_GOR03_SHINE_SPRITE_1 = 5527, // Shine Sprite block pblk1 in gor_03 collected
    GSWF_GOR03_SHINE_SPRITE_2 = 5528, // Shine Sprite block pblk2 in gor_03 collected
    GSWF_GOR02_SHINE_SPRITE_3 = 5529, // Shine Sprite block pblk3 in gor_02 collected
    GSWF_TIK00_SHINE_SPRITE = 5530,   // Shine Sprite block pblk1 in tik_00 collected
    GSWF_TIK02_SHINE_SPRITE = 5531,   // Shine Sprite block pblk1 in tik_02 collected
    GSWF_TIK05_SHINE_SPRITE = 5532,   // Shine Sprite block pblk00 in tik_05 collected
    GSWF_TIK07_SHINE_SPRITE = 5533,   // Shine Sprite block pblk2 in tik_07 collected
    GSWF_TIK16_SHINE_SPRITE = 5534,   // Shine Sprite block pblk1 in tik_16 collected
    GSWF_TIK20_SHINE_SPRITE_1 = 5535, // Shine Sprite block pblk01 in tik_20 collected
    GSWF_TIK20_SHINE_SPRITE_2 = 5536, // Shine Sprite block pblk02 in tik_20 collected
    GSWF_TIK20_SHINE_SPRITE_3 = 5537, // Shine Sprite block pblk03 in tik_20 collected
    GSWF_GON04_SHINE_SPRITE = 5538,   // Shine Sprite block pblk1 in gon_04 collected
    GSWF_GON05_SHINE_SPRITE = 5539,   // Shine Sprite block pblk00 in gon_05 collected
    GSWF_GON12_SHINE_SPRITE = 5540,   // Shine Sprite block pblk00 in gon_12 collected
    GSWF_WIN02_SHINE_SPRITE = 5541,   // Shine Sprite block pblk00 in win_02 collected
    GSWF_MRI05_SHINE_SPRITE = 5542,   // Shine Sprite block pblk00 in mri_05 collected
    GSWF_MRI09_SHINE_SPRITE = 5543,   // Shine Sprite block pblk1 in mri_09 collected
    GSWF_MRI16_SHINE_SPRITE = 5544,   // Shine Sprite block pblk1 in mri_16 collected
    GSWF_MRI19_SHINE_SPRITE = 5545,   // Shine Sprite block pblk00 in mri_19 collected
    GSWF_TOU01_SHINE_SPRITE = 5546,   // Shine Sprite block pblk01 in tou_01 collected
    GSWF_TOU06_SHINE_SPRITE = 5547,   // Shine Sprite block pblk00 in tou_06 collected
    GSWF_GRA05_SHINE_SPRITE = 5548,   // Shine Sprite block blk01 in gra_05 collected
    GSWF_JIN05_SHINE_SPRITE = 5549,   // Shine Sprite block pblk00 in jin_05 collected
    GSWF_JIN09_SHINE_SPRITE = 5550,   // Shine Sprite block blk00 in jin_09 collected
    GSWF_JIN11_SHINE_SPRITE = 5551,   // Shine Sprite block pblk00 in jin_11 collected
    GSWF_MUJ03_SHINE_SPRITE = 5552,   // Shine Sprite block pblk01 in muj_03 collected
    GSWF_MUJ04_SHINE_SPRITE = 5553,   // Shine Sprite block pblk00 in muj_04 collected
    GSWF_DOU02_SHINE_SPRITE = 5554,   // Shine Sprite block pblk1 in dou_02 collected
    GSWF_DOU04_SHINE_SPRITE = 5555,   // Shine Sprite block pblk00 in dou_04 collected
    GSWF_DOU05_SHINE_SPRITE = 5556,   // Shine Sprite block pblk1 in dou_05 collected
    GSWF_DOU09_SHINE_SPRITE = 5557,   // Shine Sprite block pblk1 in dou_09 collected
    GSWF_DOU10_SHINE_SPRITE = 5558,   // Shine Sprite block pblk00 in dou_10 collected
    GSWF_RSH02_SHINE_SPRITE = 5559,   // Shine Sprite block pblk00 in rsh_02 collected
    // Excess Express cabin (rsh_04): the passenger in talk_konari gave the Shine Sprite reward for the Autograph; set but never tested (GSW0=294 guards the reward)
    GSWF_RSH04_SHINE_SPRITE_AUTOGRAPH = 5560,
    GSWF_EKI03_SHINE_SPRITE = 5561, // Shine Sprite block pblk01 in eki_03 collected
    GSWF_EKI06_SHINE_SPRITE = 5562, // Shine Sprite block pblk01 in eki_06 collected
    GSWF_PIK01_SHINE_SPRITE = 5563, // Shine Sprite block pblk01 in pik_01 collected
    GSWF_PIK03_SHINE_SPRITE = 5564, // Shine Sprite block pblk00 in pik_03 collected
    GSWF_BOM02_SHINE_SPRITE = 5565, // Shine Sprite block pblk01 in bom_02 collected
    GSWF_BOM03_SHINE_SPRITE = 5566, // Shine Sprite block pblk00 in bom_03 collected
    GSWF_GOR00_STAR_PIECE = 5567,   // gor00 Star Piece (field item item_00) collected
    // gor00 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_GOR00_STAR_PIECE_PANEL = 5568,
    // gor01 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_GOR01_STAR_PIECE_PANEL_1 = 5569,
    GSWF_GOR01_STAR_PIECE_1 = 5570, // gor01 Star Piece (field item item_00) collected
    GSWF_GOR01_STAR_PIECE_2 = 5571, // gor01 Star Piece (field item item_01) collected
    GSWF_GOR01_STAR_PIECE_3 = 5572, // gor01 Star Piece (field item item_02) collected
    // gor01 Star Piece (hidden under the spin floor kururin2) collected
    GSWF_GOR01_STAR_PIECE_PANEL_2 = 5573,
    // gor02 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_GOR02_STAR_PIECE_PANEL_1 = 5574,
    GSWF_GOR02_STAR_PIECE_1 = 5575, // gor02 Star Piece (field item item_star1) collected
    GSWF_GOR02_STAR_PIECE_2 = 5576, // gor02 Star Piece (field item item_star2) collected
    GSWF_GOR02_STAR_PIECE_3 = 5577, // gor02 Star Piece (field item item_star3) collected
    // gor02 Star Piece (hidden under the spin floor kururin2) collected
    GSWF_GOR02_STAR_PIECE_PANEL_2 = 5578,
    // gor03 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_GOR03_STAR_PIECE_PANEL = 5579,
    GSWF_GOR03_STAR_PIECE_1 = 5580, // gor03 Star Piece (field item item_00) collected
    GSWF_GOR03_STAR_PIECE_2 = 5581, // gor03 Star Piece (field item item_01) collected
    GSWF_GOR03_STAR_PIECE_3 = 5582, // gor03 Star Piece (field item item_02) collected
    // gor04 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_GOR04_STAR_PIECE_PANEL = 5583,
    GSWF_GOR04_STAR_PIECE = 5584,   // gor04 Star Piece (field item item_00) collected
    GSWF_TIK00_STAR_PIECE_1 = 5585, // tik00 Star Piece (field item item_00) collected
    GSWF_TIK00_STAR_PIECE_2 = 5586, // tik00 Star Piece (field item item_01) collected
    GSWF_TIK00_STAR_PIECE_3 = 5587, // tik00 Star Piece (field item item_02) collected
    // tik00 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_TIK00_STAR_PIECE_PANEL = 5588,
    // tik01 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_TIK01_STAR_PIECE_PANEL = 5589,
    // tik03 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_TIK03_STAR_PIECE_PANEL = 5590,
    GSWF_TIK04_STAR_PIECE = 5591, // tik04 Star Piece (field item item_02) collected
    // tik05 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_TIK05_STAR_PIECE_PANEL = 5592,
    GSWF_TIK06_STAR_PIECE = 5593,   // tik06 Star Piece (field item item_00) collected
    GSWF_TIK07_STAR_PIECE_1 = 5594, // tik07 Star Piece (field item item_00) collected
    GSWF_TIK07_STAR_PIECE_2 = 5595, // tik07 Star Piece (field item item_01) collected
    GSWF_TIK13_STAR_PIECE = 5596,   // tik13 Star Piece (field item item_00) collected
    // tik19 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_TIK19_STAR_PIECE_PANEL = 5597,
    // hei00 Star Piece (hidden in the tree, item item_ki01) collected
    GSWF_HEI00_STAR_PIECE_TREE = 5598,
    GSWF_HEI01_STAR_PIECE = 5599, // hei01 Star Piece (field item item_01) collected
    // hei02 Star Piece (hidden in the bush, item item_kusa_1) collected
    GSWF_HEI02_STAR_PIECE_BUSH = 5600,
    // nok00 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_NOK00_STAR_PIECE_PANEL = 5601,
    // nok01 Star Piece (hidden under the spin floor kururin2) collected
    GSWF_NOK01_STAR_PIECE_PANEL = 5602,
    // gon03 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_GON03_STAR_PIECE_PANEL = 5603,
    GSWF_GON04_STAR_PIECE_1 = 5604, // gon04 Star Piece (field item item00) collected
    GSWF_GON04_STAR_PIECE_2 = 5605, // gon04 Star Piece (field item item01) collected
    GSWF_GON05_STAR_PIECE = 5606,   // gon05 Star Piece (field item item00) collected
    GSWF_GON09_STAR_PIECE = 5607,   // gon09 Star Piece (field item piece00) collected
    GSWF_WIN02_STAR_PIECE = 5608,   // win02 Star Piece (field item item_00) collected
    // win03 Star Piece (hidden in the tree, item item_tree01) collected
    GSWF_WIN03_STAR_PIECE_TREE = 5609,
    GSWF_WIN03_STAR_PIECE = 5610, // win03 Star Piece (field item item_00) collected
    // win05 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_WIN05_STAR_PIECE_PANEL = 5611,
    // mri02 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_MRI02_STAR_PIECE_PANEL = 5612,
    // mri03 Star Piece (hidden under the spin floor kururin1) collected; mri_03 init also hides the spin floor model until it is collected
    GSWF_MRI03_STAR_PIECE_PANEL = 5613,
    // mri06 Star Piece (hidden in the planter, item item_ueki02) collected
    GSWF_MRI06_STAR_PIECE_PLANTER = 5614,
    GSWF_MRI12_STAR_PIECE = 5615, // mri12 Star Piece (field item item_00) collected
    // mri15 Star Piece (hidden in the planter, item item_ueki01) collected
    GSWF_MRI15_STAR_PIECE_PLANTER = 5616,
    GSWF_MRI17_STAR_PIECE = 5617,   // mri17 Star Piece (field item item_01) collected
    GSWF_TOU01_STAR_PIECE_1 = 5618, // tou01 Star Piece (field item item_03) collected
    GSWF_TOU01_STAR_PIECE_2 = 5619, // tou01 Star Piece (field item item_01) collected
    GSWF_TOU01_STAR_PIECE_3 = 5620, // tou01 Star Piece (field item item_02) collected
    GSWF_TOU01_STAR_PIECE_4 = 5621, // tou01 Star Piece (field item item_04) collected
    // tou01 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_TOU01_STAR_PIECE_PANEL = 5622,
    // tou02 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_TOU02_STAR_PIECE_PANEL = 5623,
    GSWF_TOU05_STAR_PIECE = 5624, // tou05 Star Piece (field item item01) collected
    // Star Piece slot for Grubba's drawer in the Star Piece flag block; set together with GSWF 2508 but never read
    GSWF_TOU05_STAR_PIECE_DRAWER = 5625,
    // tou06 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_TOU06_STAR_PIECE_PANEL = 5626,
    GSWF_TOU12_STAR_PIECE = 5627, // tou12 Star Piece (field item item01) collected
    // usu00 Star Piece (hidden in the bush, item item_kusa_04) collected
    GSWF_USU00_STAR_PIECE_BUSH = 5628,
    GSWF_USU00_STAR_PIECE = 5629,   // usu00 Star Piece (field item item00) collected
    GSWF_USU01_STAR_PIECE = 5630,   // usu01 Star Piece (field item item_01) collected
    GSWF_GRA02_STAR_PIECE_1 = 5631, // gra02 Star Piece (field item item00) collected
    GSWF_GRA02_STAR_PIECE_2 = 5632, // gra02 Star Piece (field item item01) collected
    GSWF_GRA06_STAR_PIECE = 5633,   // gra06 Star Piece (field item item00) collected
    // jin03 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_JIN03_STAR_PIECE_PANEL = 5634,
    GSWF_JIN05_STAR_PIECE = 5635, // jin05 Star Piece (field item item_00) collected
    GSWF_JIN07_STAR_PIECE = 5636, // jin07 Star Piece (field item item_00) collected
    // jin08 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_JIN08_STAR_PIECE_PANEL = 5637,
    // muj00 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_MUJ00_STAR_PIECE_PANEL = 5638,
    GSWF_MUJ01_STAR_PIECE_1 = 5639, // muj01 Star Piece (field item item_00) collected
    GSWF_MUJ01_STAR_PIECE_2 = 5640, // muj01 Star Piece (field item item_01) collected
    // muj02 Star Piece (hidden in the bush, item item_kusa_6) collected
    GSWF_MUJ02_STAR_PIECE_BUSH = 5641,
    GSWF_MUJ03_STAR_PIECE = 5642, // muj03 Star Piece (field item item_00) collected
    GSWF_MUJ05_STAR_PIECE = 5643, // muj05 Star Piece (field item item_01) collected
    GSWF_DOU02_STAR_PIECE = 5644, // dou02 Star Piece (field item item_00) collected
    // dou03 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_DOU03_STAR_PIECE_PANEL = 5645,
    GSWF_DOU04_STAR_PIECE = 5646, // dou04 Star Piece (field item starpice) collected
    // dou06 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_DOU06_STAR_PIECE_PANEL = 5647,
    // rsh00 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_RSH00_STAR_PIECE_PANEL = 5648,
    // rsh02 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_RSH02_STAR_PIECE_PANEL = 5649,
    // Excess Express dining car (rsh_03): returned the Galley Pot to the cook and got a Star Piece; set but never tested
    GSWF_RSH03_STAR_PIECE_GALLEY_POT = 5650,
    // Excess Express dining car (rsh_03): returned the Shell Earrings to the waitress and got a Star Piece; set but never tested
    GSWF_RSH03_STAR_PIECE_WAITRESS = 5651,
    // Excess Express cabin (rsh_04): Star Piece taken from luggage shelf tana_5; afterwards the shelf only shows its message
    GSWF_RSH04_STAR_PIECE_SHELF = 5652,
    GSWF_EKI02_STAR_PIECE = 5653,   // eki02 Star Piece (field item item) collected
    GSWF_PIK00_STAR_PIECE_1 = 5654, // pik00 Star Piece (field item item_00) collected
    // pik00 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_PIK00_STAR_PIECE_PANEL = 5655,
    GSWF_PIK00_STAR_PIECE_2 = 5656, // pik00 Star Piece (field item item_01) collected
    GSWF_PIK04_STAR_PIECE = 5657,   // pik04 Star Piece (field item item_00) collected
    // bom00 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_BOM00_STAR_PIECE_PANEL = 5658,
    GSWF_BOM01_STAR_PIECE = 5659, // bom01 Star Piece (field item item_00) collected
    GSWF_BOM02_STAR_PIECE = 5660, // bom02 Star Piece (field item item_00) collected
    // bom02 Star Piece (hidden under the spin floor kururin1) collected
    GSWF_BOM02_STAR_PIECE_PANEL = 5661,
    GSWF_BOM03_STAR_PIECE = 5662, // bom03 Star Piece (field item item00) collected
    GSWF_BOM04_STAR_PIECE = 5663, // bom04 Star Piece (field item item00) collected
    GSWF_MOO02_STAR_PIECE = 5664, // moo02 Star Piece (field item item00) collected
    // aji_03 prize item keihin08 (Star Piece) picked up; it is spawned on entry until then
    GSWF_AJI03_STAR_PIECE_PRIZE = 5665,
    GSWF_AJI08_STAR_PIECE = 5666, // aji08 Star Piece (field item item00) collected
} GswfId;
