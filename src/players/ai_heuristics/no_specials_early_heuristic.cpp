#include "players/ai_heuristics/no_specials_early_heuristic.h"

using namespace godot;

NoSpecialsEarlyHeuristic::NoSpecialsEarlyHeuristic() {

}

NoSpecialsEarlyHeuristic::~NoSpecialsEarlyHeuristic() {

}

double NoSpecialsEarlyHeuristic::calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type) {
    if(m_turns.empty() || m_turns[m_turns.size() - 1] != player->get_id()) {
        m_turns.push_back(player->get_id());
    }

    int nb_turns = get_players_nb_turns(player->get_id());

    if(action_type == Player::Actions::PLACE_PAWN) {
        return 1.0;
    }

    return nb_turns > 3 ? 1.0 : - 1.0;
}

void NoSpecialsEarlyHeuristic::_bind_methods() {

}

int NoSpecialsEarlyHeuristic::get_players_nb_turns(int player_id) const {
    int nb_turns = 0;
    for(int id: m_turns) {
        if(player_id == id) {
            nb_turns++;
        }
    }
    return nb_turns;
}