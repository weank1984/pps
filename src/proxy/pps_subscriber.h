#ifndef _PPS_SUBCRIBER_H
#define _PPS_SUBCRIBER_H
#include <sys/poll.h>

#include "macros.h"
#include "pps_proxy.h"

/* TODO
 * 使用线程池
 */

class PPSSubcriber
{
public:
    int create_pps_subscriber(const char *service_name, pps_callback_t callback);
	void receive_message(char *buf);

private:
    int m_topic_num;
    int m_fd[MAX_TOPIC_NUM];
   	struct pollfd m_readfds[MAX_TOPIC_NUM];
    pps_callback_t m_handle[MAX_TOPIC_NUM];

DECLARE_SINGLETON(PPSSubcriber)
};

#endif