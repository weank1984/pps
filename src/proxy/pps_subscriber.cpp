#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#include "pps_subscriber.h"

static void* receive_message_loop(void* ptr)
{
    char buf[256];
    while (1)
    {
        reinterpret_cast<PPSSubcriber*>(ptr)->receive_message(buf);
    }
}

PPSSubcriber::PPSSubcriber()
{
    m_topic_num = 0;

    struct stat stat_buf;
    if (stat("/pps", &stat_buf) != 0)
    {
        perror("The PPS server isn't running");
    }

    // 创建pps epoll线程
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&tid, &attr, receive_message_loop, this);  // 创建线程
    pthread_setname_np(tid, THREAD_RECEIVE_MESSAGE);
    pthread_attr_destroy(&attr);
}


int PPSSubcriber::create_pps_subscriber(const char *service_name, pps_callback_t callback)
{
    if (m_topic_num >= MAX_TOPIC_NUM)
    {
        perror ("Couldn't create topic");
        return -1;
    }
    //
    char client_name[256];
    snprintf(client_name, 256, "%s?delta", service_name);
    m_fd[m_topic_num] = open(client_name, O_RDONLY);
    if (m_fd[m_topic_num] < 0)
    {
        perror ("Couldn't open client");
        return -1;
    }
    m_readfds[m_topic_num].fd = m_fd[m_topic_num];
    m_readfds[m_topic_num].events = POLLIN;
    m_handle[m_topic_num] = callback;
    m_topic_num++;
    //
    return 1;
}

void PPSSubcriber::receive_message(char *buf)
{
    ssize_t num_bytes;
    int ret = poll(m_readfds, m_topic_num, PPS_TIMEOUT);

    switch (ret)
    {
    case -1:
        /* An error occurred. */
        break;
    case 0:
        /* poll() timed out. */
        break;
    default:
        for (int i = 0; i < m_topic_num; ++i)
        {
            if(m_readfds[i].revents & POLLRDNORM)
            {
                num_bytes = read(m_fd[i], buf, 256);
                if (num_bytes > 0)
                {
                    m_handle[i](buf, num_bytes);
                }
            }
        }
        break;
    }
}
