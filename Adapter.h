#ifndef _ADAPTER_H_
#define _ADAPTER_H_

#include <string>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>

class Adapter
{
public:
	Adapter();
	Adapter(const std::string & address);
	~Adapter();

	bool isAttached();

	std::string getAdapterName();
	std::string getAdapterAddress();
private:
	void init();
	void cleanup();

	/** @brief Opens Adapter given an Address */
	void openAdapter(const std::string & address);

private:
	bdaddr_t m_bluetooth_address;
	int32_t m_dev_num;
	int32_t m_adapter_sock;

	bool m_attached;

	hci_dev_info m_device_info;

};

#endif

