#include "players/ai_heuristics/block_pawns_heuristic.h"

using namespace godot;

BlockPawnsHeuristic::BlockPawnsHeuristic() {

}

BlockPawnsHeuristic::~BlockPawnsHeuristic() {

}

double BlockPawnsHeuristic::calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type) {
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
    int nb_blocked = 0;

    for(Vector2i dir: dirs) {
        int cell_val = board->get_cell_at(coords + dir);
        if(cell_val > 0 && cell_val != player->get_id()) {
            nb_blocked++;
        }
    }

    return nb_blocked / 8.0;
}

void BlockPawnsHeuristic::_bind_methods() {

}