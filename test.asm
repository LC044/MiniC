declare i32 @a
declare i32 @b[2][5][3]
declare i32 @ght
define i32 @add(i32 %t0, i32 %t1) {
    declare i32 %l2 ; variable: a
    declare i32 %l3 ; variable: b
    declare i32 %l4 ; variable: return
    declare i32 %l5 ; variable: v
    declare i32 %t6
    declare i32 %t7
    declare i32 %t8
    declare i32 %t9
    declare i32 %t10
    declare i32 %t11
    entry
    %l2 = %t0
    %l3 = %t1
    %t6 = %l2
    %t7 = %l3
    %t8 = add %t6, %t7
    %l5 = %t8
    %t9 = %l5
    %t10 = add %t9, 1
    %l4 = %t10
    %t11 = %l4
    exit %t11
}
