#include "convolutional.h"

#include <stack>
#include <cmath>

Convolutional::Convolutional(int numStates, std::vector<int> g, Binary *b) :
	t(numStates, g, b), bin(b) {
	this->stateArray = 0;
	this->stateSequence.resize((1 << numStates), std::vector<Node>{Node{-1, 0, -1}});
	for (int i = 1; i < (1 << numStates); i++) {
		this->stateSequence[i][0].cost = 1e11; // infinity
	}
}

int Convolutional::encode(int input) {
	Edge e = this->t.getTransition(this->stateArray, input);
	this->stateArray = e.end;
	return e.output;
}

void Convolutional::decode(int output) {
	std::vector<Node> nextStates(this->stateSequence.size(), Node{-1, 1e12, -1});
	for (int i = 0; i < (int)this->stateSequence.size(); i++) {
		std::vector<Edge> edges = this->t.getTransitions(i);
		for (const auto &e : edges) {
			double cost = this->stateSequence[i].back().cost;
			cost += this->bin->hammingDistance(output, e.output);

			if (cost < nextStates[e.end].cost) {
				nextStates[e.end] = Node{i, cost, e.input};
			}
		}
	}

	for (int i = 0; i < (int)this->stateSequence.size(); i++) {
		this->stateSequence[i].push_back(nextStates[i]);
	}
}

void Convolutional::decode(std::vector<double> &output) {
	std::vector<Node> nextStates(this->stateSequence.size(), Node{-1, 1e14, -1});
	for (int i = 0; i < (int)this->stateSequence.size(); i++) {
		std::vector<Edge> edges = this->t.getTransitions(i);
		for (const auto &e : edges) {
			double cost = this->stateSequence[i].back().cost;
			std::vector<double> expectedOutput = this->bin->binary3ToBPSK(e.output);
			cost += this->bin->quadraticDistance(output, expectedOutput);

			if (cost < nextStates[e.end].cost) {
				nextStates[e.end] = Node{i, cost, e.input};
			}
		}
	}

	for (int i = 0; i < (int)this->stateSequence.size(); i++) {
		this->stateSequence[i].push_back(nextStates[i]);
	}
}

void Convolutional::decodeLogprob(int output) {
	std::vector<Node> nextStates(this->stateSequence.size(), Node{-1, 1e14, -1});
	for (int i = 0; i < (int)this->stateSequence.size(); i++) {
		std::vector<Edge> edges = this->t.getTransitions(i);
		for (const auto &e : edges) {
			double cost = this->stateSequence[i].back().cost;
			cost += std::fabs(this->bin->logprob(output, e.output));

			if (cost < nextStates[e.end].cost) {
				nextStates[e.end] = Node{i, cost, e.input};
			}
		}
	}

	for (int i = 0; i < (int)this->stateSequence.size(); i++) {
		this->stateSequence[i].push_back(nextStates[i]);
	}
}

std::vector<int> Convolutional::getSequence() {
	int minState = 0;
	for (int i = 0; i < (int)this->stateSequence.size(); i++) {
		if (this->stateSequence[i].back().cost < this->stateSequence[minState].back().cost) {
			minState = i;
		}
	}

	std::stack<int> s;
	int currState = minState;
	for (int i = (int)this->stateSequence[0].size() - 1; i > 0; i--) {
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

