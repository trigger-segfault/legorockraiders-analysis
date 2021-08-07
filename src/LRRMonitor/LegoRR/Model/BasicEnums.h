#pragma once

namespace lego {

// Many boolean returns from LegoRR functions may have a 3rd return state for error, this enum is for that.
enum BOOL3 : int
{
	BOOL3_FALSE = 0, // false
	BOOL3_TRUE  = 1, // true
	BOOL3_ERROR = 2, // error
};

enum Direction : int
{
	DIRECTION_UP    = 0,
	DIRECTION_RIGHT = 1,
	DIRECTION_DOWN  = 2,
	DIRECTION_LEFT  = 3,
};

}
