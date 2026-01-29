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
    std::vector<Point> shape = current().getShape();
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
    //int x = (std::rand() % 10) * STEP;
    int x = 7 * STEP;
    switch (type){
        case T:
            return std::make_unique<Teewee>(Point{x, 0});
        case O:
            return std::make_unique<Smashboy>(Point{x, 0});
        case L:
            std::cout << "Instance OrangeRicky\n";
            return std::make_unique<OrangeRicky>(Point{x, 0});
        case J:
            return std::make_unique<BlueRicky>(Point{x, 0});
        case Z:
            return std::make_unique<Cleveland>(Point{x, 0});
        case S:
            return std::make_unique<RhodeIsland>(Point{x, 0});
        case I:
            return std::make_unique<Hero>(Point{x, 0});
    }
}

// Tetrimino
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
    if (a.x < b.x && a.y < b.y && a.x >= 0 && a.y >= 0){
        islower = true;
    }
    return islower;
}

std::vector<Point> Tetrimino::getShape()
{
    return m_piece;
}

void Tetrimino::moveDown(std::vector<std::vector<bool>>& grid){
    for (size_t i = 0; i < m_piece.size(); ++i){
        m_piece[i].y += STEP;
    }
}

void Tetrimino::moveRight(std::vector<std::vector<bool>>& grid){
    for (size_t i = 0; i < m_piece.size(); ++i){
        m_piece[i].x += STEP;
    }
}

void Tetrimino::moveLeft(std::vector<std::vector<bool>>& grid){
    for (size_t i = 0; i < m_piece.size(); ++i){
        m_piece[i].x -= STEP;
    }
    
}

