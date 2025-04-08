#ifndef BLOCK_LINES_HEURISTIC_H
#define BLOCK_LINES_HEURISTIC_H

#include "players/ai_heuristics/ai_heuristic.h"

namespace godot {

class BlockLinesHeuristic: public AIHeuristic {
    GDCLASS(BlockLinesHeuristic, AIHeuristic)

public:

    BlockLinesHeuristic();

    ~BlockLinesHeuristic();

    double calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type);

protected:

    static void _bind_methods();

private:
};

}

#endif