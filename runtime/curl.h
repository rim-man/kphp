// Compiler for PHP (aka KPHP)
// Copyright (c) 2020 LLC «V Kontakte»
// Distributed under the GPL v3 License, see LICENSE.notice.txt

#pragma once

#include "runtime/kphp_core.h"

using curl_easy = int64_t;

curl_easy f$curl_init(const string &url = string{}) noexcept;

void f$curl_reset(curl_easy easy_id) noexcept;

bool f$curl_setopt(curl_easy easy_id, int64_t option, const mixed &value) noexcept;

bool f$curl_setopt_array(curl_easy easy_id, const array<mixed> &options) noexcept;

mixed f$curl_exec(curl_easy easy_id) noexcept;

mixed f$curl_getinfo(curl_easy easy_id, int64_t option = 0) noexcept;

string f$curl_error(curl_easy easy_id) noexcept;

int64_t f$curl_errno(curl_easy easy_id) noexcept;

void f$curl_close(curl_easy easy_id) noexcept;


using curl_multi = int64_t;

curl_multi f$curl_multi_init() noexcept;

Optional<int64_t> f$curl_multi_add_handle(curl_multi multi_id, curl_easy easy_id) noexcept;

Optional<string> f$curl_multi_getcontent(curl_easy easy_id) noexcept;

bool f$curl_multi_setopt(curl_multi multi_id, int64_t option, int64_t value) noexcept;

Optional<int64_t> f$curl_multi_exec(curl_multi multi_id, int64_t &still_running) noexcept;

Optional<int64_t> f$curl_multi_select(curl_multi multi_id, double timeout = 1.0) noexcept;

extern int64_t curl_multi_info_read_msgs_in_queue_stub;
Optional<array<int64_t>> f$curl_multi_info_read(curl_multi multi_id, int64_t &msgs_in_queue = curl_multi_info_read_msgs_in_queue_stub);

Optional<int64_t> f$curl_multi_remove_handle(curl_multi multi_id, curl_easy easy_id) noexcept;

Optional<int64_t> f$curl_multi_errno(curl_multi multi_id) noexcept;

void f$curl_multi_close(curl_multi multi_id) noexcept;

Optional<string> f$curl_multi_strerror(int64_t error_num) noexcept;

void free_curl_lib() noexcept;


