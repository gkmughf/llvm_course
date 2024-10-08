; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.particles_t = type { [8000 x [2 x i32]], [8000 x [2 x i32]], [8000 x i32], i32 }

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define dso_local i32 @fixed_mul(i32 noundef %0, i32 noundef %1) local_unnamed_addr #0 {
  %3 = sext i32 %0 to i64
  %4 = sext i32 %1 to i64
  %5 = mul nsw i64 %4, %3
  %6 = lshr i64 %5, 14
  %7 = trunc i64 %6 to i32
  ret i32 %7
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define dso_local i32 @fixed_div(i32 noundef %0, i32 noundef %1) local_unnamed_addr #0 {
  %3 = sext i32 %0 to i64
  %4 = shl nsw i64 %3, 14
  %5 = sext i32 %1 to i64
  %6 = sdiv i64 %4, %5
  %7 = trunc i64 %6 to i32
  ret i32 %7
}

; Function Attrs: nofree norecurse nosync nounwind sspstrong memory(none) uwtable
define dso_local i32 @fixed_sqrt(i32 noundef %0) local_unnamed_addr #1 {
  %2 = icmp slt i32 %0, 1
  br i1 %2, label %24, label %3

3:                                                ; preds = %1, %3
  %4 = phi i32 [ %6, %3 ], [ 65536, %1 ]
  %5 = icmp sgt i32 %4, %0
  %6 = lshr i32 %4, 2
  br i1 %5, label %3, label %7, !llvm.loop !5

7:                                                ; preds = %3
  %8 = icmp eq i32 %4, 0
  br i1 %8, label %24, label %9

9:                                                ; preds = %7, %9
  %10 = phi i32 [ %20, %9 ], [ %4, %7 ]
  %11 = phi i32 [ %19, %9 ], [ 0, %7 ]
  %12 = phi i32 [ %17, %9 ], [ %0, %7 ]
  %13 = add nsw i32 %10, %11
  %14 = icmp slt i32 %12, %13
  %15 = ashr i32 %11, 1
  %16 = select i1 %14, i32 0, i32 %13
  %17 = sub nsw i32 %12, %16
  %18 = select i1 %14, i32 0, i32 %10
  %19 = add nsw i32 %18, %15
  %20 = lshr i32 %10, 2
  %21 = icmp ult i32 %10, 4
  br i1 %21, label %22, label %9, !llvm.loop !7

22:                                               ; preds = %9
  %23 = shl i32 %19, 7
  br label %24

24:                                               ; preds = %7, %22, %1
  %25 = phi i32 [ 0, %1 ], [ 0, %7 ], [ %23, %22 ]
  ret i32 %25
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #2

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #2

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(argmem: readwrite) uwtable
define dso_local void @swap_i(ptr nocapture noundef %0, ptr nocapture noundef %1) local_unnamed_addr #3 {
  %3 = load i32, ptr %1, align 4, !tbaa !8
  %4 = load i32, ptr %0, align 4, !tbaa !8
  %5 = add nsw i32 %4, %3
  store i32 %5, ptr %0, align 4, !tbaa !8
  %6 = load i32, ptr %1, align 4, !tbaa !8
  %7 = sub nsw i32 %5, %6
  store i32 %7, ptr %1, align 4, !tbaa !8
  %8 = load i32, ptr %0, align 4, !tbaa !8
  %9 = sub nsw i32 %8, %7
  store i32 %9, ptr %0, align 4, !tbaa !8
  ret void
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define dso_local noundef i32 @clamp(i32 noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #0 {
  %4 = icmp sgt i32 %0, %2
  %5 = tail call i32 @llvm.smax.i32(i32 %0, i32 %1)
  %6 = select i1 %4, i32 %2, i32 %5
  ret i32 %6
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define dso_local i32 @abs(i32 noundef %0) local_unnamed_addr #0 {
  %2 = alloca [2 x i32], align 4
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %2) #10
  %3 = sub nsw i32 0, %0
  store i32 %3, ptr %2, align 4, !tbaa !8
  %4 = getelementptr inbounds i32, ptr %2, i64 1
  store i32 %0, ptr %4, align 4, !tbaa !8
  %5 = icmp sgt i32 %0, 0
  %6 = zext i1 %5 to i64
  %7 = getelementptr inbounds [2 x i32], ptr %2, i64 0, i64 %6
  %8 = load i32, ptr %7, align 4, !tbaa !8
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %2) #10
  ret i32 %8
}

