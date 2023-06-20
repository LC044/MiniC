declare i32 @a
define i32 @main() {
    declare i32 %l0 ; variable: return
    declare i32 %l1 ; variable: a
    declare i32 %l2 ; variable: a
    declare i32 %l3 ; variable: a
    declare i32 %t4
    declare i32 %t5
    entry
    @a = 3
    %l1 = 4
    %l1 = 5
    %l2 = 6
    %l3 = 7
    %t4 = %l1
    %l0 = %t4
    %t5 = %l0
    exit %t5
}
