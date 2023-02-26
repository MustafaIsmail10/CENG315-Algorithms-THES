#include "the6.h"

/*
    in the6.h "struct Pipeline" is defined as below:

    struct Pipeline {
        int id;                     // pipeline id
        int end1;                   // id of the building-1
        int end2;                   // id of the building-2
        int cost_of_consumption;    // amount/cost of consumption for pipeline
    };

*/

// getting minimum
int getMin(Pipeline *usedPipes[], bool q[], int num_of_buildings)
{
    int i = 0;
    int min = 0;
    for (i = 0; i < num_of_buildings; i++)
    {
        if (q[i])
        {
            min = i;
            break;
        }
    }

    for (i = i; i < num_of_buildings; i++)
    {
        if (q[i] && usedPipes[i]->cost_of_consumption < usedPipes[min]->cost_of_consumption)
        {
            min = i;
        }
    }
    return min;
}

vector<int> plan_min_cost_pipeline_usage(vector<Pipeline *> pipelines, int num_of_buildings)
{

    vector<int> solution;
    vector<Pipeline *> adjList[num_of_buildings];
    Pipeline *usedPipes[num_of_buildings];
    bool q[num_of_buildings];
    for (int i = 0; i < num_of_buildings; i++)
    {
        q[i] = 1;
        usedPipes[i] = nullptr;
    }

    for (int i = 0; i < pipelines.size(); i++)
    {
        // Turn on all the  furnace rooms of all buildings
        if (pipelines[i]->end1 == pipelines[i]->end2)
        {
            if (!usedPipes[pipelines[i]->end1])
            {
                usedPipes[pipelines[i]->end1] = pipelines[i];
            }
            else
            {
                if (usedPipes[pipelines[i]->end1]->cost_of_consumption > pipelines[i]->cost_of_consumption)
                {
                    usedPipes[pipelines[i]->end1] = pipelines[i];
                }
            }
        }
        else // Building adjList
        {
            adjList[pipelines[i]->end1].push_back(pipelines[i]);
            adjList[pipelines[i]->end2].push_back(pipelines[i]);
        }
    }

    for (int i = 0; i < num_of_buildings; i++)
    {
        int min = getMin(usedPipes, q, num_of_buildings);
        q[min] = false;
        for (auto adj : adjList[min])
        {
            if (adj->end1 != min)
            {
                if (q[adj->end1] && usedPipes[adj->end1]->cost_of_consumption > adj->cost_of_consumption)
                {
                    usedPipes[adj->end1] = adj;
                }
            }
            else
            {
                if (q[adj->end2] && usedPipes[adj->end2]->cost_of_consumption > adj->cost_of_consumption)
                {
                    usedPipes[adj->end2] = adj;
                }
            }
        }
        solution.push_back(usedPipes[min]->id);
    }

    return solution; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}

//**************************************************************************************
//*****************************************************************************************

Pipeline *MaxToF(int num, int building, vector<Pipeline *> adjList[], Pipeline *f[])
{
    // visited[building] = true;

    // if (f[building])
    //     return f[building];

    // for (auto r : adjList[building])
    // {
    //     int id = r->end1 == building ? r->end2 : r->end1;
    //     if (!visited[id])
    //     {
    //         Pipeline *ans = MaxToF(visited, id, adjList, f);
    //         if (ans)
    //         {
    //             Pipeline *max = r->cost_of_consumption > ans->cost_of_consumption ? r : ans;
    //             return max;
    //         }
    //     }
    // }

    // return nullptr;
    struct instance
    {
        bool isChildProcess;
        int id;
        Pipeline *r;
    };

    if (f[building])
        return f[building];
    bool visited[num];
    for (int i = 0; i < num; i++)
    {
        visited[i] = false;
    }

    stack<instance> m;
    instance root;
    root.id = building;
    root.r = nullptr;
    root.isChildProcess = false;
    m.push(root);
    Pipeline *max = nullptr;
    while (!m.empty())
    {
        instance curr = m.top();
        visited[curr.id] = true;

        if (curr.isChildProcess)
        {
            if (curr.r && max)
            {
                max = curr.r->cost_of_consumption > max->cost_of_consumption ? curr.r : max;
            }
            m.pop();
            continue;
        }
        m.pop();

        if (f[curr.id])
        {
            max = curr.r;
            break;
        }

        curr.isChildProcess = true;
        m.push(curr);

        for (auto r : adjList[curr.id])
        {
            int id = r->end1 == curr.id ? r->end2 : r->end1;
            if (!visited[id])
            {
                instance n;
                n.id = id;
                n.isChildProcess = false;
                n.r = r;
                m.push(n);
            }
        }
    }
    while (!m.empty())
    {
        instance curr = m.top();
        m.pop();
        if (curr.isChildProcess)
        {
            if (curr.r && max)
            {
                max = curr.r->cost_of_consumption > max->cost_of_consumption ? curr.r : max;
            }
        }
    }
    return max;
}

