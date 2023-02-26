#include "the5.h"

/*
    in the5.h "struct Room" is defined as below:

    struct Room {
        int id;
        char content;
        vector<Room*> neighbors;
    };

*/

// bool isVisited(vector<int> visited, int id)
// {
//     for (auto x : visited)
//     {
//         if (x == id)
//             return true;
//     }
//     return false;
// }

bool tFinder(bool *visited, Room *room, vector<int> &path)
{
    visited[room->id] = true;
    path.push_back(room->id);
    if (room->content == '*')
        return 1;
    for (auto r : room->neighbors)
    {
        if (!visited[r->id])
        {
            bool ans = tFinder(visited, r, path);
            path.push_back(room->id);
            if (ans)
                return true;
        }
    }

    return false;
}

vector<int> maze_trace(vector<Room *> maze)
{

    vector<int> path;

    // your code here
    bool visited[maze.size()] = {false};
    tFinder(visited, maze[0], path);

    return path; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}