; Function Attrs: nounwind sspstrong uwtable
define dso_local void @draw_line(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3, i32 noundef %4) local_unnamed_addr #4 {
  %6 = sub nsw i32 %2, %0
  %7 = tail call i32 @llvm.abs.i32(i32 %6, i1 true)
  %8 = sub nsw i32 %3, %1
  %9 = tail call i32 @llvm.abs.i32(i32 %8, i1 true)
  %10 = icmp slt i32 %0, %2
  %11 = select i1 %10, i32 1, i32 -1
  %12 = icmp slt i32 %1, %3
  %13 = select i1 %12, i32 1, i32 -1
  %14 = sub nsw i32 %7, %9
  %15 = sub nsw i32 0, %9
  br label %16

16:                                               ; preds = %30, %5
  %17 = phi i32 [ %1, %5 ], [ %39, %30 ]
  %18 = phi i32 [ %14, %5 ], [ %41, %30 ]
  %19 = phi i32 [ %0, %5 ], [ %36, %30 ]
  %20 = icmp ult i32 %19, 512
  %21 = icmp sgt i32 %17, -1
  %22 = select i1 %20, i1 %21, i1 false
  %23 = icmp slt i32 %17, 512
  %24 = select i1 %22, i1 %23, i1 false
  br i1 %24, label %25, label %26

25:                                               ; preds = %16
  tail call void @simPutPixel(i32 noundef %19, i32 noundef %17, i32 noundef %4) #10
  br label %26

26:                                               ; preds = %25, %16
  %27 = icmp eq i32 %19, %2
  %28 = icmp eq i32 %17, %3
  %29 = select i1 %27, i1 %28, i1 false
  br i1 %29, label %42, label %30

30:                                               ; preds = %26
  %31 = shl nsw i32 %18, 1
  %32 = icmp sgt i32 %31, %15
  %33 = select i1 %32, i32 %9, i32 0
  %34 = sub i32 %18, %33
  %35 = select i1 %32, i32 %11, i32 0
  %36 = add nsw i32 %35, %19
  %37 = icmp slt i32 %31, %7
  %38 = select i1 %37, i32 %13, i32 0
  %39 = add nsw i32 %38, %17
  %40 = select i1 %37, i32 %7, i32 0
  %41 = add nsw i32 %34, %40
  br label %16

42:                                               ; preds = %26
  ret void
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.abs.i32(i32, i1 immarg) #5

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #6

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(argmem: readwrite) uwtable
define dso_local void @swap(i32 noundef %0, i32 noundef %1, ptr nocapture noundef %2) local_unnamed_addr #3 {
  %4 = sext i32 %0 to i64
  %5 = getelementptr inbounds %struct.particles_t, ptr %2, i64 0, i32 2, i64 %4
  %6 = sext i32 %1 to i64
  %7 = getelementptr inbounds %struct.particles_t, ptr %2, i64 0, i32 2, i64 %6
  %8 = load i32, ptr %7, align 4, !tbaa !8
  %9 = load i32, ptr %5, align 4, !tbaa !8
  %10 = add nsw i32 %9, %8
  store i32 %10, ptr %5, align 4, !tbaa !8
  %11 = load i32, ptr %7, align 4, !tbaa !8
  %12 = sub nsw i32 %10, %11
  store i32 %12, ptr %7, align 4, !tbaa !8
  %13 = load i32, ptr %5, align 4, !tbaa !8
  %14 = sub nsw i32 %13, %12
  store i32 %14, ptr %5, align 4, !tbaa !8
  %15 = getelementptr inbounds %struct.particles_t, ptr %2, i64 0, i32 1, i64 %4
  %16 = getelementptr inbounds %struct.particles_t, ptr %2, i64 0, i32 1, i64 %6
  %17 = load i32, ptr %16, align 4, !tbaa !8
  %18 = load i32, ptr %15, align 4, !tbaa !8
  %19 = add nsw i32 %18, %17
  store i32 %19, ptr %15, align 4, !tbaa !8
  %20 = load i32, ptr %16, align 4, !tbaa !8
  %21 = sub nsw i32 %19, %20
  store i32 %21, ptr %16, align 4, !tbaa !8
  %22 = load i32, ptr %15, align 4, !tbaa !8
  %23 = sub nsw i32 %22, %21
  store i32 %23, ptr %15, align 4, !tbaa !8
  %24 = getelementptr inbounds %struct.particles_t, ptr %2, i64 0, i32 1, i64 %4, i64 1
  %25 = getelementptr inbounds %struct.particles_t, ptr %2, i64 0, i32 1, i64 %6, i64 1
  %26 = load i32, ptr %25, align 4, !tbaa !8
  %27 = load i32, ptr %24, align 4, !tbaa !8
  %28 = add nsw i32 %27, %26
  store i32 %28, ptr %24, align 4, !tbaa !8
  %29 = load i32, ptr %25, align 4, !tbaa !8
  %30 = sub nsw i32 %28, %29
  store i32 %30, ptr %25, align 4, !tbaa !8
  %31 = load i32, ptr %24, align 4, !tbaa !8
  %32 = sub nsw i32 %31, %30
  store i32 %32, ptr %24, align 4, !tbaa !8
  %33 = getelementptr inbounds [8000 x [2 x i32]], ptr %2, i64 0, i64 %4
  %34 = getelementptr inbounds [8000 x [2 x i32]], ptr %2, i64 0, i64 %6
  %35 = load i32, ptr %34, align 4, !tbaa !8
  %36 = load i32, ptr %33, align 4, !tbaa !8
  %37 = add nsw i32 %36, %35
  store i32 %37, ptr %33, align 4, !tbaa !8
  %38 = load i32, ptr %34, align 4, !tbaa !8
  %39 = sub nsw i32 %37, %38
  store i32 %39, ptr %34, align 4, !tbaa !8
  %40 = load i32, ptr %33, align 4, !tbaa !8
  %41 = sub nsw i32 %40, %39
  store i32 %41, ptr %33, align 4, !tbaa !8
  %42 = getelementptr inbounds [8000 x [2 x i32]], ptr %2, i64 0, i64 %4, i64 1
  %43 = getelementptr inbounds [8000 x [2 x i32]], ptr %2, i64 0, i64 %6, i64 1
  %44 = load i32, ptr %43, align 4, !tbaa !8
  %45 = load i32, ptr %42, align 4, !tbaa !8
  %46 = add nsw i32 %45, %44
  store i32 %46, ptr %42, align 4, !tbaa !8
  %47 = load i32, ptr %43, align 4, !tbaa !8
  %48 = sub nsw i32 %46, %47
  store i32 %48, ptr %43, align 4, !tbaa !8
  %49 = load i32, ptr %42, align 4, !tbaa !8
  %50 = sub nsw i32 %49, %48
  store i32 %50, ptr %42, align 4, !tbaa !8
  ret void
}

