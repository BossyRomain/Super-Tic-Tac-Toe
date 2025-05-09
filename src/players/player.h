#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/core/object.hpp>
#include <map>
#include "board/board.h"
#include "actions/action.h"

namespace godot {

#define HUMAN_PLAYER 0
#define AI_DUMB 1
#define AI_EASY 2
#define AI_MEDIUM 3
#define AI_HARD 4
#define AI_LEGENDARY 5

/**
 * Class containing all the informations about one player (regardless of its type).
 */
class Player: public Object {
    GDCLASS(Player, Object);

public:

    Player();

    ~Player();

    void _ready();

    int get_id() const;

    int get_type() const;

    /**
     * Returns the number of uses left for a type of action.
     */
    int get_action_uses_left(int action_type) const;

    void set_id(int id);

    void set_type(int type);

    /**
     * Sets the number of uses left for a type of action.
     */
    void set_action_uses_left(int action_type, int uses_left);

    /**
     * Returns true if the player can use a type of action, else returns false.
     */
    bool can_use_action(int action_type) const;

    /**
     * Decrement the number of uses left for an action by one.
     * Does nothing if there is no more uses left for this action.
     */
    void decrement_action(int action_type);

    Player* duplicate() const;

protected:

    static void _bind_methods();
    
private:

    int m_id;

    int m_type;

    /**
     * The number of uses left for a type of action.
     */
    std::map<int, int> m_actionsUsesLeft;
};

}

#endif