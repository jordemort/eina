//Compile with:
//gcc -g eina_inarray_01.c -o eina_inarray_01 `pkg-config --cflags --libs eina`

#include <Eina.h>

int
cmp(const void *a, const void *b)
{
   return *(int*)a > *(int*)b;
}

int main(int argc, char **argv)
{
   Eina_Inarray *iarr;
   char ch, *ch2;
   int a, *b;

   eina_init();
   iarr = eina_inarray_new(sizeof(char), 0);

   ch = 'a';
   eina_inarray_append(iarr, &ch);
   ch = 'b';
   eina_inarray_append(iarr, &ch);
   ch = 'c';
   eina_inarray_append(iarr, &ch);
   ch = 'd';
   eina_inarray_append(iarr, &ch);

   printf("Inline array of chars:\n");
   EINA_INARRAY_FOREACH(iarr, ch2)
     printf("char: %c(pointer: %p)\n", *ch2, ch2);

   eina_inarray_flush(iarr);
   eina_inarray_setup(iarr, sizeof(int), 4);

   a = 97;
   eina_inarray_append(iarr, &a);
   a = 98;
   eina_inarray_append(iarr, &a);
   a = 100;
   eina_inarray_append(iarr, &a);
   a = 99;
   eina_inarray_insert_sorted(iarr, &a, cmp);

   printf("Inline array of integers with %d elements:\n", eina_inarray_count(iarr));
   EINA_INARRAY_FOREACH(iarr, b)
     printf("int: %d(pointer: %p)\n", *b, b);

   eina_inarray_free(iarr);
   eina_shutdown();
}