#include "actions/action_switch_pawns.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

ActionSwitchPawns::ActionSwitchPawns() {}

ActionSwitchPawns::~ActionSwitchPawns() {}

bool ActionSwitchPawns::execute(GameState *game_state) {
    Board *board = game_state->get_board();
    const int nb_players = game_state->nb_players();

    for(int row = 0; row < board->get_rows(); row++) {
        for(int col = 0; col < board->get_cols(); col++) {
            Vector2i coords(col, row);
            int cell = board->get_cell_at(coords);

            if(cell > EMPTY_CELL) {
                cell = cell == nb_players ? 1 : cell + 1;
                board->set_cell_at(coords, cell);
            }
        }
    }
    game_state->current_player()->decrement_action(SWITCH_PAWNS);

    return true;
}

Action* ActionSwitchPawns::duplicate() const {
    return memnew(ActionSwitchPawns);
}

void ActionSwitchPawns::_bind_methods() {
    ClassDB::bind_method(D_METHOD("execute", "game_state"), &ActionSwitchPawns::execute);
}