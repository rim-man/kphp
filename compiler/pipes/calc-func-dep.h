// Compiler for PHP (aka KPHP)
// Copyright (c) 2020 LLC «V Kontakte»
// Distributed under the GPL v3 License, see LICENSE.notice.txt

#pragma once

#include <vector>

#include "common/mixin/movable_only.h"

#include "compiler/function-pass.h"

struct DepData : private vk::movable_only {
  std::vector<FunctionPtr> dep;
  std::vector<VarPtr> used_global_vars;

  std::vector<VarPtr> used_ref_vars;
  std::vector<std::pair<VarPtr, VarPtr>> ref_ref_edges;
  std::vector<std::pair<VarPtr, VarPtr>> global_ref_edges;

  std::vector<FunctionPtr> forks;
};

static_assert(std::is_nothrow_move_constructible<DepData>::value, "DepData should be movable");
static_assert(!std::is_copy_constructible<DepData>::value, "DepData shouldn't be copyable");

class CalcFuncDepPass final : public FunctionPassBase {
private:
  DepData data;
  std::vector<FunctionPtr> calls;
public:

  string get_description() override {
    return "Calc function dependencies";
  }

  bool check_function(FunctionPtr function) const override {
    return !function->is_extern();
  }

  VertexPtr on_enter_vertex(VertexPtr vertex) override;
  VertexPtr on_exit_vertex(VertexPtr vertex) override;

  DepData get_data();
};
