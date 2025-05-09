#ifndef ACTION_REPLACE_PAWN_H
#define ACTION_REPLACE_PAWN_H

#include "actions/action.h"

namespace godot {

/**
 * Replace a pawn of an opponent on a targeted cell by a player pawn.
 * Succeed if the targeted cell has an opponent pawn on it.
 */
class ActionReplacePawn: public Action {
    GDCLASS(ActionReplacePawn, Action);

public:

    ActionReplacePawn();

    ~ActionReplacePawn();

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