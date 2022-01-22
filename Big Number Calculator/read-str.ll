; ModuleID = 'seashell-compiler-output'
source_filename = "seashell-compiler-output"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [4 x i8] c" %c\00", align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"%c\00", align 1

; Function Attrs: noinline nounwind optnone
define i8* @read_str() #0 {
entry:
  %retval = alloca i8*, align 8
  %c = alloca i8, align 1
  %maxlen = alloca i32, align 4
  %len = alloca i32, align 4
  %str = alloca i8*, align 8
  store i8 0, i8* %c, align 1
  %call = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i8* %c)
  %cmp = icmp ne i32 %call, 1
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8
  br label %return

if.end:                                           ; preds = %entry
  store i32 1, i32* %maxlen, align 4
  store i32 1, i32* %len, align 4
  %0 = load i32, i32* %maxlen, align 4
  %conv = sext i32 %0 to i64
  %mul = mul i64 %conv, 1
  %call1 = call noalias i8* @malloc(i64 %mul) #3
  store i8* %call1, i8** %str, align 8
  %1 = load i8, i8* %c, align 1
  %2 = load i8*, i8** %str, align 8
  %arrayidx = getelementptr inbounds i8, i8* %2, i64 0
  store i8 %1, i8* %arrayidx, align 1
  br label %while.body

while.body:                                       ; preds = %if.end, %if.end22
  %call2 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i64 0, i64 0), i8* %c)
  %cmp3 = icmp ne i32 %call2, 1
  br i1 %cmp3, label %if.then5, label %if.end6

if.then5:                                         ; preds = %while.body
  br label %while.end

if.end6:                                          ; preds = %while.body
  %3 = load i8, i8* %c, align 1
  %conv7 = sext i8 %3 to i32
  %cmp8 = icmp eq i32 %conv7, 32
  br i1 %cmp8, label %if.then13, label %lor.lhs.false

lor.lhs.false:                                    ; preds = %if.end6
  %4 = load i8, i8* %c, align 1
  %conv10 = sext i8 %4 to i32
  %cmp11 = icmp eq i32 %conv10, 10
  br i1 %cmp11, label %if.then13, label %if.end14

if.then13:                                        ; preds = %lor.lhs.false, %if.end6
  br label %while.end

if.end14:                                         ; preds = %lor.lhs.false
  %5 = load i32, i32* %len, align 4
  %6 = load i32, i32* %maxlen, align 4
  %cmp15 = icmp eq i32 %5, %6
  br i1 %cmp15, label %if.then17, label %if.end22

if.then17:                                        ; preds = %if.end14
  %7 = load i32, i32* %maxlen, align 4
  %mul18 = mul nsw i32 %7, 2
  store i32 %mul18, i32* %maxlen, align 4
  %8 = load i8*, i8** %str, align 8
  %9 = load i32, i32* %maxlen, align 4
  %conv19 = sext i32 %9 to i64
  %mul20 = mul i64 %conv19, 1
  %call21 = call i8* @realloc(i8* %8, i64 %mul20) #3
  store i8* %call21, i8** %str, align 8
  br label %if.end22

if.end22:                                         ; preds = %if.then17, %if.end14
  %10 = load i32, i32* %len, align 4
  %inc = add nsw i32 %10, 1
  store i32 %inc, i32* %len, align 4
  %11 = load i8, i8* %c, align 1
  %12 = load i8*, i8** %str, align 8
  %13 = load i32, i32* %len, align 4
  %sub = sub nsw i32 %13, 1
  %idxprom = sext i32 %sub to i64
  %arrayidx23 = getelementptr inbounds i8, i8* %12, i64 %idxprom
  store i8 %11, i8* %arrayidx23, align 1
  br label %while.body

while.end:                                        ; preds = %if.then13, %if.then5
  %14 = load i8*, i8** %str, align 8
  %15 = load i32, i32* %len, align 4
  %add = add nsw i32 %15, 1
  %conv24 = sext i32 %add to i64
  %mul25 = mul i64 %conv24, 1
  %call26 = call i8* @realloc(i8* %14, i64 %mul25) #3
  store i8* %call26, i8** %str, align 8
  %16 = load i8*, i8** %str, align 8
  %17 = load i32, i32* %len, align 4
  %idxprom27 = sext i32 %17 to i64
  %arrayidx28 = getelementptr inbounds i8, i8* %16, i64 %idxprom27
  store i8 0, i8* %arrayidx28, align 1
  %18 = load i8*, i8** %str, align 8
  store i8* %18, i8** %retval, align 8
  br label %return

return:                                           ; preds = %while.end, %if.then
  %19 = load i8*, i8** %retval, align 8
  ret i8* %19
}

declare i32 @__isoc99_scanf(i8*, ...) #1

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

; Function Attrs: nounwind
declare i8* @realloc(i8*, i64) #2

attributes #0 = { noinline nounwind optnone "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+cx8,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+cx8,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-features"="+cx8,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.ident = !{!0}
!llvm.module.flags = !{!1}

!0 = !{!"clang version 9.0.1 (https://github.com/llvm/llvm-project.git c1a0a213378a458fbea1a5c77b315c7dce08fd05)"}
!1 = !{i32 1, !"wchar_size", i32 4}
