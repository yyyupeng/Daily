#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<fcntl.h>
#include<sys/mman.h>

int main(int argc, char *argv[])
{
    int i=0;
    int fd=0;
    int MAX = atoi(argv[1]);
    struct timeval tv1, tv2;
    int *arr = (int *)malloc( sizeof(int)*MAX );
 
    fd = open( "mmap_test", O_RDWR );
    for(i = 0; i < MAX; ++i)
        arr[i] = i;
    if( sizeof(int)*MAX != write( fd, (void *)arr, sizeof(int)*MAX ) )
    {
        printf( "Writing data failed...\n" );
        return -1;
    }
    free(arr);
    close( fd );
    
    gettimeofday( &tv1, NULL );
    fd = open( "mmap_test", O_RDWR );
    int *array = mmap( NULL, sizeof(int)*MAX, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0 );
    for( i=0; i<MAX; ++i )
        ++array[ i ];
    munmap( array, sizeof(int)*MAX );
    msync( array, sizeof(int)*MAX, MS_SYNC );
    close( fd );
    gettimeofday( &tv2, NULL );
    printf( "Time of mmap: %ldms\n", tv2.tv_usec-tv1.tv_usec );
    pause();

    return 0;
}
