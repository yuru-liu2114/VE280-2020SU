#include <iostream>
#include <sstream>
#include "dlist.h"

using namespace std;


class LRUCache {
private:
    int mem_size; // size of memory
    int *memory;
    struct block {
        int address; // its address in memory
        int data;
    };
    Dlist<block> cache;
    int cur_cache_size;     // current length of `cache`
    int max_cache_size;     // maximum length of `cache`
    static bool compare(const block *a, const block *b);

public:
    // EFFECTS: returns true if two blocks have the same address public:
    LRUCache(int cache_size, int memory_size); // constructor
    // Initialize `cur_cache_size`, `max_cache_size`, `memory`
    // Initialize all elements in `memory` to 0
    ~LRUCache(); // destructor
    int read(int address);

    // EFFECTS: returns data corresponding to address,
    //          0 <= address < mem_size;
    //          if address is out of bound, throws an exception
    //
    // if hit,
    //   removes this block and insert it to the front;
    //   returns `data`;
    // if miss,
    //    if `cur_cache_size` equals to `max_cache_size`,
    //      removes the last (least recently used) block
    //   in the `cache`;
    //    writes data in the last block
    //    to the corresponding address in `memory`;
    //    if `cur_cache_size` < `max_cache_size`,
    //    increment `cur_cache_size` by 1;
    //    reads `data` of `address` from `memory`,
    //    inserts the block with `address` and `data`
    //    to the front of `cache`;
    //   returns `data`
    void write(int address, int data);

    // EFFECTS: writes data to address, 0 <= address < mem_size
    //            if address is out of bound, throws an exception
    //
    // if hit,
    //   removes this block from list,
    //   writes `data` to this block,
    //   and inserts this block to the front;
    // if miss,
    //    if `cur_cache_size` equals to `max_cache_size`,
    //      removes the last (least recently used) block
    //      in the `cache`;
    //    writes data in the last block
    //    to the corresponding address in `memory`;
    //    if `cur_cache_size` < `max_cache_size`,
    //    increment `cur_cache_size` by 1;
    //    inserts the block with `address` and `data`
    //    to the front of `cache`
    void printCache();

    // EFFECTS: prints the cache in given format
    void printMem();

    // EFFECTS: prints the memory in given format
    int hit(int address);
};

LRUCache::LRUCache(int cache_size, int memory_size) {
    max_cache_size = cache_size;
    mem_size = memory_size;
    cur_cache_size = 0;
    memory = new int[mem_size];
    for (int i = 0; i < mem_size; ++i) {
        memory[i] = 0;
    }
}

bool LRUCache::compare(const LRUCache::block *a, const LRUCache::block *b) {
    return a->address == b->address;
}

int LRUCache::hit(int address) {
    if (address < 0 || address >= mem_size || cur_cache_size == 0) { return -1; }

    Dlist<block> cplist(cache);
    int pos = 0;
    while (!cplist.isEmpty()) {
        block *tmp = cplist.removeBack();
        if (tmp->address == address) {
            return pos;
        }
        pos++;
    }
    return -1;
}

int LRUCache::read(int address) {
    if (address < 0 || address >= mem_size) {
        cout << "ERROR: Address out of bound" << endl;
        return INT16_MIN;
        // TODO: exception
    }
    int hit_num = hit(address);
    if (cur_cache_size < max_cache_size && hit_num == -1) {
        cur_cache_size++;
        auto *newblock = new block;
        newblock->address = address;
        newblock->data = memory[address];
        cache.insertFront(newblock);
        return memory[address];
    }
    if (cur_cache_size == max_cache_size && hit_num == -1) {
        block *tmp = cache.removeBack();
        memory[tmp->address] = tmp->data;
        delete tmp;
        auto *newblock = new block;
        newblock->address = address;
        newblock->data = memory[address];
        cache.insertFront(newblock);
        return memory[address];
    }
    block *arr[cur_cache_size];
    for (int i = 0; i < cur_cache_size; ++i) {
        arr[i] = cache.removeBack();
    }
    for (int i = 0; i < hit_num; ++i) {
        cache.insertFront(arr[i]);
    }
    for (int i = hit_num + 1; i < cur_cache_size; ++i) {
        cache.insertFront(arr[i]);
    }
    cache.insertFront(arr[hit_num]);
    return arr[hit_num]->data;
}