; Function Attrs: nounwind sspstrong uwtable
define dso_local void @init_particle(i32 noundef %0, ptr nocapture noundef %1) local_unnamed_addr #4 {
  %3 = sext i32 %0 to i64
  %4 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 2, i64 %3
  store i32 0, ptr %4, align 4, !tbaa !8
  %5 = tail call i32 (...) @simRand() #10
  %6 = srem i32 %5, 8388608
  %7 = getelementptr inbounds [8000 x [2 x i32]], ptr %1, i64 0, i64 %3
  store i32 %6, ptr %7, align 4, !tbaa !8
  %8 = tail call i32 (...) @simRand() #10
  %9 = srem i32 %8, 8388608
  %10 = getelementptr inbounds [8000 x [2 x i32]], ptr %1, i64 0, i64 %3, i64 1
  store i32 %9, ptr %10, align 4, !tbaa !8
  %11 = load i32, ptr %7, align 4, !tbaa !8
  %12 = add nsw i32 %11, -4194304
  %13 = add nsw i32 %9, -4194304
  %14 = sext i32 %12 to i64
  %15 = mul nsw i64 %14, %14
  %16 = lshr i64 %15, 14
  %17 = trunc i64 %16 to i32
  %18 = sext i32 %13 to i64
  %19 = mul nsw i64 %18, %18
  %20 = lshr i64 %19, 14
  %21 = trunc i64 %20 to i32
  %22 = add nsw i32 %17, %21
  %23 = icmp slt i32 %22, 1
  br i1 %23, label %50, label %24

24:                                               ; preds = %2, %24
  %25 = phi i32 [ %27, %24 ], [ 65536, %2 ]
  %26 = icmp sgt i32 %25, %22
  %27 = lshr i32 %25, 2
  br i1 %26, label %24, label %28, !llvm.loop !5

28:                                               ; preds = %24
  %29 = icmp eq i32 %25, 0
  br i1 %29, label %46, label %30

30:                                               ; preds = %28, %30
  %31 = phi i32 [ %41, %30 ], [ %25, %28 ]
  %32 = phi i32 [ %40, %30 ], [ 0, %28 ]
  %33 = phi i32 [ %38, %30 ], [ %22, %28 ]
  %34 = add nsw i32 %32, %31
  %35 = icmp slt i32 %33, %34
  %36 = ashr i32 %32, 1
  %37 = select i1 %35, i32 0, i32 %34
  %38 = sub nsw i32 %33, %37
  %39 = select i1 %35, i32 0, i32 %31
  %40 = add nsw i32 %39, %36
  %41 = lshr i32 %31, 2
  %42 = icmp ult i32 %31, 4
  br i1 %42, label %43, label %30, !llvm.loop !7

43:                                               ; preds = %30
  %44 = shl i32 %40, 7
  %45 = icmp sgt i32 %22, 268435456
  br i1 %45, label %102, label %48

