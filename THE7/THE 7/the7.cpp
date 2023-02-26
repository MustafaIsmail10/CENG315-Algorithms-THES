#include "the7.h"
using namespace std;
// Implement your solution after this line

int getMin(int lst[], int q[], int n)
{
    int i = 0;
    int min = 0;
    for (i = 0; i < n; i++)
    {
        if (q[i])
        {
            min = i;
            break;
        }
    }

    for (i = i; i < n; i++)
    {
        if (q[i] && lst[i] < lst[min])
        {
            min = i;
        }
    }
    return min;
}

vector<Road> minPath(vector<Road> adjList[], int s, int d, int n)
{
    vector<Road> parent;
    int q[n];
    int dis[n];

    for (int i = 0; i < n; i++)
    {
        pair<int, int> x(i, i);
        parent.push_back(Road(x, 0));
        dis[i] = INT_MAX;
        q[i] = 1;
    }

    dis[s] = 0;

    for (int i = 0; i < n; i++)
    {
        int min = getMin(dis, q, n);
        q[min] = 0;
        for (auto x : adjList[min])
        {
            if (x.buildings.first == min)
            {
                if (x.time + dis[min] < dis[x.buildings.second])
                {
                    dis[x.buildings.second] = x.time + dis[min];
                    parent[x.buildings.second] = x;
                }
            }
            else
            {
                if (x.time + dis[min] < dis[x.buildings.first])
                {
                    dis[x.buildings.first] = x.time + dis[min];
                    parent[x.buildings.first] = x;
                }
            }
        }
    }
    vector<Road> path;
    int curr = d;
    while (curr != s)
    {
        path.push_back(parent[curr]);
        if (parent[curr].buildings.first == curr)
        {
            curr = parent[curr].buildings.second;
        }
        else
        {
            curr = parent[curr].buildings.first;
        }
    }

    return path;
}

int getTime(vector<Road> path)
{
    int time = 0;
    for (auto r : path)
    {
        time += r.time;
    }
    return time;
}

