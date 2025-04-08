#ifndef MAX_LINES_HEURISTIC_H
#define MAX_LINES_HEURISTIC_H

#include "players/ai_heuristics/ai_heuristic.h"

namespace godot {

class MaxLinesHeuristic: public AIHeuristic {
    GDCLASS(MaxLinesHeuristic, AIHeuristic)

public:

    MaxLinesHeuristic();

    ~MaxLinesHeuristic();

    double calculate_action_score(Board *board, AIPlayer *player, Vector2i coords, int action_type);

protected:

    static void _bind_methods();

private:
};

}

#endif