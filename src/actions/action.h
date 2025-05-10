#ifndef ACTION_H
#define ACTION_H

#include <godot_cpp/core/object.hpp>
#include "game_state/game_state.h"
#include <godot_cpp/core/class_db.hpp>

namespace godot {

#define PLACE_PAWN 0
#define REPLACE_PAWN 1
#define BAN_CELL 2
#define SWITCH_PAWNS 3

class GameState;

/**
 * Base class for all the actions the players can make in the game.
 */
class Action: public Object {
    GDCLASS(Action, Object);

public:

    Action();

    ~Action();

    /**
     * Executes the action on a given state of a game.
     * Returns true if the action successfully execute, else returns false.
     */
    virtual bool execute(GameState *game_state);

    virtual Action* duplicate() const =0;

protected:

    static void _bind_methods();

};

}

#endif