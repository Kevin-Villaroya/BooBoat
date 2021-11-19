#include "BoatAi.h"
#include "Map/Wind/LocalWind.h"
#include <cmath>
#include <optional>
#include <functional>

namespace
{
	//Manhatan distance
	float heuristic(Point from, Point to)
	{
		//TODO : LA MAP LOOP SUR ELLE MEME
		return std::abs(from.x - to.x) + std::abs(from.y - to.y);
	}
}

void BoatAi::computePlan()
{
    if(!_knowledge.pos()) return;
    Point boat_pos = *_knowledge.pos();

	struct ParentData{ size_t index; Direction leading_action; };
	struct Node
    {
        Point pos;
        std::optional<ParentData> parent;
        float cost;
        float estimatedCost;
    };
    _plan.clear();

    std::vector<Node> frontier;
    std::vector<Node> visited;
    frontier.push_back({boat_pos, std::nullopt, 0, heuristic(boat_pos, _destination)});

    while(frontier.size() > 0)
    {
        visited.push_back(std::move(frontier.back()));
        frontier.pop_back();
        Node& current = visited.back();
        size_t current_index = visited.size() - 1;

        if(current.pos == _destination)
        {
            //plan found, build from current node
            std::optional<ParentData> parent = current.parent;
            while(parent)
            {
                _plan.push_back(parent->leading_action);
                parent = visited[parent->index].parent;
            }

            return;
        }

        auto directions = availableDirections(current.pos);
        for(Direction direction : directions)
        {
            Point new_pos = current.pos + direction;
            float c = current.cost + moveCost(current.pos, direction);
            float h = heuristic(new_pos, _destination);
            frontier.push_back({new_pos, ParentData{current_index, direction}, c, c+h});
        }

        std::sort(frontier.begin(), frontier.end(), [](const Node& a, const Node& b) { return a.estimatedCost > b.estimatedCost; });
    }
}

std::vector<Direction> BoatAi::availableDirections(Point pos) const
{
	Direction possibilities[] = {Direction::North, Direction::East, Direction::South, Direction::West};
	std::vector<Direction> result;
	for(Direction direction : possibilities)
	{
		//TODO : check for land
		result.push_back(direction);
	}

	return result;
}

float BoatAi::moveCost(Point from, Direction dir) const
{
	return moveTurnsInWind(dir, _knowledge.windDirectionAt(from));
}

void BoatAi::addPerception(Knowledge perception)
{
	_knowledge.merge(perception);
	//TODO vérifier si le plan est toujours valide (et flush en cas de problème)
}

Direction BoatAi::nextDirection()
{
	if(_plan.empty())
	{
		computePlan();
	}

	Direction dir = _plan.back();
	_plan.pop_back();
	return dir;
}
