
#include <testesAluno.h>

/// this is not a real test. It does not run any SSP Solver
/// it prints outs instances of SSP problems using any instance generator
SSP_Exp alunoViewInstance() {
return SSP_Exp(
        // {"DD","A2","PD","EX"}, // DD-gabarito ; A2-may be BB or MM ; PD-ProgDinamic EX-extra
        {"DD"}, // ignored for instance viewer (but must not be empty)
        {10, 15, 20},//{10,15}, // choose sizes. if empty, test does nothing
        // possible instance generators: choose as many as you wish to see
        // if size for TODD > 25 we have long overflow
        {"TODD","P3","P6","P9","RAND", "EVOD","AVIS"} 
        ,3 );  // ignored for instance viewer
}

/// you choose the algorithms, the sizes, the instance generators and 
/// how many repetitions each combination will be tested.
/// the SSP Solver algorithms will be called and the solution will be checked
/// for correctness (the numbers will be summed up and the value checked)
/// if sizes list is empty, this does nothing.
SSP_Exp alunoTestSSP1() {
return SSP_Exp(
        // {"DD","A2","PD","EX"}, // DD-gabarito ; A2-may be BB or MM ; PD-ProgDinamic EX-extra
        {"DD"}, // choose algoritms
        {},//{10,15}, // choose sizes. if empty, test does nothing
        // possible instance generators: choose as many as you wish to test
        {"TODD","P3","P6","P9","RAND", "EVOD","AVIS"}
        // note: TOOD and AVIS are not random, do not need to repeat the test
        ,3 );  // how many times to repeat the test
}

SSP_Exp alunoTestSSP2() {
return SSP_Exp(
        // {"DD","A2","PD","EX"}, // DD-gabarito ; A2-may be BB or MM ; PD-ProgDinamic EX-extra
        {"DD"}, // choose algoritms
        {},//{10,15}, // choose sizes. if empty, test does nothing
        // possible instance generators: choose as many as you wish to test
        {"TODD","P3","P6","P9","RAND", "EVOD","AVIS"}
        // note: TOOD and AVIS are not random, do not need to repeat the test
        ,3 );  // how many times to repeat the test
}

SSP_Exp alunoTestSSP3() {
return SSP_Exp(
        // {"DD","A2","PD","EX"}, // DD-gabarito ; A2-may be BB or MM ; PD-ProgDinamic EX-extra
        {"DD"}, // choose algoritms
        {},//{10,15}, // choose sizes. if empty, test does nothing
        // possible instance generators: choose as many as you wish to test
        {"TODD","P3","P6","P9","RAND", "EVOD","AVIS"}
        // note: TOOD and AVIS are not random, do not need to repeat the test
        ,3 );  // how many times to repeat the test
}

SSP_Exp alunoTestTimed1() {
return SSP_Exp(
        // {"DD","A2","PD","EX"}, // DD-gabarito ; A2-may be BB or MM ; PD-ProgDinamic EX-extra
        {"DD"}, // choose algoritms
        {},//{10,15}, // choose sizes. if empty, test does nothing
        // possible instance generators: choose as many as you wish to test
        {"TODD","P3","P6","P9","RAND", "EVOD","AVIS"}
        // note: TOOD and AVIS are not random, do not need to repeat the test
        ,3 );  // how many times to repeat the test
}


SSP_Exp alunoTestTimed2() {
return SSP_Exp(
        // {"DD","A2","PD","EX"}, // DD-gabarito ; A2-may be BB or MM ; PD-ProgDinamic EX-extra
        {"DD"}, // choose algoritms
        {},//{10,15}, // choose sizes. if empty, test does nothing
        // possible instance generators: choose as many as you wish to test
        {"TODD","P3","P6","P9","RAND", "EVOD","AVIS"}
        // note: TOOD and AVIS are not random, do not need to repeat the test
        ,3 );  // how many times to repeat the test
}
