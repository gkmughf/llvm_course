#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include <fstream>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/InstrTypes.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/Casting.h>
#include <llvm/Support/raw_ostream.h>
#include <string>

using namespace llvm;

struct gen_IR_gen_pass : public PassInfoMixin<gen_IR_gen_pass> {

  std::string getFuncName(std::string name) {
    for (int i = 0; i < name.size(); ++i) {
      if (name[i] == '.')
        name[i] = '_';
    }
    return name + "Func";
  }
  std::string getFuncName(Function &F) {
    return getFuncName(F.getName().str());
  }
  void addLine(size_t tabs, std::string &out, std::string &&line) {
    out.append(std::string(tabs * 2, ' '));
    out.append(line);
    out.append("\n");
  }
  void decFunctions(Module &M, int tabs, std::string &out) {
    for (Function &F : M) {
      std::string funcType;
      std::string funcDec;

      funcType.append("FunctionType *funcType" + getFuncName(F) +
                      " = FunctionType::get(" + getCPPType(F.getReturnType()) +
                      ", ");

      if (F.arg_size() > 0) {
        funcType.append("{");
        for (auto &arg : F.args()) {
          funcType.append(getCPPType(arg.getType()) + ", ");
        }
        funcType.append("}, false);");
      } else {
        funcType.append("false);");
      }
      addLine(tabs, out, std::move(funcType));
      if (F.isDeclaration()) {
        addLine(tabs, out,
                "FunctionCallee " + getFuncName(F) +
                    " = module->getOrInsertFunction(\"" + F.getName().str() +
                    "\", funcType" + getFuncName(F) + ");");
      } else {
        addLine(tabs, out,
                "Function *" + getFuncName(F) + " = Function::Create(funcType" +
                    getFuncName(F) + ", Function::ExternalLinkage, \"" +
                    F.getName().str() + "\", module);");
      }
    }
  }
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {

    std::string head;
    std::string body;
    std::string tail;
    addLine(0, head, "#include \"sim.h\"");
    addLine(0, head, "#include \"llvm/ExecutionEngine/ExecutionEngine.h\"\n");
    addLine(0, head, "#include \"llvm/ExecutionEngine/GenericValue.h\"\n");
    addLine(0, head, "#include \"llvm/IR/IRBuilder.h\"");
    addLine(0, head, "#include \"llvm/IR/Module.h\"");
    addLine(0, head, "#include \"llvm/IR/LLVMContext.h\"");
    addLine(0, head, "#include \"llvm/Support/raw_ostream.h\"");
    addLine(0, head, "#include \"llvm/Support/TargetSelect.h\"");
    addLine(0, head, "#include \"llvm/IR/DerivedTypes.h\"");
    addLine(0, head, "using namespace llvm;");
    addLine(0, head, "");
    addLine(0, head, "");
    addLine(0, head, "int main() {");
    addLine(1, head, "LLVMContext context;");
    addLine(1, head, "Module *module = new Module(\"app.c\", context);");
    addLine(1, head, "IRBuilder<> builder(context);");
    addLine(0, head, "");
    addLine(0, head, "");
    decFunctions(M, 1, body);
    for (Function &F : M) {
      generateCPPForFunction(F, 1, body);
    }

    addLine(1, tail, "// LLVM IR Interpreter\n");
    addLine(1, tail, "module->print(outs(), nullptr);\n");
    addLine(1, tail, "outs() << \"[EE] Run\\n\";\n");
    addLine(1, tail, "InitializeNativeTarget();\n");
    addLine(1, tail, "InitializeNativeTargetAsmPrinter();\n");
    addLine(1, tail,
            "ExecutionEngine *ee = "
            "EngineBuilder(std::unique_ptr<Module>(module)).create();");
    addLine(1, tail,
            "ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> "
            "void * {");
    addLine(2, tail, "if (fnName == \"simPutPixel\") {");
    addLine(3, tail, "return reinterpret_cast<void *>(simPutPixel);");
    addLine(2, tail, "}");
    addLine(2, tail, "if (fnName == \"simFlush\") {");
    addLine(3, tail, "return reinterpret_cast<void *>(simFlush);");
    addLine(2, tail, "}");
    addLine(2, tail, "if (fnName == \"simRand\") {");
    addLine(3, tail, "return reinterpret_cast<void *>(simRand);");
    addLine(2, tail, "}");
    addLine(2, tail, "if (fnName == \"simClear\") {");
    addLine(3, tail, "return reinterpret_cast<void *>(simClear);");
    addLine(2, tail, "}");
    addLine(2, tail, "return nullptr;");
    addLine(1, tail, "});");
    addLine(1, tail, "ee->finalizeObject();");
    addLine(1, tail, "simInit();");
    addLine(1, tail, "ArrayRef<GenericValue> noargs;");
    addLine(1, tail, "GenericValue v = ee->runFunction(appFunc, noargs);");
    addLine(1, tail, "outs() << \"[EE] Result: \" << v.IntVal << \"\\n\";");
    addLine(1, tail, "simExit();");
    addLine(1, tail, "return EXIT_SUCCESS;");
    addLine(1, tail, "return 0;");
    addLine(0, tail, "}");

    std::ofstream outFile("generated_ir_gen.cpp");
    outFile << head << "\n\n" << body << "\n\n" << tail;
    outFile.close();

    return PreservedAnalyses::none();
  }

