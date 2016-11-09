import qbs

Module {
    Depends { name: "cpp" }
    Depends {
        name: "helper6"
        required: false
    }

    Group {
        name: "Helper5 Sources"
        prefix: path + "/"
        files: ["helper5.c"]
        cpp.defines: ["COMPILE_FIX"]
    }
}