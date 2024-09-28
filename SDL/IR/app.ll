; ModuleID = 'app.c'
source_filename = "app.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.particles_t = type { [8000 x [2 x i32]], [8000 x [2 x i32]], [8000 x i32], i32 }

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(argmem: readwrite) uwtable
define dso_local void @swap_i(ptr nocapture noundef %0, ptr nocapture noundef %1) local_unnamed_addr #0 {
  %3 = load i32, ptr %1, align 4, !tbaa !5
  %4 = load i32, ptr %0, align 4, !tbaa !5
  %5 = add nsw i32 %4, %3
  store i32 %5, ptr %0, align 4, !tbaa !5
  %6 = load i32, ptr %1, align 4, !tbaa !5
  %7 = sub nsw i32 %5, %6
  store i32 %7, ptr %1, align 4, !tbaa !5
  %8 = load i32, ptr %0, align 4, !tbaa !5
  %9 = sub nsw i32 %8, %7
  store i32 %9, ptr %0, align 4, !tbaa !5
  ret void
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define dso_local noundef i32 @clamp(i32 noundef %0, i32 noundef %1, i32 noundef %2) local_unnamed_addr #1 {
  %4 = icmp sgt i32 %0, %2
  %5 = tail call i32 @llvm.smax.i32(i32 %0, i32 %1)
  %6 = select i1 %4, i32 %2, i32 %5
  ret i32 %6
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable
define dso_local i32 @abs(i32 noundef %0) local_unnamed_addr #1 {
  %2 = alloca [2 x i32], align 4
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %2) #9
  %3 = sub nsw i32 0, %0
  store i32 %3, ptr %2, align 4, !tbaa !5
  %4 = getelementptr inbounds i32, ptr %2, i64 1
  store i32 %0, ptr %4, align 4, !tbaa !5
  %5 = icmp sgt i32 %0, 0
  %6 = zext i1 %5 to i64
  %7 = getelementptr inbounds [2 x i32], ptr %2, i64 0, i64 %6
  %8 = load i32, ptr %7, align 4, !tbaa !5
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %2) #9
  ret i32 %8
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #2

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #2

; Function Attrs: nounwind sspstrong uwtable
define dso_local void @draw_line(i32 noundef %0, i32 noundef %1, i32 noundef %2, i32 noundef %3, i32 noundef %4) local_unnamed_addr #3 {
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
  tail call void @simPutPixel(i32 noundef %19, i32 noundef %17, i32 noundef %4) #9
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
declare i32 @llvm.abs.i32(i32, i1 immarg) #4

