#include <stdlib.h>
#include <unistd.h>

#include "../knowledge/knowledge.h"
#include "../parameters/parameters.h"

#include "server.h"

static void finalize_thread_collection
(
   struct JH_server_thread_collection workers [const restrict static 1]
)
{
   free((void *) workers->threads);

   workers->threads_capacity = 0;

   pthread_mutex_destroy(&(workers->mutex));
   pthread_barrier_destroy(&(workers->barrier));

   workers->currently_running = 0;
}

static void finalize_socket
(
   struct JH_server_socket socket [const restrict static 1]
)
{
   FD_ZERO(&(socket->as_a_set));

   close(socket->file_descriptor);

   socket->file_descriptor = -1;
}

void JH_server_finalize
(
   struct JH_server server [const restrict static 1]
)
{
   JH_knowledge_finalize(&(server->k));
   finalize_thread_collection(&(server->workers));
   finalize_socket(&(server->socket));
}
