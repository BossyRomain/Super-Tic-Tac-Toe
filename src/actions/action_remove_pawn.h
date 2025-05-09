#ifndef ACTION_REMOVE_PAWN_H
#define ACTION_REMOVE_PAWN_H

#include "actions/action.h"

namespace godot {

/**
 * Try to remove a pawn from an opponent, 
 * succeed if the targeted cell has an opponent pawn on it.
 */
class ActionRemovePawn: public Action {
    GDCLASS(ActionRemovePawn, Action);

public:

    ActionRemovePawn();

    ~ActionRemovePawn();

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