declare void @simPutPixel(i32 noundef, i32 noundef, i32 noundef) local_unnamed_addr #5

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(argmem: readwrite) uwtable
define dso_local void @swap(i32 noundef %0, i32 noundef %1, ptr nocapture noundef %2) local_unnamed_addr #0 {
  %4 = sext i32 %0 to i64
  %5 = getelementptr inbounds %struct.particles_t, ptr %2, i64 0, i32 2, i64 %4
  %6 = sext i32 %1 to i64
  %7 = getelementptr inbounds %struct.particles_t, ptr %2, i64 0, i32 2, i64 %6
  %8 = load i32, ptr %7, align 4, !tbaa !5
  %9 = load i32, ptr %5, align 4, !tbaa !5
  %10 = add nsw i32 %9, %8
  store i32 %10, ptr %5, align 4, !tbaa !5
  %11 = load i32, ptr %7, align 4, !tbaa !5
  %12 = sub nsw i32 %10, %11
  store i32 %12, ptr %7, align 4, !tbaa !5
  %13 = load i32, ptr %5, align 4, !tbaa !5
  %14 = sub nsw i32 %13, %12
  store i32 %14, ptr %5, align 4, !tbaa !5
  %15 = getelementptr inbounds %struct.particles_t, ptr %2, i64 0, i32 1, i64 %4
  %16 = getelementptr inbounds %struct.particles_t, ptr %2, i64 0, i32 1, i64 %6
  %17 = load i32, ptr %16, align 4, !tbaa !5
  %18 = load i32, ptr %15, align 4, !tbaa !5
  %19 = add nsw i32 %18, %17
  store i32 %19, ptr %15, align 4, !tbaa !5
  %20 = load i32, ptr %16, align 4, !tbaa !5
  %21 = sub nsw i32 %19, %20
  store i32 %21, ptr %16, align 4, !tbaa !5
  %22 = load i32, ptr %15, align 4, !tbaa !5
  %23 = sub nsw i32 %22, %21
  store i32 %23, ptr %15, align 4, !tbaa !5
  %24 = getelementptr inbounds %struct.particles_t, ptr %2, i64 0, i32 1, i64 %4, i64 1
  %25 = getelementptr inbounds %struct.particles_t, ptr %2, i64 0, i32 1, i64 %6, i64 1
  %26 = load i32, ptr %25, align 4, !tbaa !5
  %27 = load i32, ptr %24, align 4, !tbaa !5
  %28 = add nsw i32 %27, %26
  store i32 %28, ptr %24, align 4, !tbaa !5
  %29 = load i32, ptr %25, align 4, !tbaa !5
  %30 = sub nsw i32 %28, %29
  store i32 %30, ptr %25, align 4, !tbaa !5
  %31 = load i32, ptr %24, align 4, !tbaa !5
  %32 = sub nsw i32 %31, %30
  store i32 %32, ptr %24, align 4, !tbaa !5
  %33 = getelementptr inbounds [8000 x [2 x i32]], ptr %2, i64 0, i64 %4
  %34 = getelementptr inbounds [8000 x [2 x i32]], ptr %2, i64 0, i64 %6
  %35 = load i32, ptr %34, align 4, !tbaa !5
  %36 = load i32, ptr %33, align 4, !tbaa !5
  %37 = add nsw i32 %36, %35
  store i32 %37, ptr %33, align 4, !tbaa !5
  %38 = load i32, ptr %34, align 4, !tbaa !5
  %39 = sub nsw i32 %37, %38
  store i32 %39, ptr %34, align 4, !tbaa !5
  %40 = load i32, ptr %33, align 4, !tbaa !5
  %41 = sub nsw i32 %40, %39
  store i32 %41, ptr %33, align 4, !tbaa !5
  %42 = getelementptr inbounds [8000 x [2 x i32]], ptr %2, i64 0, i64 %4, i64 1
  %43 = getelementptr inbounds [8000 x [2 x i32]], ptr %2, i64 0, i64 %6, i64 1
  %44 = load i32, ptr %43, align 4, !tbaa !5
  %45 = load i32, ptr %42, align 4, !tbaa !5
  %46 = add nsw i32 %45, %44
  store i32 %46, ptr %42, align 4, !tbaa !5
  %47 = load i32, ptr %43, align 4, !tbaa !5
  %48 = sub nsw i32 %46, %47
  store i32 %48, ptr %43, align 4, !tbaa !5
  %49 = load i32, ptr %42, align 4, !tbaa !5
  %50 = sub nsw i32 %49, %48
  store i32 %50, ptr %42, align 4, !tbaa !5
  ret void
}

