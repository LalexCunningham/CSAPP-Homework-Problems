#include "memlib.c"

/* Basic Constants and Macros */
#define WSIZE 4 /* Word and header/footer size */
#define DSIZE 8 /* Double word size */
#define CHUNKSIZE (1<<12) /* Extend heap by this amount (4096) */

#define MAX(x, y) ((x) > (y) ? (x) : (y))

/* Pack a size and allocated bit into a word */
#define PACK(size, alloc) ((size) | (alloc))

/* Read and write a word at an address p */
#define GET(p)      (*(unsigned int *)(p)) /* Pointer dereference */
#define PUT(p, val) (*(unsigned int *)(p) = (val))

/* Read the size and allocated fields from address p */
#define GET_SIZE(p)     (GET(p) & ~0x7)
#define GET_ALLOC(p)    (GET(p) & 0x1)

/* Given block ptr bp, compute address of it's header and footer */
#define HDRP(bp)    ((char *)(bp) - WSIZE)
#define FTRP(bp)    ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE;
/*
    Why DSIZE?
        Because GET_SIZE returns size of HDR + PAYLOAD + FTR
        Our bp points to the first address of payload, so 
        bp + GET_SIZE puts us 2 words ahead of the footer
*/

char *heap_listp;
char *heap_fitp;

/* Given block prt bp, compute address of next and previous blocks */
#define NEXT_BLKP(bp)   ((char *)(bp) + GET_SIZE(((char *)(bp) - WSIZE)))
#define PREV_BLKP(bp)   ((char *)(bp) - GET_SIZE(((char *)(bp) - DSIZE)))

int mm_init(void) {
    /* Create the initial empty heap */

    if ((heap_fitp = heap_listp = mem_sbrk(4*WSIZE)) == (void *) -1) {
        return -1; /* mem_sbrk returned -1, not enough memory */
    }

    /* Allocate initial structures within newly allocated 4*WSIZE bytes */
    PUT(heap_listp, 0); /* Alignment Padding? */
    PUT(heap_listp + (1*WSIZE), PACK(DSIZE, 1)); /* Prologue Header */
    PUT(heap_listp + (2*WSIZE), PACK(DSIZE, 1)); /* Prologues Footer */
    PUT(heap_listp + (3*WSIZE), PACK(0, 1)); /* Epilogues Header */
    heap_listp += (2*WSIZE);

    /* Extend the empty heap with a free block of CHUNKSIZE bytes */
    if (extend_heap(CHUNKSIZE/WSIZE) == NULL) {
        return -1;
    }
    return 0;
}

static void *extend_heap(size_t words) {
    char *bp;
    size_t size;

    /* Allocate an even number of words to maintain alignment */
    size = (words % 2) ? (words + 1) * WSIZE : words * WSIZE;
    if ((long) (bp = mem_sbrk(size)) == -1) {
        return NULL;
    }

    PUT(HDRP(bp), PACK(size, 0)); /* Free block header */
    PUT(FTRP(bp), PACK(size, 0)); /* Free block footer */
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1)); /* New epilogue header */

    /* Coalesce if the previous block was free */
    return coalesce(bp);
}

static void *coalesce(char *bp) {
    size_t prev_alloc = GET_ALLOC(FTRP(PREV_BLKP(bp)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));

    if (prev_alloc && next_alloc) {
        return bp;
    }

    else if (prev_alloc && !next_alloc) {
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
    }

    else if (!prev_alloc && next_alloc) {
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(bp), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }

    else {
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(PREV_BLKP(bp)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(bp)), PACK(size, 0));
        bp = PREV_BLKP(bp);
    }
}

void *mm_maloc(size_t size) {
    size_t asize;   /* Adjusted block size */
    size_t extend_size;     /* Amount to extend heap if no fit */
    char *bp;

    /* Ignore spurious requests */
    if (size == 0) {
        return NULL;
    }

    /* Adjust block size to include overhead and alignment reqs */
    if (size < DSIZE) {
        asize = 2*DSIZE;
    } else {
        asize = DISZE * ((size + (DSIZE) + (DSIZE-1)) / DSIZE);
    }

    /* Search the free list for a fit */
    if ((bp = find_fit(asize)) != NULL) {
        place(bp, asize);
        return bp;
    }

    /* No fit found. Get more memory and place the block */
    extendsize = MAX(asize,CHUNKSIZE);
    if ((bp = extend_heap(extendsize/WSIZE)) == NULL) 
        return NULL;
    place(bp, asize);
    return bp;
}

static void *find_fit(size_t asize) {
    char *cbp =  NEXT_BLKP(heap_listp);
    
    while (GET_SIZE(HDRP(cbp)) != 0) {
        if (GET_ALLOC(HDRP(cbp)) && GET_SIZE(HDRP(cbp)) <= asize) {
            return cbp;
        }
        cbp = NEXT_BLKP(cbp);\
    }

    return NULL;
}

static void *find_fit(size_t asize) {
    char *starting_point = heap_fitp;

    if (GET_SIZE(HDRP(heap_fitp)) == 0) {
        heap_fitp = heap_listp;
    } else {
        if (GET_ALLOC(HDRP(heap_fitp)) && GET_SIZE(HDRP(heap_fitp)) <= asize) {
            return heap_fitp;
        }
        
        heap_fitp = NEXT_BLKP(heap_fitp);
    }

    while (heap_fitp != starting_point) {

        if (GET_SIZE(HDRP(heap_fitp)) == 0) {
            heap_fitp = heap_listp;
            continue;
        }

        if (GET_ALLOC(HDRP(heap_fitp)) && GET_SIZE(HDRP(heap_fitp)) <= asize) {
            return heap_fitp;
        }
        
        heap_fitp = NEXT_BLKP(heap_fitp);
    }

    return NULL;
}

static void place(void *bp, size_t asize) {
    size_t csize = GET_SIZE(HDRP(bp));
    if (csize - asize < (2*DSIZE)) {
        PUT(HDRP(bp), PACK(csize, 1)); /* Just need to adjust the allocated bit */
        PUT(FTRP(bp), PACK(csize, 1));
    } else {
        PUT(HDRP(bp), PACK(asize), 1);
        PUT(FTRP(bp), PACK(asize), 1);
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize-asize, 0));
        PUT(FTRP(bp), PACK(csize-asize, 0));

    }
}

int main(int argc, char const *argv[])
{  
    /* code */
    return 0;
}
