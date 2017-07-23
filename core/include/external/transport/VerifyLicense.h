#ifndef __VERIFY_LICENSE__
#define __VERIFY_LICENSE__

#include <stdio.h>
#include <string>

class VerifyLicense
{
public: // config
	char* verify_service_ip;
	int verify_service_port;

public:
	VerifyLicense();
	~VerifyLicense();

	bool SendMessageTo(const char * send_msg, int send_len);
	void DoVerify(char* license);
};

#endif
