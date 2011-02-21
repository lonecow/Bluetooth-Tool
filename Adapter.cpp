
#include "Adapter.h"

#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

Adapter::Adapter()
{
	init();
	openAdapter("");
}

Adapter::Adapter(const std::string & address)
{
	init();
	openAdapter(address);
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
	m_adapter_sock = -1;
}

void Adapter::cleanup()
{
	memset(&m_bluetooth_address, 0, sizeof(m_bluetooth_address));
	memset(&m_device_info, 0, sizeof(m_device_info));

	if (isAttached())
		hci_close_dev(m_adapter_sock);

	m_adapter_sock = -1;
	m_dev_num = -1;
	m_attached = false;
}

void Adapter::openAdapter(const std::string & address)
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

std::string Adapter::getName()
{
	return std::string(m_device_info.name);
}

std::string Adapter::getAddress()
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

void Adapter::scanForDevices(std::vector<Device> & devices)
{
	devices.clear();
	if(isAttached())
	{
		/* we are going to try to discover for 1.28 * len seconds */
		int32_t len  = 8;

		/* we only want 255 people to respond */
		int32_t max_rsp = 255;

		/* flush away all cached devices first */
		int32_t flags = IREQ_CACHE_FLUSH;

		inquiry_info * info = new inquiry_info[max_rsp];

		if(info)
		{
			memset(info, 0, (sizeof(inquiry_info) * max_rsp));

			int32_t num_rsp = hci_inquiry(m_dev_num, len, max_rsp, NULL, &info, flags);

			for (int32_t i = 0; i < num_rsp; i++)
			{
				inquiry_info * local_info = (info + i);
				if(local_info)
				{
					char buffer[256] = {0};
					if (hci_read_remote_name(m_adapter_sock, &local_info->bdaddr, sizeof(buffer), buffer, 0) < 0)
					{
						devices.push_back(Device(*local_info, std::string("[unknown]")));
					}
					else
					{
						devices.push_back(Device(*local_info, std::string(buffer)));
					}
				}
			}

			delete[] info;
			info = NULL;
		}
	}
}