void CanCatch(int n, std::vector<Road> roads, int s, int d, int x, int y, int l, int printPath)
{
    // You can change these variables. These are here for demo only.
    vector<Road> adjList[n];
    vector<int> path;
    path.push_back(s);
    for (auto r : roads)
    {
        adjList[r.buildings.first].push_back(r);
        adjList[r.buildings.second].push_back(r);
    }

    vector<Road> sd = minPath(adjList, s, d, n);
    vector<Road> sx = minPath(adjList, s, x, n);
    vector<Road> sy = minPath(adjList, s, y, n);
    vector<Road> xd = minPath(adjList, x, d, n);
    vector<Road> yd = minPath(adjList, y, d, n);
    vector<Road> xy = minPath(adjList, x, y, n);

    int sdt = getTime(sd);
    int sxt = getTime(sx);
    int syt = getTime(sy);
    int xdt = getTime(xd);
    int ydt = getTime(yd);
    int xyt = getTime(xy);

    int sxyd = sxt + xyt + ydt;
    int syxd = syt + xyt + xdt;
    int sxd = sxt + xdt;
    int syd = syt + ydt;

    if (sxyd <= syxd && sxyd <= l)
    {
        cout << "YES BOTH " << sxyd << "MINUTES" << endl;

        if (printPath)
        {
            int curr = s;
            for (int i = sx.size() - 1; i >= 0; i--)
            {
                if (sx[i].buildings.first == curr)
                {
                    curr = sx[i].buildings.second;
                }
                else
                {
                    curr = sx[i].buildings.first;
                }
                path.push_back(curr);
            }
            for (int i = xy.size() - 1; i >= 0; i--)
            {
                if (xy[i].buildings.first == curr)
                {
                    curr = xy[i].buildings.second;
                }
                else
                {
                    curr = xy[i].buildings.first;
                }
                path.push_back(curr);
            }
            for (int i = yd.size() - 1; i >= 0; i--)
            {
                if (yd[i].buildings.first == curr)
                {
                    curr = yd[i].buildings.second;
                }
                else
                {
                    curr = yd[i].buildings.first;
                }
                path.push_back(curr);
            }
            PrintRange(path.begin(), path.end());
        }
    }
    else if (syxd <= l)
    {
        cout << "YES BOTH " << syxd << "MINUTES" << endl;

        if (printPath)
        {
            int curr = s;
            for (int i = sy.size() - 1; i >= 0; i--)
            {
                if (sy[i].buildings.first == curr)
                {
                    curr = sy[i].buildings.second;
                }
                else
                {
                    curr = sy[i].buildings.first;
                }
                path.push_back(curr);
            }
            int xysize = xy.size();
            for (int i = 0; i < xysize; i++)
            {
                if (xy[i].buildings.first == curr)
                {
                    curr = xy[i].buildings.second;
                }
                else
                {
                    curr = xy[i].buildings.first;
                }
                path.push_back(curr);
            }
            for (int i = xd.size() - 1; i >= 0; i--)
            {
                if (xd[i].buildings.first == curr)
                {
                    curr = xd[i].buildings.second;
                }
                else
                {
                    curr = xd[i].buildings.first;
                }
                path.push_back(curr);
            }
            PrintRange(path.begin(), path.end());
        }
    }
    else if (sxd <= syd && sxd < l)
    {
        cout << "YES PRINTER " << sxd << "MINUTES" << endl;
        if (printPath)
        {
            int curr = s;
            for (int i = sx.size() - 1; i >= 0; i--)
            {
                if (sx[i].buildings.first == curr)
                {
                    curr = sx[i].buildings.second;
                }
                else
                {
                    curr = sx[i].buildings.first;
                }
                path.push_back(curr);
            }
            for (int i = xd.size() - 1; i >= 0; i--)
            {
                if (xd[i].buildings.first == curr)
                {
                    curr = xd[i].buildings.second;
                }
                else
                {
                    curr = xd[i].buildings.first;
                }
                path.push_back(curr);
            }
            PrintRange(path.begin(), path.end());
        }
    }
    else if (syd <= l)
    {
        cout << "YES DORM " << syd << "MINUTES" << endl;
        if (printPath)
        {
            int curr = s;
            for (int i = sy.size() - 1; i >= 0; i--)
            {
                if (sy[i].buildings.first == curr)
                {
                    curr = sy[i].buildings.second;
                }
                else
                {
                    curr = sy[i].buildings.first;
                }
                path.push_back(curr);
            }
            for (int i = yd.size() - 1; i >= 0; i--)
            {
                if (yd[i].buildings.first == curr)
                {
                    curr = yd[i].buildings.second;
                }
                else
                {
                    curr = yd[i].buildings.first;
                }
                path.push_back(curr);
            }
            PrintRange(path.begin(), path.end());
        }
    }
    else if (sdt <= l)
    {
        cout << "YES DIRECTLY " << sdt << "MINUTES" << endl;
        if (printPath)
        {
            int curr = s;
            for (int i = sd.size() - 1; i >= 0; i--)
            {
                if (sd[i].buildings.first == curr)
                {
                    curr = sd[i].buildings.second;
                }
                else
                {
                    curr = sd[i].buildings.first;
                }
                path.push_back(curr);
            }
            PrintRange(path.begin(), path.end());
        }
    }
    else
    {
        cout << "IMPOSSIBLE" << endl;
    }

    // You can use the PrintRange function to print the path.
    // It helps you print elements of containers with iterators (e.g., std::vector).
    // Usage: PrintRange(path.begin(), path.end());
}

// int main()
// {
//     vector<Road> roads;

//     pair<int, int> x(0, 1);
//     roads.push_back(Road(x, 35));

//     x.first = 0;
//     x.second = 2;
//     roads.push_back(Road(x, 12));

//     x.first = 1;
//     x.second = 3;
//     roads.push_back(Road(x, 16));

//     x.first = 2;
//     x.second = 3;
//     roads.push_back(Road(x, 19));

//     x.first = 3;
//     x.second = 4;
//     roads.push_back(Road(x, 18));

//     CanCatch(5, roads, 0, 4, 1, 2, 65, 1);

//     return 0;
// }