46:                                               ; preds = %28
  %47 = icmp ugt i32 %22, 268435456
  br i1 %47, label %102, label %50

48:                                               ; preds = %43
  %49 = icmp eq i32 %44, 0
  br i1 %49, label %50, label %52

50:                                               ; preds = %46, %2, %48
  %51 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %3
  store i32 0, ptr %51, align 4, !tbaa !8
  br label %96

52:                                               ; preds = %48
  %53 = shl nsw i64 %14, 14
  %54 = sext i32 %44 to i64
  %55 = sdiv i64 %53, %54
  %56 = shl nsw i64 %18, 14
  %57 = sdiv i64 %56, %54
  %58 = sdiv i64 1342177280000, %54
  %59 = trunc i64 %58 to i32
  %60 = icmp slt i32 %59, 1
  br i1 %60, label %83, label %61

61:                                               ; preds = %52, %61
  %62 = phi i32 [ %64, %61 ], [ 65536, %52 ]
  %63 = icmp sgt i32 %62, %59
  %64 = lshr i32 %62, 2
  br i1 %63, label %61, label %65, !llvm.loop !5

65:                                               ; preds = %61
  %66 = icmp eq i32 %62, 0
  br i1 %66, label %83, label %67

67:                                               ; preds = %65, %67
  %68 = phi i32 [ %78, %67 ], [ %62, %65 ]
  %69 = phi i32 [ %77, %67 ], [ 0, %65 ]
  %70 = phi i32 [ %75, %67 ], [ %59, %65 ]
  %71 = add nsw i32 %69, %68
  %72 = icmp slt i32 %70, %71
  %73 = ashr i32 %69, 1
  %74 = select i1 %72, i32 0, i32 %71
  %75 = sub nsw i32 %70, %74
  %76 = select i1 %72, i32 0, i32 %68
  %77 = add nsw i32 %76, %73
  %78 = lshr i32 %68, 2
  %79 = icmp ult i32 %68, 4
  br i1 %79, label %80, label %67, !llvm.loop !7

80:                                               ; preds = %67
  %81 = shl i32 %77, 7
  %82 = sext i32 %81 to i64
  br label %83

83:                                               ; preds = %52, %65, %80
  %84 = phi i64 [ 0, %52 ], [ 0, %65 ], [ %82, %80 ]
  %85 = mul i64 %57, -4294967296
  %86 = ashr exact i64 %85, 32
  %87 = mul nsw i64 %84, %86
  %88 = lshr i64 %87, 14
  %89 = trunc i64 %88 to i32
  %90 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %3
  store i32 %89, ptr %90, align 4, !tbaa !8
  %91 = shl i64 %55, 32
  %92 = ashr exact i64 %91, 32
  %93 = mul nsw i64 %84, %92
  %94 = lshr i64 %93, 14
  %95 = trunc i64 %94 to i32
  br label %96

96:                                               ; preds = %83, %50
  %97 = phi i32 [ %95, %83 ], [ 0, %50 ]
  %98 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %3, i64 1
  store i32 %97, ptr %98, align 4, !tbaa !8
  store i32 1, ptr %4, align 4, !tbaa !8
  %99 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 3
  %100 = load i32, ptr %99, align 4, !tbaa !12
  %101 = add nsw i32 %100, 1
  store i32 %101, ptr %99, align 4, !tbaa !12
  br label %102

102:                                              ; preds = %46, %43, %96
  ret void
}

