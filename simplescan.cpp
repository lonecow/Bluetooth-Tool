
/**********************************
 *
 * From http://people.csail.mit.edu/albert/bluez-intro/c404.html
 *
 *********************************/
#include "Adapter.h"
#include "Device.h"

int main(int argc, char **argv)
{
	Adapter myAdapter;

	std::vector<Device> devices;

	myAdapter.scanForDevices(devices);

	printf("Found %d devices\n", devices.size());

	std::vector<Device>::iterator itt;

	for(itt = devices.begin(); itt != devices.end(); itt++)
	{
		printf("Device Name [%s], Addr [%s]\n", itt->getName().c_str(), itt->getAddress().c_str());
	}

	return 0;
}