; Function Attrs: nounwind sspstrong uwtable
define dso_local void @init_particle(i32 noundef %0, ptr nocapture noundef %1) local_unnamed_addr #3 {
  %3 = sext i32 %0 to i64
  %4 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 2, i64 %3
  store i32 0, ptr %4, align 4, !tbaa !5
  %5 = tail call i32 (...) @simRand() #9
  %6 = srem i32 %5, 8388608
  %7 = getelementptr inbounds [8000 x [2 x i32]], ptr %1, i64 0, i64 %3
  store i32 %6, ptr %7, align 4, !tbaa !5
  %8 = tail call i32 (...) @simRand() #9
  %9 = srem i32 %8, 8388608
  %10 = getelementptr inbounds [8000 x [2 x i32]], ptr %1, i64 0, i64 %3, i64 1
  store i32 %9, ptr %10, align 4, !tbaa !5
  %11 = load i32, ptr %7, align 4, !tbaa !5
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
  br i1 %26, label %24, label %28, !llvm.loop !9

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
  br i1 %42, label %43, label %30, !llvm.loop !11

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
  store i32 0, ptr %51, align 4, !tbaa !5
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
  br i1 %63, label %61, label %65, !llvm.loop !9

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
  br i1 %79, label %80, label %67, !llvm.loop !11

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
  store i32 %89, ptr %90, align 4, !tbaa !5
  %91 = shl i64 %55, 32
  %92 = ashr exact i64 %91, 32
  %93 = mul nsw i64 %84, %92
  %94 = lshr i64 %93, 14
  %95 = trunc i64 %94 to i32
  br label %96

96:                                               ; preds = %83, %50
  %97 = phi i32 [ %95, %83 ], [ 0, %50 ]
  %98 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %3, i64 1
  store i32 %97, ptr %98, align 4, !tbaa !5
  store i32 1, ptr %4, align 4, !tbaa !5
  %99 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 3
  %100 = load i32, ptr %99, align 4, !tbaa !12
  %101 = add nsw i32 %100, 1
  store i32 %101, ptr %99, align 4, !tbaa !12
  br label %102

102:                                              ; preds = %46, %43, %96
  ret void
}

declare i32 @simRand(...) local_unnamed_addr #5

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(argmem: readwrite) uwtable
define dso_local void @delete_particle(i32 noundef %0, ptr nocapture noundef %1) local_unnamed_addr #0 {
  %3 = sext i32 %0 to i64
  %4 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 2, i64 %3
  store i32 0, ptr %4, align 4, !tbaa !5
  %5 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 3
  %6 = load i32, ptr %5, align 4, !tbaa !12
  %7 = add nsw i32 %6, -1
  store i32 %7, ptr %5, align 4, !tbaa !12
  %8 = sext i32 %7 to i64
  %9 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 2, i64 %8
  %10 = load i32, ptr %9, align 4, !tbaa !5
  %11 = load i32, ptr %4, align 4, !tbaa !5
  %12 = add nsw i32 %11, %10
  store i32 %12, ptr %4, align 4, !tbaa !5
  %13 = load i32, ptr %9, align 4, !tbaa !5
  %14 = sub nsw i32 %12, %13
  store i32 %14, ptr %9, align 4, !tbaa !5
  %15 = load i32, ptr %4, align 4, !tbaa !5
  %16 = sub nsw i32 %15, %14
  store i32 %16, ptr %4, align 4, !tbaa !5
  %17 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %3
  %18 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %8
  %19 = load i32, ptr %18, align 4, !tbaa !5
  %20 = load i32, ptr %17, align 4, !tbaa !5
  %21 = add nsw i32 %20, %19
  store i32 %21, ptr %17, align 4, !tbaa !5
  %22 = load i32, ptr %18, align 4, !tbaa !5
  %23 = sub nsw i32 %21, %22
  store i32 %23, ptr %18, align 4, !tbaa !5
  %24 = load i32, ptr %17, align 4, !tbaa !5
  %25 = sub nsw i32 %24, %23
  store i32 %25, ptr %17, align 4, !tbaa !5
  %26 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %3, i64 1
  %27 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %8, i64 1
  %28 = load i32, ptr %27, align 4, !tbaa !5
  %29 = load i32, ptr %26, align 4, !tbaa !5
  %30 = add nsw i32 %29, %28
  store i32 %30, ptr %26, align 4, !tbaa !5
  %31 = load i32, ptr %27, align 4, !tbaa !5
  %32 = sub nsw i32 %30, %31
  store i32 %32, ptr %27, align 4, !tbaa !5
  %33 = load i32, ptr %26, align 4, !tbaa !5
  %34 = sub nsw i32 %33, %32
  store i32 %34, ptr %26, align 4, !tbaa !5
  %35 = getelementptr inbounds [8000 x [2 x i32]], ptr %1, i64 0, i64 %3
  %36 = getelementptr inbounds [8000 x [2 x i32]], ptr %1, i64 0, i64 %8
  %37 = load i32, ptr %36, align 4, !tbaa !5
  %38 = load i32, ptr %35, align 4, !tbaa !5
  %39 = add nsw i32 %38, %37
  store i32 %39, ptr %35, align 4, !tbaa !5
  %40 = load i32, ptr %36, align 4, !tbaa !5
  %41 = sub nsw i32 %39, %40
  store i32 %41, ptr %36, align 4, !tbaa !5
  %42 = load i32, ptr %35, align 4, !tbaa !5
  %43 = sub nsw i32 %42, %41
  store i32 %43, ptr %35, align 4, !tbaa !5
  %44 = getelementptr inbounds [8000 x [2 x i32]], ptr %1, i64 0, i64 %3, i64 1
  %45 = getelementptr inbounds [8000 x [2 x i32]], ptr %1, i64 0, i64 %8, i64 1
  %46 = load i32, ptr %45, align 4, !tbaa !5
  %47 = load i32, ptr %44, align 4, !tbaa !5
  %48 = add nsw i32 %47, %46
  store i32 %48, ptr %44, align 4, !tbaa !5
  %49 = load i32, ptr %45, align 4, !tbaa !5
  %50 = sub nsw i32 %48, %49
  store i32 %50, ptr %45, align 4, !tbaa !5
  %51 = load i32, ptr %44, align 4, !tbaa !5
  %52 = sub nsw i32 %51, %50
  store i32 %52, ptr %44, align 4, !tbaa !5
  ret void
}

