#include "encoder.h"

#include <stack>

Encoder::Encoder(int numStates, std::vector<int> g) : t(numStates, g) {
	this->stateArray = 0;
	this->stateSequence.resize((1 << numStates), std::vector<Node>{Node{-1, 0, -1}});
	for (int i = 1; i < (1 << numStates); i++) {
		this->stateSequence[i][0].cost = 1e7; // infinity
	}
}

int Encoder::encode(int input) {
	std::vector<Edge> edges = this->t.getTransitions(this->stateArray);
	this->stateArray = edges[input].end;
	return edges[input].output;
}

void Encoder::decode(int output) {
	std::vector<Node> nextStates(this->stateSequence.size(), Node{-1, (int)1e8, -1});
	for (int i = 0; i < this->stateSequence.size(); i++) {
		std::vector<Edge> edges = this->t.getTransitions(i);
		for (const auto &e : edges) {
			int cost = this->stateSequence[i].back().cost;
			cost += this->t.getNumberOfOnes(output ^ e.output);

			if (cost < nextStates[e.end].cost) {
				nextStates[e.end] = Node{i, cost, e.input};
			}
		}
	}

	for (int i = 0; i < this->stateSequence.size(); i++) {
		this->stateSequence[i].push_back(nextStates[i]);
	}
}

std::vector<int> Encoder::getSequence() {
	int minState = 0;
	for (int i = 0; i < this->stateSequence.size(); i++) {
		if (this->stateSequence[i].back().cost < this->stateSequence[minState].back().cost) {
			minState = i;
		}
	}

	std::stack<int> s;
	int currState = minState;
	for (int i = this->stateSequence[0].size() - 1; i > 0; i--) {
		s.push(this->stateSequence[currState][i].input);
		currState = this->stateSequence[currState][i].parent;
	}

	std::vector<int> sequence;
	while (!s.empty()) {
		sequence.push_back(s.top());
		s.pop();
	}
	return sequence;
}

