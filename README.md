# Skibidi-Compiler
Unlike the name, Skibidi is supposed to be an actually usable programming language, 
inspired by languages like  C++, Rust, and others. The name originated from
a joke between a friend of mine and me.

A simple Hello World program would look like this:
```skibidi
fn main() : i32 {
    std::println("Hello World");
    return 0;
}
```

A program to compute the fibonacci sequence:
```skibidi
fn main() : i32 {
    var length : u32 = 100; // compute 100 numbers after 0 and 1 of the sequence
    var a : mut u32 = 0;
    var b : mut u32 = 1;
    std::printlnf("{u32}\n{u32}", a, b);
    for([0..length]){
        var c : u32 = a + b;
        a = b;
        b = c;
        std::printlnf("{u32}", c);
    } 
    return 0;
}
```

`printlnf` is like `println`, but it formats the string and can insert values.