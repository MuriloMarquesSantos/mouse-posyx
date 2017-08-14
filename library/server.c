
#include <libwebsockets.h>
#include <string.h>
#include "../include/server.h"

struct lws_protocols protocols[] =
{
	/* The first protocol must always be the HTTP handler */
	{
		"http-only",   /* name */
		callback_http, /* callback */
		0,             /* No per session data. */
		0,             /* max frame size / rx buffer */
	},
	{
		"mouse-protocol",
		callback_mouse,
		0,
		EXAMPLE_RX_BUFFER_BYTES,
	},
	{ NULL, NULL, 0, 0 } /* terminator */
};

void PositionParser (char * Input, int * x, int * y) {
  char * pointer = NULL;

  pointer = strtok(Input, "@");
  *x = atoi(pointer);
  pointer = strtok(NULL, "@");
  *y = atoi(pointer);
}

int callback_http( struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len )
{
	switch(reason)
	{
		case LWS_CALLBACK_HTTP:
			lws_serve_http_file( wsi, "example.html", "text/html", NULL, 0 );
			break;
		default:
			break;
	}

	return 0;
}

int callback_mouse( struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len )
{
  unsigned int x,y;
	switch(reason)
	{
		case LWS_CALLBACK_RECEIVE:
			memcpy( &received_payload.data[LWS_SEND_BUFFER_PRE_PADDING], in, len );
			received_payload.len = len;

      // Parsing and set cursor position
      PositionParser (in, &x, &y);
      SetCursorPos (x,y);

			lws_callback_on_writable_all_protocol(lws_get_context(wsi),lws_get_protocol(wsi));
			break;

		case LWS_CALLBACK_SERVER_WRITEABLE:
			lws_write( wsi, &received_payload.data[LWS_SEND_BUFFER_PRE_PADDING], received_payload.len, LWS_WRITE_TEXT );
			break;

		default:
			break;
	}

	return 0;
}

int Start(SERVER * this) {
	while(!this->IsStop){
		lws_service(this->Context, 1000000);
	}

  this->IsStop = 1;

	return 0;
}

int Stop(SERVER * this) {
  this->IsStop = 1;

  while(this->IsStop) {
    sleep(1);
  }

	lws_context_destroy(this->Context);
  free(this->ContextInfo);
  free(this);

  return 0;
}

SERVER * InitializeServer(int Port) {
  SERVER * Server = malloc(sizeof(SERVER));

  if (Server == NULL) {
    printf("RESOURCE FAILED\n");
    goto FAIL;
  }

  Server->Protocols = protocols;
  Server->NumbersOfProtocols = 2;

  struct lws_context_creation_info * ContextInfo;
  ContextInfo = malloc(sizeof(struct lws_context_creation_info));

  if (ContextInfo == NULL) {
    printf("RESOURCE FAILED\n");
    free(Server);
    Server = NULL;
    goto FAIL;
  }

  memset(ContextInfo, 0, sizeof(ContextInfo));

  ContextInfo->port = Port;
  ContextInfo->protocols = Server->Protocols;
  ContextInfo->gid = -1;
  ContextInfo->uid = -1;

  Server->ContextInfo = ContextInfo;
  Server->Context = lws_create_context(Server->ContextInfo);

  Server->Start = Start;
  //Server->Stop = Stop;

FAIL:
  return Server;
}
