#include <microhttpd.h> // library for http server
#include <stdio.h>
#include <string.h>

#define PORT 8080 // port where will run our app

// function that handels every http requewst, static says that it will be visible olny in this file (like private func)
// return enum (just tells libmicrohttpd if request was handled with success or not)
static enum MHD_Result answer_to_connection(void *cls, // Custom data
                                            struct MHD_Connection *connection, // The client's connection
                                            const char *url, // "api/test"
                                            const char *method, // http method (GET, POST, DELETE ...)
                                            const char *version, const char *upload_data, 
                                            size_t *upload_data_size, void **con_cls
) {
    const char *page; // store the resonse 
    struct MHD_Response *response; // store http resonse what we will send back
    enum MHD_Result ret; // will store failde/success status and will return it at the end of the func (MHD_YES/MHD_NO)

    // check the request(routing)
    if (strcmp(method, "GET") == 0 && strcmp(url, "/api/test") == 0) {
        page = "{\"message\":\"api works\"}";
    } else {
        "{\"message\":\"...\"}";
    }

    // create http response
    response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);
    // (void*)page -> cast to generic pointer
    // MHD_RESPMEM_PERSISTENT -> don't delete message after sending it

    // metadata
    MHD_add_response_header(response, "Content-Type", "application/json");

    // send the response
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    // MHD_HTTP_OK -> 200

    // cleanUp
    MHD_destroy_response(response); // frees memory (since we are done with it)

    return ret;
}

int main() {
    struct MHD_Daemon *daemon; // like create routing (in Go: route := gin.Default)

    daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL,
                                &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon) {
        return 1;
    }

    printf("Server run on port: %d", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}