declare i32 @simRand(...) local_unnamed_addr #6

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(argmem: readwrite) uwtable
define dso_local void @delete_particle(i32 noundef %0, ptr nocapture noundef %1) local_unnamed_addr #3 {
  %3 = sext i32 %0 to i64
  %4 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 2, i64 %3
  store i32 0, ptr %4, align 4, !tbaa !8
  %5 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 3
  %6 = load i32, ptr %5, align 4, !tbaa !12
  %7 = add nsw i32 %6, -1
  store i32 %7, ptr %5, align 4, !tbaa !12
  %8 = sext i32 %7 to i64
  %9 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 2, i64 %8
  %10 = load i32, ptr %9, align 4, !tbaa !8
  %11 = load i32, ptr %4, align 4, !tbaa !8
  %12 = add nsw i32 %11, %10
  store i32 %12, ptr %4, align 4, !tbaa !8
  %13 = load i32, ptr %9, align 4, !tbaa !8
  %14 = sub nsw i32 %12, %13
  store i32 %14, ptr %9, align 4, !tbaa !8
  %15 = load i32, ptr %4, align 4, !tbaa !8
  %16 = sub nsw i32 %15, %14
  store i32 %16, ptr %4, align 4, !tbaa !8
  %17 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %3
  %18 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %8
  %19 = load i32, ptr %18, align 4, !tbaa !8
  %20 = load i32, ptr %17, align 4, !tbaa !8
  %21 = add nsw i32 %20, %19
  store i32 %21, ptr %17, align 4, !tbaa !8
  %22 = load i32, ptr %18, align 4, !tbaa !8
  %23 = sub nsw i32 %21, %22
  store i32 %23, ptr %18, align 4, !tbaa !8
  %24 = load i32, ptr %17, align 4, !tbaa !8
  %25 = sub nsw i32 %24, %23
  store i32 %25, ptr %17, align 4, !tbaa !8
  %26 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %3, i64 1
  %27 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %8, i64 1
  %28 = load i32, ptr %27, align 4, !tbaa !8
  %29 = load i32, ptr %26, align 4, !tbaa !8
  %30 = add nsw i32 %29, %28
  store i32 %30, ptr %26, align 4, !tbaa !8
  %31 = load i32, ptr %27, align 4, !tbaa !8
  %32 = sub nsw i32 %30, %31
  store i32 %32, ptr %27, align 4, !tbaa !8
  %33 = load i32, ptr %26, align 4, !tbaa !8
  %34 = sub nsw i32 %33, %32
  store i32 %34, ptr %26, align 4, !tbaa !8
  %35 = getelementptr inbounds [8000 x [2 x i32]], ptr %1, i64 0, i64 %3
  %36 = getelementptr inbounds [8000 x [2 x i32]], ptr %1, i64 0, i64 %8
  %37 = load i32, ptr %36, align 4, !tbaa !8
  %38 = load i32, ptr %35, align 4, !tbaa !8
  %39 = add nsw i32 %38, %37
  store i32 %39, ptr %35, align 4, !tbaa !8
  %40 = load i32, ptr %36, align 4, !tbaa !8
  %41 = sub nsw i32 %39, %40
  store i32 %41, ptr %36, align 4, !tbaa !8
  %42 = load i32, ptr %35, align 4, !tbaa !8
  %43 = sub nsw i32 %42, %41
  store i32 %43, ptr %35, align 4, !tbaa !8
  %44 = getelementptr inbounds [8000 x [2 x i32]], ptr %1, i64 0, i64 %3, i64 1
  %45 = getelementptr inbounds [8000 x [2 x i32]], ptr %1, i64 0, i64 %8, i64 1
  %46 = load i32, ptr %45, align 4, !tbaa !8
  %47 = load i32, ptr %44, align 4, !tbaa !8
  %48 = add nsw i32 %47, %46
  store i32 %48, ptr %44, align 4, !tbaa !8
  %49 = load i32, ptr %45, align 4, !tbaa !8
  %50 = sub nsw i32 %48, %49
  store i32 %50, ptr %45, align 4, !tbaa !8
  %51 = load i32, ptr %44, align 4, !tbaa !8
  %52 = sub nsw i32 %51, %50
  store i32 %52, ptr %44, align 4, !tbaa !8
  ret void
}

; Function Attrs: nounwind sspstrong uwtable
define dso_local void @init_particles(ptr nocapture noundef %0) local_unnamed_addr #4 {
  br label %3

2:                                                ; preds = %3
  ret void

3:                                                ; preds = %1, %3
  %4 = phi i32 [ 0, %1 ], [ %5, %3 ]
  tail call void @init_particle(i32 noundef %4, ptr noundef %0)
  %5 = add nuw nsw i32 %4, 1
  %6 = icmp eq i32 %5, 8000
  br i1 %6, label %2, label %3, !llvm.loop !14
}

; Function Attrs: nounwind sspstrong uwtable
define dso_local void @update_particles(ptr nocapture noundef %0) local_unnamed_addr #4 {
  %2 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 3
  %3 = load i32, ptr %2, align 4, !tbaa !12
  %4 = icmp slt i32 %3, 8000
  br i1 %4, label %6, label %5

5:                                                ; preds = %6, %1
  br label %12

6:                                                ; preds = %1, %6
  %7 = phi i32 [ %9, %6 ], [ %3, %1 ]
  %8 = load i32, ptr %2, align 4, !tbaa !12
  tail call void @init_particle(i32 noundef %8, ptr noundef nonnull %0)
  %9 = add i32 %7, 1
  %10 = icmp eq i32 %9, 8000
  br i1 %10, label %5, label %6, !llvm.loop !15

11:                                               ; preds = %113
  ret void

12:                                               ; preds = %5, %113
  %13 = phi i32 [ %115, %113 ], [ 0, %5 ]
  %14 = sext i32 %13 to i64
  %15 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 2, i64 %14
  %16 = load i32, ptr %15, align 4, !tbaa !8
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %113, label %18

