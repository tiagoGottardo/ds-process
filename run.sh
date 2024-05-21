gcc -c AVLtree.c -o AVLtree.o;
ar rcs avl_tree.a AVLtree.o;

rm app; 
gcc main.c -o app \
  -L/home/tiagopg/projects/ds-process/ -l:avl_tree.a;
./app;
