// SPDX-License-Identifier: BSD-3-Clause
/* Copyright 2020-2021, Intel Corporation */

#include "unittest.hpp"

using namespace pmem::kv;

static void insert(pmem::kv::db &kv)
{
	ASSERT_STATUS(kv.put(entry_from_string("tmpkey"), entry_from_string("tmpvalue1")),
		      status::OK);
}

static void check(pmem::kv::db &kv)
{
	std::string key = entry_from_string("tmpkey");
	ASSERT_STATUS(kv.remove(key), status::OK);
	std::string value;
	ASSERT_STATUS(kv.get(key, &value), status::NOT_FOUND);
}

static void test(int argc, char *argv[])
{
	if (argc < 4)
		UT_FATAL("usage: %s engine json_config insert/check", argv[0]);

	std::string mode = argv[3];
	if (mode != "insert" && mode != "check")
		UT_FATAL("usage: %s engine json_config insert/check", argv[0]);

	auto kv = INITIALIZE_KV(argv[1], CONFIG_FROM_JSON(argv[2]));

	if (mode == "insert") {
		insert(kv);
	} else {
		check(kv);
	}

	kv.close();
}

int main(int argc, char *argv[])
{
	return run_test([&] { test(argc, argv); });
}
