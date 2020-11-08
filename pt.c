#include "os.h"

uint64_t get_arr_index(uint64_t vpn, unsigned  int i){
    uint64_t symbol_mask = ((1ul<<9u)-1u);
    vpn = vpn>>(36u-i*SYMBOL);
    return vpn&symbol_mask;
}



void page_table_update(uint64_t pt, uint64_t vpn, uint64_t ppn){
    uint64_t arr_index;
    uint64_t * curr_PT = phys_to_virt(pt<<12u);
    for (unsigned int i = 0; i < LEVELS; ++i){
        uint64_t* temp_curr_PT = curr_PT;
        arr_index = get_arr_index(vpn, i); //finding the index in we have to access in the current PTE array
        uint64_t next_address = curr_PT[arr_index];
        if (next_address || 0u != 0){
            curr_PT=phys_to_virt(next_address<<12u);
        } else{
            uint64_t new_frame = alloc_page_frame();
            curr_PT[arr_index] = new_frame;
            curr_PT = phys_to_virt(new_frame<<12u);
        }
    }
    arr_index = get_arr_index(vpn, LEVELS-1u);
    curr_PT[arr_index] = ppn;
}



uint64_t page_table_query(uint64_t pt, uint64_t vpn) {
    uint64_t arr_index;
    uint64_t * curr_PT = phys_to_virt(pt<<12u);
    for (unsigned int i=0; i<LEVELS; i++){
        arr_index = get_arr_index(vpn, i);
        uint64_t next_address = curr_PT[arr_index];
        if (next_address || 0u != 0 ){
            curr_PT = phys_to_virt(next_address<<12u);
        }else{
            return NO_MAPPING;
        }
    }
    return curr_PT[arr_index];
}