vector<int> optimize_plan(vector<Pipeline *> current_solution, Pipeline *new_pipeline)
{

    vector<int> solution;
    int num = current_solution.size();
    vector<Pipeline *> adjList[num];
    Pipeline *f[num];

    for (int i = 0; i < num; i++)
    {
        f[i] = nullptr;
    }
    // building adjecency list
    for (int i = 0; i < num; i++)
    {
        if (current_solution[i]->end1 == current_solution[i]->end2)
        {
            f[current_solution[i]->end1] = current_solution[i];
        }
        else // Building adjList
        {
            adjList[current_solution[i]->end1].push_back(current_solution[i]);
            adjList[current_solution[i]->end2].push_back(current_solution[i]);
        }
    }

    if (new_pipeline->end1 == new_pipeline->end2)
    {
        int id = new_pipeline->end1;
        if (f[id])
        {
            for (int i = 0; i < num; i++)
            {
                if (current_solution[i] == f[id])
                {
                    Pipeline *smaller = f[id]->cost_of_consumption > new_pipeline->cost_of_consumption ? new_pipeline : f[id];
                    solution.push_back(smaller->id);
                }
                else
                {
                    solution.push_back(current_solution[i]->id);
                }
            }
        }
        else
        {

            bool visited[num];
            for (int i = 0; i < num; i++)
            {
                visited[i] = false;
            }

            Pipeline *maxPipe = MaxToF(num, id, adjList, f);
            for (int i = 0; i < num; i++)
            {
                if (current_solution[i]->id == maxPipe->id)
                {
                    Pipeline *smaller = current_solution[i]->cost_of_consumption > new_pipeline->cost_of_consumption ? new_pipeline : current_solution[i];
                    solution.push_back(smaller->id);
                }
                else
                {
                    solution.push_back(current_solution[i]->id);
                }
            }
        }
    }
    else
    {

        int b1 = new_pipeline->end1;
        bool visited[num];
        for (int i = 0; i < num; i++)
        {
            visited[i] = false;
        }
        Pipeline *maxPipe1 = MaxToF(num, b1, adjList, f);

        int b2 = new_pipeline->end2;
        for (int i = 0; i < num; i++)
        {
            visited[i] = false;
        }
        Pipeline *maxPipe2 = MaxToF(num, b2, adjList, f);

        Pipeline *maxPipe = maxPipe1->cost_of_consumption > maxPipe2->cost_of_consumption ? maxPipe1 : maxPipe2;

        for (int i = 0; i < num; i++)
        {
            if (current_solution[i]->id == maxPipe->id)
            {
                Pipeline *smaller = current_solution[i]->cost_of_consumption > new_pipeline->cost_of_consumption ? new_pipeline : current_solution[i];
                solution.push_back(smaller->id);
            }
            else
            {
                solution.push_back(current_solution[i]->id);
            }
        }
    }

    return solution; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}