  std::string getOperandName(Value *v) {
    std::string str;
    raw_string_ostream OS(str);
    v->printAsOperand(OS, false);
    if (str[0] == '%') {
      return "v" + str.substr(1);
    }
    Type *t = v->getType();
    if (t->isIntegerTy(1)) {
      return "builder.getInt1(" + str + ")";
    }
    if (t->isIntegerTy(8)) {
      return "builder.getInt8(" + str + ")";
    }
    if (t->isIntegerTy(16)) {
      return "builder.getInt16(" + str + ")";
    }
    if (t->isIntegerTy(32)) {
      return "builder.getInt32(" + str + ")";
    }
    if (t->isIntegerTy(64)) {
      return "builder.getInt64(" + str + ")";
    }
    return str;
  }

  void generateCPPForFunction(Function &F, int tabs, std::string &out) {
    if (F.isDeclaration())
      return;
    addLine(tabs, out, "");
    addLine(tabs, out, "");
    addLine(tabs, out, "// Генерация функции: " + F.getName().str());
    addLine(tabs, out, "{");
    tabs++;
    int ii = 0;
    for (auto &arg : F.args()) {
      addLine(tabs, out,
              "Value *v" + std::to_string(ii) + " = " + F.getName().str() +
                  "Func" + "->getArg(" + std::to_string(ii) + ");");
      ++ii;
    }
    for (BasicBlock &BB : F) {
      std::string str = getOperandName(&BB);
      addLine(tabs, out,
              "BasicBlock *" + str + " = BasicBlock::Create(context, \"\", " +
                  getFuncName(BB.getParent()->getName().str()) + ");");
    }
    out.append("\n\n");
    std::vector<PHINode *> phis;
    for (BasicBlock &BB : F) {
      generateCPPForBasicBlock(BB, tabs, out, phis);
    }
    for (auto &phiInst : phis) {
      for (unsigned i = 0; i < phiInst->getNumIncomingValues(); ++i) {
        std::string incomingValueName =
            getOperandName(phiInst->getIncomingValue(i));
        std::string incomingBlockName =
            getOperandName(phiInst->getIncomingBlock(i));

        addLine(tabs, out,
                getOperandName(phiInst) + "->addIncoming(" + incomingValueName +
                    ", " + incomingBlockName + ");");
      }
    }

    tabs--;
    addLine(tabs, out, "}");
  }

