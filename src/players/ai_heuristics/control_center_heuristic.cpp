#include "players/ai_heuristics/control_center_heuristic.h"

using namespace godot;

ControlCenterHeuristic::ControlCenterHeuristic() {

}

ControlCenterHeuristic::~ControlCenterHeuristic() {

}

double ControlCenterHeuristic::calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type) {
    Vector2 board_center(board->get_cols() / 2.0, board->get_rows() / 2.0);

    double dist_to_center = sqrt(pow(board_center.x - coords.x, 2.0) + pow(board_center.y - coords.y, 2.0));
    double max_dist = sqrt(pow(board_center.x, 2.0) + pow(board_center.y, 2.0));

    return 1.0 - (dist_to_center / max_dist);
}

void ControlCenterHeuristic::_bind_methods() {

}
