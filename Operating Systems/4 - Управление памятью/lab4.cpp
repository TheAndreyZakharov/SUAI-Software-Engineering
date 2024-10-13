#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <climits>

#include "lab4.h"  // Include the header for random number generation

struct Page {
    int vpn;     // Virtual page number
    bool r;      // Reference bit (used for administrative purposes here)
    bool m;      // Modified bit (not actively used in FIFO or LRU)
    int last_used; // Used for LRU to store the last use time

    Page() : vpn(-1), r(false), m(false), last_used(0) {}  // Default constructor initializes an empty page
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [algorithm number]" << std::endl;
        return 1;
    }

    int algorithm = std::stoi(argv[1]); // 1 for FIFO, 2 for LRU
    const int NUM_PAGES = 12;           // Number of physical pages available
    std::vector<Page> page_table(NUM_PAGES);
    std::deque<int> queue;              // Queue for FIFO
    int timer = 0;                      // Used as a timestamp for LRU

    int operation_type, virtual_page;
    while (std::cin >> operation_type >> virtual_page) {
        bool page_found = false;
        int empty_index = -1;

        for (int i = 0; i < NUM_PAGES; ++i) {
            if (page_table[i].vpn == virtual_page) {
                page_table[i].r = true;
                page_table[i].m = operation_type == 1 || page_table[i].m;
                page_table[i].last_used = timer;  // Update the last used time for LRU
                page_found = true;
                break;
            }
            if (page_table[i].vpn == -1 && empty_index == -1) {
                empty_index = i;       // Track the first empty spot
            }
        }

        if (!page_found) {
            int replace_index = empty_index != -1 ? empty_index : -1;

            if (replace_index == -1) {
                if (algorithm == 1) {  // FIFO
                    if (!queue.empty()) {
                        replace_index = queue.front();
                        queue.pop_front();
                    }
                }
                else if (algorithm == 2) {  // LRU
                    int oldest_time = INT_MAX;
                    for (int i = 0; i < NUM_PAGES; ++i) {
                        if (page_table[i].last_used < oldest_time) {
                            oldest_time = page_table[i].last_used;
                            replace_index = i;
                        }
                    }
                }
            }

            if (replace_index != -1) {
                page_table[replace_index].vpn = virtual_page;
                page_table[replace_index].r = true;
                page_table[replace_index].m = (operation_type == 1);
                page_table[replace_index].last_used = timer;  // Update time for LRU
                if (algorithm == 1) {
                    queue.push_back(replace_index);  // Add to queue for FIFO
                }
            }
        }

        std::ostringstream output;
        for (int i = 0; i < NUM_PAGES; ++i) {
            if (i > 0) output << " ";
            output << (page_table[i].vpn == -1 ? "#" : std::to_string(page_table[i].vpn));
        }
        std::cout << output.str() << std::endl;
        timer++;  // Increment timer for LRU
    }

    return 0;
}

