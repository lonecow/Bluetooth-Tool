#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <string>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>

class Device
{
public:
	Device(const inquiry_info & device_info, const std::string & name);
	~Device();

private:
	void init();
	void cleanup();

public:
	std::string getName();
	std::string getAddress();

private:
	inquiry_info m_info;
	std::string m_name;
};
#endif

