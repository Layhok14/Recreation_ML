#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

typedef float sample[3];

typedef struct { float w1; float w2; float b; } Weight;

typedef struct{
    Weight and;
    Weight or;
    Weight nand;
}Xor;

sample or_train[]={
    {0,0,0},
    {1,0,1},
    {0,1,1},
    {1,1,1},
};

sample and_train[]={
    {0,0,0},
    {1,0,0},
    {0,1,0},
    {1,1,1},
};

sample nand_train[]={
    {0,0,1},
    {1,0,1},
    {0,1,1},
    {1,1,0},
};

sample xor_train[] = {
    {0,0,0},
    {1,0,1},
    {0,1,1},
    {1,1,0},
};

sample *train = xor_train; 
size_t train_count = 4;
float rand_float(){
    return (float) rand() / (float) RAND_MAX;
}
float sigmoid_function(float x){
    return (float) 1/(1+exp(-x));
} 

// formula for XOR: (A AND NOT B) OR (NOT A AND B)
// design of the NN: first Layer: AND and NAND. Second Layer -> OR.
float forward(Xor model, float x1, float x2){    
    float n_a = sigmoid_function(model.and.w1*x1+model.and.w2*x2+model.and.b);
    float n_b = sigmoid_function(model.nand.w1*x1+model.nand.w2*x2+model.nand.b); 
    return sigmoid_function(model.or.w1*n_a+model.or.w2*n_b+model.or.b); 
}
float cost (Xor model){ 
    float result=0.0;
    for(size_t i = 0 ; i < train_count;++i){
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = train[i][2];
        float predicted = forward(model,x1,x2);
        float difference = y- predicted;
        result += difference*difference; 
    }
    result/=train_count;
    return result;
} 
Xor learning(Xor difference, Xor model, float learning_rate){
    model.and.w1 -=learning_rate* difference.and.w1;
    model.and.w2 -=learning_rate* difference.and.w2;
    model.and.b -=learning_rate* difference.and.b;
    model.or.w1 -=learning_rate* difference.or.w1;
    model.or.w2 -=learning_rate* difference.or.w2;
    model.or.b -=learning_rate* difference.or.b;
    model.nand.w1 -=learning_rate* difference.nand.w1;
    model.nand.w2 -=learning_rate* difference.nand.w2;
    model.nand.b -=learning_rate* difference.nand.b;
    return model;
}
Xor finite_difference(float eps, Xor model){
    Xor temp;
    float c = cost(model);
    model.and.w1 += eps;
    temp.and.w1 = (cost(model) - c)/eps;
    model.and.w1 -= eps;
    
    model.and.w2 += eps;
    temp.and.w2 = (cost(model) - c)/eps;
    model.and.w2 -= eps;

    model.and.b += eps;
    temp.and.b = (cost(model) - c)/eps;
    model.and.b -= eps;

    model.or.w1 += eps;
    temp.or.w1 = (cost(model) - c)/eps;
    model.or.w1 -= eps;
    
    model.or.w2 += eps;
    temp.or.w2 = (cost(model) - c)/eps;
    model.or.w2 -= eps;

    model.or.b += eps;
    temp.or.b = (cost(model) - c)/eps;
    model.or.b -= eps;

    model.nand.w1 += eps;
    temp.nand.w1 = (cost(model) - c)/eps;
    model.nand.w1 -= eps;
    
    model.nand.w2 += eps;
    temp.nand.w2 = (cost(model) - c)/eps;
    model.nand.w2 -= eps;

    model.nand.b += eps;
    temp.nand.b = (cost(model) - c)/eps;
    model.nand.b -= eps;
    return temp;

}
void print_xor(Xor model){
    printf("and.w1=%f\n",model.and.w1);
    printf("and.w2=%f\n",model.and.w2);
    printf("and.b=%f\n",model.and.b); 
    printf("or.w1=%f\n",model.or.w1);
    printf("or.w2=%f\n",model.or.w2);
    printf("or.b=%f\n",model.or.b); 

   printf("nand.w1=%f\n",model.nand.w1);
    printf("nand.w2=%f\n",model.nand.w2);
    printf("nand.b=%f\n",model.nand.b); 
}
int main(){ 
    srand(67); 
    Xor model = {
        {rand_float(), rand_float(), rand_float()},
        {rand_float(), rand_float(), rand_float()},
        {rand_float(), rand_float(), rand_float()},
    };
    float eps = 1e-1;
    float learning_rate = 1e-3;
    print_xor(model);
    printf("----------------------------------------------\n");
    for(size_t i = 0; i < 20; ++i){
        Xor difference  = finite_difference(eps, model);
        Xor result =  learning(difference, model, learning_rate);
        model = result;
        float c = cost(model);
        // print_xor(model);
        // printf("``````````````````````````````````````````````````\n");
        printf("cost: %f\n", c);
    }
    printf("----------------------------------------------\n");
    print_xor(model);
}
