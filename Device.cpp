
#include "Device.h"


Device::Device(const inquiry_info & device_info, const std::string & name)
{
	init();
	m_info = device_info;
	m_name = name;
}

Device::~Device()
{
	cleanup();
}

void Device::init()
{
	memset(&m_info, 0, sizeof(m_info));
	m_name.clear();
}

void Device::cleanup()
{
	memset(&m_info, 0, sizeof(m_info));
	m_name.clear();
}

std::string Device::getName()
{
	return m_name;
}

std::string Device::getAddress()
{
	char buffer[256] = {0};
	ba2str(&m_info.bdaddr, buffer);
	return std::string(buffer);
}

