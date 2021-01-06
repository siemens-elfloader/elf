
#include <swilib.h>
#include <spl/gbs_tweak.h>

/*

extern void (*CreateICL)(PGROUP *pg);

PGROUP procs_pg =
{
    .id = RPOCESS_GROUP_ID >> 8 & 0xff,
#ifdef NEWSGOLD
    .name = "ELF_PROCESS_GROUP",
#endif
    .prio = 90,
    .stacksize = 0x8000,
    .maxmembers = 255
};


PGROUP threads_pg =
{
    .id = THREADS_GROUP_ID >> 8 & 0xff,
#ifdef NEWSGOLD
    .name = "ELF_THREADS_GROUP",
#endif
    .prio = 95,
    .stacksize = 0x8000,
    .maxmembers = 255
};


__attribute_constructor
void createElfSystemGroups()
{
    if(!getenv("GBS_GROUP_CRT")) {
        CreateICL(&procs_pg);
        CreateICL(&threads_pg);
        setenv("GBS_GROUP_CRT", "yes", 1);
    }
}

*/



