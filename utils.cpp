#include "utils.h"
#include <iostream>

int min(int a, int b){
    if (a < b)
        return a;
    return b;
}

int max(int a, int b){
    if (a > b)
        return a;
    return b;
}

// class Tetris
Tetris::Tetris(){
    buildGrid();
}

void Tetris::add(std::unique_ptr<Tetrimino> tetrimino){
    m_tetriminos.push_back(std::move(tetrimino));
}

Tetrimino& Tetris::current() {
    return *m_tetriminos[m_tetriminos.size()-1];
}
void Tetris::buildGrid() {
    for (int x = 0; x < m_window.x / STEP; ++x) {
        m_grid.push_back(std::vector<bool>{});
        for (int y = 0; y < m_window.y / STEP; ++y){
            m_grid[x].push_back(true);
        }
    }
}

void Tetris::updateGrid(){
    Point* shape = current().getShape();
    for (size_t i = 0; i < 4; ++i) {
        int x = shape[i].x / STEP;
        int y = shape[i].y / STEP;
        m_grid[x][y] = false;
    }
}

std::unique_ptr<Tetrimino> Tetris::block() {
    Type type = static_cast<Type>(std::rand() % 7);
    return block(type);
}


std::unique_ptr<Tetrimino> Tetris::block(Type type) {
    int x = (std::rand() % 10) * STEP;
    switch (type){
        case T:
            return std::make_unique<Teewee>(Point{x, 0});
        case Block:
            return std::make_unique<Smashboy>(Point{x, 0});
        case L:
            return std::make_unique<OrangeRicky>(Point{x, 0});
        case ReverseL:
            return std::make_unique<BlueRicky>(Point{x, 0});
        case Z:
            return std::make_unique<Cleveland>(Point{x, 0});
        case S:
            return std::make_unique<RhodeIsland>(Point{x, 0});
        case I:
            return std::make_unique<Hero>(Point{x, 0});
    }
}

// class Tetrimino
// Tetrimino::Tetrimino(Point a) {
//     update(a, m_window);
// }

// bool Tetrimino::update(Point& a, Point& dim){
//     bool isUpdated = false;
//     m_pos.x = a.x;
//     m_pos.y = a.y;
  
//     Point un = Point{m_pos.x, m_pos.y + STEP};
//     Point deux = Point{m_pos.x,  m_pos.y + STEP * 2};
//     Point trois = Point{m_pos.x + STEP, m_pos.y + STEP};

//     if (lower(m_pos, dim) && lower(un, dim) && lower(deux, dim) && lower(trois, dim)) {
//         m_piece[0] = m_pos;
//         m_piece[1] = un;
//         m_piece[2] = deux;
//         m_piece[3] = trois;
//         isUpdated = true;
//     }
  
//     return isUpdated;
// }
bool Tetrimino::canMoveDown(int bound){
    bool move = true;
    for (int i = 0; i < 4; ++i){
        if (m_piece[i].y >= bound){
            move = false;
            break;
        }
    }
    return move;
}
bool Tetrimino::canMove(std::vector<std::vector<bool>> grid, char direction){
    bool move = true;
    int a = 0;
    int b = 0;
    switch (direction){
        case 'l':
            a = - STEP;
            b = 0;
            break;
        case 'r':
            a = STEP;
            b = 0;
            break;
        default: // down
            a = 0;
            b = STEP;
    }
    for (int i = 0; i < 4; ++i){
        if (!grid[(m_piece[i].x + a) / STEP ][(m_piece[i].y + b) / STEP]){
            move = false;
            break;
        }
    }
    return move;
}

bool Tetrimino::canMoveLeft(int bound){
    bool move = true;
    for (int i = 0; i < 4; ++i){
        if (m_piece[i].x < bound){
            move = false;
            break;
        }
    }
    return move;
}

bool Tetrimino::canMoveRight(int bound){
    bool move = true;
    for (int i = 0; i < 4; ++i){
        if (m_piece[i].x >= bound){
            move = false;
            break;
        }
    }
    return move;
}

bool Tetrimino::lower(Point const& a, Point const& b) {
    bool islower = false;
    if (a.x < b.x && a.y < b.y){
        islower = true;
    }
    return islower;
}

Point* Tetrimino::getShape()
{
    return m_piece;
}

void Tetrimino::moveDown(int increment){
    m_pos.y += increment;
    update(m_pos, m_window);
}

void Tetrimino::moveRight(int increment){
    m_pos.x += increment;
    update(m_pos, m_window);
}

void Tetrimino::moveLeft(int increment){
    m_pos.x -= increment;
    update(m_pos, m_window);
}

Teewee::Teewee(Point a){
    bool valid = update(a, m_window);
    while (!valid) {
        int x = (std::rand() % 10) * STEP;
        valid = update(Point{x, a.y}, m_window);
    }
}

bool Teewee::update(Point const& a, Point const& dim){
    bool isUpdated = false;
    m_pos.x = a.x;
    m_pos.y = a.y;
  
    Point un = Point{m_pos.x, m_pos.y + STEP};
    Point deux = Point{m_pos.x,  m_pos.y + STEP * 2};
    Point trois = Point{m_pos.x + STEP, m_pos.y + STEP};

    if (lower(m_pos, dim) && lower(un, dim) && lower(deux, dim) && lower(trois, dim)) {
        m_piece[0] = m_pos;
        m_piece[1] = un;
        m_piece[2] = deux;
        m_piece[3] = trois;
        isUpdated = true;
    }
  
    return isUpdated;
}

