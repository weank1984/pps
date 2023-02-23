#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "pps_publisher.h"

int PPSPublisher::create_pps_publisher(const char *service_name)
{
   struct stat stat_buf;
   if (stat("/pps", &stat_buf) != 0)
   {
      printf("The PPS server isn't running.\n");
      return 0;
   }

   /* debug */
   printf("%s\n", service_name);

   /* Create the "button" object (if it doesn't already exist). */
   m_fd = open(service_name, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
   if (m_fd < 0)
   {
      perror ("Couldn't open service");
      return 0;
   }

   return 1;
}


int PPSPublisher::publish_message(const char *msg, int msg_size)
{
   ssize_t len, bytes_written;
   char buf[256];
   len = snprintf(buf, 256, "%s\n", msg);

   bytes_written = write(m_fd, buf, len);
   if (bytes_written == -1)
   {
      perror("write()");
   }
   else if (bytes_written != len)
   {
      printf("Bytes written: %d String length: %d\n", (int)bytes_written, (int)len);
   }

   return 1;
}
