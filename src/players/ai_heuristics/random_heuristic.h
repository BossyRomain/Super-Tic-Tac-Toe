#ifndef RANDOM_HEURISTIC_H
#define RANDOM_HEURISTIC_H

#include "players/ai_heuristics/ai_heuristic.h"

namespace godot {

/**
 * Give a random score to eaech action, regardless of the board's state.
 */
class RandomHeuristic: public AIHeuristic {
    GDCLASS(RandomHeuristic, AIHeuristic)

public:

    RandomHeuristic();

    ~RandomHeuristic();

    double calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type) override;

protected:

    static void _bind_methods();

private:
};

}

#endif