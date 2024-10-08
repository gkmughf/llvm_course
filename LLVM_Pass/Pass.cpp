#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

struct MyModPass : public PassInfoMixin<MyModPass> {
  bool isFuncLogger(StringRef name) { return name == "instructionLogger"; }
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {

    for (auto &F : M) {

      if (F.isDeclaration() || isFuncLogger(F.getName()))
        continue;

      LLVMContext &Ctx = F.getContext();
      IRBuilder<> builder(Ctx);
      Type *retType = Type::getVoidTy(Ctx);

      ArrayRef<Type *> ILoggerParamTypes = {
          builder.getInt8Ty()->getPointerTo(),
          builder.getInt8Ty()->getPointerTo()};
      FunctionType *IloggerFuncType =
          FunctionType::get(retType, ILoggerParamTypes, false);
      FunctionCallee ILoggerFunc =
          M.getOrInsertFunction("instructionLogger", IloggerFuncType);

      for (auto &B : F) {
        for (auto &I : B) {
          if (isa<PHINode>(&I)) {
            continue;
          }
          builder.SetInsertPoint(&I);
          Value *instructionName =
              builder.CreateGlobalStringPtr(I.getOpcodeName());
          for (auto &U : I.operands()) {
            if (auto *useI = dyn_cast<Instruction>(U.get())) {
              Value *operandName =
                  builder.CreateGlobalStringPtr(useI->getOpcodeName());
              Value *args[] = {instructionName, operandName};
              builder.CreateCall(ILoggerFunc, args);
            }
          }
        }
      }
    }

    return PreservedAnalyses::none();
  }
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerOptimizerLastEPCallback([&](ModulePassManager &MPM, auto) {
      MPM.addPass(MyModPass{});
      return true;
    });
  };
  return {LLVM_PLUGIN_API_VERSION, "MyPlugin", "0.0.1", callback};
}

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}