  void generateCPPForBasicBlock(BasicBlock &BB, int tabs, std::string &out,
                                std::vector<PHINode *> &phis) {
    addLine(tabs, out, "builder.SetInsertPoint(" + getOperandName(&BB) + ");");
    for (Instruction &I : BB) {
      generateCPPForInstruction(I, tabs, out, phis);
    }
    out.append("\n\n");
  }
  void generateCPPForInstruction(Instruction &I, int tabs, std::string &out,
                                 std::vector<PHINode *> &phis) {
    if (auto *callInst = dyn_cast<CallInst>(&I)) {
      addLine(tabs, out,
              "// Вызов функции: " +
                  callInst->getCalledFunction()->getName().str());
      std::string tmpstr(
          "builder.CreateCall(" +
          getFuncName(callInst->getCalledFunction()->getName().str()) + ", {");
      for (unsigned i = 0; i < callInst->arg_size(); ++i) {
        tmpstr.append(getOperandName(callInst->getArgOperand(i)) + ", ");
      }
      tmpstr.append("});");
      if (!callInst->getType()->isVoidTy() && !callInst->use_empty()) {
        addLine(tabs, out,
                "Value *" + getOperandName(callInst) + " = " + tmpstr);
      } else {
        addLine(tabs, out, std::move(tmpstr));
      }

    } else if (auto *icmpInst = dyn_cast<ICmpInst>(&I)) {
      addLine(tabs, out,
              "Value *" + getOperandName(icmpInst) + " = builder.CreateICmp(" +
                  "static_cast<CmpInst::Predicate>(" +
                  std::to_string(icmpInst->getPredicate()) + "), " +
                  getOperandName(icmpInst->getOperand(0)) + ", " +
                  getOperandName(icmpInst->getOperand(1)) + ");");
    } else if (auto *binOp = dyn_cast<BinaryOperator>(&I)) {
      std::string op;
      switch (binOp->getOpcode()) {
      case Instruction::Add:
        op = "CreateAdd";
        break;
      case Instruction::Sub:
        op = "CreateSub";
        break;
      case Instruction::Mul:
        op = "CreateMul";
        break;
      case Instruction::UDiv:
        op = "CreateUDiv";
        break;
      case Instruction::SDiv:
        op = "CreateSDiv";
        break;
      case Instruction::And:
        op = "CreateAnd";
        break;
      case Instruction::Or:
        op = "CreateOr";
        break;
      case Instruction::Xor:
        op = "CreateXor";
        break;
      case Instruction::Shl:
        op = "CreateShl";
        break;
      case Instruction::LShr:
        op = "CreateLShr";
        break;
      case Instruction::AShr:
        op = "CreateAShr";
        break;
      case Instruction::SRem:
        op = "CreateSRem";
        break;
      default:
        op = "IDONTKNOW";
        break;
      }
      addLine(tabs, out,
              "Value *" + getOperandName(binOp) + " = builder." + op + "(" +
                  getOperandName(binOp->getOperand(0)) + ", " +
                  getOperandName(binOp->getOperand(1)) + ");");
    } else if (auto *phiInst = dyn_cast<PHINode>(&I)) {
      addLine(tabs, out,
              "PHINode *" + getOperandName(phiInst) + " = builder.CreatePHI(" +
                  getCPPType(phiInst->getType()) + ", " +
                  std::to_string(phiInst->getNumIncomingValues()) + ");");

      phis.push_back(phiInst);
    } else if (auto *selectInst = dyn_cast<SelectInst>(&I)) {
      addLine(tabs, out,
              "Value *" + getOperandName(selectInst) +
                  " = builder.CreateSelect(" +
                  getOperandName(selectInst->getCondition()) + ", " +
                  getOperandName(selectInst->getTrueValue()) + ", " +
                  getOperandName(selectInst->getFalseValue()) + ");");
    } else if (auto *branchInst = dyn_cast<BranchInst>(&I)) {
      if (branchInst->isConditional()) {
        addLine(tabs, out,
                "builder.CreateCondBr(" +
                    getOperandName(branchInst->getCondition()) + ", " +
                    getOperandName(branchInst->getSuccessor(0)) + ", " +
                    getOperandName(branchInst->getSuccessor(1)) + ");");
      } else {
        addLine(tabs, out,
                "  builder.CreateBr(" +
                    getOperandName(branchInst->getSuccessor(0)) + ");");
      }
    } else if (auto *retInst = dyn_cast<ReturnInst>(&I)) {
      if (retInst->getNumOperands() > 0) {
        addLine(tabs, out,
                "builder.CreateRet(" +
                    getOperandName(retInst->getReturnValue()) + ");");
      } else {
        addLine(tabs, out, "builder.CreateRetVoid();");
      }
    } else if (auto *loadInst = dyn_cast<LoadInst>(&I)) {
      addLine(tabs, out,
              "Value *" + getOperandName(loadInst) +
                  " = builder.CreateAlignedLoad(" +
                  getCPPType(loadInst->getType()) + ", " +
                  getOperandName(loadInst->getPointerOperand()) +
                  ", MaybeAlign(" +
                  std::to_string(loadInst->getAlign().value()) + "));");
    } else if (auto *storeInst = dyn_cast<StoreInst>(&I)) {
      addLine(tabs, out,
              "builder.CreateAlignedStore(" +
                  getOperandName(storeInst->getValueOperand()) + ", " +
                  getOperandName(storeInst->getPointerOperand()) +
                  ", MaybeAlign(" +
                  std::to_string(storeInst->getAlign().value()) + "));");
    } else if (auto *allocaInst = dyn_cast<AllocaInst>(&I)) {
      addLine(tabs, out,
              "Value *" + getOperandName(allocaInst) +
                  " = builder.CreateAlloca(" +
                  getCPPType(allocaInst->getAllocatedType()) + ");");
    } else if (auto *gepInst = dyn_cast<GetElementPtrInst>(&I)) {
      std::string tmpstr = "Value *" + getOperandName(gepInst) +
                           " = GetElementPtrInst::Create(" +
                           getCPPType(gepInst->getSourceElementType()) + "," +
                           getOperandName(gepInst->getPointerOperand()) + ", {";

      for (unsigned i = 1; i < gepInst->getNumOperands(); ++i) {
        tmpstr.append(getOperandName(gepInst->getOperand(i)) + ", ");
      }
      tmpstr.append("});");
      addLine(tabs, out, std::move(tmpstr));
      addLine(tabs, out, "builder.Insert(" + getOperandName(gepInst) + ");");
    } else if (auto *truncInst = dyn_cast<TruncInst>(&I)) {
      addLine(tabs, out,
              "Value *" + getOperandName(truncInst) +
                  " = builder.CreateTrunc(" +
                  getOperandName(truncInst->getOperand(0)) + ", " +
                  getCPPType(truncInst->getType()) + ");");
    } else if (auto *zextInst = dyn_cast<ZExtInst>(&I)) {
      addLine(tabs, out,
              "Value *" + getOperandName(zextInst) + " = builder.CreateZExt(" +
                  getOperandName(zextInst->getOperand(0)) + ", " +
                  getCPPType(zextInst->getType()) + ");");
    } else if (auto *sextInst = dyn_cast<SExtInst>(&I)) {
      addLine(tabs, out,
              "Value *" + getOperandName(sextInst) + " = builder.CreateSExt(" +
                  getOperandName(sextInst->getOperand(0)) + ", " +
                  getCPPType(sextInst->getDestTy()) + ");");

    } else {
      addLine(tabs, out, "errr " + std::string(I.getOpcodeName()));
    }
  }
  std::string getCPPType(Type *T) {
    if (T->isVoidTy()) {
      return "Type::getVoidTy(context)";
    } else if (T->isIntegerTy(1)) {
      return "Type::getInt1Ty(context)";
    } else if (T->isIntegerTy(16)) {
      return "Type::getInt16Ty(context)";
    } else if (T->isIntegerTy(32)) {
      return "Type::getInt32Ty(context)";
    } else if (T->isIntegerTy(64)) {
      return "Type::getInt64Ty(context)";
    } else if (T->isArrayTy()) {
      ArrayType *arrayType = dyn_cast<ArrayType>(T);
      Type *elementType = arrayType->getElementType();
      uint64_t numElements = arrayType->getArrayNumElements();

      return "ArrayType::get(" + getCPPType(elementType) + ", " +
             std::to_string(numElements) + ")";
    } else if (T->isPointerTy()) {
      if (T->getPointerAddressSpace() == 0)
        return "PointerType::get(context, 0)";
    }
    std::string str;
    raw_string_ostream OS(str);
    T->print(OS, false);
    return "getUnknownTy - " + str;
  }
};

PassPluginLibraryInfo getPassPluginInfo() {
  const auto callback = [](PassBuilder &PB) {
    PB.registerOptimizerLastEPCallback([&](ModulePassManager &MPM, auto) {
      MPM.addPass(gen_IR_gen_pass{});
      return true;
    });
  };
  return {LLVM_PLUGIN_API_VERSION, "MyPlugin", "0.0.1", callback};
}

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return getPassPluginInfo();
}
