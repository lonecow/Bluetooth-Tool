
#include "Adapter.h"

#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

Adapter::Adapter()
{
	init();
	OpenAdapter("");
}

Adapter::Adapter(const std::string & address)
{
	init();
	OpenAdapter(address);
}

Adapter::~Adapter()
{
	cleanup();
}

void Adapter::init()
{
	memset(&m_bluetooth_address, 0, sizeof(m_bluetooth_address));
	memset(&m_device_info, 0, sizeof(m_device_info));
	m_dev_num = -1;
	m_attached = false;
}

void Adapter::cleanup()
{
	memset(&m_bluetooth_address, 0, sizeof(m_bluetooth_address));
	memset(&m_device_info, 0, sizeof(m_device_info));
	m_dev_num = -1;
	m_attached = false;
}

void Adapter::OpenAdapter(const std::string & address)
{
	if(address != "")
		m_dev_num = hci_devid(address.c_str());
	else
		m_dev_num = hci_get_route(NULL);

	m_adapter_sock = hci_open_dev(m_dev_num);

	if (m_dev_num < 0 || m_adapter_sock < 0)
	{
		cleanup();
	}
	else
	{
		hci_devinfo(m_dev_num, &m_device_info);
		m_attached = true;
	}
}

bool Adapter::isAttached()
{
	return m_attached;
}

std::string Adapter::getAdapterName()
{
	return std::string(m_device_info.name);
}

std::string Adapter::getAdapterAddress()
{
	char buffer[256] = {0};

	if (isAttached())
	{
		snprintf(buffer, sizeof(buffer),	"%02x:%02x:%02x:%02x:%02x:%02x",
							m_device_info.bdaddr.b[0],
							m_device_info.bdaddr.b[1],
							m_device_info.bdaddr.b[2],
							m_device_info.bdaddr.b[3],
							m_device_info.bdaddr.b[4],
							m_device_info.bdaddr.b[5]);
	}

	return std::string(buffer);
}


