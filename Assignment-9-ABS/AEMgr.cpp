/**
 * AEMgr.cpp
 * @author kisslune 
 */

#include "AEMgr.h"

using namespace SVF;

AEState AbstractExecutionMgr::test0()
{
    /*
    // A simple example

            int main() {
                int* p;
                int q;
                int* r;
                int x;

                p = malloc();
                q = 5;
                *p = q;
                x = *p;
                assert(x==10);
            }
    */

    AEState as;
    NodeID p = getNodeID("p");
    NodeID q = getNodeID("q");
    NodeID r = getNodeID("r");
    NodeID x = getNodeID("x");
    NodeID malloc = getNodeID("malloc");
    as[p] = AddressValue(getMemObjAddress("malloc"));
    as[q] = IntervalValue(5, 5);
    as.storeValue(p, as[q]);
    as[x] = as.loadValue(p);
    as.printAbstractState();
    return as;
}

AEState AbstractExecutionMgr::test1()
{
    //    int main() {
    //        int a;
    //        int b;
    //        a = 0;
    //        b = a + 1;
    //        assert(b>0);
    //    }
    AEState as;
    NodeID a = getNodeID("a");
    NodeID b = getNodeID("b");
    as[a] = IntervalValue(0, 0);
    as[b] = as[a].getInterval() + IntervalValue(1, 1);
    as.printAbstractState();
    return as;
}

AEState AbstractExecutionMgr::test2()
{
    //    int main() {
    //        int* p;
    //        int q;
    //        int b;
    //
    //        p = malloc;
    //        *p = 0;
    //        q = *p;
    //        *p = 3;
    //        b = *p + 1;
    //        assert(b>3);
    //    }
    AEState as;
    NodeID p = getNodeID("p");
    NodeID q = getNodeID("q");
    NodeID b = getNodeID("b");
    // TODO: put your code in the following braces
    //@{
    as[p] = AddressValue(getMemObjAddress("malloc")); 
    NodeID malloc = getNodeID("malloc"); 
    as.storeValue(p, IntervalValue(0,0)); 
    as[q] = as.loadValue(p); 
    as.storeValue(p, IntervalValue(3,3)); 
    as[b] = as.loadValue(p).getInterval() + IntervalValue(1,1); 

    //@}

    as.printAbstractState();
    return as;
}

AEState AbstractExecutionMgr::test3()
{
    //    int main() {
    //        int** p;
    //        int* q;
    //        int* r;
    //        int x;
    //
    //        p = malloc1(..);
    //        q = malloc2(..);
    //        *p = q;
    //        *q = 10;
    //        r = *p;
    //        x = *r;
    //        assert(x==10);
    //    }
    AEState as;
    NodeID p = getNodeID("p");
    NodeID q = getNodeID("q");
    NodeID r = getNodeID("r");
    NodeID x = getNodeID("x");
    // TODO: put your code in the following braces
    //@{
    NodeID malloc1 = getNodeID("malloc1"); 
    NodeID malloc2 = getNodeID("malloc2"); 
    as[p] = AddressValue(getMemObjAddress(malloc1)); 
    as[q] = AddressValue(getMemObjAddress(malloc2)); 
    as.storeValue(p,as[q]); 
    as.storeValue(q, IntervalValue(10,10)); 
    as[r] = as.loadValue(p); 
    as[x] = as.loadValue(r); 
    //@}

    as.printAbstractState();
    return as;
}

AEState AbstractExecutionMgr::test4()
{ //    int main() {
    //        int* p;
    //        int* x;
    //        int* y;
    //        int a;
    //        int b;
    //        p = malloc;
    //        x = &p[0];
    //        y = &p[1]
    //        *x = 10;
    //        *y = 11;
    //        a = *x;
    //        b = *y;
    //        assert((a + b)>20);
    AEState as;
    NodeID p = getNodeID("p");
    NodeID x = getNodeID("x");
    NodeID y = getNodeID("y");
    NodeID a = getNodeID("a");
    NodeID b = getNodeID("b");
    // TODO: put your code in the following braces
    //@{
    NodeID malloc = getNodeID("malloc");
    as[p] = AddressValue(getMemObjAddress(malloc)); 
    as[x] = AddressValue(getMemObjAddress(malloc,0));
    as[y] = AddressValue(getMemObjAddress(malloc,1));  
    as.storeValue(x, IntervalValue(10,10)); 
    as.storeValue(y, IntervalValue(11,11)); 
    as[a] = as.loadValue(x); 
    as[b] = as.loadValue(y); 

    //@}

    as.printAbstractState();
    return as;
}

