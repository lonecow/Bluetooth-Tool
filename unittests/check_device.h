#ifndef __CHECK_DEVICE_H__
#define __CHECK_DEVICE_H__

#include <cxxtest/TestSuite.h>

/*
 *
 *
 *
 * YOU MUST HAVE A BLUE TOOTH ADAPTER FOR THIS TO WORK
 *
 *
 */

#include "Device.h"

class check_device : public CxxTest::TestSuite
{
public:
	inquiry_info empty_info;

	check_device()
	{
		memset(&empty_info, 0, sizeof(empty_info));
	}

	~check_device()
	{
	}

	void setUp()
	{
	}

	void tearDown()
	{
	}

	void test_add_emptyName()
	{
		Device myDevice(empty_info, "");

		TS_ASSERT_EQUALS("", myDevice.getName());
	}

	void test_return_valid_Name()
	{
		Device myDevice(empty_info, "This is valid");

		TS_ASSERT_EQUALS("This is valid", myDevice.getName());
	}

	void test_return_blank_address()
	{
		Device myDevice(empty_info, "");

		TS_ASSERT_EQUALS("00:00:00:00:00:00", myDevice.getAddress());
	}

	void test_return_valid_address()
	{
		inquiry_info info = {0};
		info.bdaddr.b[0] = 0;
		info.bdaddr.b[1] = 1;
		info.bdaddr.b[2] = 2;
		info.bdaddr.b[3] = 3;
		info.bdaddr.b[4] = 4;
		info.bdaddr.b[5] = 16;

		Device myDevice(info, "");

		TS_ASSERT_EQUALS("10:04:03:02:01:00", myDevice.getAddress());
	}
};

#endif