Teewee::Teewee(Point a){
    bool valid = create(a, m_window);
    while (!valid) {
        int x = (std::rand() % 10) * STEP;
        valid = create(Point{x, a.y}, m_window);
    }
}
// T
bool Teewee::create(Point const& a, Point const& dim){
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

bool Teewee::rotateRight(std::vector<std::vector<bool>>& grid) {
    std::vector<Point> v ;
    switch (m_angle){
    case 0:
        //  angle => 90
        v.push_back(Point{m_piece[0].x + STEP, m_piece[0].y + STEP});
        v.push_back(Point{m_piece[1].x, m_piece[1].y});
        v.push_back(Point{m_piece[2].x - STEP, m_piece[2].y - STEP});
        v.push_back(Point{m_piece[3].x - STEP, m_piece[3].y + STEP});
        break;
    case 90:
        // angle => 180
        v.push_back(Point{m_piece[0].x - STEP, m_piece[0].y + STEP});
        v.push_back(Point{m_piece[1].x, m_piece[1].y});
        v.push_back(Point{m_piece[2].x + STEP, m_piece[2].y - STEP});
        v.push_back(Point{m_piece[3].x - STEP, m_piece[3].y - STEP});
        break;
    case 180:
        // angle => 270
        v.push_back(Point{m_piece[0].x - STEP, m_piece[0].y - STEP});
        v.push_back(Point{m_piece[1].x, m_piece[1].y});
        v.push_back(Point{m_piece[2].x + STEP, m_piece[2].y + STEP});
        v.push_back(Point{m_piece[3].x + STEP, m_piece[3].y - STEP});
        break;
    case 270:
        // angle => 0
        v.push_back(Point{m_piece[0].x + STEP, m_piece[0].y - STEP});
        v.push_back(Point{m_piece[1].x, m_piece[1].y});
        v.push_back(Point{m_piece[2].x - STEP, m_piece[2].y + STEP});
        v.push_back(Point{m_piece[3].x + STEP, m_piece[3].y + STEP});
        break;
    default:
        m_angle = 0;
    }
  
    if (v.size() == 4 && lower(v[0], m_window) && lower(v[1], m_window) && lower(v[2], m_window) && lower(v[3], m_window)){
        bool rotated = true;
        for (size_t i = 0; i < v.size(); ++i){
            if (!grid[v[i].x / STEP][v[i].y / STEP]) {
                rotated = false;
                break;
            }
        }
        if (rotated) {
            for (size_t i = 0; i < m_piece.size(); ++i){
                m_piece[i] = v[i];
            }
            m_angle = (m_angle + 90) % 360;
            return true;
        }
    }
    return false;
}

bool Teewee::rotateLeft(std::vector<std::vector<bool>>& grid) {
    std::vector<Point> v ;
    switch (m_angle){
    case 0:
        //  angle => 270
        v.push_back(Point{m_piece[0].x - STEP, m_piece[0].y + STEP});
        v.push_back(Point{m_piece[1].x, m_piece[1].y});
        v.push_back(Point{m_piece[2].x + STEP, m_piece[2].y - STEP});
        v.push_back( Point{m_piece[3].x - STEP, m_piece[3].y - STEP});
        break;
    case 270:
        // angle => 180
        v.push_back(Point{m_piece[0].x + STEP, m_piece[0].y + STEP});
        v.push_back(Point{m_piece[1].x, m_piece[1].y});
        v.push_back(Point{m_piece[2].x - STEP, m_piece[2].y - STEP});
        v.push_back(Point{m_piece[3].x - STEP, m_piece[3].y + STEP});
        break;
    case 180:
        // angle => 90
        v.push_back(Point{m_piece[0].x + STEP, m_piece[0].y - STEP});
        v.push_back(Point{m_piece[1].x, m_piece[1].y});
        v.push_back(Point{m_piece[2].x - STEP, m_piece[2].y + STEP});
        v.push_back(Point{m_piece[3].x + STEP, m_piece[3].y + STEP});
        break;
    case 90:
        // angle => 0
        v.push_back(Point{m_piece[0].x - STEP, m_piece[0].y - STEP});
        v.push_back(Point{m_piece[1].x, m_piece[1].y});
        v.push_back(Point{m_piece[2].x + STEP, m_piece[2].y + STEP});
        v.push_back(Point{m_piece[3].x + STEP, m_piece[3].y - STEP});
        break;
    default:
        m_angle = 0;
    }
    if (v.size() == 4 && lower(v[0], m_window) && lower(v[1], m_window) && lower(v[2], m_window) && lower(v[3], m_window)){
        bool rotated = true;
        for (size_t i = 0; i < v.size(); ++i){
            if (!grid[v[i].x / STEP][v[i].y / STEP]) {
                rotated = false;
                break;
            }
        }
        if (rotated) {
            for (size_t i = 0; i < m_piece.size(); ++i){
                m_piece[i] = v[i];
            }
            m_angle = (m_angle + 270) % 360;
            return true;
        }
    }
    return false;
}

Smashboy::Smashboy(Point a){
    bool valid = create(a, m_window);
    while (!valid) {
        int x = (std::rand() % 10) * STEP;
        valid = create(Point{x, a.y}, m_window);
    }
}

bool Smashboy::create(Point const& a, Point const& dim){
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

bool Smashboy::rotateRight(std::vector<std::vector<bool>>& grid) {
    return true;
}

bool Smashboy::rotateLeft(std::vector<std::vector<bool>>& grid) {
    return true;
}

// I
Hero::Hero(Point a){
    bool valid = create(a, m_window);
    while (!valid) {
        int x = (std::rand() % 10) * STEP;
        valid = create(Point{x, a.y}, m_window);
    }
}

bool Hero::create(Point const& a, Point const& dim){
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

bool Hero::rotateRight(std::vector<std::vector<bool>>& grid) {
    std::vector<Point> v ;
    switch (m_angle){
    case 0:
        //  angle => 90
        v.push_back(Point{m_piece[0].x + STEP*2, m_piece[0].y + STEP});
        v.push_back(Point{m_piece[1].x + STEP, m_piece[1].y});
        v.push_back(Point{m_piece[2].x, m_piece[2].y - STEP});
        v.push_back( Point{m_piece[3].x - STEP, m_piece[3].y - STEP*2});
        break;
    case 90:
        // angle => 0
        v.push_back(Point{m_piece[0].x - STEP*2, m_piece[0].y - STEP});
        v.push_back(Point{m_piece[1].x - STEP, m_piece[1].y});
        v.push_back(Point{m_piece[2].x, m_piece[2].y + STEP});
        v.push_back(Point{m_piece[3].x + STEP, m_piece[3].y + STEP*2});
        break;
    default:
        m_angle = 0;
    }
    if (v.size() && lower(v[0], m_window) && lower(v[1], m_window) && lower(v[2], m_window) && lower(v[3], m_window)){
        bool rotated = true;
        for (size_t i = 0; i < v.size(); ++i){
            if (!grid[v[i].x / STEP][v[i].y / STEP]) {
                rotated = false;
                break;
            }
        }
        if (rotated) {
            for (size_t i = 0; i < m_piece.size(); ++i){
                m_piece[i] = v[i];
            }
            m_angle = (m_angle + 90) % 180;
            return true;
        }
    }
   
    return false;
}

bool Hero::rotateLeft(std::vector<std::vector<bool>>& grid) {
    return rotateRight(grid);
}


RhodeIsland::RhodeIsland(Point a){
    bool valid = create(a, m_window);
    while (!valid) {
        int x = (std::rand() % 10) * STEP;
        valid = create(Point{x, a.y}, m_window);
    }
}
// S
bool RhodeIsland::create(Point const& a, Point const& dim){
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

bool RhodeIsland::rotateRight(std::vector<std::vector<bool>>& grid) {
    std::vector<Point> v ;
    switch (m_angle){
    case 0:
        //  angle => 90
        v.push_back(Point{m_piece[0].x - STEP, m_piece[0].y + STEP*2});
        v.push_back({m_piece[1].x, m_piece[1].y + STEP});
        v.push_back(Point{m_piece[2].x - STEP, m_piece[2].y});
        v.push_back( Point{m_piece[3].x, m_piece[3].y - STEP});
        break;
    case 90:
        // angle => 0
        // TODO
        v.push_back(Point{m_piece[0].x + STEP, m_piece[0].y - STEP*2});
        v.push_back(Point{m_piece[1].x, m_piece[1].y - STEP});
        v.push_back(Point{m_piece[2].x + STEP, m_piece[2].y});
        v.push_back(Point{m_piece[3].x, m_piece[3].y + STEP});
        break;
    default:
        m_angle = 0;
    }
    if (v.size() && lower(v[0], m_window) && lower(v[1], m_window) && lower(v[2], m_window) && lower(v[3], m_window)){
        bool rotated = true;
        for (size_t i = 0; i < v.size(); ++i){
            if (!grid[v[i].x / STEP][v[i].y / STEP]) {
                rotated = false;
                break;
            }
        }
        if (rotated) {
            for (size_t i = 0; i < m_piece.size(); ++i){
                m_piece[i] = v[i];
            }
            m_angle = (m_angle + 90) % 180;
            return true;
        }
    }

    return false;
}

bool RhodeIsland::rotateLeft(std::vector<std::vector<bool>>& grid) {
    return rotateRight(grid);
}

// Z
Cleveland::Cleveland(Point a){
    bool valid = create(a, m_window);
    while (!valid) {
        int x = (std::rand() % 10) * STEP;
        valid = create(Point{x, a.y}, m_window);
    }
}

bool Cleveland::create(Point const& a, Point const& dim){
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

bool Cleveland::rotateRight(std::vector<std::vector<bool>>& grid) {
    std::vector<Point> v ;
    switch (m_angle){
    case 0:
        //  angle => 90
        v.push_back(Point{m_piece[0].x + STEP, m_piece[0].y});
        v.push_back(Point{m_piece[1].x, m_piece[1].y + STEP});
        v.push_back(Point{m_piece[2].x - STEP, m_piece[2].y});
        v.push_back( Point{m_piece[3].x - STEP*2, m_piece[3].y + STEP});
        break;
    case 90:
        // angle => 0
        v.push_back(Point{m_piece[0].x - STEP, m_piece[0].y});
        v.push_back(Point{m_piece[1].x, m_piece[1].y - STEP});
        v.push_back(Point{m_piece[2].x + STEP, m_piece[2].y});
        v.push_back(Point{m_piece[3].x + STEP*2, m_piece[3].y - STEP});
        break;
    default:
       m_angle = 0;
    }
    if (lower(v[0], m_window) && lower(v[1], m_window) && lower(v[2], m_window) && lower(v[3], m_window)){
        bool rotated = true;
        for (size_t i = 0; i < v.size(); ++i){
            if (!grid[v[i].x / STEP][v[i].y / STEP]) {
                rotated = false;
                break;
            }
        }
        if (rotated) {
            for (size_t i = 0; i < m_piece.size(); ++i){
                m_piece[i] = v[i];
            }
            m_angle = (m_angle + 90) % 180;
            return true;
        }
    }

    return false;
}

bool Cleveland::rotateLeft(std::vector<std::vector<bool>>& grid) {
    return rotateRight(grid);
}

// L
OrangeRicky::OrangeRicky(Point a){
    bool valid = create(a, m_window);
    while (!valid) {
        int x = (std::rand() % 10) * STEP;
        valid = create(Point{x, a.y}, m_window);
    }
}
// L
bool OrangeRicky::create(Point const& a, Point const& dim){
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

bool OrangeRicky::rotateRight(std::vector<std::vector<bool>>& grid) {
    std::vector<Point> v ;
    switch (m_angle){
    case 0:
        //  angle => 90
        v.push_back(Point{m_piece[0].x + STEP*2, m_piece[0].y + STEP});
        v.push_back(Point{m_piece[1].x + STEP, m_piece[1].y});
        v.push_back(Point{m_piece[2].x, m_piece[2].y - STEP});
        v.push_back(Point{m_piece[3].x - STEP, m_piece[3].y});
        break;
    case 90:
        // angle => 180
        v.push_back(Point{m_piece[0].x - STEP, m_piece[0].y + STEP*2});
        v.push_back(Point{m_piece[1].x, m_piece[1].y + STEP});
        v.push_back(Point{m_piece[2].x + STEP, m_piece[2].y});
        v.push_back(Point{m_piece[3].x, m_piece[3].y - STEP});
        break;
    case 180:
        // angle => 270
        v.push_back(Point{m_piece[0].x - STEP*2, m_piece[0].y - STEP});
        v.push_back(Point{m_piece[1].x - STEP, m_piece[1].y});
        v.push_back(Point{m_piece[2].x, m_piece[2].y + STEP});
        v.push_back(Point{m_piece[3].x + STEP, m_piece[3].y});
        break;
    case 270:
        // angle => 0
        v.push_back(Point{m_piece[0].x + STEP, m_piece[0].y - STEP*2});
        v.push_back(Point{m_piece[1].x, m_piece[1].y - STEP});
        v.push_back(Point{m_piece[2].x - STEP, m_piece[2].y});
        v.push_back(Point{m_piece[3].x, m_piece[3].y + STEP});
        break;
    default:
        m_angle = 0;
    }
    if (v.size() && lower(v[0], m_window) && lower(v[1], m_window) && lower(v[2], m_window) && lower(v[3], m_window)){
        bool rotated = true;
        for (size_t i = 0; i < v.size(); ++i){
            if (!grid[v[i].x / STEP][v[i].y / STEP]) {
                rotated = false;
                break;
            }
        }
        if (rotated) {
            for (size_t i = 0; i < m_piece.size(); ++i){
                m_piece[i] = v[i];
            }
            m_angle = (m_angle + 90) % 360;
            return true;
        }
    }
    return false;
}

bool OrangeRicky::rotateLeft(std::vector<std::vector<bool>>& grid) {
    std::vector<Point> v ;
    switch (m_angle){
    case 0:
        //  angle => 270
        v.push_back(Point{m_piece[0].x - STEP, m_piece[0].y + STEP*2});
        v.push_back({m_piece[1].x, m_piece[1].y + STEP});
        v.push_back(Point{m_piece[2].x + STEP, m_piece[2].y});
        v.push_back( Point{m_piece[3].x, m_piece[3].y - STEP});
        break;
    case 270:
        // angle => 180
        v.push_back(Point{m_piece[0].x + STEP*2, m_piece[0].y + STEP});
        v.push_back(Point{m_piece[1].x + STEP, m_piece[1].y});
        v.push_back(Point{m_piece[2].x, m_piece[2].y - STEP});
        v.push_back(Point{m_piece[3].x - STEP, m_piece[3].y});
        break;
    case 180:
        // angle => 90
        v.push_back(Point{m_piece[0].x + STEP, m_piece[0].y - STEP*2});
        v.push_back(Point{m_piece[1].x, m_piece[1].y - STEP});
        v.push_back(Point{m_piece[2].x - STEP, m_piece[2].y});
        v.push_back(Point{m_piece[3].x, m_piece[3].y + STEP});
        break;
    case 90:
        // angle => 0
        v.push_back(Point{m_piece[0].x - STEP*2, m_piece[0].y - STEP});
        v.push_back(Point{m_piece[1].x - STEP, m_piece[1].y});
        v.push_back(Point{m_piece[2].x, m_piece[2].y + STEP});
        v.push_back(Point{m_piece[3].x + STEP, m_piece[3].y});
        break;
    default:
        m_angle = 0;
    }
    if (v.size() && lower(v[0], m_window) && lower(v[1], m_window) && lower(v[2], m_window) && lower(v[3], m_window)){
        bool rotated = true;
        for (size_t i = 0; i < v.size(); ++i){
            if (!grid[v[i].x / STEP][v[i].y / STEP]) {
                rotated = false;
                break;
            }
        }
        if (rotated) {
            for (size_t i = 0; i < m_piece.size(); ++i){
                m_piece[i] = v[i];
            }
            m_angle = (m_angle + 270) % 360;
            return true;
        }
    }
    return false;
}

// J
BlueRicky::BlueRicky(Point a){
    bool valid = create(a, m_window);
    while (!valid) {
        int x = (std::rand() % 10) * STEP;
        valid = create(Point{x, a.y}, m_window);
    }
}

bool BlueRicky::create(Point const& a, Point const& dim){
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

bool BlueRicky::rotateRight(std::vector<std::vector<bool>>& grid) {
    std::vector<Point> v ;
    switch (m_angle){
    case 0:
        //  angle => 90
        v.push_back(Point{m_piece[0].x + STEP, m_piece[0].y + STEP*2});
        v.push_back(Point{m_piece[1].x, m_piece[1].y + STEP});
        v.push_back(Point{m_piece[2].x - STEP, m_piece[2].y});
        v.push_back( Point{m_piece[3].x, m_piece[3].y - STEP});
        break;
    case 90:
        // angle => 180
        v.push_back(Point{m_piece[0].x - STEP, m_piece[0].y + STEP*2});
        v.push_back(Point{m_piece[1].x, m_piece[1].y + STEP});
        v.push_back(Point{m_piece[2].x + STEP, m_piece[2].y});
        v.push_back(Point{m_piece[3].x, m_piece[3].y - STEP});
        break;
    case 180:
        // angle => 270
        v.push_back(Point{m_piece[0].x - STEP*2, m_piece[0].y - STEP});
        v.push_back(Point{m_piece[1].x - STEP, m_piece[1].y});
        v.push_back(Point{m_piece[2].x, m_piece[2].y + STEP});
        v.push_back(Point{m_piece[3].x + STEP, m_piece[3].y});
        break;
    case 270:
        // angle => 0
        v.push_back(Point{m_piece[0].x + STEP, m_piece[0].y - STEP*2});
        v.push_back(Point{m_piece[1].x, m_piece[1].y - STEP});
        v.push_back(Point{m_piece[2].x - STEP, m_piece[2].y});
        v.push_back(Point{m_piece[3].x, m_piece[3].y + STEP});
        break;
    default:
        m_angle = 0;
    }
    if (v.size() && lower(v[0], m_window) && lower(v[1], m_window) && lower(v[2], m_window) && lower(v[3], m_window)){
        bool rotated = true;
        for (size_t i = 0; i < v.size(); ++i){
            if (!grid[v[i].x / STEP][v[i].y / STEP]) {
                rotated = false;
                break;
            }
        }
        if (rotated) {
            for (size_t i = 0; i < m_piece.size(); ++i){
                m_piece[i] = v[i];
            }
            m_angle = (m_angle + 90) % 360;
            return true;
        }
    }
  
    return false;
}


bool BlueRicky::rotateLeft(std::vector<std::vector<bool>>& grid) {
    bool rotated = true;
    std::vector<Point> v ;
    v.push_back(Point{m_piece[0].x - STEP*2, m_piece[0].y + STEP});
    v.push_back(Point{m_piece[1].x - STEP, m_piece[1].y});
    v.push_back(Point{m_piece[2].x, m_piece[2].y - STEP});
    v.push_back( Point{m_piece[3].x + STEP, m_piece[3].y});
    if (lower(v[0], m_window) && lower(v[1], m_window) && lower(v[2], m_window) && lower(v[3], m_window)){
        for (size_t i = 0; i < v.size(); ++i){
            if (!grid[v[i].x / STEP][v[i].y / STEP]) {
                rotated = false;
                break;
            }
        }
    }
    if (rotated) {
        for (size_t i = 0; i < m_piece.size(); ++i){
            m_piece[i] = v[i];
        }
    }
    return rotated;
}