18:                                               ; preds = %12
  %19 = getelementptr inbounds [8000 x [2 x i32]], ptr %0, i64 0, i64 %14
  %20 = load i32, ptr %19, align 4, !tbaa !8
  %21 = sub i32 4194304, %20
  %22 = getelementptr inbounds [8000 x [2 x i32]], ptr %0, i64 0, i64 %14, i64 1
  %23 = load i32, ptr %22, align 4, !tbaa !8
  %24 = sub i32 4194304, %23
  %25 = sext i32 %21 to i64
  %26 = mul nsw i64 %25, %25
  %27 = lshr i64 %26, 14
  %28 = trunc i64 %27 to i32
  %29 = sext i32 %24 to i64
  %30 = mul nsw i64 %29, %29
  %31 = lshr i64 %30, 14
  %32 = trunc i64 %31 to i32
  %33 = add nsw i32 %32, %28
  %34 = icmp slt i32 %33, 40960000
  br i1 %34, label %35, label %82

35:                                               ; preds = %18
  store i32 0, ptr %15, align 4, !tbaa !8
  %36 = load i32, ptr %2, align 4, !tbaa !12
  %37 = add nsw i32 %36, -1
  store i32 %37, ptr %2, align 4, !tbaa !12
  %38 = sext i32 %37 to i64
  %39 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 2, i64 %38
  %40 = load i32, ptr %39, align 4, !tbaa !8
  %41 = load i32, ptr %15, align 4, !tbaa !8
  %42 = add nsw i32 %41, %40
  store i32 %42, ptr %15, align 4, !tbaa !8
  %43 = load i32, ptr %39, align 4, !tbaa !8
  %44 = sub nsw i32 %42, %43
  store i32 %44, ptr %39, align 4, !tbaa !8
  %45 = load i32, ptr %15, align 4, !tbaa !8
  %46 = sub nsw i32 %45, %44
  store i32 %46, ptr %15, align 4, !tbaa !8
  %47 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %14
  %48 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %38
  %49 = load i32, ptr %48, align 4, !tbaa !8
  %50 = load i32, ptr %47, align 4, !tbaa !8
  %51 = add nsw i32 %50, %49
  store i32 %51, ptr %47, align 4, !tbaa !8
  %52 = load i32, ptr %48, align 4, !tbaa !8
  %53 = sub nsw i32 %51, %52
  store i32 %53, ptr %48, align 4, !tbaa !8
  %54 = load i32, ptr %47, align 4, !tbaa !8
  %55 = sub nsw i32 %54, %53
  store i32 %55, ptr %47, align 4, !tbaa !8
  %56 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %14, i64 1
  %57 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %38, i64 1
  %58 = load i32, ptr %57, align 4, !tbaa !8
  %59 = load i32, ptr %56, align 4, !tbaa !8
  %60 = add nsw i32 %59, %58
  store i32 %60, ptr %56, align 4, !tbaa !8
  %61 = load i32, ptr %57, align 4, !tbaa !8
  %62 = sub nsw i32 %60, %61
  store i32 %62, ptr %57, align 4, !tbaa !8
  %63 = load i32, ptr %56, align 4, !tbaa !8
  %64 = sub nsw i32 %63, %62
  store i32 %64, ptr %56, align 4, !tbaa !8
  %65 = getelementptr inbounds [8000 x [2 x i32]], ptr %0, i64 0, i64 %38
  %66 = load i32, ptr %65, align 4, !tbaa !8
  %67 = load i32, ptr %19, align 4, !tbaa !8
  %68 = add nsw i32 %67, %66
  store i32 %68, ptr %19, align 4, !tbaa !8
  %69 = load i32, ptr %65, align 4, !tbaa !8
  %70 = sub nsw i32 %68, %69
  store i32 %70, ptr %65, align 4, !tbaa !8
  %71 = load i32, ptr %19, align 4, !tbaa !8
  %72 = sub nsw i32 %71, %70
  store i32 %72, ptr %19, align 4, !tbaa !8
  %73 = getelementptr inbounds [8000 x [2 x i32]], ptr %0, i64 0, i64 %38, i64 1
  %74 = load i32, ptr %73, align 4, !tbaa !8
  %75 = load i32, ptr %22, align 4, !tbaa !8
  %76 = add nsw i32 %75, %74
  store i32 %76, ptr %22, align 4, !tbaa !8
  %77 = load i32, ptr %73, align 4, !tbaa !8
  %78 = sub nsw i32 %76, %77
  store i32 %78, ptr %73, align 4, !tbaa !8
  %79 = load i32, ptr %22, align 4, !tbaa !8
  %80 = sub nsw i32 %79, %78
  store i32 %80, ptr %22, align 4, !tbaa !8
  %81 = add nsw i32 %13, -1
  br label %113

