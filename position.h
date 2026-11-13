#ifndef POSITION_H
#define POSITION_H

struct Position
{
    int gr;
    int gc;

    Position(int r, int c) : gr(r), gc(c) {}

    bool operator==(const Position &other) const
    {
        return gr == other.gr && gc == other.gc;
    }

    bool operator!=(const Position &other) const
    {
        return !(*this == other);
    }

    int manhattanDistance(const Position &other) const
    {
        int dr = gr - other.gr;
        int dc = gc - other.gc;
        if (dr < 0)
            dr = -dr;
        if (dc < 0)
            dc = -dc;
        return dr + dc;
    }
};

#endif
