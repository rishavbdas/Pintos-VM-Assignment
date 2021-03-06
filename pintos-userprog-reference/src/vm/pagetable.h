#include <stdbool.h>
#include "threads/synch.h"
#include "lib/kernel/hash.h"
/* #include "userprog/process.h" */
#include "filesys/off_t.h"
#define MAX_MAPS 100
enum data_location
{
  mmap1,all_zero,swap,filesys
};
/* int mapid; */
void *mapids[MAX_MAPS];
struct page_data
{
  void * vaddr;
  struct hash_elem hash_elem;
  enum data_location loc;
  
  int swap_sector; //Valid if loc==swap
  
  struct file* file; //Valid if loc= filesys or mmap
  int page_read_bytes; //valid if loc=filesys
  bool writable;
  off_t offset;
  
  //valid loc== mmap
  int pagenumber;//starting with 0;
  int mapid;
  int length;
  
  int block_sector; //valid if loc==swap
}; 


struct page_data *
SPT_lookup (const void *address,struct thread *t);

void SPT_init();

void SPT_insert(struct page_data *p,struct thread *t);
bool SPT_remove(const void *address,struct thread *t);
