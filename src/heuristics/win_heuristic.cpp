#include "heuristics/win_heuristic.h"

using namespace godot;

WinHeuristic::WinHeuristic() {

}

WinHeuristic::~WinHeuristic() {

}

double WinHeuristic::calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, ActionType action_type) {
    if(action_type == ActionType::PLACE_PAWN || action_type == ActionType::REPLACE_PAWN) {
        Board *copy = board->clone();
        copy->set_cell_at(coords, player->get_id());
        int winner = copy->get_winner();
        memdelete(copy);
        return winner == player->get_id() ? 1.0 : 0.0;
    }
    return 0.0;
}

void WinHeuristic::_bind_methods() {

}