#ifndef NO_SPECIALS_EARLY_HEURISTIC_H
#define NO_SPECIALS_EARLY_HEURISTIC_H

#include "players/ai_heuristics/ai_heuristic.h"
#include <vector>

namespace godot {

/**
 * Avoid to use specials actions at the beginning of a game (3 first turns of the player).
 */
class NoSpecialsEarlyHeuristic: public AIHeuristic {
    GDCLASS(NoSpecialsEarlyHeuristic, AIHeuristic)

public:

    NoSpecialsEarlyHeuristic();

    ~NoSpecialsEarlyHeuristic();

    double calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type) override;

protected:

    static void _bind_methods();

private:

    int get_players_nb_turns(int player_id) const;

    std::vector<int> m_turns;
};

}

#endif