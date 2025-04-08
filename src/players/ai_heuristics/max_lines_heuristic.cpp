#include "players/ai_heuristics/max_lines_heuristic.h"

using namespace godot;

MaxLinesHeuristic::MaxLinesHeuristic() {

}

MaxLinesHeuristic::~MaxLinesHeuristic() {

}

double MaxLinesHeuristic::calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type) {
    if(action_type == Player::Actions::REMOVE_PAWN || action_type == Player::Actions::BAN_CELL) {
        return -1.0;
    }

    const Vector2i dirs[] = {
        Vector2i(1, 0),
        Vector2i(-1, 0),
        Vector2i(0, 1),
        Vector2i(0, -1),
        Vector2i(1, 1),
        Vector2i(-1, 1),
        Vector2i(1, -1),
        Vector2i(-1, -1),
    };
    const int NB_TO_WIN = 4;

    // Number of almost winning lines
    int nb_lines_almost = 0;
    // Number of lines that are not almost winning
    int nb_lines_other = 0;

    for(Vector2i dir: dirs) {
        int i = 1;
        while(i < NB_TO_WIN - 1 && board->get_cell_at(coords + dir * i) == player->get_id()) {
            i++;
        }

        if(i == NB_TO_WIN - 1) {
            nb_lines_almost++;
        } else if(i > 1 || board->get_cell_at(coords + dir) == player->get_id()) {
            nb_lines_other++;
        }
    }

    if(nb_lines_almost > 0) {
        return nb_lines_almost / 8.0;
    } else {
        return nb_lines_other / 8.0;
    }
}

void MaxLinesHeuristic::_bind_methods() {

}