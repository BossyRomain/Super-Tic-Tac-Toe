#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/core/object.hpp>
#include <godot_cpp/classes/node.hpp>
#include <map>
#include "board/board.h"

namespace godot {

enum ActionType {
    PLACE_PAWN = 0,
    REMOVE_PAWN,
    REPLACE_PAWN,
    BAN_CELL
};

class Action;

/**
 * The base abstract class for all the types of players.
 */
class Player: public Node {
    GDCLASS(Player, Node);

public:

    Player();

    ~Player();

    void _ready();

    int get_id() const;

    /**
     * Returns the number of uses left for a type of action.
     */
    int get_action_uses_left(ActionType action_type) const;

    void set_id(int id);

    /**
     * Returns true if the player can still use a type of action, else false.
     */
    bool can_use_action(ActionType action_type) const;

    /**
     * Decrement the number of uses left for a type of action by one.
     */
    void decrement_uses_action(ActionType action_type);

    /**
     * Method called when the player need to choose an action during his turn.
     * When the player has choosed, the signal action_choosed is emited.
     */
    virtual void choose_action(Board *board);

protected:

    static void _bind_methods();
    
private:

    int m_id;

    /**
     * The number of uses left for a type of action.
     */
    std::map<ActionType, int> m_actionsUsesLeft;
};

class Action: public Object {
    GDCLASS(Action, Object);

public:

    Action();

    ~Action();

    ActionType get_type() const;

    Vector2i get_coords() const;

    Player* get_player() const;

    void set_type(ActionType type);

    void set_coords(Vector2i coords);

    void set_player(Player *player);

    /**
     * Play the action, returns true if the action succeed, else returns false.
     */
    bool execute(Board *board);

protected:

    static void _bind_methods();

private:

    ActionType m_type;

    Vector2i m_coords;

    Player *m_player;
};

}

VARIANT_ENUM_CAST(ActionType);

#endif