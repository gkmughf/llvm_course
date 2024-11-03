clang++ gen_IR_gen_pass.cpp -fPIC -shared -I$(llvm-config --includedir) -o Pass.so
clang -fpass-plugin=./Pass.so -O1 ../SDL/app.c -c
clang++ $(llvm-config --cppflags --ldflags --libs) ../SDL/sim.c generated_ir_gen.cpp -lSDL2
./a.out > gen.ll