; Function Attrs: nounwind sspstrong uwtable
define dso_local void @init_particles(ptr nocapture noundef %0) local_unnamed_addr #3 {
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
define dso_local void @update_particles(ptr nocapture noundef %0) local_unnamed_addr #3 {
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
  %16 = load i32, ptr %15, align 4, !tbaa !5
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %113, label %18

18:                                               ; preds = %12
  %19 = getelementptr inbounds [8000 x [2 x i32]], ptr %0, i64 0, i64 %14
  %20 = load i32, ptr %19, align 4, !tbaa !5
  %21 = sub i32 4194304, %20
  %22 = getelementptr inbounds [8000 x [2 x i32]], ptr %0, i64 0, i64 %14, i64 1
  %23 = load i32, ptr %22, align 4, !tbaa !5
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
  store i32 0, ptr %15, align 4, !tbaa !5
  %36 = load i32, ptr %2, align 4, !tbaa !12
  %37 = add nsw i32 %36, -1
  store i32 %37, ptr %2, align 4, !tbaa !12
  %38 = sext i32 %37 to i64
  %39 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 2, i64 %38
  %40 = load i32, ptr %39, align 4, !tbaa !5
  %41 = load i32, ptr %15, align 4, !tbaa !5
  %42 = add nsw i32 %41, %40
  store i32 %42, ptr %15, align 4, !tbaa !5
  %43 = load i32, ptr %39, align 4, !tbaa !5
  %44 = sub nsw i32 %42, %43
  store i32 %44, ptr %39, align 4, !tbaa !5
  %45 = load i32, ptr %15, align 4, !tbaa !5
  %46 = sub nsw i32 %45, %44
  store i32 %46, ptr %15, align 4, !tbaa !5
  %47 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %14
  %48 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %38
  %49 = load i32, ptr %48, align 4, !tbaa !5
  %50 = load i32, ptr %47, align 4, !tbaa !5
  %51 = add nsw i32 %50, %49
  store i32 %51, ptr %47, align 4, !tbaa !5
  %52 = load i32, ptr %48, align 4, !tbaa !5
  %53 = sub nsw i32 %51, %52
  store i32 %53, ptr %48, align 4, !tbaa !5
  %54 = load i32, ptr %47, align 4, !tbaa !5
  %55 = sub nsw i32 %54, %53
  store i32 %55, ptr %47, align 4, !tbaa !5
  %56 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %14, i64 1
  %57 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %38, i64 1
  %58 = load i32, ptr %57, align 4, !tbaa !5
  %59 = load i32, ptr %56, align 4, !tbaa !5
  %60 = add nsw i32 %59, %58
  store i32 %60, ptr %56, align 4, !tbaa !5
  %61 = load i32, ptr %57, align 4, !tbaa !5
  %62 = sub nsw i32 %60, %61
  store i32 %62, ptr %57, align 4, !tbaa !5
  %63 = load i32, ptr %56, align 4, !tbaa !5
  %64 = sub nsw i32 %63, %62
  store i32 %64, ptr %56, align 4, !tbaa !5
  %65 = getelementptr inbounds [8000 x [2 x i32]], ptr %0, i64 0, i64 %38
  %66 = load i32, ptr %65, align 4, !tbaa !5
  %67 = load i32, ptr %19, align 4, !tbaa !5
  %68 = add nsw i32 %67, %66
  store i32 %68, ptr %19, align 4, !tbaa !5
  %69 = load i32, ptr %65, align 4, !tbaa !5
  %70 = sub nsw i32 %68, %69
  store i32 %70, ptr %65, align 4, !tbaa !5
  %71 = load i32, ptr %19, align 4, !tbaa !5
  %72 = sub nsw i32 %71, %70
  store i32 %72, ptr %19, align 4, !tbaa !5
  %73 = getelementptr inbounds [8000 x [2 x i32]], ptr %0, i64 0, i64 %38, i64 1
  %74 = load i32, ptr %73, align 4, !tbaa !5
  %75 = load i32, ptr %22, align 4, !tbaa !5
  %76 = add nsw i32 %75, %74
  store i32 %76, ptr %22, align 4, !tbaa !5
  %77 = load i32, ptr %73, align 4, !tbaa !5
  %78 = sub nsw i32 %76, %77
  store i32 %78, ptr %73, align 4, !tbaa !5
  %79 = load i32, ptr %22, align 4, !tbaa !5
  %80 = sub nsw i32 %79, %78
  store i32 %80, ptr %22, align 4, !tbaa !5
  %81 = add nsw i32 %13, -1
  br label %113

