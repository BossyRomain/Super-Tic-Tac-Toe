#ifndef ACTION_PLACE_PAWN_H
#define ACTION_PLACE_PAWN_H

#include "actions/action.h"

namespace godot {

/**
 * Try to place a pawn on a targeted cell, the cell must be empty
 * (not banned or with an pawn on it) to succeed.
 */
class ActionPlacePawn: public Action {
    GDCLASS(ActionPlacePawn, Action);

public:

    ActionPlacePawn();

    ~ActionPlacePawn();

    Vector2i get_coords();

    void set_coords(Vector2i coords);

    bool execute(GameState *game_state) override;
    
    virtual Action* duplicate() const override;

protected:

    static void _bind_methods();

private:

    Vector2i m_coords;
};

}

#endif