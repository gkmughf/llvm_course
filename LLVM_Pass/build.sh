clang++ Pass.cpp -fPIC -shared -I$(llvm-config --includedir) -o libPass.so
clang -fpass-plugin=./libPass.so -O2 ../SDL/start.c ../SDL/sim.c ../SDL/app.c log.c -lSDL2 -o BH.out
