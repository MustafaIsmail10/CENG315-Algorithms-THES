#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct Pipeline
{
    int id;                  // pipeline id
    int end1;                // id of the building-1
    int end2;                // id of the building-2
    int cost_of_consumption; // amount/cost of consumption for pipeline
};

vector<int> plan_min_cost_pipeline_usage(vector<Pipeline *> pipelines, int num_of_buildings);
vector<int> optimize_plan(vector<Pipeline *> current_solution, Pipeline *new_pipeline);