Smashboy::Smashboy(Point a){
    bool valid = update(a, m_window);
    while (!valid) {
        int x = (std::rand() % 10) * STEP;
        valid = update(Point{x, a.y}, m_window);
    }
}

bool Smashboy::update(Point const& a, Point const& dim){
    bool isUpdated = false;
    m_pos.x = a.x;
    m_pos.y = a.y;
    Point un = Point{m_pos.x, m_pos.y + STEP};
    Point deux = Point{m_pos.x + STEP,  m_pos.y};
    Point trois = Point{m_pos.x + STEP, m_pos.y + STEP};

    if (lower(m_pos, dim) && lower(un, dim) && lower(deux, dim) && lower(trois, dim)) {
        m_piece[0] = m_pos;
        m_piece[1] = un;
        m_piece[2] = deux;
        m_piece[3] = trois;
        isUpdated = true;
    }
    return isUpdated;
}

// I
Hero::Hero(Point a){
    bool valid = update(a, m_window);
    while (!valid) {
        int x = (std::rand() % 10) * STEP;
        valid = update(Point{x, a.y}, m_window);
    }
}

bool Hero::update(Point const& a, Point const& dim){
    bool isUpdated = false;
    m_pos.x = a.x;
    m_pos.y = a.y;
    Point un = Point{m_pos.x, m_pos.y + STEP};
    Point deux = Point{m_pos.x,  m_pos.y + STEP*2};
    Point trois = Point{m_pos.x, m_pos.y + STEP*3};

    if (lower(m_pos, dim) && lower(un, dim) && lower(deux, dim) && lower(trois, dim)) {
        m_piece[0] = m_pos;
        m_piece[1] = un;
        m_piece[2] = deux;
        m_piece[3] = trois;
        isUpdated = true;
    }
    return isUpdated;
}

// S
RhodeIsland::RhodeIsland(Point a){
    bool valid = update(a, m_window);
    while (!valid) {
        int x = (std::rand() % 10) * STEP;
        valid = update(Point{x, a.y}, m_window);
    }
}

bool RhodeIsland::update(Point const& a, Point const& dim){
    bool isUpdated = false;
    m_pos.x = a.x;
    m_pos.y = a.y;
    Point un = Point{m_pos.x - STEP, m_pos.y};
    Point deux = Point{m_pos.x - STEP,  m_pos.y + STEP};
    Point trois = Point{m_pos.x - STEP*2, m_pos.y + STEP};

    if (lower(m_pos, dim) && lower(un, dim) && lower(deux, dim) && lower(trois, dim)) {
        m_piece[0] = m_pos;
        m_piece[1] = un;
        m_piece[2] = deux;
        m_piece[3] = trois;
        isUpdated = true;
    }
    return isUpdated;
}

// Z
Cleveland::Cleveland(Point a){
    bool valid = update(a, m_window);
    while (!valid) {
        int x = (std::rand() % 10) * STEP;
        valid = update(Point{x, a.y}, m_window);
    }
}

bool Cleveland::update(Point const& a, Point const& dim){
    bool isUpdated = false;
    m_pos.x = a.x;
    m_pos.y = a.y;
    Point un = Point{m_pos.x + STEP, m_pos.y};
    Point deux = Point{m_pos.x + STEP,  m_pos.y + STEP};
    Point trois = Point{m_pos.x + STEP*2, m_pos.y + STEP};

    if (lower(m_pos, dim) && lower(un, dim) && lower(deux, dim) && lower(trois, dim)) {
        m_piece[0] = m_pos;
        m_piece[1] = un;
        m_piece[2] = deux;
        m_piece[3] = trois;
        isUpdated = true;
    }
    return isUpdated;
}

// L
OrangeRicky::OrangeRicky(Point a){
    bool valid = update(a, m_window);
    while (!valid) {
        int x = (std::rand() % 10) * STEP;
        valid = update(Point{x, a.y}, m_window);
    }
}

bool OrangeRicky::update(Point const& a, Point const& dim){
    bool isUpdated = false;
    m_pos.x = a.x;
    m_pos.y = a.y;
    Point un = Point{m_pos.x, m_pos.y + STEP};
    Point deux = Point{m_pos.x,  m_pos.y + STEP*2};
    Point trois = Point{m_pos.x + STEP, m_pos.y + STEP*2};

    if (lower(m_pos, dim) && lower(un, dim) && lower(deux, dim) && lower(trois, dim)) {
        m_piece[0] = m_pos;
        m_piece[1] = un;
        m_piece[2] = deux;
        m_piece[3] = trois;
        isUpdated = true;
    }
    return isUpdated;
}

// Reverse L
BlueRicky::BlueRicky(Point a){
    bool valid = update(a, m_window);
    while (!valid) {
        int x = (std::rand() % 10) * STEP;
        valid = update(Point{x, a.y}, m_window);
    }
}

bool BlueRicky::update(Point const& a, Point const& dim){
    bool isUpdated = false;
    m_pos.x = a.x;
    m_pos.y = a.y;
    Point un = Point{m_pos.x, m_pos.y + STEP};
    Point deux = Point{m_pos.x,  m_pos.y + STEP*2};
    Point trois = Point{m_pos.x - STEP, m_pos.y + STEP*2};

    if (lower(m_pos, dim) && lower(un, dim) && lower(deux, dim) && lower(trois, dim)) {
        m_piece[0] = m_pos;
        m_piece[1] = un;
        m_piece[2] = deux;
        m_piece[3] = trois;
        isUpdated = true;
    }
    return isUpdated;
}