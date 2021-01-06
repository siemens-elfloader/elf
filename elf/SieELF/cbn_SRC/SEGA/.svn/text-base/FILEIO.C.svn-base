
#include "shared.h"


/*
    Load a normal file, or ZIP/GZ archive.
    Returns NULL if an error occured.
*/
uint8 *load_archive(char *filename, int *file_size)
{
    uint8 *buf = NULL;
    if(!(buf=(uint8*)loadfile(filename))) return 0;
    *file_size=loadfilesize;
    return buf;
}


/*
    Verifies if a file is a ZIP archive or not.
    Returns: 1= ZIP archive, 0= not a ZIP archive
*/

/*
    Returns the size of a GZ compressed file.
*/