82:                                               ; preds = %18
  %83 = zext nneg i32 %33 to i64
  %84 = udiv i64 1342177280000, %83
  %85 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %14
  %86 = load i32, ptr %85, align 4, !tbaa !5
  %87 = shl nsw i64 %25, 18
  %88 = mul i64 %87, %84
  %89 = ashr i64 %88, 32
  %90 = mul nsw i64 %89, 546
  %91 = lshr i64 %90, 14
  %92 = trunc i64 %91 to i32
  %93 = add nsw i32 %86, %92
  %94 = tail call i32 @llvm.smax.i32(i32 %93, i32 -1638400)
  %95 = tail call i32 @llvm.smin.i32(i32 %94, i32 1638400)
  store i32 %95, ptr %85, align 4, !tbaa !5
  %96 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %14, i64 1
  %97 = load i32, ptr %96, align 4, !tbaa !5
  %98 = shl nsw i64 %29, 18
  %99 = mul i64 %98, %84
  %100 = ashr i64 %99, 32
  %101 = mul nsw i64 %100, 546
  %102 = lshr i64 %101, 14
  %103 = trunc i64 %102 to i32
  %104 = add nsw i32 %97, %103
  %105 = tail call i32 @llvm.smax.i32(i32 %104, i32 -1638400)
  %106 = tail call i32 @llvm.smin.i32(i32 %105, i32 1638400)
  store i32 %106, ptr %96, align 4, !tbaa !5
  %107 = mul nsw i32 %95, 546
  %108 = ashr i32 %107, 14
  %109 = add nsw i32 %108, %20
  store i32 %109, ptr %19, align 4, !tbaa !5
  %110 = mul nsw i32 %106, 546
  %111 = ashr i32 %110, 14
  %112 = add nsw i32 %111, %23
  store i32 %112, ptr %22, align 4, !tbaa !5
  br label %113

