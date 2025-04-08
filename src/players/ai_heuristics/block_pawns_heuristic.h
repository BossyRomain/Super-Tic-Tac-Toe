#ifndef BLOCK_PAWNS_HEURISTIC_H
#define BLOCK_PAWNS_HEURISTIC_H

#include "players/ai_heuristics/ai_heuristic.h"

namespace godot {

/**
 * Try to place pawns next to the maximum amount of others players pawns.
*/
class BlockPawnsHeuristic: public AIHeuristic {
    GDCLASS(BlockPawnsHeuristic, AIHeuristic)

public:

    BlockPawnsHeuristic();

    ~BlockPawnsHeuristic();

    double calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type);

protected:

    static void _bind_methods();

private:
};

}

#endif