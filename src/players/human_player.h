#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "players/player.h"
#include <godot_cpp/classes/input_event.hpp>

namespace godot {

/**
 * Represents a human player.
 */
class HumanPlayer: public Player {
    GDCLASS(HumanPlayer, Player);

public:

    HumanPlayer();

    ~HumanPlayer();

    void _input(Ref<InputEvent> event);

    void _ready();

    ActionType get_action_type() const;

    Callable get_cell_coords_callable() const;

    void set_action_type(ActionType action_type);

    void set_get_cell_coords_callable(Callable callable);

    void choose_action(Board *board) override;

protected:

    static void _bind_methods();

private:

    ActionType m_action_type;

    Callable m_get_cell_coords;
};

}

#endif