/*
 * Copyright (c) [2019] Huawei Technologies Co.,Ltd.All rights reverved.
 *
 * OpenArkCompiler is licensed under the Mulan PSL v1. 
 * You can use this software according to the terms and conditions of the Mulan PSL v1.
 * You may obtain a copy of Mulan PSL v1 at:
 *
 * 	http://license.coscl.org.cn/MulanPSL 
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
 * FIT FOR A PARTICULAR PURPOSE.  
 * See the Mulan PSL v1 for more details.  
 */
#ifndef MAPLE_ME_INCLUDE_ME_DOMINANCE_H
#define MAPLE_ME_INCLUDE_ME_DOMINANCE_H
#include "dominance.h"
#include "me_function.h"
#include "me_phase.h"

namespace maple {
class MeDoDominance : public MeFuncPhase {
 public:
  explicit MeDoDominance(MePhaseID id) : MeFuncPhase(id) {}

  virtual ~MeDoDominance() = default;
  AnalysisResult *Run(MeFunction *func, MeFuncResultMgr *m, ModuleResultMgr *mrm) override;
  std::string PhaseName() const override {
    return "dominance";
  }
};

}  // namespace maple
#endif
