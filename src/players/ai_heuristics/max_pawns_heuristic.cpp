#include "players/ai_heuristics/max_pawns_heuristic.h"

using namespace godot;

MaxPawnsHeuristic::MaxPawnsHeuristic() {

}

MaxPawnsHeuristic::~MaxPawnsHeuristic() {

}

double MaxPawnsHeuristic::calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type) {
    return action_type == Player::Actions::PLACE_PAWN || action_type == Player::Actions::REPLACE_PAWN ? 1.0 : 0.0;
}

void MaxPawnsHeuristic::_bind_methods() {
}