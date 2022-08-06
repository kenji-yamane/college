#ifndef LAB1_HASH_H
#define LAB1_HASH_H

#include <vector>
#include <forward_list>
#include <string>
#include <cassert>
#include <iostream>

class Hash {
    
public:
    
    /// construct hashtable with size and hashfunction
    Hash(int tablesize,int (*hf) (std::string) ) ;
    
    
    
    int contains(std::string str, int &collisions);
    
    int add(std::string str, int &collisions) ;
    
    int worst_case();
    
    int size();
    
    int remove(std::string str, int &collisions) ;
    

private:
    
	int _total_size;
    int (*_hash_func) (std::string); /// function pointer

	std::vector<int> _size_registry;
    
    std::vector<std::forward_list<std::string> > _table;
};//class



#endif
