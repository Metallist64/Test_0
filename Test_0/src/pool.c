// Helper macro for iterating through all objects in a specific pool (used for initialisation object)
#define FOREACH_IN_POOL(ObjectType, object, pool) \
    for (ObjectType **ptr = (ObjectType **)pool->allocStack, *object = *ptr;  /* Initialize pointer to start of pool's allocation stack and get first object */  \
         ptr < (ObjectType **)pool->allocStack + pool->size;                  /* Continue while pointer is within pool bounds (start + size) */ \
         object = *++ptr)                                                     /* Move to next pointer in stack and dereference to get next object */

// Helper macro for iterating through all allocated objects in a specific pool (used in main cycle for updating active objects)
#define FOREACH_ALLOCATED_IN_POOL(ObjectType, object, pool) \
    for (ObjectType **ptr = (ObjectType **)POOL_getFirst(pool), *object = *ptr;   /* Initialize pointer to first allocated object in pool */ \
         ptr < (ObjectType **)POOL_getFirst(pool) + POOL_getNumAllocated(pool);   /* Continue while pointer is within allocated objects range */ \
         object = *++ptr)     

         