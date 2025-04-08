#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/node.hpp>
#include <map>
#include "board/board.h"

namespace godot {

/**
 * The base abstract class for all the types of players.
 */
class Player: public Node {
    GDCLASS(Player, Node);

public:

    enum Actions {
        PLACE_PAWN = 0,
        REMOVE_PAWN = 1,
        REPLACE_PAWN = 2,
        BAN_CELL = 3,
    };

    Player();

    ~Player();

    void _ready();

    int get_id() const;

    /**
     * Returns the number of uses left for a type of action.
     */
    int get_action_uses_left(int actionType) const;

    void set_id(int id);

    /**
     * Sets the number of uses left for a type of action.
     */
    void set_action_uses_left(int actionType, int left);

    /**
     * Method called when the player need to choose an action during his turn.
     * When the player has choosed, the signal action_choosed is emited.
     */
    virtual void play(Board *board);

protected:

    static void _bind_methods();
    
private:

    int m_id;

    /**
     * The number of uses left for a type of action.
     */
    std::map<int, int> m_actionsUsesLeft;
};

}

VARIANT_ENUM_CAST(Player::Actions);

#endif