113:                                              ; preds = %35, %82, %12
  %114 = phi i32 [ %13, %12 ], [ %81, %35 ], [ %13, %82 ]
  %115 = add nsw i32 %114, 1
  %116 = icmp slt i32 %114, 7999
  br i1 %116, label %12, label %11, !llvm.loop !16
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(argmem: read) uwtable
define dso_local i32 @get_velocity_sq(i32 noundef %0, ptr nocapture noundef readonly %1) local_unnamed_addr #6 {
  %3 = sext i32 %0 to i64
  %4 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %3
  %5 = load i32, ptr %4, align 4, !tbaa !5
  %6 = sext i32 %5 to i64
  %7 = mul nsw i64 %6, %6
  %8 = lshr i64 %7, 14
  %9 = trunc i64 %8 to i32
  %10 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %3, i64 1
  %11 = load i32, ptr %10, align 4, !tbaa !5
  %12 = sext i32 %11 to i64
  %13 = mul nsw i64 %12, %12
  %14 = lshr i64 %13, 14
  %15 = trunc i64 %14 to i32
  %16 = add nsw i32 %15, %9
  ret i32 %16
}

; Function Attrs: nounwind sspstrong uwtable
define dso_local void @display_particles(ptr nocapture noundef readonly %0) local_unnamed_addr #3 {
  tail call void @simClear(i32 noundef -16777216) #9
  br label %3

2:                                                ; preds = %76
  tail call void (...) @simFlush() #9
  ret void

3:                                                ; preds = %1, %76
  %4 = phi i64 [ 0, %1 ], [ %77, %76 ]
  %5 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 2, i64 %4
  %6 = load i32, ptr %5, align 4, !tbaa !5
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %76, label %8

8:                                                ; preds = %3
  %9 = getelementptr inbounds [8000 x [2 x i32]], ptr %0, i64 0, i64 %4
  %10 = load i32, ptr %9, align 4, !tbaa !5
  %11 = ashr i32 %10, 14
  %12 = getelementptr inbounds [8000 x [2 x i32]], ptr %0, i64 0, i64 %4, i64 1
  %13 = load i32, ptr %12, align 4, !tbaa !5
  %14 = ashr i32 %13, 14
  %15 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %4
  %16 = load i32, ptr %15, align 4, !tbaa !5
  %17 = sdiv i32 %16, -10
  %18 = add i32 %17, %10
  %19 = ashr i32 %18, 14
  %20 = getelementptr inbounds %struct.particles_t, ptr %0, i64 0, i32 1, i64 %4, i64 1
  %21 = load i32, ptr %20, align 4, !tbaa !5
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
  %36 = lshr i64 %35, 6
  %37 = trunc i64 %36 to i32
  %38 = and i32 %37, -256
  %39 = xor i32 %38, -1
  %40 = sub nsw i32 %19, %11
  %41 = tail call i32 @llvm.abs.i32(i32 %40, i1 true)
  %42 = sub nsw i32 %24, %14
  %43 = tail call i32 @llvm.abs.i32(i32 %42, i1 true)
  %44 = icmp slt i32 %11, %19
  %45 = select i1 %44, i32 1, i32 -1
  %46 = icmp slt i32 %14, %24
  %47 = select i1 %46, i32 1, i32 -1
  %48 = sub nsw i32 %41, %43
  %49 = sub nsw i32 0, %43
  br label %50

50:                                               ; preds = %64, %8
  %51 = phi i32 [ %14, %8 ], [ %73, %64 ]
  %52 = phi i32 [ %48, %8 ], [ %75, %64 ]
  %53 = phi i32 [ %11, %8 ], [ %70, %64 ]
  %54 = icmp ult i32 %53, 512
  %55 = icmp sgt i32 %51, -1
  %56 = select i1 %54, i1 %55, i1 false
  %57 = icmp slt i32 %51, 512
  %58 = select i1 %56, i1 %57, i1 false
  br i1 %58, label %59, label %60

