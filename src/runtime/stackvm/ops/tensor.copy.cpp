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
#include "../runtime_module.h"
#include <nncase/kernels/tensor_compute.h>
#include <nncase/runtime/interpreter.h>
#include <nncase/runtime/runtime_op_utility.h>

using namespace nncase;
using namespace nncase::runtime;
using namespace nncase::runtime::stackvm;

result<void> stackvm_runtime_module::visit(const tensor_copy_op_t &op) noexcept
{
    try_var(output, pop_addr());
    try_var(input, pop_addr());
    auto &shape = shape_regs_[op.rshape];
    auto &in_strides = shape_regs_[op.rstride_src];
    auto &out_strides = shape_regs_[op.rstride_dest];

    return kernels::copy(op.datatype, reinterpret_cast<const gsl::byte *>(input), reinterpret_cast<gsl::byte *>(output), shape, in_strides, out_strides, kernel_context());
}