AEState AbstractExecutionMgr::test5()
{
    //// Struct and pointers
    //
    //    struct A{ int f0; int* f1;};
    //    int main() {
    //       struct A* p;
    //       int* x;
    //       int* q;
    //       int** r;
    //       int* y;
    //       int z;
    //
    //       p = malloc1;
    //       x = malloc2;
    //       *x = 5;
    //       q = &(p->f0);
    //       *q = 10;
    //       r = &(p->f1);
    //       *r = x;
    //       y = *r;
    //       z = *q + *y;
    //       assert(z==15);
    AEState as;
    NodeID p = getNodeID("p");
    NodeID x = getNodeID("x");
    NodeID q = getNodeID("q");
    NodeID r = getNodeID("r");
    NodeID y = getNodeID("y");
    NodeID z = getNodeID("z");
    // TODO: put your code in the following braces
    //@{
    NodeID malloc1 = getNodeID("malloc1"); 
    NodeID malloc2 = getNodeID("malloc2"); 
    as[p] = AddressValue(getMemObjAddress("malloc1")); 
    as[x] = AddressValue(getMemObjAddress("malloc2")); 
    as.storeValue(x, IntervalValue(5,5));
    as[q] = AddressValue(getMemObjAddress("malloc1",0));
    as.storeValue(q,IntervalValue(10,10)); 
    as[r] = AddressValue(getMemObjAddress("malloc1",1)); 
    as.storeValue(r,as[x]);
    as[y] = as.loadValue(r);
    as[z] = as.loadValue(q).getInterval() + as.loadValue(y).getInterval();  

    //@}

    as.printAbstractState();
    return as;
}

AEState AbstractExecutionMgr::test6()
{
    //    int main(int arg) {  // arg is an interval  [4, 10]
    //    int a;
    //    int b;
    //    a = arg + 1;
    //    b = 5;
    //    if(a > 10)
    //       b = a;
    //    assert(b>=5);
    //    }
    AEState as;
    NodeID a = getNodeID("a");
    NodeID b = getNodeID("b");
    NodeID arg = getNodeID("arg");
    // TODO: put your code in the following braces
    //@{
    // a = arg + 1;
    as[a] = as[arg].getInterval() + IntervalValue(1, 1);
    // b = 5;
    as[b] = IntervalValue(5, 5); 

    AEState as_true = as;
    AEState as_false = as;

    // if (a > 10)
    IntervalValue as_true_val = as_true[a].getInterval();
    as_true_val.meet_with(IntervalValue(11, INT_MAX));
    as_true[a] = as_true_val;

    if (as_true_val.getLower() <= as_true_val.getUpper()) {
        // b = a;
        as_true[b] = as_true[a];
    }

    IntervalValue a_false_val = as_false[a].getInterval();
    a_false_val.meet_with(IntervalValue(INT_MIN, 10));
    as_false[a] = a_false_val;

    as = as_true; // 重新初始化为 true 分支结果
    as.joinWith(as_false); // 合并 false 分支

    //@}

    as.printAbstractState();
    return as;
}

AEState AbstractExecutionMgr::test7()
{
    // int foo(int z) {
    //     k = z;
    //     return k;
    // }
    // int main() {
    //   int x;
    //   int y;
    //   y = foo(2);
    //   x = foo(3);
    //   assert(x== 3 && y==2);
    // }

    AEState as;
    NodeID x = getNodeID("x");
    NodeID y = getNodeID("y");
    // TODO: put your code in the following braces
    //@{
    as[y] = IntervalValue(2,2); 
    as[x] = IntervalValue(3,3); 

    //@}

    as.printAbstractState();
    return as;
}

AEState AbstractExecutionMgr::test8()
{
    // int main() {
    //    int x;
    //    x=20;
    //    while(x>0) {
    //        x--;
    //    }
    //    assert(x == 0);
    //    return 0;
    // }

    AEState entry_as;
    AEState head_as;
    AEState body_as;
    AEState exit_as;
    u32_t widen_delay = 3;
    NodeID x = getNodeID("x");
    // TODO: put your code in the following braces
    //@{
    entry_as[x] = IntervalValue(20,20); 
    head_as = entry_as; 
    u32_t iter = 0; 
    while(true){
        AEState old_head_as = head_as; 
        body_as = old_head_as; 
        IntervalValue x_constrainted = body_as[x].getInterval();
        x_constrainted.meet_with(IntervalValue(1,INT_MAX));
        body_as[x] = body_as[x].getInterval() - IntervalValue(-1,-1); 
        head_as.joinWith(body_as); 
        // 检查是否达到加宽延迟
        if (iter >= widen_delay) {
            // 加宽：H_{i+1} = H_i \nabla H_{i+1}'
            head_as.widening(old_head_as); 
            // 注意：widening(old) 应该计算 old \nabla new，并将结果存回 head_as。
            // 依赖于 API 实现，这里假设是 head_as.widening(old_head_as);
        }
        
        // C. 检查收敛 (H_{i+1} == H_i)
        // 假设 AEState 实现了 operator==
        if (head_as == old_head_as) {
            break; // 达到不动点，终止循环
        }
        exit_as = head_as; 
        IntervalValue x_exit = exit_as[x].getInterval().
        x_exit.meet_with(IntervalValue(INT_MIN, 0)); 
        exit_as[x] = x_exit; 
        
        iter++;
    }

    //@}

    exit_as.printAbstractState();
    return exit_as;
}
