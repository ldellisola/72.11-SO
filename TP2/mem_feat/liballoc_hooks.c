//#include <stdio.h>
//#include <stdlib.h>
// #include <pthread.h>
//#include <sys/mman.h>
//#include <unistd.h>

/* esto es compatibilidad

#if !defined(MAP_ANONYMOUS) && defined(MAP_ANON)
# define MAP_ANONYMOUS MAP_ANON
#endif
#if !defined(MAP_FAILED)
# define MAP_FAILED ((char*)-1)
#endif

#ifndef MAP_NORESERVE
# ifdef MAP_AUTORESRV
#  define MAP_NORESERVE MAP_AUTORESRV
# else
#  define MAP_NORESERVE 0
# endif
#endif

*/
 /* uso de threads para lock y unlock
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

*/
static int page_size = -1;


// estas son para lock y unlock
/*
int liballoc_lock()
{
	pthread_mutex_lock( &mutex );
	return 0;
}

int liballoc_unlock()
{
	pthread_mutex_unlock( &mutex );
	return 0;
}
*/

// systemcalls a progamar: getpagesize(), mmap, munmap, mprotect

void* liballoc_alloc( int pages )
{
	// si lo llamo por primera vez, getpagesize() que es una systemcall, podemos hardocdearlo
	if ( page_size < 0 ) page_size = getpagesize();
	unsigned int size = pages * page_size;
	

	// hace un nuevo mmap a partir de la direccion 0, del tamaño size, sin proteccion, con flags, FD -1 y sin offset	
	char *p2 = (char*)mmap(0, size, PROT_NONE, MAP_PRIVATE|MAP_NORESERVE|MAP_ANONYMOUS, -1, 0);
	if ( p2 == MAP_FAILED) return NULL;

	// mprotect cambia las protecciones entre el rango [p2, p2+size-1]
	if(mprotect(p2, size, PROT_READ|PROT_WRITE) != 0) 
	{
		//si falla, desmapea y retorna NULL
		munmap(p2, size);
		return NULL;
	}

	return p2;
}

int liballoc_free( void* ptr, int pages )
{
	return munmap( ptr, pages * page_size );
}


