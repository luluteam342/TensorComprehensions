/**
 * Copyright (c) 2017-present, Facebook, Inc.
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
#pragma once

#include <string>
#include <vector>

#include "tc/c2/tc_op.h"
#include "tc/library/dper_lut_concat.h"

namespace caffe2 {

template <typename T, class Context, class Engine = caffe2::DefaultEngine>
class TcDperLutConcatOp : public TcOp<T, Context, Engine> {
 public:
  static constexpr auto description = tc::TC_DPER_LUT_CONCAT;

  TcDperLutConcatOp(
      const caffe2::OperatorDef& operator_def,
      caffe2::Workspace* ws)
      : TcOp<T, Context, Engine>(operator_def, ws) {
    this->tc_ = tc::TC_DPER_LUT_CONCAT;
    this->tc_name_ = tc::TC_DPER_LUT_CONCAT_NAME;
  }

  ~TcDperLutConcatOp() override {}

 protected:
  void SetupNaiveMappingOptions() override {
    this->mapping_options_.tile(1)
        .mapToThreads(128)
        .mapToBlocks(32)
        .unroll(1)
        .useSharedMemory(false)
        .usePrivateMemory(false);
  }
};
} // namespace caffe2