82:                                               ; preds = %18
  %83 = zext nneg i32 %33 to i64
  %84 = udiv i64 1342177280000, %83
  %85 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %14
  %86 = load i32, ptr %85, align 4, !tbaa !8
  %87 = shl nsw i64 %25, 18
  %88 = mul i64 %87, %84
  %89 = ashr i64 %88, 32
  %90 = mul nsw i64 %89, 546
  %91 = lshr i64 %90, 14
  %92 = trunc i64 %91 to i32
  %93 = add nsw i32 %86, %92
  %94 = tail call i32 @llvm.smax.i32(i32 %93, i32 -1638400)
  %95 = tail call i32 @llvm.smin.i32(i32 %94, i32 1638400)
  store i32 %95, ptr %85, align 4, !tbaa !8
  %96 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %14, i64 1
  %97 = load i32, ptr %96, align 4, !tbaa !8
  %98 = shl nsw i64 %29, 18
  %99 = mul i64 %98, %84
  %100 = ashr i64 %99, 32
  %101 = mul nsw i64 %100, 546
  %102 = lshr i64 %101, 14
  %103 = trunc i64 %102 to i32
  %104 = add nsw i32 %97, %103
  %105 = tail call i32 @llvm.smax.i32(i32 %104, i32 -1638400)
  %106 = tail call i32 @llvm.smin.i32(i32 %105, i32 1638400)
  store i32 %106, ptr %96, align 4, !tbaa !8
  %107 = mul nsw i32 %95, 546
  %108 = ashr i32 %107, 14
  %109 = add nsw i32 %108, %20
  store i32 %109, ptr %19, align 4, !tbaa !8
  %110 = mul nsw i32 %106, 546
  %111 = ashr i32 %110, 14
  %112 = add nsw i32 %111, %23
  store i32 %112, ptr %22, align 4, !tbaa !8
  br label %113

113:                                              ; preds = %35, %82, %12
  %114 = phi i32 [ %13, %12 ], [ %81, %35 ], [ %13, %82 ]
  %115 = add nsw i32 %114, 1
  %116 = icmp slt i32 %114, 7999
  br i1 %116, label %12, label %11, !llvm.loop !16
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(argmem: read) uwtable
define dso_local i32 @get_velocity_sq(i32 noundef %0, ptr nocapture noundef readonly %1) local_unnamed_addr #7 {
  %3 = sext i32 %0 to i64
  %4 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %3
  %5 = load i32, ptr %4, align 4, !tbaa !8
  %6 = sext i32 %5 to i64
  %7 = mul nsw i64 %6, %6
  %8 = lshr i64 %7, 14
  %9 = trunc i64 %8 to i32
  %10 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %3, i64 1
  %11 = load i32, ptr %10, align 4, !tbaa !8
  %12 = sext i32 %11 to i64
  %13 = mul nsw i64 %12, %12
  %14 = lshr i64 %13, 14
  %15 = trunc i64 %14 to i32
  %16 = add nsw i32 %15, %9
  ret i32 %16
}

; Function Attrs: nounwind sspstrong uwtable
define dso_local void @display_particles(ptr nocapture noundef readonly %0) local_unnamed_addr #4 {
  tail call void @simClear(i32 noundef -16777216) #10
  br label %3

2:                                                ; preds = %78
  tail call void (...) @simFlush() #10
  ret void

3:                                                ; preds = %1, %78
  %4 = phi i64 [ 0, %1 ], [ %79, %78 ]
  %5 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 2, i64 %4
  %6 = load i32, ptr %5, align 4, !tbaa !8
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %78, label %8

8:                                                ; preds = %3
  %9 = getelementptr inbounds [8000 x [2 x i32]], ptr %0, i64 0, i64 %4
  %10 = load i32, ptr %9, align 4, !tbaa !8
  %11 = ashr i32 %10, 14
  %12 = getelementptr inbounds [8000 x [2 x i32]], ptr %0, i64 0, i64 %4, i64 1
  %13 = load i32, ptr %12, align 4, !tbaa !8
  %14 = ashr i32 %13, 14
  %15 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %4
  %16 = load i32, ptr %15, align 4, !tbaa !8
  %17 = sdiv i32 %16, -10
  %18 = add i32 %17, %10
  %19 = ashr i32 %18, 14
  %20 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %4, i64 1
  %21 = load i32, ptr %20, align 4, !tbaa !8
  %22 = sdiv i32 %21, -10
  %23 = add i32 %22, %13
  %24 = ashr i32 %23, 14
  %25 = sext i32 %16 to i64
  %26 = mul nsw i64 %25, %25
  %27 = lshr i64 %26, 14
  %28 = sext i32 %21 to i64
  %29 = mul nsw i64 %28, %28
  %30 = lshr i64 %29, 14
  %31 = add nuw nsw i64 %30, %27
  %32 = shl i64 %31, 32
  %33 = ashr exact i64 %32, 18
  %34 = sdiv i64 %33, 327680000
  %35 = mul nsw i64 %34, 255
  %36 = lshr i64 %35, 14
  %37 = trunc i64 %36 to i32
  %38 = shl i32 %37, 9
  %39 = shl i32 %37, 3
  %40 = or i32 %38, %39
  %41 = xor i32 %40, -1
  %42 = sub nsw i32 %19, %11
  %43 = tail call i32 @llvm.abs.i32(i32 %42, i1 true)
  %44 = sub nsw i32 %24, %14
  %45 = tail call i32 @llvm.abs.i32(i32 %44, i1 true)
  %46 = icmp slt i32 %11, %19
  %47 = select i1 %46, i32 1, i32 -1
  %48 = icmp slt i32 %14, %24
  %49 = select i1 %48, i32 1, i32 -1
  %50 = sub nsw i32 %43, %45
  %51 = sub nsw i32 0, %45
  br label %52

