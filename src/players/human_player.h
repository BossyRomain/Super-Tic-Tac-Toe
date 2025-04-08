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

    int get_action() const;

    Callable get_cell_coords_callable() const;

    void set_action(int action_type);

    void set_get_cell_coords_callable(Callable callable);

    void play(Board *board) override;

protected:

    static void _bind_methods();

private:

    int m_action;

    Callable m_get_cell_coords;
};

}

#endif