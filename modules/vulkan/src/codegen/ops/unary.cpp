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
#include "../module_builder.h"
#include "../templates/template.h"

using namespace nncase;
using namespace nncase::codegen;
using namespace nncase::codegen::vulkan;
using namespace nncase::ir;
using namespace nncase::runtime;
using namespace nncase::runtime::vulkan;
using namespace nlohmann;

void vulkan_module_builder::emit([[maybe_unused]] unary &node)
{
    json ctx;
    ctx["unary_op"] = unary_op_to_string(node.unary_op());
    auto shader = render_and_compile("unary.hlsl", ctx);

    throw std::runtime_error("not implemented");
}
