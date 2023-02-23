#ifndef _PPS_PROXY_H
#define _PPS_PROXY_H

typedef void (*pps_callback_t)(void * /*message*/, int /*message size*/);

#define MAX_TOPIC_NUM       (32)
#define PPS_TIMEOUT         (3000)

#define THREAD_DISPLAY_VIDEO     "display_video"
#define THREAD_RECEIVE_MESSAGE   "receive_msg"
#define THREAD_HANDLE_MESSAGE    "handle_msg"

#endif