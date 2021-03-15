.data
print_sum:
.string "Сумма элементов массива > M: %d\n"
print_elem:
.string "Кол-во элементов < M: %d\n"
arr:
.long 2, 3, 10, 5, 3
arr_end:
counter:
.long 5
M:
.long 3
.text
.global main
.type main, @function
main:
        movl $arr, %ebx /* в %ebx заносим элементы массива; */
        movl counter, %ecx /* в %ecx счетчик чисел; */
        movl M, %edx /* в %edx будем хранить число M; */
        movl $0, %eax  /* в %eax будем хранить результат; */
        movl $0, %esi /* в %esi будем хранить M > Array; */
        
loop_start:
        cmpl %edx,(%ebx) /* сравниваем наше число M с элементами массива; */
        jl less_count /* переход, если первый операнд меньше второго; */
        jg more_count /* переход, если первый операнд больше второго; */
        je equally_count /* переход, если операнды равны; */
        
less_count:
        addl  $4, %ebx /* используем системный вызов для записи в регистр %ebx; */
        addl  $1, %esi
        jmp loop_end
        
more_count:
        addl (%ebx),%eax /* используем указатель на наш регистр, где хранится результат; */
        addl  $4, %ebx /* используем системный вызов для записи в регистр %ebx; */
        jmp loop_end /* безусловный переход; */
        
equally_count:
        addl  $4, %ebx /* используем системный вызов для записи в регистр %ebx; */
        jmp loop_end /* безусловный переход; */
        
loop_end:
        loop  loop_start /* уменьшаем значение %ecx и если не равно 0 переход; */

print_info: /* здесь работаем со стеком и выводим сумму элементов массива > M и кол-во элементов < M; */
    pushl %eax
    pushl $print_sum
    call  printf
    addl  $8, %esp
    movl  $0, %eax
            
    pushl %esi
    pushl $print_elem
    call  printf
    addl  $8, %esp
    movl  $0, %esi
ret