59:                                               ; preds = %50
  tail call void @simPutPixel(i32 noundef %53, i32 noundef %51, i32 noundef %39) #9
  br label %60

60:                                               ; preds = %59, %50
  %61 = icmp eq i32 %53, %19
  %62 = icmp eq i32 %51, %24
  %63 = select i1 %61, i1 %62, i1 false
  br i1 %63, label %76, label %64

64:                                               ; preds = %60
  %65 = shl nsw i32 %52, 1
  %66 = icmp sgt i32 %65, %49
  %67 = select i1 %66, i32 %43, i32 0
  %68 = sub i32 %52, %67
  %69 = select i1 %66, i32 %45, i32 0
  %70 = add nsw i32 %69, %53
  %71 = icmp slt i32 %65, %41
  %72 = select i1 %71, i32 %47, i32 0
  %73 = add nsw i32 %72, %51
  %74 = select i1 %71, i32 %41, i32 0
  %75 = add nsw i32 %68, %74
  br label %50

76:                                               ; preds = %60, %3
  %77 = add nuw nsw i64 %4, 1
  %78 = icmp eq i64 %77, 8000
  br i1 %78, label %2, label %3, !llvm.loop !17
}

declare void @simClear(i32 noundef) local_unnamed_addr #5

declare void @simFlush(...) local_unnamed_addr #5

; Function Attrs: noreturn nounwind sspstrong uwtable
define dso_local void @app() local_unnamed_addr #7 {
  %1 = alloca %struct.particles_t, align 4
  call void @llvm.lifetime.start.p0(i64 160004, ptr nonnull %1) #9
  %2 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 3
  store i32 0, ptr %2, align 4, !tbaa !12
  br label %3

3:                                                ; preds = %3, %0
  %4 = phi i32 [ 0, %0 ], [ %5, %3 ]
  call void @init_particle(i32 noundef %4, ptr noundef nonnull %1)
  %5 = add nuw nsw i32 %4, 1
  %6 = icmp eq i32 %5, 8000
  br i1 %6, label %7, label %3, !llvm.loop !14

7:                                                ; preds = %3, %84
  call void @update_particles(ptr noundef nonnull %1)
  tail call void @simClear(i32 noundef -16777216) #9
  br label %8

8:                                                ; preds = %81, %7
  %9 = phi i64 [ 0, %7 ], [ %82, %81 ]
  %10 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 2, i64 %9
  %11 = load i32, ptr %10, align 4, !tbaa !5
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %81, label %13

13:                                               ; preds = %8
  %14 = getelementptr inbounds [8000 x [2 x i32]], ptr %1, i64 0, i64 %9
  %15 = load i32, ptr %14, align 4, !tbaa !5
  %16 = ashr i32 %15, 14
  %17 = getelementptr inbounds [8000 x [2 x i32]], ptr %1, i64 0, i64 %9, i64 1
  %18 = load i32, ptr %17, align 4, !tbaa !5
  %19 = ashr i32 %18, 14
  %20 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %9
  %21 = load i32, ptr %20, align 4, !tbaa !5
  %22 = sdiv i32 %21, -10
  %23 = add i32 %22, %15
  %24 = ashr i32 %23, 14
  %25 = getelementptr inbounds %struct.particles_t, ptr %1, i64 0, i32 1, i64 %9, i64 1
  %26 = load i32, ptr %25, align 4, !tbaa !5
  %27 = sdiv i32 %26, -10
  %28 = add i32 %27, %18
  %29 = ashr i32 %28, 14
  %30 = sext i32 %21 to i64
  %31 = mul nsw i64 %30, %30
  %32 = lshr i64 %31, 14
  %33 = sext i32 %26 to i64
  %34 = mul nsw i64 %33, %33
  %35 = lshr i64 %34, 14
  %36 = add nuw nsw i64 %35, %32
  %37 = shl i64 %36, 32
  %38 = ashr exact i64 %37, 18
  %39 = sdiv i64 %38, 327680000
  %40 = mul nsw i64 %39, 255
  %41 = lshr i64 %40, 6
  %42 = trunc i64 %41 to i32
  %43 = and i32 %42, -256
  %44 = xor i32 %43, -1
  %45 = sub nsw i32 %24, %16
  %46 = tail call i32 @llvm.abs.i32(i32 %45, i1 true)
  %47 = sub nsw i32 %29, %19
  %48 = tail call i32 @llvm.abs.i32(i32 %47, i1 true)
  %49 = icmp slt i32 %16, %24
  %50 = select i1 %49, i32 1, i32 -1
  %51 = icmp slt i32 %19, %29
  %52 = select i1 %51, i32 1, i32 -1
  %53 = sub nsw i32 %46, %48
  %54 = sub nsw i32 0, %48
  br label %55

