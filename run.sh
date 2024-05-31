gcc -c AVLtree.c -o AVLtree.o;
ar rcs avl_tree.a AVLtree.o;

gcc -c MaxHeap.c -o MaxHeap.o;
ar rcs max_heap.a MaxHeap.o;

gcc -c HashMap.c -o HashMap.o;
ar rcs hash_map.a HashMap.o;

gcc -c Parser.c -o Parser.o;
ar rcs parser.a Parser.o;

gcc -c Process.c -o Process.o;
ar rcs process.a Process.o;

rm app; 
gcc main.c -o app \
  -L/home/tiagopg/projects/ds-process -l:avl_tree.a \
  -L/home/tiagopg/projects/ds-process -l:max_heap.a \
  -L/home/tiagopg/projects/ds-process -l:parser.a \
  -L/home/tiagopg/projects/ds-process -l:process.a \
  -L/home/tiagopg/projects/ds-process -l:hash_map.a;
./app;
