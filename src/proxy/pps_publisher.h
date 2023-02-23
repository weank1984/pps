#ifndef _PPS_PUBLISHER_H
#define _PPS_PUBLISHER_H

class PPSPublisher
{
public:
	PPSPublisher(const char *service_name)
	{
		create_pps_publisher(service_name);
	}

	int publish_message(const char *msg, int msg_size);
private:
	int create_pps_publisher(const char *service_name);

	int m_fd;
protected:
	// const PPSPublisher() = delete;
};

#endif