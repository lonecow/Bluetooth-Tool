#ifndef __CHECK_SOCKET_H__
#define __CHECK_SOCKET_H__

#include <cxxtest/TestSuite.h>

/*
 *
 *
 *
 * YOU MUST HAVE A BLUE TOOTH ADAPTER FOR THIS TO WORK
 *
 *
 */

#include "Adapter.h"

class check_adapter : public CxxTest::TestSuite
{
public:
	bdaddr_t bad_address;

	check_adapter()
	{
		bad_address.b[0] = 1;
		bad_address.b[1] = 1;
		bad_address.b[2] = 1;
		bad_address.b[3] = 1;
		bad_address.b[4] = 1;
		bad_address.b[5] = 1;
	}

	~check_adapter()
	{
	}

	void setUp()
	{
	}

	void tearDown()
	{
	}

	void test_found_default_adapter()
	{
		Adapter test_adapter;

		TS_ASSERT_EQUALS(true, test_adapter.isAttached())
	}

	void test_getAdapterName()
	{
		Adapter test_adapter;
		TS_ASSERT_DIFFERS(std::string(""), test_adapter.getName());
	}

	void test_getAdapterAddress()
	{
		Adapter test_adapter;
		TS_ASSERT_DIFFERS(std::string(""), test_adapter.getAddress());
	}

	void test_bad_adapter_doesnt_work()
	{
		Adapter test_adapter(std::string("01:01:01:01:01:01"));
		TS_ASSERT_EQUALS(false, test_adapter.isAttached())
	}

	void test_bad_adapter_blank_address()
	{
		Adapter test_adapter(std::string("01:01:01:01:01:01"));
		TS_ASSERT_EQUALS(std::string(""), test_adapter.getAddress());
	}

	void test_bad_adapter_blank_name()
	{
		Adapter test_adapter(std::string("01:01:01:01:01:01"));
		TS_ASSERT_EQUALS(std::string(""), test_adapter.getName());
	}
};

#endif /* __CHECK_SOCKET_H__ */

