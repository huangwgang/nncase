/* Copyright 2019-2021 Canaan Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "template.h"
#include <fmt/format.h>
#include <libzippp/libzippp.h>
#include <span>
#include <system_error>

using namespace libzippp;

#if _MSC_VER
#include "resource.h"
#include <Windows.h>

#define THROW_WIN32_IF_NOT(x, fmt_str, ...)                                                                    \
    if (!(x))                                                                                                  \
    {                                                                                                          \
        auto err_code = GetLastError();                                                                        \
        auto err_msg = std::system_category().message(err_code);                                               \
        throw std::system_error(err_code, std::system_category(), fmt::format(fmt_str, err_msg, __VA_ARGS__)); \
    }

namespace
{
struct xz_res
{
    std::span<const uint8_t> data;

    xz_res()
    {
        auto hres = FindResourceW(nullptr, MAKEINTRESOURCEW(IDR_VULKAN_TEMPLATES), L"Binary");
        THROW_WIN32_IF_NOT(hres, "Cannot find resource: {}", "Vulkan Templates");
        auto size = SizeofResource(nullptr, hres);
        auto hmem = LoadResource(nullptr, hres);
        THROW_WIN32_IF_NOT(hmem, "Cannot load resource: {}", "Vulkan Templates");
        auto res_data = LockResource(hmem);
        data = { reinterpret_cast<const uint8_t *>(res_data), (size_t)size };
    }
};
}
#else
#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#include "incbin.h"
INCBIN(templates_xz, "vulkan_templates_xz.xz");

namespace
{
struct xz_res
{
    std::span<const uint8_t> data;

    xz_res()
    {
        data = { reinterpret_cast<const uint8_t *>(gtemplates_xz_data), (size_t)gtemplates_xz_size };
    }
};
}
#endif

namespace
{
class xz_reader
{
public:
    xz_reader()
        : archive_(ZipArchive::fromBuffer(xz_res_.data.data(),
            (libzippp_uint32)xz_res_.data.size(), ZipArchive::ReadOnly, true))
    {
        if (!archive_)
            throw std::runtime_error("Load vulkan templates archive failed");
    }

private:
    xz_res xz_res_;
    std::unique_ptr<ZipArchive> archive_;
};
}