52:                                               ; preds = %66, %8
  %53 = phi i32 [ %14, %8 ], [ %75, %66 ]
  %54 = phi i32 [ %50, %8 ], [ %77, %66 ]
  %55 = phi i32 [ %11, %8 ], [ %72, %66 ]
  %56 = icmp ult i32 %55, 512
  %57 = icmp sgt i32 %53, -1
  %58 = select i1 %56, i1 %57, i1 false
  %59 = icmp slt i32 %53, 512
  %60 = select i1 %58, i1 %59, i1 false
  br i1 %60, label %61, label %62

61:                                               ; preds = %52
  tail call void @simPutPixel(i32 noundef %55, i32 noundef %53, i32 noundef %41) #10
  br label %62

62:                                               ; preds = %61, %52
  %63 = icmp eq i32 %55, %19
  %64 = icmp eq i32 %53, %24
  %65 = select i1 %63, i1 %64, i1 false
  br i1 %65, label %78, label %66

66:                                               ; preds = %62
  %67 = shl nsw i32 %54, 1
  %68 = icmp sgt i32 %67, %51
  %69 = select i1 %68, i32 %45, i32 0
  %70 = sub i32 %54, %69
  %71 = select i1 %68, i32 %47, i32 0
  %72 = add nsw i32 %71, %55
  %73 = icmp slt i32 %67, %43
  %74 = select i1 %73, i32 %49, i32 0
  %75 = add nsw i32 %74, %53
  %76 = select i1 %73, i32 %43, i32 0
  %77 = add nsw i32 %70, %76
  br label %52

78:                                               ; preds = %62, %3
  %79 = add nuw nsw i64 %4, 1
  %80 = icmp eq i64 %79, 8000
  br i1 %80, label %2, label %3, !llvm.loop !17
}

declare void @simClear(i32 noundef) local_unnamed_addr #6

declare void @simFlush(...) local_unnamed_addr #6

; Function Attrs: noreturn nounwind sspstrong uwtable
define dso_local void @app() local_unnamed_addr #8 {
  %1 = alloca %struct.particles_t, align 4
  call void @llvm.lifetime.start.p0(i64 160004, ptr nonnull %1) #10
  %2 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 3
  store i32 0, ptr %2, align 4, !tbaa !12
  br label %3

3:                                                ; preds = %3, %0
  %4 = phi i32 [ 0, %0 ], [ %5, %3 ]
  call void @init_particle(i32 noundef %4, ptr noundef nonnull %1)
  %5 = add nuw nsw i32 %4, 1
  %6 = icmp eq i32 %5, 8000
  br i1 %6, label %7, label %3, !llvm.loop !14

7:                                                ; preds = %3, %7
  call void @update_particles(ptr noundef nonnull %1)
  call void @display_particles(ptr noundef nonnull %1)
  br label %7
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.smax.i32(i32, i32) #9

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.smin.i32(i32, i32) #9

attributes #0 = { mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree norecurse nosync nounwind sspstrong memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #3 = { mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #5 = { mustprogress nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #6 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #7 = { mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #8 = { noreturn nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #9 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #10 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"clang version 18.1.8"}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.mustprogress"}
!7 = distinct !{!7, !6}
!8 = !{!9, !9, i64 0}
!9 = !{!"int", !10, i64 0}
!10 = !{!"omnipotent char", !11, i64 0}
!11 = !{!"Simple C/C++ TBAA"}
!12 = !{!13, !9, i64 160000}
!13 = !{!"particles_t", !10, i64 0, !10, i64 64000, !10, i64 128000, !9, i64 160000}
!14 = distinct !{!14, !6}
!15 = distinct !{!15, !6}
!16 = distinct !{!16, !6}
!17 = distinct !{!17, !6}
