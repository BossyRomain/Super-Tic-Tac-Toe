#ifndef ACTION_BAN_CELL_H
#define ACTION_BAN_CELL_H

#include "actions/action.h"

namespace godot {

/**
 * Ban a targeted so that no players can place a pawn on it for the rest of a game.
 * Succeed if the targeted cell is not already banned.
 */
class ActionBanCell: public Action {
    GDCLASS(ActionBanCell, Action);

public:

    ActionBanCell();

    ~ActionBanCell();

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