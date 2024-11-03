#include "sim.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"

#include "llvm/ExecutionEngine/GenericValue.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/IR/DerivedTypes.h"
using namespace llvm;


int main() {
  LLVMContext context;
  Module *module = new Module("app.c", context);
  IRBuilder<> builder(context);




  FunctionType *funcTypefixed_mulFunc = FunctionType::get(Type::getInt32Ty(context), {Type::getInt32Ty(context), Type::getInt32Ty(context), }, false);
  Function *fixed_mulFunc = Function::Create(funcTypefixed_mulFunc, Function::ExternalLinkage, "fixed_mul", module);
  FunctionType *funcTypefixed_divFunc = FunctionType::get(Type::getInt32Ty(context), {Type::getInt32Ty(context), Type::getInt32Ty(context), }, false);
  Function *fixed_divFunc = Function::Create(funcTypefixed_divFunc, Function::ExternalLinkage, "fixed_div", module);
  FunctionType *funcTypefixed_sqrtFunc = FunctionType::get(Type::getInt32Ty(context), {Type::getInt32Ty(context), }, false);
  Function *fixed_sqrtFunc = Function::Create(funcTypefixed_sqrtFunc, Function::ExternalLinkage, "fixed_sqrt", module);
  FunctionType *funcTypellvm_lifetime_start_p0Func = FunctionType::get(Type::getVoidTy(context), {Type::getInt64Ty(context), PointerType::get(context, 0), }, false);
  FunctionCallee llvm_lifetime_start_p0Func = module->getOrInsertFunction("llvm.lifetime.start.p0", funcTypellvm_lifetime_start_p0Func);
  FunctionType *funcTypellvm_lifetime_end_p0Func = FunctionType::get(Type::getVoidTy(context), {Type::getInt64Ty(context), PointerType::get(context, 0), }, false);
  FunctionCallee llvm_lifetime_end_p0Func = module->getOrInsertFunction("llvm.lifetime.end.p0", funcTypellvm_lifetime_end_p0Func);
  FunctionType *funcTypeswap_iFunc = FunctionType::get(Type::getVoidTy(context), {PointerType::get(context, 0), PointerType::get(context, 0), }, false);
  Function *swap_iFunc = Function::Create(funcTypeswap_iFunc, Function::ExternalLinkage, "swap_i", module);
  FunctionType *funcTypeclampFunc = FunctionType::get(Type::getInt32Ty(context), {Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context), }, false);
  Function *clampFunc = Function::Create(funcTypeclampFunc, Function::ExternalLinkage, "clamp", module);
  FunctionType *funcTypeabsFunc = FunctionType::get(Type::getInt32Ty(context), {Type::getInt32Ty(context), }, false);
  Function *absFunc = Function::Create(funcTypeabsFunc, Function::ExternalLinkage, "abs", module);
  FunctionType *funcTypedraw_lineFunc = FunctionType::get(Type::getVoidTy(context), {Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context), }, false);
  Function *draw_lineFunc = Function::Create(funcTypedraw_lineFunc, Function::ExternalLinkage, "draw_line", module);
  FunctionType *funcTypellvm_abs_i32Func = FunctionType::get(Type::getInt32Ty(context), {Type::getInt32Ty(context), Type::getInt1Ty(context), }, false);
  FunctionCallee llvm_abs_i32Func = module->getOrInsertFunction("llvm.abs.i32", funcTypellvm_abs_i32Func);
  FunctionType *funcTypesimPutPixelFunc = FunctionType::get(Type::getVoidTy(context), {Type::getInt32Ty(context), Type::getInt32Ty(context), Type::getInt32Ty(context), }, false);
  FunctionCallee simPutPixelFunc = module->getOrInsertFunction("simPutPixel", funcTypesimPutPixelFunc);
  FunctionType *funcTypeswapFunc = FunctionType::get(Type::getVoidTy(context), {Type::getInt32Ty(context), Type::getInt32Ty(context), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), }, false);
  Function *swapFunc = Function::Create(funcTypeswapFunc, Function::ExternalLinkage, "swap", module);
  FunctionType *funcTypeinit_particleFunc = FunctionType::get(Type::getVoidTy(context), {Type::getInt32Ty(context), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), }, false);
  Function *init_particleFunc = Function::Create(funcTypeinit_particleFunc, Function::ExternalLinkage, "init_particle", module);
  FunctionType *funcTypesimRandFunc = FunctionType::get(Type::getInt32Ty(context), false);
  FunctionCallee simRandFunc = module->getOrInsertFunction("simRand", funcTypesimRandFunc);
  FunctionType *funcTypedelete_particleFunc = FunctionType::get(Type::getVoidTy(context), {Type::getInt32Ty(context), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), }, false);
  Function *delete_particleFunc = Function::Create(funcTypedelete_particleFunc, Function::ExternalLinkage, "delete_particle", module);
  FunctionType *funcTypeinit_particlesFunc = FunctionType::get(Type::getVoidTy(context), {PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), }, false);
  Function *init_particlesFunc = Function::Create(funcTypeinit_particlesFunc, Function::ExternalLinkage, "init_particles", module);
  FunctionType *funcTypeupdate_particlesFunc = FunctionType::get(Type::getVoidTy(context), {PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), }, false);
  Function *update_particlesFunc = Function::Create(funcTypeupdate_particlesFunc, Function::ExternalLinkage, "update_particles", module);
  FunctionType *funcTypeget_velocity_sqFunc = FunctionType::get(Type::getInt32Ty(context), {Type::getInt32Ty(context), PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), }, false);
  Function *get_velocity_sqFunc = Function::Create(funcTypeget_velocity_sqFunc, Function::ExternalLinkage, "get_velocity_sq", module);
  FunctionType *funcTypedisplay_particlesFunc = FunctionType::get(Type::getVoidTy(context), {PointerType::get(context, 0), PointerType::get(context, 0), PointerType::get(context, 0), }, false);
  Function *display_particlesFunc = Function::Create(funcTypedisplay_particlesFunc, Function::ExternalLinkage, "display_particles", module);
  FunctionType *funcTypesimClearFunc = FunctionType::get(Type::getVoidTy(context), {Type::getInt32Ty(context), }, false);
  FunctionCallee simClearFunc = module->getOrInsertFunction("simClear", funcTypesimClearFunc);
  FunctionType *funcTypesimFlushFunc = FunctionType::get(Type::getVoidTy(context), false);
  FunctionCallee simFlushFunc = module->getOrInsertFunction("simFlush", funcTypesimFlushFunc);
  FunctionType *funcTypeappFunc = FunctionType::get(Type::getVoidTy(context), false);
  Function *appFunc = Function::Create(funcTypeappFunc, Function::ExternalLinkage, "app", module);
  FunctionType *funcTypellvm_smax_i32Func = FunctionType::get(Type::getInt32Ty(context), {Type::getInt32Ty(context), Type::getInt32Ty(context), }, false);
  FunctionCallee llvm_smax_i32Func = module->getOrInsertFunction("llvm.smax.i32", funcTypellvm_smax_i32Func);
  FunctionType *funcTypellvm_smin_i32Func = FunctionType::get(Type::getInt32Ty(context), {Type::getInt32Ty(context), Type::getInt32Ty(context), }, false);
  FunctionCallee llvm_smin_i32Func = module->getOrInsertFunction("llvm.smin.i32", funcTypellvm_smin_i32Func);
  
  
  // Генерация функции: fixed_mul
  {
    Value *v0 = fixed_mulFunc->getArg(0);
    Value *v1 = fixed_mulFunc->getArg(1);
    BasicBlock *v2 = BasicBlock::Create(context, "", fixed_mulFunc);


    builder.SetInsertPoint(v2);
    Value *v3 = builder.CreateSExt(v0, Type::getInt64Ty(context));
    Value *v4 = builder.CreateSExt(v1, Type::getInt64Ty(context));
    Value *v5 = builder.CreateMul(v4, v3);
    Value *v6 = builder.CreateLShr(v5, builder.getInt64(10));
    Value *v7 = builder.CreateTrunc(v6, Type::getInt32Ty(context));
    builder.CreateRet(v7);


  }
  
  
  // Генерация функции: fixed_div
  {
    Value *v0 = fixed_divFunc->getArg(0);
    Value *v1 = fixed_divFunc->getArg(1);
    BasicBlock *v2 = BasicBlock::Create(context, "", fixed_divFunc);


    builder.SetInsertPoint(v2);
    Value *v3 = builder.CreateSExt(v0, Type::getInt64Ty(context));
    Value *v4 = builder.CreateShl(v3, builder.getInt64(10));
    Value *v5 = builder.CreateSExt(v1, Type::getInt64Ty(context));
    Value *v6 = builder.CreateSDiv(v4, v5);
    Value *v7 = builder.CreateTrunc(v6, Type::getInt32Ty(context));
    builder.CreateRet(v7);


  }
  
  
  // Генерация функции: fixed_sqrt
  {
    Value *v0 = fixed_sqrtFunc->getArg(0);
    BasicBlock *v1 = BasicBlock::Create(context, "", fixed_sqrtFunc);
    BasicBlock *v3 = BasicBlock::Create(context, "", fixed_sqrtFunc);
    BasicBlock *v7 = BasicBlock::Create(context, "", fixed_sqrtFunc);
    BasicBlock *v9 = BasicBlock::Create(context, "", fixed_sqrtFunc);
    BasicBlock *v22 = BasicBlock::Create(context, "", fixed_sqrtFunc);
    BasicBlock *v24 = BasicBlock::Create(context, "", fixed_sqrtFunc);


    builder.SetInsertPoint(v1);
    Value *v2 = builder.CreateICmp(static_cast<CmpInst::Predicate>(40), v0, builder.getInt32(1));
    builder.CreateCondBr(v2, v24, v3);


    builder.SetInsertPoint(v3);
    PHINode *v4 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    Value *v5 = builder.CreateICmp(static_cast<CmpInst::Predicate>(38), v4, v0);
    Value *v6 = builder.CreateLShr(v4, builder.getInt32(2));
    builder.CreateCondBr(v5, v3, v7);


    builder.SetInsertPoint(v7);
    Value *v8 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v4, builder.getInt32(0));
    builder.CreateCondBr(v8, v24, v9);


    builder.SetInsertPoint(v9);
    PHINode *v10 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    PHINode *v11 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    PHINode *v12 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    Value *v13 = builder.CreateAdd(v10, v11);
    Value *v14 = builder.CreateICmp(static_cast<CmpInst::Predicate>(40), v12, v13);
    Value *v15 = builder.CreateAShr(v11, builder.getInt32(1));
    Value *v16 = builder.CreateSelect(v14, builder.getInt32(0), v13);
    Value *v17 = builder.CreateSub(v12, v16);
    Value *v18 = builder.CreateSelect(v14, builder.getInt32(0), v10);
    Value *v19 = builder.CreateAdd(v18, v15);
    Value *v20 = builder.CreateLShr(v10, builder.getInt32(2));
    Value *v21 = builder.CreateICmp(static_cast<CmpInst::Predicate>(36), v10, builder.getInt32(4));
    builder.CreateCondBr(v21, v22, v9);


    builder.SetInsertPoint(v22);
    Value *v23 = builder.CreateShl(v19, builder.getInt32(5));
      builder.CreateBr(v24);


    builder.SetInsertPoint(v24);
    PHINode *v25 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    builder.CreateRet(v25);


    v4->addIncoming(v6, v3);
    v4->addIncoming(builder.getInt32(1048576), v1);
    v10->addIncoming(v20, v9);
    v10->addIncoming(v4, v7);
    v11->addIncoming(v19, v9);
    v11->addIncoming(builder.getInt32(0), v7);
    v12->addIncoming(v17, v9);
    v12->addIncoming(v0, v7);
    v25->addIncoming(builder.getInt32(0), v1);
    v25->addIncoming(builder.getInt32(0), v7);
    v25->addIncoming(v23, v22);
  }
  
  
  // Генерация функции: swap_i
  {
    Value *v0 = swap_iFunc->getArg(0);
    Value *v1 = swap_iFunc->getArg(1);
    BasicBlock *v2 = BasicBlock::Create(context, "", swap_iFunc);


    builder.SetInsertPoint(v2);
    Value *v3 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v1, MaybeAlign(4));
    Value *v4 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v0, MaybeAlign(4));
    Value *v5 = builder.CreateAdd(v4, v3);
    builder.CreateAlignedStore(v5, v0, MaybeAlign(4));
    Value *v6 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v1, MaybeAlign(4));
    Value *v7 = builder.CreateSub(v5, v6);
    builder.CreateAlignedStore(v7, v1, MaybeAlign(4));
    Value *v8 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v0, MaybeAlign(4));
    Value *v9 = builder.CreateSub(v8, v7);
    builder.CreateAlignedStore(v9, v0, MaybeAlign(4));
    builder.CreateRetVoid();


  }
  
  
  // Генерация функции: clamp
  {
    Value *v0 = clampFunc->getArg(0);
    Value *v1 = clampFunc->getArg(1);
    Value *v2 = clampFunc->getArg(2);
    BasicBlock *v3 = BasicBlock::Create(context, "", clampFunc);


    builder.SetInsertPoint(v3);
    Value *v4 = builder.CreateICmp(static_cast<CmpInst::Predicate>(38), v0, v2);
    // Вызов функции: llvm.smax.i32
    Value *v5 = builder.CreateCall(llvm_smax_i32Func, {v0, v1, });
    Value *v6 = builder.CreateSelect(v4, v2, v5);
    builder.CreateRet(v6);


  }
  
  
  // Генерация функции: abs
  {
    Value *v0 = absFunc->getArg(0);
    BasicBlock *v1 = BasicBlock::Create(context, "", absFunc);


    builder.SetInsertPoint(v1);
    Value *v2 = builder.CreateAlloca(ArrayType::get(Type::getInt32Ty(context), 2));
    // Вызов функции: llvm.lifetime.start.p0
    builder.CreateCall(llvm_lifetime_start_p0Func, {builder.getInt64(8), v2, });
    Value *v3 = builder.CreateSub(builder.getInt32(0), v0);
    builder.CreateAlignedStore(v3, v2, MaybeAlign(4));
    Value *v4 = GetElementPtrInst::Create(Type::getInt32Ty(context),v2, {builder.getInt64(1), });
    builder.Insert(v4);
    builder.CreateAlignedStore(v0, v4, MaybeAlign(4));
    Value *v5 = builder.CreateICmp(static_cast<CmpInst::Predicate>(38), v0, builder.getInt32(0));
    Value *v6 = builder.CreateZExt(v5, Type::getInt64Ty(context));
    Value *v7 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v2, {builder.getInt64(0), v6, });
    builder.Insert(v7);
    Value *v8 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v7, MaybeAlign(4));
    // Вызов функции: llvm.lifetime.end.p0
    builder.CreateCall(llvm_lifetime_end_p0Func, {builder.getInt64(8), v2, });
    builder.CreateRet(v8);


  }
  
  
  // Генерация функции: draw_line
  {
    Value *v0 = draw_lineFunc->getArg(0);
    Value *v1 = draw_lineFunc->getArg(1);
    Value *v2 = draw_lineFunc->getArg(2);
    Value *v3 = draw_lineFunc->getArg(3);
    Value *v4 = draw_lineFunc->getArg(4);
    BasicBlock *v5 = BasicBlock::Create(context, "", draw_lineFunc);
    BasicBlock *v19 = BasicBlock::Create(context, "", draw_lineFunc);
    BasicBlock *v22 = BasicBlock::Create(context, "", draw_lineFunc);
    BasicBlock *v42 = BasicBlock::Create(context, "", draw_lineFunc);


    builder.SetInsertPoint(v5);
    Value *v6 = builder.CreateSub(v2, v0);
    // Вызов функции: llvm.abs.i32
    Value *v7 = builder.CreateCall(llvm_abs_i32Func, {v6, builder.getInt1(true), });
    Value *v8 = builder.CreateSub(v3, v1);
    // Вызов функции: llvm.abs.i32
    Value *v9 = builder.CreateCall(llvm_abs_i32Func, {v8, builder.getInt1(true), });
    Value *v10 = builder.CreateICmp(static_cast<CmpInst::Predicate>(40), v0, v2);
    Value *v11 = builder.CreateSelect(v10, builder.getInt32(1), builder.getInt32(-1));
    Value *v12 = builder.CreateICmp(static_cast<CmpInst::Predicate>(40), v1, v3);
    Value *v13 = builder.CreateSelect(v12, builder.getInt32(1), builder.getInt32(-1));
    Value *v14 = builder.CreateAnd(v0, builder.getInt32(511));
    Value *v15 = builder.CreateAnd(v1, builder.getInt32(255));
    // Вызов функции: simPutPixel
    builder.CreateCall(simPutPixelFunc, {v14, v15, v4, });
    Value *v16 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v0, v2);
    Value *v17 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v1, v3);
    Value *v18 = builder.CreateAnd(v17, v16);
    builder.CreateCondBr(v18, v42, v19);


    builder.SetInsertPoint(v19);
    Value *v20 = builder.CreateSub(v7, v9);
    Value *v21 = builder.CreateSub(builder.getInt32(0), v9);
      builder.CreateBr(v22);


    builder.SetInsertPoint(v22);
    PHINode *v23 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    PHINode *v24 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    PHINode *v25 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    Value *v26 = builder.CreateShl(v24, builder.getInt32(1));
    Value *v27 = builder.CreateICmp(static_cast<CmpInst::Predicate>(38), v26, v21);
    Value *v28 = builder.CreateSelect(v27, v9, builder.getInt32(0));
    Value *v29 = builder.CreateSub(v24, v28);
    Value *v30 = builder.CreateSelect(v27, v11, builder.getInt32(0));
    Value *v31 = builder.CreateAdd(v30, v23);
    Value *v32 = builder.CreateICmp(static_cast<CmpInst::Predicate>(40), v26, v7);
    Value *v33 = builder.CreateSelect(v32, v13, builder.getInt32(0));
    Value *v34 = builder.CreateAdd(v33, v25);
    Value *v35 = builder.CreateSelect(v32, v7, builder.getInt32(0));
    Value *v36 = builder.CreateAdd(v29, v35);
    Value *v37 = builder.CreateAnd(v31, builder.getInt32(511));
    Value *v38 = builder.CreateAnd(v34, builder.getInt32(255));
    // Вызов функции: simPutPixel
    builder.CreateCall(simPutPixelFunc, {v37, v38, v4, });
    Value *v39 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v31, v2);
    Value *v40 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v34, v3);
    Value *v41 = builder.CreateAnd(v40, v39);
    builder.CreateCondBr(v41, v42, v22);


    builder.SetInsertPoint(v42);
    builder.CreateRetVoid();


    v23->addIncoming(v0, v19);
    v23->addIncoming(v31, v22);
    v24->addIncoming(v20, v19);
    v24->addIncoming(v36, v22);
    v25->addIncoming(v1, v19);
    v25->addIncoming(v34, v22);
  }
  
  
  // Генерация функции: swap
  {
    Value *v0 = swapFunc->getArg(0);
    Value *v1 = swapFunc->getArg(1);
    Value *v2 = swapFunc->getArg(2);
    Value *v3 = swapFunc->getArg(3);
    Value *v4 = swapFunc->getArg(4);
    Value *v5 = swapFunc->getArg(5);
    BasicBlock *v6 = BasicBlock::Create(context, "", swapFunc);


    builder.SetInsertPoint(v6);
    Value *v7 = builder.CreateSExt(v0, Type::getInt64Ty(context));
    Value *v8 = GetElementPtrInst::Create(Type::getInt32Ty(context),v4, {v7, });
    builder.Insert(v8);
    Value *v9 = builder.CreateSExt(v1, Type::getInt64Ty(context));
    Value *v10 = GetElementPtrInst::Create(Type::getInt32Ty(context),v4, {v9, });
    builder.Insert(v10);
    Value *v11 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v10, MaybeAlign(4));
    Value *v12 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v8, MaybeAlign(4));
    Value *v13 = builder.CreateAdd(v12, v11);
    builder.CreateAlignedStore(v13, v8, MaybeAlign(4));
    Value *v14 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v10, MaybeAlign(4));
    Value *v15 = builder.CreateSub(v13, v14);
    builder.CreateAlignedStore(v15, v10, MaybeAlign(4));
    Value *v16 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v8, MaybeAlign(4));
    Value *v17 = builder.CreateSub(v16, v15);
    builder.CreateAlignedStore(v17, v8, MaybeAlign(4));
    Value *v18 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v3, {v7, });
    builder.Insert(v18);
    Value *v19 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v3, {v9, });
    builder.Insert(v19);
    Value *v20 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v19, MaybeAlign(4));
    Value *v21 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v18, MaybeAlign(4));
    Value *v22 = builder.CreateAdd(v21, v20);
    builder.CreateAlignedStore(v22, v18, MaybeAlign(4));
    Value *v23 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v19, MaybeAlign(4));
    Value *v24 = builder.CreateSub(v22, v23);
    builder.CreateAlignedStore(v24, v19, MaybeAlign(4));
    Value *v25 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v18, MaybeAlign(4));
    Value *v26 = builder.CreateSub(v25, v24);
    builder.CreateAlignedStore(v26, v18, MaybeAlign(4));
    Value *v27 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v3, {v7, builder.getInt64(1), });
    builder.Insert(v27);
    Value *v28 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v3, {v9, builder.getInt64(1), });
    builder.Insert(v28);
    Value *v29 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v28, MaybeAlign(4));
    Value *v30 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v27, MaybeAlign(4));
    Value *v31 = builder.CreateAdd(v30, v29);
    builder.CreateAlignedStore(v31, v27, MaybeAlign(4));
    Value *v32 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v28, MaybeAlign(4));
    Value *v33 = builder.CreateSub(v31, v32);
    builder.CreateAlignedStore(v33, v28, MaybeAlign(4));
    Value *v34 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v27, MaybeAlign(4));
    Value *v35 = builder.CreateSub(v34, v33);
    builder.CreateAlignedStore(v35, v27, MaybeAlign(4));
    Value *v36 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v2, {v7, });
    builder.Insert(v36);
    Value *v37 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v2, {v9, });
    builder.Insert(v37);
    Value *v38 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v37, MaybeAlign(4));
    Value *v39 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v36, MaybeAlign(4));
    Value *v40 = builder.CreateAdd(v39, v38);
    builder.CreateAlignedStore(v40, v36, MaybeAlign(4));
    Value *v41 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v37, MaybeAlign(4));
    Value *v42 = builder.CreateSub(v40, v41);
    builder.CreateAlignedStore(v42, v37, MaybeAlign(4));
    Value *v43 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v36, MaybeAlign(4));
    Value *v44 = builder.CreateSub(v43, v42);
    builder.CreateAlignedStore(v44, v36, MaybeAlign(4));
    Value *v45 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v2, {v7, builder.getInt64(1), });
    builder.Insert(v45);
    Value *v46 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v2, {v9, builder.getInt64(1), });
    builder.Insert(v46);
    Value *v47 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v46, MaybeAlign(4));
    Value *v48 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v45, MaybeAlign(4));
    Value *v49 = builder.CreateAdd(v48, v47);
    builder.CreateAlignedStore(v49, v45, MaybeAlign(4));
    Value *v50 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v46, MaybeAlign(4));
    Value *v51 = builder.CreateSub(v49, v50);
    builder.CreateAlignedStore(v51, v46, MaybeAlign(4));
    Value *v52 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v45, MaybeAlign(4));
    Value *v53 = builder.CreateSub(v52, v51);
    builder.CreateAlignedStore(v53, v45, MaybeAlign(4));
    builder.CreateRetVoid();


  }
  
  
  // Генерация функции: init_particle
  {
    Value *v0 = init_particleFunc->getArg(0);
    Value *v1 = init_particleFunc->getArg(1);
    Value *v2 = init_particleFunc->getArg(2);
    Value *v3 = init_particleFunc->getArg(3);
    Value *v4 = init_particleFunc->getArg(4);
    BasicBlock *v5 = BasicBlock::Create(context, "", init_particleFunc);
    BasicBlock *v27 = BasicBlock::Create(context, "", init_particleFunc);
    BasicBlock *v31 = BasicBlock::Create(context, "", init_particleFunc);
    BasicBlock *v33 = BasicBlock::Create(context, "", init_particleFunc);
    BasicBlock *v46 = BasicBlock::Create(context, "", init_particleFunc);
    BasicBlock *v48 = BasicBlock::Create(context, "", init_particleFunc);
    BasicBlock *v51 = BasicBlock::Create(context, "", init_particleFunc);
    BasicBlock *v53 = BasicBlock::Create(context, "", init_particleFunc);
    BasicBlock *v55 = BasicBlock::Create(context, "", init_particleFunc);
    BasicBlock *v64 = BasicBlock::Create(context, "", init_particleFunc);
    BasicBlock *v68 = BasicBlock::Create(context, "", init_particleFunc);
    BasicBlock *v70 = BasicBlock::Create(context, "", init_particleFunc);
    BasicBlock *v83 = BasicBlock::Create(context, "", init_particleFunc);
    BasicBlock *v86 = BasicBlock::Create(context, "", init_particleFunc);
    BasicBlock *v99 = BasicBlock::Create(context, "", init_particleFunc);
    BasicBlock *v104 = BasicBlock::Create(context, "", init_particleFunc);


    builder.SetInsertPoint(v5);
    Value *v6 = builder.CreateSExt(v0, Type::getInt64Ty(context));
    Value *v7 = GetElementPtrInst::Create(Type::getInt32Ty(context),v3, {v6, });
    builder.Insert(v7);
    builder.CreateAlignedStore(builder.getInt32(0), v7, MaybeAlign(4));
    // Вызов функции: simRand
    Value *v8 = builder.CreateCall(simRandFunc, {});
    Value *v9 = builder.CreateSRem(v8, builder.getInt32(524288));
    Value *v10 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v6, });
    builder.Insert(v10);
    builder.CreateAlignedStore(v9, v10, MaybeAlign(4));
    // Вызов функции: simRand
    Value *v11 = builder.CreateCall(simRandFunc, {});
    Value *v12 = builder.CreateSRem(v11, builder.getInt32(262144));
    Value *v13 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v6, builder.getInt64(1), });
    builder.Insert(v13);
    builder.CreateAlignedStore(v12, v13, MaybeAlign(4));
    Value *v14 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v10, MaybeAlign(4));
    Value *v15 = builder.CreateAdd(v14, builder.getInt32(-131072));
    Value *v16 = builder.CreateAdd(v12, builder.getInt32(-262144));
    Value *v17 = builder.CreateSExt(v15, Type::getInt64Ty(context));
    Value *v18 = builder.CreateMul(v17, v17);
    Value *v19 = builder.CreateLShr(v18, builder.getInt64(10));
    Value *v20 = builder.CreateTrunc(v19, Type::getInt32Ty(context));
    Value *v21 = builder.CreateSExt(v16, Type::getInt64Ty(context));
    Value *v22 = builder.CreateMul(v21, v21);
    Value *v23 = builder.CreateLShr(v22, builder.getInt64(10));
    Value *v24 = builder.CreateTrunc(v23, Type::getInt32Ty(context));
    Value *v25 = builder.CreateAdd(v20, v24);
    Value *v26 = builder.CreateICmp(static_cast<CmpInst::Predicate>(40), v25, builder.getInt32(1));
    builder.CreateCondBr(v26, v48, v27);


    builder.SetInsertPoint(v27);
    PHINode *v28 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    Value *v29 = builder.CreateICmp(static_cast<CmpInst::Predicate>(38), v28, v25);
    Value *v30 = builder.CreateLShr(v28, builder.getInt32(2));
    builder.CreateCondBr(v29, v27, v31);


    builder.SetInsertPoint(v31);
    Value *v32 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v28, builder.getInt32(0));
    builder.CreateCondBr(v32, v48, v33);


    builder.SetInsertPoint(v33);
    PHINode *v34 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    PHINode *v35 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    PHINode *v36 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    Value *v37 = builder.CreateAdd(v35, v34);
    Value *v38 = builder.CreateICmp(static_cast<CmpInst::Predicate>(40), v36, v37);
    Value *v39 = builder.CreateAShr(v35, builder.getInt32(1));
    Value *v40 = builder.CreateSelect(v38, builder.getInt32(0), v37);
    Value *v41 = builder.CreateSub(v36, v40);
    Value *v42 = builder.CreateSelect(v38, builder.getInt32(0), v34);
    Value *v43 = builder.CreateAdd(v42, v39);
    Value *v44 = builder.CreateLShr(v34, builder.getInt32(2));
    Value *v45 = builder.CreateICmp(static_cast<CmpInst::Predicate>(36), v34, builder.getInt32(4));
    builder.CreateCondBr(v45, v46, v33);


    builder.SetInsertPoint(v46);
    Value *v47 = builder.CreateShl(v43, builder.getInt32(5));
      builder.CreateBr(v48);


    builder.SetInsertPoint(v48);
    PHINode *v49 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    Value *v50 = builder.CreateICmp(static_cast<CmpInst::Predicate>(38), v25, builder.getInt32(268435456));
    builder.CreateCondBr(v50, v104, v51);


    builder.SetInsertPoint(v51);
    Value *v52 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v49, builder.getInt32(0));
    builder.CreateCondBr(v52, v53, v55);


    builder.SetInsertPoint(v53);
    Value *v54 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v2, {v6, });
    builder.Insert(v54);
    builder.CreateAlignedStore(builder.getInt32(0), v54, MaybeAlign(4));
      builder.CreateBr(v99);


    builder.SetInsertPoint(v55);
    Value *v56 = builder.CreateShl(v17, builder.getInt64(10));
    Value *v57 = builder.CreateSExt(v49, Type::getInt64Ty(context));
    Value *v58 = builder.CreateSDiv(v56, v57);
    Value *v59 = builder.CreateShl(v21, builder.getInt64(10));
    Value *v60 = builder.CreateSDiv(v59, v57);
    Value *v61 = builder.CreateSDiv(builder.getInt64(2621440000), v57);
    Value *v62 = builder.CreateTrunc(v61, Type::getInt32Ty(context));
    Value *v63 = builder.CreateICmp(static_cast<CmpInst::Predicate>(40), v62, builder.getInt32(1));
    builder.CreateCondBr(v63, v86, v64);


    builder.SetInsertPoint(v64);
    PHINode *v65 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    Value *v66 = builder.CreateICmp(static_cast<CmpInst::Predicate>(38), v65, v62);
    Value *v67 = builder.CreateLShr(v65, builder.getInt32(2));
    builder.CreateCondBr(v66, v64, v68);


    builder.SetInsertPoint(v68);
    Value *v69 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v65, builder.getInt32(0));
    builder.CreateCondBr(v69, v86, v70);


    builder.SetInsertPoint(v70);
    PHINode *v71 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    PHINode *v72 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    PHINode *v73 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    Value *v74 = builder.CreateAdd(v72, v71);
    Value *v75 = builder.CreateICmp(static_cast<CmpInst::Predicate>(40), v73, v74);
    Value *v76 = builder.CreateAShr(v72, builder.getInt32(1));
    Value *v77 = builder.CreateSelect(v75, builder.getInt32(0), v74);
    Value *v78 = builder.CreateSub(v73, v77);
    Value *v79 = builder.CreateSelect(v75, builder.getInt32(0), v71);
    Value *v80 = builder.CreateAdd(v79, v76);
    Value *v81 = builder.CreateLShr(v71, builder.getInt32(2));
    Value *v82 = builder.CreateICmp(static_cast<CmpInst::Predicate>(36), v71, builder.getInt32(4));
    builder.CreateCondBr(v82, v83, v70);


    builder.SetInsertPoint(v83);
    Value *v84 = builder.CreateShl(v80, builder.getInt32(5));
    Value *v85 = builder.CreateSExt(v84, Type::getInt64Ty(context));
      builder.CreateBr(v86);


    builder.SetInsertPoint(v86);
    PHINode *v87 = builder.CreatePHI(Type::getInt64Ty(context), 3);
    Value *v88 = builder.CreateMul(v60, builder.getInt64(-4294967296));
    Value *v89 = builder.CreateAShr(v88, builder.getInt64(32));
    Value *v90 = builder.CreateMul(v87, v89);
    Value *v91 = builder.CreateLShr(v90, builder.getInt64(10));
    Value *v92 = builder.CreateTrunc(v91, Type::getInt32Ty(context));
    Value *v93 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v2, {v6, });
    builder.Insert(v93);
    builder.CreateAlignedStore(v92, v93, MaybeAlign(4));
    Value *v94 = builder.CreateShl(v58, builder.getInt64(32));
    Value *v95 = builder.CreateAShr(v94, builder.getInt64(32));
    Value *v96 = builder.CreateMul(v87, v95);
    Value *v97 = builder.CreateLShr(v96, builder.getInt64(10));
    Value *v98 = builder.CreateTrunc(v97, Type::getInt32Ty(context));
      builder.CreateBr(v99);


    builder.SetInsertPoint(v99);
    PHINode *v100 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    Value *v101 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v2, {v6, builder.getInt64(1), });
    builder.Insert(v101);
    builder.CreateAlignedStore(v100, v101, MaybeAlign(4));
    builder.CreateAlignedStore(builder.getInt32(1), v7, MaybeAlign(4));
    Value *v102 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v4, MaybeAlign(4));
    Value *v103 = builder.CreateAdd(v102, builder.getInt32(1));
    builder.CreateAlignedStore(v103, v4, MaybeAlign(4));
      builder.CreateBr(v104);


    builder.SetInsertPoint(v104);
    builder.CreateRetVoid();


    v28->addIncoming(v30, v27);
    v28->addIncoming(builder.getInt32(1048576), v5);
    v34->addIncoming(v44, v33);
    v34->addIncoming(v28, v31);
    v35->addIncoming(v43, v33);
    v35->addIncoming(builder.getInt32(0), v31);
    v36->addIncoming(v41, v33);
    v36->addIncoming(v25, v31);
    v49->addIncoming(builder.getInt32(0), v5);
    v49->addIncoming(builder.getInt32(0), v31);
    v49->addIncoming(v47, v46);
    v65->addIncoming(v67, v64);
    v65->addIncoming(builder.getInt32(1048576), v55);
    v71->addIncoming(v81, v70);
    v71->addIncoming(v65, v68);
    v72->addIncoming(v80, v70);
    v72->addIncoming(builder.getInt32(0), v68);
    v73->addIncoming(v78, v70);
    v73->addIncoming(v62, v68);
    v87->addIncoming(builder.getInt64(0), v55);
    v87->addIncoming(builder.getInt64(0), v68);
    v87->addIncoming(v85, v83);
    v100->addIncoming(v98, v86);
    v100->addIncoming(builder.getInt32(0), v53);
  }
  
  
  // Генерация функции: delete_particle
  {
    Value *v0 = delete_particleFunc->getArg(0);
    Value *v1 = delete_particleFunc->getArg(1);
    Value *v2 = delete_particleFunc->getArg(2);
    Value *v3 = delete_particleFunc->getArg(3);
    Value *v4 = delete_particleFunc->getArg(4);
    BasicBlock *v5 = BasicBlock::Create(context, "", delete_particleFunc);


    builder.SetInsertPoint(v5);
    Value *v6 = builder.CreateSExt(v0, Type::getInt64Ty(context));
    Value *v7 = GetElementPtrInst::Create(Type::getInt32Ty(context),v3, {v6, });
    builder.Insert(v7);
    builder.CreateAlignedStore(builder.getInt32(0), v7, MaybeAlign(4));
    Value *v8 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v4, MaybeAlign(4));
    Value *v9 = builder.CreateAdd(v8, builder.getInt32(-1));
    builder.CreateAlignedStore(v9, v4, MaybeAlign(4));
    Value *v10 = builder.CreateSExt(v9, Type::getInt64Ty(context));
    Value *v11 = GetElementPtrInst::Create(Type::getInt32Ty(context),v3, {v10, });
    builder.Insert(v11);
    Value *v12 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v11, MaybeAlign(4));
    Value *v13 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v7, MaybeAlign(4));
    Value *v14 = builder.CreateAdd(v13, v12);
    builder.CreateAlignedStore(v14, v7, MaybeAlign(4));
    Value *v15 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v11, MaybeAlign(4));
    Value *v16 = builder.CreateSub(v14, v15);
    builder.CreateAlignedStore(v16, v11, MaybeAlign(4));
    Value *v17 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v7, MaybeAlign(4));
    Value *v18 = builder.CreateSub(v17, v16);
    builder.CreateAlignedStore(v18, v7, MaybeAlign(4));
    Value *v19 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v2, {v6, });
    builder.Insert(v19);
    Value *v20 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v2, {v10, });
    builder.Insert(v20);
    Value *v21 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v20, MaybeAlign(4));
    Value *v22 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v19, MaybeAlign(4));
    Value *v23 = builder.CreateAdd(v22, v21);
    builder.CreateAlignedStore(v23, v19, MaybeAlign(4));
    Value *v24 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v20, MaybeAlign(4));
    Value *v25 = builder.CreateSub(v23, v24);
    builder.CreateAlignedStore(v25, v20, MaybeAlign(4));
    Value *v26 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v19, MaybeAlign(4));
    Value *v27 = builder.CreateSub(v26, v25);
    builder.CreateAlignedStore(v27, v19, MaybeAlign(4));
    Value *v28 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v2, {v6, builder.getInt64(1), });
    builder.Insert(v28);
    Value *v29 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v2, {v10, builder.getInt64(1), });
    builder.Insert(v29);
    Value *v30 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v29, MaybeAlign(4));
    Value *v31 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v28, MaybeAlign(4));
    Value *v32 = builder.CreateAdd(v31, v30);
    builder.CreateAlignedStore(v32, v28, MaybeAlign(4));
    Value *v33 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v29, MaybeAlign(4));
    Value *v34 = builder.CreateSub(v32, v33);
    builder.CreateAlignedStore(v34, v29, MaybeAlign(4));
    Value *v35 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v28, MaybeAlign(4));
    Value *v36 = builder.CreateSub(v35, v34);
    builder.CreateAlignedStore(v36, v28, MaybeAlign(4));
    Value *v37 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v6, });
    builder.Insert(v37);
    Value *v38 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v10, });
    builder.Insert(v38);
    Value *v39 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v38, MaybeAlign(4));
    Value *v40 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v37, MaybeAlign(4));
    Value *v41 = builder.CreateAdd(v40, v39);
    builder.CreateAlignedStore(v41, v37, MaybeAlign(4));
    Value *v42 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v38, MaybeAlign(4));
    Value *v43 = builder.CreateSub(v41, v42);
    builder.CreateAlignedStore(v43, v38, MaybeAlign(4));
    Value *v44 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v37, MaybeAlign(4));
    Value *v45 = builder.CreateSub(v44, v43);
    builder.CreateAlignedStore(v45, v37, MaybeAlign(4));
    Value *v46 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v6, builder.getInt64(1), });
    builder.Insert(v46);
    Value *v47 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v10, builder.getInt64(1), });
    builder.Insert(v47);
    Value *v48 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v47, MaybeAlign(4));
    Value *v49 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v46, MaybeAlign(4));
    Value *v50 = builder.CreateAdd(v49, v48);
    builder.CreateAlignedStore(v50, v46, MaybeAlign(4));
    Value *v51 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v47, MaybeAlign(4));
    Value *v52 = builder.CreateSub(v50, v51);
    builder.CreateAlignedStore(v52, v47, MaybeAlign(4));
    Value *v53 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v46, MaybeAlign(4));
    Value *v54 = builder.CreateSub(v53, v52);
    builder.CreateAlignedStore(v54, v46, MaybeAlign(4));
    builder.CreateRetVoid();


  }
  
  
  // Генерация функции: init_particles
  {
    Value *v0 = init_particlesFunc->getArg(0);
    Value *v1 = init_particlesFunc->getArg(1);
    Value *v2 = init_particlesFunc->getArg(2);
    Value *v3 = init_particlesFunc->getArg(3);
    BasicBlock *v4 = BasicBlock::Create(context, "", init_particlesFunc);
    BasicBlock *v5 = BasicBlock::Create(context, "", init_particlesFunc);
    BasicBlock *v6 = BasicBlock::Create(context, "", init_particlesFunc);


    builder.SetInsertPoint(v4);
      builder.CreateBr(v6);


    builder.SetInsertPoint(v5);
    builder.CreateRetVoid();


    builder.SetInsertPoint(v6);
    PHINode *v7 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    // Вызов функции: init_particle
    builder.CreateCall(init_particleFunc, {v7, v0, v1, v2, v3, });
    Value *v8 = builder.CreateAdd(v7, builder.getInt32(1));
    Value *v9 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v8, builder.getInt32(1000));
    builder.CreateCondBr(v9, v5, v6);


    v7->addIncoming(builder.getInt32(0), v4);
    v7->addIncoming(v8, v6);
  }
  
  
  // Генерация функции: update_particles
  {
    Value *v0 = update_particlesFunc->getArg(0);
    Value *v1 = update_particlesFunc->getArg(1);
    Value *v2 = update_particlesFunc->getArg(2);
    Value *v3 = update_particlesFunc->getArg(3);
    BasicBlock *v4 = BasicBlock::Create(context, "", update_particlesFunc);
    BasicBlock *v7 = BasicBlock::Create(context, "", update_particlesFunc);
    BasicBlock *v8 = BasicBlock::Create(context, "", update_particlesFunc);
    BasicBlock *v13 = BasicBlock::Create(context, "", update_particlesFunc);
    BasicBlock *v14 = BasicBlock::Create(context, "", update_particlesFunc);
    BasicBlock *v20 = BasicBlock::Create(context, "", update_particlesFunc);
    BasicBlock *v37 = BasicBlock::Create(context, "", update_particlesFunc);
    BasicBlock *v84 = BasicBlock::Create(context, "", update_particlesFunc);
    BasicBlock *v122 = BasicBlock::Create(context, "", update_particlesFunc);


    builder.SetInsertPoint(v4);
    Value *v5 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v3, MaybeAlign(4));
    Value *v6 = builder.CreateICmp(static_cast<CmpInst::Predicate>(40), v5, builder.getInt32(1000));
    builder.CreateCondBr(v6, v8, v7);


    builder.SetInsertPoint(v7);
      builder.CreateBr(v14);


    builder.SetInsertPoint(v8);
    PHINode *v9 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    Value *v10 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v3, MaybeAlign(4));
    // Вызов функции: init_particle
    builder.CreateCall(init_particleFunc, {v10, v0, v1, v2, v3, });
    Value *v11 = builder.CreateAdd(v9, builder.getInt32(1));
    Value *v12 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v11, builder.getInt32(1000));
    builder.CreateCondBr(v12, v7, v8);


    builder.SetInsertPoint(v13);
    builder.CreateRetVoid();


    builder.SetInsertPoint(v14);
    PHINode *v15 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    Value *v16 = builder.CreateSExt(v15, Type::getInt64Ty(context));
    Value *v17 = GetElementPtrInst::Create(Type::getInt32Ty(context),v2, {v16, });
    builder.Insert(v17);
    Value *v18 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v17, MaybeAlign(4));
    Value *v19 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v18, builder.getInt32(0));
    builder.CreateCondBr(v19, v122, v20);


    builder.SetInsertPoint(v20);
    Value *v21 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v0, {v16, });
    builder.Insert(v21);
    Value *v22 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v21, MaybeAlign(4));
    Value *v23 = builder.CreateSub(builder.getInt32(131072), v22);
    Value *v24 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v0, {v16, builder.getInt64(1), });
    builder.Insert(v24);
    Value *v25 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v24, MaybeAlign(4));
    Value *v26 = builder.CreateSub(builder.getInt32(262144), v25);
    Value *v27 = builder.CreateSExt(v23, Type::getInt64Ty(context));
    Value *v28 = builder.CreateMul(v27, v27);
    Value *v29 = builder.CreateLShr(v28, builder.getInt64(10));
    Value *v30 = builder.CreateTrunc(v29, Type::getInt32Ty(context));
    Value *v31 = builder.CreateSExt(v26, Type::getInt64Ty(context));
    Value *v32 = builder.CreateMul(v31, v31);
    Value *v33 = builder.CreateLShr(v32, builder.getInt64(10));
    Value *v34 = builder.CreateTrunc(v33, Type::getInt32Ty(context));
    Value *v35 = builder.CreateAdd(v34, v30);
    Value *v36 = builder.CreateICmp(static_cast<CmpInst::Predicate>(40), v35, builder.getInt32(2560000));
    builder.CreateCondBr(v36, v37, v84);


    builder.SetInsertPoint(v37);
    builder.CreateAlignedStore(builder.getInt32(0), v17, MaybeAlign(4));
    Value *v38 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v3, MaybeAlign(4));
    Value *v39 = builder.CreateAdd(v38, builder.getInt32(-1));
    builder.CreateAlignedStore(v39, v3, MaybeAlign(4));
    Value *v40 = builder.CreateSExt(v39, Type::getInt64Ty(context));
    Value *v41 = GetElementPtrInst::Create(Type::getInt32Ty(context),v2, {v40, });
    builder.Insert(v41);
    Value *v42 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v41, MaybeAlign(4));
    Value *v43 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v17, MaybeAlign(4));
    Value *v44 = builder.CreateAdd(v43, v42);
    builder.CreateAlignedStore(v44, v17, MaybeAlign(4));
    Value *v45 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v41, MaybeAlign(4));
    Value *v46 = builder.CreateSub(v44, v45);
    builder.CreateAlignedStore(v46, v41, MaybeAlign(4));
    Value *v47 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v17, MaybeAlign(4));
    Value *v48 = builder.CreateSub(v47, v46);
    builder.CreateAlignedStore(v48, v17, MaybeAlign(4));
    Value *v49 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v16, });
    builder.Insert(v49);
    Value *v50 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v40, });
    builder.Insert(v50);
    Value *v51 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v50, MaybeAlign(4));
    Value *v52 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v49, MaybeAlign(4));
    Value *v53 = builder.CreateAdd(v52, v51);
    builder.CreateAlignedStore(v53, v49, MaybeAlign(4));
    Value *v54 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v50, MaybeAlign(4));
    Value *v55 = builder.CreateSub(v53, v54);
    builder.CreateAlignedStore(v55, v50, MaybeAlign(4));
    Value *v56 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v49, MaybeAlign(4));
    Value *v57 = builder.CreateSub(v56, v55);
    builder.CreateAlignedStore(v57, v49, MaybeAlign(4));
    Value *v58 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v16, builder.getInt64(1), });
    builder.Insert(v58);
    Value *v59 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v40, builder.getInt64(1), });
    builder.Insert(v59);
    Value *v60 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v59, MaybeAlign(4));
    Value *v61 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v58, MaybeAlign(4));
    Value *v62 = builder.CreateAdd(v61, v60);
    builder.CreateAlignedStore(v62, v58, MaybeAlign(4));
    Value *v63 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v59, MaybeAlign(4));
    Value *v64 = builder.CreateSub(v62, v63);
    builder.CreateAlignedStore(v64, v59, MaybeAlign(4));
    Value *v65 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v58, MaybeAlign(4));
    Value *v66 = builder.CreateSub(v65, v64);
    builder.CreateAlignedStore(v66, v58, MaybeAlign(4));
    Value *v67 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v0, {v40, });
    builder.Insert(v67);
    Value *v68 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v67, MaybeAlign(4));
    Value *v69 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v21, MaybeAlign(4));
    Value *v70 = builder.CreateAdd(v69, v68);
    builder.CreateAlignedStore(v70, v21, MaybeAlign(4));
    Value *v71 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v67, MaybeAlign(4));
    Value *v72 = builder.CreateSub(v70, v71);
    builder.CreateAlignedStore(v72, v67, MaybeAlign(4));
    Value *v73 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v21, MaybeAlign(4));
    Value *v74 = builder.CreateSub(v73, v72);
    builder.CreateAlignedStore(v74, v21, MaybeAlign(4));
    Value *v75 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v0, {v40, builder.getInt64(1), });
    builder.Insert(v75);
    Value *v76 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v75, MaybeAlign(4));
    Value *v77 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v24, MaybeAlign(4));
    Value *v78 = builder.CreateAdd(v77, v76);
    builder.CreateAlignedStore(v78, v24, MaybeAlign(4));
    Value *v79 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v75, MaybeAlign(4));
    Value *v80 = builder.CreateSub(v78, v79);
    builder.CreateAlignedStore(v80, v75, MaybeAlign(4));
    Value *v81 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v24, MaybeAlign(4));
    Value *v82 = builder.CreateSub(v81, v80);
    builder.CreateAlignedStore(v82, v24, MaybeAlign(4));
    Value *v83 = builder.CreateAdd(v15, builder.getInt32(-1));
      builder.CreateBr(v122);


    builder.SetInsertPoint(v84);
    Value *v85 = builder.CreateZExt(v35, Type::getInt64Ty(context));
    Value *v86 = builder.CreateUDiv(builder.getInt64(5242880000), v85);
    Value *v87 = builder.CreateShl(v86, builder.getInt64(32));
    Value *v88 = builder.CreateAShr(v87, builder.getInt64(32));
    Value *v89 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v16, });
    builder.Insert(v89);
    Value *v90 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v89, MaybeAlign(4));
    Value *v91 = builder.CreateShl(v27, builder.getInt64(22));
    Value *v92 = builder.CreateMul(v91, v88);
    Value *v93 = builder.CreateAShr(v92, builder.getInt64(32));
    Value *v94 = builder.CreateMul(v93, builder.getInt64(20));
    Value *v95 = builder.CreateLShr(v94, builder.getInt64(10));
    Value *v96 = builder.CreateTrunc(v95, Type::getInt32Ty(context));
    Value *v97 = builder.CreateAdd(v90, v96);
    // Вызов функции: llvm.smax.i32
    Value *v98 = builder.CreateCall(llvm_smax_i32Func, {v97, builder.getInt32(-102400), });
    // Вызов функции: llvm.smin.i32
    Value *v99 = builder.CreateCall(llvm_smin_i32Func, {v98, builder.getInt32(102400), });
    builder.CreateAlignedStore(v99, v89, MaybeAlign(4));
    Value *v100 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v16, builder.getInt64(1), });
    builder.Insert(v100);
    Value *v101 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v100, MaybeAlign(4));
    Value *v102 = builder.CreateShl(v31, builder.getInt64(22));
    Value *v103 = builder.CreateMul(v102, v88);
    Value *v104 = builder.CreateAShr(v103, builder.getInt64(32));
    Value *v105 = builder.CreateMul(v104, builder.getInt64(20));
    Value *v106 = builder.CreateLShr(v105, builder.getInt64(10));
    Value *v107 = builder.CreateTrunc(v106, Type::getInt32Ty(context));
    Value *v108 = builder.CreateAdd(v101, v107);
    // Вызов функции: llvm.smax.i32
    Value *v109 = builder.CreateCall(llvm_smax_i32Func, {v108, builder.getInt32(-102400), });
    // Вызов функции: llvm.smin.i32
    Value *v110 = builder.CreateCall(llvm_smin_i32Func, {v109, builder.getInt32(102400), });
    builder.CreateAlignedStore(v110, v100, MaybeAlign(4));
    Value *v111 = builder.CreateMul(v99, builder.getInt32(20));
    Value *v112 = builder.CreateAShr(v111, builder.getInt32(10));
    Value *v113 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v21, MaybeAlign(4));
    Value *v114 = builder.CreateAdd(v112, v113);
    builder.CreateAlignedStore(v114, v21, MaybeAlign(4));
    Value *v115 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v100, MaybeAlign(4));
    Value *v116 = builder.CreateSExt(v115, Type::getInt64Ty(context));
    Value *v117 = builder.CreateMul(v116, builder.getInt64(20));
    Value *v118 = builder.CreateLShr(v117, builder.getInt64(10));
    Value *v119 = builder.CreateTrunc(v118, Type::getInt32Ty(context));
    Value *v120 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v24, MaybeAlign(4));
    Value *v121 = builder.CreateAdd(v120, v119);
    builder.CreateAlignedStore(v121, v24, MaybeAlign(4));
      builder.CreateBr(v122);


    builder.SetInsertPoint(v122);
    PHINode *v123 = builder.CreatePHI(Type::getInt32Ty(context), 3);
    Value *v124 = builder.CreateAdd(v123, builder.getInt32(1));
    Value *v125 = builder.CreateICmp(static_cast<CmpInst::Predicate>(40), v123, builder.getInt32(999));
    builder.CreateCondBr(v125, v14, v13);


    v9->addIncoming(v11, v8);
    v9->addIncoming(v5, v4);
    v15->addIncoming(v124, v122);
    v15->addIncoming(builder.getInt32(0), v7);
    v123->addIncoming(v15, v14);
    v123->addIncoming(v83, v37);
    v123->addIncoming(v15, v84);
  }
  
  
  // Генерация функции: get_velocity_sq
  {
    Value *v0 = get_velocity_sqFunc->getArg(0);
    Value *v1 = get_velocity_sqFunc->getArg(1);
    Value *v2 = get_velocity_sqFunc->getArg(2);
    Value *v3 = get_velocity_sqFunc->getArg(3);
    BasicBlock *v4 = BasicBlock::Create(context, "", get_velocity_sqFunc);


    builder.SetInsertPoint(v4);
    Value *v5 = builder.CreateSExt(v0, Type::getInt64Ty(context));
    Value *v6 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v2, {v5, });
    builder.Insert(v6);
    Value *v7 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v6, MaybeAlign(4));
    Value *v8 = builder.CreateSExt(v7, Type::getInt64Ty(context));
    Value *v9 = builder.CreateMul(v8, v8);
    Value *v10 = builder.CreateLShr(v9, builder.getInt64(10));
    Value *v11 = builder.CreateTrunc(v10, Type::getInt32Ty(context));
    Value *v12 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v2, {v5, builder.getInt64(1), });
    builder.Insert(v12);
    Value *v13 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v12, MaybeAlign(4));
    Value *v14 = builder.CreateSExt(v13, Type::getInt64Ty(context));
    Value *v15 = builder.CreateMul(v14, v14);
    Value *v16 = builder.CreateLShr(v15, builder.getInt64(10));
    Value *v17 = builder.CreateTrunc(v16, Type::getInt32Ty(context));
    Value *v18 = builder.CreateAdd(v17, v11);
    builder.CreateRet(v18);


  }
  
  
  // Генерация функции: display_particles
  {
    Value *v0 = display_particlesFunc->getArg(0);
    Value *v1 = display_particlesFunc->getArg(1);
    Value *v2 = display_particlesFunc->getArg(2);
    BasicBlock *v3 = BasicBlock::Create(context, "", display_particlesFunc);
    BasicBlock *v4 = BasicBlock::Create(context, "", display_particlesFunc);
    BasicBlock *v5 = BasicBlock::Create(context, "", display_particlesFunc);
    BasicBlock *v10 = BasicBlock::Create(context, "", display_particlesFunc);
    BasicBlock *v61 = BasicBlock::Create(context, "", display_particlesFunc);
    BasicBlock *v64 = BasicBlock::Create(context, "", display_particlesFunc);
    BasicBlock *v84 = BasicBlock::Create(context, "", display_particlesFunc);


    builder.SetInsertPoint(v3);
    // Вызов функции: simClear
    builder.CreateCall(simClearFunc, {builder.getInt32(-16777216), });
      builder.CreateBr(v5);


    builder.SetInsertPoint(v4);
    // Вызов функции: simFlush
    builder.CreateCall(simFlushFunc, {});
    builder.CreateRetVoid();


    builder.SetInsertPoint(v5);
    PHINode *v6 = builder.CreatePHI(Type::getInt64Ty(context), 2);
    Value *v7 = GetElementPtrInst::Create(Type::getInt32Ty(context),v2, {v6, });
    builder.Insert(v7);
    Value *v8 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v7, MaybeAlign(4));
    Value *v9 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v8, builder.getInt32(0));
    builder.CreateCondBr(v9, v84, v10);


    builder.SetInsertPoint(v10);
    Value *v11 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v0, {v6, });
    builder.Insert(v11);
    Value *v12 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v11, MaybeAlign(4));
    Value *v13 = builder.CreateAShr(v12, builder.getInt32(10));
    Value *v14 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v0, {v6, builder.getInt64(1), });
    builder.Insert(v14);
    Value *v15 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v14, MaybeAlign(4));
    Value *v16 = builder.CreateAShr(v15, builder.getInt32(10));
    Value *v17 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v6, });
    builder.Insert(v17);
    Value *v18 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v17, MaybeAlign(4));
    Value *v19 = builder.CreateSDiv(v18, builder.getInt32(-10));
    Value *v20 = builder.CreateAdd(v19, v12);
    Value *v21 = builder.CreateAShr(v20, builder.getInt32(10));
    Value *v22 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v6, builder.getInt64(1), });
    builder.Insert(v22);
    Value *v23 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v22, MaybeAlign(4));
    Value *v24 = builder.CreateSDiv(v23, builder.getInt32(-10));
    Value *v25 = builder.CreateAdd(v24, v15);
    Value *v26 = builder.CreateAShr(v25, builder.getInt32(10));
    Value *v27 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v6, });
    builder.Insert(v27);
    Value *v28 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v27, MaybeAlign(4));
    Value *v29 = builder.CreateSExt(v28, Type::getInt64Ty(context));
    Value *v30 = builder.CreateMul(v29, v29);
    Value *v31 = builder.CreateLShr(v30, builder.getInt64(10));
    Value *v32 = GetElementPtrInst::Create(ArrayType::get(Type::getInt32Ty(context), 2),v1, {v6, builder.getInt64(1), });
    builder.Insert(v32);
    Value *v33 = builder.CreateAlignedLoad(Type::getInt32Ty(context), v32, MaybeAlign(4));
    Value *v34 = builder.CreateSExt(v33, Type::getInt64Ty(context));
    Value *v35 = builder.CreateMul(v34, v34);
    Value *v36 = builder.CreateLShr(v35, builder.getInt64(10));
    Value *v37 = builder.CreateAdd(v36, v31);
    Value *v38 = builder.CreateShl(v37, builder.getInt64(32));
    Value *v39 = builder.CreateAShr(v38, builder.getInt64(22));
    Value *v40 = builder.CreateSDiv(v39, builder.getInt64(20480000));
    Value *v41 = builder.CreateMul(v40, builder.getInt64(255));
    Value *v42 = builder.CreateLShr(v41, builder.getInt64(10));
    Value *v43 = builder.CreateTrunc(v42, Type::getInt32Ty(context));
    Value *v44 = builder.CreateShl(v43, builder.getInt32(9));
    Value *v45 = builder.CreateShl(v43, builder.getInt32(3));
    Value *v46 = builder.CreateOr(v44, v45);
    Value *v47 = builder.CreateXor(v46, builder.getInt32(-1));
    Value *v48 = builder.CreateSub(v21, v13);
    // Вызов функции: llvm.abs.i32
    Value *v49 = builder.CreateCall(llvm_abs_i32Func, {v48, builder.getInt1(true), });
    Value *v50 = builder.CreateSub(v26, v16);
    // Вызов функции: llvm.abs.i32
    Value *v51 = builder.CreateCall(llvm_abs_i32Func, {v50, builder.getInt1(true), });
    Value *v52 = builder.CreateICmp(static_cast<CmpInst::Predicate>(40), v13, v21);
    Value *v53 = builder.CreateSelect(v52, builder.getInt32(1), builder.getInt32(-1));
    Value *v54 = builder.CreateICmp(static_cast<CmpInst::Predicate>(40), v16, v26);
    Value *v55 = builder.CreateSelect(v54, builder.getInt32(1), builder.getInt32(-1));
    Value *v56 = builder.CreateAnd(v13, builder.getInt32(511));
    Value *v57 = builder.CreateAnd(v16, builder.getInt32(255));
    // Вызов функции: simPutPixel
    builder.CreateCall(simPutPixelFunc, {v56, v57, v47, });
    Value *v58 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v13, v21);
    Value *v59 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v16, v26);
    Value *v60 = builder.CreateAnd(v58, v59);
    builder.CreateCondBr(v60, v84, v61);


    builder.SetInsertPoint(v61);
    Value *v62 = builder.CreateSub(v49, v51);
    Value *v63 = builder.CreateSub(builder.getInt32(0), v51);
      builder.CreateBr(v64);


    builder.SetInsertPoint(v64);
    PHINode *v65 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    PHINode *v66 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    PHINode *v67 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    Value *v68 = builder.CreateShl(v66, builder.getInt32(1));
    Value *v69 = builder.CreateICmp(static_cast<CmpInst::Predicate>(38), v68, v63);
    Value *v70 = builder.CreateSelect(v69, v51, builder.getInt32(0));
    Value *v71 = builder.CreateSub(v66, v70);
    Value *v72 = builder.CreateSelect(v69, v53, builder.getInt32(0));
    Value *v73 = builder.CreateAdd(v72, v65);
    Value *v74 = builder.CreateICmp(static_cast<CmpInst::Predicate>(40), v68, v49);
    Value *v75 = builder.CreateSelect(v74, v55, builder.getInt32(0));
    Value *v76 = builder.CreateAdd(v75, v67);
    Value *v77 = builder.CreateSelect(v74, v49, builder.getInt32(0));
    Value *v78 = builder.CreateAdd(v71, v77);
    Value *v79 = builder.CreateAnd(v73, builder.getInt32(511));
    Value *v80 = builder.CreateAnd(v76, builder.getInt32(255));
    // Вызов функции: simPutPixel
    builder.CreateCall(simPutPixelFunc, {v79, v80, v47, });
    Value *v81 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v73, v21);
    Value *v82 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v76, v26);
    Value *v83 = builder.CreateAnd(v82, v81);
    builder.CreateCondBr(v83, v84, v64);


    builder.SetInsertPoint(v84);
    Value *v85 = builder.CreateAdd(v6, builder.getInt64(1));
    Value *v86 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v85, builder.getInt64(1000));
    builder.CreateCondBr(v86, v4, v5);


    v6->addIncoming(builder.getInt64(0), v3);
    v6->addIncoming(v85, v84);
    v65->addIncoming(v13, v61);
    v65->addIncoming(v73, v64);
    v66->addIncoming(v62, v61);
    v66->addIncoming(v78, v64);
    v67->addIncoming(v16, v61);
    v67->addIncoming(v76, v64);
  }
  
  
  // Генерация функции: app
  {
    BasicBlock *v0 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *v5 = BasicBlock::Create(context, "", appFunc);
    BasicBlock *v9 = BasicBlock::Create(context, "", appFunc);


    builder.SetInsertPoint(v0);
    Value *v1 = builder.CreateAlloca(ArrayType::get(ArrayType::get(Type::getInt32Ty(context), 2), 1000));
    Value *v2 = builder.CreateAlloca(ArrayType::get(ArrayType::get(Type::getInt32Ty(context), 2), 1000));
    Value *v3 = builder.CreateAlloca(ArrayType::get(Type::getInt32Ty(context), 1000));
    Value *v4 = builder.CreateAlloca(Type::getInt32Ty(context));
    // Вызов функции: llvm.lifetime.start.p0
    builder.CreateCall(llvm_lifetime_start_p0Func, {builder.getInt64(8000), v1, });
    // Вызов функции: llvm.lifetime.start.p0
    builder.CreateCall(llvm_lifetime_start_p0Func, {builder.getInt64(8000), v2, });
    // Вызов функции: llvm.lifetime.start.p0
    builder.CreateCall(llvm_lifetime_start_p0Func, {builder.getInt64(4000), v3, });
    // Вызов функции: llvm.lifetime.start.p0
    builder.CreateCall(llvm_lifetime_start_p0Func, {builder.getInt64(4), v4, });
    builder.CreateAlignedStore(builder.getInt32(0), v4, MaybeAlign(4));
      builder.CreateBr(v5);


    builder.SetInsertPoint(v5);
    PHINode *v6 = builder.CreatePHI(Type::getInt32Ty(context), 2);
    // Вызов функции: init_particle
    builder.CreateCall(init_particleFunc, {v6, v1, v2, v3, v4, });
    Value *v7 = builder.CreateAdd(v6, builder.getInt32(1));
    Value *v8 = builder.CreateICmp(static_cast<CmpInst::Predicate>(32), v7, builder.getInt32(1000));
    builder.CreateCondBr(v8, v9, v5);


    builder.SetInsertPoint(v9);
    // Вызов функции: update_particles
    builder.CreateCall(update_particlesFunc, {v1, v2, v3, v4, });
    // Вызов функции: display_particles
    builder.CreateCall(display_particlesFunc, {v1, v2, v3, });
      builder.CreateBr(v9);


    v6->addIncoming(builder.getInt32(0), v0);
    v6->addIncoming(v7, v5);
  }


  // LLVM IR Interpreter

  module->print(outs(), nullptr);

  outs() << "[EE] Run\n";

  InitializeNativeTarget();

  InitializeNativeTargetAsmPrinter();

  ExecutionEngine *ee = EngineBuilder(std::unique_ptr<Module>(module)).create();
  ee->InstallLazyFunctionCreator([&](const std::string &fnName) -> void * {
    if (fnName == "simPutPixel") {
      return reinterpret_cast<void *>(simPutPixel);
    }
    if (fnName == "simFlush") {
      return reinterpret_cast<void *>(simFlush);
    }
    if (fnName == "simRand") {
      return reinterpret_cast<void *>(simRand);
    }
    if (fnName == "simClear") {
      return reinterpret_cast<void *>(simClear);
    }
    return nullptr;
  });
  ee->finalizeObject();
  simInit();
  ArrayRef<GenericValue> noargs;
  GenericValue v = ee->runFunction(appFunc, noargs);
  outs() << "[EE] Result: " << v.IntVal << "\n";
  simExit();
  return EXIT_SUCCESS;
  return 0;
}
