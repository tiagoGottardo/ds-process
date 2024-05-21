gcc -c AVLtree.c -o AVLtree.o;
ar rcs avl_tree.a AVLtree.o;

gcc -c MaxHeap.c -o MaxHeap.o;
ar rcs max_heap.a MaxHeap.o;

rm app; 
gcc main.c -o app \
  -L/home/tiagopg/projects/ds-process/ -l:avl_tree.a \
  -L/home/tiagopg/projects/ds-process/ -l:max_heap.a;
./app;