LRUCache::~LRUCache() {
    delete[] memory;
    Dlist<block> copy(cache);
    while (!copy.isEmpty()) {
        block *tmp = copy.removeFront();
        delete tmp;
    }
}

void LRUCache::printCache() {
    Dlist<block> copy(cache);
    while (!copy.isEmpty()) {
        block *tmp = copy.removeFront();
        cout << tmp->address << " " << tmp->data << endl;
    }
}

void LRUCache::printMem() {
    for (int i = 0; i < mem_size; ++i) {
        cout << memory[i] << " ";
    }
    cout<<endl;
}

void LRUCache::write(int address, int data) {
    if (address < 0 || address >= mem_size) {
        cout << "ERROR: Address out of bound" << endl;
        return;

    }
    int hit_num = hit(address);
    if (cur_cache_size < max_cache_size && hit_num == -1) {
        cur_cache_size++;
        auto *newblock = new block;
        newblock->address = address;
        newblock->data = data;
        cache.insertFront(newblock);
        return;
    }
    if (cur_cache_size == max_cache_size && hit_num == -1) {
        block *tmp = cache.removeBack();
        memory[tmp->address] = tmp->data;
        delete tmp;
        auto *newblock = new block;
        newblock->address = address;
        newblock->data = data;
        cache.insertFront(newblock);
        return;
    }
    block *arr[cur_cache_size];
    for (int i = 0; i < cur_cache_size; ++i) {
        arr[i] = cache.removeBack();
    }
    for (int i = 0; i < hit_num; ++i) {
        cache.insertFront(arr[i]);
    }
    for (int i = hit_num + 1; i < cur_cache_size; ++i) {
        cache.insertFront(arr[i]);
    }
    arr[hit_num]->data = data;
    cache.insertFront(arr[hit_num]);
}


int main() {
    int cache_size;
    int memory_size;
    cin >> cache_size >> memory_size;
    LRUCache c(cache_size, memory_size);
    string line, ch;
    string exit = "EXIT";
    string read="READ";
    string write="WRITE";
    string pcache="PRINTCACHE";
    string pmem="PRINTMEM";
    cin.ignore();
    while (getline(cin, line)) {
        if (line.size() <= 2) {
            break;
        }
        if (line.compare(exit) == 0) {
            break;
        }
        istringstream istring(line);
        istringstream copystring(line);
        int cn=1;
        string cmd;
        istring>>cmd;
        while(istring){
            istring>>ch;
            if(istring){
                cn++;
            }
        }
        if(cmd.compare(read)==0) {
            if(cn<2) {
                cout << "ERROR: Not enough operands" << endl;
                continue;
            }
            if(cn>=3){
                cout << "ERROR: Too many operands" << endl;
                continue;
            }
            int address;
            copystring>>cmd>>address;
            int read_result=c.read(address);
            if(read_result!=INT16_MIN){
                cout<<c.read(address)<<endl;
            }
        }
        else if(cmd.compare(write)==0) {
            if(cn<3) {
                cout << "ERROR: Not enough operands" << endl;
                continue;
            }
            if(cn>=4){
                cout << "ERROR: Too many operands" << endl;
                continue;
            }
            int address,data;
            copystring>>cmd>>address>>data;
            c.write(address,data);
        }
        else if(cmd.compare(pcache)==0) {
            if(cn<1) {
                cout << "ERROR: Not enough operands" << endl;
                continue;
            }
            if(cn>=2){
                cout << "ERROR: Too many operands" << endl;
                continue;
            }
            c.printCache();
        }
        else if(cmd.compare(pmem)==0) {
            if(cn<1) {
                cout << "ERROR: Not enough operands" << endl;
                continue;
            }
            if(cn>=2){
                cout << "ERROR: Too many operands" << endl;
                continue;
            }
            c.printMem();
        }
        else{
            cout << "ERROR: Unknown instruction" << endl;
            continue;
        }
    }
    return 0;
}






