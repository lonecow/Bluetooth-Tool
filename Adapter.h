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

	/** @brief indicates weather or not we were able to find an adapter */
	bool isAttached();

	/** @brief Gets this adapters short Name */
	std::string getName();

	/** @brief Gets this Adapters Name */
	std::string getAddress();
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

