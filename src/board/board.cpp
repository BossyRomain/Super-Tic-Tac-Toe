#include "board/board.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Board::Board(): m_rows(DEFAULT_ROWS), m_cols(DEFAULT_COLS) {
    m_cells = new int*[m_rows];
    for(int r = 0; r < m_rows; r++) {
        m_cells[r] = new int[m_cols];
        for(int c = 0; c < m_cols; c++) {
            m_cells[r][c] = 0;
        }
    }
}

Board::Board(const Board& board): m_rows(board.m_rows), m_cols(board.m_cols) {
    m_cells = new int*[m_rows];
    for(int r = 0; r < m_rows; r++) {
        m_cells[r] = new int[m_cols];
        for(int c = 0; c < m_cols; c++) {
            m_cells[r][c] = board.m_cells[r][c];
        }
    }
}

Board::~Board() {
    delete_cells();
}

int Board::get_rows() const {
    return m_rows;
}

int Board::get_cols() const {
    return m_cols;
}

void Board::set_rows(int rows) {
    if(rows > 0 && m_rows != rows) {
        resize(rows, m_cols);
    }
}

void Board::set_cols(int cols) {
    if(cols > 0 && m_cols != cols) {
        resize(m_rows, cols);
    }
}

void Board::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_rows"), &Board::get_rows);
    ClassDB::bind_method(D_METHOD("set_rows", "rows"), &Board::set_rows);

    ClassDB::bind_method(D_METHOD("get_cols"), &Board::get_cols);
    ClassDB::bind_method(D_METHOD("set_cols", "cols"), &Board::set_cols);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "rows"), "set_rows", "get_rows");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cols"), "set_cols", "get_cols");
}

void Board::resize(int rows, int cols) {
    if(rows == m_rows && cols == m_cols) {
        // if the dimensions are unchanged
        return;
    }

    int **p_newCells = new int*[rows];
    for(int r = 0; r < rows; r++) {
        p_newCells[r] = new int[cols];
        for(int c = 0; c < cols; c++) {
            if(r < m_rows && c < m_cols) {
                // Cell keeped
                p_newCells[r][c] = m_cells[r][c];
            } else {
                // Creates new cell
                p_newCells[r][c] = 0;
            }
        }
    }

    delete_cells();

    m_rows = rows;
    m_cols = cols;
    m_cells = p_newCells;
}

void Board::delete_cells() {
    for(int r = 0; r < m_rows; r++) {
        delete m_cells[r];
    }
    delete m_cells;
}