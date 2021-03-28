#include <iostream>
#include <ctime>

using namespace std;

int main()
{
   srand(time(0));
   long long int  n = rand() % 8 + 3;
   long long int arr[n];
   int  middle = n/2;
   
   cout << "N: \n" << n << endl;
   
   cout << "Random Array: \n";
   for(int i = 0; i<n; i++)
   {
       arr[i] = rand () % 9+1;
       cout << arr[i] << " ";
   }
   cout << "\nNew array C++: \n";
       for (int i = 0; i < middle; i++)
           arr[i] = arr[n-i-1] = i+1;
           
       for (int i = 0; i < n; i++)
           cout << arr[i] << " ";
  
   long long *ptr_array = &arr[0];
   long long *ctr_array = &arr[n/2];
   long long *end_array = &arr[n-1];
   
 asm (
       "movl %[ptr_array], %%ebx\n\t" // Поместили указатель на начало матрицы в ebx
       "movl %[ptr_array], %%edx\n\t" // Поместили указатель на начало матрицы в edx
       "movl $8, %%eax\n\t" // Поместили 8 в eax
       "mull %[n]\n\t" // Умножили eax на n (получили сдвиг для перехода)
       "addl $8, %%eax\n\t" // Прибавили к edx 8 (сдвинули указатель вправо)
       "addl %%eax, %%edx\n\t" // Прибавили к edx содержимое eax (сдвинули указатель)
       "sub $16, %%edx\n\t" // Вычитаем из edx 16 (сдвинули указатели)
       "addl %%eax, %[ptr_array]\n\t" // Прибавили к ptr_array содержимое eax (получили указатель на первый элемент с конца)
       "push %%ebx\n\t" // Поместили в стек ebx (адрес следующего элемента)

       "loop_start:\n\t"
           "addl $8, %%ebx\n\t" // Увеличили адрес в ebx на 8 (переместились на один элементов вправо)
           "cmp %%ebx, %[ptr_array]\n\t" // Проверили, что не достигнута середина в матрице
           "je start_center\n\t" // Если достигнута - переход на start_center
           "cmp %%ebx, %%edx\n\t" // Проверили, что достигнута середина в матрице
           "je after_center\n\t" // Если достигнута - переход на after_center
           "push %%edx\n\t" // Вернули edx в стек
           "cmp %%ebx, %[end_array]\n\t" // Проверили, что достиг конец
           "je end\n\t" // Перешли на вывод результатов
       "jmp loop_start\n\t"

       "start_center:\n\t" // Метка, которая начинает работу с первой частью разбитого масива
           "push $1\n\t"
           "pop (%%ebx)\n\t"
           "cmp %%edx, %[ctr_array]\n\t"
           "je prt_after_center\n\t"
           "addl %%eax, %[ptr_array]\n\t"
           "cmp %%ebx, %[end_array]\n\t"
           "je end\n\t"
       "jmp loop_start\n\t"

       "after_center:\n\t" // Метка, которая начинает работу со второй частью массива
           "push $1\n\t"
           "pop (%%ebx)\n\t"
           "addl %%eax, %%edx\n\t"
           "sub $16, %%edx\n\t"
           "cmp %%ebx, %[end_array]\n\t"
           "je end\n\t"
       "jmp loop_start\n\t"

       "prt_after_center:\n\t" // Метка, которая делит массив на 2
           "addl %%eax, %[ptr_array]\n\t"
           "addl %%eax, %%edx\n\t"
           "sub $16, %%edx\n\t"
       "jmp loop_start\n\t"
       "end:\n\t"
      
       :
       :[ptr_array]"m"(ptr_array), [end_array]"m"(end_array), [ctr_array]"m"(ctr_array), [n]"m"(n)
       :"%eax", "%ebx", "%edx", "%esi"
   );

   cout << "\nNew array Asm: \n";
   for (int i = 0; i < n; i++){
           cout << arr[i] << " ";
       }
       cout << endl;
   return 0;
}
