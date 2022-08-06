#include "hash.h"

Hash::Hash(int tablesize, int (*hf) (std::string) ) {
	this->_hash_func = hf;

	this->_table.resize(tablesize);
	this->_size_registry.resize(tablesize, 0);
	this->_total_size = 0;
}

int Hash::add(std::string str, int &collisions) { 
	if (this->contains(str, collisions) == 1) {
		return 0;
	}

	int hash_key = this->hash(str);
	this->_table[hash_key].push_front(str);
	this->_size_registry[hash_key]++;
	this->_total_size++;
    return 1;
}//add

int Hash::remove(std::string str, int &collisions) { 
	if (this->contains(str, collisions) == 0) {
		return 0;
	}
    
	int hash_key = this->hash(str);
    this->_table[hash_key].remove(str);
	this->_size_registry[hash_key]--;
	this->_total_size--;
    return 1;
}//remove


int Hash::hash(std::string str) { 
	int hash_digest = this->_hash_func(str);

	if (hash_digest >= (int)this->_table.size()) {
		return (int)this->_table.size() - 1;
	} else if (hash_digest < 0) {
		return 0;
	} else {
		return hash_digest;
	}
}//hash
    
int Hash::contains(std::string str, int &collisions) { 
	int hash_key = this->hash(str);
	collisions = 0;

	for (const auto &c : this->_table[hash_key]) {
		if (str != c) {
			collisions++;
		} else {
			collisions++;
			return 1;
		}
	}
    return 0;
    
}//contains


int Hash::worst_case() {
	int worst = this->_size_registry[0];

	for (auto &c : this->_size_registry) {
		if (worst < c) {
			worst = c;
		}
	}

	return worst;
}//worst_case

int Hash::size() {
	return this->_total_size;
}//size

