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
#include <nncase/ir/op_utils.h>
#include <nncase/ir/ops/take.h>
#include <xtensor/xarray.hpp>

using namespace nncase;
using namespace nncase::ir;

take::take(datatype_t type, shape_t input_shape, shape_t indices_shape, shape_t output_shape, int32_t axis, std::string mode)
    : axis_(axis)
    , mode_(mode)
{
    add_input("input", type, input_shape);
    add_input("indices", dt_int32, indices_shape);
    add_output("output", type, output_shape);
}

bool take::properties_equal(node &other) const
{
    auto &r = static_cast<take &>(other);
    return axis() == r.axis() && mode() == r.mode();
}