55:                                               ; preds = %69, %13
  %56 = phi i32 [ %19, %13 ], [ %78, %69 ]
  %57 = phi i32 [ %53, %13 ], [ %80, %69 ]
  %58 = phi i32 [ %16, %13 ], [ %75, %69 ]
  %59 = icmp ult i32 %58, 512
  %60 = icmp sgt i32 %56, -1
  %61 = select i1 %59, i1 %60, i1 false
  %62 = icmp slt i32 %56, 512
  %63 = select i1 %61, i1 %62, i1 false
  br i1 %63, label %64, label %65

64:                                               ; preds = %55
  tail call void @simPutPixel(i32 noundef %58, i32 noundef %56, i32 noundef %44) #9
  br label %65

65:                                               ; preds = %64, %55
  %66 = icmp eq i32 %58, %24
  %67 = icmp eq i32 %56, %29
  %68 = select i1 %66, i1 %67, i1 false
  br i1 %68, label %81, label %69

69:                                               ; preds = %65
  %70 = shl nsw i32 %57, 1
  %71 = icmp sgt i32 %70, %54
  %72 = select i1 %71, i32 %48, i32 0
  %73 = sub i32 %57, %72
  %74 = select i1 %71, i32 %50, i32 0
  %75 = add nsw i32 %74, %58
  %76 = icmp slt i32 %70, %46
  %77 = select i1 %76, i32 %52, i32 0
  %78 = add nsw i32 %77, %56
  %79 = select i1 %76, i32 %46, i32 0
  %80 = add nsw i32 %73, %79
  br label %55

81:                                               ; preds = %65, %8
  %82 = add nuw nsw i64 %9, 1
  %83 = icmp eq i64 %82, 8000
  br i1 %83, label %84, label %8, !llvm.loop !17

84:                                               ; preds = %81
  tail call void (...) @simFlush() #9
  br label %7
}

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.smax.i32(i32, i32) #8

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.smin.i32(i32, i32) #8

attributes #0 = { mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(argmem: readwrite) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #3 = { nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { mustprogress nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #5 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { mustprogress nofree norecurse nosync nounwind sspstrong willreturn memory(argmem: read) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #7 = { noreturn nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #8 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #9 = { nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"clang version 18.1.8"}
!5 = !{!6, !6, i64 0}
!6 = !{!"int", !7, i64 0}
!7 = !{!"omnipotent char", !8, i64 0}
!8 = !{!"Simple C/C++ TBAA"}
!9 = distinct !{!9, !10}
!10 = !{!"llvm.loop.mustprogress"}
!11 = distinct !{!11, !10}
!12 = !{!13, !6, i64 160000}
!13 = !{!"particles_t", !7, i64 0, !7, i64 64000, !7, i64 128000, !6, i64 160000}
!14 = distinct !{!14, !10}
!15 = distinct !{!15, !10}
!16 = distinct !{!16, !10}
!17 = distinct !{!17, !10}
