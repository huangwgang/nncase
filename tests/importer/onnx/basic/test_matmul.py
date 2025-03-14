# Copyright 2019-2021 Canaan Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# pylint: disable=invalid-name, unused-argument, import-outside-toplevel

import pytest
import torch
from onnx_test_runner import OnnxTestRunner


def _make_module(shape):

    class MatmulModule(torch.nn.Module):
        def __init__(self):
            super(MatmulModule, self).__init__()
            self.y = torch.randn(*shape)

        def forward(self, x):
            x = torch.matmul(x, self.y)

            return x

    return MatmulModule()


in_shapes = [
    [[1, 2], [2, 1]],
    [[3, 4], [4, 5]]
]


@pytest.mark.parametrize('in_shape', in_shapes)
def test_matmul(in_shape, request):
    module = _make_module(in_shape[1])

    runner = OnnxTestRunner(request.node.name)
    model_file = runner.from_torch(module, in_shape[0])
    runner.run(model_file)


if __name__ == "__main__":
    pytest.main(['-vv', 'test_matmul.py'])
