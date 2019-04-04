'use strict';

const mod = GE.Modules();
mod.require("Threading");
// mod.require("Resource");

const isolate = Threading.Isolate();

let fun = function(a, b) {
    const mod = GE.Modules();
    // mod.require("SDL");

    // const dir = Resource.Directory("res");
    print("having fun!");
}

let bun = function(a, b) {
    print("having much more fun!");
    isolate.QueueFunction(fun, a, b);

}

let my_A = 1;
let my_B = 2;
isolate.QueueFunction(fun, my_A, my_B);
isolate.QueueFunction(bun, my_A, my_B);

isolate.Process1();
// isolate.Process1();
isolate.QueueFunction(bun, my_A, my_B);
