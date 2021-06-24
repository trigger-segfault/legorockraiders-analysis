
#ifndef LEGORR__PTL_EVENTS_H
#define LEGORR__PTL_EVENTS_H


enum PTLEVENTS
{
/*  |E */ PTLEVENT_NULL                              = 0, // no action is taken
/*  |  */ PTLEVENT_SELECT                            = 1,
/*  |  */ PTLEVENT_SELECTED                          = 2,
/*  |  */ PTLEVENT_CLEAR_SELECTION                   = 3,
/*  |  */ PTLEVENT_DESELECT                          = 4,
/*  |E */ PTLEVENT_GOTO                              = 5,
/*  |E */ PTLEVENT_ROCK_MONSTER_GOTO                 = 6,
/* C|  */ PTLEVENT_ROCK_MONSTER_GOTO_COMPLETE        = 7,
/*  |  */ PTLEVENT_USER_GOTO                         = 8,
/*  |  */ PTLEVENT_FIRST_PERSON                      = 9,
/*  |  */ PTLEVENT_TRACK_OBJECT                      = 10,
/*  |  */ PTLEVENT_TOP_VIEW                          = 11,
/*  |  */ PTLEVENT_PLAY_SAMPLE                       = 12,
/* C|  */ PTLEVENT_DIG                               = 13,
/* C|  */ PTLEVENT_DIG_COMPLETE                      = 14,
/* C|  */ PTLEVENT_REPAIR                            = 15,
/*  |  */ PTLEVENT_REPAIR_COMPLETE                   = 16,
/* C|  */ PTLEVENT_REINFORCE                         = 17,
/* C|  */ PTLEVENT_REINFORCE_COMPLETE                = 18,
/*  |E */ PTLEVENT_ROCK_FALL                         = 19,
/* C|  */ PTLEVENT_ROCK_FALL_COMPLETE                = 20,
/*  |E */ PTLEVENT_GENERATE_CRYSTAL                  = 21,
/* C|  */ PTLEVENT_GENERATE_CRYSTAL_COMPLETE         = 22,
/* C|E */ PTLEVENT_COLLECT_CRYSTAL                   = 23,
/* C|  */ PTLEVENT_COLLECT_CRYSTAL_COMPLETE          = 24,
/*  |E */ PTLEVENT_CRYSTAL_TO_REFINERY               = 25,
/* C|  */ PTLEVENT_CRYSTAL_TO_REFINERY_COMPLETE      = 26,
/*  |E */ PTLEVENT_GENERATE_ORE                      = 27,
/* C|  */ PTLEVENT_GENERATE_ORE_COMPLETE             = 28,
/* C|E */ PTLEVENT_COLLECT_ORE                       = 29,
/*  |  */ PTLEVENT_COLLECT_ORE_COMPLETE              = 30,
/*  |E */ PTLEVENT_GENERATE_ROCK_MONSTER             = 31,
/* C|  */ PTLEVENT_GENERATE_ROCK_MONSTER_COMPLETE    = 32,
/*  |E */ PTLEVENT_GATHER_ROCK                       = 33,
/* C|  */ PTLEVENT_GATHER_ROCK_COMPLETE              = 34,
/*  |E */ PTLEVENT_PICK_RANDOM_FLOOR                 = 35,
/* C|  */ PTLEVENT_PICK_RANDOM_FLOOR_COMPLETE        = 36,
/*  |E */ PTLEVENT_ATTACK_BUILDING                   = 37,
/*  |  */ PTLEVENT_ATTACK_BUILDING_COMPLETE          = 38,
/* C|  */ PTLEVENT_CLEAR                             = 39,
/* C|  */ PTLEVENT_CLEAR_COMPLETE                    = 40,
/*  |  */ PTLEVENT_GET_IN                            = 41,
/*  |  */ PTLEVENT_MAN_SELECTED_AND_MONSTER_CLICKED  = 42,
/*  |  */ PTLEVENT_FOLLOW_ATTACK                     = 43,
/* C|  */ PTLEVENT_COLLECT_TOOL                      = 44,
/*  |  */ PTLEVENT_REDUCE_SELECTION                  = 45,
/*  |  */ PTLEVENT_CLEAR_FALL_IN                     = 46,
/*  |  */ PTLEVENT_CLEAR_FALL_IN_COMPLETE            = 47,
/* C|  */ PTLEVENT_BUILD_PATH                        = 48,
/*  |  */ PTLEVENT_BUILD_PATH_COMPLETE               = 49,
/* C|  */ PTLEVENT_TRAIN                             = 50,
/*  |  */ PTLEVENT_TRAIN_COMPLETE                    = 51,
/*  |  */ PTLEVENT_GENERATE_CRYSTAL_AND_ORE          = 52,
/*  |  */ PTLEVENT_GENERATE_CRYSTAL_AND_ORE_COMPLETE = 53,
/*  |E */ PTLEVENT_GENERATE_FROM_CRY_ORE             = 54,
/*  |  */ PTLEVENT_GENERATE_FROM_CRY_ORE_COMPLETE    = 55,
/* C|  */ PTLEVENT_UPGRADE                           = 56,
/*  |  */ PTLEVENT_UPGRADE_COMPLETE                  = 57,
/*  |  */ PTLEVENT_CLEAR_BUILDING                    = 58,
/*  |  */ PTLEVENT_CLEAR_BUILDING_COMPLETE           = 59,
/*  |  */ PTLEVENT_CLEAR_INITIAL                     = 60,
/*  |  */ PTLEVENT_CLEAR_INITIAL_COMPLETE            = 61,
/*  |  */ PTLEVENT_CLEAR_REMOVE_PATH                 = 62,
/* C|  */ PTLEVENT_CLEAR_REMOVE_PATH_COMPLETE        = 63,
/*  |  */ PTLEVENT_DEBUG_DESTROY_ALL                 = 64,
};


#endif /* LEGORR__PTL_EVENTS_H */
